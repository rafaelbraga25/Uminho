use scdb;
set SQL_SAFE_UPDATES = 0;

delete from cu;
delete from teacher;
delete from student;

insert into cu
values ('EES',1,1);

insert into shift
values ('EES','T1',1,100,10);

insert into timetable
values('EES','T1',2,9,11);

insert into shift
values ('EES','PL1',0,20,10);

insert into timetable
values('EES','PL1',2,11,13);

insert into shift
values ('EES','PL3',0,20,10);

insert into timetable
values('EES','PL3',4,9,11);

insert into shift
values ('EES','PL5',0,20,10);

insert into timetable
values('EES','PL5',4,11,13);

insert into shift
values ('EES','PL6',0,20,10);

insert into timetable
values('EES','PL6',4,13,15);

insert into shift
values ('EES','PL2',0,20,10);

insert into timetable
values('EES','PL2',6,14,16);

insert into shift
values ('EES','PL4',0,20,10);

insert into timetable
values('EES','PL4',6,16,18);

insert into shift
values ('EES','PL7',0,20,10);

insert into timetable
values('EES','PL7',6,11,13);

insert into cu
values ('PF',1,1);

insert into shift
values ('PF','TP1',0,20,10);

insert into timetable
values('PF','TP1',2,11,13);

insert into shift
values ('PF','TP2',0,20,10);

insert into timetable
values('PF','TP2',2,11,13);

insert into shift
values ('PF','T1',1,50,10);

insert into timetable
values('PF','T1',2,14,15);

insert into timetable
values('PF','T1',6,10,11);

insert into shift
values ('PF','T2',1,50,10);

insert into timetable
values('PF','T2',2,14,15);

insert into timetable
values('PF','T2',6,10,11);

insert into shift
values ('PF','TP5',0,20,10);

insert into timetable
values('PF','TP5',4,9,11);

insert into shift
values ('PF','TP7',0,20,10);

insert into timetable
values('PF','TP7',4,9,11);

insert into shift
values ('PF','TP3',0,20,10);

insert into timetable
values('PF','TP3',4,11,13);

insert into shift
values ('PF','TP6',0,20,10);

insert into timetable
values('PF','TP6',4,11,13);

insert into shift
values ('PF','TP4',0,20,10);

insert into timetable
values('PF','TP4',6,11,13);

insert into shift
values ('PF','TP8',0,20,10);

insert into timetable
values('PF','TP8',6,11,13);

insert into cu
values ('LI1',1,1);

insert into shift
values ('LI1','PL1',0,15,10);

insert into timetable
values('LI1','PL1',2,11,13);

insert into shift
values ('LI1','PL7',0,15,10);

insert into timetable
values('LI1','PL7',2,11,13);

insert into shift
values ('LI1','PL6',0,15,10);

insert into timetable
values('LI1','PL6',4,9,11);

insert into shift
values ('LI1','PL3',0,15,10);

insert into timetable
values('LI1','PL3',4,9,11);

insert into shift
values ('LI1','PL8',0,15,10);

insert into timetable
values('LI1','PL8',4,11,13);

insert into shift
values ('LI1','PL4',0,15,10);

insert into timetable
values('LI1','PL4',4,11,13);

insert into shift
values ('LI1','PL5',0,35,10);

insert into timetable
values('LI1','PL5',6,11,13);

insert into shift
values ('LI1','PL2',0,35,10);

insert into timetable
values('LI1','PL2',6,11,13);

insert into cu
values ('CALC',1,1);

insert into shift
values ('CALC','TP5',0,30,10);

insert into timetable
values('CALC','TP5',2,15,17);

insert into timetable
values('CALC','TP5',6,14,16);

insert into shift
values ('CALC','TP1',0,30,10);

insert into timetable
values('CALC','TP1',3,9,11);

insert into timetable
values('CALC','TP1',5,9,11);

insert into shift
values ('CALC','TP2',0,30,10);

insert into timetable
values('CALC','TP2',3,11,13);

insert into timetable
values('CALC','TP2',5,11,13);

insert into shift
values ('CALC','TP3',0,30,10);

insert into timetable
values('CALC','TP3',3,14,16);

insert into timetable
values('CALC','TP3',5,14,16);

insert into shift
values ('CALC','TP4',0,30,10);

insert into timetable
values('CALC','TP4',3,14,16);

insert into timetable
values('CALC','TP4',5,14,16);

insert into cu
values ('TMD',1,1);

insert into shift
values ('TMD','TP3',0,40,10);

insert into timetable
values('TMD','TP3',3,9,11);

insert into timetable
values('TMD','TP3',5,9,11);

insert into shift
values ('TMD','TP4',0,40,10);

insert into timetable
values('TMD','TP4',3,11,13);

insert into timetable
values('TMD','TP4',5,11,13);

insert into shift
values ('TMD','TP1',0,40,10);

insert into timetable
values('TMD','TP1',3,14,16);

insert into timetable
values('TMD','TP1',5,14,16);

insert into shift
values ('TMD','TP2',0,40,10);

insert into timetable
values('TMD','TP2',3,14,16);

insert into timetable
values('TMD','TP2',5,14,16);

insert into cu
values ('ALG',1,1);

insert into shift
values ('ALG','TP1',0,40,10);

insert into timetable
values('ALG','TP1',3,9,11);

insert into timetable
values('ALG','TP1',5,9,11);

insert into shift
values ('ALG','TP3',0,40,10);

insert into timetable
values('ALG','TP3',3,9,11);

insert into timetable
values('ALG','TP3',5,9,11);

insert into shift
values ('ALG','TP2',0,40,10);

insert into timetable
values('ALG','TP2',3,11,13);

insert into timetable
values('ALG','TP2',5,11,13);

insert into shift
values ('ALG','TP4',0,40,10);

insert into timetable
values('ALG','TP4',3,11,13);

insert into timetable
values('ALG','TP4',5,11,13);

insert into cu
values ('EA',2,1);

insert into shift
values ('EA','T1',1,100,10);

insert into timetable
values('EA','T1',2,13,15);

insert into shift
values ('EA','TP3',0,30,10);

insert into timetable
values('EA','TP3',2,15,17);

insert into shift
values ('EA','TP1',0,30,10);

insert into timetable
values('EA','TP1',2,17,19);

insert into shift
values ('EA','TP2',0,30,10);

insert into timetable
values('EA','TP2',5,17,19);

insert into shift
values ('EA','TP4',0,30,10);

insert into timetable
values('EA','TP4',5,17,19);

insert into cu
values ('EE',2,1);

insert into shift
values ('EE','TP2',0,30,10);

insert into timetable
values('EE','TP2',2,15,17);

insert into shift
values ('EE','TP1',0,30,10);

insert into timetable
values('EE','TP1',2,17,19);

insert into shift
values ('EE','T1',1,100,10);

insert into timetable
values('EE','T1',5,13,15);

insert into shift
values ('EE','TP3',0,30,10);

insert into timetable
values('EE','TP3',5,15,17);

insert into shift
values ('EE','TP4',0,30,10);

insert into timetable
values('EE','TP4',5,17,19);

insert into cu
values ('CD',2,1);

insert into shift
values ('CD','TP3',0,30,10);

insert into timetable
values('CD','TP3',2,15,17);

insert into shift
values ('CD','TP2',0,30,10);

insert into timetable
values('CD','TP2',2,17,19);

insert into shift
values ('CD','TP1',0,30,10);

insert into timetable
values('CD','TP1',4,9,11);

insert into shift
values ('CD','TP4',0,30,10);

insert into timetable
values('CD','TP4',4,11,13);

insert into shift
values ('CD','T1',1,100,10);

insert into timetable
values('CD','T1',6,14,16);

insert into cu
values ('ISD',2,1);

insert into shift
values ('ISD','TP3',0,40,10);

insert into timetable
values('ISD','TP3',3,9,11);

insert into timetable
values('ISD','TP3',4,11,13);

insert into shift
values ('ISD','TP1',0,40,10);

insert into timetable
values('ISD','TP1',4,9,11);

insert into timetable
values('ISD','TP1',5,15,17);

insert into shift
values ('ISD','TP2',0,40,10);

insert into timetable
values('ISD','TP2',3,16,18);

insert into timetable
values('ISD','TP2',6,16,18);

insert into cu
values ('ARQC',2,1);

insert into shift
values ('ARQC','PL4',0,20,10);

insert into timetable
values('ARQC','PL4',3,9,11);

insert into shift
values ('ARQC','T1',1,100,10);

insert into timetable
values('ARQC','T1',3,13,14);

insert into timetable
values('ARQC','T1',6,13,14);

insert into shift
values ('ARQC','PL1',0,20,10);

insert into timetable
values('ARQC','PL1',3,14,16);

insert into shift
values ('ARQC','PL6',0,20,10);

insert into timetable
values('ARQC','PL6',3,16,18);

insert into shift
values ('ARQC','PL3',0,20,10);

insert into timetable
values('ARQC','PL3',4,9,11);

insert into shift
values ('ARQC','PL5',0,20,10);

insert into timetable
values('ARQC','PL5',4,11,13);

insert into shift
values ('ARQC','PL2',0,20,10);

insert into timetable
values('ARQC','PL2',5,15,17);

insert into cu
values ('AC',2,1);

insert into shift
values ('AC','TP7',0,20,10);

insert into timetable
values('AC','TP7',3,14,16);

insert into shift
values ('AC','TP1',0,20,10);

insert into timetable
values('AC','TP1',3,14,16);

insert into shift
values ('AC','TP6',0,20,10);

insert into timetable
values('AC','TP6',3,14,16);

insert into shift
values ('AC','TP3',0,20,10);

insert into timetable
values('AC','TP3',3,16,18);

insert into shift
values ('AC','T1',1,100,10);

insert into timetable
values('AC','T1',5,9,11);

insert into shift
values ('AC','TP4',0,20,10);

insert into timetable
values('AC','TP4',5,15,17);

insert into shift
values ('AC','TP8',0,20,10);

insert into timetable
values('AC','TP8',5,15,17);

insert into shift
values ('AC','TP2',0,20,10);

insert into timetable
values('AC','TP2',5,17,19);

insert into shift
values ('AC','TP5',0,20,10);

insert into timetable
values('AC','TP5',5,17,19);

insert into cu
values ('RC',3,1);

insert into shift
values ('RC','PL4',0,20,10);

insert into timetable
values('RC','PL4',2,9,11);

insert into shift
values ('RC','PL1',0,20,10);

insert into timetable
values('RC','PL1',2,14,16);

insert into shift
values ('RC','PL5',0,20,10);

insert into timetable
values('RC','PL5',2,16,18);

insert into shift
values ('RC','PL3',0,20,10);

insert into timetable
values('RC','PL3',3,9,11);

insert into shift
values ('RC','T1',1,100,10);

insert into timetable
values('RC','T1',5,11,13);

insert into shift
values ('RC','PL2',0,20,10);

insert into timetable
values('RC','PL2',6,14,16);

insert into cu
values ('MNOL',3,1);

insert into shift
values ('MNOL','PL5',0,20,10);

insert into timetable
values('MNOL','PL5',2,9,11);

insert into shift
values ('MNOL','PL2',0,20,10);

insert into timetable
values('MNOL','PL2',2,16,18);

insert into shift
values ('MNOL','T1',1,100,10);

insert into timetable
values('MNOL','T1',3,11,13);

insert into shift
values ('MNOL','PL4',0,20,10);

insert into timetable
values('MNOL','PL4',3,14,16);

insert into shift
values ('MNOL','PL1',0,20,10);

insert into timetable
values('MNOL','PL1',4,9,11);

insert into shift
values ('MNOL','PL3',0,20,10);

insert into timetable
values('MNOL','PL3',6,14,16);

insert into cu
values ('BD',3,1);

insert into shift
values ('BD','PL4',0,20,10);

insert into timetable
values('BD','PL4',2,9,11);

insert into shift
values ('BD','PL1',0,20,10);

insert into timetable
values('BD','PL1',2,14,16);

insert into shift
values ('BD','PL6',0,20,10);

insert into timetable
values('BD','PL6',3,9,11);

insert into shift
values ('BD','PL5',0,20,10);

insert into timetable
values('BD','PL5',3,16,18);

insert into shift
values ('BD','T1',1,100,10);

insert into timetable
values('BD','T1',4,11,13);

insert into shift
values ('BD','PL2',0,20,10);

insert into timetable
values('BD','PL2',5,14,16);

insert into shift
values ('BD','PL3',0,20,10);

insert into timetable
values('BD','PL3',5,16,18);

insert into cu
values ('MDIO',3,1);

insert into shift
values ('MDIO','T1',1,100,10);

insert into timetable
values('MDIO','T1',2,11,13);

insert into shift
values ('MDIO','TP2',0,30,10);

insert into timetable
values('MDIO','TP2',4,9,11);

insert into shift
values ('MDIO','TP4',0,30,10);

insert into timetable
values('MDIO','TP4',4,9,11);

insert into shift
values ('MDIO','TP3',0,30,10);

insert into timetable
values('MDIO','TP3',5,14,16);

insert into shift
values ('MDIO','TP1',0,30,10);

insert into timetable
values('MDIO','TP1',5,16,18);

insert into cu
values ('SD',3,1);

insert into shift
values ('SD','PL3',0,20,10);

insert into timetable
values('SD','PL3',2,14,16);

insert into shift
values ('SD','PL1',0,20,10);

insert into timetable
values('SD','PL1',3,9,11);

insert into shift
values ('SD','PL6',0,20,10);

insert into timetable
values('SD','PL6',3,9,11);

insert into shift
values ('SD','PL5',0,20,10);

insert into timetable
values('SD','PL5',3,14,16);

insert into shift
values ('SD','PL4',0,20,10);

insert into timetable
values('SD','PL4',3,16,18);

insert into shift
values ('SD','PL2',0,20,10);

insert into timetable
values('SD','PL2',5,9,11);

insert into shift
values ('SD','T1',1,100,10);

insert into timetable
values('SD','T1',6,9,11);

insert into cu
values ('DSS',3,1);

insert into shift
values ('DSS','PL5',0,20,10);

insert into timetable
values('DSS','PL5',3,14,16);

insert into shift
values ('DSS','PL2',0,20,10);

insert into timetable
values('DSS','PL2',3,16,18);

insert into shift
values ('DSS','PL6',0,20,10);

insert into timetable
values('DSS','PL6',4,9,11);

insert into shift
values ('DSS','PL1',0,20,10);

insert into timetable
values('DSS','PL1',5,9,11);

insert into shift
values ('DSS','PL4',0,20,10);

insert into timetable
values('DSS','PL4',5,14,16);

insert into shift
values ('DSS','PL3',0,20,10);

insert into timetable
values('DSS','PL3',5,16,18);

insert into shift
values ('DSS','T1',1,100,10);

insert into timetable
values('DSS','T1',6,11,13);

insert into student
values('a80000','pass',1);

insert into student_cu
values('a80000','EES');

insert into student_cu
values('a80000','PF');

insert into student_cu
values('a80000','TMD');

insert into student_cu
values('a80000','CALC');

insert into student_cu
values('a80000','ALG');

insert into student_cu
values('a80000','LI1');

insert into student
values('a80001','pass',0);

insert into student_cu
values('a80001','EES');

insert into student_cu
values('a80001','PF');

insert into student_cu
values('a80001','TMD');

insert into student_cu
values('a80001','CALC');

insert into student_cu
values('a80001','ALG');

insert into student_cu
values('a80001','LI1');

insert into student
values('a80002','pass',0);

insert into student_cu
values('a80002','EES');

insert into student_cu
values('a80002','PF');

insert into student_cu
values('a80002','TMD');

insert into student_cu
values('a80002','CALC');

insert into student_cu
values('a80002','ALG');

insert into student_cu
values('a80002','LI1');

insert into student
values('a80003','pass',0);

insert into student_cu
values('a80003','EES');

insert into student_cu
values('a80003','PF');

insert into student_cu
values('a80003','TMD');

insert into student_cu
values('a80003','CALC');

insert into student_cu
values('a80003','ALG');

insert into student_cu
values('a80003','LI1');

insert into student
values('a80004','pass',0);

insert into student_cu
values('a80004','EES');

insert into student_cu
values('a80004','PF');

insert into student_cu
values('a80004','TMD');

insert into student_cu
values('a80004','CALC');

insert into student_cu
values('a80004','ALG');

insert into student_cu
values('a80004','LI1');

insert into student
values('a80005','pass',0);

insert into student_cu
values('a80005','EES');

insert into student_cu
values('a80005','PF');

insert into student_cu
values('a80005','TMD');

insert into student_cu
values('a80005','CALC');

insert into student_cu
values('a80005','ALG');

insert into student_cu
values('a80005','LI1');

insert into student
values('a80006','pass',0);

insert into student_cu
values('a80006','EES');

insert into student_cu
values('a80006','PF');

insert into student_cu
values('a80006','TMD');

insert into student_cu
values('a80006','CALC');

insert into student_cu
values('a80006','ALG');

insert into student_cu
values('a80006','LI1');

insert into student
values('a80007','pass',0);

insert into student_cu
values('a80007','EES');

insert into student_cu
values('a80007','PF');

insert into student_cu
values('a80007','TMD');

insert into student_cu
values('a80007','CALC');

insert into student_cu
values('a80007','ALG');

insert into student_cu
values('a80007','LI1');

insert into student
values('a80008','pass',0);

insert into student_cu
values('a80008','EES');

insert into student_cu
values('a80008','PF');

insert into student_cu
values('a80008','TMD');

insert into student_cu
values('a80008','CALC');

insert into student_cu
values('a80008','ALG');

insert into student_cu
values('a80008','LI1');

insert into student
values('a80009','pass',0);

insert into student_cu
values('a80009','EES');

insert into student_cu
values('a80009','PF');

insert into student_cu
values('a80009','TMD');

insert into student_cu
values('a80009','CALC');

insert into student_cu
values('a80009','ALG');

insert into student_cu
values('a80009','LI1');

insert into student
values('a80010','pass',1);

insert into student_cu
values('a80010','EES');

insert into student_cu
values('a80010','PF');

insert into student_cu
values('a80010','TMD');

insert into student_cu
values('a80010','CALC');

insert into student_cu
values('a80010','ALG');

insert into student_cu
values('a80010','LI1');

insert into student
values('a80011','pass',0);

insert into student_cu
values('a80011','EES');

insert into student_cu
values('a80011','PF');

insert into student_cu
values('a80011','TMD');

insert into student_cu
values('a80011','CALC');

insert into student_cu
values('a80011','ALG');

insert into student_cu
values('a80011','LI1');

insert into student
values('a80012','pass',0);

insert into student_cu
values('a80012','EES');

insert into student_cu
values('a80012','PF');

insert into student_cu
values('a80012','TMD');

insert into student_cu
values('a80012','CALC');

insert into student_cu
values('a80012','ALG');

insert into student_cu
values('a80012','LI1');

insert into student
values('a80013','pass',0);

insert into student_cu
values('a80013','EES');

insert into student_cu
values('a80013','PF');

insert into student_cu
values('a80013','TMD');

insert into student_cu
values('a80013','CALC');

insert into student_cu
values('a80013','ALG');

insert into student_cu
values('a80013','LI1');

insert into student
values('a80014','pass',0);

insert into student_cu
values('a80014','EES');

insert into student_cu
values('a80014','PF');

insert into student_cu
values('a80014','TMD');

insert into student_cu
values('a80014','CALC');

insert into student_cu
values('a80014','ALG');

insert into student_cu
values('a80014','LI1');

insert into student
values('a80015','pass',0);

insert into student_cu
values('a80015','EES');

insert into student_cu
values('a80015','PF');

insert into student_cu
values('a80015','TMD');

insert into student_cu
values('a80015','CALC');

insert into student_cu
values('a80015','ALG');

insert into student_cu
values('a80015','LI1');

insert into student
values('a80016','pass',0);

insert into student_cu
values('a80016','EES');

insert into student_cu
values('a80016','PF');

insert into student_cu
values('a80016','TMD');

insert into student_cu
values('a80016','CALC');

insert into student_cu
values('a80016','ALG');

insert into student_cu
values('a80016','LI1');

insert into student
values('a80017','pass',0);

insert into student_cu
values('a80017','EES');

insert into student_cu
values('a80017','PF');

insert into student_cu
values('a80017','TMD');

insert into student_cu
values('a80017','CALC');

insert into student_cu
values('a80017','ALG');

insert into student_cu
values('a80017','LI1');

insert into student
values('a80018','pass',0);

insert into student_cu
values('a80018','EES');

insert into student_cu
values('a80018','PF');

insert into student_cu
values('a80018','TMD');

insert into student_cu
values('a80018','CALC');

insert into student_cu
values('a80018','ALG');

insert into student_cu
values('a80018','LI1');

insert into student
values('a80019','pass',0);

insert into student_cu
values('a80019','EES');

insert into student_cu
values('a80019','PF');

insert into student_cu
values('a80019','TMD');

insert into student_cu
values('a80019','CALC');

insert into student_cu
values('a80019','ALG');

insert into student_cu
values('a80019','LI1');

insert into student
values('a80020','pass',1);

insert into student_cu
values('a80020','EES');

insert into student_cu
values('a80020','PF');

insert into student_cu
values('a80020','TMD');

insert into student_cu
values('a80020','CALC');

insert into student_cu
values('a80020','ALG');

insert into student_cu
values('a80020','LI1');

insert into student
values('a80021','pass',0);

insert into student_cu
values('a80021','EES');

insert into student_cu
values('a80021','PF');

insert into student_cu
values('a80021','TMD');

insert into student_cu
values('a80021','CALC');

insert into student_cu
values('a80021','ALG');

insert into student_cu
values('a80021','LI1');

insert into student
values('a80022','pass',0);

insert into student_cu
values('a80022','EES');

insert into student_cu
values('a80022','PF');

insert into student_cu
values('a80022','TMD');

insert into student_cu
values('a80022','CALC');

insert into student_cu
values('a80022','ALG');

insert into student_cu
values('a80022','LI1');

insert into student
values('a80023','pass',0);

insert into student_cu
values('a80023','EES');

insert into student_cu
values('a80023','PF');

insert into student_cu
values('a80023','TMD');

insert into student_cu
values('a80023','CALC');

insert into student_cu
values('a80023','ALG');

insert into student_cu
values('a80023','LI1');

insert into student
values('a80024','pass',0);

insert into student_cu
values('a80024','EES');

insert into student_cu
values('a80024','PF');

insert into student_cu
values('a80024','TMD');

insert into student_cu
values('a80024','CALC');

insert into student_cu
values('a80024','ALG');

insert into student_cu
values('a80024','LI1');

insert into student
values('a80025','pass',0);

insert into student_cu
values('a80025','EES');

insert into student_cu
values('a80025','PF');

insert into student_cu
values('a80025','TMD');

insert into student_cu
values('a80025','CALC');

insert into student_cu
values('a80025','ALG');

insert into student_cu
values('a80025','LI1');

insert into student
values('a80026','pass',0);

insert into student_cu
values('a80026','EES');

insert into student_cu
values('a80026','PF');

insert into student_cu
values('a80026','TMD');

insert into student_cu
values('a80026','CALC');

insert into student_cu
values('a80026','ALG');

insert into student_cu
values('a80026','LI1');

insert into student
values('a80027','pass',0);

insert into student_cu
values('a80027','EES');

insert into student_cu
values('a80027','PF');

insert into student_cu
values('a80027','TMD');

insert into student_cu
values('a80027','CALC');

insert into student_cu
values('a80027','ALG');

insert into student_cu
values('a80027','LI1');

insert into student
values('a80028','pass',0);

insert into student_cu
values('a80028','EES');

insert into student_cu
values('a80028','PF');

insert into student_cu
values('a80028','TMD');

insert into student_cu
values('a80028','CALC');

insert into student_cu
values('a80028','ALG');

insert into student_cu
values('a80028','LI1');

insert into student
values('a80029','pass',0);

insert into student_cu
values('a80029','EES');

insert into student_cu
values('a80029','PF');

insert into student_cu
values('a80029','TMD');

insert into student_cu
values('a80029','CALC');

insert into student_cu
values('a80029','ALG');

insert into student_cu
values('a80029','LI1');

insert into student
values('a80030','pass',1);

insert into student_cu
values('a80030','EES');

insert into student_cu
values('a80030','PF');

insert into student_cu
values('a80030','TMD');

insert into student_cu
values('a80030','CALC');

insert into student_cu
values('a80030','ALG');

insert into student_cu
values('a80030','LI1');

insert into student
values('a80031','pass',0);

insert into student_cu
values('a80031','EES');

insert into student_cu
values('a80031','PF');

insert into student_cu
values('a80031','TMD');

insert into student_cu
values('a80031','CALC');

insert into student_cu
values('a80031','ALG');

insert into student_cu
values('a80031','LI1');

insert into student
values('a80032','pass',0);

insert into student_cu
values('a80032','EES');

insert into student_cu
values('a80032','PF');

insert into student_cu
values('a80032','TMD');

insert into student_cu
values('a80032','CALC');

insert into student_cu
values('a80032','ALG');

insert into student_cu
values('a80032','LI1');

insert into student
values('a80033','pass',0);

insert into student_cu
values('a80033','EES');

insert into student_cu
values('a80033','PF');

insert into student_cu
values('a80033','TMD');

insert into student_cu
values('a80033','CALC');

insert into student_cu
values('a80033','ALG');

insert into student_cu
values('a80033','LI1');

insert into student
values('a80034','pass',0);

insert into student_cu
values('a80034','EES');

insert into student_cu
values('a80034','PF');

insert into student_cu
values('a80034','TMD');

insert into student_cu
values('a80034','CALC');

insert into student_cu
values('a80034','ALG');

insert into student_cu
values('a80034','LI1');

insert into student
values('a80035','pass',0);

insert into student_cu
values('a80035','EES');

insert into student_cu
values('a80035','PF');

insert into student_cu
values('a80035','TMD');

insert into student_cu
values('a80035','CALC');

insert into student_cu
values('a80035','ALG');

insert into student_cu
values('a80035','LI1');

insert into student
values('a80036','pass',0);

insert into student_cu
values('a80036','EES');

insert into student_cu
values('a80036','PF');

insert into student_cu
values('a80036','TMD');

insert into student_cu
values('a80036','CALC');

insert into student_cu
values('a80036','ALG');

insert into student_cu
values('a80036','LI1');

insert into student
values('a80037','pass',0);

insert into student_cu
values('a80037','EES');

insert into student_cu
values('a80037','PF');

insert into student_cu
values('a80037','TMD');

insert into student_cu
values('a80037','CALC');

insert into student_cu
values('a80037','ALG');

insert into student_cu
values('a80037','LI1');

insert into student
values('a80038','pass',0);

insert into student_cu
values('a80038','EES');

insert into student_cu
values('a80038','PF');

insert into student_cu
values('a80038','TMD');

insert into student_cu
values('a80038','CALC');

insert into student_cu
values('a80038','ALG');

insert into student_cu
values('a80038','LI1');

insert into student
values('a80039','pass',0);

insert into student_cu
values('a80039','EES');

insert into student_cu
values('a80039','PF');

insert into student_cu
values('a80039','TMD');

insert into student_cu
values('a80039','CALC');

insert into student_cu
values('a80039','ALG');

insert into student_cu
values('a80039','LI1');

insert into student
values('a80040','pass',1);

insert into student_cu
values('a80040','EES');

insert into student_cu
values('a80040','PF');

insert into student_cu
values('a80040','TMD');

insert into student_cu
values('a80040','CALC');

insert into student_cu
values('a80040','ALG');

insert into student_cu
values('a80040','LI1');

insert into student
values('a80041','pass',0);

insert into student_cu
values('a80041','EES');

insert into student_cu
values('a80041','PF');

insert into student_cu
values('a80041','TMD');

insert into student_cu
values('a80041','CALC');

insert into student_cu
values('a80041','ALG');

insert into student_cu
values('a80041','LI1');

insert into student
values('a80042','pass',0);

insert into student_cu
values('a80042','EES');

insert into student_cu
values('a80042','PF');

insert into student_cu
values('a80042','TMD');

insert into student_cu
values('a80042','CALC');

insert into student_cu
values('a80042','ALG');

insert into student_cu
values('a80042','LI1');

insert into student
values('a80043','pass',0);

insert into student_cu
values('a80043','EES');

insert into student_cu
values('a80043','PF');

insert into student_cu
values('a80043','TMD');

insert into student_cu
values('a80043','CALC');

insert into student_cu
values('a80043','ALG');

insert into student_cu
values('a80043','LI1');

insert into student
values('a80044','pass',0);

insert into student_cu
values('a80044','EES');

insert into student_cu
values('a80044','PF');

insert into student_cu
values('a80044','TMD');

insert into student_cu
values('a80044','CALC');

insert into student_cu
values('a80044','ALG');

insert into student_cu
values('a80044','LI1');

insert into student
values('a80045','pass',0);

insert into student_cu
values('a80045','EES');

insert into student_cu
values('a80045','PF');

insert into student_cu
values('a80045','TMD');

insert into student_cu
values('a80045','CALC');

insert into student_cu
values('a80045','ALG');

insert into student_cu
values('a80045','LI1');

insert into student
values('a80046','pass',0);

insert into student_cu
values('a80046','EES');

insert into student_cu
values('a80046','PF');

insert into student_cu
values('a80046','TMD');

insert into student_cu
values('a80046','CALC');

insert into student_cu
values('a80046','ALG');

insert into student_cu
values('a80046','LI1');

insert into student
values('a80047','pass',0);

insert into student_cu
values('a80047','EES');

insert into student_cu
values('a80047','PF');

insert into student_cu
values('a80047','TMD');

insert into student_cu
values('a80047','CALC');

insert into student_cu
values('a80047','ALG');

insert into student_cu
values('a80047','LI1');

insert into student
values('a80048','pass',0);

insert into student_cu
values('a80048','EES');

insert into student_cu
values('a80048','PF');

insert into student_cu
values('a80048','TMD');

insert into student_cu
values('a80048','CALC');

insert into student_cu
values('a80048','ALG');

insert into student_cu
values('a80048','LI1');

insert into student
values('a80049','pass',0);

insert into student_cu
values('a80049','EES');

insert into student_cu
values('a80049','PF');

insert into student_cu
values('a80049','TMD');

insert into student_cu
values('a80049','CALC');

insert into student_cu
values('a80049','ALG');

insert into student_cu
values('a80049','LI1');

insert into student
values('a80050','pass',1);

insert into student_cu
values('a80050','EES');

insert into student_cu
values('a80050','PF');

insert into student_cu
values('a80050','TMD');

insert into student_cu
values('a80050','CALC');

insert into student_cu
values('a80050','ALG');

insert into student_cu
values('a80050','LI1');

insert into student
values('a80051','pass',0);

insert into student_cu
values('a80051','EES');

insert into student_cu
values('a80051','PF');

insert into student_cu
values('a80051','TMD');

insert into student_cu
values('a80051','CALC');

insert into student_cu
values('a80051','ALG');

insert into student_cu
values('a80051','LI1');

insert into student
values('a80052','pass',0);

insert into student_cu
values('a80052','EES');

insert into student_cu
values('a80052','PF');

insert into student_cu
values('a80052','TMD');

insert into student_cu
values('a80052','CALC');

insert into student_cu
values('a80052','ALG');

insert into student_cu
values('a80052','LI1');

insert into student
values('a80053','pass',0);

insert into student_cu
values('a80053','EES');

insert into student_cu
values('a80053','PF');

insert into student_cu
values('a80053','TMD');

insert into student_cu
values('a80053','CALC');

insert into student_cu
values('a80053','ALG');

insert into student_cu
values('a80053','LI1');

insert into student
values('a80054','pass',0);

insert into student_cu
values('a80054','EES');

insert into student_cu
values('a80054','PF');

insert into student_cu
values('a80054','TMD');

insert into student_cu
values('a80054','CALC');

insert into student_cu
values('a80054','ALG');

insert into student_cu
values('a80054','LI1');

insert into student
values('a80055','pass',0);

insert into student_cu
values('a80055','EES');

insert into student_cu
values('a80055','PF');

insert into student_cu
values('a80055','TMD');

insert into student_cu
values('a80055','CALC');

insert into student_cu
values('a80055','ALG');

insert into student_cu
values('a80055','LI1');

insert into student
values('a80056','pass',0);

insert into student_cu
values('a80056','EES');

insert into student_cu
values('a80056','PF');

insert into student_cu
values('a80056','TMD');

insert into student_cu
values('a80056','CALC');

insert into student_cu
values('a80056','ALG');

insert into student_cu
values('a80056','LI1');

insert into student
values('a80057','pass',0);

insert into student_cu
values('a80057','EES');

insert into student_cu
values('a80057','PF');

insert into student_cu
values('a80057','TMD');

insert into student_cu
values('a80057','CALC');

insert into student_cu
values('a80057','ALG');

insert into student_cu
values('a80057','LI1');

insert into student
values('a80058','pass',0);

insert into student_cu
values('a80058','EES');

insert into student_cu
values('a80058','PF');

insert into student_cu
values('a80058','TMD');

insert into student_cu
values('a80058','CALC');

insert into student_cu
values('a80058','ALG');

insert into student_cu
values('a80058','LI1');

insert into student
values('a80059','pass',0);

insert into student_cu
values('a80059','EES');

insert into student_cu
values('a80059','PF');

insert into student_cu
values('a80059','TMD');

insert into student_cu
values('a80059','CALC');

insert into student_cu
values('a80059','ALG');

insert into student_cu
values('a80059','LI1');

insert into student
values('a80060','pass',1);

insert into student_cu
values('a80060','EES');

insert into student_cu
values('a80060','PF');

insert into student_cu
values('a80060','TMD');

insert into student_cu
values('a80060','CALC');

insert into student_cu
values('a80060','ALG');

insert into student_cu
values('a80060','LI1');

insert into student
values('a80061','pass',0);

insert into student_cu
values('a80061','EES');

insert into student_cu
values('a80061','PF');

insert into student_cu
values('a80061','TMD');

insert into student_cu
values('a80061','CALC');

insert into student_cu
values('a80061','ALG');

insert into student_cu
values('a80061','LI1');

insert into student
values('a80062','pass',0);

insert into student_cu
values('a80062','EES');

insert into student_cu
values('a80062','PF');

insert into student_cu
values('a80062','TMD');

insert into student_cu
values('a80062','CALC');

insert into student_cu
values('a80062','ALG');

insert into student_cu
values('a80062','LI1');

insert into student
values('a80063','pass',0);

insert into student_cu
values('a80063','EES');

insert into student_cu
values('a80063','PF');

insert into student_cu
values('a80063','TMD');

insert into student_cu
values('a80063','CALC');

insert into student_cu
values('a80063','ALG');

insert into student_cu
values('a80063','LI1');

insert into student
values('a80064','pass',0);

insert into student_cu
values('a80064','EES');

insert into student_cu
values('a80064','PF');

insert into student_cu
values('a80064','TMD');

insert into student_cu
values('a80064','CALC');

insert into student_cu
values('a80064','ALG');

insert into student_cu
values('a80064','LI1');

insert into student
values('a80065','pass',0);

insert into student_cu
values('a80065','EES');

insert into student_cu
values('a80065','PF');

insert into student_cu
values('a80065','TMD');

insert into student_cu
values('a80065','CALC');

insert into student_cu
values('a80065','ALG');

insert into student_cu
values('a80065','LI1');

insert into student
values('a80066','pass',0);

insert into student_cu
values('a80066','EES');

insert into student_cu
values('a80066','PF');

insert into student_cu
values('a80066','TMD');

insert into student_cu
values('a80066','CALC');

insert into student_cu
values('a80066','ALG');

insert into student_cu
values('a80066','LI1');

insert into student
values('a80067','pass',0);

insert into student_cu
values('a80067','EES');

insert into student_cu
values('a80067','PF');

insert into student_cu
values('a80067','TMD');

insert into student_cu
values('a80067','CALC');

insert into student_cu
values('a80067','ALG');

insert into student_cu
values('a80067','LI1');

insert into student
values('a80068','pass',0);

insert into student_cu
values('a80068','EES');

insert into student_cu
values('a80068','PF');

insert into student_cu
values('a80068','TMD');

insert into student_cu
values('a80068','CALC');

insert into student_cu
values('a80068','ALG');

insert into student_cu
values('a80068','LI1');

insert into student
values('a80069','pass',0);

insert into student_cu
values('a80069','EES');

insert into student_cu
values('a80069','PF');

insert into student_cu
values('a80069','TMD');

insert into student_cu
values('a80069','CALC');

insert into student_cu
values('a80069','ALG');

insert into student_cu
values('a80069','LI1');

insert into student
values('a80070','pass',1);

insert into student_cu
values('a80070','EES');

insert into student_cu
values('a80070','PF');

insert into student_cu
values('a80070','TMD');

insert into student_cu
values('a80070','CALC');

insert into student_cu
values('a80070','ALG');

insert into student_cu
values('a80070','LI1');

insert into student
values('a80071','pass',0);

insert into student_cu
values('a80071','EES');

insert into student_cu
values('a80071','PF');

insert into student_cu
values('a80071','TMD');

insert into student_cu
values('a80071','CALC');

insert into student_cu
values('a80071','ALG');

insert into student_cu
values('a80071','LI1');

insert into student
values('a80072','pass',0);

insert into student_cu
values('a80072','EES');

insert into student_cu
values('a80072','PF');

insert into student_cu
values('a80072','TMD');

insert into student_cu
values('a80072','CALC');

insert into student_cu
values('a80072','ALG');

insert into student_cu
values('a80072','LI1');

insert into student
values('a80073','pass',0);

insert into student_cu
values('a80073','EES');

insert into student_cu
values('a80073','PF');

insert into student_cu
values('a80073','TMD');

insert into student_cu
values('a80073','CALC');

insert into student_cu
values('a80073','ALG');

insert into student_cu
values('a80073','LI1');

insert into student
values('a80074','pass',0);

insert into student_cu
values('a80074','EES');

insert into student_cu
values('a80074','PF');

insert into student_cu
values('a80074','TMD');

insert into student_cu
values('a80074','CALC');

insert into student_cu
values('a80074','ALG');

insert into student_cu
values('a80074','LI1');

insert into student
values('a80075','pass',0);

insert into student_cu
values('a80075','EES');

insert into student_cu
values('a80075','PF');

insert into student_cu
values('a80075','TMD');

insert into student_cu
values('a80075','CALC');

insert into student_cu
values('a80075','ALG');

insert into student_cu
values('a80075','LI1');

insert into student
values('a80076','pass',0);

insert into student_cu
values('a80076','EES');

insert into student_cu
values('a80076','PF');

insert into student_cu
values('a80076','TMD');

insert into student_cu
values('a80076','CALC');

insert into student_cu
values('a80076','ALG');

insert into student_cu
values('a80076','LI1');

insert into student
values('a80077','pass',0);

insert into student_cu
values('a80077','EES');

insert into student_cu
values('a80077','PF');

insert into student_cu
values('a80077','TMD');

insert into student_cu
values('a80077','CALC');

insert into student_cu
values('a80077','ALG');

insert into student_cu
values('a80077','LI1');

insert into student
values('a80078','pass',0);

insert into student_cu
values('a80078','EES');

insert into student_cu
values('a80078','PF');

insert into student_cu
values('a80078','TMD');

insert into student_cu
values('a80078','CALC');

insert into student_cu
values('a80078','ALG');

insert into student_cu
values('a80078','LI1');

insert into student
values('a80079','pass',0);

insert into student_cu
values('a80079','EES');

insert into student_cu
values('a80079','PF');

insert into student_cu
values('a80079','TMD');

insert into student_cu
values('a80079','CALC');

insert into student_cu
values('a80079','ALG');

insert into student_cu
values('a80079','LI1');

insert into student
values('a80080','pass',1);

insert into student_cu
values('a80080','EES');

insert into student_cu
values('a80080','PF');

insert into student_cu
values('a80080','TMD');

insert into student_cu
values('a80080','CALC');

insert into student_cu
values('a80080','ALG');

insert into student_cu
values('a80080','LI1');

insert into student
values('a80081','pass',0);

insert into student_cu
values('a80081','EES');

insert into student_cu
values('a80081','PF');

insert into student_cu
values('a80081','TMD');

insert into student_cu
values('a80081','CALC');

insert into student_cu
values('a80081','ALG');

insert into student_cu
values('a80081','LI1');

insert into student
values('a80082','pass',0);

insert into student_cu
values('a80082','EES');

insert into student_cu
values('a80082','PF');

insert into student_cu
values('a80082','TMD');

insert into student_cu
values('a80082','CALC');

insert into student_cu
values('a80082','ALG');

insert into student_cu
values('a80082','LI1');

insert into student
values('a80083','pass',0);

insert into student_cu
values('a80083','EES');

insert into student_cu
values('a80083','PF');

insert into student_cu
values('a80083','TMD');

insert into student_cu
values('a80083','CALC');

insert into student_cu
values('a80083','ALG');

insert into student_cu
values('a80083','LI1');

insert into student
values('a80084','pass',0);

insert into student_cu
values('a80084','EES');

insert into student_cu
values('a80084','PF');

insert into student_cu
values('a80084','TMD');

insert into student_cu
values('a80084','CALC');

insert into student_cu
values('a80084','ALG');

insert into student_cu
values('a80084','LI1');

insert into student
values('a80085','pass',0);

insert into student_cu
values('a80085','EES');

insert into student_cu
values('a80085','PF');

insert into student_cu
values('a80085','TMD');

insert into student_cu
values('a80085','CALC');

insert into student_cu
values('a80085','ALG');

insert into student_cu
values('a80085','LI1');

insert into student
values('a80086','pass',0);

insert into student_cu
values('a80086','EES');

insert into student_cu
values('a80086','PF');

insert into student_cu
values('a80086','TMD');

insert into student_cu
values('a80086','CALC');

insert into student_cu
values('a80086','ALG');

insert into student_cu
values('a80086','LI1');

insert into student
values('a80087','pass',0);

insert into student_cu
values('a80087','EES');

insert into student_cu
values('a80087','PF');

insert into student_cu
values('a80087','TMD');

insert into student_cu
values('a80087','CALC');

insert into student_cu
values('a80087','ALG');

insert into student_cu
values('a80087','LI1');

insert into student
values('a80088','pass',0);

insert into student_cu
values('a80088','EES');

insert into student_cu
values('a80088','PF');

insert into student_cu
values('a80088','TMD');

insert into student_cu
values('a80088','CALC');

insert into student_cu
values('a80088','ALG');

insert into student_cu
values('a80088','LI1');

insert into student
values('a80089','pass',0);

insert into student_cu
values('a80089','EES');

insert into student_cu
values('a80089','PF');

insert into student_cu
values('a80089','TMD');

insert into student_cu
values('a80089','CALC');

insert into student_cu
values('a80089','ALG');

insert into student_cu
values('a80089','LI1');

insert into student
values('a80090','pass',1);

insert into student_cu
values('a80090','EES');

insert into student_cu
values('a80090','PF');

insert into student_cu
values('a80090','TMD');

insert into student_cu
values('a80090','CALC');

insert into student_cu
values('a80090','ALG');

insert into student_cu
values('a80090','LI1');

insert into student
values('a80091','pass',0);

insert into student_cu
values('a80091','EES');

insert into student_cu
values('a80091','PF');

insert into student_cu
values('a80091','TMD');

insert into student_cu
values('a80091','CALC');

insert into student_cu
values('a80091','ALG');

insert into student_cu
values('a80091','LI1');

insert into student
values('a80092','pass',0);

insert into student_cu
values('a80092','EES');

insert into student_cu
values('a80092','PF');

insert into student_cu
values('a80092','TMD');

insert into student_cu
values('a80092','CALC');

insert into student_cu
values('a80092','ALG');

insert into student_cu
values('a80092','LI1');

insert into student
values('a80093','pass',0);

insert into student_cu
values('a80093','EES');

insert into student_cu
values('a80093','PF');

insert into student_cu
values('a80093','TMD');

insert into student_cu
values('a80093','CALC');

insert into student_cu
values('a80093','ALG');

insert into student_cu
values('a80093','LI1');

insert into student
values('a80094','pass',0);

insert into student_cu
values('a80094','EES');

insert into student_cu
values('a80094','PF');

insert into student_cu
values('a80094','TMD');

insert into student_cu
values('a80094','CALC');

insert into student_cu
values('a80094','ALG');

insert into student_cu
values('a80094','LI1');

insert into student
values('a80095','pass',0);

insert into student_cu
values('a80095','EES');

insert into student_cu
values('a80095','PF');

insert into student_cu
values('a80095','TMD');

insert into student_cu
values('a80095','CALC');

insert into student_cu
values('a80095','ALG');

insert into student_cu
values('a80095','LI1');

insert into student
values('a80096','pass',0);

insert into student_cu
values('a80096','EES');

insert into student_cu
values('a80096','PF');

insert into student_cu
values('a80096','TMD');

insert into student_cu
values('a80096','CALC');

insert into student_cu
values('a80096','ALG');

insert into student_cu
values('a80096','LI1');

insert into student
values('a80097','pass',0);

insert into student_cu
values('a80097','EES');

insert into student_cu
values('a80097','PF');

insert into student_cu
values('a80097','TMD');

insert into student_cu
values('a80097','CALC');

insert into student_cu
values('a80097','ALG');

insert into student_cu
values('a80097','LI1');

insert into student
values('a80098','pass',0);

insert into student_cu
values('a80098','EES');

insert into student_cu
values('a80098','PF');

insert into student_cu
values('a80098','TMD');

insert into student_cu
values('a80098','CALC');

insert into student_cu
values('a80098','ALG');

insert into student_cu
values('a80098','LI1');

insert into student
values('a80099','pass',0);

insert into student_cu
values('a80099','EES');

insert into student_cu
values('a80099','PF');

insert into student_cu
values('a80099','TMD');

insert into student_cu
values('a80099','CALC');

insert into student_cu
values('a80099','ALG');

insert into student_cu
values('a80099','LI1');

insert into student
values('a70000','pass',1);

insert into student_cu
values('a70000','AC');

insert into student_cu
values('a70000','ARQC');

insert into student_cu
values('a70000','ISD');

insert into student_cu
values('a70000','EA');

insert into student_cu
values('a70000','EE');

insert into student_cu
values('a70000','CD');

insert into student_cu
values('a70000','PF');

insert into student
values('a70001','pass',0);

insert into student_cu
values('a70001','AC');

insert into student_cu
values('a70001','ARQC');

insert into student_cu
values('a70001','ISD');

insert into student_cu
values('a70001','EA');

insert into student_cu
values('a70001','EE');

insert into student_cu
values('a70001','CD');

insert into student_cu
values('a70001','PF');

insert into student
values('a70002','pass',0);

insert into student_cu
values('a70002','AC');

insert into student_cu
values('a70002','ARQC');

insert into student_cu
values('a70002','ISD');

insert into student_cu
values('a70002','EA');

insert into student_cu
values('a70002','EE');

insert into student_cu
values('a70002','CD');

insert into student_cu
values('a70002','PF');

insert into student
values('a70003','pass',0);

insert into student_cu
values('a70003','AC');

insert into student_cu
values('a70003','ARQC');

insert into student_cu
values('a70003','ISD');

insert into student_cu
values('a70003','EA');

insert into student_cu
values('a70003','EE');

insert into student_cu
values('a70003','CD');

insert into student_cu
values('a70003','PF');

insert into student
values('a70004','pass',0);

insert into student_cu
values('a70004','AC');

insert into student_cu
values('a70004','ARQC');

insert into student_cu
values('a70004','ISD');

insert into student_cu
values('a70004','EA');

insert into student_cu
values('a70004','EE');

insert into student_cu
values('a70004','CD');

insert into student_cu
values('a70004','PF');

insert into student
values('a70005','pass',0);

insert into student_cu
values('a70005','AC');

insert into student_cu
values('a70005','ARQC');

insert into student_cu
values('a70005','ISD');

insert into student_cu
values('a70005','EA');

insert into student_cu
values('a70005','EE');

insert into student_cu
values('a70005','CD');

insert into student_cu
values('a70005','PF');

insert into student
values('a70006','pass',0);

insert into student_cu
values('a70006','AC');

insert into student_cu
values('a70006','ARQC');

insert into student_cu
values('a70006','ISD');

insert into student_cu
values('a70006','EA');

insert into student_cu
values('a70006','EE');

insert into student_cu
values('a70006','CD');

insert into student_cu
values('a70006','PF');

insert into student
values('a70007','pass',0);

insert into student_cu
values('a70007','AC');

insert into student_cu
values('a70007','ARQC');

insert into student_cu
values('a70007','ISD');

insert into student_cu
values('a70007','EA');

insert into student_cu
values('a70007','EE');

insert into student_cu
values('a70007','CD');

insert into student_cu
values('a70007','PF');

insert into student
values('a70008','pass',0);

insert into student_cu
values('a70008','AC');

insert into student_cu
values('a70008','ARQC');

insert into student_cu
values('a70008','ISD');

insert into student_cu
values('a70008','EA');

insert into student_cu
values('a70008','EE');

insert into student_cu
values('a70008','CD');

insert into student_cu
values('a70008','PF');

insert into student
values('a70009','pass',0);

insert into student_cu
values('a70009','AC');

insert into student_cu
values('a70009','ARQC');

insert into student_cu
values('a70009','ISD');

insert into student_cu
values('a70009','EA');

insert into student_cu
values('a70009','EE');

insert into student_cu
values('a70009','CD');

insert into student_cu
values('a70009','PF');

insert into student
values('a70010','pass',1);

insert into student_cu
values('a70010','AC');

insert into student_cu
values('a70010','ARQC');

insert into student_cu
values('a70010','ISD');

insert into student_cu
values('a70010','EA');

insert into student_cu
values('a70010','EE');

insert into student_cu
values('a70010','CD');

insert into student_cu
values('a70010','PF');

insert into student
values('a70011','pass',0);

insert into student_cu
values('a70011','AC');

insert into student_cu
values('a70011','ARQC');

insert into student_cu
values('a70011','ISD');

insert into student_cu
values('a70011','EA');

insert into student_cu
values('a70011','EE');

insert into student_cu
values('a70011','CD');

insert into student_cu
values('a70011','PF');

insert into student
values('a70012','pass',0);

insert into student_cu
values('a70012','AC');

insert into student_cu
values('a70012','ARQC');

insert into student_cu
values('a70012','ISD');

insert into student_cu
values('a70012','EA');

insert into student_cu
values('a70012','EE');

insert into student_cu
values('a70012','CD');

insert into student_cu
values('a70012','PF');

insert into student
values('a70013','pass',0);

insert into student_cu
values('a70013','AC');

insert into student_cu
values('a70013','ARQC');

insert into student_cu
values('a70013','ISD');

insert into student_cu
values('a70013','EA');

insert into student_cu
values('a70013','EE');

insert into student_cu
values('a70013','CD');

insert into student_cu
values('a70013','PF');

insert into student
values('a70014','pass',0);

insert into student_cu
values('a70014','AC');

insert into student_cu
values('a70014','ARQC');

insert into student_cu
values('a70014','ISD');

insert into student_cu
values('a70014','EA');

insert into student_cu
values('a70014','EE');

insert into student_cu
values('a70014','CD');

insert into student_cu
values('a70014','PF');

insert into student
values('a70015','pass',0);

insert into student_cu
values('a70015','AC');

insert into student_cu
values('a70015','ARQC');

insert into student_cu
values('a70015','ISD');

insert into student_cu
values('a70015','EA');

insert into student_cu
values('a70015','EE');

insert into student_cu
values('a70015','CD');

insert into student_cu
values('a70015','PF');

insert into student
values('a70016','pass',0);

insert into student_cu
values('a70016','AC');

insert into student_cu
values('a70016','ARQC');

insert into student_cu
values('a70016','ISD');

insert into student_cu
values('a70016','EA');

insert into student_cu
values('a70016','EE');

insert into student_cu
values('a70016','CD');

insert into student_cu
values('a70016','PF');

insert into student
values('a70017','pass',0);

insert into student_cu
values('a70017','AC');

insert into student_cu
values('a70017','ARQC');

insert into student_cu
values('a70017','ISD');

insert into student_cu
values('a70017','EA');

insert into student_cu
values('a70017','EE');

insert into student_cu
values('a70017','CD');

insert into student_cu
values('a70017','PF');

insert into student
values('a70018','pass',0);

insert into student_cu
values('a70018','AC');

insert into student_cu
values('a70018','ARQC');

insert into student_cu
values('a70018','ISD');

insert into student_cu
values('a70018','EA');

insert into student_cu
values('a70018','EE');

insert into student_cu
values('a70018','CD');

insert into student_cu
values('a70018','PF');

insert into student
values('a70019','pass',0);

insert into student_cu
values('a70019','AC');

insert into student_cu
values('a70019','ARQC');

insert into student_cu
values('a70019','ISD');

insert into student_cu
values('a70019','EA');

insert into student_cu
values('a70019','EE');

insert into student_cu
values('a70019','CD');

insert into student_cu
values('a70019','PF');

insert into student
values('a70020','pass',1);

insert into student_cu
values('a70020','AC');

insert into student_cu
values('a70020','ARQC');

insert into student_cu
values('a70020','ISD');

insert into student_cu
values('a70020','EA');

insert into student_cu
values('a70020','EE');

insert into student_cu
values('a70020','CD');

insert into student_cu
values('a70020','PF');

insert into student
values('a70021','pass',0);

insert into student_cu
values('a70021','AC');

insert into student_cu
values('a70021','ARQC');

insert into student_cu
values('a70021','ISD');

insert into student_cu
values('a70021','EA');

insert into student_cu
values('a70021','EE');

insert into student_cu
values('a70021','CD');

insert into student_cu
values('a70021','PF');

insert into student
values('a70022','pass',0);

insert into student_cu
values('a70022','AC');

insert into student_cu
values('a70022','ARQC');

insert into student_cu
values('a70022','ISD');

insert into student_cu
values('a70022','EA');

insert into student_cu
values('a70022','EE');

insert into student_cu
values('a70022','CD');

insert into student_cu
values('a70022','PF');

insert into student
values('a70023','pass',0);

insert into student_cu
values('a70023','AC');

insert into student_cu
values('a70023','ARQC');

insert into student_cu
values('a70023','ISD');

insert into student_cu
values('a70023','EA');

insert into student_cu
values('a70023','EE');

insert into student_cu
values('a70023','CD');

insert into student_cu
values('a70023','PF');

insert into student
values('a70024','pass',0);

insert into student_cu
values('a70024','AC');

insert into student_cu
values('a70024','ARQC');

insert into student_cu
values('a70024','ISD');

insert into student_cu
values('a70024','EA');

insert into student_cu
values('a70024','EE');

insert into student_cu
values('a70024','CD');

insert into student_cu
values('a70024','PF');

insert into student
values('a70025','pass',0);

insert into student_cu
values('a70025','AC');

insert into student_cu
values('a70025','ARQC');

insert into student_cu
values('a70025','ISD');

insert into student_cu
values('a70025','EA');

insert into student_cu
values('a70025','EE');

insert into student_cu
values('a70025','CD');

insert into student
values('a70026','pass',0);

insert into student_cu
values('a70026','AC');

insert into student_cu
values('a70026','ARQC');

insert into student_cu
values('a70026','ISD');

insert into student_cu
values('a70026','EA');

insert into student_cu
values('a70026','EE');

insert into student_cu
values('a70026','CD');

insert into student
values('a70027','pass',0);

insert into student_cu
values('a70027','AC');

insert into student_cu
values('a70027','ARQC');

insert into student_cu
values('a70027','ISD');

insert into student_cu
values('a70027','EA');

insert into student_cu
values('a70027','EE');

insert into student_cu
values('a70027','CD');

insert into student
values('a70028','pass',0);

insert into student_cu
values('a70028','AC');

insert into student_cu
values('a70028','ARQC');

insert into student_cu
values('a70028','ISD');

insert into student_cu
values('a70028','EA');

insert into student_cu
values('a70028','EE');

insert into student_cu
values('a70028','CD');

insert into student
values('a70029','pass',0);

insert into student_cu
values('a70029','AC');

insert into student_cu
values('a70029','ARQC');

insert into student_cu
values('a70029','ISD');

insert into student_cu
values('a70029','EA');

insert into student_cu
values('a70029','EE');

insert into student_cu
values('a70029','CD');

insert into student
values('a70030','pass',1);

insert into student_cu
values('a70030','AC');

insert into student_cu
values('a70030','ARQC');

insert into student_cu
values('a70030','ISD');

insert into student_cu
values('a70030','EA');

insert into student_cu
values('a70030','EE');

insert into student_cu
values('a70030','CD');

insert into student
values('a70031','pass',0);

insert into student_cu
values('a70031','AC');

insert into student_cu
values('a70031','ARQC');

insert into student_cu
values('a70031','ISD');

insert into student_cu
values('a70031','EA');

insert into student_cu
values('a70031','EE');

insert into student_cu
values('a70031','CD');

insert into student
values('a70032','pass',0);

insert into student_cu
values('a70032','AC');

insert into student_cu
values('a70032','ARQC');

insert into student_cu
values('a70032','ISD');

insert into student_cu
values('a70032','EA');

insert into student_cu
values('a70032','EE');

insert into student_cu
values('a70032','CD');

insert into student
values('a70033','pass',0);

insert into student_cu
values('a70033','AC');

insert into student_cu
values('a70033','ARQC');

insert into student_cu
values('a70033','ISD');

insert into student_cu
values('a70033','EA');

insert into student_cu
values('a70033','EE');

insert into student_cu
values('a70033','CD');

insert into student
values('a70034','pass',0);

insert into student_cu
values('a70034','AC');

insert into student_cu
values('a70034','ARQC');

insert into student_cu
values('a70034','ISD');

insert into student_cu
values('a70034','EA');

insert into student_cu
values('a70034','EE');

insert into student_cu
values('a70034','CD');

insert into student
values('a70035','pass',0);

insert into student_cu
values('a70035','AC');

insert into student_cu
values('a70035','ARQC');

insert into student_cu
values('a70035','ISD');

insert into student_cu
values('a70035','EA');

insert into student_cu
values('a70035','EE');

insert into student_cu
values('a70035','CD');

insert into student
values('a70036','pass',0);

insert into student_cu
values('a70036','AC');

insert into student_cu
values('a70036','ARQC');

insert into student_cu
values('a70036','ISD');

insert into student_cu
values('a70036','EA');

insert into student_cu
values('a70036','EE');

insert into student_cu
values('a70036','CD');

insert into student
values('a70037','pass',0);

insert into student_cu
values('a70037','AC');

insert into student_cu
values('a70037','ARQC');

insert into student_cu
values('a70037','ISD');

insert into student_cu
values('a70037','EA');

insert into student_cu
values('a70037','EE');

insert into student_cu
values('a70037','CD');

insert into student
values('a70038','pass',0);

insert into student_cu
values('a70038','AC');

insert into student_cu
values('a70038','ARQC');

insert into student_cu
values('a70038','ISD');

insert into student_cu
values('a70038','EA');

insert into student_cu
values('a70038','EE');

insert into student_cu
values('a70038','CD');

insert into student
values('a70039','pass',0);

insert into student_cu
values('a70039','AC');

insert into student_cu
values('a70039','ARQC');

insert into student_cu
values('a70039','ISD');

insert into student_cu
values('a70039','EA');

insert into student_cu
values('a70039','EE');

insert into student_cu
values('a70039','CD');

insert into student
values('a70040','pass',1);

insert into student_cu
values('a70040','AC');

insert into student_cu
values('a70040','ARQC');

insert into student_cu
values('a70040','ISD');

insert into student_cu
values('a70040','EA');

insert into student_cu
values('a70040','EE');

insert into student_cu
values('a70040','CD');

insert into student
values('a70041','pass',0);

insert into student_cu
values('a70041','AC');

insert into student_cu
values('a70041','ARQC');

insert into student_cu
values('a70041','ISD');

insert into student_cu
values('a70041','EA');

insert into student_cu
values('a70041','EE');

insert into student_cu
values('a70041','CD');

insert into student
values('a70042','pass',0);

insert into student_cu
values('a70042','AC');

insert into student_cu
values('a70042','ARQC');

insert into student_cu
values('a70042','ISD');

insert into student_cu
values('a70042','EA');

insert into student_cu
values('a70042','EE');

insert into student_cu
values('a70042','CD');

insert into student
values('a70043','pass',0);

insert into student_cu
values('a70043','AC');

insert into student_cu
values('a70043','ARQC');

insert into student_cu
values('a70043','ISD');

insert into student_cu
values('a70043','EA');

insert into student_cu
values('a70043','EE');

insert into student_cu
values('a70043','CD');

insert into student
values('a70044','pass',0);

insert into student_cu
values('a70044','AC');

insert into student_cu
values('a70044','ARQC');

insert into student_cu
values('a70044','ISD');

insert into student_cu
values('a70044','EA');

insert into student_cu
values('a70044','EE');

insert into student_cu
values('a70044','CD');

insert into student
values('a70045','pass',0);

insert into student_cu
values('a70045','AC');

insert into student_cu
values('a70045','ARQC');

insert into student_cu
values('a70045','ISD');

insert into student_cu
values('a70045','EA');

insert into student_cu
values('a70045','EE');

insert into student_cu
values('a70045','CD');

insert into student
values('a70046','pass',0);

insert into student_cu
values('a70046','AC');

insert into student_cu
values('a70046','ARQC');

insert into student_cu
values('a70046','ISD');

insert into student_cu
values('a70046','EA');

insert into student_cu
values('a70046','EE');

insert into student_cu
values('a70046','CD');

insert into student
values('a70047','pass',0);

insert into student_cu
values('a70047','AC');

insert into student_cu
values('a70047','ARQC');

insert into student_cu
values('a70047','ISD');

insert into student_cu
values('a70047','EA');

insert into student_cu
values('a70047','EE');

insert into student_cu
values('a70047','CD');

insert into student
values('a70048','pass',0);

insert into student_cu
values('a70048','AC');

insert into student_cu
values('a70048','ARQC');

insert into student_cu
values('a70048','ISD');

insert into student_cu
values('a70048','EA');

insert into student_cu
values('a70048','EE');

insert into student_cu
values('a70048','CD');

insert into student
values('a70049','pass',0);

insert into student_cu
values('a70049','AC');

insert into student_cu
values('a70049','ARQC');

insert into student_cu
values('a70049','ISD');

insert into student_cu
values('a70049','EA');

insert into student_cu
values('a70049','EE');

insert into student_cu
values('a70049','CD');

insert into student
values('a70050','pass',1);

insert into student_cu
values('a70050','AC');

insert into student_cu
values('a70050','ARQC');

insert into student_cu
values('a70050','ISD');

insert into student_cu
values('a70050','EA');

insert into student_cu
values('a70050','EE');

insert into student_cu
values('a70050','CD');

insert into student
values('a70051','pass',0);

insert into student_cu
values('a70051','AC');

insert into student_cu
values('a70051','ARQC');

insert into student_cu
values('a70051','ISD');

insert into student_cu
values('a70051','EA');

insert into student_cu
values('a70051','EE');

insert into student_cu
values('a70051','CD');

insert into student
values('a70052','pass',0);

insert into student_cu
values('a70052','AC');

insert into student_cu
values('a70052','ARQC');

insert into student_cu
values('a70052','ISD');

insert into student_cu
values('a70052','EA');

insert into student_cu
values('a70052','EE');

insert into student_cu
values('a70052','CD');

insert into student
values('a70053','pass',0);

insert into student_cu
values('a70053','AC');

insert into student_cu
values('a70053','ARQC');

insert into student_cu
values('a70053','ISD');

insert into student_cu
values('a70053','EA');

insert into student_cu
values('a70053','EE');

insert into student_cu
values('a70053','CD');

insert into student
values('a70054','pass',0);

insert into student_cu
values('a70054','AC');

insert into student_cu
values('a70054','ARQC');

insert into student_cu
values('a70054','ISD');

insert into student_cu
values('a70054','EA');

insert into student_cu
values('a70054','EE');

insert into student_cu
values('a70054','CD');

insert into student
values('a70055','pass',0);

insert into student_cu
values('a70055','AC');

insert into student_cu
values('a70055','ARQC');

insert into student_cu
values('a70055','ISD');

insert into student_cu
values('a70055','EA');

insert into student_cu
values('a70055','EE');

insert into student_cu
values('a70055','CD');

insert into student
values('a70056','pass',0);

insert into student_cu
values('a70056','AC');

insert into student_cu
values('a70056','ARQC');

insert into student_cu
values('a70056','ISD');

insert into student_cu
values('a70056','EA');

insert into student_cu
values('a70056','EE');

insert into student_cu
values('a70056','CD');

insert into student
values('a70057','pass',0);

insert into student_cu
values('a70057','AC');

insert into student_cu
values('a70057','ARQC');

insert into student_cu
values('a70057','ISD');

insert into student_cu
values('a70057','EA');

insert into student_cu
values('a70057','EE');

insert into student_cu
values('a70057','CD');

insert into student
values('a70058','pass',0);

insert into student_cu
values('a70058','AC');

insert into student_cu
values('a70058','ARQC');

insert into student_cu
values('a70058','ISD');

insert into student_cu
values('a70058','EA');

insert into student_cu
values('a70058','EE');

insert into student_cu
values('a70058','CD');

insert into student
values('a70059','pass',0);

insert into student_cu
values('a70059','AC');

insert into student_cu
values('a70059','ARQC');

insert into student_cu
values('a70059','ISD');

insert into student_cu
values('a70059','EA');

insert into student_cu
values('a70059','EE');

insert into student_cu
values('a70059','CD');

insert into student
values('a70060','pass',1);

insert into student_cu
values('a70060','AC');

insert into student_cu
values('a70060','ARQC');

insert into student_cu
values('a70060','ISD');

insert into student_cu
values('a70060','EA');

insert into student_cu
values('a70060','EE');

insert into student_cu
values('a70060','CD');

insert into student
values('a70061','pass',0);

insert into student_cu
values('a70061','AC');

insert into student_cu
values('a70061','ARQC');

insert into student_cu
values('a70061','ISD');

insert into student_cu
values('a70061','EA');

insert into student_cu
values('a70061','EE');

insert into student_cu
values('a70061','CD');

insert into student
values('a70062','pass',0);

insert into student_cu
values('a70062','AC');

insert into student_cu
values('a70062','ARQC');

insert into student_cu
values('a70062','ISD');

insert into student_cu
values('a70062','EA');

insert into student_cu
values('a70062','EE');

insert into student_cu
values('a70062','CD');

insert into student
values('a70063','pass',0);

insert into student_cu
values('a70063','AC');

insert into student_cu
values('a70063','ARQC');

insert into student_cu
values('a70063','ISD');

insert into student_cu
values('a70063','EA');

insert into student_cu
values('a70063','EE');

insert into student_cu
values('a70063','CD');

insert into student
values('a70064','pass',0);

insert into student_cu
values('a70064','AC');

insert into student_cu
values('a70064','ARQC');

insert into student_cu
values('a70064','ISD');

insert into student_cu
values('a70064','EA');

insert into student_cu
values('a70064','EE');

insert into student_cu
values('a70064','CD');

insert into student
values('a70065','pass',0);

insert into student_cu
values('a70065','AC');

insert into student_cu
values('a70065','ARQC');

insert into student_cu
values('a70065','ISD');

insert into student_cu
values('a70065','EA');

insert into student_cu
values('a70065','EE');

insert into student_cu
values('a70065','CD');

insert into student
values('a70066','pass',0);

insert into student_cu
values('a70066','AC');

insert into student_cu
values('a70066','ARQC');

insert into student_cu
values('a70066','ISD');

insert into student_cu
values('a70066','EA');

insert into student_cu
values('a70066','EE');

insert into student_cu
values('a70066','CD');

insert into student
values('a70067','pass',0);

insert into student_cu
values('a70067','AC');

insert into student_cu
values('a70067','ARQC');

insert into student_cu
values('a70067','ISD');

insert into student_cu
values('a70067','EA');

insert into student_cu
values('a70067','EE');

insert into student_cu
values('a70067','CD');

insert into student
values('a70068','pass',0);

insert into student_cu
values('a70068','AC');

insert into student_cu
values('a70068','ARQC');

insert into student_cu
values('a70068','ISD');

insert into student_cu
values('a70068','EA');

insert into student_cu
values('a70068','EE');

insert into student_cu
values('a70068','CD');

insert into student
values('a70069','pass',0);

insert into student_cu
values('a70069','AC');

insert into student_cu
values('a70069','ARQC');

insert into student_cu
values('a70069','ISD');

insert into student_cu
values('a70069','EA');

insert into student_cu
values('a70069','EE');

insert into student_cu
values('a70069','CD');

insert into student
values('a70070','pass',1);

insert into student_cu
values('a70070','AC');

insert into student_cu
values('a70070','ARQC');

insert into student_cu
values('a70070','ISD');

insert into student_cu
values('a70070','EA');

insert into student_cu
values('a70070','EE');

insert into student_cu
values('a70070','CD');

insert into student
values('a70071','pass',0);

insert into student_cu
values('a70071','AC');

insert into student_cu
values('a70071','ARQC');

insert into student_cu
values('a70071','ISD');

insert into student_cu
values('a70071','EA');

insert into student_cu
values('a70071','EE');

insert into student_cu
values('a70071','CD');

insert into student
values('a70072','pass',0);

insert into student_cu
values('a70072','AC');

insert into student_cu
values('a70072','ARQC');

insert into student_cu
values('a70072','ISD');

insert into student_cu
values('a70072','EA');

insert into student_cu
values('a70072','EE');

insert into student_cu
values('a70072','CD');

insert into student
values('a70073','pass',0);

insert into student_cu
values('a70073','AC');

insert into student_cu
values('a70073','ARQC');

insert into student_cu
values('a70073','ISD');

insert into student_cu
values('a70073','EA');

insert into student_cu
values('a70073','EE');

insert into student_cu
values('a70073','CD');

insert into student
values('a70074','pass',0);

insert into student_cu
values('a70074','AC');

insert into student_cu
values('a70074','ARQC');

insert into student_cu
values('a70074','ISD');

insert into student_cu
values('a70074','EA');

insert into student_cu
values('a70074','EE');

insert into student_cu
values('a70074','CD');

insert into student
values('a70075','pass',0);

insert into student_cu
values('a70075','AC');

insert into student_cu
values('a70075','ARQC');

insert into student_cu
values('a70075','ISD');

insert into student_cu
values('a70075','EA');

insert into student_cu
values('a70075','EE');

insert into student_cu
values('a70075','CD');

insert into student
values('a70076','pass',0);

insert into student_cu
values('a70076','AC');

insert into student_cu
values('a70076','ARQC');

insert into student_cu
values('a70076','ISD');

insert into student_cu
values('a70076','EA');

insert into student_cu
values('a70076','EE');

insert into student_cu
values('a70076','CD');

insert into student
values('a70077','pass',0);

insert into student_cu
values('a70077','AC');

insert into student_cu
values('a70077','ARQC');

insert into student_cu
values('a70077','ISD');

insert into student_cu
values('a70077','EA');

insert into student_cu
values('a70077','EE');

insert into student_cu
values('a70077','CD');

insert into student
values('a70078','pass',0);

insert into student_cu
values('a70078','AC');

insert into student_cu
values('a70078','ARQC');

insert into student_cu
values('a70078','ISD');

insert into student_cu
values('a70078','EA');

insert into student_cu
values('a70078','EE');

insert into student_cu
values('a70078','CD');

insert into student
values('a70079','pass',0);

insert into student_cu
values('a70079','AC');

insert into student_cu
values('a70079','ARQC');

insert into student_cu
values('a70079','ISD');

insert into student_cu
values('a70079','EA');

insert into student_cu
values('a70079','EE');

insert into student_cu
values('a70079','CD');

insert into student
values('a70080','pass',1);

insert into student_cu
values('a70080','AC');

insert into student_cu
values('a70080','ARQC');

insert into student_cu
values('a70080','ISD');

insert into student_cu
values('a70080','EA');

insert into student_cu
values('a70080','EE');

insert into student_cu
values('a70080','CD');

insert into student
values('a70081','pass',0);

insert into student_cu
values('a70081','AC');

insert into student_cu
values('a70081','ARQC');

insert into student_cu
values('a70081','ISD');

insert into student_cu
values('a70081','EA');

insert into student_cu
values('a70081','EE');

insert into student_cu
values('a70081','CD');

insert into student
values('a70082','pass',0);

insert into student_cu
values('a70082','AC');

insert into student_cu
values('a70082','ARQC');

insert into student_cu
values('a70082','ISD');

insert into student_cu
values('a70082','EA');

insert into student_cu
values('a70082','EE');

insert into student_cu
values('a70082','CD');

insert into student
values('a70083','pass',0);

insert into student_cu
values('a70083','AC');

insert into student_cu
values('a70083','ARQC');

insert into student_cu
values('a70083','ISD');

insert into student_cu
values('a70083','EA');

insert into student_cu
values('a70083','EE');

insert into student_cu
values('a70083','CD');

insert into student
values('a70084','pass',0);

insert into student_cu
values('a70084','AC');

insert into student_cu
values('a70084','ARQC');

insert into student_cu
values('a70084','ISD');

insert into student_cu
values('a70084','EA');

insert into student_cu
values('a70084','EE');

insert into student_cu
values('a70084','CD');

insert into student
values('a70085','pass',0);

insert into student_cu
values('a70085','AC');

insert into student_cu
values('a70085','ARQC');

insert into student_cu
values('a70085','ISD');

insert into student_cu
values('a70085','EA');

insert into student_cu
values('a70085','EE');

insert into student_cu
values('a70085','CD');

insert into student
values('a70086','pass',0);

insert into student_cu
values('a70086','AC');

insert into student_cu
values('a70086','ARQC');

insert into student_cu
values('a70086','ISD');

insert into student_cu
values('a70086','EA');

insert into student_cu
values('a70086','EE');

insert into student_cu
values('a70086','CD');

insert into student
values('a70087','pass',0);

insert into student_cu
values('a70087','AC');

insert into student_cu
values('a70087','ARQC');

insert into student_cu
values('a70087','ISD');

insert into student_cu
values('a70087','EA');

insert into student_cu
values('a70087','EE');

insert into student_cu
values('a70087','CD');

insert into student
values('a70088','pass',0);

insert into student_cu
values('a70088','AC');

insert into student_cu
values('a70088','ARQC');

insert into student_cu
values('a70088','ISD');

insert into student_cu
values('a70088','EA');

insert into student_cu
values('a70088','EE');

insert into student_cu
values('a70088','CD');

insert into student
values('a70089','pass',0);

insert into student_cu
values('a70089','AC');

insert into student_cu
values('a70089','ARQC');

insert into student_cu
values('a70089','ISD');

insert into student_cu
values('a70089','EA');

insert into student_cu
values('a70089','EE');

insert into student_cu
values('a70089','CD');

insert into student
values('a70090','pass',1);

insert into student_cu
values('a70090','AC');

insert into student_cu
values('a70090','ARQC');

insert into student_cu
values('a70090','ISD');

insert into student_cu
values('a70090','EA');

insert into student_cu
values('a70090','EE');

insert into student_cu
values('a70090','CD');

insert into student
values('a70091','pass',0);

insert into student_cu
values('a70091','AC');

insert into student_cu
values('a70091','ARQC');

insert into student_cu
values('a70091','ISD');

insert into student_cu
values('a70091','EA');

insert into student_cu
values('a70091','EE');

insert into student_cu
values('a70091','CD');

insert into student
values('a70092','pass',0);

insert into student_cu
values('a70092','AC');

insert into student_cu
values('a70092','ARQC');

insert into student_cu
values('a70092','ISD');

insert into student_cu
values('a70092','EA');

insert into student_cu
values('a70092','EE');

insert into student_cu
values('a70092','CD');

insert into student
values('a70093','pass',0);

insert into student_cu
values('a70093','AC');

insert into student_cu
values('a70093','ARQC');

insert into student_cu
values('a70093','ISD');

insert into student_cu
values('a70093','EA');

insert into student_cu
values('a70093','EE');

insert into student_cu
values('a70093','CD');

insert into student
values('a70094','pass',0);

insert into student_cu
values('a70094','AC');

insert into student_cu
values('a70094','ARQC');

insert into student_cu
values('a70094','ISD');

insert into student_cu
values('a70094','EA');

insert into student_cu
values('a70094','EE');

insert into student_cu
values('a70094','CD');

insert into student
values('a70095','pass',0);

insert into student_cu
values('a70095','AC');

insert into student_cu
values('a70095','ARQC');

insert into student_cu
values('a70095','ISD');

insert into student_cu
values('a70095','EA');

insert into student_cu
values('a70095','EE');

insert into student_cu
values('a70095','CD');

insert into student
values('a70096','pass',0);

insert into student_cu
values('a70096','AC');

insert into student_cu
values('a70096','ARQC');

insert into student_cu
values('a70096','ISD');

insert into student_cu
values('a70096','EA');

insert into student_cu
values('a70096','EE');

insert into student_cu
values('a70096','CD');

insert into student
values('a70097','pass',0);

insert into student_cu
values('a70097','AC');

insert into student_cu
values('a70097','ARQC');

insert into student_cu
values('a70097','ISD');

insert into student_cu
values('a70097','EA');

insert into student_cu
values('a70097','EE');

insert into student_cu
values('a70097','CD');

insert into student
values('a70098','pass',0);

insert into student_cu
values('a70098','AC');

insert into student_cu
values('a70098','ARQC');

insert into student_cu
values('a70098','ISD');

insert into student_cu
values('a70098','EA');

insert into student_cu
values('a70098','EE');

insert into student_cu
values('a70098','CD');

insert into student
values('a70099','pass',0);

insert into student_cu
values('a70099','AC');

insert into student_cu
values('a70099','ARQC');

insert into student_cu
values('a70099','ISD');

insert into student_cu
values('a70099','EA');

insert into student_cu
values('a70099','EE');

insert into student_cu
values('a70099','CD');

insert into student
values('a60000','pass',1);

insert into student_cu
values('a60000','DSS');

insert into student_cu
values('a60000','SD');

insert into student_cu
values('a60000','MDIO');

insert into student_cu
values('a60000','MNOL');

insert into student_cu
values('a60000','BD');

insert into student_cu
values('a60000','RC');

insert into student_cu
values('a60000','PF');

insert into student_cu
values('a60000','AC');

insert into student
values('a60001','pass',0);

insert into student_cu
values('a60001','DSS');

insert into student_cu
values('a60001','SD');

insert into student_cu
values('a60001','MDIO');

insert into student_cu
values('a60001','MNOL');

insert into student_cu
values('a60001','BD');

insert into student_cu
values('a60001','RC');

insert into student_cu
values('a60001','PF');

insert into student_cu
values('a60001','AC');

insert into student
values('a60002','pass',0);

insert into student_cu
values('a60002','DSS');

insert into student_cu
values('a60002','SD');

insert into student_cu
values('a60002','MDIO');

insert into student_cu
values('a60002','MNOL');

insert into student_cu
values('a60002','BD');

insert into student_cu
values('a60002','RC');

insert into student_cu
values('a60002','PF');

insert into student_cu
values('a60002','AC');

insert into student
values('a60003','pass',0);

insert into student_cu
values('a60003','DSS');

insert into student_cu
values('a60003','SD');

insert into student_cu
values('a60003','MDIO');

insert into student_cu
values('a60003','MNOL');

insert into student_cu
values('a60003','BD');

insert into student_cu
values('a60003','RC');

insert into student_cu
values('a60003','PF');

insert into student_cu
values('a60003','AC');

insert into student
values('a60004','pass',0);

insert into student_cu
values('a60004','DSS');

insert into student_cu
values('a60004','SD');

insert into student_cu
values('a60004','MDIO');

insert into student_cu
values('a60004','MNOL');

insert into student_cu
values('a60004','BD');

insert into student_cu
values('a60004','RC');

insert into student_cu
values('a60004','PF');

insert into student_cu
values('a60004','AC');

insert into student
values('a60005','pass',0);

insert into student_cu
values('a60005','DSS');

insert into student_cu
values('a60005','SD');

insert into student_cu
values('a60005','MDIO');

insert into student_cu
values('a60005','MNOL');

insert into student_cu
values('a60005','BD');

insert into student_cu
values('a60005','RC');

insert into student_cu
values('a60005','PF');

insert into student_cu
values('a60005','AC');

insert into student
values('a60006','pass',0);

insert into student_cu
values('a60006','DSS');

insert into student_cu
values('a60006','SD');

insert into student_cu
values('a60006','MDIO');

insert into student_cu
values('a60006','MNOL');

insert into student_cu
values('a60006','BD');

insert into student_cu
values('a60006','RC');

insert into student_cu
values('a60006','PF');

insert into student_cu
values('a60006','AC');

insert into student
values('a60007','pass',0);

insert into student_cu
values('a60007','DSS');

insert into student_cu
values('a60007','SD');

insert into student_cu
values('a60007','MDIO');

insert into student_cu
values('a60007','MNOL');

insert into student_cu
values('a60007','BD');

insert into student_cu
values('a60007','RC');

insert into student_cu
values('a60007','PF');

insert into student_cu
values('a60007','AC');

insert into student
values('a60008','pass',0);

insert into student_cu
values('a60008','DSS');

insert into student_cu
values('a60008','SD');

insert into student_cu
values('a60008','MDIO');

insert into student_cu
values('a60008','MNOL');

insert into student_cu
values('a60008','BD');

insert into student_cu
values('a60008','RC');

insert into student_cu
values('a60008','PF');

insert into student_cu
values('a60008','AC');

insert into student
values('a60009','pass',0);

insert into student_cu
values('a60009','DSS');

insert into student_cu
values('a60009','SD');

insert into student_cu
values('a60009','MDIO');

insert into student_cu
values('a60009','MNOL');

insert into student_cu
values('a60009','BD');

insert into student_cu
values('a60009','RC');

insert into student_cu
values('a60009','PF');

insert into student_cu
values('a60009','AC');

insert into student
values('a60010','pass',1);

insert into student_cu
values('a60010','DSS');

insert into student_cu
values('a60010','SD');

insert into student_cu
values('a60010','MDIO');

insert into student_cu
values('a60010','MNOL');

insert into student_cu
values('a60010','BD');

insert into student_cu
values('a60010','RC');

insert into student_cu
values('a60010','PF');

insert into student_cu
values('a60010','AC');

insert into student
values('a60011','pass',0);

insert into student_cu
values('a60011','DSS');

insert into student_cu
values('a60011','SD');

insert into student_cu
values('a60011','MDIO');

insert into student_cu
values('a60011','MNOL');

insert into student_cu
values('a60011','BD');

insert into student_cu
values('a60011','RC');

insert into student_cu
values('a60011','PF');

insert into student_cu
values('a60011','AC');

insert into student
values('a60012','pass',0);

insert into student_cu
values('a60012','DSS');

insert into student_cu
values('a60012','SD');

insert into student_cu
values('a60012','MDIO');

insert into student_cu
values('a60012','MNOL');

insert into student_cu
values('a60012','BD');

insert into student_cu
values('a60012','RC');

insert into student_cu
values('a60012','PF');

insert into student_cu
values('a60012','AC');

insert into student
values('a60013','pass',0);

insert into student_cu
values('a60013','DSS');

insert into student_cu
values('a60013','SD');

insert into student_cu
values('a60013','MDIO');

insert into student_cu
values('a60013','MNOL');

insert into student_cu
values('a60013','BD');

insert into student_cu
values('a60013','RC');

insert into student_cu
values('a60013','PF');

insert into student_cu
values('a60013','AC');

insert into student
values('a60014','pass',0);

insert into student_cu
values('a60014','DSS');

insert into student_cu
values('a60014','SD');

insert into student_cu
values('a60014','MDIO');

insert into student_cu
values('a60014','MNOL');

insert into student_cu
values('a60014','BD');

insert into student_cu
values('a60014','RC');

insert into student_cu
values('a60014','PF');

insert into student_cu
values('a60014','AC');

insert into student
values('a60015','pass',0);

insert into student_cu
values('a60015','DSS');

insert into student_cu
values('a60015','SD');

insert into student_cu
values('a60015','MDIO');

insert into student_cu
values('a60015','MNOL');

insert into student_cu
values('a60015','BD');

insert into student_cu
values('a60015','RC');

insert into student_cu
values('a60015','PF');

insert into student_cu
values('a60015','AC');

insert into student
values('a60016','pass',0);

insert into student_cu
values('a60016','DSS');

insert into student_cu
values('a60016','SD');

insert into student_cu
values('a60016','MDIO');

insert into student_cu
values('a60016','MNOL');

insert into student_cu
values('a60016','BD');

insert into student_cu
values('a60016','RC');

insert into student_cu
values('a60016','PF');

insert into student_cu
values('a60016','AC');

insert into student
values('a60017','pass',0);

insert into student_cu
values('a60017','DSS');

insert into student_cu
values('a60017','SD');

insert into student_cu
values('a60017','MDIO');

insert into student_cu
values('a60017','MNOL');

insert into student_cu
values('a60017','BD');

insert into student_cu
values('a60017','RC');

insert into student_cu
values('a60017','PF');

insert into student_cu
values('a60017','AC');

insert into student
values('a60018','pass',0);

insert into student_cu
values('a60018','DSS');

insert into student_cu
values('a60018','SD');

insert into student_cu
values('a60018','MDIO');

insert into student_cu
values('a60018','MNOL');

insert into student_cu
values('a60018','BD');

insert into student_cu
values('a60018','RC');

insert into student_cu
values('a60018','PF');

insert into student_cu
values('a60018','AC');

insert into student
values('a60019','pass',0);

insert into student_cu
values('a60019','DSS');

insert into student_cu
values('a60019','SD');

insert into student_cu
values('a60019','MDIO');

insert into student_cu
values('a60019','MNOL');

insert into student_cu
values('a60019','BD');

insert into student_cu
values('a60019','RC');

insert into student_cu
values('a60019','PF');

insert into student_cu
values('a60019','AC');

insert into student
values('a60020','pass',1);

insert into student_cu
values('a60020','DSS');

insert into student_cu
values('a60020','SD');

insert into student_cu
values('a60020','MDIO');

insert into student_cu
values('a60020','MNOL');

insert into student_cu
values('a60020','BD');

insert into student_cu
values('a60020','RC');

insert into student_cu
values('a60020','PF');

insert into student_cu
values('a60020','AC');

insert into student
values('a60021','pass',0);

insert into student_cu
values('a60021','DSS');

insert into student_cu
values('a60021','SD');

insert into student_cu
values('a60021','MDIO');

insert into student_cu
values('a60021','MNOL');

insert into student_cu
values('a60021','BD');

insert into student_cu
values('a60021','RC');

insert into student_cu
values('a60021','PF');

insert into student_cu
values('a60021','AC');

insert into student
values('a60022','pass',0);

insert into student_cu
values('a60022','DSS');

insert into student_cu
values('a60022','SD');

insert into student_cu
values('a60022','MDIO');

insert into student_cu
values('a60022','MNOL');

insert into student_cu
values('a60022','BD');

insert into student_cu
values('a60022','RC');

insert into student_cu
values('a60022','PF');

insert into student_cu
values('a60022','AC');

insert into student
values('a60023','pass',0);

insert into student_cu
values('a60023','DSS');

insert into student_cu
values('a60023','SD');

insert into student_cu
values('a60023','MDIO');

insert into student_cu
values('a60023','MNOL');

insert into student_cu
values('a60023','BD');

insert into student_cu
values('a60023','RC');

insert into student_cu
values('a60023','PF');

insert into student_cu
values('a60023','AC');

insert into student
values('a60024','pass',0);

insert into student_cu
values('a60024','DSS');

insert into student_cu
values('a60024','SD');

insert into student_cu
values('a60024','MDIO');

insert into student_cu
values('a60024','MNOL');

insert into student_cu
values('a60024','BD');

insert into student_cu
values('a60024','RC');

insert into student_cu
values('a60024','PF');

insert into student_cu
values('a60024','AC');

insert into student
values('a60025','pass',0);

insert into student_cu
values('a60025','DSS');

insert into student_cu
values('a60025','SD');

insert into student_cu
values('a60025','MDIO');

insert into student_cu
values('a60025','MNOL');

insert into student_cu
values('a60025','BD');

insert into student_cu
values('a60025','RC');

insert into student
values('a60026','pass',0);

insert into student_cu
values('a60026','DSS');

insert into student_cu
values('a60026','SD');

insert into student_cu
values('a60026','MDIO');

insert into student_cu
values('a60026','MNOL');

insert into student_cu
values('a60026','BD');

insert into student_cu
values('a60026','RC');

insert into student
values('a60027','pass',0);

insert into student_cu
values('a60027','DSS');

insert into student_cu
values('a60027','SD');

insert into student_cu
values('a60027','MDIO');

insert into student_cu
values('a60027','MNOL');

insert into student_cu
values('a60027','BD');

insert into student_cu
values('a60027','RC');

insert into student
values('a60028','pass',0);

insert into student_cu
values('a60028','DSS');

insert into student_cu
values('a60028','SD');

insert into student_cu
values('a60028','MDIO');

insert into student_cu
values('a60028','MNOL');

insert into student_cu
values('a60028','BD');

insert into student_cu
values('a60028','RC');

insert into student
values('a60029','pass',0);

insert into student_cu
values('a60029','DSS');

insert into student_cu
values('a60029','SD');

insert into student_cu
values('a60029','MDIO');

insert into student_cu
values('a60029','MNOL');

insert into student_cu
values('a60029','BD');

insert into student_cu
values('a60029','RC');

insert into student
values('a60030','pass',1);

insert into student_cu
values('a60030','DSS');

insert into student_cu
values('a60030','SD');

insert into student_cu
values('a60030','MDIO');

insert into student_cu
values('a60030','MNOL');

insert into student_cu
values('a60030','BD');

insert into student_cu
values('a60030','RC');

insert into student
values('a60031','pass',0);

insert into student_cu
values('a60031','DSS');

insert into student_cu
values('a60031','SD');

insert into student_cu
values('a60031','MDIO');

insert into student_cu
values('a60031','MNOL');

insert into student_cu
values('a60031','BD');

insert into student_cu
values('a60031','RC');

insert into student
values('a60032','pass',0);

insert into student_cu
values('a60032','DSS');

insert into student_cu
values('a60032','SD');

insert into student_cu
values('a60032','MDIO');

insert into student_cu
values('a60032','MNOL');

insert into student_cu
values('a60032','BD');

insert into student_cu
values('a60032','RC');

insert into student
values('a60033','pass',0);

insert into student_cu
values('a60033','DSS');

insert into student_cu
values('a60033','SD');

insert into student_cu
values('a60033','MDIO');

insert into student_cu
values('a60033','MNOL');

insert into student_cu
values('a60033','BD');

insert into student_cu
values('a60033','RC');

insert into student
values('a60034','pass',0);

insert into student_cu
values('a60034','DSS');

insert into student_cu
values('a60034','SD');

insert into student_cu
values('a60034','MDIO');

insert into student_cu
values('a60034','MNOL');

insert into student_cu
values('a60034','BD');

insert into student_cu
values('a60034','RC');

insert into student
values('a60035','pass',0);

insert into student_cu
values('a60035','DSS');

insert into student_cu
values('a60035','SD');

insert into student_cu
values('a60035','MDIO');

insert into student_cu
values('a60035','MNOL');

insert into student_cu
values('a60035','BD');

insert into student_cu
values('a60035','RC');

insert into student
values('a60036','pass',0);

insert into student_cu
values('a60036','DSS');

insert into student_cu
values('a60036','SD');

insert into student_cu
values('a60036','MDIO');

insert into student_cu
values('a60036','MNOL');

insert into student_cu
values('a60036','BD');

insert into student_cu
values('a60036','RC');

insert into student
values('a60037','pass',0);

insert into student_cu
values('a60037','DSS');

insert into student_cu
values('a60037','SD');

insert into student_cu
values('a60037','MDIO');

insert into student_cu
values('a60037','MNOL');

insert into student_cu
values('a60037','BD');

insert into student_cu
values('a60037','RC');

insert into student
values('a60038','pass',0);

insert into student_cu
values('a60038','DSS');

insert into student_cu
values('a60038','SD');

insert into student_cu
values('a60038','MDIO');

insert into student_cu
values('a60038','MNOL');

insert into student_cu
values('a60038','BD');

insert into student_cu
values('a60038','RC');

insert into student
values('a60039','pass',0);

insert into student_cu
values('a60039','DSS');

insert into student_cu
values('a60039','SD');

insert into student_cu
values('a60039','MDIO');

insert into student_cu
values('a60039','MNOL');

insert into student_cu
values('a60039','BD');

insert into student_cu
values('a60039','RC');

insert into student
values('a60040','pass',1);

insert into student_cu
values('a60040','DSS');

insert into student_cu
values('a60040','SD');

insert into student_cu
values('a60040','MDIO');

insert into student_cu
values('a60040','MNOL');

insert into student_cu
values('a60040','BD');

insert into student_cu
values('a60040','RC');

insert into student
values('a60041','pass',0);

insert into student_cu
values('a60041','DSS');

insert into student_cu
values('a60041','SD');

insert into student_cu
values('a60041','MDIO');

insert into student_cu
values('a60041','MNOL');

insert into student_cu
values('a60041','BD');

insert into student_cu
values('a60041','RC');

insert into student
values('a60042','pass',0);

insert into student_cu
values('a60042','DSS');

insert into student_cu
values('a60042','SD');

insert into student_cu
values('a60042','MDIO');

insert into student_cu
values('a60042','MNOL');

insert into student_cu
values('a60042','BD');

insert into student_cu
values('a60042','RC');

insert into student
values('a60043','pass',0);

insert into student_cu
values('a60043','DSS');

insert into student_cu
values('a60043','SD');

insert into student_cu
values('a60043','MDIO');

insert into student_cu
values('a60043','MNOL');

insert into student_cu
values('a60043','BD');

insert into student_cu
values('a60043','RC');

insert into student
values('a60044','pass',0);

insert into student_cu
values('a60044','DSS');

insert into student_cu
values('a60044','SD');

insert into student_cu
values('a60044','MDIO');

insert into student_cu
values('a60044','MNOL');

insert into student_cu
values('a60044','BD');

insert into student_cu
values('a60044','RC');

insert into student
values('a60045','pass',0);

insert into student_cu
values('a60045','DSS');

insert into student_cu
values('a60045','SD');

insert into student_cu
values('a60045','MDIO');

insert into student_cu
values('a60045','MNOL');

insert into student_cu
values('a60045','BD');

insert into student_cu
values('a60045','RC');

insert into student
values('a60046','pass',0);

insert into student_cu
values('a60046','DSS');

insert into student_cu
values('a60046','SD');

insert into student_cu
values('a60046','MDIO');

insert into student_cu
values('a60046','MNOL');

insert into student_cu
values('a60046','BD');

insert into student_cu
values('a60046','RC');

insert into student
values('a60047','pass',0);

insert into student_cu
values('a60047','DSS');

insert into student_cu
values('a60047','SD');

insert into student_cu
values('a60047','MDIO');

insert into student_cu
values('a60047','MNOL');

insert into student_cu
values('a60047','BD');

insert into student_cu
values('a60047','RC');

insert into student
values('a60048','pass',0);

insert into student_cu
values('a60048','DSS');

insert into student_cu
values('a60048','SD');

insert into student_cu
values('a60048','MDIO');

insert into student_cu
values('a60048','MNOL');

insert into student_cu
values('a60048','BD');

insert into student_cu
values('a60048','RC');

insert into student
values('a60049','pass',0);

insert into student_cu
values('a60049','DSS');

insert into student_cu
values('a60049','SD');

insert into student_cu
values('a60049','MDIO');

insert into student_cu
values('a60049','MNOL');

insert into student_cu
values('a60049','BD');

insert into student_cu
values('a60049','RC');

insert into student
values('a60050','pass',1);

insert into student_cu
values('a60050','DSS');

insert into student_cu
values('a60050','SD');

insert into student_cu
values('a60050','MDIO');

insert into student_cu
values('a60050','MNOL');

insert into student_cu
values('a60050','BD');

insert into student_cu
values('a60050','RC');

insert into student
values('a60051','pass',0);

insert into student_cu
values('a60051','DSS');

insert into student_cu
values('a60051','SD');

insert into student_cu
values('a60051','MDIO');

insert into student_cu
values('a60051','MNOL');

insert into student_cu
values('a60051','BD');

insert into student_cu
values('a60051','RC');

insert into student
values('a60052','pass',0);

insert into student_cu
values('a60052','DSS');

insert into student_cu
values('a60052','SD');

insert into student_cu
values('a60052','MDIO');

insert into student_cu
values('a60052','MNOL');

insert into student_cu
values('a60052','BD');

insert into student_cu
values('a60052','RC');

insert into student
values('a60053','pass',0);

insert into student_cu
values('a60053','DSS');

insert into student_cu
values('a60053','SD');

insert into student_cu
values('a60053','MDIO');

insert into student_cu
values('a60053','MNOL');

insert into student_cu
values('a60053','BD');

insert into student_cu
values('a60053','RC');

insert into student
values('a60054','pass',0);

insert into student_cu
values('a60054','DSS');

insert into student_cu
values('a60054','SD');

insert into student_cu
values('a60054','MDIO');

insert into student_cu
values('a60054','MNOL');

insert into student_cu
values('a60054','BD');

insert into student_cu
values('a60054','RC');

insert into student
values('a60055','pass',0);

insert into student_cu
values('a60055','DSS');

insert into student_cu
values('a60055','SD');

insert into student_cu
values('a60055','MDIO');

insert into student_cu
values('a60055','MNOL');

insert into student_cu
values('a60055','BD');

insert into student_cu
values('a60055','RC');

insert into student
values('a60056','pass',0);

insert into student_cu
values('a60056','DSS');

insert into student_cu
values('a60056','SD');

insert into student_cu
values('a60056','MDIO');

insert into student_cu
values('a60056','MNOL');

insert into student_cu
values('a60056','BD');

insert into student_cu
values('a60056','RC');

insert into student
values('a60057','pass',0);

insert into student_cu
values('a60057','DSS');

insert into student_cu
values('a60057','SD');

insert into student_cu
values('a60057','MDIO');

insert into student_cu
values('a60057','MNOL');

insert into student_cu
values('a60057','BD');

insert into student_cu
values('a60057','RC');

insert into student
values('a60058','pass',0);

insert into student_cu
values('a60058','DSS');

insert into student_cu
values('a60058','SD');

insert into student_cu
values('a60058','MDIO');

insert into student_cu
values('a60058','MNOL');

insert into student_cu
values('a60058','BD');

insert into student_cu
values('a60058','RC');

insert into student
values('a60059','pass',0);

insert into student_cu
values('a60059','DSS');

insert into student_cu
values('a60059','SD');

insert into student_cu
values('a60059','MDIO');

insert into student_cu
values('a60059','MNOL');

insert into student_cu
values('a60059','BD');

insert into student_cu
values('a60059','RC');

insert into student
values('a60060','pass',1);

insert into student_cu
values('a60060','DSS');

insert into student_cu
values('a60060','SD');

insert into student_cu
values('a60060','MDIO');

insert into student_cu
values('a60060','MNOL');

insert into student_cu
values('a60060','BD');

insert into student_cu
values('a60060','RC');

insert into student
values('a60061','pass',0);

insert into student_cu
values('a60061','DSS');

insert into student_cu
values('a60061','SD');

insert into student_cu
values('a60061','MDIO');

insert into student_cu
values('a60061','MNOL');

insert into student_cu
values('a60061','BD');

insert into student_cu
values('a60061','RC');

insert into student
values('a60062','pass',0);

insert into student_cu
values('a60062','DSS');

insert into student_cu
values('a60062','SD');

insert into student_cu
values('a60062','MDIO');

insert into student_cu
values('a60062','MNOL');

insert into student_cu
values('a60062','BD');

insert into student_cu
values('a60062','RC');

insert into student
values('a60063','pass',0);

insert into student_cu
values('a60063','DSS');

insert into student_cu
values('a60063','SD');

insert into student_cu
values('a60063','MDIO');

insert into student_cu
values('a60063','MNOL');

insert into student_cu
values('a60063','BD');

insert into student_cu
values('a60063','RC');

insert into student
values('a60064','pass',0);

insert into student_cu
values('a60064','DSS');

insert into student_cu
values('a60064','SD');

insert into student_cu
values('a60064','MDIO');

insert into student_cu
values('a60064','MNOL');

insert into student_cu
values('a60064','BD');

insert into student_cu
values('a60064','RC');

insert into student
values('a60065','pass',0);

insert into student_cu
values('a60065','DSS');

insert into student_cu
values('a60065','SD');

insert into student_cu
values('a60065','MDIO');

insert into student_cu
values('a60065','MNOL');

insert into student_cu
values('a60065','BD');

insert into student_cu
values('a60065','RC');

insert into student
values('a60066','pass',0);

insert into student_cu
values('a60066','DSS');

insert into student_cu
values('a60066','SD');

insert into student_cu
values('a60066','MDIO');

insert into student_cu
values('a60066','MNOL');

insert into student_cu
values('a60066','BD');

insert into student_cu
values('a60066','RC');

insert into student
values('a60067','pass',0);

insert into student_cu
values('a60067','DSS');

insert into student_cu
values('a60067','SD');

insert into student_cu
values('a60067','MDIO');

insert into student_cu
values('a60067','MNOL');

insert into student_cu
values('a60067','BD');

insert into student_cu
values('a60067','RC');

insert into student
values('a60068','pass',0);

insert into student_cu
values('a60068','DSS');

insert into student_cu
values('a60068','SD');

insert into student_cu
values('a60068','MDIO');

insert into student_cu
values('a60068','MNOL');

insert into student_cu
values('a60068','BD');

insert into student_cu
values('a60068','RC');

insert into student
values('a60069','pass',0);

insert into student_cu
values('a60069','DSS');

insert into student_cu
values('a60069','SD');

insert into student_cu
values('a60069','MDIO');

insert into student_cu
values('a60069','MNOL');

insert into student_cu
values('a60069','BD');

insert into student_cu
values('a60069','RC');

insert into student
values('a60070','pass',1);

insert into student_cu
values('a60070','DSS');

insert into student_cu
values('a60070','SD');

insert into student_cu
values('a60070','MDIO');

insert into student_cu
values('a60070','MNOL');

insert into student_cu
values('a60070','BD');

insert into student_cu
values('a60070','RC');

insert into student
values('a60071','pass',0);

insert into student_cu
values('a60071','DSS');

insert into student_cu
values('a60071','SD');

insert into student_cu
values('a60071','MDIO');

insert into student_cu
values('a60071','MNOL');

insert into student_cu
values('a60071','BD');

insert into student_cu
values('a60071','RC');

insert into student
values('a60072','pass',0);

insert into student_cu
values('a60072','DSS');

insert into student_cu
values('a60072','SD');

insert into student_cu
values('a60072','MDIO');

insert into student_cu
values('a60072','MNOL');

insert into student_cu
values('a60072','BD');

insert into student_cu
values('a60072','RC');

insert into student
values('a60073','pass',0);

insert into student_cu
values('a60073','DSS');

insert into student_cu
values('a60073','SD');

insert into student_cu
values('a60073','MDIO');

insert into student_cu
values('a60073','MNOL');

insert into student_cu
values('a60073','BD');

insert into student_cu
values('a60073','RC');

insert into student
values('a60074','pass',0);

insert into student_cu
values('a60074','DSS');

insert into student_cu
values('a60074','SD');

insert into student_cu
values('a60074','MDIO');

insert into student_cu
values('a60074','MNOL');

insert into student_cu
values('a60074','BD');

insert into student_cu
values('a60074','RC');

insert into student
values('a60075','pass',0);

insert into student_cu
values('a60075','DSS');

insert into student_cu
values('a60075','SD');

insert into student_cu
values('a60075','MDIO');

insert into student_cu
values('a60075','MNOL');

insert into student_cu
values('a60075','BD');

insert into student_cu
values('a60075','RC');

insert into student
values('a60076','pass',0);

insert into student_cu
values('a60076','DSS');

insert into student_cu
values('a60076','SD');

insert into student_cu
values('a60076','MDIO');

insert into student_cu
values('a60076','MNOL');

insert into student_cu
values('a60076','BD');

insert into student_cu
values('a60076','RC');

insert into student
values('a60077','pass',0);

insert into student_cu
values('a60077','DSS');

insert into student_cu
values('a60077','SD');

insert into student_cu
values('a60077','MDIO');

insert into student_cu
values('a60077','MNOL');

insert into student_cu
values('a60077','BD');

insert into student_cu
values('a60077','RC');

insert into student
values('a60078','pass',0);

insert into student_cu
values('a60078','DSS');

insert into student_cu
values('a60078','SD');

insert into student_cu
values('a60078','MDIO');

insert into student_cu
values('a60078','MNOL');

insert into student_cu
values('a60078','BD');

insert into student_cu
values('a60078','RC');

insert into student
values('a60079','pass',0);

insert into student_cu
values('a60079','DSS');

insert into student_cu
values('a60079','SD');

insert into student_cu
values('a60079','MDIO');

insert into student_cu
values('a60079','MNOL');

insert into student_cu
values('a60079','BD');

insert into student_cu
values('a60079','RC');

insert into student
values('a60080','pass',1);

insert into student_cu
values('a60080','DSS');

insert into student_cu
values('a60080','SD');

insert into student_cu
values('a60080','MDIO');

insert into student_cu
values('a60080','MNOL');

insert into student_cu
values('a60080','BD');

insert into student_cu
values('a60080','RC');

insert into student
values('a60081','pass',0);

insert into student_cu
values('a60081','DSS');

insert into student_cu
values('a60081','SD');

insert into student_cu
values('a60081','MDIO');

insert into student_cu
values('a60081','MNOL');

insert into student_cu
values('a60081','BD');

insert into student_cu
values('a60081','RC');

insert into student
values('a60082','pass',0);

insert into student_cu
values('a60082','DSS');

insert into student_cu
values('a60082','SD');

insert into student_cu
values('a60082','MDIO');

insert into student_cu
values('a60082','MNOL');

insert into student_cu
values('a60082','BD');

insert into student_cu
values('a60082','RC');

insert into student
values('a60083','pass',0);

insert into student_cu
values('a60083','DSS');

insert into student_cu
values('a60083','SD');

insert into student_cu
values('a60083','MDIO');

insert into student_cu
values('a60083','MNOL');

insert into student_cu
values('a60083','BD');

insert into student_cu
values('a60083','RC');

insert into student
values('a60084','pass',0);

insert into student_cu
values('a60084','DSS');

insert into student_cu
values('a60084','SD');

insert into student_cu
values('a60084','MDIO');

insert into student_cu
values('a60084','MNOL');

insert into student_cu
values('a60084','BD');

insert into student_cu
values('a60084','RC');

insert into student
values('a60085','pass',0);

insert into student_cu
values('a60085','DSS');

insert into student_cu
values('a60085','SD');

insert into student_cu
values('a60085','MDIO');

insert into student_cu
values('a60085','MNOL');

insert into student_cu
values('a60085','BD');

insert into student_cu
values('a60085','RC');

insert into student
values('a60086','pass',0);

insert into student_cu
values('a60086','DSS');

insert into student_cu
values('a60086','SD');

insert into student_cu
values('a60086','MDIO');

insert into student_cu
values('a60086','MNOL');

insert into student_cu
values('a60086','BD');

insert into student_cu
values('a60086','RC');

insert into student
values('a60087','pass',0);

insert into student_cu
values('a60087','DSS');

insert into student_cu
values('a60087','SD');

insert into student_cu
values('a60087','MDIO');

insert into student_cu
values('a60087','MNOL');

insert into student_cu
values('a60087','BD');

insert into student_cu
values('a60087','RC');

insert into student
values('a60088','pass',0);

insert into student_cu
values('a60088','DSS');

insert into student_cu
values('a60088','SD');

insert into student_cu
values('a60088','MDIO');

insert into student_cu
values('a60088','MNOL');

insert into student_cu
values('a60088','BD');

insert into student_cu
values('a60088','RC');

insert into student
values('a60089','pass',0);

insert into student_cu
values('a60089','DSS');

insert into student_cu
values('a60089','SD');

insert into student_cu
values('a60089','MDIO');

insert into student_cu
values('a60089','MNOL');

insert into student_cu
values('a60089','BD');

insert into student_cu
values('a60089','RC');

insert into student
values('a60090','pass',1);

insert into student_cu
values('a60090','DSS');

insert into student_cu
values('a60090','SD');

insert into student_cu
values('a60090','MDIO');

insert into student_cu
values('a60090','MNOL');

insert into student_cu
values('a60090','BD');

insert into student_cu
values('a60090','RC');

insert into student
values('a60091','pass',0);

insert into student_cu
values('a60091','DSS');

insert into student_cu
values('a60091','SD');

insert into student_cu
values('a60091','MDIO');

insert into student_cu
values('a60091','MNOL');

insert into student_cu
values('a60091','BD');

insert into student_cu
values('a60091','RC');

insert into student
values('a60092','pass',0);

insert into student_cu
values('a60092','DSS');

insert into student_cu
values('a60092','SD');

insert into student_cu
values('a60092','MDIO');

insert into student_cu
values('a60092','MNOL');

insert into student_cu
values('a60092','BD');

insert into student_cu
values('a60092','RC');

insert into student
values('a60093','pass',0);

insert into student_cu
values('a60093','DSS');

insert into student_cu
values('a60093','SD');

insert into student_cu
values('a60093','MDIO');

insert into student_cu
values('a60093','MNOL');

insert into student_cu
values('a60093','BD');

insert into student_cu
values('a60093','RC');

insert into student
values('a60094','pass',0);

insert into student_cu
values('a60094','DSS');

insert into student_cu
values('a60094','SD');

insert into student_cu
values('a60094','MDIO');

insert into student_cu
values('a60094','MNOL');

insert into student_cu
values('a60094','BD');

insert into student_cu
values('a60094','RC');

insert into student
values('a60095','pass',0);

insert into student_cu
values('a60095','DSS');

insert into student_cu
values('a60095','SD');

insert into student_cu
values('a60095','MDIO');

insert into student_cu
values('a60095','MNOL');

insert into student_cu
values('a60095','BD');

insert into student_cu
values('a60095','RC');

insert into student
values('a60096','pass',0);

insert into student_cu
values('a60096','DSS');

insert into student_cu
values('a60096','SD');

insert into student_cu
values('a60096','MDIO');

insert into student_cu
values('a60096','MNOL');

insert into student_cu
values('a60096','BD');

insert into student_cu
values('a60096','RC');

insert into student
values('a60097','pass',0);

insert into student_cu
values('a60097','DSS');

insert into student_cu
values('a60097','SD');

insert into student_cu
values('a60097','MDIO');

insert into student_cu
values('a60097','MNOL');

insert into student_cu
values('a60097','BD');

insert into student_cu
values('a60097','RC');

insert into student
values('a60098','pass',0);

insert into student_cu
values('a60098','DSS');

insert into student_cu
values('a60098','SD');

insert into student_cu
values('a60098','MDIO');

insert into student_cu
values('a60098','MNOL');

insert into student_cu
values('a60098','BD');

insert into student_cu
values('a60098','RC');

insert into student
values('a60099','pass',0);

insert into student_cu
values('a60099','DSS');

insert into student_cu
values('a60099','SD');

insert into student_cu
values('a60099','MDIO');

insert into student_cu
values('a60099','MNOL');

insert into student_cu
values('a60099','BD');

insert into student_cu
values('a60099','RC');

insert into teacher
values('p101','pass');

insert into teacher
values('p102','pass');

insert into teacher
values('p103','pass');

insert into teacher
values('p104','pass');

insert into teacher
values('p105','pass');

insert into teacher
values('p106','pass');

insert into teacher
values('p201','pass');

insert into teacher
values('p202','pass');

insert into teacher
values('p203','pass');

insert into teacher
values('p204','pass');

insert into teacher
values('p205','pass');

insert into teacher
values('p206','pass');

insert into teacher
values('p301','pass');

insert into teacher
values('p302','pass');

insert into teacher
values('p303','pass');

insert into teacher
values('p304','pass');

insert into teacher
values('p305','pass');

insert into teacher
values('p306','pass');

insert into teacher_cu
values('p101','EES');

insert into teacher_cu
values('p102','PF');

insert into teacher_cu
values('p103','TMD');

insert into teacher_cu
values('p104','CALC');

insert into teacher_cu
values('p105','ALG');

insert into teacher_cu
values('p106','LI1');

insert into teacher_cu
values('p201','AC');

insert into teacher_cu
values('p202','ARQC');

insert into teacher_cu
values('p203','ISD');

insert into teacher_cu
values('p204','EA');

insert into teacher_cu
values('p205','EE');

insert into teacher_cu
values('p206','CD');

insert into teacher_cu
values('p301','DSS');

insert into teacher_cu
values('p302','SD');

insert into teacher_cu
values('p303','MDIO');

insert into teacher_cu
values('p304','MNOL');

insert into teacher_cu
values('p305','BD');

insert into teacher_cu
values('p306','RC');

