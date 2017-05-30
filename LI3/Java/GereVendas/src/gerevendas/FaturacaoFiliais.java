/**
 * Classe para a faturação de cada filial. Envolve todos os métodos relacionados
 * com a faturação.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendas;

import java.io.Serializable;
import java.util.Arrays;
import java.util.Map;
import java.util.TreeMap;
import java.util.HashMap;

public class FaturacaoFiliais implements Serializable {
    
    // Variáveis de instância
    
    private Map<Integer, InfoProdutos> fatFiliais;      //Faturação por filial
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public FaturacaoFiliais() {
        fatFiliais = new HashMap<>();
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param map Map com a faturação por filial.
     */
    public FaturacaoFiliais(Map<Integer, InfoProdutos> map) {
        fatFiliais = this.copiaFatFiliais(map);
    }
    
    
    /**
     * Construtor a partir de outra FaturacaoFiliais.
     * 
     * @param f Faturação a guardar.
     */
    public FaturacaoFiliais(FaturacaoFiliais f) {
        fatFiliais = f.getFatFiliais();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o map com a faturação das filiais. 
     */
    public Map<Integer, InfoProdutos> getFatFiliais() {
        return this.copiaFatFiliais(fatFiliais);
    }
    
    
    /**
     * Devolve o número de unidades vendidas.
     */
    public int getVendas() {
        return fatFiliais.values()
                         .stream()
                         .reduce(0, (s, f) -> s += f.getVendas(),
                                 (s1, s2) -> s1 + s2);
    }
    
    
    /**
     * Devolve o total da soma da faturação de todas as filiais.
     */
    public double getFaturado() {
        return fatFiliais.values()
                         .stream()
                         .reduce(0.0, (s, f) -> s += f.getFaturado(),
                                 (s1, s2) -> s1 + s2);
    }
    
    
    /**
     * @return Devolve o faturada para cada filial.
     */
    public Map<Integer, Double> getFaturadoFilial() 
    {
        Map<Integer, Double> r = new TreeMap<>();
        
        fatFiliais.forEach((k, v) -> r.put(k, v.getFaturado()));
        
        return r;
    }
     
    
    /**
     * Calcula quantas vezes um Produto foi comprado e o total faturado.
     * 
     * @param produto Código do Produto.
     * @return Unidades e faturado nas vendas do Produto.
     */
    public ParVendasFaturado getVendasProduto(String produto) {
        
      ParVendasFaturado aux = new ParVendasFaturado(0, 0);
        
        fatFiliais.forEach((k, v) -> {

            aux.somaParVendasFaturado(v.getVendasProduto(produto));
            
        });
        
        return aux;
    }
    
    
    /**
     * Faz o Set para a Faturação das Filiais.
     */
    public void setFatFiliais(Map<Integer, InfoProdutos> map) {
        fatFiliais = this.copiaFatFiliais(map);
    } 
    
    
    /**
     * Adiciona uma venda à faturação da filial correspondente.
     * 
     * @param produto Código do produto vendido.
     * @param preco Preço do produto vendido.
     * @param unidades Unidades de produto vendido.
     * @param filial Filial da venda.
     */
    public void addVenda(String produto, double preco, int unidades, 
                         int filial) {
        
        InfoProdutos f = fatFiliais.get(filial);
        
        try {
            //Tenta adicionar os dados da venda ao produto correspondente.
            f.addVenda(produto, preco, unidades);
        }
        catch (NullPointerException e) {
            
            //Caso não se tenha faturação relativa ao produto, cria-se e
            //adiciona-se a venda a esse produto.
            f = new InfoProdutos();
            
            f.addVenda(produto, preco, unidades);
        }
        
        fatFiliais.put(filial, f);
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
        
        FaturacaoFiliais f = (FaturacaoFiliais) o;
        
        return fatFiliais.equals(f.getFatFiliais());
    }
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { fatFiliais });
    }

    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Faturacao Filiais: \n");
        
        fatFiliais.values().forEach(f -> sb.append(f.toString()));
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public FaturacaoFiliais clone() {
        return new FaturacaoFiliais(this);
    }
    
    
    // Métodos privados
    
    /**
     * Copia os elementos de um Map para um novo map.
     * 
     * @param map Map a copiar.
     * @return Novo Map com os elementos do Map dado.
     */
    private Map<Integer, InfoProdutos> 
            copiaFatFiliais(Map<Integer, InfoProdutos> map) {
            
            Map<Integer, InfoProdutos> temp = new HashMap<>();
            
            map.forEach((k, v) -> temp.put(k, v.clone()));
            
            return temp;
    }
}
