/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Horario;
import Business.Pair;
import Business.Turno;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author rafae
 */
public class TurnoDAO extends DAO {
    private static final String TABLE = "shift";
    private static final String CU_ID = "cu_ID";
    private static final String SHIFT_ID = "shift_ID";
    private static final String TEO = "teo";
    private static final String CAPACITY = "capacity";
    private static final String NUM_CLASSES = "numClasses";
    
    private static final String STUDENT_SHIFT_TABLE = "student_shift";
    private static final String STUDENT_ID = "student_ID";
    private static final String MISSED_CLASSES = "missedClasses";
    
    
    private Connection connection;
    
    
    public void add(String uc, Map<String, Turno> map) {
        map.values().forEach((t) -> {
            this.add(uc, t);
        });
    }
    
    
    public void add(String uc, Turno t) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = 
                    connection.prepareStatement("INSERT INTO " + TABLE + 
                            "\nVALUES (?, ?, ?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " +
                            TEO + " = ?, " + 
                            CAPACITY + " = ?, " + NUM_CLASSES + " = ?");

            stm.setString(1, uc);
            stm.setString(2, t.getNomeTurno());
            stm.setBoolean(3, t.isTeorico());
            stm.setInt(4, t.getCapacidade());
            stm.setInt(5, t.getNumAulas());
            stm.setBoolean(6, t.isTeorico());
            stm.setInt(7, t.getCapacidade());
            stm.setInt(8, t.getNumAulas());
            stm.executeUpdate();
            
            List<Pair<String, Integer>> list = t.getAlunos();
            
            PreparedStatement aStm = connection.prepareStatement(
                    "INSERT INTO " + STUDENT_SHIFT_TABLE + 
                            "\nVALUES (?, ?, ?, ?)\n" +
                            "ON DUPLICATE KEY UPDATE " + MISSED_CLASSES + 
                            " = ?"
            );
            
            for (Pair<String, Integer> p : list) {
                aStm.setString(1, p.getLeft());
                aStm.setString(2, uc);
                aStm.setString(3, t.getNomeTurno());
                aStm.setInt(4, p.getRight());
                aStm.setInt(5, p.getRight());
                aStm.addBatch();
            }
            
            aStm.executeBatch();
            
            HorarioDAO horarioDAO = new HorarioDAO();
            PedidoDAO pedidoDAO = new PedidoDAO();
            
            horarioDAO.add(uc, t.getNomeTurno(), t.getHorarios());
            pedidoDAO.add(uc, t.getNomeTurno(), t.getPedidos());
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public void addAluno(String uc, String turno, String aluno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "INSERT INTO " + STUDENT_SHIFT_TABLE + 
                            "\nVALUES (?, ?, ?, ?)" + 
                                    "ON DUPLICATE KEY UPDATE " + 
                            MISSED_CLASSES + " = ?"
            );
            
            stm.setString(1, aluno);
            stm.setString(2, uc);
            stm.setString(3, turno);
            stm.setInt(4, 0);
            stm.setInt(5, 0);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public void addFalta(String uc, String turno, String aluno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "UPDATE " + STUDENT_SHIFT_TABLE +
                            "\nSET " + MISSED_CLASSES + " = " + 
                            MISSED_CLASSES + " + 1\nWHERE " + STUDENT_ID + 
                            " = ? AND " + CU_ID + " = ? AND " + SHIFT_ID + 
                            " = ?"
            );
            
            stm.setString(1, aluno);
            stm.setString(2, uc);
            stm.setString(3, turno);
            stm.executeUpdate();
            
        } catch (SQLException | ClassNotFoundException e) {
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
  
    
    public void removeAluno(String uc, String turno, String aluno) {
        try {
            connection = Connector.connect();
            
            PreparedStatement stm = connection.prepareStatement(
                    "DELETE FROM " + STUDENT_SHIFT_TABLE + "\nWHERE " + CU_ID + 
                            " = ? AND " + SHIFT_ID + " = ? AND " + STUDENT_ID +
                            " = ?"
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
    
    
    public Map<String, Turno> get(String uc) {
        Map<String, Turno> map = new HashMap<>();
        
        try {
            connection = Connector.connect();
            
            PreparedStatement stm =
                    connection.prepareStatement("SELECT * FROM " + TABLE + 
                            "\nWHERE " + CU_ID + " = ?");
            
            stm.setString(1, uc);
            
            ResultSet rs = stm.executeQuery();
            
            while (rs.next()) {
                Turno t = new Turno(
                        rs.getString(SHIFT_ID),
                        rs.getBoolean(TEO),
                        rs.getInt(CAPACITY),
                        rs.getInt(NUM_CLASSES)
                );
                
                PreparedStatement aStm = connection.prepareStatement(
                        "SELECT " + STUDENT_ID + ", " + MISSED_CLASSES + 
                                " FROM " + STUDENT_SHIFT_TABLE + "\nWHERE " +
                                CU_ID + " = ? AND " + SHIFT_ID + " = ?"
                );
                
                aStm.setString(1, uc);
                aStm.setString(2, t.getNomeTurno());
                
                ResultSet aRs = aStm.executeQuery();
                
                while (aRs.next()) {
                    t.addAluno(aRs.getString(STUDENT_ID), 
                            aRs.getInt(MISSED_CLASSES));
                }
                
                HorarioDAO hDAO = new HorarioDAO();
                PedidoDAO pDAO = new PedidoDAO();
                List<Horario> horarios = hDAO.get(uc, t.getNomeTurno());
                List<Pair<String, Boolean>> pedidos = 
                        pDAO.get(uc, t.getNomeTurno());
                
                horarios.forEach((h) -> {
                    t.addHorario(h);
                });
                
                pedidos.forEach((p) -> {
                    if (p.getRight()) {
                        t.addPedidoAlunoTE(p.getLeft());
                    } else {
                        t.addPedidoAluno(p.getLeft());
                    }
                });
                
                map.put(t.getNomeTurno(), t);
            }
        } catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
        
        return map;
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
