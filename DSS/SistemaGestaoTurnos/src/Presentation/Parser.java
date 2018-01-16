/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Presentation;
import Business.BusinessFacade;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import org.json.simple.JSONObject;
import org.json.simple.JSONArray;
import org.json.simple.parser.ParseException;
import org.json.simple.parser.JSONParser;

/**
 *
 * @author rafae
 */
public class Parser {
    
    private static final String UCS = "cus";
    private static final String NAME = "name";
    private static final String YEAR = "year";
    private static final String SEMESTER = "semester";
    private static final String SHIFTS = "shifts";
    private static final String SCHEDULES = "schedules";
    private static final String CLASSES = "classes";
    private static final String TEO = "teo";
    private static final String CAPACITY = "capacity";
    private static final String WEEK_DAY = "weekDay";
    private static final String B_HOUR = "bHour";
    private static final String E_HOUR = "eHour";
    private static final String TEACHERS = "teachers";
    private static final String UC_NAMES = "cuNames";
    private static final String USERNAME = "username";
    private static final String PASSWORD = "password";
    private static final String WS = "ws";
    private static final String STUDENTS = "students";
    
    
    private final BusinessFacade bFacade;
    private final File file;
    private boolean parseOK;
    
    
    public Parser(BusinessFacade bFacade, File file) {
        this.bFacade = bFacade;
        this.file = file;
        parseOK = true;
    }
    
    
    private void getUCs(JSONObject obj) {
        JSONArray ucArray = (JSONArray)obj.get(UCS);
       
        try {
            for (int i = 0; i < ucArray.size(); i++) {
                JSONObject uc = (JSONObject)ucArray.get(i);
                String ucName = (String)uc.get(NAME);
                bFacade.addUC(ucName, 
                        Integer.parseInt((String)uc.get(YEAR)),
                        Integer.parseInt((String)uc.get(SEMESTER)));
                
                JSONArray sArray = (JSONArray)uc.get(SHIFTS);
                
                for (int j = 0; j < sArray.size(); j++) {
                    JSONObject s = (JSONObject)sArray.get(j);
                    String tName = (String)s.get(NAME);
                    int teo = Integer.parseInt((String)s.get(TEO));
                    bFacade.addTurno(ucName, tName, teo > 0, 
                            Integer.parseInt((String)s.get(CAPACITY)), 
                            Integer.parseInt((String)s.get(CLASSES)));
                    
                    JSONArray hArray = (JSONArray)s.get(SCHEDULES);
                            
                    for (int w = 0; w < hArray.size(); w++) {
                        JSONObject h = (JSONObject)hArray.get(w);
                        bFacade.addHorario(ucName, tName, 
                                Integer.parseInt((String)h.get(WEEK_DAY)), 
                                Integer.parseInt((String)h.get(B_HOUR)), 
                                Integer.parseInt((String)h.get(E_HOUR)));
                    }        
                }
            }
        } catch (Exception e) {
            parseOK = false;
            throw new RuntimeException(e);
        }
    }
   
    
    private void getTeachers(JSONObject obj) {
        JSONArray tArray = (JSONArray)obj.get(TEACHERS);
       
        try {
            for (int i = 0; i < tArray.size(); i++) {
                JSONObject t = (JSONObject)tArray.get(i);
                List<String> names = new ArrayList<>();
                
                JSONArray nArray = (JSONArray)t.get(UC_NAMES);
                
                for (int j = 0; j < nArray.size(); j++) {
                    JSONObject n = (JSONObject)nArray.get(j);
                    names.add((String)n.get(NAME));
                }
                
                bFacade.addProfessor((String)t.get(USERNAME), 
                        (String)t.get(PASSWORD), names);
            }
        } catch (Exception e) {
            parseOK = false;
            throw new RuntimeException(e);
        }
    }
    
    
    private void getStudents(JSONObject obj) {
        JSONArray sArray = (JSONArray)obj.get(STUDENTS);
       
        try {
            for (int i = 0; i < sArray.size(); i++) {
                JSONObject t = (JSONObject)sArray.get(i);
                int ws = Integer.parseInt((String)t.get(WS));
               
                
                bFacade.addAluno((String)t.get(USERNAME), 
                        (String)t.get(PASSWORD), (ws > 0));
            }
        } catch (Exception e) {
            parseOK = false;
            throw new RuntimeException(e);
        }
    }
    
    
    public boolean parse() { 
        JSONParser parser = new JSONParser();

        try {
            Object obj = parser.parse(new FileReader(file));
            JSONObject jsonobj = (JSONObject) obj;
            
            getUCs(jsonobj);
            getTeachers(jsonobj);
            getStudents(jsonobj);
        } catch (IOException | ParseException e) {
            throw new RuntimeException(e);
        }

        return parseOK;
    }
}
