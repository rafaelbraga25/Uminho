/**
 * Classe auxiliar para guardar uma String e um número inteiro.
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


public class ParStringInt implements Serializable {
    
    // Variáveis de instância
    
    private String string;      //String a guardar.
    private int inteiro;        //Inteiro a guardar.
    
    
    // Construtores
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param str String a guardar.
     * @param i Valor inteiro a guardar.
     */
    public ParStringInt(String str, int i) {
        string = str;
        inteiro = i;
    }
    
    
    /**
     * Construtor a partir de outro ParStringInt.
     * 
     * @param p ParStringInt a guardar.
     */
    public ParStringInt(ParStringInt p) {
        string = p.getString();
        inteiro = p.getInteiro();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve a String. 
     */
    public String getString() {
        return string;
    }
    
    
    /**
     * Devolve o valor inteiro. 
     */
    public int getInteiro() {
        return inteiro;
    }
    
    
    /**
     * Adiciona um valor ao inteiro. 
     */
    public void addInteiro(int i) {
        inteiro += i;
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
        
        ParStringInt p = (ParStringInt) o;
        
        return (string.equals(p.getString()) && inteiro == p.getInteiro());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { string, inteiro });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParStringInt: ");
        
        sb.append(string);
        sb.append(" - ");
        sb.append(inteiro);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParStringInt clone() {
        return new ParStringInt(this);
    } 
}
