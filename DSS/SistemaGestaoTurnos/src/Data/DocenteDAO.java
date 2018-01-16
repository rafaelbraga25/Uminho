/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Docente;
import Business.Utilizador;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

/**
 *
 * @author rafae
 */
public class DocenteDAO extends UtilizadorDAO 
        implements Map<String, Utilizador>{
    
    private static final String TEACHER_TABLE = "teacher";
    private static final String TEACHER_CU_TABLE = "teacher_cu";
    private static final String TEACHER_ID = "teacher_ID";
    private static final String PASSWORD = "password";
    private static final String CU_ID = "cu_ID";
    
    
    private Connection connection;
    
    
    @Override 
    public Collection<Utilizador> values() {
        Collection<Utilizador> col = new HashSet<>();
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + TEACHER_TABLE
            );
            
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                Docente p = new Docente(
                        rs.getString(TEACHER_ID),
                        rs.getString(PASSWORD)
                );
                
                PreparedStatement uStm = connection.prepareStatement(
                        "SELECT " + CU_ID + " FROM " + TEACHER_CU_TABLE +
                                "\nWHERE " + TEACHER_ID + " = ?"
                );
                uStm.setString(1, p.getUsername());
                ResultSet uRs = uStm.executeQuery();
                
                while (uRs.next()) {
                    p.addUC(uRs.getString(CU_ID));
                }
                
                col.add(p);
            } 
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return col;
    }
    
    
    @Override
    public Utilizador remove(Object key) {
        Utilizador u = this.get((String)key);
       
        super.remove(TEACHER_TABLE, TEACHER_ID, (String)key);
        
        return u;
    }
    
    
    @Override
    public Utilizador put(String key, Utilizador value) {
        Utilizador p = null;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO " + TEACHER_TABLE + 
                            "\nVALUES (?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " +
                            PASSWORD + " = ?"
            );

            stm.setString(1, value.getUsername());
            stm.setString(2, value.getPassword());
            stm.setString(3, value.getPassword());
            stm.executeUpdate();
            
            List<String> list = ((Docente)value).getUCs();
            
            PreparedStatement uStm = connection.prepareStatement(
                    "INSERT INTO " + TEACHER_CU_TABLE + 
                            "\nVALUES (?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " +
                            TEACHER_ID + " = ?"
            );
            
            for (String u : list) {
                uStm.setString(1, key);
                uStm.setString(2, u);
                uStm.setString(3, key);
                uStm.addBatch();
            }
            
            uStm.executeBatch();
            
            p = value;
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return p;
    }


    @Override
    public Utilizador get(Object key) {
        Utilizador u = null;
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + TEACHER_TABLE + 
                            "\nWHERE " + TEACHER_ID + " = ?"
            );
            
            stm.setString(1, (String)key);
            ResultSet rs = stm.executeQuery();
            
            if (rs.next()) {
                Docente p = new Docente(
                        rs.getString(TEACHER_ID),
                        rs.getString(PASSWORD)
                );
                
                PreparedStatement uStm = connection.prepareStatement(
                        "SELECT " + CU_ID + " FROM " + TEACHER_CU_TABLE +
                                "\nWHERE " + TEACHER_ID + " = ?"
                );
                
                uStm.setString(1, (String)key);
                ResultSet uRs = uStm.executeQuery();
                
                while (uRs.next()) {
                    p.addUC(uRs.getString(CU_ID));
                }
                
                u = p;
            }
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
            
        return u;
    }
    
    
    public Utilizador get(String key, String password) {
        Utilizador u = null;
        Utilizador aux = this.get(key);
        
        if (aux != null && aux.getPassword().equals(password)) {
            u = aux;
        }
        
        return u;
    }
    
    
    @Override
    public boolean containsKey(Object key) {
        boolean r = false;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = 
                    connection.prepareStatement("SELECT " + TEACHER_ID + 
                            " FROM " + TEACHER_TABLE + "\nWHERE " +
                            TEACHER_ID + " = ?");
            
            stm.setString(4, (String)key);
            
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
    public void clear() {
        super.clear(TEACHER_TABLE);
    }
 
    
    @Override
    public int size() {
        return super.size(TEACHER_TABLE);
    }
}
