
Create Database ChewieDB;


CREATE TABLE ChewieDB.dbo.Estabelecimento (
  ID INT IDENTITY(1,1) NOT NULL PRIMARY KEY,
  Nome VARCHAR(45) NOT NULL,
  Foto TEXT NULL,
  Descricao TEXT NULL,
  Total_Avaliacao INT NOT NULL DEFAULT 0,
  Numero_Avaliacao INT NOT NULL DEFAULT 0,
  Media_Avaliacao DECIMAL(2,1) NOT NULL DEFAULT 0,
  Morada VARCHAR(50) NOT NULL
);


CREATE TABLE ChewieDB.dbo.Prato (
  Nome VARCHAR(50) NOT NULL PRIMARY KEY
);


CREATE TABLE ChewieDB.dbo.Utilizador (
  Username VARCHAR(24) NOT NULL PRIMARY KEY,
  UserPass VARCHAR(24) NOT NULL
);


CREATE TABLE  ChewieDB.dbo.Horario_Funcionamento
(
	Dia INT NOT NULL,
	Estabelecimento INT FOREIGN KEY REFERENCES ChewieDB.dbo.Estabelecimento(ID) NOT NULL,
	Inicio TIME NOT NULL,
	Fim TIME NOT NULL,
	CONSTRAINT PK_Horario PRIMARY KEY(Dia, Estabelecimento, Inicio, Fim)
);


CREATE TABLE  ChewieDB.dbo.Contacto
(
	Tipo VARCHAR(16) NOT NULL,
	Descricao VARCHAR(50) NOT NULL,
	Estabelecimento INT FOREIGN KEY REFERENCES ChewieDB.dbo.Estabelecimento(ID) NOT NULL,
	CONSTRAINT PK_Contacto PRIMARY KEY(Tipo, Descricao, Estabelecimento)
);


CREATE TABLE  ChewieDB.dbo.Critica
(
	Avaliacao INT NULL,
	Comentario VARCHAR(160) NULL,
	DataComentario DATETIME NULL,
	Estabelecimento INT FOREIGN KEY REFERENCES ChewieDB.dbo.Estabelecimento(ID) NOT NULL,
	Utilizador VARCHAR(24) FOREIGN KEY REFERENCES ChewieDB.dbo.Utilizador(Username) NOT NULL,
	CONSTRAINT PK_Critica PRIMARY KEY(Estabelecimento, Utilizador)
);


CREATE TABLE  ChewieDB.dbo.Historico
(
	DataPesquisa DATETIME NOT NULL,
	Estabelecimento INT FOREIGN KEY REFERENCES ChewieDB.dbo.Estabelecimento(ID) NOT NULL,
	Utilizador VARCHAR(24) FOREIGN KEY REFERENCES ChewieDB.dbo.Utilizador(Username) NOT NULL,
	Prato VARCHAR(50) FOREIGN KEY REFERENCES ChewieDB.dbo.Prato(Nome) NOT NULL,
	CONSTRAINT PK_Historico PRIMARY KEY(DataPesquisa, Estabelecimento, Utilizador, Prato)
);


CREATE TABLE  ChewieDB.dbo.Ementa
(
	Detalhe VARCHAR(50),
	Valor BIT,
	Estabelecimento INT FOREIGN KEY REFERENCES ChewieDB.dbo.Estabelecimento(ID) NOT NULL,
	Prato VARCHAR(50) FOREIGN KEY REFERENCES ChewieDB.dbo.Prato(Nome) NOT NULL,
	CONSTRAINT PK_Ementa PRIMARY KEY(Detalhe, Estabelecimento, Prato)
);


CREATE TABLE  ChewieDB.dbo.Preferencias
(
	Preferencia VARCHAR(50),
	Contador INT DEFAULT 0,
	Valor BIT,
	Utilizador VARCHAR(24) FOREIGN KEY REFERENCES ChewieDB.dbo.Utilizador(Username) NOT NULL,
	Prato VARCHAR(50) FOREIGN KEY REFERENCES ChewieDB.dbo.Prato(Nome) NOT NULL,
	CONSTRAINT PK_Preferencias PRIMARY KEY(Preferencia, Utilizador, Prato)
);
