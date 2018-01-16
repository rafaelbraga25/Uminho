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
public class DirecaoCurso extends Utilizador {
    
    public DirecaoCurso(String username, String password) {
        super(username, password);
    }
    
    
    public DirecaoCurso(DirecaoCurso d) {
        super(d);
    }
    
    
    @Override
    public DirecaoCurso clone() {
        return new DirecaoCurso(this);
    }
}
