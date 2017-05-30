/**
 * Classe para os campos de uma venda: Código do Produto, Preço do Produto,
 * Unidades vendidas, Tipo de venda, Código de Cliente, Mês da venda e Filial
 * da venda.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import java.io.Serializable;
import java.util.Arrays;


public class Venda implements Serializable {
    
    // Variáveis de instância
	
    private String produto;         //Código do Produto
    private double preco;           //Preço do Produto
    private int unidades;           //Unidades vendidas
    private String tipo;            //Tipo de venda
    private String cliente;         //Código de Cliente
    private int mes;                //Mês da venda
    private int filial;             //Filial da venda
 
    
    
    // Construtores
    
    /**
     * Construtor com parâmetros.
     * 
     * @param produto Código do Produto
     * @param preco Preço do Produto
     * @param unidades Unidades vendidas
     * @param tipo Tipo de venda
     * @param cliente Código de Cliente
     * @param mes Mês da venda
     * @param filial Filial da venda
     */
    public Venda(String produto, double preco, int unidades, String tipo,
                 String cliente, int mes, int filial) {
        this.produto = produto;
        this.preco = preco;
        this.unidades = unidades;
        this.tipo = tipo;
        this.cliente = cliente;
        this.mes = mes;
        this.filial = filial;
    }
    
    
    /**
     * Construtor a partir de outra Venda.
     * 
     * @param p Venda a guardar.
     */
    public Venda(Venda v) {
        produto = v.getProduto();
        preco = v.getPreco();
        unidades = v.getUnidades();
        tipo = v.getTipo();
        cliente = v.getCliente();
        mes = v.getMes();
        filial = v.getFilial();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o Código do Produto.
     */
    public String getProduto() {
        return produto;
    }
    
    
    /**
     * Devolve o Preço do Produto.
     */
    public double getPreco() {
        return preco;
    }
    
    
    /**
     * Devolve as unidades vendidas do Produto.
     */
    public int getUnidades() {
        return unidades;
    }
    
    
    /**
     * Devolve o tipo do Produto.
     */
    public String getTipo() {
        return tipo;
    }
    
    
    /**
     * Devolve o Código do Cliente.
     */
    public String getCliente() {
        return cliente;
    }
    
    
    /**
     * Devolve o mês da venda.
     */
    public int getMes() {
        return mes;
    }
    
    
    /**
     * Devolve a filial da venda.
     */
    public int getFilial() {
        return filial;
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Compara um objeto com um elemento desta classe.
     * 
     * @param o Objeto a comparar.
     * @return true caso sejam iguais
     *         false caso contrário
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (o.getClass() != this.getClass())) {
            return false;
        }
        
        Venda v = (Venda) o;
        
        return (produto.equals(v.getProduto()) && preco == v.getPreco() &&
                unidades == v.getUnidades() && tipo.equals(v.getTipo()) &&
                cliente.equals(v.getCliente()) && mes == v.getMes() &&
                filial == v.getFilial());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    @Override
    public int hashCode() {
        return Arrays.hashCode(new Object[] { produto, preco, unidades, tipo,
                                              cliente, mes, filial} );
    }
    
   
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("Venda: ");
        
        sb.append(produto);
        sb.append("-");
        sb.append(preco);
        sb.append("-");
        sb.append(unidades);
        sb.append("-");
        sb.append(tipo);
        sb.append("-");
        sb.append(cliente);
        sb.append("-");
        sb.append(mes);
        sb.append("-");
        sb.append(filial);
        
        return sb.toString();
    }
    
   
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public Venda clone() {
        return new Venda(this);
    }
}




