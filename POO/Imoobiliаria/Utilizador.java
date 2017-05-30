
/**
 * Classe que define um utilizador.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import java.util.GregorianCalendar;
import java.util.Arrays;
import java.text.SimpleDateFormat;
import java.io.Serializable;

public class Utilizador implements Serializable
{
    // Variáveis de instância
    
    private String email;
    private String nome;
    private String password;
    private String morada;
    private GregorianCalendar dataNascimento;
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param email          Email do utilizador.
     * @param nome           Nome do utilizador.
     * @param password       Password.
     * @param morada         Morada do utilizador.
     * @param dataNascimento Data de nascimento do utilizador.
     */   
    public Utilizador(String email, String nome, String password, String morada, 
                      GregorianCalendar dataNascimento) {
        this.email = email;
        this.nome = nome;
        this.password = password;
        this.morada = morada;
        this.dataNascimento = dataNascimento;
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param u Um utilizador.
     */      
    public Utilizador(Utilizador u) {
        email = u.getEmail();
        nome = u.getNome();
        password = u.getPassword();
        morada = u.getMorada();
        dataNascimento = u.getDataNascimento();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "email" de um utilizador.
     */
    public String getEmail() { 
        return email; 
    }
    
    
    /**
     * @return Devolve o campo "nome" de um utilizador.
     */    
    public String getNome() { 
        return nome; 
    }
    
    
    /**
     * @return Devolve o campo "password" de um utilizador.
     */    
    public String getPassword() { 
        return password; 
    }
    
    
    /**
     * @return Devolve o campo "morada" de um utilizador.
     */    
    public String getMorada() { 
        return morada; 
    }
    
    
    /**
     * @return Devolve o campo "dataNascimento" de um utilizador.
     */    
    public GregorianCalendar getDataNascimento() { 
        return dataNascimento; 
    }
    
    
    /**
     * Altera o valor do campo "email".
     */    
    public void setEmail(String email) { 
        this.email = email; 
    }
    
    
    /**
     * Altera o valor do campo "nome".
     */    
    public void setNome(String nome) { 
        this.nome = nome; 
    }
    
    
    /**
     * Altera o valor do campo "password".
     */    
    public void setPassword(String password) { 
        this.password = password; 
    }
    
    
    /**
     * Altera o valor do campo "morada".
     */    
    public void setMorada(String morada) { 
        this.morada = morada; 
    }
    
    
    /**
     * Altera o valor do campo "dataNascimento".
     */    
    public void setDataNascimento(GregorianCalendar dataNascimento) {
        this.dataNascimento = dataNascimento; 
    }
    
    
    // Métodos complementares comuns
    /**
     * Verifica se um objeto é igual a uma instância da classe Utilizador.
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
        
        Utilizador u = (Utilizador) o;
        
        return (email.equals(u.getEmail()) && nome.equals(u.getNome()) && 
                password.equals(u.getPassword()) && morada.equals(u.getMorada()) &&
                dataNascimento.equals(u.getDataNascimento()));
    }
    
    
    /**
     * @return Devolve um código de hash relativo a um utilizador.
     */    
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { email, nome, password, morada, dataNascimento });
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Utilizador.
     */     
    public String toString() {
        StringBuilder sb = new StringBuilder("Utilizador = ");
        SimpleDateFormat f = new SimpleDateFormat("dd-MM-yyyy");
        
        f.setTimeZone(dataNascimento.getTimeZone());
        
        sb.append(email);
        sb.append(" ");
        sb.append(nome);
        sb.append(" ");
        sb.append(password);
        sb.append(" ");
        sb.append(morada);
        sb.append(" ");
        sb.append(f.format(dataNascimento.getTime()));
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um utilizador.
     */     
    public Utilizador clone() { 
        return new Utilizador(this); 
    }
}
