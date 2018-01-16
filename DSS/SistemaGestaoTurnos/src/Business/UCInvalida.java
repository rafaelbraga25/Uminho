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
public class UCInvalida extends Exception {
    
    public UCInvalida() {
        super();
    }
    
    
    public UCInvalida(String message) {
        super(message);
    }
    
    
    public UCInvalida(Exception e) {
        super(e);
    }
}
