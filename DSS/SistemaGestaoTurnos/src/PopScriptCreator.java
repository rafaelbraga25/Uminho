
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public class PopScriptCreator {
    
    private PrintWriter pw;
    
    
    public void createSQLFile(String sqlFile) {
        try {
            pw = new PrintWriter(new BufferedWriter(
                            new FileWriter(sqlFile)));
            
            pw.write("use scdb;\n");
            pw.write("set SQL_SAFE_UPDATES = 0;\n\n");
            
            
            createCU("EES", 1, 1);   

        
            createShift("EES", "T1", true, 100, 10);
            createTimetable("EES", "T1", 2, 9, 11);


            createShift("EES", "PL1", false, 20, 10);
            createTimetable("EES", "PL1", 2, 11, 13);


            createShift("EES", "PL3", false, 20, 10);
            createTimetable("EES", "PL3", 4, 9, 11);


            createShift("EES", "PL5", false, 20, 10);
            createTimetable("EES", "PL5", 4, 11, 13);


            createShift("EES", "PL6", false, 20, 10);
            createTimetable("EES", "PL6", 4, 13, 15);


            createShift("EES", "PL2", false, 20, 10);
            createTimetable("EES", "PL2", 6, 14, 16);


            createShift("EES", "PL4", false, 20, 10);
            createTimetable("EES", "PL4", 6, 16, 18);


            createShift("EES", "PL7", false, 20, 10);
            createTimetable("EES", "PL7", 6, 11, 13);





            createCU("PF", 1, 1);

            createShift("PF", "TP1", false, 20, 10);
            createTimetable("PF", "TP1", 2, 11, 13);


            createShift("PF", "TP2", false, 20, 10);
            createTimetable("PF", "TP2", 2, 11, 13);


            createShift("PF", "T1", true, 50, 10);
            createTimetable("PF", "T1", 2, 14, 15);
            createTimetable("PF", "T1", 6, 10, 11);


            createShift("PF", "T2", true, 50, 10);
            createTimetable("PF", "T2", 2, 14, 15);
            createTimetable("PF", "T2", 6, 10, 11);


            createShift("PF", "TP5", false, 20, 10);
            createTimetable("PF", "TP5", 4, 9, 11);


            createShift("PF", "TP7", false, 20, 10);
            createTimetable("PF", "TP7", 4, 9, 11);


            createShift("PF", "TP3", false, 20, 10);
            createTimetable("PF", "TP3", 4, 11, 13);


            createShift("PF", "TP6", false, 20, 10);
            createTimetable("PF", "TP6", 4, 11, 13);


            createShift("PF", "TP4", false, 20, 10);
            createTimetable("PF", "TP4", 6, 11, 13);


            createShift("PF", "TP8", false, 20, 10);
            createTimetable("PF", "TP8", 6, 11, 13);
            

            


            createCU("LI1", 1, 1);

            createShift("LI1", "PL1", false, 15, 10);
            createTimetable("LI1", "PL1", 2, 11, 13);


            createShift("LI1", "PL7", false, 15, 10);
            createTimetable("LI1", "PL7", 2, 11, 13);


            createShift("LI1", "PL6", false, 15, 10);
            createTimetable("LI1", "PL6", 4, 9, 11);


            createShift("LI1", "PL3", false, 15, 10);
            createTimetable("LI1", "PL3", 4, 9, 11);


            createShift("LI1", "PL8", false, 15, 10);
            createTimetable("LI1", "PL8", 4, 11, 13);


            createShift("LI1", "PL4", false, 15, 10);
            createTimetable("LI1", "PL4", 4, 11, 13);


            createShift("LI1", "PL5", false, 35, 10);
            createTimetable("LI1", "PL5", 6, 11, 13);


            createShift("LI1", "PL2", false, 35, 10);
            createTimetable("LI1", "PL2", 6, 11, 13);


            


            createCU("CALC", 1, 1);

            createShift("CALC", "TP5", false, 30, 10);
            createTimetable("CALC", "TP5", 2, 15, 17);
            createTimetable("CALC", "TP5", 6, 14, 16);


            createShift("CALC", "TP1", false, 30, 10);
            createTimetable("CALC", "TP1", 3, 9, 11);
            createTimetable("CALC", "TP1", 5, 9, 11);


            createShift("CALC", "TP2", false, 30, 10);
            createTimetable("CALC", "TP2", 3, 11, 13);
            createTimetable("CALC", "TP2", 5, 11, 13);


            createShift("CALC", "TP3", false, 30, 10);
            createTimetable("CALC", "TP3", 3, 14, 16);
            createTimetable("CALC", "TP3", 5, 14, 16);


            createShift("CALC", "TP4", false, 30, 10);
            createTimetable("CALC", "TP4", 3, 14, 16);
            createTimetable("CALC", "TP4", 5, 14, 16);


            


            createCU("TMD", 1, 1);

            createShift("TMD", "TP3", false, 40, 10);
            createTimetable("TMD", "TP3", 3, 9, 11);
            createTimetable("TMD", "TP3", 5, 9, 11);


            createShift("TMD", "TP4", false, 40, 10);
            createTimetable("TMD", "TP4", 3, 11, 13);
            createTimetable("TMD", "TP4", 5, 11, 13);


            createShift("TMD", "TP1", false, 40, 10);
            createTimetable("TMD", "TP1", 3, 14, 16);
            createTimetable("TMD", "TP1", 5, 14, 16);


            createShift("TMD", "TP2", false, 40, 10);
            createTimetable("TMD", "TP2", 3, 14, 16);
            createTimetable("TMD", "TP2", 5, 14, 16);


            


            createCU("ALG", 1, 1);

            createShift("ALG", "TP1", false, 40, 10);
            createTimetable("ALG", "TP1", 3, 9, 11);
            createTimetable("ALG", "TP1", 5, 9, 11);


            createShift("ALG", "TP3", false, 40, 10);
            createTimetable("ALG", "TP3", 3, 9, 11);
            createTimetable("ALG", "TP3", 5, 9, 11);


            createShift("ALG", "TP2", false, 40, 10);
            createTimetable("ALG", "TP2", 3, 11, 13);
            createTimetable("ALG", "TP2", 5, 11, 13);


            createShift("ALG", "TP4", false, 40, 10);
            createTimetable("ALG", "TP4", 3, 11, 13);
            createTimetable("ALG", "TP4", 5, 11, 13);


            


            createCU("EA", 2, 1);

            createShift("EA", "T1", true, 100, 10);
            createTimetable("EA", "T1", 2, 13, 15);


            createShift("EA", "TP3", false, 30, 10);
            createTimetable("EA", "TP3", 2, 15, 17);


            createShift("EA", "TP1", false, 30, 10);
            createTimetable("EA", "TP1", 2, 17, 19);


            createShift("EA", "TP2", false, 30, 10);
            createTimetable("EA", "TP2", 5, 17, 19);


            createShift("EA", "TP4", false, 30, 10);
            createTimetable("EA", "TP4", 5, 17, 19);


            


            createCU("EE", 2, 1);

            createShift("EE", "TP2", false, 30, 10);
            createTimetable("EE", "TP2", 2, 15, 17);


            createShift("EE", "TP1", false, 30, 10);
            createTimetable("EE", "TP1", 2, 17, 19);


            createShift("EE", "T1", true, 100, 10);
            createTimetable("EE", "T1", 5, 13, 15);


            createShift("EE", "TP3", false, 30, 10);
            createTimetable("EE", "TP3", 5, 15, 17);


            createShift("EE", "TP4", false, 30, 10);
            createTimetable("EE", "TP4", 5, 17, 19);


            


            createCU("CD", 2, 1);

            createShift("CD", "TP3", false, 30, 10);
            createTimetable("CD", "TP3", 2, 15, 17);


            createShift("CD", "TP2", false, 30, 10);
            createTimetable("CD", "TP2", 2, 17, 19);


            createShift("CD", "TP1", false, 30, 10);
            createTimetable("CD", "TP1", 4, 9, 11);


            createShift("CD", "TP4", false, 30, 10);
            createTimetable("CD", "TP4", 4, 11, 13);


            createShift("CD", "T1", true, 100, 10);
            createTimetable("CD", "T1", 6, 14, 16);


            


            createCU("ISD", 2, 1);

            createShift("ISD", "TP3", false, 40, 10);
            createTimetable("ISD", "TP3", 3, 9, 11);
            createTimetable("ISD", "TP3", 4, 11, 13);


            createShift("ISD", "TP1", false, 40, 10);
            createTimetable("ISD", "TP1", 4, 9, 11);
            createTimetable("ISD", "TP1", 5, 15, 17);


            createShift("ISD", "TP2", false, 40, 10);
            createTimetable("ISD", "TP2", 3, 16, 18);
            createTimetable("ISD", "TP2", 6, 16, 18);


            


            createCU("ARQC", 2, 1);
            
            createShift("ARQC", "PL4", false, 20, 10);
            createTimetable("ARQC", "PL4", 3, 9, 11);


            createShift("ARQC", "T1", true, 100, 10);
            createTimetable("ARQC", "T1", 3, 13, 14);
            createTimetable("ARQC", "T1", 6, 13, 14);


            createShift("ARQC", "PL1", false, 20, 10);
            createTimetable("ARQC", "PL1", 3, 14, 16);


            createShift("ARQC", "PL6", false, 20, 10);
            createTimetable("ARQC", "PL6", 3, 16, 18);


            createShift("ARQC", "PL3", false, 20, 10);
            createTimetable("ARQC", "PL3", 4, 9, 11);


            createShift("ARQC", "PL5", false, 20, 10);
            createTimetable("ARQC", "PL5", 4, 11, 13);


            createShift("ARQC", "PL2", false, 20, 10);
            createTimetable("ARQC", "PL2", 5, 15, 17);


            


            createCU("AC", 2, 1);

            createShift("AC", "TP7", false, 20, 10);
            createTimetable("AC", "TP7", 3, 14, 16);


            createShift("AC", "TP1", false, 20, 10);
            createTimetable("AC", "TP1", 3, 14, 16);


            createShift("AC", "TP6", false, 20, 10);
            createTimetable("AC", "TP6", 3, 14, 16);


            createShift("AC", "TP3", false, 20, 10);
            createTimetable("AC", "TP3", 3, 16, 18);


            createShift("AC", "T1", true, 100, 10);
            createTimetable("AC", "T1", 5, 9, 11);


            createShift("AC", "TP4", false, 20, 10);
            createTimetable("AC", "TP4", 5, 15, 17);


            createShift("AC", "TP8", false, 20, 10);
            createTimetable("AC", "TP8", 5, 15, 17);


            createShift("AC", "TP2", false, 20, 10);
            createTimetable("AC", "TP2", 5, 17, 19);


            createShift("AC", "TP5", false, 20, 10);
            createTimetable("AC", "TP5", 5, 17, 19);



            createCU("RC", 3, 1);

            createShift("RC", "PL4", false, 20, 10);
            createTimetable("RC", "PL4", 2, 9, 11);


            createShift("RC", "PL1", false, 20, 10);
            createTimetable("RC", "PL1", 2, 14, 16);


            createShift("RC", "PL5", false, 20, 10);
            createTimetable("RC", "PL5", 2, 16, 18);


            createShift("RC", "PL3", false, 20, 10);
            createTimetable("RC", "PL3", 3, 9, 11);


            createShift("RC", "T1", true, 100, 10);
            createTimetable("RC", "T1", 5, 11, 13);


            createShift("RC", "PL2", false, 20, 10);
            createTimetable("RC", "PL2", 6, 14, 16);


            


            createCU("MNOL", 3, 1);

            createShift("MNOL", "PL5", false, 20, 10);
            createTimetable("MNOL", "PL5", 2, 9, 11);


            createShift("MNOL", "PL2", false, 20, 10);
            createTimetable("MNOL", "PL2", 2, 16, 18);


            createShift("MNOL", "T1", true, 100, 10);
            createTimetable("MNOL", "T1", 3, 11, 13);


            createShift("MNOL", "PL4", false, 20, 10);
            createTimetable("MNOL", "PL4", 3, 14, 16);


            createShift("MNOL", "PL1", false, 20, 10);
            createTimetable("MNOL", "PL1", 4, 9, 11);


            createShift("MNOL", "PL3", false, 20, 10);
            createTimetable("MNOL", "PL3", 6, 14, 16);


            



            createCU("BD", 3, 1);
            
            createShift("BD", "PL4", false, 20, 10);
            createTimetable("BD", "PL4", 2, 9, 11);


            createShift("BD", "PL1", false, 20, 10);
            createTimetable("BD", "PL1", 2, 14, 16);


            createShift("BD", "PL6", false, 20, 10);
            createTimetable("BD", "PL6", 3, 9, 11);


            createShift("BD", "PL5", false, 20, 10);
            createTimetable("BD", "PL5", 3, 16, 18);


            createShift("BD", "T1", true, 100, 10);
            createTimetable("BD", "T1", 4, 11, 13);


            createShift("BD", "PL2", false, 20, 10);
            createTimetable("BD", "PL2", 5, 14, 16);


            createShift("BD", "PL3", false, 20, 10);
            createTimetable("BD", "PL3", 5, 16, 18);



            createCU("MDIO", 3, 1);

            createShift("MDIO", "T1", true, 100, 10);
            createTimetable("MDIO", "T1", 2, 11, 13);


            createShift("MDIO", "TP2", false, 30, 10);
            createTimetable("MDIO", "TP2", 4, 9, 11);


            createShift("MDIO", "TP4", false, 30, 10);
            createTimetable("MDIO", "TP4", 4, 9, 11);


            createShift("MDIO", "TP3", false, 30, 10);
            createTimetable("MDIO", "TP3", 5, 14, 16);


            createShift("MDIO", "TP1", false, 30, 10);
            createTimetable("MDIO", "TP1", 5, 16, 18);


            

            createCU("SD", 3, 1);

            createShift("SD", "PL3", false, 20, 10);
            createTimetable("SD", "PL3", 2, 14, 16);


            createShift("SD", "PL1", false, 20, 10);
            createTimetable("SD", "PL1", 3, 9, 11);


            createShift("SD", "PL6", false, 20, 10);
            createTimetable("SD", "PL6", 3, 9, 11);


            createShift("SD", "PL5", false, 20, 10);
            createTimetable("SD", "PL5", 3, 14, 16);


            createShift("SD", "PL4", false, 20, 10);
            createTimetable("SD", "PL4", 3, 16, 18);

           
            createShift("SD", "PL2", false, 20, 10);
            createTimetable("SD", "PL2", 5, 9, 11);


            createShift("SD", "T1", true, 100, 10);
            createTimetable("SD", "T1", 6, 9, 11);



            createCU("DSS", 3, 1);

            createShift("DSS", "PL5", false, 20, 10);
            createTimetable("DSS", "PL5", 3, 14, 16);


            createShift("DSS", "PL2", false, 20, 10);
            createTimetable("DSS", "PL2", 3, 16, 18);


            createShift("DSS", "PL6", false, 20, 10);
            createTimetable("DSS", "PL6", 4, 9, 11);


            createShift("DSS", "PL1", false, 20, 10);
            createTimetable("DSS", "PL1", 5, 9, 11);


            createShift("DSS", "PL4", false, 20, 10);
            createTimetable("DSS", "PL4", 5, 14, 16);


            createShift("DSS", "PL3", false, 20, 10);
            createTimetable("DSS", "PL3", 5, 16, 18);


            createShift("DSS", "T1", true, 100, 10);
            createTimetable("DSS", "T1", 6, 11, 13);
        
    
            
            for (int i = 0; i < 100; i++) {
                String a = "a" + (80000 + i);
            
                if (i % 10 == 0) {
                    createStudent(a, "pass", true);
                } else {
                    createStudent(a, "pass", false);
                }
                
                createStudentCU(a, "EES");
                createStudentCU(a, "PF");
                createStudentCU(a, "TMD");
                createStudentCU(a, "CALC");
                createStudentCU(a, "ALG");
                createStudentCU(a, "LI1");
            }
            
            for (int i = 0; i < 100; i++) {
                String a = "a" + (70000 + i);
            
                if (i % 10 == 0) {
                    createStudent(a, "pass", true);
                } else {
                    createStudent(a, "pass", false);
                }
                
                createStudentCU(a, "AC");
                createStudentCU(a, "ARQC");
                createStudentCU(a, "ISD");
                createStudentCU(a, "EA");
                createStudentCU(a, "EE");
                createStudentCU(a, "CD");
                
                if (i < 25) {
                    createStudentCU(a, "PF");
                }
            }
            
            
            for (int i = 0; i < 100; i++) {
                String a = "a" + (60000 + i);
            
                if (i % 10 == 0) {
                    createStudent(a, "pass", true);
                } else {
                    createStudent(a, "pass", false);
                }
                
                createStudentCU(a, "DSS");
                createStudentCU(a, "SD");
                createStudentCU(a, "MDIO");
                createStudentCU(a, "MNOL");
                createStudentCU(a, "BD");
                createStudentCU(a, "RC");
                
                if (i < 25) {
                    createStudentCU(a, "PF");
                    createStudentCU(a, "AC");
                }
            }
            
            
            
            
            for (int i = 1; i <= 3; i++) {
                for (int j = 1; j <= 6; j++) {
                    int n = (i * 100) + j;
                    String p = "p" + n;
                    createTeacher(p, "pass");
                }
            }
            
            createTeacherCU("p101", "EES");
            createTeacherCU("p102", "PF");
            createTeacherCU("p103", "TMD");
            createTeacherCU("p104", "CALC");
            createTeacherCU("p105", "ALG");
            createTeacherCU("p106", "LI1");
   
            createTeacherCU("p201", "AC");
            createTeacherCU("p202", "ARQC");
            createTeacherCU("p203", "ISD");
            createTeacherCU("p204", "EA");
            createTeacherCU("p205", "EE");
            createTeacherCU("p206", "CD");
            
            createTeacherCU("p301", "DSS");
            createTeacherCU("p302", "SD");
            createTeacherCU("p303", "MDIO");
            createTeacherCU("p304", "MNOL");
            createTeacherCU("p305", "BD");
            createTeacherCU("p306", "RC");
            
            pw.flush();
            pw.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    
    
    private void createCU(String cu, int year, int semester) {
        StringBuilder sb = new StringBuilder("insert into cu\nvalues ('");
        sb.append(cu);
        sb.append("',");
        sb.append(year);
        sb.append(",");
        sb.append(semester);
        sb.append(");\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createShift(String cu, String shift, boolean teo, 
            int capacity, int numClasses) {
        int t = (teo) ? 1 : 0;
        StringBuilder sb = new StringBuilder("insert into shift\nvalues ('");
        sb.append(cu);
        sb.append("','");
        sb.append(shift);
        sb.append("',");
        sb.append(t);
        sb.append(",");
        sb.append(capacity);
        sb.append(",");
        sb.append(numClasses);
        sb.append(");\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createTimetable(String cu, String shift, int weekDay, 
            int beginningHour, int endingHour) {
        StringBuilder sb = new StringBuilder("insert into timetable\nvalues('");
        sb.append(cu);
        sb.append("','");
        sb.append(shift);
        sb.append("',");
        sb.append(weekDay);
        sb.append(",");
        sb.append(beginningHour);
        sb.append(",");
        sb.append(endingHour);
        sb.append(");\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createTeacher(String user, String pass) {
        StringBuilder sb = new StringBuilder("insert into teacher\nvalues('");
        sb.append(user);
        sb.append("','");
        sb.append(pass);
        sb.append("');\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createStudent(String user, String pass, boolean ws) {
        int w = (ws) ? 1 : 0;
        StringBuilder sb = new StringBuilder("insert into student\nvalues('");
        sb.append(user);
        sb.append("','");
        sb.append(pass);
        sb.append("',");
        sb.append(w);
        sb.append(");\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createTeacherCU(String teacher, String cu) {
        StringBuilder sb = 
                new StringBuilder("insert into teacher_cu\nvalues('");
        sb.append(teacher);
        sb.append("','");
        sb.append(cu);
        sb.append("');\n\n");
        
        pw.write(sb.toString());
    }
    
    
    private void createStudentCU(String student, String cu) {
        StringBuilder sb = 
                new StringBuilder("insert into student_cu\nvalues('");
        sb.append(student);
        sb.append("','");
        sb.append(cu);
        sb.append("');\n\n");
        
        pw.write(sb.toString());
    }
}
