/**
 * Classe auxiliar para guardar um número inteiro e um real.
 * É utilizada por outras classes de maneira a ser possível devolver mais do 
 * que um parâmetro.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendas;

import java.util.Arrays;
import java.io.Serializable;

public class ParIntDouble implements Serializable {
    
    // Variáveis de instância
    
    private int inteiro;        //Inteiro a guardar.
    private double real;        //Real a guardar.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public ParIntDouble() {
        inteiro = 0;
        real = 0;
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i Valor inteiro a guardar.
     * @param d Valor real a guardar.
     */
    public ParIntDouble(int i, double d) {
        inteiro = i;
        real = d;
    }
    
    
    /**
     * Construtor a partir de outro ParIntDouble.
     * 
     * @param t ParIntDouble a guardar.
     */
    public ParIntDouble(ParIntDouble t) {
        inteiro = t.getInteiro();
        real = t.getReal();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o valor inteiro. 
     */
    public int getInteiro() {
        return inteiro;
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
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        ParIntDouble t = (ParIntDouble) o;
        
        return (inteiro == t.getInteiro() && real == t.getReal());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { inteiro, real });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParIntDouble = ");
        
        sb.append(inteiro);
        sb.append(" - ");
        sb.append(real);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParIntDouble clone() {
        return new ParIntDouble(this);
    }
}

