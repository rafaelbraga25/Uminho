/**
 * Classe os dados das vendas numa filial.
 * O map compras está dividida por meses.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;


import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Vector;
import java.util.Collections;


public class GestaoFilial {
    
    // Variáveis de instância
    
    private Map<Integer, ComprasClientes> compras;  //Map com os dados das vendas
                                                    //por mês.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public GestaoFilial() {
        compras = new HashMap<>();
    }
    
    
    /**
     * Construtor por partes.
     * 
     * @param map Map existente com informações das vendas na filial por mês.
     */
    public GestaoFilial(Map<Integer, ComprasClientes> map) {
        compras = this.copiaCompras(map);
    }
    
    
    /**
     * Construtor a partir de outro GestaoFilial.
     * 
     * @param g GestaoFilial a guardar.
     */
    public GestaoFilial(GestaoFilial g) {
        compras = g.getCompras();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve um map com os dados das vendas na filial por mês.
     */
    public Map<Integer, ComprasClientes> getCompras() {
        return this.copiaCompras(compras);
    }
    

    /**
     * Faz o Set das compras por mês na filial.
     * 
     * @param map Map com os dados a copiar.
     */
    public void setCompras(Map<Integer, ComprasClientes> map) {
        compras = this.copiaCompras(map);
    }
    
    
    /**
     * Adiciona os dados de uma venda ao respetivo mês.
     * 
     * @param produto Produto a adicionar.
     * @param preco Preço do produto.
     * @param unidades Unidades vendidas.
     * @param cliente Cliente que comprou o Produto.
     * @param mes Mês da venda.
     */
    public void addVenda(String produto, double preco, int unidades,
                         String cliente, int mes) {
        
        ComprasClientes c = compras.get(mes);
        
        try {
            //Tenta adicionar a venda ao mês correspondente.
            c.addVenda(produto, preco, unidades, cliente);
        }
        catch (NullPointerException e) {
            //Caso não exista uma Key correspondente a esse mê, é criada uma nova
            //chave igual ao mês.
            c = new ComprasClientes();
            
            c.addVenda(produto, preco, unidades, cliente);
        }
        
        //Adiciona-se a venda ao mês.
        compras.put(mes, c);
    }

    
    /**
     * Devolve os códigos de produtos mais comprados e respetivas unidades, para
     * um dado Cliente.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados por um Cliente e respetivas unidades.
     */
    public Map<String, Integer> getProdutosMaisCompradosHashMap(String cliente) {
        Map<String, Integer> acc = new HashMap<>();
        
        compras.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, v.getProdutosMaisCompradosHashMap(cliente))
        );
        
        return acc;
    }

    
    /**
     * Devolve os códigos de produtos mais comprados e respetivas unidades, para
     * um dado Cliente.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados por um Cliente e respetivas unidades.
     */
    public Map<String, Integer> getProdutosMaisCompradosTreeMap(String cliente) {
        Map<String, Integer> acc = new TreeMap<>();
        
        compras.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, v.getProdutosMaisCompradosTreeMap(cliente))
        );
        
        return acc;
    }
    
    
    /**
     * Devolve uma lista com os clientes que mais compraram e quanto gastaram,
     * na filial em todo o ano.
     */
    public List<ParStringDouble> getMaioresCompradoresHashMapArrayList() {
        List<ParStringDouble> res = new ArrayList<>();
        Map<String, Double> acc = new HashMap<>();
        
        compras.forEach((k, v) ->
            this.juntaMapStringDouble(acc, v.getMaioresCompradores()));
        
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringDouble(k, acc.get(k))));
        
        Collections.sort(res, new ParStringDoubleComparator());
        
        return res;
    }
    
    
    /**
     * Devolve uma lista com os clientes que mais compraram e quanto gastaram,
     * na filial em todo o ano.
     */
    public List<ParStringDouble> getMaioresCompradoresHashMapVector() {
        List<ParStringDouble> res = new Vector<>();
        Map<String, Double> acc = new HashMap<>();
        
        compras.forEach((k, v) ->
            this.juntaMapStringDouble(acc, v.getMaioresCompradores()));
        
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringDouble(k, acc.get(k))));
        
        Collections.sort(res, new ParStringDoubleComparator());
        
        return res;
    }
    
    
    /**
     * Devolve uma lista com os clientes que mais compraram e quanto gastaram,
     * na filial em todo o ano.
     */
    public List<ParStringDouble> getMaioresCompradoresTreeMapArrayList() {
        List<ParStringDouble> res = new ArrayList<>();
        Map<String, Double> acc = new TreeMap<>();
        
        compras.forEach((k, v) ->
            this.juntaMapStringDouble(acc, v.getMaioresCompradores()));
        
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringDouble(k, acc.get(k))));
        
        Collections.sort(res, new ParStringDoubleComparator());
        
        return res;
    }
    
    
    /**
     * Devolve uma lista com os clientes que mais compraram e quanto gastaram,
     * na filial em todo o ano.
     */
    public List<ParStringDouble> getMaioresCompradoresTreeMapVector() {
        List<ParStringDouble> res = new Vector<>();
        Map<String, Double> acc = new TreeMap<>();
        
        compras.forEach((k, v) ->
            this.juntaMapStringDouble(acc, v.getMaioresCompradores()));
        
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringDouble(k, acc.get(k))));
        
        Collections.sort(res, new ParStringDoubleComparator());
        
        return res;
    }
    
    
    /**
     * Devolve, para um Produto, os clientes que mais gastaram na compra desse
     * Produto.
     * 
     * @param produto Produto a procurar.
     * @return Clientes que mais compraram o Produto dado.
     */
    public Map<String, Double> getClientesMaisCompraramHashMap(String produto) {
        Map<String, Double> acc = new HashMap<>();
        
        compras.values().forEach(v ->
            this.juntaMapStringDouble(acc, v.getClientesMaisCompraramHashMap(produto)));
        
        return acc;
    }
    
    
    /**
     * Devolve, para um Produto, os clientes que mais gastaram na compra desse
     * Produto.
     * 
     * @param produto Produto a procurar.
     * @return Clientes que mais compraram o Produto dado.
     */
    public Map<String, Double> getClientesMaisCompraramTreeMap(String produto) {
        Map<String, Double> acc = new TreeMap<>();
        
        compras.values().forEach(v ->
            this.juntaMapStringDouble(acc, v.getClientesMaisCompraramTreeMap(produto)));
        
        return acc;
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
        
        GestaoFilial g = (GestaoFilial) o;
        
        return compras.equals(g.getCompras());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { compras });
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Gestao Filial: \n");
        
        compras.values().stream().forEach(v -> sb.append(v.toString()));
        
        return sb.toString();
    }
 
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public GestaoFilial clone() {
        return new GestaoFilial(this);
    }
    
    
    // Métodos privados
    
    /*
     * Copias as informações de um Map para outro Map.
     *
     * @param map Map de onde se vai copiar as informações.
     * @return Map com as informações copiadas.
     */
    private Map<Integer, ComprasClientes> 
            copiaCompras(Map<Integer, ComprasClientes> map) {
                
            Map<Integer, ComprasClientes> temp = new HashMap<>();
                
            map.forEach((k, v) -> temp.put(k, v.clone()));
                
            return temp;
    }
            
    
    /**
     * Adiciona a um acumulador os produtos que mais foram comprados.
     * Caso exista uma Key igual ao código do Produto, somam-se o número de
     * unidades vendidas.
     * Caso contrário, cria-se uma nova Key igual ao código do Produto.
     * 
     * @param acc Acumulador.
     * @param map Map com os valores a adicionar ao acumulador.
     */
    private void juntaProdsMaisComprados(Map<String, Integer> acc,
                                        Map<String, Integer> map) {
    
        map.forEach((k, v) -> {
            Integer i = acc.get(k);
            
            if (i == null) {
                acc.put(k, v);
            }
            else {
                i += map.get(k);
                acc.put(k, i);
            }
        });
    }
           
    
    /**
     * Adiciona a um acumulador os clientes que mais gastaram.
     * Caso exista uma Key igual ao código do Cliente, somam-se total gasto.
     * Caso contrário, cria-se uma nova Key igual ao código do Cliente.
     * 
     * @param acc Acumulador.
     * @param map Map com os valores a adicionar ao acumulador. 
     */
    private void juntaMapStringDouble(Map<String, Double> acc,
                                     Map<String, Double> map) {
    
        map.forEach((k, v) -> {
            Double d = acc.get(k);
            
            if (d == null) {
                acc.put(k, v);
            }
            else {
                d += map.get(k);
                acc.put(k, d);
            }
        });
    }
}
