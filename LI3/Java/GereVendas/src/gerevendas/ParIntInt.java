/**
 * Classe auxiliar para guardar dois números inteiros.
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

public class ParIntInt implements Serializable {
    
    // Variáveis de instância
    
    private int primInt;        //Primeiro inteiro a guardar.
    private int segInt;         //Segundo inteiro a guardar.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public ParIntInt() {
        primInt = 0;
        segInt = 0;
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i1 Primeiro valor inteiro a guardar.
     * @param i2 Segundo valor inteiro a guardar.
     */
    public ParIntInt(int i1, int i2) {
        primInt = i1;
        segInt = i2;
    }
    
    
    /**
     * Construtor a partir de outro ParIntInt.
     * 
     * @param pII ParIntInt a guardar.
     */
    public ParIntInt(ParIntInt pII) {
        primInt = pII.getPrimInt();
        segInt = pII.getSegInt();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o primeiro valor inteiro. 
     */
    public int getPrimInt() {
        return primInt;
    }

    
    /**
     * Devolve o segundo valor inteiro. 
     */
    public int getSegInt() {
        return segInt;
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
        
        ParIntInt pII = (ParIntInt) o;
        
        return (primInt == pII.getPrimInt() && segInt == pII.getSegInt());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { primInt, segInt });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParIntInt = ");
        
        sb.append(primInt);
        sb.append(" - ");
        sb.append(segInt);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParIntInt clone() {
        return new ParIntInt(this);
    }
}

