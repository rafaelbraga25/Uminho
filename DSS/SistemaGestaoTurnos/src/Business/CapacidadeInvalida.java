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
public class CapacidadeInvalida extends Exception {
    
    public CapacidadeInvalida() {
        super();
    }
    
    public CapacidadeInvalida(String message) {
        super(message);
    }
    
    public CapacidadeInvalida(Exception e) {
        super(e);
    }
}
