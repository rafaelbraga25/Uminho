/**
 * Classe auxiliar para guardar um número inteiro, um número real e um HashSet
 * de Strings.
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
import java.util.Set;
import java.util.HashSet;

public class TuploIntDoubleSet  implements Serializable {
    
    // Variáveis de instância
    
    private int inteiro;     //Inteiro a guardar
    private double real;     //Real a guardar
    private Set<String> set; //Set a guardar
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public TuploIntDoubleSet() {
        this(0, 0, new HashSet<>());
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i Valor inteiro a guardar.
     * @param d Valor real a guardar.
     * @param s Set a guardar.
     */
    public TuploIntDoubleSet(int i, double d, Set<String> s) {
        inteiro = i;
        real = d;
        set = s;
    }
    
    
    /**
     * Construtor a partir de outro TuploIntDoubleSet.
     * 
     * @param t TuploIntDoubleSet a guardar.
     */
    public TuploIntDoubleSet(TuploIntDoubleSet t) {
        inteiro = t.getInteiro();
        real = t.getReal();
        set = t.getSet();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o valor inteiro. 
     */
    public int getInteiro() {
        return inteiro;
    }

    /**
     * Devolve o número real. 
     */
    public double getReal() {
        return real;
    }
    
    
    /**
     * Devolve o Set de Strings. 
     */
    public Set<String> getSet() {
        return set;
    }
    
    
    /**
     * Adiciona um valor ao número inteiro.
     * 
     * @param i Valor a adicionar.
     * @return void
     */
    public void addInteiro(int i) {
        inteiro += i;
    }
    
    
    /**
     * Adiciona um valor ao número real.
     * 
     * @param r Valor a adicionar.
     * @return void
     */
    public void addReal(double r) {
        real += r;
    }
    
    
    /**
     * Adiciona todas as Strings de um Set a outro Set.
     * 
     * @param s Set de Strings a adicionar.
     * @return void
     */
    public void addSet(Set<String> s) {
        set.addAll(s);
    }
    
    
    /**
     * Adiciona um TuploIntDoubleSet a outro TuploIntDoubleSet.
     * 
     * @param t TuploIntDoubleSet a adicionar.
     * @return void
     */
    public void addTuploIntDoubleSet(TuploIntDoubleSet t) {
        inteiro += t.getInteiro();
        real += t.getReal();
        set.addAll(t.getSet());
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
        
        TuploIntDoubleSet t = (TuploIntDoubleSet) o;
        
        return (inteiro == t.getInteiro() && real == t.getReal() &&
                set.equals(t.getSet()));
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { inteiro, real, set });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("TuploIntDoubleSet = ");
        
        sb.append(inteiro);
        sb.append(" - ");
        sb.append(real);
        sb.append("\n");
        sb.append(set.toString());
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public TuploIntDoubleSet clone() {
        return new TuploIntDoubleSet(this);
    }
}
