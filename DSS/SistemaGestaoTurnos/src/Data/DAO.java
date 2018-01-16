/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

/**
 *
 * @author rafae
 */
public abstract class DAO {
    
    private Connection connection;
    
    
    public Connection getConnection() {
        return connection;
    }
    
    
    public void clear(String table) {
        try {
            connection = Connector.connect();
            PreparedStatement stm = 
                    connection.prepareStatement("DELETE FROM " + table);
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public void remove(String table, String column, String key) {
        try {
            connection = Connector.connect();
            PreparedStatement stm =
                    connection.prepareStatement("DELETE FROM " + table +
                            "\nWHERE " + column + " = " + key);
            
            stm.executeUpdate();
        } catch (SQLException | ClassNotFoundException e) {
            throw new RuntimeException(e);
        } finally {
            Connector.close(connection);
        }
    }
    
    
    public int size(String table) {
        int i = 0;
        
        try {
            connection = Connector.connect();
            PreparedStatement stm = 
                    connection.prepareStatement("SELECT count(*) FROM " + 
                            table);
            
            ResultSet rs = stm.executeQuery();
            
            if(rs.next()) {
                i = rs.getInt(1);
            }
        }
        catch (ClassNotFoundException | SQLException e) {
            throw new RuntimeException(e);
        }
        finally {
            Connector.close(connection);
        }
        
        return i;
    }
    
    
    @Override 
    public int hashCode() {
        return connection.hashCode();
    }
    
    
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        DAO d = (DAO)o;
        
        return connection.equals(d.getConnection());
    }
}
