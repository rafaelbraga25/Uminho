package Business;

import java.util.Arrays;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public class Pair<L, R> {
    
    private L left;
    private R right;
    
    
    public Pair(L left, R right) {
        this.left = left;
        this.right = right;
    }
    
    
    public L getLeft() {
        return left;
    }
    
    
    public R getRight() {
        return right;
    }
    
    
    public void setLeft(L left) {
        this.left = left;
    }
    
    
    public void setRight(R right) {
        this.right = right;
    }
    
    
    @Override
    public int hashCode() { 
        return Arrays.hashCode(new Object[] {
            left, 
            right
        });
    }

    
    @Override
    public boolean equals(Object o) {
        if (o == this) {
            return true;
        }
        
        if (o == null || (o.getClass() != this.getClass())) {
            return false;
        }
      
        Pair p = (Pair)o;
        
        return left.equals(p.getLeft()) && right.equals(p.getRight());
    }
}
