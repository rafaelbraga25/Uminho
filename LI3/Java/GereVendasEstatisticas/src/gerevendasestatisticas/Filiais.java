    /**
 * Classe para a gestão das filiais. Envolve todos os métodos relacionados com
 * o tratamento de dados relativos às filiais. Também inclui para cada Cliente
 * os produtos que comprou.
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
import java.util.HashSet;
import java.util.TreeSet;
import java.util.LinkedHashSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.List;
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.Collections;


public class Filiais implements Serializable{
    
    // Variáveis de instância
    
    private Map<Integer, GestaoFilial> gestaoFiliais;   //Dados relativos a cada
                                                        //filial. As Keys
                                                        //correspondem ao número
                                                        //da filial
    
    private Map<String, Set<String>> clientesProdutos;  //Clientes e respetivos
                                                        //produtos que compraram.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public Filiais() {
        gestaoFiliais = new HashMap<>();
        clientesProdutos = new HashMap<>();
    }
    
    
    /**
     * Construtor com parâmetros.
     * 
     * @param map Map com os dados relativos à gestão de cada filial
     * @param cP Map com códigos de clientes como Keys e nos values os produtos
     *           que compraram.
     */
    public Filiais(Map<Integer, GestaoFilial> map, Map<String, Set<String>> cP) {
        gestaoFiliais = this.copiaGestaoFiliais(map);
        clientesProdutos = cP;
    }
    
    
    /**
     * Construtor a partir de outra Filiais.
     * 
     * @param f Dados da gestão de filiais a guardar.
     */
    public Filiais(Filiais f) {
        gestaoFiliais = f.getGestaoFiliais();
        clientesProdutos = f.getClientesProdutos();
    }
    
    
    // Métodos de instância
    
    /**
     * Devolve o Map relativo à gestão das filiais.
     */
    public Map<Integer, GestaoFilial> getGestaoFiliais() {
        return this.copiaGestaoFiliais(gestaoFiliais);
    }
    
    
    /**
     * Devolve o Map relativo aos produtos que cada Cliente comprou.
     */
    public Map<String, Set<String>> getClientesProdutos() {
        return clientesProdutos;
    }
    
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosTreeSetHashMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        Set<ParStringInt> res = new TreeSet<>(compProds);
        Map<String, Integer> acc = new HashMap<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosHashMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringInt(k, acc.get(k))));
        
        return res;
    }
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosHashSetHashMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        List<ParStringInt> aux = new ArrayList<>();
        Map<String, Integer> acc = new TreeMap<>();
        Set<ParStringInt> res = new HashSet<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosHashMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> aux.add(new ParStringInt(k, acc.get(k))));
        
        Collections.sort(aux, compProds);
        
        aux.forEach(p -> res.add(p.clone()));
        
        return res;
    }
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosLinkedHashSetHashMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        List<ParStringInt> aux = new ArrayList<>();
        Map<String, Integer> acc = new HashMap<>();
        Set<ParStringInt> res = new LinkedHashSet<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosHashMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> aux.add(new ParStringInt(k, acc.get(k))));
        
        Collections.sort(aux, compProds);
        
        aux.forEach(p -> res.add(p.clone()));
        
        return res;
    }
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosTreeSetTreeMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        Set<ParStringInt> res = new TreeSet<>(compProds);
        Map<String, Integer> acc = new HashMap<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosTreeMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> res.add(new ParStringInt(k, acc.get(k))));
        
        return res;
    }
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosHashSetTreeMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        List<ParStringInt> aux = new ArrayList<>();
        Map<String, Integer> acc = new TreeMap<>();
        Set<ParStringInt> res = new HashSet<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosTreeMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> aux.add(new ParStringInt(k, acc.get(k))));
        
        Collections.sort(aux, compProds);
        
        aux.forEach(p -> res.add(p.clone()));
        
        return res;
    }
    
    
    /**
     * Devolve os produtos mais comprados por um Cliente e as unidades que
     * comprou.
     * 
     * @param cliente Cliente a procurar.
     * @return Produtos mais comprados pelo Cliente e as unidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosLinkedHashSetTreeMap(String cliente) {
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
                
        List<ParStringInt> aux = new ArrayList<>();
        Map<String, Integer> acc = new TreeMap<>();
        Set<ParStringInt> res = new LinkedHashSet<>();
        
        gestaoFiliais.forEach((k, v) -> 
            this.juntaProdsMaisComprados(acc, 
                    v.getProdutosMaisCompradosTreeMap(cliente))
        );
        
        acc.keySet().stream()
                    .forEach(k -> aux.add(new ParStringInt(k, acc.get(k))));
        
        Collections.sort(aux, compProds);
        
        aux.forEach(p -> res.add(p.clone()));
        
        return res;
    }
    
    
    /**
     * Para cada filial, devolve a lista dos clientes que mais gastaram e quanto
     * eles gastaram.
     * 
     * @return Clientes que mais gastaram e quanto gastaram.
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresHashMapArrayList() {
        Map<Integer, List<ParStringDouble>> res = new HashMap<>();
        
        gestaoFiliais.forEach((k, v) -> res.put(k, v.getMaioresCompradoresHashMapArrayList()));
        
        return res;
    }
    
    
    
    /**
     * Para cada filial, devolve a lista dos clientes que mais gastaram e quanto
     * eles gastaram.
     * 
     * @return Clientes que mais gastaram e quanto gastaram.
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresHashMapVector() {
        Map<Integer, List<ParStringDouble>> res = new HashMap<>();
        
        gestaoFiliais.forEach((k, v) -> res.put(k, v.getMaioresCompradoresHashMapVector()));
        
        return res;
    }
    
    
    /**
     * Para cada filial, devolve a lista dos clientes que mais gastaram e quanto
     * eles gastaram.
     * 
     * @return Clientes que mais gastaram e quanto gastaram.
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresTreeMapArrayList() {
        Map<Integer, List<ParStringDouble>> res = new TreeMap<>();
        
        gestaoFiliais.forEach((k, v) -> res.put(k, v.getMaioresCompradoresTreeMapArrayList()));
        
        return res;
    }
    
    
    /**
     * Para cada filial, devolve a lista dos clientes que mais gastaram e quanto
     * eles gastaram.
     * 
     * @return Clientes que mais gastaram e quanto gastaram.
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresTreeMapVector() {
        Map<Integer, List<ParStringDouble>> res = new TreeMap<>();
        
        gestaoFiliais.forEach((k, v) -> res.put(k, v.getMaioresCompradoresTreeMapVector()));
        
        return res;
    }
    
    
    /**
     * Devolve um Map em que as Keys são códigos de clientes e os seus values
     * o número de Produtos diferentes que esses clientes compraram.
     * 
     * @return Clientes e números de produtos que compraram.
     */
    public Map<String, Integer> getClientesMaisProdutos() {
        return clientesProdutos.entrySet()
                               .parallelStream()
                               .collect(Collectors.toMap(
                                       e -> e.getKey(), 
                                       e -> e.getValue().size()));
    }
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramTreeSetHashMap(String produto) {
        Map<String, Double> acc = new HashMap<>();
        Set<ParStringDouble> res = new TreeSet<>(new ParStringDoubleComparator());
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramHashMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramHashSetHashMap(String produto) {
        Map<String, Double> acc = new HashMap<>();
        Set<ParStringDouble> res = new HashSet<>();
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramHashMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramLinkedHashSetHashMap(String produto) {
        Map<String, Double> acc = new HashMap<>();
        Set<ParStringDouble> res = new LinkedHashSet<>();
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramHashMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramTreeSetTreeMap(String produto) {
        Map<String, Double> acc = new TreeMap<>();
        Set<ParStringDouble> res = new TreeSet<>(new ParStringDoubleComparator());
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramTreeMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramHashSetTreeMap(String produto) {
        Map<String, Double> acc = new TreeMap<>();
        Set<ParStringDouble> res = new HashSet<>();
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramTreeMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    /**
     * Para um Produto devolve os códigos de clientes que o compraram e quanto
     * gastaram na compra.
     * 
     * @param produto Produto a procurar.
     * @return Clientes e números de produtos que compraram.
     */
    public Set<ParStringDouble> getClientesMaisCompraramLinkedHashSetTreeMap(String produto) {
        Map<String, Double> acc = new TreeMap<>();
        Set<ParStringDouble> res = new LinkedHashSet<>();
        
        gestaoFiliais.values().forEach(v ->
            this.juntaClientesMaisCompraram(acc, v.getClientesMaisCompraramTreeMap(produto))
        );
        
        acc.forEach((k, v) -> res.add(new ParStringDouble(k, v)));
        
        return res;
    }
    
    
    /**
     * Faz o set para a gestaoFiliais. 
     * @param map Map da gestão de filiais a copiar.
     */
    public void setGestaoFiliais(Map<Integer, GestaoFilial> map) {
        gestaoFiliais = this.copiaGestaoFiliais(map);
    }
    
    
    /**
     * Adiciona uma venda à gestão de filiais.
     * 
     * @param produto Produto a adicionar.
     * @param preco Preço do produto.
     * @param unidades Unidades vendidas.
     * @param cliente Cliente que comprou o produto.
     * @param mes Mês da venda.
     * @param filial Filial da venda.
     */
    public void addVenda(String produto, double preco, int unidades,
                         String cliente, int mes, int filial) {
        
        GestaoFilial g = gestaoFiliais.get(filial);
        Set<String> prods;
        
        try {
            //Tenta adicionar os dados da venda à filial correspondente.
            g.addVenda(produto, preco, unidades, cliente, mes);
        }
        catch (NullPointerException e) {
            //Caso não se tenha um Map relativo às vendas na filial, cria-se
            //esse Map e adiciona-se a venda.
            g = new GestaoFilial();
            
            g.addVenda(produto, preco, unidades, cliente, mes);
        }
        
        //Adiciona a filial à gestão de filiais.
        gestaoFiliais.put(filial, g);
        
        try {
            //Tenta adicionar o Produto ao Cliente no Map clientesProdutos.
            prods = clientesProdutos.get(cliente);
            prods.add(produto);
        }
        catch (NullPointerException e) {
            //Caso não haja uma Key igual a Cliente, cria-se um Set para adicionar
            //o Produto.
            prods = new HashSet<>();
            prods.add(produto);
        }
        
        //Adiciona-se o Set com os Produtos ao Cliente correspondente.
        clientesProdutos.put(cliente, prods);
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
        
        Filiais f = (Filiais) o;
        
        return (gestaoFiliais.equals(f.getGestaoFiliais()) && 
                clientesProdutos.equals(f.getClientesProdutos()));
    }
    
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { gestaoFiliais, clientesProdutos });
    }

    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        gestaoFiliais.values().stream().forEach(v -> sb.append(v.toString()));
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public Filiais clone() {
        return new Filiais(this);
    }
    
    
    // Métodos privados
    
    /**
     * Copia os elementos de um Map para um novo map.
     * 
     * @param map Map a copiar.
     * @return Novo Map com os elementos do Map dado.
     */
    private Map<Integer, GestaoFilial> 
            copiaGestaoFiliais(Map<Integer, GestaoFilial> map) {
                
            Map<Integer, GestaoFilial> temp = new HashMap<>();
                
            map.forEach((k, v) -> temp.put(k, v.clone()));
                
            return temp;
    }
            
  
    /*
     * Adiciona a um acumulador os códigos de produtos e as respetivas quantidades
     * vendidas.
     * Caso já exista uma Key igual ao código a inserir, soma as unidades.
     * Caso contrário, é criada uma nova Key igual ao código.
     * 
     * @param acc Acumulador.
     * @param map Map com os dados a adicionar.
     */
    private void 
           juntaProdsMaisComprados(Map<String, Integer> acc,
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
           
    
    /*
     * Adiciona a um acumulador os clientes e os respetivos gastos.
     * Caso já exista uma Key igual ao código a inserir, soma os gastos.
     * Caso contrário, é criada uma nova Key igual ao código.
     * 
     * @param acc Acumulador.
     * @param map Map com os dados a adicionar.
     */
    private void 
           juntaClientesMaisCompraram(Map<String, Double> acc,
                                      Map<String, Double> map) {               
        map.forEach((k, v) -> {
            Double d = acc.get(k);
            
            if (d == null) {
                acc.put(k, v);
            }
            else {
                d += map.get(k);
                acc.put(k, v);
            }
        });
    }
}

