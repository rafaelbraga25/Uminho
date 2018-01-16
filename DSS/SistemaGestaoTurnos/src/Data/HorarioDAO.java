/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Horario;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author rafae
 */
public class HorarioDAO extends DAO {
    
    private static final String TABLE = "timetable";
    private static final String WEEK_DAY = "weekDay";
    private static final String BEGINNING_HOUR = "beginningHour";
    private static final String ENDING_HOUR = "endingHour";
    private static final String CU_ID = "cu_ID";
    private static final String SHIFT_ID = "shift_ID";
    
    
    private Connection connection;
    
    
    public void add(String uc, String turno, List<Horario> list) {
        list.forEach((h) -> {
            this.add(uc, turno, h);
        });
    }
    
    
    public void add(String uc, String turno, Horario h) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = 
                    connection.prepareStatement("INSERT INTO " + TABLE + 
                            "\nVALUES (?, ?, ?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " + CU_ID + 
                            " = ?");

            
            stm.setString(1, uc);
            stm.setString(2, turno);
            stm.setInt(3, h.getDiaSemana());
            stm.setInt(4, h.getHoraInicio());
            stm.setInt(5, h.getHoraFim());
            stm.setString(6, uc);
            stm.executeUpdate();
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public void remove(String uc, String turno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "DELETE FROM " + TABLE + "\nWHERE " + CU_ID + 
                            " = ? AND " + SHIFT_ID + " = ?"
            );
            
            stm.setString(1, uc);
            stm.setString(2, turno);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public List<Horario> get(String uc, String turno) {
        List<Horario> list = null;
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm =
                    connection.prepareStatement("SELECT * FROM " + TABLE + 
                            "\nWHERE " + CU_ID + " = ? AND " + 
                            SHIFT_ID + " = ?");
            
            stm.setString(1, uc);
            stm.setString(2, turno);
            
            ResultSet rs = stm.executeQuery();
            list = new ArrayList<>();
            
            while (rs.next()) {
                list.add(new Horario(
                        rs.getInt(WEEK_DAY),
                        rs.getInt(BEGINNING_HOUR),
                        rs.getInt(ENDING_HOUR)
                ));
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return list;
    }
    
    
    public void clear() {
        super.clear(TABLE);
    }
    
    
    public boolean isEmpty() {
        return this.size() == 0;
    }
    
    
    public int size() {
        return super.size(TABLE);
    }
}
