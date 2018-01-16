package Business;


import java.util.Comparator;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public class UCComparator implements Comparator<UC> {
    
    @Override
    public int compare(UC u1, UC u2) {
        if (u1.getAno() > u2.getAno()) {
            return -1;
        }
        
        if (u1.getAno() < u2.getAno()) {
            return 1;
        }
        
        if (u1.getTurnosPraticos().size() > u2.getTurnosPraticos().size()) {
            return 1;
        }
        
        if (u1.getTurnosPraticos().size() < u2.getTurnosPraticos().size()) {
            return -1;
        }
        
        return 0;
    }
}
