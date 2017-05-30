/**
 * Classe auxiliar para guardar dois números inteiros e um real.
 * É utilizada por outras classes de maneira a ser possível devolver mais do 
 * que um parâmetro.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import java.util.Arrays;
import java.io.Serializable;


public class TuploIntDouble implements Serializable {
    
    // Variáveis de instância
    
    private int primInt;            //Primeiro inteiro a guardar
    private int segInt;             //Segundo inteiro a guardar
    private double primDouble;      //Real a guardar
    
    
    // Construtores

    /**
     * Construtor vazio.
     */
    public TuploIntDouble() {
        primInt = 0;
        segInt = 0;
        primDouble = 0;
    }
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i1 Valor a guardar no primeiro inteiro.
     * @param i2 Valor a guardar no segundo inteiro.
     * @param d  Valor a guardar no real.
     */
    public TuploIntDouble(int i1, int i2, double d) {
        primInt = i1;
        segInt = i2;
        primDouble = d;
    }
    
    
    /**
     * Construtor a partir de outro TuploIntDouble.
     * 
     * @param t TuploIntDouble a guardar.
     */
    public TuploIntDouble(TuploIntDouble t) {
        primInt = t.getPrimInt();
        segInt = t.getSegInt();
        primDouble = t.getPrimDouble();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o primeiro inteiro.
     */
    public int getPrimInt() {
        return primInt;
    }

    /**
     * Devolve o segundo inteiro.
     */
    public int getSegInt() {
        return segInt;
    }

    
    /**
     * Devolve o real.
     */
    public double getPrimDouble() {
        return primDouble;
    }
    
    
    /**
     * Adiciona um valor ao primeiro inteiro.
     * 
     * @param i Valor a adicionar
     * @return void
     */
    public void addPrimInt(int i) {
        primInt += i;
    }
    
    
    /**
     * Adiciona um valor ao segundo inteiro.
     * 
     * @param i Valor a adicionar
     * @return void
     */
    public void addSegInt(int i) {
        segInt += i;
    }
    
    
    /**
     * Adiciona um valor ao real.
     * 
     * @param d Valor a adicionar
     * @return void
     */
    public void addPrimDouble(double d) {
        primDouble += d;
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
        
        TuploIntDouble t = (TuploIntDouble) o;
        
        return (primInt == t.getPrimInt() && segInt == t.getSegInt() &&
                primDouble == t.getPrimDouble());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { primInt, segInt, primDouble });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("TuploIntDouble = ");
        
        sb.append(primInt);
        sb.append(" - ");
        sb.append(segInt);
        sb.append(" - ");
        sb.append(primDouble);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public TuploIntDouble clone() {
        return new TuploIntDouble(this);
    }
}
