/**
 * Classe auxiliar para guardar uma String e um número real.
 * É utilizada por outras classes de maneira a ser possível devolver mais do 
 * que um parâmetro.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */


package gerevendas;

import java.io.Serializable;
import java.util.Arrays;

public class ParStringDouble implements Serializable {
	
    // Variáveis de instância
	
    private String string;      //String a guardar
    private double real;        //Real a guardar
	
	
    // Construtores
	
        
    /**
     * Construtor com parâmetros.
     * 
     * @param string String a guardar.
     * @param real Número real a guardar.
     */
    public ParStringDouble(String string, double real) {
	this.string = string;
	this.real = real;
    }
    
    
    /**
     * Construtor a partir de outro ParStringDouble.
     * 
     * @param p ParStringDouble a guardar.
     */
    public ParStringDouble(ParStringDouble p) {
	this.string = p.getString();
	this.real = p.getReal();
    }
	
	
    // Métodos de instância
    
    /**
     * Devolve a String. 
     */
    public String getString() { 
	return string;
    }
    
    
    /**
     * Devolve o valor real. 
     */
    public double getReal() {
	return real;
    }
	
	
    // Métodos complementares comuns
    
    /**
     * Compara um objeto com um elemento desta classe.
     * 
     * @param o Objeto a comparar.
     * @return true caso sejam iguais
     *         false caso contrário
     */
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (o.getClass() != this.getClass())) {
            return false;
        }
        
        ParStringDouble p = (ParStringDouble) o;
        
        return (string.equals(p.getString()) && real == p.getReal());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { string, real } );
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParStringDouble: ");
        
        sb.append(string);
        sb.append("-");
        sb.append(real);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParStringDouble clone() {
        return new ParStringDouble(this);
    }
}

