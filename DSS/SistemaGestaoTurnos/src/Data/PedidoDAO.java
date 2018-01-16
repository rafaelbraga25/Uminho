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
import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author rafae
 */
class PedidoDAO extends DAO {
    
    private static final String TABLE = "request";
    private static final String CU_ID = "cu_ID";
    private static final String SHIFT_ID = "shift_ID";
    private static final String STUDENT_ID = "student_ID";
    private static final String WS = "ws";
    private static final String IDX = "idx";
    
    
    private Connection connection;
    
    
    public void 
        add(String uc, String turno, List<Pair<String, Boolean>> list) {
        for (int i = 0; i < list.size(); i++) {
            Pair<String, Boolean> p = list.get(i);
            this.add(uc, turno, p.getLeft(), p.getRight(), i);
        }
    }
        
    
    private void 
        add(String uc, String turno, String aluno, boolean TE, int idx) {
        try {
            connection = Connector.connect();
             
            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO " + TABLE + "\nVALUES (?, ?, ?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " +
                            WS + " = ?," + IDX + " = ?" 
            );
            
            stm.setString(1, aluno);
            stm.setString(2, uc);
            stm.setString(3, turno);
            stm.setBoolean(4, TE);
            stm.setInt(5, idx);
            stm.setBoolean(6, TE);
            stm.setInt(7, idx);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
        
        
    public List<Pair<String, Boolean>> get(String uc, String turno) {
        List<Pair<String, Boolean>> list = new ArrayList<>();
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "SELECT " + STUDENT_ID + ", " + WS +  " FROM " + TABLE + 
                            "\nWHERE " + CU_ID + " = ? AND " +
                            SHIFT_ID + " = ?\nORDER BY " + IDX
            );
            
            stm.setString(1, uc);
            stm.setString(2, turno);
            
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                list.add(new Pair<>(
                        rs.getString(STUDENT_ID),
                        rs.getBoolean(WS)
                ));
            }
        } catch(SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return list;
    }
    
    
    @Override
    public void remove(String uc, String turno, String aluno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "DELETE FROM " + TABLE + "\nWHERE " + CU_ID + 
                            " = ? AND " + SHIFT_ID + " = ? AND " +
                            STUDENT_ID + " = ?"
            );
            
            stm.setString(1, uc);
            stm.setString(2, turno);
            stm.setString(3, aluno);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public void remove(String uc, String aluno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "DELETE FROM " + TABLE + "\nWHERE " + CU_ID + 
                            " = ? AND " + STUDENT_ID + " = ?"
            );
            
            stm.setString(1, uc);
            stm.setString(2, aluno);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
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
