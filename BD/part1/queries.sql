use eventosdb;

create view EventosNaoLotados as
select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from evento e
    join edicao o
    on e.id = o.eventoID
	where o.nMulheres + o.nHomens < o.lotacao and date(o.inicio) >= date(now())
    order by inicio;



select * from EventosNaoLotados;










delimiter $$
create procedure InfoOrganizacao (in nome varchar(45))
begin
	select o.nome, o.email, o.pais, o.cidade, o.rua, 
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30,
            c.contacto 
		from organizacao as o
		join contacto c
		on o.id = c.id
		where o.nome like concat ('%', nome, '%');
end $$


call InfoOrganizacao('Carapau Vivo') $$












$$
create procedure InfoEdicao (in nEdicao int, titulo varchar(100))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
		from evento as e
		join edicao o
		on o.eventoID = e.id and o.nEdicao = nEdicao
		where e.titulo like concat ('%', titulo, '%');
end $$


call InfoEdicao(1, 'Party') $$











$$
create procedure EventosPorData (in dataEvento date)
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from evento as e
	join edicao o
	on o.eventoID = e.id
    where dataEvento >= date(o.inicio) and dataEvento <= date(o.fim);
end $$


call EventosPorData('2018-02-24') $$








$$
create procedure EventosPorIntervalo (in inicio date, fim date)
begin
	if (inicio >= fim) then
		select ('Datas invalidas') as msg;
	else
		select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
		from evento e
        join edicao o
        on e.id = o.eventoID
		where (date(o.fim) >= inicio and date(o.fim) <= fim) or
			(date(o.inicio) >= inicio and date(o.inicio) <= fim);
	end if;
end $$


call EventosPorIntervalo('2017-12-01', '2018-04-01') $$






$$
create procedure EventosCidade (in cidade varchar(30))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from evento e
	join edicao o on 
	o.eventoID = e.id
	where o.cidade = cidade and date(o.inicio) >= date(now())
		order by o.inicio;
end $$


call EventosCidade('Braga') $$







$$
create procedure EventosPais (in pais varchar(30))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from evento e
	join edicao o on 
	o.eventoID = e.id
	where o.pais = pais and date(o.inicio) >= date(now())
		order by o.inicio;
end $$

call EventosPais('Portugal') $$






$$
create procedure OrganizacoesEvento (in eventoID int)
begin
	select o.nome, o.email, o.pais, o.cidade, o.rua, 
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30,
            c.contacto
	from organizacao o
    join contacto c
    on c.orgID = o.id
    where o.id in (
		select orgID from organizacaoevento orgE
        where orgE.eventoID = eventoID
	);
end $$

call OrganizacoesEvento(1) $$






$$
create procedure EdicoesEvento (in titulo varchar(100))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from edicao o
    join evento e
    on o.eventoID = e.id
    where o.eventoID in (
		select id from evento
        where evento.titulo like concat ('%', titulo, '%')
    );
end $$

call EdicoesEvento('Jazz Fest') $$




$$
create procedure UltimaEdicaoEvento (in titulo varchar(100))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from edicao o
    join evento e
    on o.eventoID = e.id
    where o.eventoID in (
		select id from evento
        where evento.titulo like concat ('%', titulo, '%')
    )
    order by o.nEdicao desc
    limit 1;
end $$

call UltimaEdicaoEvento('Party') $$




$$
create procedure EventosOrganizacao (in nome varchar(45))
begin
	select org.nome, e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from edicao o
    join evento e
    on o.eventoID = e.id
    join organizacao org
    on org.nome like concat ('%', nome, '%')
    where e.id in (
		select orgE.eventoID from organizacaoevento orgE
					where orgE.orgID in (
						select org.id from organizacao org
						where org.nome like concat ('%', nome, '%'))	
	)
    order by o.inicio desc;
end $$

call EventosOrganizacao('Carapau') $$



$$
create procedure PessoasEvento(in nEdicao int, eventoID int)
begin
	select nome, email, sexo, dataNasc
    from pessoa p
    where p.id in (
		select pessoaID from pessoavaiedicao pe
		where pe.nEdicao = nEdicao and pe.eventoID = eventoID
    );
end $$

call PessoasEvento(1, 1) $$




$$
create procedure EventosPorPreco (in preco decimal(6,2))
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
            concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
            concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
            concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
            concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
	from edicao o
    join evento e
    on o.eventoID = e.id
    where o.preco <= preco and
		date(o.inicio) >= date(now())
	order by o.inicio;
end $$


call EventosPorPreco(50) $$


$$
create procedure EventosPorGenero (in sexo enum('M', 'F'))
begin
	if sexo = 'M' then
		select e.titulo,
				o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
				concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
				concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
				concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
				concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
				concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
		from edicao o
		join evento e
		on o.eventoID = e.id
		where date(o.inicio) >= date(now())
		order by o.inicio asc, o.nHomens desc;
	else 
		select e.titulo,
				o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
				concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
				concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
				concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18,
				concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre18_25,
				concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as entre25_30
		from edicao o
		join evento e
		on o.eventoID = e.id
		where date(o.inicio) >= date(now())
		order by o.inicio asc, o.nMulheres desc;
    end if;
end $$

call EventosPorGenero('F') $$







$$
create procedure EventosPorMenores18 ()
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
			concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
			concat(round(o.menores18 / (o.nMulheres + o.nHomens) * 100, 2), '%') as menores18
	from edicao o
	join evento e
	on o.eventoID = e.id
	where date(o.inicio) >= date(now())
	order by o.inicio asc, o.menores18 desc;
end $$


call EventosPorMenores18() $$



$$
create procedure EventosPorEntre18_25 ()
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
			concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
			concat(round(o.pessoas18_25 / (o.nMulheres + o.nHomens) * 100, 2), '%') as pessoas18_25
	from edicao o
	join evento e
	on o.eventoID = e.id
	where date(o.inicio) >= date(now())
	order by o.inicio asc, o.pessoas18_25 desc;
end $$

call EventosPorEntre18_25 $$





$$
create procedure EventosPorEntre25_30 ()
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
			concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
			concat(round(o.pessoas25_30 / (o.nMulheres + o.nHomens) * 100, 2), '%') as pessoas25_30
	from edicao o
	join evento e
	on o.eventoID = e.id
	where date(o.inicio) >= date(now())
	order by o.inicio asc, o.pessoas25_30 desc;
end $$

call EventosPorEntre25_30() $$




$$
create procedure EventosPorMaiores30 ()
begin
	select e.titulo,
			o.nEdicao, o.descricao, o.lotacao, o.inicio, o.fim, o.pais, o.cidade, o.rua,
			concat(round(o.nMulheres / (o.nMulheres + o.nHomens) * 100, 2), '%') as mulheres,
			concat(round(o.nHomens / (o.nMulheres + o.nHomens) * 100, 2), '%') as homens,
			concat(round((o.nMulheres + o.nHomens - o.menores18 - o.pessoas18_25 - o.pessoas25_30) / (o.nMulheres + o.nHomens) * 100, 2), '%') as maiores30
	from edicao o
	join evento e
	on o.eventoID = e.id
	where date(o.inicio) >= date(now())
	order by o.inicio asc, (o.nMulheres + o.nHomens - o.menores18 - o.pessoas18_25 - o.pessoas25_30) desc;
end $$

call EventosPorMaiores30() $$