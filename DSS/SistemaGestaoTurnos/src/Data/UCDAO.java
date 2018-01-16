/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Turno;
import Business.UC;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 *
 * @author rafae
 */
public class UCDAO extends DAO implements Map<String, UC> {
    
    private static final String TABLE = "cu";
    private static final String CU_ID = "cu_ID";
    private static final String YEAR = "year";
    private static final String SEMESTER = "semester";
  
    private static final String STUDENT_CU_TABLE = "student_cu";
    private static final String STUDENT_ID = "student_ID";
    
    
    private Connection connection;
    
    
    @Override
    public UC get(Object key) {
        UC u = null;
        
        try {
            connection = Connector.connect();

            PreparedStatement stm = 
                    connection.prepareStatement("SELECT * FROM " + TABLE +
                            "\nWHERE " + CU_ID + " = ?");

            stm.setString(1, (String)key);
            
            ResultSet rs = stm.executeQuery();

            if (rs.next()) {
                u = new UC(
                        rs.getString(CU_ID),
                        rs.getInt(YEAR),
                        rs.getInt(SEMESTER)
                );
                
                PreparedStatement aStm = connection.prepareStatement(
                        "SELECT " + STUDENT_ID + " FROM " + STUDENT_CU_TABLE +
                                "\nWHERE " + CU_ID + " = ?"
                );
                
                aStm.setString(1, (String)key);
                
                ResultSet aRs = aStm.executeQuery();
                
                while (aRs.next()) {
                    u.addAluno(aRs.getString(STUDENT_ID));
                }
                
                TurnoDAO tDAO = new TurnoDAO();
                Map<String, Turno> turnos = tDAO.get((String)key);
                
                for (Turno t : turnos.values()) {
                    u.addTurno(t);
                }
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return u;
    }
    
    
    @Override
    public UC put(String key, UC value) {
        UC uc = null;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = 
                    connection.prepareStatement("INSERT INTO " + TABLE +
                            " VALUES (?, ?, ?) " +
                            "ON DUPLICATE KEY UPDATE " + 
                            YEAR + " = ?, " + SEMESTER + " = ?");
            
            stm.setString(1, key);
            stm.setInt(2, value.getAno());
            stm.setInt(3, value.getSemestre());
            stm.setInt(4, value.getAno());
            stm.setInt(5, value.getSemestre());
            stm.executeUpdate();
            
            TurnoDAO tDAO = new TurnoDAO();
            tDAO.add(key, value.getTurnos());
            
            List<String> list = value.getAlunos();
            PreparedStatement aStm =
                    connection.prepareStatement("INSERT INTO " + 
                            STUDENT_CU_TABLE + "\nVALUES (?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " + STUDENT_ID + 
                            " = ?");
            
            for (String a : list) {
                aStm.setString(1, a);
                aStm.setString(2, key);
                aStm.setString(3, a);
                aStm.addBatch();
            }
            
            aStm.executeBatch();
            
            uc = value;
        } catch(ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        } 
        
        return uc;
    }
    
    
    @Override
    public void putAll(Map<? extends String, ? extends UC> map) {
        map.values().forEach((u) -> {
            this.put(u.getNome(), u);
        });
    }
   
    
    @Override
    public UC remove(Object key) {
        UC u = this.get((String)key);
        
        super.remove(TABLE, CU_ID, (String)key);
        
        return u;
    }
    
    
    @Override
    public boolean containsKey(Object key) {
        boolean r = false;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = 
                    connection.prepareStatement("SELECT " + CU_ID +
                            " FROM " + TABLE +
                            "\nWHERE " + CU_ID + " = ?");
            
            stm.setString(1, (String)key);
            
            ResultSet rs = stm.executeQuery();
            r = rs.next();
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return r;
    }
    
    
    @Override 
    public boolean containsValue(Object value) {
        UC u = (UC)value;
        return this.containsKey(u.getNome());
    }
    
        
    @Override
    public Set<Map.Entry<String, UC>> entrySet() {
        throw new NullPointerException();
    }
    
    
    @Override
    public Collection<UC> values() {
        Collection<UC> col = new HashSet<>();
        try {
            connection = Connector.connect();
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + TABLE
            );
            
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                UC u = new UC(
                        rs.getString(CU_ID),
                        rs.getInt(YEAR),
                        rs.getInt(SEMESTER)
                );
                
                PreparedStatement aStm = connection.prepareStatement(
                        "SELECT " + STUDENT_ID + " FROM " + 
                                STUDENT_CU_TABLE + "\nWHERE " +
                                CU_ID + " = ?"
                );
                
                aStm.setString(1, u.getNome());
                
                ResultSet aRs = aStm.executeQuery();
                
                while (aRs.next()) {
                    u.addAluno(aRs.getString(STUDENT_ID));
                }
                
                TurnoDAO tDAO = new TurnoDAO();
                Map<String, Turno> turnos = tDAO.get(u.getNome());
                
                turnos.values().forEach((t) -> {
                    u.addTurno(t);
                });
                
                col.add(u);
            }
            
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        }
        finally {
            Connector.close(connection);
        }
        return col;
    }
    
    
    @Override
    public Set<String> keySet() {
        throw new NullPointerException();
    }
    
    
    @Override
    public int size() {
        return super.size(TABLE);
    }
    
    
    @Override
    public boolean isEmpty() {
        return this.size() == 0;
    }
    
    
    @Override
    public void clear() {
        super.clear(TABLE);
    }
}
