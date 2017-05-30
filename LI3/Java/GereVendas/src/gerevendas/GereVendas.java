/**
 * Nesta classe estão presentes todas as funções e métodos necessários para o
 * correcto funcionamento de GereVendas.
 * O menu de navegação (e a sua definição), os menus auxiliares, o menu de 
 * paginação, todas as consultas/queries assim como as variáveis para efeitos de 
 * estatística estão aqui presentes.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * 
 * @version 2016.06.11
 */

package gerevendas;

import static java.lang.System.out;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.util.stream.Collectors;

public class GereVendas {
    
    private static Hipermercado hipermercado; // Uma instância de Hipermercado.
    private static Menu menuMain;             // O menu principal.
    private static Menu menuLer;              // O menu de leitura de ficheiros.
    private static Menu menuGuardar;          // O menu para guardar dados.
    
    // Variáveis para efeitos de estatística.
    private static int numRegErrados;      // Número de vendas inválidas.
    private static Set<String> prodsNComp; // Conjunto de produtos não comprados.
    private static Set<String> prodsComp;  // Conjunto de produtos comprados.
    private static Set<String> clisNComp;  // Conjunto de clientes que não compraram.
    private static Set<String> clisComp;   // Conjunto de clientes que compraram.
    private static int comprasZero;        // Número de compras de valor 0.
    private static double fatTotal;        // Faturação total pela venda de produtos.
    private static boolean init;           // Valor de inicialização.
    private static ArrayList<Venda> lst;
    
    
    /**
     * Esta função efectua o tratamento de uma linha de vendas. De forma a 
     * otimizar o programa, são efectuados diversos cálculos auxiliares
     * conjuntamente com o envio de dados para as estruturas devidas.
     * 
     * @param linha Uma linha de Venda.
     * @return true se a linha da venda era válida.
     */
    public static boolean parseLinhaVenda(String linha) {
	double preco;                       // Preço de uma venda.
	int unidades;                       // Unidades de uma venda.
	int mes;                            // Mês de um código de venda.
	int filial;                         // Filial respectiva de uma venda.
        String cliente;                     // Código cliente que conste numa venda. 
	String[] campos = linha.split(" "); // Efectua o split da linha e guarda o resultado em campos.
	String produto = campos[0].trim();  // Código de produto que conste numa venda.
		
	try {
            // Guardar o resultado do split em campos para a variável respectiva.
            preco = Double.parseDouble(campos[1].trim());
            unidades = Integer.parseInt(campos[2].trim());
            cliente = campos[4].trim();
            mes = Integer.parseInt(campos[5].trim());
            filial = Integer.parseInt(campos[6].trim());
           
            fatTotal += preco * unidades; // Atualiza a faturação total.
            prodsNComp.remove(produto);   // Removemos o produto visto este ter sido comprado.
            prodsComp.add(produto);       // Acrescentamos um produto aos produtos comprados.
            clisNComp.remove(cliente);    // Removemos um cliente, este já efectuou uma compra.
            clisComp.add(cliente);        // Acrescentamos este cliente àqueles que já compraram.
            
            if(preco == 0) {
                comprasZero++; // Se o preço é zero, incrementar o número de compras a zero.
            }
            
            
            // Adiciona-se os devidos campos à faturação global.
            hipermercado.addFGlobal(produto, preco, unidades, mes, filial);
            
            // Adiciona-se os devidos campos às filiais.
            hipermercado.addFiliais(produto, preco, unidades, cliente, mes, filial);
            
            // Adiciona-se um novo produto aos produtos mais vendidos.
            hipermercado.addXMaisVendidos(produto, unidades, cliente);
            
            return true; // A linha era válida, correu tudo bem.
	}
        catch (NumberFormatException | NullPointerException | IndexOutOfBoundsException e) {
            numRegErrados++; // A linha é inválida, incrementamos o número destas.
            return false;  // Retornamos erro.
	}
    }
    
    
    /**
     * Apresenta os valores da consulta estatística 1.2.
     * Assume que os dados já estão todos em memória.
     */
    private static void showStat()
    {
        StringBuilder sb = new StringBuilder();
        double sum =  0; // Utilizada no cálculo da faturação total.
        
        Map<Integer, Map<Integer, Double>> fatFiliais = hipermercado.getFaturadoFilial();
        
        sb.append("Unidades vendidas:\n");
        
        hipermercado.getVendasMes()
                    .forEach((k, v) -> sb.append("Mês ")
                                         .append(k)    
                                         .append(": ")
                                         .append(v)
                                         .append("\n"));
        
        sb.append("\n");
        
        try {
            // Como será necessário apresentar uma tabela cujo cabeçalho são as filiais,
            // apresentamos o conjunto KeySet do mês 1 para o efeito.
            fatFiliais.get(1)
                    .keySet()
                    .stream()
                    .forEach(k -> sb.append("\t\tFilial ").append(k));
        }
        catch (NullPointerException e) { }

        
        
        sb.append("\n");
        
        // Apresentar o valor faturado de cada mês.
        fatFiliais.forEach((k, v) -> {
            sb.append("Mês ").append(k).append(":");
            v.values() 
             .stream()
             .forEach(f -> sb.append("\t  ").append(f));
            sb.append("\n");
        });
        
        for (Map<Integer, Double> m : fatFiliais.values()) {
            for (Double f : m.values()) {
                sum += f;
            }
        }
        
        sb.append("Faturação Global: ").append(sum).append("\n\n");
        
        sb.append("Clientes distintos que compraram no:\n");
        hipermercado.getClientesMes()
                    .forEach((k, v) -> sb.append("Mês ")
                                         .append(k)    
                                         .append(": ")
                                         .append(v) // Número de clientes que compraram num determinado mês.
                                         .append("\n"));
        
        // Apresenta, por fim, o resultado.
        out.println(sb);
    }
    
    /**
     * Inicializa os valores para a consulta estatística 1.1.
     */
    private static void initStat() {
        numRegErrados = 0;
        fatTotal = 0;
        prodsNComp = new HashSet<>();
        prodsComp = new HashSet<>();
        clisNComp = new HashSet<>();
        clisComp = new HashSet<>();
        comprasZero = 0;
    }
    
    /**
     * Apresenta os valores da consulta estatística 1.1.
     * 
     * @param fich Ficheiro carregado.
     * @param t    Tempo necessário para o carregamento do ficheiro.
     */
    private static void printStat(String fich, double t) {
        System.out.println("Ficheiro " + fich + " lido em " + t + " segundos."
        + "\nVendas erradas: " + numRegErrados
        + "\nNúmero total de produtos: " + hipermercado.getTotalProdutos() 
        + "\nNúmero total de produtos comprados: " + prodsComp.size() 
        + "\nNúmero de produtos que não foram comprados: " + prodsNComp.size()
        + "\nNúmero total de clientes: " + hipermercado.getTotalClientes()
        + "\nClientes que realizaram compras: " + clisComp.size() 
        + "\nNúmero de clientes que não realizaram compras: " + clisNComp.size()
        + "\nCompras de valor zero: " + comprasZero 
        + "\nFaturação Global: " + fatTotal + "\n");
    }
    
    /**
     * Função de arranque do programa.
     * Contém o conjunto de operações que permite ao utilizador navegar os menus
     * assim como os resultados das consultas.
     * 
     * @param args 
     */    
    public static void main(String args[])
    {
        init = true;                          // Início do programa.
        hipermercado = new Hipermercado();    // Inicialização da instância Hipermercado
        String codigo = "";                   // Um código de produto/cliente usado em diversos contextos.
        int i = 0;                            // Variável auxiliar para contextos diferentes.  
        List<String> res = new ArrayList<>(); // Recebe um ArrayList de strings de várias consultas.
        int op = 0;                           // Opção do menu de carregamento de ficheiros.
        lst = new ArrayList<>();
        
        // Inicialização das variáveis para efeitos de estatística.
        initStat();
       
        // Inicialização dos menus.
        carregarMenus();
       
        // Apresenta o menu de leitura de ficheiros para a inicialização do programa.
        op = menuLerDados();
        
        if (op == 0 && init) {
            System.exit(0);
        }
        
        init = false;
        
        do {
            menuMain.executa();
            switch (menuMain.getOpcao()) {
                // Para cada querie é medido o seu tempo de consulta.
                // Em queries que seja necessário uma amostragem detalhada de valores,
                // é utilizada uma função auxiliar que converte o output dessa consulta num
                // ArrayList para ser posteriormente navegado.
                case 1: Crono.start();
                        Set<String> s = hipermercado.getNuncaComprados();
                        out.println("Resultado obtido em " + Crono.print() + "s\n");
                        
                        if (s.size() == 0) {
                            out.println("Todos os produtos foram comprados.");
                        } 
                        else {
                            // Navegamos o resultado da consulta. O set é convertido em list primeiramente.
                            navegacao(s.stream().collect(Collectors.toList()), "");
                        }
                        break;
                        
                case 2: i = devolveMes();
                        Crono.start();
                        // O resultado da querie é tratado com a verTotalVendasClientes e apresentado no ecrã.
                        verTotalVendasClientes(hipermercado.getVendasClientesMes(i), i);
                        break;
                
                case 3: codigo = devolveCliente();
                        Crono.start();
                        verComprasClientes(hipermercado.getComprasCliente(codigo), codigo);
                        break;
                        
                case 4: codigo = devolveProduto();
                        Crono.start();
                        verVendasProdutos(hipermercado.getVendasProduto(codigo), codigo);
                        break;
                        
                case 5: codigo = devolveCliente();
                        Crono.start();
                        res = parIntStringToString(hipermercado.getProdutosMaisComprados(codigo));
                        out.println("Resultado obtido em " + Crono.print() + "s\n");
                        navegacao(res, "");
                        break;
                
                case 6: i = devolveInt();
                        Crono.start();
                        res = tuploIntIntStringToString(hipermercado.getXMaisVendidos(i));
                        out.println("Resultado obtido em " + Crono.print() + "s\n");
                        navegacao(res, "");
                        break;
                        
                case 7: Crono.start();
                        verMaioresCompradores(hipermercado.getMaioresCompradores());
                        break;
                
                case 8: i = devolveInt();
                        Crono.start();
                        res = parStringIntToString(hipermercado.getClientesMaisProdutos(i));
                        out.println("Resultado obtido em " + Crono.print() + "s\n");
                        navegacao(res, "");
                        break;
                        
                case 9: codigo = devolveProduto();
                        i = devolveInt();
                        Crono.start();
                        res = parStringDoubleToString(hipermercado.getClientesMaisCompraram(codigo, i));
                        out.println("Resultado obtido em " + Crono.print() + "s\n");
                        navegacao(res, "");
                        break;
                        
                case 10: menuLerDados(); // Menu de leitura de dados.
                         break;
                
                case 11: menuGuardarDados(); // Menu para efectuar a salvaguarda do estado do programa.
                         break;            
            }
            
        } while (menuMain.getOpcao() != 0); // Sai do programa quando a opção de navegação for 0.
    }      
    
    /**
     * Lê uma string do input.
     * 
     * @return A String dada pelo utilizador.
     */
    public static String lerInput(String msg)
    {
        String in;
        System.out.print(msg);
        in = Input.lerString();
        return in;
    }
    
    /**
     * Lê os ficheiros de disco para o carregamento das estruturas.
     * 
     * @param clientes Ficheiro dos clientes.
     * @param produtos Ficheiro dos produtos.
     * @param vendas   Ficheiro das vendas.
     */
    public static void lerDados(String clientes, String produtos, String vendas) {
        hipermercado = new Hipermercado();//Inicializa o hipermercado.
        
        Ficheiros.readLines(clientes, (String s) -> {
            try {
                hipermercado.addCliente(s); // Adiciona-se um novo cliente ao catálogo.
                clisNComp.add(s);           // Adiciona-se o cliente aos clientes 
                                            // que não efectuaram compras para posteriormente
                                            // caso haja uma linha de vendas com este cliente, 
                                            // o mesmo ser removido de clisNcomp.
            }
            catch (CodigoInvalidoException e) { }
            return null;
        });
        
        Ficheiros.readLines(produtos, (String s) -> {
            try {
                hipermercado.addProduto(s); // Adiciona-se um novo produto ao catálogo.
                prodsNComp.add(s);          // Adiciona-se o produto a prodsNComp 
                                            // (que não efectuaram compras), posteriormente
                                            // caso haja uma linha de vendas com este produto, 
                                            // o mesmo deve ser removido de prodsNcomp.
            }
            catch (CodigoInvalidoException e) { }
            return null;
        });
        
        out.println("A ler " + vendas + "...");
        
        Ficheiros.readLines(vendas, (String s) -> {
            GereVendas.parseLinhaVenda(s); // Aplica a função de parse às linhas resultado de readLines.
            return null;
        });
        
        out.println();
    }
    
    
    // Métodos auxiliares.
    
    /*
     * Carrega todos os menus utilizados na main.
     */
    private static void carregarMenus() {
        // Menu para navegação das consultas.
        String[] ops = {"Lista de Produtos nunca comprados e o seu total.",
                        "Vendas realizadas e Clientes distintos de um mês.",
                        "Compras, Produtos e Gastos de um Cliente por mês.",
                        "Vendas, Clientes distintos e Faturado de um Produto por mês.",
                        "Produtos mais comprados por um Cliente.",
                        "Obter os X Produtos mais vendidos e Clientes distintos.",
                        "Obter os 3 maiores compradores por filial.",
                        "Obter os X Clientes que compraram mais Produtos diferentes.",
                        "Obter os X Clientes que mais compraram um Produto.",
                        "Carregar ficheiros.",
                        "Guardar estado do programa."};
        
        // Menu para Leitura de ficheiros em disco.
        String[] ler = {"Ler ficheiros de texto por defeito.",
                        "Carregar Hipermercado por defeito.",
                        "Introduzir ficheiros de texto manualmente",
                        "Carregar Hipermercado a partir de um ficheiro dado."};
       
        // Menu para guardar o Hipermercado para disco para futuro carregamento.
        String[] guardar = {"Guardar no ficheiro por defeito.",
                            "Introduzir nome do ficheiro onde guardar."};
        
        // Inicialização dos menus.
        menuMain = new Menu(ops);
        menuLer = new Menu(ler);
        menuGuardar = new Menu(guardar);
    }
    
    /*
     * Execução do menu de leitura de dados/ficheiros.
     */
    private static int menuLerDados() {
        String clientes; // Ficheiro de clientes.
        String produtos; // Ficheiro de produtos.
        String str;      // Dependendo do contexto representa o ficheiro para carregar
                         // o estado do programa ou o ficheiro de vendas.
        
        do {
            menuLer.executa();
            switch (menuLer.getOpcao()) {
                case 1: initStat(); // Inicialização das variáveis de estatística 1.1.
                        Crono.start();
                        // Ficheiros de leitura por predefinição.
                        lerDados("Clientes.txt", "Produtos.txt", "Vendas_3M.txt");
                        printStat("Vendas_3M.txt", Crono.stop()); // Apresenta o resultado da estatística 1.1.
                        showStat(); // Apresenta o resultado da estatística 1.2.
                        break;
                
                // Carrega Hipermercado do ficheiro de predefinição.        
                case 2: hipermercado = Ficheiros.carregarHipermercado("hipermercado.dat");
                        break;
                        
                case 3: 
                        do {
                            out.print("Ficheiro de Clientes\n> ");
                            clientes = Input.lerString();
                            // Enquanto o ficheiro não existir continuará a pedir o input.
                        } while (!Ficheiros.existeFicheiro(clientes));
                        
                        do {
                            out.print("Ficheiro de Produtos\n> ");
                            produtos = Input.lerString();
                        } while (!Ficheiros.existeFicheiro(produtos));
                            
                        
                        do {
                            out.print("Ficheiro de Vendas\n> ");
                            str = Input.lerString();
                        } while (!Ficheiros.existeFicheiro(str));
                        
                        initStat(); // Inicialização das variáveis para estatística 1.1.
                        Crono.start();
                        lerDados(clientes, produtos, str); // Leitura dos ficheiros.
                        printStat(str, Crono.stop()); // Resultado da estatística 1.1.
                        showStat(); // Resultado da estatística 1.2, os dados já se encontram em memória.
                        break;
                    
                case 4: do {
                            // Carrega o Hipermercado a partir de um ficheiro em disco.
                            System.out.print("Ficheiro\n> ");
                            str = Input.lerString();
                        } while (!Ficheiros.existeFicheiro(str));
                
                        hipermercado = Ficheiros.carregarHipermercado(str); // Carrega o Hipermercado.
                        break;
            }
        } while (menuLer.getOpcao() > 4 && menuLer.getOpcao() <= 0);
        
        return menuLer.getOpcao();
    }   
    
    /*
     * Executa o menu que guarda o estado do Hipermercado para disco.
     */
    private static void menuGuardarDados() {
        String ficheiro; // Ficheiro onde guardar o ficheiro objecto (Hipermercado).
        
        do {
            menuGuardar.executa();
            switch (menuGuardar.getOpcao()) {
                case 1: Ficheiros.guardarHipermercado("hipermercado.dat", 
                                                      hipermercado);
                        break;
                        
                case 2: System.out.print("Ficheiro\n> ");
                        ficheiro = Input.lerString();
                        // Guarda o Hipermercado.
                        Ficheiros.guardarHipermercado(ficheiro, hipermercado);
                        break;
            }
        } while (menuGuardar.getOpcao() <= 0 && menuGuardar.getOpcao() > 2);
    }  
    
    /*
     * Apresenta o resultado da consulta número 2.
     * 
     * @param res Resultado da consulta.
     * @param mes Mês.
     */
    private static void verTotalVendasClientes(ParIntInt res, int mes) {
        out.println("Resultado obtido em " + Crono.print() + "s\n");
        out.println("Para o mês " + mes + ":");
        out.println("Total global de vendas: " + res.getPrimInt());
        out.println("Clientes distintos que compraram: " + res.getSegInt());
    }
    
    /*
     * Apresenta o resultado da consulta número 3.
     * 
     * @param res     Estrutura resultante da consulta.
     * @param cliente Parâmetro utilizado na consulta, um código cliente.
     */
    private static void verComprasClientes(Map<Integer, TuploIntDouble> res,
                                           String cliente) {
        int mes = 0;
        out.println("Resultado obtido em " + Crono.print() + "s\n");
        
        out.println("Cliente " + cliente);
    
        for (TuploIntDouble val: res.values()) {
            mes++;
            out.print("Mês " + mes + ": ");
            out.println("Unidades: " + val.getPrimInt() + " | "
                        + " Comprou " + val.getSegInt() + " produtos |"
                        + " Gastou " + val.getPrimDouble() + " u.m.");
        }
    }
    
    /*
     * Apresenta o resultado da consulta número 4.
     * 
     * @param res     Estrutura resultado da consulta que será interpretada nesta função.
     * @param produto Parâmetro utilizado na consulta, um código de produto.
     */
    private static void verVendasProdutos(Map<Integer, TuploIntDouble> res,
                                          String produto) {
        
        int mes = 0;
        
        out.println("Resultado obtido em " + Crono.print() + "s\n");
        
        out.println("Produto " + produto);
        
        for (TuploIntDouble val: res.values()) {
            mes++;
            out.print("Mês " + mes + ": ");
            out.println("Foi comprado " + val.getSegInt() + " vezes |"
                        + " Nº Clientes: " + val.getPrimInt() + " |"
                        + " Faturado: " + val.getPrimDouble());
        }
    }
    
    /*
     * Apresenta o resultado da consulta número 7.
     * 
     * @param res Estrutura resultado da consulta. 
     */
    private static void verMaioresCompradores(Map<Integer, List<ParStringDouble>> res) {

        out.println("Resultado obtido em " + Crono.print() + "s\n");
        
        for (Integer filial : res.keySet()) {
        
            out.println("Filial " + filial);
         
            for(ParStringDouble aux : res.get(filial)) {
                // Converte para uma string e apresenta no ecrã
                out.println(aux.getString() + "  Gasto: " + aux.getReal()); 
            }
        }
    }
    /*
     * Converte o resultado da consulta número 5 para ser posteriormente navegado.
     * 
     * @param res  A estrutura resultado da consulta.
     * @return     Uma lista de strings sendo a conversão de vários ParStringInt.
     */
    private static List<String> parIntStringToString(Set<ParStringInt> res) {
        
        List <String> aux = new ArrayList<>();
        
        res.forEach(v -> {
            aux.add(v.getString() + " | Unidades: " + v.getInteiro());
        });
        
        return aux;
    }
    
    /*
     * Converte o resultado da consulta número 6 para ser posteriormente navegado. 
     *
     * @param res A estrutura resultado da consulta.
     * @return    Uma lista de strings, conversão dos diversos TuploIntIntString.
     */
    private static List<String> tuploIntIntStringToString (Set<TuploIntIntString> res) {
        
        List <String> aux = new ArrayList<>();
        
        res.forEach(v -> {
            aux.add(v.getStr()+ " | Clientes: " + v.getSegInt() + " | Unidades: " + v.getPrimInt());
        });
        
        return aux;
    }
    
    /**
     * Converte o resultado da consulta número 8 para ser posteriormente navegado. 
     * 
     * @param res Estrutura resultado da consulta.
     * @return    Uma lista de strings sendo a conversão dos diversos ParStringInt.
     */
    private static List<String> parStringIntToString (Set<ParStringInt> res) {
        
        List <String> aux = new ArrayList<>();
        
        res.forEach( v -> {
            aux.add(v.getString() + " | Produtos: " + v.getInteiro());
        });
        
        return aux;
    }
    
    /**
     * Converte o resultado da consulta número 9 para ser posteriormente navegado.
     * 
     * @param res Estrutura resultado da consulta.
     * @return    Uma lista de strings, cada uma delas é o resultado da conversão de um ParStringDouble.
     */
    private static List<String> parStringDoubleToString (Set<ParStringDouble> res) {
        
        List <String> aux = new ArrayList<>();
        
        res.forEach( v -> {
            aux.add(v.getString() + " | Gasto: " + v.getReal());
        });
        
        return aux;
    }
    
    /*
     * Devolve um código de um cliente do input.
     * 
     * @return Código de cliente válido. 
     */
    private static String devolveCliente() {
        String str; 
        
        do {
            System.out.print("Cliente\n> ");
            str = Input.lerString();
            
            if (str.length() == 5 && Character.isUpperCase(str.charAt(0))) {
                break;
            }
            else {
                System.out.println("Input inválido! Introduza novamente:");
            }
            
        } while (true);
        
        return str;
    }
    
    /*
     * Devolve um código de um produto do input.
     * 
     * @return Código de produto válido. 
     */
    private static String devolveProduto() {
        String str; 
        
        do {
            System.out.print("Produto\n> ");
            str = Input.lerString();
            
            if (str.length() == 6 && Character.isUpperCase(str.charAt(0)) &&
                Character.isUpperCase(str.charAt(1))) {
                
                break;
            }
            else {
                System.out.println("Input inválido! Introduza novamente:");
            }
            
        } while (true);
        
        return str;
    }
    
    /*
     * Devolve um mês do recebido no input.
     * 
     * @return Mês válido. 
     */
    private static int devolveMes() {
        int mes;
        
        do {
            System.out.print("Mês\n> ");
            mes = Input.lerInt();
            
            if (mes >= 1 && mes <= 12) {
                break;
            }
            else {
                System.out.println("Mês inválido! Introduza novamente:");
            }
            
        } while (true);
        
        return mes;
    }
    
    /*
     * Devolve um natural positivo.
     * 
     * @return Inteiro. 
     */
    private static int devolveInt() {
        int i;
        
        do {
            System.out.print("Valor\n> ");
            i = Input.lerInt();
            
            if (i >= 1) {
                break;
            }
            else {
                System.out.println("Valor inválido! Introduza novamente:");
            }
            
        } while (true);
        
        return i;
    }
    /*
     * Recebe uma lista de strings e permite ao utilizador navegar nela. Permite ir para a página seguinte, para a
     * página anterior ou uma qualquer página explicitada pelo utilizador.
     * 
     * @param lst      Uma lista para ser navegada pelo utilizador.
     * @return message Mensagem que poderá ser apresentada a indicar o tipo de elementos apresentados.
     */  
    private static void navegacao(List<String> lst, String message) {
        Paginacao p = new Paginacao(20, lst);
        String op = "";
        int pag = 1;
        int items = 0;
        
        items = p.nextPage((String s) -> {
            out.println(s);
            return null;
        });
        
        if (items < p.getNumElements()) {
            do {
                out.println("\nPágina " + pag + " de " + p.getNumPags());
                out.println(message + "" + items + " de " + p.getNumElements() + ".\n"); 
                out.println("n - Próxima página.");
                out.println("p - Página anterior.");
                out.println("1 - " + p.getNumPags() + " Ir para a página.");
                out.println("0 - Sair.");
                
                op = Input.lerString(); 
               
                if (!op.equals("0")) {
                    if (op.equals("n") || op.equals("N")) {
                        if (pag == p.getNumPags()) {
                            op = "-";
                        }
                        else {
                            items += p.nextPage((String s) -> {
                                                    out.println(s);
                                                    return null;
                                    });
                            pag++;
                        }
                    }
                    else if (op.equals("p") || op.equals("P")) {
                        if (pag == 1) {
                            op = "-";
                        }
                        else {
                            items -= p.previousPage((String s) -> {
                                                      out.println(s);
                                                      return null;
                                    });
                            pag--;
                        }
                    }
                    else {
                        try {
                            pag = Integer.parseInt(op);
                            
                            if (pag < 1 || pag > p.getNumPags()) {
                                out.print("Opção inválida!");
                            }
                            else {
                                items = p.goToPage(pag, (String s) -> {
                                                        out.println(s);
                                                        return null;
                                        });
                            }
                        }
                        catch (NumberFormatException | NullPointerException e) {
                            out.println("Opção inválida!\n");
                        }
                    }
                }
                
            } while (!op.equals("0"));
        }
    }
}

