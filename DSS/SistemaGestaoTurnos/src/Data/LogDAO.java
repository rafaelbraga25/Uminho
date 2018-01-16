/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Pair;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;


/**
 *
 * @author rafae
 */
public class LogDAO {
    
    private static final String LOG_TABLE = "log";
    private static final String CU_ID = "cu_ID";
    private static final String SHIFT_ID = "shift_ID";
    private static final String DATE = "date";
    private static final String TEXT = "text";
    
    
    private Connection connection;
    
    
    public void write(String cu, String shift, String log) {
        try {
            connection = Connector.connect();
            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO " + LOG_TABLE + 
                            "\nVALUES (?, ?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " + TEXT + 
                            " = ?"
            );
            
            Date dt = new Date();
            SimpleDateFormat sdf = 
                new java.text.SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

            String currentTime = sdf.format(dt);
            
            stm.setString(1, cu);
            stm.setString(2, shift);
            stm.setString(3, currentTime);
            stm.setString(4, log);
            stm.setString(5, log);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public List<Pair<String, String>> read(String cu, String shift) {
        List<Pair<String, String>> list = new ArrayList<>();
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + LOG_TABLE + 
                            "\nWHERE " + CU_ID + " = ? AND " + SHIFT_ID + 
                            " = ?\nORDER BY " + DATE + " DESC"
            );
            
            stm.setString(1, cu);
            stm.setString(2, shift);
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                String date = rs.getString(DATE);
                String log = rs.getString(TEXT);
               
                list.add(new Pair<>(date, log));
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    
        return list;
    }
}
