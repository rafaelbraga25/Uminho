/**
 * Classe para o faturado e o número de unidades vendidas de um Produto.
 * É utilizada por outras classes para guardar informações sobre as vendas.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import java.io.Serializable;
import java.util.Arrays;


public class ParVendasFaturado implements Serializable {

    // Variáveis de instância
    
    private double faturado;        //Faturado na venda de um Produto
    private int vendas;             //Unidades vendidas de Produto

    
    // Construtores
    
    /**
     * Construtor com parâmetros.
     * 
     * @param preco Preço de venda do Produto.
     * @param unidades Unidades vendidas do Produto.
     */
    public ParVendasFaturado(double preco, int unidades) {
        faturado = (preco * unidades);
        vendas = unidades;
    }
    
    
    /**
     * Construtor a partir de outro ParVendasFaturado.
     * 
     * @param p ParVendasFaturado a guardar.
     */
    public ParVendasFaturado(ParVendasFaturado p) {
        faturado = p.getFaturado();
        vendas = p.getVendas();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o faturado com a venda de um Produto.
     */
    public double getFaturado() {
        return faturado;
    }

    
    /**
     * Devolve as unidades de Produto numa venda.
     */
    public int getVendas() {
        return vendas;
    }
    
    
    /**
     * Adiciona unidades vendidas e faturado a um Produto.
     * @param preco Preço do Produto.
     * @param unidades Unidades vendidas.
     */
    public void addVendasFaturado(double preco, int unidades) {
        faturado += (preco * unidades);
        vendas += unidades;
    }
    
    
    /**
     * Soma a um ParVendasFaturado outro ParVendasFaturado.
     * 
     * @param pvf ParVendasFaturado a somar.
     */
    public void somaParVendasFaturado (ParVendasFaturado pvf) {
        faturado += pvf.getFaturado();
        vendas += pvf.getVendas();
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
        
        ParVendasFaturado p = (ParVendasFaturado) o;
        
        return (faturado == p.getFaturado() && vendas == p.getVendas());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { faturado, vendas });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("ParVendasFaturado = ");
        
        sb.append(faturado);
        sb.append("-");
        sb.append(vendas);
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ParVendasFaturado clone() {
        return new ParVendasFaturado(this);
    }
}
