/**
 * Classe auxiliar para guardar um número inteiro e Set de Strings.
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
import java.util.HashSet;
import java.util.Set;

public class ParIntSet implements Serializable {
    
// Variáveis de instância
    
    private int inteiro;            //Inteiro a guardar.
    private Set<String> set;        //Set de Strings a guardar.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public ParIntSet() {
        this(0, new HashSet<>());
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i Valor inteiro a guardar.
     * @param s Set de Strings a guardar.
     */
    public ParIntSet(int i, Set<String> s) {
        inteiro = i;
        set = s;
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i Valor inteiro a guardar.
     * @param str String a guardar.
     */
    public ParIntSet(int i, String str) {
        inteiro += i;

        set = new HashSet<>();
        set.add(str);
    }
    
    
    /**
     * Construtor a partir de outro ParIntSet.
     * 
     * @param t ParIntSet a guardar.
     */
    public ParIntSet(ParIntSet t) {
        inteiro = t.getInteiro();
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
     * Devolve o Set de Strings. 
     */
    public Set<String> getSet() {
        return set;
    }
    
    
    /**
     * Adiciona um valor ao inteiro.
     * 
     * @param i Valor a adicionar
     * @return void
     */
    public void addInteiro(int i) {
        inteiro += i;
    }
    
    
    /**
     * Adiciona todos as Strings de um Set a outro Set.
     * 
     * @param s Set de Strings a adicionar.
     * @return void
     */
    public void addSet(Set<String> s) {
        set.addAll(s);
    }
    
    
    /**
     * Adiciona um ParIntSet a outro ParIntSet.
     * 
     * @param p ParIntSet a adicionar.
     * @return void
     */
    public void addParIntSet(ParIntSet p) {
        inteiro += p.getInteiro();
        set.addAll(p.getSet());
    }
    
    
    /**
     * Adiciona um inteiro e uma String ao ParIntSet.
     * 
     * @param i Inteiro a adicionar.
     * @param str String a adicionar.
     * @return void
     */
    public void addIntString(int i, String str) {
        inteiro += i;
        set.add(str);
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
        
        ParIntSet t = (ParIntSet) o;
        
        return (inteiro == t.getInteiro() && set.equals(t.getSet()));
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { inteiro, set });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParIntSet = ");
        
        sb.append(inteiro);
        sb.append("\n");
        sb.append(set.toString());
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParIntSet clone() {
        return new ParIntSet(this);
    }
}
