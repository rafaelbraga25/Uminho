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
public abstract class Utilizador {
    
    private final String username;
    private String password;
    
    
    public Utilizador(String nomeUtilizador, String password) {
        this.username = nomeUtilizador;
        this.password = password;
    }
    
    
    public Utilizador(Utilizador u) {
        username = u.getUsername();
        password = u.getPassword();
    }
    
    
    public String getUsername() {
        return username;
    }
    
    
    public String getPassword() {
        return password;
    }
    
    
    public void setPassword(String password) {
        this.password = password;
    }
    
    
    @Override
    public int hashCode() {
        return Arrays.hashCode(new Object[] {
            username,
            password
        });
    }
    
    
    @Override
    public abstract Utilizador clone();
}
