/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Business;

/**
 *
 * @author rafae
 */
public class UtilizadorInvalido extends Exception {
    
    public UtilizadorInvalido() {
        super();
    }
    
    
    public UtilizadorInvalido(String message) {
        super(message);
    }
    
    
    public UtilizadorInvalido(Exception e) {
        super(e);
    }
}
