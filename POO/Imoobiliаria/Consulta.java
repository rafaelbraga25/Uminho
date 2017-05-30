
/**
 * Classe que define uma consulta.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import java.text.SimpleDateFormat;
import java.util.GregorianCalendar;
import java.util.Arrays;
import java.io.Serializable;

public class Consulta implements Serializable
{
    // Variáveis de instância
    
    private String email;           // Email do utilizador que realizou a consulta.
    private GregorianCalendar data; // Data em que foi realizada a consulta.    
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param email Email do utilizador que realizou a consulta.
     * @param nome  Nome do utilizador que realizou a consulta.
     */     
    public Consulta(String email, GregorianCalendar data) {
        this.email = email;
        this.data = data;
    }
    
    
    /**
     * Construtor vazio.
     */      
    public Consulta() { 
        this("", new GregorianCalendar()); 
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param c Uma consulta.
     */      
    public Consulta(Consulta c) {
        email = c.getEmail();
        data = c.getData();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "email" consulta.
     */    
    public String getEmail() { 
        return email; 
    }
    
    
    /**
     * @return Devolve o campo "data" da consulta.
     */      
    public GregorianCalendar getData() { 
        return data; 
    }
    
    
    /**
     * Altera o valor do campo "email".
     */     
    public void setEmail(String email) { 
        this.email = email; 
    }
   
    
    /**
     * Altera o valor do campo "data".
     */     
    public void setData(GregorianCalendar data) {
        this.data = data; 
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Consulta.
     * 
     * @param o Objeto ao qual se quer efetuar a comparação.
     * @return Devolve true caso o objeto seja igual ou false, caso contrário.
     */      
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        Consulta c = (Consulta) o;
        
        return (email.equals(c.getEmail()) && data.equals(c.getData()));
    }
    
    
    /**
     * @return Devolve um código de hash relativo a uma consulta.
     */    
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { email, data }); 
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Consulta.
     */     
    public String toString() {
        StringBuilder sb = new StringBuilder("Consulta = ");
        SimpleDateFormat f = new SimpleDateFormat("dd-MM-yyyy HH:mm");
        
        f.setTimeZone(data.getTimeZone());
        
        sb.append(email);
        sb.append(" ");
        sb.append(f.format(data.getTime()));
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de uma consulta.
     */     
    public Consulta clone() { 
        return new Consulta(this); 
    }
}
