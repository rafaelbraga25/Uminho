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

package gerevendas;

import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;
import java.util.Map;
import java.util.HashMap;
import java.util.List;
import java.util.Vector;
import java.util.Iterator;
import java.util.Collections;
import java.util.Comparator;
import java.io.Serializable;


public class Hipermercado implements Serializable {
    
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
     * @return Devolve o número total de produtos presentes no catálogo de
     *         produtos.
     */
    public int getTotalProdutos() {
        return produtos.getTotalCodigos();
    }
    
    
    /**
     * @return Devolve uma cópia do catálogo de clientes.
     */
    public Catalogo getClientes() {
        return clientes.clone();
    }
    
    
    /**
     * @return Devolve o número de total de clientes presentes no catálogo de
     *         clientes.
     */
    public int getTotalClientes() {
        return clientes.getTotalCodigos();
    }
    

    /**
     * @return Devolve uma cópia dos produtos mais vendidos. 
     */
    public Map<String, ParIntSet> getXMaisVendidos() {
        return this.copiaXMV(xMaisVendidos);
    }


    /**
     * @return Devolve, para cada mês, a quantidades de clientes distintos que 
     *         efeturam compras.
     */
    public Map<Integer, Integer> getClientesMes() {
        return filiais.getClientesMes();
    }
    
    
    /**
     * @return Devolve, para cada mês, o número total de vendas efetuadas.
     */
    public Map<Integer, Integer> getVendasMes() {   
        return fGlobal.getVendasMes();
    }
    
    
    /**
     * @return Devolve o total faturado. 
     */
    public double getFaturado() {
        return fGlobal.getFaturado();
    }
    
    
    /**
     * @return Devolve, para cada mês, o total faturado para cada filial. 
     */
    public Map<Integer, Map<Integer, Double>> getFaturadoFilial() {
        return fGlobal.getFaturadoFilial();
    }
    
    
    /////////////////////////////// Query 1 ///////////////////////////////////
    
    /**
     * @return Devolve o conjunto de produtos que nunca foram comprados. 
     */
    public Set<String> getNuncaComprados() {
        return fGlobal.getNuncaComprados();
    }
    
    
    /////////////////////////////// Query 2 ///////////////////////////////////
    
    /**
     * 
     * @param mes Mês a procurar.
     * @return Devolve um par que contém o número total de vendas realizadas no
     *         mês recebido, bem como o número total de clientes distintos
     *         que efeturam compras nesse mês.
     */
    public ParIntInt getVendasClientesMes(int mes) {
       return new ParIntInt(fGlobal.getVendas(mes), 
                            filiais.getClientesPorMes(mes));
    }
    
    
    /////////////////////////////// Query 3 ///////////////////////////////////
    
    /**
     * @param cliente Cliente a procurar.
     * @return Devolve para cada mês o número total de compras que um cliente
     *         efetuou, o número total de produtos distintos que comprou, bem 
     *         como o valor total gasto por esse cliente.
     */
    public Map<Integer, TuploIntDouble> getComprasCliente(String cliente) {
        return filiais.getComprasCliente(cliente);
    }
    
    
    /////////////////////////////// Query 4 ///////////////////////////////////
    
    /**
     * @param produto Produto a procurar
     * @return Devolve, para cada mês, quantas vezes um produto foi comprado,
     *         por quantos clientes distintos, e o total faturado por esse
     *         produto.
     */
    public Map<Integer, TuploIntDouble> getVendasProduto(String produto) {
        
        /* Das filiais obtem-se para cada mês o número de distintos clientes
         * que compraram o produto que se pretende pesquisar.
         */ 
        Map<Integer, Integer> clientesMes = filiais.getVendasProduto(produto);
        
        
        /* Da faturação global obtem-se para cada mês o total de vendas e o
         * total faturado do produto a pesquisar.
         */
        Map<Integer, ParVendasFaturado> infoVendas = 
                fGlobal.getVendasProduto(produto);
       
        
        // Junção entre os resultados guardados em clientesMes e infoVendas.
        Map<Integer, TuploIntDouble> res = new HashMap<>(); 
        
        clientesMes.forEach((k, v) -> {
            TuploIntDouble aux = new TuploIntDouble();
            aux.addPrimInt(clientesMes.get(k));
            aux.addSegInt(infoVendas.get(k).getVendas());
            aux.addPrimDouble(infoVendas.get(k).getFaturado());
            res.put(k, aux);
        });
        
        return res;
        
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
    public Set<ParStringInt> getProdutosMaisComprados(String cliente) {
        return filiais.getProdutosMaisComprados(cliente);
    }
    
    
    /////////////////////////////// Query 6 ///////////////////////////////////
    
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
    public Set<TuploIntIntString> getXMaisVendidos(int x) {
        int i = 0; /* Variável auxiliar para selecionar os primeiros x 
                    * resultados */
        
        /* Comparador que efetua a ordenação no conjunto a devolver.
         * Ordena o conjunto por ordem decrescente de unidades vendidas. */
        Comparator<TuploIntIntString> cmp = new Comparator<TuploIntIntString>(){
            public int compare (TuploIntIntString a, TuploIntIntString b) {
                if (a.getPrimInt() > b.getPrimInt()) {
                    return -1;
                }
                
                if (a.getPrimInt() < b.getPrimInt()) {
                    return 1;
                }
                
                /* Para unidades vendidas iguais ordena o conjunto por
                 * ordem alfabética dos códigos de produtos. */
                return a.getStr().compareTo(b.getStr());
            }
        };       
                
        Set<TuploIntIntString> aux = new TreeSet<>(cmp); 
       
        /* A cada valor da estrutura dos produtos mais vendidos converte
         * o conjunto de clientes distintos que compraram um produto para 
         * o seu valor total. O resultado é ordenado pelo critério de 
         * comparação descrito acima. */
        xMaisVendidos.forEach((k, v) -> {
            aux.add(new TuploIntIntString(v.getInteiro(),
                                          v.getSet().size(),
                                          k));
        });
        
        
        Set<TuploIntIntString> ret = new TreeSet<>(cmp); /* Conjunto a retornar
                                                          * ordenado por comp.
                                                          */
        
        /* Do conjunto obtido selecionam-se os primeiros x elementos deste. */
        for (TuploIntIntString tiis : aux) {
           if (i == x) {
               break;
           }
           ret.add(tiis);
           i++;
        }

        return ret;
    }
    
    
    /////////////////////////////// Query 7 ///////////////////////////////////
    
    /**
     * @return Devolve um mapeamento entre todas as filiais e a lista dos seus 
     *         três maiores compradores em termos de valor gasto. 
     */
    public Map<Integer, List<ParStringDouble>> getMaioresCompradores() {
        int i = 0; /* Variável auxiliar para selecionar os três maiores
                    * compradores. */
        
        /* Obtem-se a partir de todas as filiais os seus maiores compradores. */
        Map<Integer, List<ParStringDouble>> t = filiais.getMaioresCompradores();
        
        /* Mapeamento que irá conter apenas os três maiores compradores de 
           cada filial. */
        Map<Integer, List<ParStringDouble>> res = new HashMap<>();
        
        
        /* Para cada filial obtem-se a lista dos seus maiores compradores. */
        for (Integer k : t.keySet()) {
            Iterator<ParStringDouble> it = t.get(k).iterator();
            List<ParStringDouble> lst = new Vector<>();
            
            /* Selecionam-se da lista os três maiores compradores. */
            while (it.hasNext() && i < 3) {
                lst.add(it.next().clone());
                i++;
            }
            
            /* Ordenada-se a lista dos três maiores compradores de acordo com
             * o total gasto por estes. */
            Collections.sort(lst, new ParStringDoubleComparator());
            
            res.put(k, lst);
            
            /* Inicia-se a contagem para a filial seguinte. */
            i = 0;
        }
        
        return res;
    }
    
    
    /////////////////////////////// Query 8 ///////////////////////////////////
    
    /**
     * O conjunto devolvido é ordenado por ordem decrescente do número de 
     * produtos distintos que um cliente comprou. Para quantidades iguais o
     * conjunto é ordenado por ordem alfabética dos códigos de clientes.
     * 
     * @param x Quantidade de resultados pretendida.
     * @return Devolve o conjunto de clientes que compraram o maior número de
     *         produtos distintos.
     */
    public Set<ParStringInt> getClientesMaisProdutos(int x) {
        int i = 0; /* Variável auxiliar para selecionar os x resultados
                    * pretendidos. */
        
        /* Obtem-se o mapeamento entre todos os clientes e respetiva
         * quantidade de produtos distintos que estes compraram.
         */
        Map<String, Integer> cli = filiais.getClientesMaisProdutos();
        
        /* Comparador que ordena o conjunto a devolver.
         * Ordena o conjunto por ordem decrescente de produtos distintos
         * comprados.
         */
        Comparator<ParStringInt> compProds = 
                (p1, p2) -> {
                    if (p1.getInteiro() > p2.getInteiro()) {
                        return -1;
                    }
                    
                    if (p1.getInteiro() < p2.getInteiro()) {
                        return 1;
                    }
                    
                    /* Para quantidades iguais ordena o conjunto por
                     * ordem alfabética de códigos de clientes. 
                     */
                    return p1.getString().compareTo(p2.getString()); 
                };
        
        
        /* Conjunto auxliar que irá conter todos os clientes. */
        Set<ParStringInt> aux = new TreeSet<>(compProds);
        
        /* Conjunto a ser retornado que apenas irá conter os x clientes
         * e quantidade produtos distintos que estes compraram. */
        Set<ParStringInt> res = new TreeSet<>(compProds);
        
        cli.forEach((k, v) -> aux.add(new ParStringInt(k, v)));
        
        Iterator<ParStringInt> it = aux.iterator();
        
        /* Seleciona os x primeiros resultados já que o conjunto está ordenado
         * por ordem decrescente. */
        while (it.hasNext() && i < x) {
            res.add(it.next().clone());
            i++;
        }
        
        return res;
    }
    
    
    /////////////////////////////// Query 9 ///////////////////////////////////
    
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
    public Set<ParStringDouble> getClientesMaisCompraram(String produto, int x) {
        int i = 0; /* Variável auxilar para selecionar os x resultados 
                    * pretendidos. */
                     
        /* Conjunto a ser devolvido ordenado pelo critério desta query. */
        Set<ParStringDouble> res = new TreeSet<>(new ParStringDoubleComparator());
        
        /* Obtem-se o conjunto de todos os clientes que compraram um produto, 
         * bem como o valor gasto por estes. */
        Iterator<ParStringDouble> it = 
                filiais.getClientesMaisCompraram(produto).iterator();
        
        /* Selecionam-se os primeiros x clientes e valores gastos do conjunto
         * obtido acima. */
        while (it.hasNext() && i < x) {
            res.add(it.next().clone());
            i++;
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
