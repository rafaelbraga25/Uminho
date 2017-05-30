/**
 * Classe meramente responsável pelas estatísticas referentes ao programa
 * GereVendas. Contém estatísticas referentes à leitura dos ficheiros de um
 * milhão, três milhões e cinco milhões de vendas. Mede os tempos de leitura 
 * com e sem parsing desses três ficheiros e efetua calculos para diferentes
 * coleções das queries 5 a 9 de um ficheiro de vendas escolhido pelo 
 * utilizador.
 * Mostra todos estes resultados em tabelas e em gráficos.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import static java.lang.System.out;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.chart.BarChart;
import javafx.scene.chart.LineChart;
import javafx.scene.chart.CategoryAxis;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.stage.Stage;
import java.util.function.Function;
import javax.swing.JFrame;
import java.awt.GridLayout;
import javafx.embed.swing.JFXPanel;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class GereVendasEstatisticas extends Application {

    // Variáveis de classe
    
    private static Hipermercado hipermercado;                // Hipermercado.
    private final static String QUERY5 = "Query 5";         
    private final static String QUERY6 = "Query 6";
    private final static String QUERY7 = "Query 7";
    private final static String QUERY8 = "Query 8";
    private final static String QUERY9 = "Query 9";
    private final static String VENDAS_1M = "Vendas_1M.txt";
    private final static String VENDAS_3M = "Vendas_3M.txt";
    private final static String VENDAS_5M = "Vendas_5M.txt";
    private static JFrame frame;                             // Frame para se 
                                                             // carregar os
                                                             // gráficos.
    private static int counter;                              // Contador para
                                                             // profiling.
    private static ArrayList<Double> times;                  // ArrayList com
                                                             // as medições
                                                             // de tempos de 
                                                             // profiling.
    private static String file;                              // Ficheiro 
                                                             // para testar 
                                                             // queries.
    private final static int NUM_ADD = 50000;                
   
    
    
    /**
     * Separa cada campo da linha de vendas e guarda essa venda em hipermercado.
     * Conta os tempos de cada 50000 inserções.
     * 
     * @param linha Linhas lida do ficheiro de vendas.
     * @return Void.
     */
    public static Void parseLinha(String linha) {
	String[] campos = linha.split(" ");
	String produto = campos[0].trim();
        
        if (counter == NUM_ADD) {
            counter = 0;
            times.add(Crono.stop());
        }
        
        if (counter == 0) {
            Crono.start();    
        }
        
        counter++;
        
	try {
            double preco = Double.parseDouble(campos[1].trim());
            int unidades = Integer.parseInt(campos[2].trim());
            String cliente = campos[4].trim();
            int mes = Integer.parseInt(campos[5].trim());
            int filial = Integer.parseInt(campos[6].trim());
                    
            hipermercado.addFGlobal(produto, preco, unidades, mes, filial);
            hipermercado.addFiliais(produto, preco, unidades, cliente, mes, filial);
            hipermercado.addXMaisVendidos(produto, unidades, cliente);
             
            return null;
	}
	catch (NumberFormatException | NullPointerException e) { 
            return null;
        }
    }
    
    
    /**
     * Separa cada campo da linha de vendas e guarda essa venda em hipermercado.
     * 
     * @param linha 
     * @return Classe venda com todos os campos de uma venda. 
     */
    public static Venda parseLinhaVenda(String linha) {
	String[] campos = linha.split(" ");
	String produto = campos[0].trim();
		
	try {
            double preco = Double.parseDouble(campos[1].trim());
            int unidades = Integer.parseInt(campos[2].trim());
            String tipo = campos[3].trim();
            String cliente = campos[4].trim();
            int mes = Integer.parseInt(campos[5].trim());
            int filial = Integer.parseInt(campos[6].trim());
             
            return new Venda(produto, preco, unidades, tipo, cliente,
                             mes, filial);
	}
	catch (NumberFormatException | NullPointerException e) { 
            return null;
        }
    }
    
    
    /**
     * Converte todas as linhas de um ficheiro de vendas lido para instâncias
     * de venda.
     * 
     * @param linhas ArrayList com todas as linhas de um ficheiro de vendas.
     * @return ArrayList com todas as linhas convertidas para instâncias
     *         de Venda.
     */
    public static ArrayList<Venda> parseAllLinhas(ArrayList<String> linhas) { 
        ArrayList<Venda> vendas = 
                (ArrayList<Venda>) linhas.parallelStream()
                                         .map(l -> parseLinhaVenda(l))
                                         .collect(Collectors.toList());
        
        return vendas;
    } 
    
    
    /**
     * Chama todas as funções reponsáveis pelos calculos de todas as estatísticas
     * do programa GereVendas.
     * 
     * @param stage Container de uma scene. 
     */
    @Override
    public void start(Stage stage) {
        CategoryAxis xAxis = new CategoryAxis();
        NumberAxis yAxis = new NumberAxis();
        BarChart<String,Number> bc = new BarChart<>(xAxis,yAxis);
        double th5 = 0; // Tempos de um TreeSet combinado com um HashMap da Query 5
        double hh5 = 0; // Tempos de um HashSet combinado com um HashMap da Query 5
        double lh5 = 0; // Tempos de um LinkedHashSet combinado com um HashMap da Query 5
        double tt5 = 0; // Tempos de um TreeSet combinado com um TreeMap da Query 5
        double ht5 = 0; // Tempos de um HashSet combinado com um TreeMap da Query 5
        double lt5 = 0; // Tempos de um LinkedHashSet combinado com um TreeMap da Query 5
        double th9 = 0; // Tempos de um TreeSet combinado com um HashMap da Query 9
        double hh9 = 0; // Tempos de um HashSet combinado com um HashMap da Query 9
        double lh9 = 0; // Tempos de um LinkedHashSet combinado com um HashMap da Query 9
        double tt9 = 0; // Tempos de um TreeSet combinado com um TreeMap da Query 9
        double ht9 = 0; // Tempos de um HashSet combinado com um TreeMap da Query 9
        double lt9 = 0; // Tempos de um LinkedHashSet combinado com um TreeMap da Query 9
        
        GereVendasEstatisticas.leituraSemParsing();
        GereVendasEstatisticas.leituraComParsing();
        
        out.println("\nA carregar o ficheiro " + file + "...");
        
        Ficheiros.readLines(file, GereVendasEstatisticas::parseLinha);
        GereVendasEstatisticas.profiling();
        
        
        // Título do gráfico e título dos eixos x e y.
        bc.setTitle("Estatísticas das Queries 5 e 9");
        xAxis.setLabel("Queries");       
        yAxis.setLabel("Tempo");
    
        GereVendasEstatisticas.estatisticasQueries6e8();
        GereVendasEstatisticas.estatisticasQuery7();
        
        out.println("\nA calcular as estatísticas das Queries 5 e 9...\n");
        
        
        // Calcula todos os tempos das queries 5 e 9
        
        th5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosTreeSetHashMap("Z5000");
                return null;
        });
        
        hh5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosHashSetHashMap("Z5000");
                return null;
        });
        
        lh5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosLinkedHashSetHashMap("Z5000");
                return null;
        });
        
        tt5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosTreeSetTreeMap("Z5000");
                return null;
        });
        
        ht5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosHashSetTreeMap("Z5000");
                return null;
        });
        
        lt5 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getProdutosMaisCompradosLinkedHashSetTreeMap("Z5000");
                return null;
        });
        
        
        th9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramTreeSetHashMap("AF1184", 5);
                return null;
        });
        
        hh9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramHashSetHashMap("AF1184", 5);
                return null;
        });
        
        lh9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramLinkedHashSetHashMap("AF1184", 5);
                return null;
        });
        
        tt9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramTreeSetTreeMap("AF1184", 5);
                return null;
        });
        
        ht9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramHashSetTreeMap("AF1184", 5);
                return null;
        });
        
        lt9 = GereVendasEstatisticas.getTime((Void f) -> {
                hipermercado.getClientesMaisCompraramLinkedHashSetTreeMap("AF1184", 5);
                return null;
        });
        
        // Mostra em ecrã uma tabela em modo texto os resultados obtidos.
        
        out.print("\t  TreeSet com HashMap\tHashSet com HashMap");
        out.print("\tLinkedHashSet com HashMap\t   TreeSet com TreeMap");
        out.println("\t     HashSet com TreeMap\tLinkedHashSet com TreeMap");
        out.println("Query 5:    " + th5 + "\t\t  " + hh5 + "\t\t    " + lh5 + "  \t\t\t   "
                    + tt5 + " \t\t  " + ht5 + " \t\t   " + lt5);
        out.println("Query 9:    " + th9 + "\t\t  " + hh9 + "\t\t    " + lh9 + "  \t\t\t   "
                    + tt9 + " \t\t  " + ht9 + " \t\t   " + lt9);
        
        
        // Adiciona a cada categoria do gráfico os resultados obtidos.
        
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("TreeSet com HashMap");
        series1.getData().add(new XYChart.Data(QUERY5, th5)); 
        series1.getData().add(new XYChart.Data(QUERY9, th9));
        
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("HashSet com HashMap");
        series2.getData().add(new XYChart.Data(QUERY5, hh5));
        series2.getData().add(new XYChart.Data(QUERY9, hh9));
        
        XYChart.Series series3 = new XYChart.Series();
        series3.setName("LinkedHashSet com HashMap");
        series3.getData().add(new XYChart.Data(QUERY5, lh5));
        series3.getData().add(new XYChart.Data(QUERY9, lh9));
        
        XYChart.Series series4 = new XYChart.Series();
        series4.setName("TreeSet com TreeMap");
        series4.getData().add(new XYChart.Data(QUERY5, tt5));
        series4.getData().add(new XYChart.Data(QUERY9, tt9));
           
        XYChart.Series series5 = new XYChart.Series();
        series5.setName("HashSet com TreeMap");
        series5.getData().add(new XYChart.Data(QUERY5, ht5));
        series5.getData().add(new XYChart.Data(QUERY9, ht9));
             
        XYChart.Series series6 = new XYChart.Series();
        series6.setName("LinkedHashSet com TreeMap");
        series6.getData().add(new XYChart.Data(QUERY5, lt5));
        series6.getData().add(new XYChart.Data(QUERY9, lt9));
        
        
        // Adiciona todas as categorias ao gráfico e este à frame do programam.
        
        Scene scene  = new Scene(bc, 200, 200);
        bc.getData().addAll(series1, series2, series3, series4, 
                            series5, series6);
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
        frame.add(panel);
        frame.setVisible(true);
    }

    
    /**
     * Função de arranque e inicialização do programa.
     * 
     * @param args Argumentos.
     */
    public static void main(String[] args) {
        hipermercado = new Hipermercado(); // Inicialização do hipermercado.
        counter = 0;                       // Inicia o contador de inserções. 
        times = new ArrayList<>();         // Inicia o ArrayList de tempos
                                           // de 50000 adições.
        String[] ops = {
            "Vendas 1M.",
            "Vendas 3M.",
            "Vendas 5M."
        };
        
        Menu menu = new Menu(ops); // Inicia o menu.
        
        menu.executa("Ficheiro para efetuar as estatísticas das Queries");
        
        /* Pede ao utilizador para escolher entre os ficheiros de um 
         * milhão, três e cinco milhões de vendas. Serão testas as queries
         * 5 a 9 relativas a esse ficheiro e efetuados testes de profiling.
         */

        switch(menu.getOpcao()) {
            case 1: file = "Vendas_1M.txt";
                    break;
            case 2: file = "Vendas_3M.txt";
                    break;
            case 3: file = "Vendas_5M.txt";
                    break;
            default: System.exit(0);
        }
        
        
        /* Inicia a frame do programa. */
        frame = new JFrame("Estatísticas");
        frame.setExtendedState(JFrame.MAXIMIZED_BOTH); 
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new GridLayout(2, 3, 20, 20));
        
        /* Cria os gráficos. */
        launch(args);
    }
    
    
    /*
     * @param f Função a aplicar para se medir os tempos.
     * @return Devolve o tempo decorrido de uma certa função recebida.
     */
    private static double getTime(Function<Void, Void> f) {
        Crono.start();
        f.apply(null);
        return Crono.stop();
    } 
    
    
    /**
     * Efetua testes de profiling ao ficheiro de vendas escolhido.
     * São medidos tempos a cada 50000 adições à classe hipermercado.
     */
    private static void profiling() {
        NumberAxis xAxis = new NumberAxis();
        NumberAxis yAxis = new NumberAxis();
      
        xAxis.setLabel("Número de adições");
      
        LineChart<Number,Number> lineChart = new LineChart<>(xAxis,yAxis);
                
        lineChart.setTitle("Profiling " + file);
    
        XYChart.Series series = new XYChart.Series();
        series.setName(Integer.toString(NUM_ADD) + " adições");
        
        series.getData().add(new XYChart.Data(0, 0));
        
        /* Adiciona ao grafico os valores de todos os tempos de cada 50000
         * adições. */
        
        for (int i = 0; i < times.size(); i++) {
            series.getData()
                  .add(new XYChart.Data((i + 1) * NUM_ADD, times.get(i)));
        }
        
        
        // Adiciona o gráfico à frame. 
        Scene scene  = new Scene(lineChart, 200, 200);
        lineChart.getData().add(series);
        
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
     
        frame.add(panel);
    }
    
    
    /*
     * Calcula os tempos de leitura dos ficheiros de um, três e cinco milhões
     * sem parsing. Estes ficheiros são lidos tanto com scanner como 
     * bufferedReader
     */
    private static void leituraSemParsing() {
        CategoryAxis xAxis = new CategoryAxis();
        NumberAxis yAxis = new NumberAxis();
        BarChart<String,Number> bc = new BarChart<>(xAxis,yAxis);
        
        out.println("\nA efetuar a leitura dos ficheiros sem parsing...");
      
        // Calcula os tempos de leitura.
        double v1s = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithScanner(VENDAS_1M);
                        return null;
                    });
        
        double v1b = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithBuff(VENDAS_1M);
                        return null;
                    });
        
        double v3s = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithScanner(VENDAS_3M);
                        return null;
                    });
        
        double v3b = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithBuff(VENDAS_3M);
                        return null;
                    });
        
        double v5s = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithScanner(VENDAS_5M);
                        return null;
                    });
        
        double v5b = GereVendasEstatisticas.getTime((Void f) -> {
                        Ficheiros.readLinesWithBuff(VENDAS_5M);
                        return null;
                    });
        
        // Mostra os resultados numa tabela em modo de texto. 
        out.println("\n\t\t Vendas 1M \t Vendas 3M \t Vendas 5M");
        out.println("Scanner:  \t" + v1s + "\t" + v3s + "\t" + v5s);
        out.println("BufferedReader:\t" + v1b + "\t" + v3b + "\t" + v5b);
        
        bc.setTitle("Tempo de leitura dos ficheiros sem parsing");
        xAxis.setLabel("Ficheiros");       
        yAxis.setLabel("Tempo");
        
        // Adicona ao gráfico os valores dos tempos de leitura com scanner.
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("Scanner");
        series1.getData().add(new XYChart.Data(VENDAS_1M, v1s)); 
        series1.getData().add(new XYChart.Data(VENDAS_3M, v3s));
        series1.getData().add(new XYChart.Data(VENDAS_5M, v5s));
        
        
        // Adiciona ao gráfico os valores dos tempos de leitura com
        // bufferedReader
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("BufferedReader");
        series2.getData().add(new XYChart.Data(VENDAS_1M, v1b));
        series2.getData().add(new XYChart.Data(VENDAS_3M, v3b));
        series2.getData().add(new XYChart.Data(VENDAS_5M, v5b));
        
        Scene scene  = new Scene(bc, 200, 200);
        bc.getData().addAll(series1, series2);
        
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
     
        frame.add(panel);
    }
    
    
    /*
     * Calcula os tempos de leitura dos ficheiros de um, três e cinco milhões
     * com parsing. Estes ficheiros são lidos tanto com scanner como 
     * bufferedReader
     */
    private static void leituraComParsing() {
        CategoryAxis xAxis = new CategoryAxis();
        NumberAxis yAxis = new NumberAxis();
        BarChart<String,Number> bc = new BarChart<>(xAxis,yAxis);
        
        out.println("\nA efetuar a leitura dos ficheiros com parsing...");
        
        // Calcula os tempos de leitura.
        double v1s = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithScanner(VENDAS_1M));
                        return null;
                    });
        
        double v1b = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithBuff(VENDAS_1M));
                        return null;
                    });
        
        double v3s = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithScanner(VENDAS_3M));
                        return null;
                    });
        
        double v3b = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithBuff(VENDAS_3M));
                        return null;
                    });
        
        double v5s = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithScanner(VENDAS_5M));
                        return null;
                    });
        
        double v5b = GereVendasEstatisticas.getTime((Void f) -> {
                        GereVendasEstatisticas.parseAllLinhas(
                            Ficheiros.readLinesWithBuff(VENDAS_5M));
                        return null;
                    });
        
        // Mostra os resultados numa tabela em modo de texto. 
        out.println("\n\t\t Vendas 1M \t Vendas 3M \t Vendas 5M");
        out.println("Scanner:  \t" + v1s + "\t" + v3s + "\t" + v5s);
        out.println("BufferedReader:\t" + v1b + "\t" + v3b + "\t" + v5b);
        
        bc.setTitle("Tempo de leitura dos ficheiros com parsing");
        xAxis.setLabel("Ficheiros");       
        yAxis.setLabel("Tempo");
        
        // Adiciona ao gráfico os valores dos tempos de leitura com scanner.
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("Scanner");
        series1.getData().add(new XYChart.Data(VENDAS_1M, v1s));
        series1.getData().add(new XYChart.Data(VENDAS_3M, v3s));
        series1.getData().add(new XYChart.Data(VENDAS_5M, v5s));
        
        // Adiciona ao gráfico os valores dos tempos de leitura com
        // bufferedReader
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("BufferedReader");
        series2.getData().add(new XYChart.Data(VENDAS_1M, v1b));
        series2.getData().add(new XYChart.Data(VENDAS_3M, v3b));
        series2.getData().add(new XYChart.Data(VENDAS_5M, v5b));
            
        Scene scene  = new Scene(bc, 200, 200);
        bc.getData().addAll(series1, series2);
        
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
     
        frame.add(panel);
    }
    
    
    /*
     * Calcula os resultados das queries 6 a 8 para diferentes tipos de 
     * coleções
     */
    private static void estatisticasQueries6e8() {
        CategoryAxis xAxis = new CategoryAxis();
        NumberAxis yAxis = new NumberAxis();
        BarChart<String,Number> bc = new BarChart<>(xAxis,yAxis);
        
        out.println("\nA calcular as estatísticas para as Queries 6 e 8...\n");
        
        // Calcula os tempos das queries 6 e 8.
        double t6 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getXMaisVendidosTreeSet(5);
                        return null;
        });
        
        double h6 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getXMaisVendidosHashSet(5);
                        return null;
        });
        
        double l6 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getXMaisVendidosLinkedHashSet(5);
                        return null;
        });
        
        double t8 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getClientesMaisProdutosTreeSet(5);
                        return null;
        });
        
        double h8 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getClientesMaisProdutosHashSet(5);
                        return null;
        });
        
        double l8 = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getClientesMaisProdutosLinkedHashSet(5);
                        return null;
        });
      
        // Mostra os resultados numa tabela em modo de texto.
        out.println("  \t  TreeSet\t  HashSet\tLinkedHashSet");
        out.println("Query6: " + t6 + "\t" + h6 + "\t " + l6);
        out.println("Query8: " + t8 + "\t" + h8 + "\t " + l8);
        
        bc.setTitle("Estatísticas das Queries 6 e 8");
        xAxis.setLabel("Queries");       
        yAxis.setLabel("Tempo");
        
        // Adiciona os valores ao gráfico.
        
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("TreeSet");       
        series1.getData().add(new XYChart.Data(QUERY6, t6));
        series1.getData().add(new XYChart.Data(QUERY8, t8));
              
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("HashSet");
        series2.getData().add(new XYChart.Data(QUERY6, h6));
        series2.getData().add(new XYChart.Data(QUERY8, h8));
              
        XYChart.Series series3 = new XYChart.Series();
        series3.setName("LinkedHashSet");
        series3.getData().add(new XYChart.Data(QUERY6, l6));
        series3.getData().add(new XYChart.Data(QUERY8, l8));
             
        Scene scene  = new Scene(bc, 200, 200);
        bc.getData().addAll(series1, series2, series3);
        
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
        
        frame.add(panel);
    }
    
    
    /**
     * Calcula os resultados da query 7 para diferentes tipos de coleções.
     */
    private static void estatisticasQuery7() {
        CategoryAxis xAxis = new CategoryAxis();
        NumberAxis yAxis = new NumberAxis();
        BarChart<String,Number> bc = new BarChart<>(xAxis,yAxis);
        
        out.println("\nA calcular as estatísticas para a Query 7...\n");
        
        // Calcula os tempos da query 7 para os diferentes tipos de coleções.
        double ha = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getMaioresCompradoresHashMapArrayList();
                        return null;
        });    
        
        double hv = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getMaioresCompradoresHashMapVector();
                        return null;
        });    
        
        double ta = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getMaioresCompradoresTreeMapArrayList();
                        return null;
        });    
        
        double tv = GereVendasEstatisticas.getTime((Void f) -> {
                        hipermercado.getMaioresCompradoresTreeMapVector();
                        return null;
        });    
        
        
        // Mostra os resultados numa tabela em modo de texto.
        out.print("HashMap com ArrayList\tHashMap com Vector");
        out.println("\tTreeMap com ArrayList\tTreeMap com Vector");
        out.println(ha + "    \t\t" + hv + " \t\t" + ta + " \t\t" + tv);
        
        bc.setTitle("Estatísticas da Query 7");
        xAxis.setLabel("Query");       
        yAxis.setLabel("Tempo");
        
        // Adiciona os valores ao gráfico.
        
        XYChart.Series series1 = new XYChart.Series();
        series1.setName("HashMap com ArrayList");
        series1.getData().add(new XYChart.Data(QUERY7, ha));
        
        XYChart.Series series2 = new XYChart.Series();
        series2.setName("HashMap com Vector");
        series2.getData().add(new XYChart.Data(QUERY7, hv));
        
        XYChart.Series series3 = new XYChart.Series();
        series3.setName("TreeMap com ArrayList");
        series3.getData().add(new XYChart.Data(QUERY7, ta));
      
        XYChart.Series series4 = new XYChart.Series();
        series4.setName("TreeMap com Vector");
        series4.getData().add(new XYChart.Data(QUERY7, tv));
           
        Scene scene  = new Scene(bc, 200, 200);
        bc.getData().addAll(series1, series2, series3, series4);
        
        JFXPanel panel = new JFXPanel();
        panel.setScene(scene);
        
        frame.add(panel);
    }
}
