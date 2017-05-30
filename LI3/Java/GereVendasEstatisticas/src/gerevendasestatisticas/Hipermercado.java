/**
 * Classe principal que contém as estruturas necessárias para o funcionamento
 * do programa GereVendas. Contém estruturas referente à faturação global, à
 * gestão de filiais, bem como catálogos de clientes e de produtos. Guarda 
 * informação acerca dos produtos mais vendidos. 
 * Esta classe é também responsável pelo cálculo de todas as queries iterativas
 * do programa GereVendas.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;


import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.HashMap;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Vector;
import java.util.Iterator;
import java.util.Collections;
import java.util.Comparator;
import java.util.stream.Collectors;


public class Hipermercado {
    
    // Variáveis de instância
    
    private FaturacaoGlobal fGlobal;              // Faturação global.
    private Filiais filiais;                      // Gestão de todas as filiais.
    private Catalogo produtos;                    // Catálogo de produtos.
    private Catalogo clientes;                    // Catálogo de clientes.
    private Map<String, ParIntSet> xMaisVendidos; /* Mapemento entre todos os 
                                                   * produtos e o total das 
                                                   * de unidades vendidas destes
                                                   * bem como o conjunto de 
                                                   * clientes que os compraram. 
                                                   */
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public Hipermercado() {
        this(new FaturacaoGlobal(),
             new Filiais(),
             new Catalogo(),
             new Catalogo(),
             new HashMap<>());
    }
    
    /**
     * Construtor por partes.
     *  
     * @param fG  Faturação global. 
     * @param fL  Gestão de todas as filiais.
     * @param pro Catálogo de produtos.
     * @param cli Catálogo de clientes.
     * @param xMV Mapeamento entre todos os produtos e conjunto de clientes
     *            que os compraram, bem como todas as unidades vendidas.
     */
    public Hipermercado(FaturacaoGlobal fG, Filiais fL,
                        Catalogo pro, Catalogo cli,
                        Map<String, ParIntSet> xMV) {
        
        fGlobal = fG.clone();
        filiais = fL.clone();
        produtos = pro.clone();
        clientes = cli.clone();
        xMaisVendidos = this.copiaXMV(xMV);     
    }
    
    
    
    /**
     * Construtor de cópia.
     * 
     * @param h Hipermercado.
     */
    public Hipermercado(Hipermercado h) {
        fGlobal = h.getFGlobal();
        filiais = h.getFiliais();
        produtos = h.getProdutos();
        clientes = h.getClientes();
        xMaisVendidos = h.getXMaisVendidos();
    }
        
    
    // Métodos de instância
    
    /**
     * @return Devolve uma cópia da faturação global. 
     */
    public FaturacaoGlobal getFGlobal() {
        return fGlobal.clone();
    }
    
    
    /**
     * @return Devolve uma cópia da gestão de todas as filiais.
     */
    public Filiais getFiliais() {
        return filiais.clone();
    }
    
    
    /**
     * @return Devolve uma cópia do catálogo de produtos. 
     */
    public Catalogo getProdutos() {
        return produtos.clone();
    }
    
    
    /**
     * @return Devolve uma cópia do catálogo de clientes.
     */
    public Catalogo getClientes() {
        return clientes.clone();
    }

    
    /**
     * @return Devolve uma cópia dos produtos mais vendidos. 
     */
    public Map<String, ParIntSet> getXMaisVendidos() {
        return this.copiaXMV(xMaisVendidos);
    }
    
    
    /////////////////////////////// Query 5 ///////////////////////////////////
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosTreeSetHashMap(String cliente) {
        return filiais.getProdutosMaisCompradosTreeSetHashMap(cliente);
    }
 
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosHashSetHashMap(String cliente) {
        return filiais.getProdutosMaisCompradosHashSetHashMap(cliente);
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosLinkedHashSetHashMap(String cliente) {
        return filiais.getProdutosMaisCompradosHashSetHashMap(cliente);
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosTreeSetTreeMap(String cliente) {
        return filiais.getProdutosMaisCompradosTreeSetTreeMap(cliente);
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosHashSetTreeMap(String cliente) {
        return filiais.getProdutosMaisCompradosHashSetTreeMap(cliente);
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de quantidades
     * de produtos compradas. Para quantidades iguais é ordenado por ordem 
     * alfabética dos códigos de produtos.
     * 
     * @param cliente Cliente a procurar.
     * @return Devolve o conjunto de produtos que um cliente mais comprou e as
     *         suas respetivas quantidades.
     */
    public Set<ParStringInt> getProdutosMaisCompradosLinkedHashSetTreeMap(String cliente) {
        return filiais.getProdutosMaisCompradosLinkedHashSetTreeMap(cliente);
    }
    
    
    ////////////////////////////////// QUERY 6 /////////////////////////////////
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de unidades 
     * compradas dos produtos. Para valores iguais de unidades, o conjunto é
     * ordenado por ordem alfabética dos códigos de produtos.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto com os x produtos mais vendidos bem como as
     *         suas quantidades e o número de clientes distintos que os 
     *         compraram.
     */
    public List<TuploIntIntString> getXMaisVendidosTreeSet(int x) {    
        Comparator<TuploIntIntString> cmp = new Comparator<TuploIntIntString>(){
            public int compare (TuploIntIntString a, TuploIntIntString b) {
                if (a.getPrimInt() > b.getPrimInt()) {
                    return -1;
                }
                
                if (a.getPrimInt() < b.getPrimInt()) {
                    return 1;
                }
                
                return a.getStr().compareTo(b.getStr());
            }
        };      
        
                
        Set<TuploIntIntString> resOrd = new TreeSet<>(cmp);
        
        
        xMaisVendidos.forEach((k, v) -> {
            resOrd.add(new TuploIntIntString(v.getInteiro(),
                                          v.getSet().size(),
                                          k));
        });
        
        int i = 0;
        
        List<TuploIntIntString> aux = new ArrayList<>();
        
        for(TuploIntIntString t : resOrd) {
            if (i == x) {
                break;
            }
            i++;
            aux.add(t);
        }
        
        return aux;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de unidades 
     * compradas dos produtos. Para valores iguais de unidades, o conjunto é
     * ordenado por ordem alfabética dos códigos de produtos.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto com os x produtos mais vendidos bem como as
     *         suas quantidades e o número de clientes distintos que os 
     *         compraram.
     */
    public List<TuploIntIntString> getXMaisVendidosHashSet(int x) {    
        Comparator<TuploIntIntString> cmp = new Comparator<TuploIntIntString>(){
            public int compare (TuploIntIntString a, TuploIntIntString b) {
                if (a.getPrimInt() > b.getPrimInt()) {
                    return -1;
                }
                
                if (a.getPrimInt() < b.getPrimInt()) {
                    return 1;
                }
                
                return a.getStr().compareTo(b.getStr());
            }
        };      
        
                
        Set<TuploIntIntString> resOrd = new HashSet<>();
        
        
        xMaisVendidos.forEach((k, v) -> 
            resOrd.add(new TuploIntIntString(v.getInteiro(),
                                             v.getSet().size(),
                                             k))
        );
        
        int i = 0;
        
        List<TuploIntIntString> aux = resOrd.parallelStream()
                                            .collect(Collectors.toList());
        
        Collections.sort(aux, cmp);
        
        for(TuploIntIntString t : resOrd) {
            if (i == x) {
                break;
            }
            i++;
            aux.add(t);
        }
        
        return aux;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de unidades 
     * compradas dos produtos. Para valores iguais de unidades, o conjunto é
     * ordenado por ordem alfabética dos códigos de produtos.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto com os x produtos mais vendidos bem como as
     *         suas quantidades e o número de clientes distintos que os 
     *         compraram.
     */
    public List<TuploIntIntString> getXMaisVendidosLinkedHashSet(int x) {    
        Comparator<TuploIntIntString> cmp = new Comparator<TuploIntIntString>(){
            public int compare (TuploIntIntString a, TuploIntIntString b) {
                if (a.getPrimInt() > b.getPrimInt()) {
                    return -1;
                }
                
                if (a.getPrimInt() < b.getPrimInt()) {
                    return 1;
                }
                
                return a.getStr().compareTo(b.getStr());
            }
        };      
        
                
        Set<TuploIntIntString> resOrd = new LinkedHashSet<>();
        
        
        xMaisVendidos.forEach((k, v) -> 
            resOrd.add(new TuploIntIntString(v.getInteiro(),
                                             v.getSet().size(),
                                             k))
        );
        
        int i = 0;
        
        List<TuploIntIntString> aux = resOrd.parallelStream()
                                            .collect(Collectors.toList());
        
        Collections.sort(aux, cmp);
        
        for(TuploIntIntString t : resOrd) {
            if (i == x) {
                break;
            }
            i++;
            aux.add(t);
        }
        
        return aux;
    }
    
    
    ////////////////////////////////// QUERY 7 /////////////////////////////////
    
    
    /**
     * @return Devolve um mapeamento entre todas as filiais e a lista dos seus 
     *         três maiores compradores em termos de valor gasto. 
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresHashMapArrayList() {
        int i = 0;
        Map<Integer, List<ParStringDouble>> t = filiais.getMaioresCompradoresHashMapArrayList();
        Map<Integer, List<ParStringDouble>> res = new HashMap<>();
        
        for (Integer k : t.keySet()) {
            Iterator<ParStringDouble> it = t.get(k).iterator();
            //Set<ParStringDouble> set = new TreeSet<>(new ParStringDoubleComparator());
            List<ParStringDouble> lst = new ArrayList<>();
            
            while (it.hasNext() && i < 3) {
                lst.add(it.next().clone());
                i++;
            }
            
            Collections.sort(lst, new ParStringDoubleComparator());
            
            res.put(k, lst);
            
            i = 0;
        }
        
        return res;
    }
    
    
    /**
     * @return Devolve um mapeamento entre todas as filiais e a lista dos seus 
     *         três maiores compradores em termos de valor gasto. 
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresHashMapVector() {
        int i = 0;
        Map<Integer, List<ParStringDouble>> t = filiais.getMaioresCompradoresHashMapVector();
        Map<Integer, List<ParStringDouble>> res = new HashMap<>();
        
        for (Integer k : t.keySet()) {
            Iterator<ParStringDouble> it = t.get(k).iterator();
          
            List<ParStringDouble> lst = new Vector<>();
            
            while (it.hasNext() && i < 3) {
                lst.add(it.next().clone());
                i++;
            }
            
            Collections.sort(lst, new ParStringDoubleComparator());
            
            res.put(k, lst);
            
            i = 0;
        }
        
        return res;
    }
    
    
    /**
     * @return Devolve um mapeamento entre todas as filiais e a lista dos seus 
     *         três maiores compradores em termos de valor gasto. 
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresTreeMapArrayList() {
        int i = 0;
        Map<Integer, List<ParStringDouble>> t = filiais.getMaioresCompradoresTreeMapArrayList();
        Map<Integer, List<ParStringDouble>> res = new TreeMap<>();
        
        for (Integer k : t.keySet()) {
            Iterator<ParStringDouble> it = t.get(k).iterator();
            List<ParStringDouble> lst = new ArrayList<>();
            
            while (it.hasNext() && i < 3) {
                lst.add(it.next().clone());
                i++;
            }
            
            Collections.sort(lst, new ParStringDoubleComparator());
            
            res.put(k, lst);
            
            i = 0;
        }
        
        return res;
    }
    
    
    /**
     * @return Devolve um mapeamento entre todas as filiais e a lista dos seus 
     *         três maiores compradores em termos de valor gasto. 
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradoresTreeMapVector() {
        int i = 0;
        Map<Integer, List<ParStringDouble>> t = filiais.getMaioresCompradoresTreeMapVector();
        Map<Integer, List<ParStringDouble>> res = new TreeMap<>();
        
        for (Integer k : t.keySet()) {
            Iterator<ParStringDouble> it = t.get(k).iterator();
            List<ParStringDouble> lst = new Vector<>();
            
            while (it.hasNext() && i < 3) {
                lst.add(it.next().clone());
                i++;
            }
            
            Collections.sort(lst, new ParStringDoubleComparator());
            
            res.put(k, lst);
            
            i = 0;
        }
        
        return res;
    }
    
    
    
    ////////////////////////////////// QUERY 8 /////////////////////////////////
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente do número de 
     * produtos distintos que um cliente comprou. Para quantidades iguais o
     * conjunto é ordenado por ordem alfabética dos códigos de clientes.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto de clientes que compraram o maior número de
     *         produtos distintos.
     */
    public Set<ParStringInt> getClientesMaisProdutosTreeSet(int x) {
        int i = 0;
        Map<String, Integer> cli = filiais.getClientesMaisProdutos();
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
        Set<ParStringInt> aux = new TreeSet<>(compProds);
        Set<ParStringInt> res = new TreeSet<>(compProds);
        
        cli.forEach((k, v) -> aux.add(new ParStringInt(k, v)));
        
        Iterator<ParStringInt> it = aux.iterator();
        
        while (it.hasNext() && i < x) {
            res.add(it.next().clone());
            i++;
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente do número de 
     * produtos distintos que um cliente comprou. Para quantidades iguais o
     * conjunto é ordenado por ordem alfabética dos códigos de clientes.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto de clientes que compraram o maior número de
     *         produtos distintos.
     */
    public Set<ParStringInt> getClientesMaisProdutosHashSet(int x) {
        int i = 0;
        Map<String, Integer> cli = filiais.getClientesMaisProdutos();
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
        List<ParStringInt> aux = new ArrayList<>();
        Set<ParStringInt> res = new HashSet<>();
        
        cli.forEach((k, v) -> aux.add(new ParStringInt(k, v)));
        
        Collections.sort(aux, compProds);
        
        for (; i < x; i++) {
            res.add(aux.get(i).clone());
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente do número de 
     * produtos distintos que um cliente comprou. Para quantidades iguais o
     * conjunto é ordenado por ordem alfabética dos códigos de clientes.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto de clientes que compraram o maior número de
     *         produtos distintos.
     */
    public Set<ParStringInt> getClientesMaisProdutosLinkedHashSet(int x) {
        int i = 0;
        Map<String, Integer> cli = filiais.getClientesMaisProdutos();
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return 1;
                    }
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return -1;
                    }
                    else {
                        return p1.getString().compareTo(p2.getString());
                    } 
                };
        List<ParStringInt> aux = new ArrayList<>();
        Set<ParStringInt> res = new LinkedHashSet<>();
        
        cli.forEach((k, v) -> aux.add(new ParStringInt(k, v)));
        
        Collections.sort(aux, compProds);
        
        for (; i < x; i++) {
            res.add(aux.get(i).clone());
        }
        
        return res;
    }
    
    
    ////////////////////////////////// QUERY 9 /////////////////////////////////
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramTreeSetHashMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new TreeSet<>(new ParStringDoubleComparator());
        Iterator<ParStringDouble> it = 
                filiais.getClientesMaisCompraramTreeSetHashMap(produto).iterator();
        
        while (it.hasNext() && i < x) {
            res.add(it.next().clone());
            i++;
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramHashSetHashMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new HashSet<>();
        List<ParStringDouble> lst = 
                filiais.getClientesMaisCompraramHashSetHashMap(produto)
                       .parallelStream()
                       .collect(Collectors.toList());
        
        
        Collections.sort(lst, new ParStringDoubleComparator());
        
        for (; i < x; i++) {
            res.add(lst.get(i).clone());
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramLinkedHashSetHashMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new LinkedHashSet<>();
        List<ParStringDouble> lst = 
                filiais.getClientesMaisCompraramLinkedHashSetHashMap(produto)
                       .parallelStream()
                       .collect(Collectors.toList());
        
        
        Collections.sort(lst, new ParStringDoubleComparator());
        
        for (; i < x; i++) {
            res.add(lst.get(i).clone());
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramTreeSetTreeMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new TreeSet<>(new ParStringDoubleComparator());
        Iterator<ParStringDouble> it = 
                filiais.getClientesMaisCompraramTreeSetTreeMap(produto).iterator();
        
        while (it.hasNext() && i < x) {
            res.add(it.next().clone());
            i++;
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramHashSetTreeMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new HashSet<>();
        List<ParStringDouble> lst = 
                filiais.getClientesMaisCompraramHashSetTreeMap(produto)
                       .parallelStream()
                       .collect(Collectors.toList());
        
        
        Collections.sort(lst, new ParStringDoubleComparator());
        
        for (; i < x; i++) {
            res.add(lst.get(i).clone());
        }
        
        return res;
    }
    
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente de valor gasto.
     * Para valores iguais é ordenado por ordem alfabética dos códigos de 
     * clientes.
     * 
     * @param produto Produto a procurar.
     * @param x       Quantidade de resultados pretendida.
     * @return Devolve o conjunto dos x clientes que mais compraram um produto
     *         bem como o valor total gasto por estes.
     */
    public Set<ParStringDouble> getClientesMaisCompraramLinkedHashSetTreeMap(String produto, int x) {
        int i = 0;
        Set<ParStringDouble> res = new LinkedHashSet<>();
        List<ParStringDouble> lst = 
                filiais.getClientesMaisCompraramLinkedHashSetTreeMap(produto)
                       .parallelStream()
                       .collect(Collectors.toList());
        
        
        Collections.sort(lst, new ParStringDoubleComparator());
        
        for (; i < x; i++) {
            res.add(lst.get(i).clone());
        }
        
        return res;
    }
    
    /**
     * Adiciona uma venda à faturação global.
     * 
     * @param produto  Produto vendido.
     * @param preco    Preço do produto.
     * @param unidades Unidades vendidas do produto.
     * @param mes      Mês da venda.
     * @param filial   Filial onde foi efetuada a venda.
     */
    public void addFGlobal(String produto, double preco, int unidades,
                           int mes, int filial) {
        fGlobal.addVenda(produto, preco, unidades, mes, filial);
    }
    
    
    /**
     * Adicina uma compra à gestão de todas as filiais.
     * 
     * @param produto  Produto comprado.
     * @param preco    Preço do produto.
     * @param unidades Unidades compradas.
     * @param cliente  Cliente que comprou um produto.
     * @param mes      Mês da compra.
     * @param filial   Filial onde foi efetuada a compra.
     */
    public void addFiliais(String produto, double preco, int unidades,
                           String cliente, int mes, int filial) {
       
        filiais.addVenda(produto, preco, unidades, cliente, mes, filial);
    }
    
    
    /**
     * Adiciona um produto ao catálogo de produtos.
     * @param produto Código do produto a adicionar.
     * @throws CodigoInvalidoException É lançada esta exceção quando um código
     *                                 de produto não é válido. Um código não
     *                                 é válido se for vazio.
     */
    public void addProduto(String produto) throws CodigoInvalidoException {
        try {
            produtos.addCodigo(produto);
            
        }
        catch (CodigoInvalidoException e) {
            throw e;
        }
        
        fGlobal.addNuncaComprado(produto);
    }
    
    
    /**
     * Adiciona um cliente ao catálogo de clientes.
     * @param cliente Código do produto a adicionar.
     * @throws CodigoInvalidoException É lançada esta exceção quando um código
     *                                 de cliente não é válido. Um código não
     *                                 é válido se for vazio.
     */
    public void addCliente(String cliente) throws CodigoInvalidoException {
        try {
            clientes.addCodigo(cliente);
        }
        catch (CodigoInvalidoException e) {
            throw e;
        }
    }
    
    
    /**
     * Adiciona um produto aos produtos mais vendidos. É adicionado um cliente
     * que o comprou bem como as unidades que este cliente comprou.
     * 
     * @param produto  Produto a adicionar.
     * @param unidades Unidades que um cliente comprou de um produto.
     * @param cliente  Cliente que comprou um produto
     */
    public void addXMaisVendidos(String produto, int unidades,
                                 String cliente) {
        try {
            xMaisVendidos.get(produto).addIntString(unidades, cliente);
        }
        catch (NullPointerException e) {
            xMaisVendidos.put(produto, new ParIntSet(unidades, cliente));
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
    
        Hipermercado h = (Hipermercado) o;
 
        return (fGlobal.equals(h.getFGlobal()) &&
                filiais.equals(h.getFiliais()) &&
                produtos.equals(h.getProdutos()) &&
                clientes.equals(h.getClientes()) &&
                xMaisVendidos.equals(h.getXMaisVendidos()));
    }
   
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { fGlobal,
                                              filiais,
                                              produtos,
                                              clientes,
                                              xMaisVendidos});
    }
    
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
        StringBuilder sb = new StringBuilder();
        
        sb.append(fGlobal.toString());
        sb.append(filiais.toString());
        sb.append(produtos.toString());
        sb.append(clientes.toString());
        sb.append(xMaisVendidos.toString());
        
        return sb.toString();
    }
    
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public Hipermercado clone() {
        return new Hipermercado(this);
    }
    
    
    // Métodos privados
    
    /*
     * Método auxiliar que efetua uma cópia de cada valor do map de produtos
     * mais vendidos.
     *
     * @param map Produtos mais vendidos a ser copiados.
     * @return 
     */
    private Map<String, ParIntSet> 
        copiaXMV(Map<String, ParIntSet> map) {
            
        Map<String, ParIntSet> temp = new HashMap<>();
        
        map.forEach((k, v) -> temp.put(k, v.clone()));
        
        return temp;
    }
}
