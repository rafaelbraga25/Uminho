/**
 * Classe em que cada Key do Map é um Produto e o Value corresponde às unidades
 * vendidas e o faturado das suas vendas.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

/**
 *
 * @author RafaelBraga
 */

import java.util.Arrays;
import java.util.stream.Collectors;
import java.util.Map;
import java.util.HashMap;
import java.io.Serializable;

public class InfoProdutos implements Serializable {
    
    // Variáveis de instância
    
    private Map<String, ParVendasFaturado> mapVF; //Map com as informações da
                                                  //vendas do Produto.
    
    private double gasto;                         // Valor total dispendido
                                                  // por clientes.
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public InfoProdutos() {
        mapVF = new HashMap<>();
        gasto = 0;
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param map Map existente com informações das vendas do Produto.
     * @param g   Valor total gasto por um cliente em todos os produtos.
     */
    public InfoProdutos(Map<String, ParVendasFaturado> map, double g) {
        mapVF = this.copiaVF(map);
        gasto = g;
    }
    
    
    /**
     * Construtor a partir de outro InfoProdutos.
     * 
     * @param i InfoProdutos a guardar.
     */
    public InfoProdutos(InfoProdutos i) {
        mapVF = i.getMapVF();
        gasto = i.getGasto();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o Map com as informações das vendas. 
     */
    public Map<String, ParVendasFaturado> getMapVF() {
        return this.copiaVF(mapVF);
    }

    /**
     * @return Devolve o total gasto na compra de todos os produtos. 
     */
    public double getGasto() {
        return gasto;
    }
    
    
    /**
     * Adiciona uma venda ao Map de informações.
     * 
     * @param produto Produto a adicionar.
     * @param preco Preço do produto a adicionar.
     * @param unidades Unidades de produto compradas.
     * @return void
     */
    public void addVenda(String produto, double preco, int unidades) {
        ParVendasFaturado p = mapVF.get(produto);
        
        try {
            p.addVendasFaturado(preco, unidades);
        }
        catch (NullPointerException e) {
            p = new ParVendasFaturado(preco, unidades);
        }
        
        mapVF.put(produto, p);
        gasto += (preco * unidades);
    }
    
    
    /**
     * Verifica se um produto existe no Map de informações.
     * 
     * @param produto Produto a procurar
     * @return true caso o Produto exista no Map
     *         false caso contrário
     */
    public boolean containsProduto(String produto) {
        return mapVF.containsKey(produto);
    }
  

    /**
     * Para cada Produto, devolve o seu número de unidades vendidas.
     * 
     * @return A cada Produto as unidades vendidas.
     */
    public Map<String, Integer> getMapeamentoProdutosQuantidade() {
        return mapVF.entrySet()
                    .stream()
                    .collect(Collectors.toMap(
                            e -> e.getKey(), 
                            e -> e.getValue().getVendas()));
    }
    
    
    /**
     * Devolve o total faturado com a venda de todos os produtos.
     * 
     * @return Total faturado com as vendas. 
     */
    public double getValorTotalProdutos() {
        return mapVF.values()
                    .stream()
                    .mapToDouble(p -> p.getFaturado()).sum();
    }
    
    
    /**
     * Devolve todas as unidades vendidas de todos os produtos.
     * 
     * @return Total de unidades vendidas. 
     */
    public int getTotalVendas() {
        return mapVF.values()
                    .stream()
                    .mapToInt(p -> p.getVendas()).sum();
    }
    

    /**
     * Para um Produto devolve o faturado.
     * 
     * @param produto Produto a procurar.
     * @return Faturado com o Produto.
     */
    public double getValor(String produto) {
        try {
            //Tenta obter o faturado com o produto.
            return mapVF.get(produto).getFaturado();
        }
        catch (NullPointerException e) {
            //Caso não exista no Map de informações, devolve 0.
            return 0;
        }
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
        
        InfoProdutos i = (InfoProdutos) o;
        
        return mapVF.equals(i.getMapVF()) && gasto == i.getGasto();
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { mapVF, gasto });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        sb.append(gasto);
        sb.append("\n");
        
        mapVF.values().stream().forEach(v -> {
                sb.append(v.toString());
                sb.append("\n"); 
        });
        
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public InfoProdutos clone() {
        return new InfoProdutos(this);
    }
    
    
    // Métodos privados
    
    /*
     * Copias as informações de um Map para outro Map.
     *
     * @param map Map de onde se vai copiar as informações.
     * @return Map com as informações copiadas.
     */
    private Map<String, ParVendasFaturado> 
        copiaVF(Map<String, ParVendasFaturado> map) {
            
        Map<String, ParVendasFaturado> temp = new HashMap<>();
        
        map.forEach((k, v) -> temp.put(k, v.clone()));
        
        return temp;
    }
}


