/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Aluno;
import Business.Utilizador;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;

/**
 *
 * @author rafae
 */
public class AlunoDAO extends UtilizadorDAO implements Map<String, Utilizador> {
    
    
    private static final String CU_ID = "cu_ID";
    private static final String STUDENT_TABLE = "student";
    private static final String STUDENT_SHIFT_TABLE = "student_shift";
    private static final String REQUEST_TABLE = "request";
    private static final String STUDENT_ID = "student_ID";
    private static final String PASSWORD = "password";
    private static final String WS = "ws";
    private static final String SHIFT_ID = "shift_ID";
            
    
    private Connection connection;
    
    
    @Override 
    public Collection<Utilizador> values() {
        Collection<Utilizador> col = new HashSet<>();
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + STUDENT_TABLE
            );
            
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                Aluno a = new Aluno(
                        rs.getString(STUDENT_ID),
                        rs.getString(PASSWORD),
                        rs.getBoolean(WS)
                );
                
                PreparedStatement sStm = connection.prepareStatement(
                            "SELECT " + CU_ID + ", " + SHIFT_ID + 
                                    " FROM " + STUDENT_SHIFT_TABLE + 
                                    "\nWHERE " + STUDENT_ID + " = ?"
                );
                
                sStm.setString(1, a.getUsername());
                ResultSet sRs = sStm.executeQuery();
                
                while (sRs.next()) {
                    a.addTurno(sRs.getString(CU_ID), sRs.getString(SHIFT_ID));
                }
                
                PreparedStatement pStm = connection.prepareStatement(
                            "SELECT " + CU_ID + ", " + SHIFT_ID + " FROM " + 
                                    REQUEST_TABLE + "\nWHERE " + STUDENT_ID +
                                    " = ?"
                );
                
                pStm.setString(1, a.getUsername());
                ResultSet pRs = pStm.executeQuery();
                
                while (pRs.next()) {
                    a.addPedido(pRs.getString(CU_ID), pRs.getString(SHIFT_ID));
                }
                
                col.add(a);
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
        
        super.remove(STUDENT_TABLE, STUDENT_ID, (String)key);
        
        return u;
    }
    
    
    @Override
    public Utilizador put(String key, Utilizador value) {
        Utilizador a = null;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO " + STUDENT_TABLE + 
                            "\nVALUES (?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " + PASSWORD + 
                            " = ?," + WS +
                            " = ?"
            );
            
            stm.setString(1, key);
            stm.setString(2, value.getPassword());
            stm.setBoolean(3, ((Aluno)value).isTE());
            stm.setString(4, value.getPassword());
            stm.setBoolean(5, ((Aluno)value).isTE());
            stm.executeUpdate();
            
            a = value;
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return a;
    }
        
    
    @Override
    public Utilizador get(Object key) {
        Utilizador u = null;
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT * FROM " + STUDENT_TABLE + 
                            "\nWHERE " + STUDENT_ID + " = ?"
            );
            
            stm.setString(1, (String)key);
            ResultSet rs = stm.executeQuery();
            
            if (rs.next()) {
                Aluno a = new Aluno(
                        rs.getString(STUDENT_ID),
                        rs.getString(PASSWORD),
                        rs.getBoolean(WS)
                );
                
                PreparedStatement sStm = connection.prepareStatement(
                            "SELECT " + CU_ID + ", " + SHIFT_ID + " FROM " + 
                                    STUDENT_SHIFT_TABLE + 
                                    "\nWHERE " + STUDENT_ID + " = ?"
                );
                
                sStm.setString(1, (String)key);
                ResultSet sRs = sStm.executeQuery();
                
                while (sRs.next()) {
                    a.addTurno(sRs.getString(CU_ID), sRs.getString(SHIFT_ID));
                }
                
                PreparedStatement pStm = connection.prepareStatement(
                            "SELECT " + CU_ID + ", " + SHIFT_ID + " FROM " + 
                                    REQUEST_TABLE + "\nWHERE " +
                                    STUDENT_ID + " = ?"
                );
                
                pStm.setString(1, (String)key);
                ResultSet pRs = pStm.executeQuery();
                
                while (pRs.next()) {
                    a.addPedido(pRs.getString(CU_ID), pRs.getString(SHIFT_ID));
                }
                
                u = a;
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
                    connection.prepareStatement("SELECT " + STUDENT_ID + 
                            " FROM " + STUDENT_TABLE + "\nWHERE " +
                            STUDENT_ID + " = ?");
            
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
    public void clear() {
        super.clear(STUDENT_TABLE);
    }
    
    
    @Override
    public int size() {
        return super.size(STUDENT_TABLE);
    }
}
