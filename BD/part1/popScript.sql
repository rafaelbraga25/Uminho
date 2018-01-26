use eventosdb;

delete from evento;
delete from organizacao;
delete from pessoa;



call insertPessoa('mail2.com','Sr.Minado','M','1997-10-10');
call insertPessoa('mail.com','Sra.Fallonz','F','2004-10-10');
call insertPessoa('mail3.com', 'frounus','F','2005-10-10');
call insertPessoa('JoaoP.com', 'João Paiva', 'M', '1990-03-05');
call insertPessoa('MigSar.com', 'Miguel Saraiva', 'M', '1992-10-15');
call insertPessoa('JoanaL.com', 'Joana', 'F', '1995-02-17');
call insertPessoa('BeatrizP.com', 'Beatriz Passos', 'F', '1996-05-04');
call insertPessoa('MariaM.com', 'Maria Milhazes', 'F', '1997-06-06');
call insertPessoa('SofiaS.com', 'Sofia Saraiva', 'F', '1998-07-08');
call insertPessoa('AmandaD.com', 'Amanda Diamantina', 'F', '1993-09-08');
call insertPessoa('AnaM.com', 'Ana Miguel', 'F', '1994-12-18');
call insertPessoa('Laringz.com', 'Lara Esperibitas', 'F', '1989-10-26');
call insertPessoa('Bruningz.com', 'Bruna Lamaredi', 'F', '2000-01-09');
call insertPessoa('CarolinaCerq.com', 'Carolina Cerqueira', 'F', '2002-02-06');
call insertPessoa('IsabelMendes.com', 'Isabel Mendes', 'F', '2001-06-09');
call insertPessoa('Sofz.com', 'Sofia Menezes', 'F', '1998-05-08');
call insertPessoa('JP.com', 'João Pedro', 'M', '1990-05-08');
call insertPessoa('MiguelS.com', 'Miguel Simões', 'M', '1991-08-19');
call insertPessoa('RaulVilas.com', 'Raul Vilas', 'M', '2001-12-19');
call insertPessoa('FabingzCruz.com', 'Fabio Cruz', 'M', '2000-12-03');
call insertPessoa('BP.com', 'Bruno Pinto', 'M', '1999-09-15');
call insertPessoa('AnaQ.com', 'Ana Quintas', 'F', '1995-11-11');
call insertPessoa('JoaoSingz.com', 'João Sousa', 'M', '2003-09-09');
call insertPessoa('GerardoMs.com', 'Gerardo Sampaio', 'M', '1998-11-19');
call insertPessoa('RicsCorreia.com', 'Ricardo Correia', 'M', '1997-08-07');
call insertPessoa('SS.com', 'Sara Meireles', 'F', '1996-12-30');
call insertPessoa('RubenRods.com', 'Ruben Rodrigues', 'M', '2000-11-26');
call insertPessoa('PauloN.com', 'Paulo Nuno', 'M', '1985-12-01');
call insertPessoa('MOliv.com', 'Marta Oliveira', 'F', '1992-02-06');
call insertPessoa('MarcosG.com', 'Marcos Gomes', 'M', '1997-05-05');
call insertPessoa('HugoH.com', 'Hugo Henriques', 'M', '1993-09-29');
call insertPessoa('BeatriS.com', 'Beatriz Sá', 'F', '1994-12-01');
call insertPessoa('RicardoS.com', 'Ricardo Silva', 'M', '1995-01-01');
call insertPessoa('FilipeM.com', 'Filipe Miguel', 'M', '1997-10-10');
call insertPessoa('JorgeF.com', 'Jorge Fernandes', 'M', '1999-12-12');
call insertPessoa('VitorM.com', 'Vitor Mendes', 'M', '2001-09-29');
call insertPessoa('AndreS.com', 'André Silva', 'M', '2002-12-31');
call insertPessoa('ZeP.com', 'José Pedro', 'M', '1990-01-01');
call insertPessoa('DaniN.com', 'Daniel Nogueira', 'M', '1991-02-01');
call insertPessoa('Cr7Ronaldo.com', 'Cristiano Ronaldo' , 'M', '1985-02-05');




call insertEvento('PartyDoEsperibitas');
call insertEvento('Paredes de Moura');
call insertEvento('Baile Finalistas');
call insertEvento('Jantar de Curso');
call insertEvento('Quizz');
call insertEvento('Jazz Fest');
call insertEvento('NOSes Alive');
call insertEvento('Vilar de Mouras');
call insertEvento('Enterro da Cadela');
call insertEvento('Noite da mulher');
call insertEvento('Shot O.clock');
call insertEvento('Happy 9 hours');
call insertEvento('Until Dawn');
call insertEvento('Noite dos Cotas');






call insertOrganizacao('FestivaleirosXPTO.com', 'FestivaleirosXPTO', 'Portugal', 'Lisboa', 'Rua do rossio');
call insertOrganizacao('ListaX.com', 'Comissão festas', 'Portugal', 'Braga', 'Rua do Souto');
call insertOrganizacao('CarapauVivo.com', 'Carapau Vivo', 'Portugal', 'Braga', 'Rua do peixe');
call insertOrganizacao('CafeDaSogra.com', 'Café da Sogra', 'Portugal', 'Braga', 'Rua nova de Santa cruz');



 
call insertFoto (1,'/fotos/fotografia1.jpg');
call insertFoto (2,'/fotos/fotografia2.jpg');
call insertFoto (3,'/fotos/fotografia3.jpg');
call insertFoto (4,'/fotos/fotografia4.jpg');
call insertFoto (5,'/fotos/fotografia5.jpg');
call insertFoto (6,'/fotos/fotografia6.jpg');
call insertFoto (7,'/fotos/fotografia7.jpg');
call insertFoto (8,'/fotos/fotografia8.jpg');
call insertFoto (9,'/fotos/fotografia9.jpg');
call insertFoto (10,'/fotos/fotografiad.jpg');
call insertFoto (11,'/fotos/fotografia.jpg');
call insertFoto (12,'/fotos/fotografsdsdsdia.jpg');
call insertFoto (13,'/fotos/fotografia10.jpg');
call insertFoto (14,'/fotos/fotografdsdsdsddsddffia.jpg');
call insertFoto (15,'/fotos/fotografia11.jpg');
call insertFoto (16,'/fotos/fotografia12.jpg');
call insertFoto (17,'/fotos/fotografia13.jpg');
call insertFoto (18,'/fotos/fotografia14.jpg');
call insertFoto (19,'/fotos/fotografia15.jpg');
call insertFoto (20,'/fotos/fotografia16.jpg');
call insertFoto (21,'/fotos/fotografia17.jpg');
call insertFoto (22,'/fotos/fotografia18.jpg');
call insertFoto (23,'/fotos/fotografia19.jpg');
call insertFoto (24,'/fotos/fotografia20.jpg');
call insertFoto (25,'/fotos/fotografia21.jpg');
call insertFoto (26,'/fotos/fotografia22.jpg');
call insertFoto (27,'/fotos/fotografia23.jpg');
call insertFoto (28,'/fotos/fotografia24.jpg');
call insertFoto (29,'/fotos/fotografia25.jpg');
call insertFoto (30,'/fotos/fotografia26.jpg');
call insertFoto (31,'/fotos/fotografia27.jpg');
call insertFoto (32,'/fotos/fotografia28.jpg');
call insertFoto (33,'/fotos/fotografia29.jpg');
call insertFoto (34,'/fotos/fotografia30.jpg');
call insertFoto (35,'/fotos/fotografia31.jpg');
call insertFoto (36,'/fotos/fotografia32.jpg');
call insertFoto (37,'/fotos/fotografia33.jpg');
call insertFoto (38,'/fotos/fotografia34.jpg');
call insertFoto (39,'/fotos/fotografia35.jpg');
call insertFoto (40,'/fotos/fotografia36.jpg');
call insertFoto (41,'/fotos/fotografia37.jpg');
call insertFoto (42,'/fotos/fotografia38.jpg');







call insertEdicao (1, 1, 'Entrada Grátis', 0, 150, '2016-08-12 20:30:00', '2016-08-13 07:00:00', 'Portugal', 'Braga', 'Rua da festa');
call insertEdicao (2, 1, 'Entrada Grátis', 0, 150, '2017-12-28 20:30:00', '2016-12-29 07:00:00','Portugal', 'Braga', 'Rua da festa');
call insertEdicao (1, 2, 'Música fantástica', 90, 20000, '2018-08-14 15:30:00', '2018-08-19 19:00:00','Portugal', 'Paredes de Moura', 'Rua do acampamento');
call insertEdicao (1, 3, 'Dançar até de manha', 25,  500, '2018-06-10 20:30:00', '2018-06-11 05:00:00','Portugal', 'Braga', 'Rua do baile');
call insertEdicao (1, 4, 'Convivio e vinhaça', 8, 150, '2017-09-13 20:00:00', '2017-09-14 00:00:01', 'Portugal', 'Braga', 'Rua do jantar');
call insertEdicao (2, 4, 'Convivio e cerveja', 8, 150, '2017-12-06 20:00:00', '2017-12-07 00:00:01', 'Portugal', 'Braga', 'Rua do jantar');
call insertEdicao (1, 5, 'Poe em causa o teu conhecimento', 2.5, 100, '2017-12-01 21:00:00', '2017-12-02 01:30:00', 'Portugal', 'Braga', 'Rua Nova de Santa Cruz');
call insertEdicao (2, 5, 'Poe em causa o teu conhecimento', 2.5, 100, '2017-12-13 21:00:00', '2017-12-14 01:30:00', 'Portugal', 'Braga', 'Rua Nova de Santa Cruz');
call insertEdicao (1, 6, 'Bom Jazz e o melhor convivio', 30, 10000, '2018-02-20 13:00:00', '2018-02-25 19:00:00', 'Portugal', 'Lisboa', 'Rua do jazz');
call insertEdicao (1, 7, 'Anda destruir connosco', 90, 30000, '2018-06-23 13:00:00', '2018-06-29 19:00:00', 'Portugal', 'Lisboa', 'Rua incrivel');
call insertEdicao (1, 8, 'Para bons apreciadores de música', 60, 10000, '2018-05-18 19:00:00', '2018-05-21 05:00:00', 'Portugal', 'Mouros', 'Rua da boa musica');
call insertEdicao (1, 9, 'Vem despedir-te do ano letivo em grande', 40, 5000, '2017-06-06 22:00:00', '2017-06-07 08:00:00', 'Portugal', 'Braga', 'Rua do estádio');
call insertEdicao (2, 9, 'Vem despedir-te do ano letivo em grande', 40, 5000, '2018-06-06 22:00:00', '2018-06-07 08:00:00', 'Portugal', 'Braga', 'Rua do estádio');
call insertEdicao (1, 10, 'Para elas e para eles', 12.5, 1000, '2017-12-29 22:00:00', '2017-12-30 06:00:00', 'Portugal', 'Braga', 'Rua do peixe');
call insertEdicao (1, 11, 'Shot grátis de hora a hora', 15, 1000, '2018-01-27 22:00:00', '2018-01-28 06:00:00', 'Portugal', 'Braga', 'Rua do peixe');
call insertEdicao (1, 12, 'Festa inédita Happy hour toda a noite finos 50cent', 20, 1000, '2018-01-21 22:00:00', '2018-01-22 06:00:00', 'Portugal', 'Braga', 'Rua do peixe');
call insertEdicao (1, 13, 'Sunset prolongado pela noite dentro com os melhor djs', 20, 3000, '2017-12-20 15:00:00', '2017-12-21 11:00:00', 'Portugal', 'Matosinhos', 'Rua da anemona');
call insertEdicao (1, 14, 'Musica anos 1900s no melhor ambiente', 17.5, 300, '2018-04-01 21:00:00', '2018-04-02 04:00:00', 'Portugal', 'Braga', 'Rua clássica');





call insertcontacto (1, '255658659', 'Telefone');
call insertcontacto (2, '918756386', 'Telemóvel');
call insertcontacto (3, 'carapauvivoon.com', 'Website');
call insertcontacto (4, '255698745', 'Telefone');





call insertOrganizacaoEvento (1, 2);
call insertOrganizacaoEvento (1, 6);
call insertOrganizacaoEvento (1, 7);
call insertOrganizacaoEvento (1, 8);
call insertOrganizacaoEvento (1, 9);
call insertOrganizacaoEvento (1, 13);
call insertOrganizacaoEvento (2, 3);
call insertOrganizacaoEvento (2, 4);
call insertOrganizacaoEvento (2, 1);
call insertOrganizacaoEvento (3, 10);
call insertOrganizacaoEvento (3, 11);
call insertOrganizacaoEvento (3, 12);
call insertOrganizacaoEvento (4, 5);
call insertOrganizacaoEvento (4, 14);
 












call insertPessoaVaiEdicao (5, 1, 1);
call insertPessoaVaiEdicao (10,1,1);
call insertPessoaVaiEdicao (15,1,1);
call insertPessoaVaiEdicao (20,1,1);
call insertPessoaVaiEdicao (25,1,1);
call insertPessoaVaiEdicao (30,1,1);
call insertPessoaVaiEdicao (35,1,1);
call insertPessoaVaiEdicao (40,1,1);
call insertPessoaVaiEdicao (45,1,1);
call insertPessoaVaiEdicao (50,1,1);
call insertPessoaVaiEdicao (52,1,1);
call insertPessoaVaiEdicao (1,2,1);
call insertPessoaVaiEdicao (6,2,1);
call insertPessoaVaiEdicao (11,2,1);
call insertPessoaVaiEdicao (16,2,1);
call insertPessoaVaiEdicao (21,2,1);
call insertPessoaVaiEdicao (26,2,1);
call insertPessoaVaiEdicao (31,2,1);
call insertPessoaVaiEdicao (36,2,1);
call insertPessoaVaiEdicao (41,2,1);
call insertPessoaVaiEdicao (46,2,1);
call insertPessoaVaiEdicao (51,2,1);
call insertPessoaVaiEdicao (2,3,1);
call insertPessoaVaiEdicao (7,3,1);
call insertPessoaVaiEdicao (12,3,1);
call insertPessoaVaiEdicao (17,3,1);
call insertPessoaVaiEdicao (22,3,1);
call insertPessoaVaiEdicao (27,3,1);
call insertPessoaVaiEdicao (32,3,1);
call insertPessoaVaiEdicao (37,3,1);
call insertPessoaVaiEdicao (42,3,1);
call insertPessoaVaiEdicao (47,3,1);
call insertPessoaVaiEdicao (52,3,1);
call insertPessoaVaiEdicao (3,4,1);
call insertPessoaVaiEdicao (8,4,1);
call insertPessoaVaiEdicao (13,4,1);
call insertPessoaVaiEdicao (18,4,1);
call insertPessoaVaiEdicao (23,4,1);
call insertPessoaVaiEdicao (28,4,1);
call insertPessoaVaiEdicao (33,4,1);
call insertPessoaVaiEdicao (38,4,1);
call insertPessoaVaiEdicao (43,4,1);
call insertPessoaVaiEdicao (48,4,1);
call insertPessoaVaiEdicao (1,5,1);
call insertPessoaVaiEdicao (3,5,1);
call insertPessoaVaiEdicao (5,5,1);
call insertPessoaVaiEdicao (7,5,1);
call insertPessoaVaiEdicao (9,5,1);
call insertPessoaVaiEdicao (15,5,1);
call insertPessoaVaiEdicao (13,5,1);
call insertPessoaVaiEdicao (11,5,1);
call insertPessoaVaiEdicao (20,5,1);
call insertPessoaVaiEdicao (22,5,1);
call insertPessoaVaiEdicao (24,5,1);
call insertPessoaVaiEdicao (26,5,1);
call insertPessoaVaiEdicao (35,5,1);
call insertPessoaVaiEdicao (37,5,1);
call insertPessoaVaiEdicao (39,5,1);
call insertPessoaVaiEdicao (45,5,1);
call insertPessoaVaiEdicao (3,6,1);
call insertPessoaVaiEdicao (6,6,1);
call insertPessoaVaiEdicao (9,6,1);
call insertPessoaVaiEdicao (12,6,1);
call insertPessoaVaiEdicao (15,6,1);
call insertPessoaVaiEdicao (18,6,1);
call insertPessoaVaiEdicao (21,6,1);
call insertPessoaVaiEdicao (24,6,1);
call insertPessoaVaiEdicao (27,6,1);
call insertPessoaVaiEdicao (30,6,1);
call insertPessoaVaiEdicao (33,6,1);
call insertPessoaVaiEdicao (36,6,1);
call insertPessoaVaiEdicao (39,6,1);
call insertPessoaVaiEdicao (40,6,1);
call insertPessoaVaiEdicao (42,6,1);
call insertPessoaVaiEdicao (45,6,1);
call insertPessoaVaiEdicao (48,6,1);
call insertPessoaVaiEdicao (51,6,1);
call insertPessoaVaiEdicao (7,7,1);
call insertPessoaVaiEdicao (14,7,1);
call insertPessoaVaiEdicao (21,7,1);
call insertPessoaVaiEdicao (28,7,1);
call insertPessoaVaiEdicao (35,7,1);
call insertPessoaVaiEdicao (42,7,1);
call insertPessoaVaiEdicao (49,7,1);
call insertPessoaVaiEdicao (52,7,1);
call insertPessoaVaiEdicao (17,7,1);
call insertPessoaVaiEdicao (27,7,1);
call insertPessoaVaiEdicao (1,8,1);
call insertPessoaVaiEdicao (6,8,1);
call insertPessoaVaiEdicao (12,8,1);
call insertPessoaVaiEdicao (18,8,1);
call insertPessoaVaiEdicao (24,8,1);
call insertPessoaVaiEdicao (30,8,1);
call insertPessoaVaiEdicao (36,8,1);
call insertPessoaVaiEdicao (42,8,1);
call insertPessoaVaiEdicao (48,8,1);
call insertPessoaVaiEdicao (51,8,1);
call insertPessoaVaiEdicao (21,8,1);
call insertPessoaVaiEdicao (31,8,1);
call insertPessoaVaiEdicao (2,9,1);
call insertPessoaVaiEdicao (6,9,1);
call insertPessoaVaiEdicao (10,9,1);
call insertPessoaVaiEdicao (14,9,1);
call insertPessoaVaiEdicao (18,9,1);
call insertPessoaVaiEdicao (22,9,1);
call insertPessoaVaiEdicao (26,9,1);
call insertPessoaVaiEdicao (30,9,1);
call insertPessoaVaiEdicao (34,9,1);
call insertPessoaVaiEdicao (38,9,1);
call insertPessoaVaiEdicao (42,9,1);
call insertPessoaVaiEdicao (46,9,1);
call insertPessoaVaiEdicao (50,9,1);
call insertPessoaVaiEdicao (15,9,1);
call insertPessoaVaiEdicao (21,9,1);
call insertPessoaVaiEdicao (23,9,1);
call insertPessoaVaiEdicao (37,9,1);
call insertPessoaVaiEdicao (39,9,1);
call insertPessoaVaiEdicao (9,10,1);
call insertPessoaVaiEdicao (18,10,1);
call insertPessoaVaiEdicao (27,10,1);
call insertPessoaVaiEdicao (36,10,1);
call insertPessoaVaiEdicao (45,10,1);
call insertPessoaVaiEdicao (52,10,1);
call insertPessoaVaiEdicao (3,10,1);
call insertPessoaVaiEdicao (7,10,1);
call insertPessoaVaiEdicao (11,10,1);
call insertPessoaVaiEdicao (15,10,1);
call insertPessoaVaiEdicao (19,10,1);
call insertPessoaVaiEdicao (23,10,1);
call insertPessoaVaiEdicao (31,10,1);
call insertPessoaVaiEdicao (35,10,1);
call insertPessoaVaiEdicao (39,10,1);
call insertPessoaVaiEdicao (41,10,1);
call insertPessoaVaiEdicao (1,11,1);
call insertPessoaVaiEdicao (2,11,1);
call insertPessoaVaiEdicao (3,11,1);
call insertPessoaVaiEdicao (5,11,1);
call insertPessoaVaiEdicao (8,11,1);
call insertPessoaVaiEdicao (13,11,1);
call insertPessoaVaiEdicao (21,11,1);
call insertPessoaVaiEdicao (34,11,1);
call insertPessoaVaiEdicao (52,11,1);
call insertPessoaVaiEdicao (3,12,1);
call insertPessoaVaiEdicao (9,12,1);
call insertPessoaVaiEdicao (15,12,1);
call insertPessoaVaiEdicao (18,12,1);
call insertPessoaVaiEdicao (34,12,1);
call insertPessoaVaiEdicao (26,12,1);
call insertPessoaVaiEdicao (29,12,1);
call insertPessoaVaiEdicao (33,12,1);
call insertPessoaVaiEdicao (45,12,1);
call insertPessoaVaiEdicao (50,12,1);
call insertPessoaVaiEdicao (48,12,1);
call insertPessoaVaiEdicao (42,12,1);
call insertPessoaVaiEdicao (1,13,1);
call insertPessoaVaiEdicao (11,13,1);
call insertPessoaVaiEdicao (21,13,1);
call insertPessoaVaiEdicao (31,13,1);
call insertPessoaVaiEdicao (41,13,1);
call insertPessoaVaiEdicao (51,13,1);
call insertPessoaVaiEdicao (9,13,1);
call insertPessoaVaiEdicao (19,13,1);
call insertPessoaVaiEdicao (29,13,1);
call insertPessoaVaiEdicao (39,13,1);
call insertPessoaVaiEdicao (51,14,1);
call insertPessoaVaiEdicao (50,14,1);
call insertPessoaVaiEdicao (2,14,1);
call insertPessoaVaiEdicao (5,14,1);
call insertPessoaVaiEdicao (31,14,1);
call insertPessoaVaiEdicao (32,14,1);
call insertPessoaVaiEdicao (33,14,1);
call insertPessoaVaiEdicao (34,14,1);
call insertPessoaVaiEdicao (35,14,1);
call insertPessoaVaiEdicao (36,14,1);
call insertPessoaVaiEdicao (37,14,1);
call insertPessoaVaiEdicao (15,14,1);
call insertPessoaVaiEdicao (14,14,1);
call insertPessoaVaiEdicao (13,14,1);
call insertPessoaVaiEdicao (12,14,1);
call insertPessoaVaiEdicao (11,14,1);
call insertPessoaVaiEdicao (10,14,1);
call insertPessoaVaiEdicao (9,14,1);


