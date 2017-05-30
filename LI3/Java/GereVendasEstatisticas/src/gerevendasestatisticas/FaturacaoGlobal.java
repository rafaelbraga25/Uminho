/**
 * Classe para a faturação global. Envolve todos os métodos relacionados com
 * a faturação. Também inclui os produtos que nunca foram comprados.
 * A faturação global começa por estar separada por meses.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import java.io.Serializable;

import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;
import java.util.Set;
import java.util.TreeSet;


public class FaturacaoGlobal implements Serializable {
	
    // Variáveis de instância
	
    private Map<Integer, FaturacaoFiliais> fatGlobal;   //Faturação por meses
    
    private Set<String> nuncaComprados;                 //Produtos nunca comprados
	
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public FaturacaoGlobal() {
        fatGlobal = new HashMap<>();
        nuncaComprados = new TreeSet<>();
    }
	
    
    /**
     * Construtor com parâmetros.
     * 
     * @param map Map com a faturação por meses.
     * @param set Set com os produtos nunca comprados.
     */
    public FaturacaoGlobal(Map<Integer, FaturacaoFiliais> map, Set<String> set) {
        fatGlobal = this.copiaFatGlobal(map);
        nuncaComprados = set;
    }
	
    
    /**
     * Construtor cópia.
     * 
     * @param f Faturação a guardar.
     */
    public FaturacaoGlobal(FaturacaoGlobal f) {
    	fatGlobal = f.getFatGlobal();
        nuncaComprados = f.getNuncaComprados();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o map com a faturação global. 
     */
    public Map<Integer, FaturacaoFiliais> getFatGlobal() {
        return this.copiaFatGlobal(fatGlobal);
    }
    
    
    /**
     * Devolve o Set com os produtos que nunca foram comprados. 
     */
    public Set<String> getNuncaComprados() {
        return nuncaComprados;
    }
    
    
    /**
     * Faz um Set para os produtos nunca comprados.
     */
    public void setNuncaComprados(Set<String> prods) {
        nuncaComprados = prods;
    }
    
    
    /**
     * Adiciona uma venda à faturação global.
     * 
     * @param produto Código do produto vendido.
     * @param preco Preço do produto vendido.
     * @param unidades Unidades de produto vendido.
     * @param mes Mês da venda.
     * @param filial Filial da venda.
     */
    public void addVenda(String produto, double preco, int unidades, int mes,
                         int filial) {
        
        FaturacaoFiliais f = fatGlobal.get(mes);
        
        try {
            //Tenta adicionar os dados da venda à filial correspondente.
            f.addVenda(produto, preco, unidades, filial);
        }
        catch (NullPointerException e) {
            
            //Caso não se tenha faturação relativa à filial, cria-se e adiciona-se
            //a venda à filial.
            f = new FaturacaoFiliais();
            
            f.addVenda(produto, preco, unidades, filial);
        }
        
        //Adiciona-se a venda ao mês correspondente.
        fatGlobal.put(mes, f);
        
        //Remove-se o produto do Set dos produtos nunca vendidos.
        nuncaComprados.remove(produto);
    }
    
    
    /**
     * Adiciona um Produto ao Set dos produtos nunca comprados.
     * 
     * @param produto Código de produto.
     */
    public void addNuncaComprado(String produto) {
        nuncaComprados.add(produto);
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
        
        FaturacaoGlobal f = (FaturacaoGlobal) o;
        
        return (fatGlobal.equals(f.getFatGlobal()) &&
                nuncaComprados.equals(f.getNuncaComprados()));
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { fatGlobal, nuncaComprados });
    }

    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Faturação Global: \n");
        
        fatGlobal.values().stream().forEach(v -> sb.append(v.toString()));
        nuncaComprados.stream().forEach(p -> { 
            sb.append(p);
            sb.append("\n");
        });
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public FaturacaoGlobal clone() {
	return new FaturacaoGlobal(this);
    }
    
    
    // Métodos privados
    
    /**
     * Copia os elementos de um Map para um novo map.
     * 
     * @param map Map a copiar.
     * @return Novo Map com os elementos do Map dado.
     */
    private Map<Integer, FaturacaoFiliais>
            copiaFatGlobal(Map<Integer, FaturacaoFiliais> map) {
            
            Map<Integer, FaturacaoFiliais> temp = new HashMap<>();
            
            map.forEach((k, v) -> temp.put(k, v.clone()));
            
            return temp;
    }
}

