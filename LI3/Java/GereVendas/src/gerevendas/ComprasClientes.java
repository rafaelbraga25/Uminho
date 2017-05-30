/**
 * Classe em que cada Key do Map é um Cliente e o Value corresponde às
 * informações das compras que fez. 
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
import java.util.HashMap;
import java.util.Set;
import java.util.stream.Collectors;


public class ComprasClientes implements Serializable {
    
    // Variáveis de instância
    
    private Map<String, InfoProdutos> infoMap;  //Map com as informações das
                                                //compras dos Clientes.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public ComprasClientes() {
        infoMap = new HashMap<>();
    }
    
    
    /**
     * Construtor por partes.
     * 
     * @param map Map existente com informações das compras de clientes.
     */
    public ComprasClientes(Map<String, InfoProdutos> map) {
        infoMap = this.copiaInfoMap(map);
    }
    
    
    /**
     * Construtor a partir de outro ComprasClientes.
     * 
     * @param c ComprasClientes a guardar.
     */
    public ComprasClientes(ComprasClientes c) {
        infoMap = c.getInfoMap();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o Map com as informações das compras. 
     */
    public Map<String, InfoProdutos> getInfoMap() {
        return this.copiaInfoMap(infoMap);
    }
    
    
    /**
     * Devolve o número de produtos que um cliente comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Número de produtos que comprou.
     */
    public int getTotalProdutos(String cliente) {
        int total = 0;
        
        try {
            total = infoMap.get(cliente).getVendas();
        }
        catch (NullPointerException e) { }
        
        return total;
    }
    
  
    
    /**
     * Devolve um TuploIntDoubleSet com o número de unidades que o Cliente
     * comprou, o total gasto pelo Cliente e um Set com todos os códigos dos
     * produtos que o Cliente comprou
     * 
     * @param cliente Cliente a procurar.
     * @return Número de unidades que o Cliente comprou, total gasto pelo Cliente
     *         e um Set com todos os códigos dos produtos que o Cliente comprou.
     */
    public TuploIntDoubleSet getProdutosDistintos(String cliente) {
        try {
            //Tenta obter as informações das compras do Cliente.
            return infoMap.get(cliente).getProdutosDistintos();
        }
        catch (NullPointerException e) {
            //Caso o Cliente não exista, devolve um TuploIntDoubleSet vazio.
            return new TuploIntDoubleSet();
        }
    }
  
    
    /**
     * Devolve um Set com todos os Clientes que fizeram compras.
     * 
     * @return Set com os Clientes.
     */
    public Set<String> getClientes()
    {
        return infoMap.keySet().stream().collect(Collectors.toSet());
    }
    
    
    /**
     * Devolve um Set com todos os clientes que compraram um dado Produto.
     * 
     * @param produto Produto comprado pelos clientes.
     * @return Set com os Clientes.
     */
    public Set<String> getClientesDistintos(String produto) {
        Set<String> s = infoMap.entrySet()
                               .stream()
                               .filter(p -> p.getValue().containsProduto(produto))
                               .map(Map.Entry::getKey)
                               .collect(Collectors.toSet());
        
        return s;
    }
    
    
    /**
     * Devolve um Map com todos os produtos que um Cliente comprou e as
     * respectivas unidades.
     * 
     * @param cliente Clientea procurar.
     * @return Produtos que um Cliente comprou e respectivas unidades.
     */
    public Map<String, Integer> getProdutosMaisComprados(String cliente) {
        try {
            //Tenta obter as informações das compras do Cliente.
            return infoMap.get(cliente).getMapeamentoProdutosQuantidade();
        }
        catch (NullPointerException e) {
            //Caso o Cliente não exista, devolve um HashMap vazio.
            return new HashMap<>();
        }
    } 
    
    
    /**
     * Devolve um Map com os clientes que mais compraram.
     * 
     * @return Clientes que mais compraram.
     */
    public Map<String, Double> getMaioresCompradores() {
        return infoMap.entrySet()
                      .stream()
                      .collect(Collectors.toMap(
                              e -> e.getKey(),
                              e -> e.getValue().getGasto())
                      );
    }
    
    
    /**
     * Devolve os clientes que mais compraram um produto.
     * 
     * @param produto Produto a procurar.
     * @return Clientes que mais compraram um Produto. 
     */
    public Map<String, Double> getClientesMaisCompraram(String produto) {
        Map<String, Double> res = new HashMap<>();
        
        for (String cliente : infoMap.keySet()) {
            if (infoMap.get(cliente).containsProduto(produto)) {
                res.put(cliente, infoMap.get(cliente).getValor(produto));
            }
        }
        
        return res;
    }
    
    
    /**
     * Adiciona as informações de um Map a outro Map. 
     */
    public void setInfoMap(Map<String, InfoProdutos> map) {
        infoMap = this.copiaInfoMap(map);
    }
    
    
    /**
     * Adiciona uma venda ao Map de informações.
     * 
     * @param produto Produto a adicionar.
     * @param preco Preço do produto a adicionar.
     * @param unidades Unidades de produto compradas.
     * @param cliente Cliente que comprou o produto.
     * @return void
     */
    public void addVenda(String produto, double preco, int unidades,
                         String cliente) {
        
        InfoProdutos i = infoMap.get(cliente);
        
        try {
            //Adiciona as informações da compra ao historial do cliente.
            i.addVenda(produto, preco, unidades);
        }
        catch (NullPointerException e) {
            
            //Caso ainda não se tenha adicionado o Cliente ao Map de informações
            //dos clientes, cria-se uma nova entrada no Map para esse Cliente.
            i = new InfoProdutos();
            
            i.addVenda(produto, preco, unidades);
        }
        
        //Adiciona-se o Cliente ao Map de informações.
        infoMap.put(cliente, i); 
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
        
        ComprasClientes c = (ComprasClientes) o;
        
        return infoMap.equals(c.getInfoMap());
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { infoMap });
    }

    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        infoMap.values().stream().forEach(v -> sb.append(v.toString()));
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public ComprasClientes clone() {
        return new ComprasClientes(this);
    }
    
    
    // Métodos privados
    
    /*
     * Copias as informações de um Map para outro Map.
     *
     * @param map Map de onde se vai copiar as informações.
     * @return Map com as informações copiadas.
     */
    private Map<String, InfoProdutos> 
            copiaInfoMap(Map<String, InfoProdutos> map) {
                
            Map<String, InfoProdutos> temp = new HashMap<>();
                
            map.forEach((k, v) -> temp.put(k, v.clone()));
                
            return temp;
    }
}
