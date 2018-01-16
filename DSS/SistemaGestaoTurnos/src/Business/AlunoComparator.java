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
public class AlunoComparator implements Comparator<String> {
    
    @Override
    public int compare(String a1, String a2) {
        if (a1.compareTo(a2) < 0) {
            return 1;
        }
        
        if (a1.compareTo(a2) > 0) {
            return -1;
        }
        
        return 0;
    }
}
