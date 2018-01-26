USE  eventosdb;

SET SQL_SAFE_UPDATES = 0;

delimiter $$

create procedure insertPessoa(in e varchar(45), n varchar(45), s enum('M', 'F'), d date)
begin
	declare erro bool default 0;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		insert 
			into pessoa (email, nome, sexo, dataNasc)
            values (e, n, s, d);
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela Pessoa') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$


create procedure insertOrganizacao(in e varchar(45), n varchar(45), p varchar(30), c varchar(30), r varchar(50))
begin
	declare erro bool default 0;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		insert 
			into organizacao (email, nome, pais, cidade, rua)
            values (e, n, p, c, r);
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela Organizacao') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$


create procedure insertEvento(in n varchar(100))
begin
	declare erro bool default 0;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		insert 
			into evento (titulo)
            values (n);
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela Evento') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end;
$$



$$
create procedure insertFoto(in p int, f varchar(1000))
begin
	declare erro bool default 0;
    declare existe bool default 1;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		set existe = (select id from pessoa where id = p);

		if existe then
			insert 
				into foto (pessoaID, foto) 
				values (p, f);
		else
			select ('A pessoa não existe') as msg;
            set erro = 1;
		end if;
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela Foto') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$



$$
create procedure insertEdicao(in ne int, e int, d varchar(1000), p decimal(6,2), 
							  l int, i datetime, f datetime, pa varchar (30), c varchar(30), r varchar(50))
begin
	declare erro bool default 0;
    declare fimUltimaEdicao datetime;
    declare existe bool default 1;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		set existe = (select id from evento where id = e);

		if existe then
			if i >= f then
				select ('Data de inicio é incompatível com a data de fim do evento') as msg;
				set erro = 1;
			else 
				set fimUltimaEdicao = (select fim from edicao 
									where e = eventoID
									order by nEdicao desc
									limit 1);
			
				if fimUltimaEdicao >= i then
					select ('Data de inicio da edicao atual é incompativel com as edições anteriores') as msg;
					set erro = 1;
				else
					insert 
						into edicao (nEdicao, eventoID, descricao, preco, lotacao, inicio, fim, pais, cidade, rua) 
						values (ne, e, d, p, l, i, f, pa, c, r);
				end if;
			end if;
		else
			select ('O evento associado à edição não existe') as msg;
			set erro = 1;
		end if;
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela EdicaoEvento') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$



$$
create procedure insertContacto (in o int, c varchar (45), t enum('telefone', 'telemovel', 'website'))
begin
	declare erro bool default 0;
    declare existe bool default 1;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		set existe = (select id from organizacao where id = o);
        
        if existe then
			insert 
				into contacto (orgID, contacto, tipo) 
				values (o, c, t);
		else
			select ('A organização associada ao contacto não existe') as msg;
			set erro = 1;
		end if;
            
		if erro then
			select ('Erro ao adicionar uma entrada na tabela Contacto') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$



create procedure insertOrganizacaoEvento(in o int, e int)
begin
	declare erro bool default 0;
    declare existeOrg bool default 1;
    declare existeE bool default 1;
    declare continue handler for sqlexception set erro = 1;

	start transaction;
		
        set existeOrg = (select id from organizacao where id = o);
        set existeE = (select id from evento where id = e);
        
        if existeOrg and existeE then
			insert 
				into organizacaoevento (orgID, eventoID) 
				values (o, e);
		else 
			select ('Organização ou evento inválidos') as msg;
			set erro = 1;
		end if;
            
		if erro then
			select ('Erro ao indicar que um evento pertence a uma organização') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$

$$
create procedure insertPessoaVaiEdicao(in p int, e int, ne int)
begin
	declare erro bool default 0;
	declare existePessoa bool default 1;
    declare existeE bool default 1;
    declare s enum ('M', 'F');
    declare idade int;
	declare d date;
    declare continue handler for sqlexception set erro = 1;

	start transaction;

		set existePessoa = (select id from pessoa where id = p);
        set existeE = (select eventoID from edicao where eventoID = e and ne = nEdicao);

		if existePessoa and existeE then
			set d = (select dataNasc from pessoa where id = p);
			set idade = (select extract(year from (from_days(datediff(now(), d)))) + 0);
			set s = (select sexo from pessoa where id = p);
			
			if (s = 'M') then
				update edicao 
					set nHomens = nHomens + 1 
					where eventoID = e and nEdicao = ne;
			   
				update organizacao as og
					set og.nHomens = og.nHomens + 1
					where og.id in (
						select orgID from organizacaoevento 
						where eventoID = e
					);
			else
				update edicao 
					set nMulheres = nMulheres + 1
					where eventoID = e and nEdicao = ne;
				
				update organizacao as og
					set og.nMulheres = og.nMulheres + 1
					where og.id in (
						select orgID from organizacaoevento 
						where eventoID = e
					);
			end if;
			
			if (idade >= 18 and idade <= 25) then
				update edicao
					set pessoas18_25 = pessoas18_25 + 1 
					where eventoID = e and nEdicao = ne;
					
		
			elseif (idade >= 25 and idade <= 30) then
				update edicao 
					set pessoas25_30 = pessoas25_30 + 1
					where eventoID = e and nEdicao = ne;
					
				update organizacao as og
					set og.pessoas25_30 = og.pessoas25_30 + 1
					where og.id in (
						select orgID from organizacaoevento 
						where eventoID = e
					);
			elseif (idade < 18) then
				update edicao 
					set menores18 = menores18 + 1
					where eventoID = e and nEdicao = ne;
					
				update organizacao as og
					set og.menores18 = og.menores18 + 1
					where og.id in (
						select orgID from organizacaoevento 
						where eventoID = e
					);
			end if;
			
			insert 
				into pessoavaiedicao (pessoaID, eventoID, nEdicao) 
				values (p, e, ne);
		else
			select ('Pessoa ou edição inválidas') as msg;
		 	set erro = 1;
		end if;
            
		if erro then
			select ('Erro ao indicar que uma pessoa vai a uma edição de evento') as msg;
			rollback;
		else 
			select ('Operação efetuada com sucesso') as msg;
			commit;
		end if;
end; 
$$