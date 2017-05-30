/**
 * Classe auxiliar para guardar dois números inteiros e uma String.
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

public class TuploIntIntString  implements Serializable {
    
    private int primInt; //Primeiro inteiro a guardar
    private int segInt;  //Segundo inteiro a guardar
    private String str;  //String a guardar
    
    
    // Construtores
   
    /**
     * Construtor vazio.
     */
    public TuploIntIntString() {
        primInt = 0;
        segInt = 0;
        str = "";
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param i1 Valor inteiro a guardar no primeiro inteiro.
     * @param i2 Valor inteiro a guardar no segundo inteiro.
     * @param s String a guardar.
     */
    public TuploIntIntString(int i1, int i2, String s) {
        primInt = i1;
        segInt = i2;
        str = s;
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param tIIS TuploIntIntString a guardar.
     */
    public TuploIntIntString (TuploIntIntString tIIS) {
        primInt = tIIS.getPrimInt();
        segInt = tIIS.getSegInt();
        str = tIIS.getStr();
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
    
    
    /**
     * Devolve a String. 
     */
    public String getStr() {
        return str;
    }
    
    
    /**
     * Adiciona um valor ao primeiro inteiro.
     * 
     * @param i Valor a adicionar. 
     * @return void
     */
    public void addPrimInt(int i) {
        primInt += i;
    }
    
    
    /**
     * Adiciona um valor ao segundo inteiro.
     * 
     * @param i Valor a adicionar.
     * @return void
     */
    public void addSegInt(int i) {
        segInt += i;
    }
    
    /**
     * Adiciona uma String.
     * 
     * @param s 
     * @return void
     */
    public void addStr(String s) {
        str = s;
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
        
        TuploIntIntString t = (TuploIntIntString) o;
        
        return (primInt == t.getPrimInt() && segInt == t.getSegInt() &&
                str.equals(t.getStr()));
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { primInt, segInt, str });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("TuploIntIntString = ");
        
        sb.append(primInt);
        sb.append(" - ");
        sb.append(segInt);
        sb.append(" - ");
        sb.append(str);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public TuploIntIntString clone() {
        return new TuploIntIntString(this);
    }
}
