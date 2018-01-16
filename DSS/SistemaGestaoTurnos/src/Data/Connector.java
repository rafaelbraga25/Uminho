package Data;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;


public class Connector {   
    
    private static final String URL = "localhost";
    private static final String DB = "scdb";
    private static final String USERNAME = "root"; 
    private static final String PASSWORD = "pass"; 
    
    /**
     * Estabelece ligação à base de dados
     * @return
     * @throws SQLException
     * @throws ClassNotFoundException 
     */
    public static Connection connect() throws SQLException, ClassNotFoundException {
        Class.forName("com.mysql.jdbc.Driver");
        //cliente deve fechar conexão!
        return DriverManager.getConnection("jdbc:mysql://"+URL+"/"+DB+"?user="+USERNAME+"&password="+PASSWORD);    
    }
    
    /**
     * Fecha a ligação à base de dados, se aberta.
     * @param c 
     */
    public static void close(Connection c) {
        try {
            if(c != null && !c.isClosed()) {
                c.close();
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
}
