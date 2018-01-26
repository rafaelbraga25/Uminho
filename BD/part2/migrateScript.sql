use eventosdb;

# Verificar o caminho dos ficheiros
select @@GLOBAL.secure_file_priv; 

# Pessoas
select 'id', 'email', 'nome', 'sexo', 'dataNasc'
union all
select * from pessoa
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/persons.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# Fotos
select 'id', 'pessoaID', 'foto'
union all
select * from foto
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/photos.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# PessoasVaoEdicoes
select 'pessoaID', 'eventoID', 'nEdicao'
union all
select * from pessoavaiedicao
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/personsEditions.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# Edicoes
select 'nEdicao', 'eventoID', 'descricao', 'preco', 
	'lotacao', 'inicio', 'fim', 'pais', 'cidade', 'rua',
    'nMulheres', 'nHomens', 'menores18', 'pessoas18_25', 'pessoas25_30'
union all
select * from edicao
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/editions.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# Eventos
select 'id', 'titulo'
union all
select * from evento
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/events.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# OrganizacoesEventos
select 'orgID', 'eventoID'
union all
select * from organizacaoevento
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/orgsEvents.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# Organizacoes
select 'id', 'email', 'nome', 'pais', 
	'cidade', 'rua', 'nMulheres', 'nHomens', 
    'menores18', 'pessoas18_25', 'pessoas25_30'
union all
select * from organizacao
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/orgs.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';


# Contactos
select 'id', 'orgID', 'contacto', 'tipo'
union all
select * from contacto
into outfile 'C:/ProgramData/MySQL/MYSQL Server 5.7/Uploads/contacts.csv'
fields terminated by ','
enclosed by '"'
lines terminated by '\n';