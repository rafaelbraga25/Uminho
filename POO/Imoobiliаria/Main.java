
/**
 * Classe responsável pelo controlo total da aplicação.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

import static java.lang.System.out;

import ImoobiliariaExceptions.*;

import java.io.ObjectInputStream;
import java.io.FileInputStream;
import java.io.IOException;

import java.util.GregorianCalendar;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.stream.Collectors;
import java.text.SimpleDateFormat;

public class Main {
    
    // Variáveis de classe
    
    private static String file = "imoobiliaria.dat"; // Valor por defeito do ficheiro objeto.
    private static Imoobiliaria im;                  // Instância da classe Imoobiliaria.
    private static Menu menuMain;                    
    private static Menu menuUtilizador;              
    private static Menu menuComprador;               
    private static Menu menuVendedor;                
    private static Menu menuLeilao;                  
    
  
    // Métodos de classe
    
    /**
     * @brief Inicia a aplicação lendo o ficheiro objeto.
     */
    public static Imoobiliaria initApp() {
      
        try {
            ObjectInputStream oin = new ObjectInputStream(new FileInputStream(file));
            im = (Imoobiliaria) oin.readObject();
            oin.close();
        }
        catch (IOException e) {
            im = new Imoobiliaria();
            System.out.println("Erro ao ler os dados!\nErro de leitura\n.");
        } 
        catch (ClassNotFoundException e) {
            im = new Imoobiliaria();
            out.println("Erro ao ler os dados!\nFicheiro com formato desconhecido\n.");
        }
        catch (ClassCastException e) {
            im = new Imoobiliaria();
            out.println("Erro ao ler os dados!\nErro de formato\n.");        
        }
  
        return im;
    }
    
    /**
     * @brief Inicia os diferentes menus da aplicação.
     */
    public static void initMenus() {
        String[] mainOps = { "Registar.",
                             "Login.",
                             "Entrar anonimamente." };
                             
        String[] compradorOps = { "Pesquisar imóveis.",
                                  "Adicionar imóvel aos imóveis favoritos.", 
                                  "Consultar imóveis favoritos.",
                                  "Consultar catálogo de imóveis e respetivos vendedores." };
                                  
        String[] vendedorOps = { "Registar imóvel.",
                                 "Obter as 10 últimas consultas dos imóveis em venda.",
                                 "Alterar estado de um imóvel.",
                                 "Obter lista dos imóveis mais consultados.",
                                 "Pesquisar imóvel.",
                                 "Consultar catálogo de imóveis e respetivos vendedores.", 
                                 "Consultar o portfólio de imóveis em venda.",
                                 "Consultar o histórico de imóveis vendidos.",
                                 "Iniciar leilão." };
                                  
        String[] utilizadorOps = { "Pesquisar imóveis.",
                                   "Consultar catálogo de imóveis e respetivos vendedores." };
                               
        String[] leilaoOps = { "Adicionar comprador.",
                               "Terminar Leilao e mostrar resultados." };
                               
        menuMain = new Menu(mainOps);
        menuUtilizador = new Menu(utilizadorOps);
        menuComprador = new Menu(compradorOps);
        menuVendedor = new Menu(vendedorOps);
        menuLeilao = new Menu(leilaoOps);
    }
    
    /**
     * @brief Carrega o ficheiro objeto com todos os dados e mostra o menu principal da aplicação.
     * 
     * Primeiro inicia a aplicação. Caso tenha recebido um argumento altera o nome do ficheiro objeto para esse valor.
     * No final da execução da aplicação guarda todos os dados no ficheiro objeto.
     * 
     * @param args Argumentos de execução do programa.
     */
    public static void main(String[] args) {
        if (args.length > 0) {
            Main.setFile(args[0]);
        }
        
        im = Main.initApp();
        Main.initMenus();
        Main.clearTerminal();
        
        do {
           
            menuMain.executa("Imoobiliária");
            
            switch (menuMain.getOpcao()) {
                case 1 : Main.registar();
                         break;
                case 2 : Main.login();
                         break;
                case 3 : Main.sessaoAnonima();
            }
            
        } while (menuMain.getOpcao() != 0);
        
        Main.save();
    }
    
    /**
     * Guarda o estado da aplicação no ficheiro objeto.
     */
    public static void save() {
        try {
            im.gravaObj(file);
        }
        catch (IOException e) {
            out.println("Erro ao gravar os dados no ficheiro " + file + "!");
        }
    }
    
    
    // Métodos do menu principal
    
    /**
     * @brief Método responsável pela exibição dos passos necessários para o registo de um utilizador na aplicação.
     */
    public static void registar() {
        String email = "";
        String nome = "";
        String password = "";
        String morada = "";
        GregorianCalendar data = null;
        boolean ok = false;
        int op = 0;
        
        Main.clearTerminal();
        
        while (!ok) {
            out.print("Email: ");
            email = Input.lerString("Email inválido!", "Email: ");
            
            if (im.containsUser(email)) {
                out.println("O email já existe!");
            }
            else {
                ok = true;
            }
        }
        
        out.print("Nome: ");
        nome = Input.lerString("Nome inválido!", "Nome: ");
        
        out.print("Password: ");
        password = Input.lerString("Password inválida!", "Password: ");
        
        out.print("Morada: ");
        morada = Input.lerString("Morada inválida!", "Morada: ");
        
        out.print("Data de nascimento (dd-mm-aaaa): ");
        data = Input.lerData("Data inválida. Tente novamente.", "Data de nascimento (dd-mm-aaaa): "); 
        
        op = Main.getIntInterval(1, 2, "1 - Vendedor.\n2 - Comprador.\nTipo de utilizador: ", 
                                 "Tipo inválido. Tente novamente");
        
        switch (op) {
            case 1 : Main.registarVendedor(email, nome, password, morada, data);
                     break;
            case 2 : Main.registarComprador(email, nome, password, morada, data);
        }
    }
    
    /**
     * @brief Método responsável pelo registo de um vendedor na aplicação.
     * 
     * Cria-se uma nova instância da classe Vendedor cujos campos correspondem aos valores recebidos como parâmetro.
     * Chama-se a função que regista um comprador e é tratada a exceção que ocorre quando se tenta registar um
     * vendedor que já exista.
     * 
     * @param email    Email do vendedor.
     * @param nome     Nome do vendedor.
     * @param password Password do vendedor.
     * @param morada   Morada do vendedor.
     * @param data     Data de nascimento do vendedor.
     */
    public static void registarVendedor(String email, String nome, String password, String morada,
                                        GregorianCalendar data) {
                                            
        Vendedor v = new Vendedor(email, nome, password, morada, data);
                                            
        try {
            im.registarUtilizador(v);
            Main.save();
        }
        catch (UtilizadorExistenteException e) {
            out.println("O utilizador já está registado!\n\n\n");
        }
        
    }
    
    /**
     * @brief Método responsável pelo registo de um comprador na aplicação.
     * 
     * Primeiro pede-se ao comprador as informações relativas à participação nos leilões, exibindo-lhe a opção de
     * participar ou não. Caso o comprador afirme querer participar, são-lhe pedidos os dados como o valor máximo
     * que pretende gastar num leilão, os incrementos das licitações e o tempo entre esses mesmos incrementos. De
     * seguida, cria-se uma nova instância da classe Comprador cujos campos correspondem aos valores recebidos como 
     * parâmetro. Chama-se a função que regista um comprador e é tratada a exceção que ocorre quando se tenta 
     * registar um comprador que já exista.
     * 
     * @param email    Email do comprador.
     * @param nome     Nome do comprador.
     * @param password Password do comprador.
     * @param morada   Morada do comprador.
     * @param data     Data de nascimento do comprador.
     */    
    public static void registarComprador(String email, String nome, String password, String morada,
                                         GregorianCalendar data) {
        
        boolean participa = false;
        String p = "";
        double limite = 0;
        double incrementos = 0;
        double duracao = 0;
        Comprador c = null;
        
        p = Main.getSNString("Deseja participar em leilões? (S/N): ", "Opção inválida. Tente novamente");
        
        participa = (p.equals("s") || p.equals("S")) ? true : false;
        
        if (participa) {
            out.print("Valor máximo que pretende gastar num leilão: ");
            limite = Input.lerDouble("Valor inválido!", "Valor máximo que pretende gastar num leilão: ");
            
            out.print("Valor dos incrementos de um leilão: ");
            incrementos = Input.lerDouble("Valor inválido!", "Valor dos incrementos de um leilão: ");
            
            out.print("Tempo de duração entre incrementos: ");
            duracao = Input.lerDouble("Valor inválido!", "Tempo de duração entre incrementos: ");
        }
        
        c = new Comprador(email, nome, password, morada, data, participa, limite, incrementos, duracao);
        
        try {
            im.registarUtilizador(c);
            Main.save();
        }
        catch (UtilizadorExistenteException e) {
            out.println("O utilizador já está registado!\n\n\n");
        }
    }
    
    /**
     * @brief Método responsável pela exibição das informações que permitem a um utilizador autenticar-se na aplicação.
     * 
     * Primeiro pede-se e verifica-se o email e a password do utilizador. Caso o login esteja correto, verifica-se se
     * se trata de um vendedor ou de um comprador e chama-se a função respetiva para iniciar sessão. É ainda lançada
     * a exceção SemAutorizacao caso o utilizador não esteja registado ou se as credencias estiverem erradas.
     */
    public static void login() {
        String email = "";
        String password = "";
        
        Main.clearTerminal();
        
        out.print("Email: ");
        email = Input.lerString("Email inválido!", "Email: ");
            
        out.print("Password: ");
        password = Input.lerString("Password inválida!", "Password: ");
            
        try {
            im.iniciaSessao(email, password);
          
            if (im.getUtilizador() instanceof Vendedor) {
                Main.sessaoVendedor();
            }
            else {
                Main.sessaoComprador();
            }
        }
        catch (SemAutorizacaoException e) {
            out.println("O utilizador não está registado ou a password está incorreta!");
        }
    }
    
    /**
     * @brief Método responsável pela exibição das informações relativas às funcionalidaes ao dispor de um qualquer
     *        vendedor.
     */
    public static void sessaoVendedor() {
        Main.clearTerminal();
        
        do {
            menuVendedor.executa("Menu de Vendedor");
            
            switch (menuVendedor.getOpcao()) {
                case 1 : Main.registarImovel();
                         break;
                case 2 : Main.getConsultas();
                         break;
                case 3 : Main.setEstado();
                         break;
                case 4 : Main.getTopImoveis();
                         break;
                case 5 : Main.pesquisarImoveis();
                         break;
                case 6 : Main.mapeamentoImoveis();
                         break;
                case 7 : Main.portfolioImoveis();
                         break;
                case 8 : Main.historicoImoveis();
                         break;
                case 9 : Main.leilao();
            }
            
        } while (menuVendedor.getOpcao() != 0);
        
        im.fechaSessao();
    }
    
    /**
     * @brief Método responsável pela exibição das informações relativas às funcionalidaes ao dispor de um qualquer
     *        comprador.
     */
    public static void sessaoComprador() {
        Main.clearTerminal();
        
        do {
            menuComprador.executa("Menu de Comprador");
            
            switch (menuComprador.getOpcao()) {
                case 1 : Main.pesquisarImoveis();
                         break;
                case 2 : Main.adicionarImovelFavorito();
                         break;
                case 3 : Main.imoveisFavoritos();
                         break;
                case 4 : Main.mapeamentoImoveis();
            }
            
        } while (menuComprador.getOpcao() != 0);
        
        im.fechaSessao();
    }
    
    /**
     * @brief Método responsável pela exibição das informações relativas às funcionalidaes ao dispor de um qualquer
     * utilizador não registado.
     */
    public static void sessaoAnonima() {
        Main.clearTerminal();
        
        do {
            menuUtilizador.executa("Sessão Anónima");
            
            switch (menuUtilizador.getOpcao()) {
                case 1 : Main.pesquisarImoveis();
                         break;
                case 2 : Main.mapeamentoImoveis();
            }
            
        } while (menuUtilizador.getOpcao() != 0);
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos do imóvel que prentede registar. De seguida, regista-se
     * o imóvel de acordo com o tipo explicitado. Por fim, são tratadas as exceções relativas à inserção de imóveis
     * apenas por vendedores registados e de imóveis que ainda não existam na aplicação.
     */
    public static void registarImovel() {
        String id = "";
        String rua = "";
        double preco = 0;
        double precoMin = 0;
        int tipo = 0;
        Imovel i = null;
        
        out.print("Id do imóvel: ");
        id = Input.lerString("Id inválido!", "Id do imóvel: ");
        
        out.print("Rua: ");
        rua = Input.lerString("Rua inválida!", "Rua: ");
        
        preco = Main.getDoubleInterval(1, "Preço: ", "Valor inválido. Tente novemente.");
        precoMin = Main.getDoubleInterval(1, "Preço mínimo: ", "Valor inválido. Tente novemente.");
        
        out.print("1 - Moradia.\n2 - Apartamento.\n");
        out.print("3 - Loja.\n4 - Loja habitável.\n5 - Terreno.\n");
        
        tipo = Main.getIntInterval(1, 5, "Tipo de imóvel: ", "Tipo inválido. Tente novamente.");
    
        switch (tipo) {
            case 1 : i = Main.registarMoradia(id, rua, preco, precoMin);
                     break;
            case 2 : i = Main.registarApartamento(id, rua, preco, precoMin);
                     break;
            case 3 : i = Main.registarLoja(id, rua, preco, precoMin);
                     break;
            case 4 : i = Main.registarLojaHabitavel(id, rua, preco, precoMin);
                     break;
            case 5 : i = Main.registarTerreno(id, rua, preco, precoMin); 
        }
        
        try {
            im.registaImovel(i);
            Main.save();
        }
        catch (SemAutorizacaoException e) {
            out.println("Apenas vendedores registados podem inserir imóveis!");
        }
        catch (ImovelExisteException e) {
            out.println("O imóvel já se encontra registado.");
        }
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel da classe Moradia na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos da moradia que prentede registar exibindo-se as opções
     * possíveis para os tipos e sendo tratados os casos em que se insiram valores inválidos. Por fim, cria-se uma
     * nova entidade da classe Moradia cujos campos correspondem aos passados como parâmetro (os comuns à superclasse
     * Imovel) e respondidos pelo utilizador (os específicos à classe Moradia). Por fim, é devolvida esta nova moradia.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     * @return m       Nova instância criada da classe Moradia.
     */
    public static Imovel registarMoradia(String id, String rua, double preco, double precoMin) {
        Moradia.TipoMoradia[] tipos = Moradia.TipoMoradia.values();
        int tIndex = 0;
        double areaIm = 0;
        double areaTotal = 0;
        double areaTerreno = 0;
        int numQuartos = 0;
        int numWCs = 0;
        int numPorta = 0;
        Moradia m = null;
        
        for (Moradia.TipoMoradia t : tipos) {
            out.printf("%d - %s\n", t.ordinal() + 1, t.name());
        }
        
        tIndex = Main.getIntInterval(1, tipos.length, "Tipo de moradia: ", "Tipo inválido. Tente novamente.");
        areaIm = Main.getDoubleInterval(1, "Área de implantação: ", "Valor inválido. Tente novamente"); 
        areaTotal = Main.getDoubleInterval(1, "Área total: ", "Valor inválido. Tente novamente"); 
        areaTerreno = Main.getDoubleInterval(1, "Área do terreno: ", "Valor inválido. Tente novamente"); 
        numQuartos = Main.getIntInterval(1, "Nº de quartos: ", "Valor inválido. Tente novamente"); 
        numWCs = Main.getIntInterval(1, "Nº de WCs: ", "Valor inválido. Tente novamente"); 
        numPorta = Main.getIntInterval(1, "Nº de porta: ", "Valor inválido. Tente novamente"); 
        
        m = new Moradia(id, rua, preco, precoMin, tipos[tIndex - 1], areaIm, areaTotal, areaTerreno, 
                        numQuartos, numWCs, numPorta);
                        
        return m;
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel da classe Apartamento na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos do apartamento que prentede registar, exibindo-se as 
     * opções possíveis para os tipos e sendo tratados os casos em que se insiram valores inválidos. Por fim, 
     * cria-se uma nova entidade da classe Apartamento cujos campos correspondem aos passados como parâmetro
     * (os comuns à superclasse Imovel) e respondidos pelo utilizador (os específicos à classe Apartamento).
     * Por fim, é devolvido este novo apartamento.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     * @return m       Nova instância criada da classe Moradia.
     */    
    public static Imovel registarApartamento(String id, String rua, double preco, double precoMin) {
        Apartamento.TipoApartamento[] tipos = Apartamento.TipoApartamento.values();
        int tIndex = 0;
        double areaTotal = 0;
        int numQuartos = 0;
        int numWCs = 0;
        int numPorta = 0;
        int numAndar = 0;
        String possui = "";
        boolean possuiGaragem = false;
        Apartamento a = null;
        
        for (Apartamento.TipoApartamento t : tipos) {
            out.printf("%d - %s\n", t.ordinal() + 1, t.name());
        }
        
        tIndex = Main.getIntInterval(1, tipos.length, "Tipo de apartamento: ", "Tipo inválido. Tente novamente.");
        areaTotal = Main.getDoubleInterval(1, "Área total: ", "Valor inválido. Tente novamente");  
        numQuartos = Main.getIntInterval(1, "Nº de quartos: ", "Valor inválido. Tente novamente"); 
        numWCs = Main.getIntInterval(1, "Nº de WCs: ", "Valor inválido. Tente novamente"); 
        numPorta = Main.getIntInterval(1, "Nº de porta: ", "Valor inválido. Tente novamente"); 
        numAndar = Main.getIntInterval(1, "Nº do andar: ", "Valor inválido. Tente novamente"); 
        
        possui = Main.getSNString("Possui garagem? (S/N): ", "Valor inválido. Tente novamente.");
        possuiGaragem = (possui.equals("S") || possui.equals("s")) ? true : false;
        
        a = new Apartamento(id, rua, preco, precoMin, tipos[tIndex - 1], areaTotal, numQuartos, numWCs, 
                            numPorta, numAndar, possuiGaragem);
                        
        return a;
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel da classe Loja na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos da loja que prentede registar, exibindo-se as opções 
     * possíveis para os tipos de negócio e sendo tratados os casos em que se insiram valores inválidos. Por fim, 
     * cria-se uma nova entidade da classe Loja cujos campos correspondem aos passados como parâmetro (os comuns 
     * à superclasse Imovel) e respondidos pelo utilizador (os específicos à classe Loja). Por fim, é devolvida 
     * esta nova loja.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     * @return m       Nova instância criada da classe Moradia.
     */    
    public static Imovel registarLoja(String id, String rua, double preco, double precoMin) {
        double area = 0;
        boolean possuiWC = false;
        String tipo = "";
        String possui = "";
        int numPorta = 0;
        Loja l = null;
        
        area = Main.getDoubleInterval(1, "Área da loja: ", "Valor inválido. Tente novamente"); 
        
        possui = Main.getSNString("Possui WC? (S/N): ", "Valor inválido. Tente novamente.");
        possuiWC = (possui.equals("S") || possui.equals("s")) ? true : false;
        
        out.print("Tipo de negócio da loja: ");
        tipo = Input.lerString("Negócio inválido!", "Tipo de negócio da loja: ");
        
        numPorta = Main.getIntInterval(1, "Nº de porta: ", "Valor inválido. Tente novamente"); 
        
        l = new Loja(id, rua, preco, precoMin, area, possuiWC, tipo, numPorta);
                        
        return l;
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel da classe LojaHabitavel na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos da loja habitável que prentede registar, exibindo-se as 
     * opções possíveis para os tipos de negócio e sendo tratados os casos em que se insiram valores inválidos. Por 
     * fim, cria-se uma nova entidade da classe LojaHabitavel cujos campos correspondem aos passados como parâmetro
     * (os comuns à superclasse Imovel) e respondidos pelo utilizador (os específicos à classe LojaHabitavel). Por 
     * fim, é devolvida esta nova loja habitável.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     * @return m       Nova instância criada da classe Moradia.
     */     
    public static Imovel registarLojaHabitavel(String id, String rua, double preco, double precoMin) {
        double area = 0;
        boolean possuiWC = false;
        String possui = "";
        String tipo = "";
        int numPorta = 0;
        Apartamento.TipoApartamento[] tipos = Apartamento.TipoApartamento.values();
        int tIndex = 0;
        double areaAp = 0;
        int numQuartos = 0;
        int numWCs = 0;
        int numAndar = 0;
        boolean possuiGaragem = false;
        
        LojaHabitavel l = null;
        
        area = Main.getDoubleInterval(1, "Área da loja: ", "Valor inválido. Tente novamente");
        
        possui = Main.getSNString("Possui WC? (S/N): ", "Valor inválido. Tente novamente.");
        possuiWC = (possui.equals("S") || possui.equals("s")) ? true : false;
        
        out.print("Tipo de negócio da loja: ");
        tipo = Input.lerString("Negócio inválido!", "Tipo de negócio da loja: ");
        
        numPorta = Main.getIntInterval(1, "Nº de porta: ", "Valor inválido. Tente novamente");
        
        for (Apartamento.TipoApartamento t : tipos) {
            out.printf("%d - %s\n", t.ordinal() + 1, t.name());
        }
        
        tIndex = Main.getIntInterval(1, tipos.length, "Tipo de apartamento: ", "Tipo inválido. Tente novamente.");
        areaAp = Main.getDoubleInterval(1, "Área do apartamento: ", "Valor inválido. Tente novamente");
        numQuartos = Main.getIntInterval(1, "Nº de quartos: ", "Valor inválido. Tente novamente"); 
        numWCs = Main.getIntInterval(1, "Nº de WCs: ", "Valor inválido. Tente novamente"); 
        numAndar = Main.getIntInterval(1, "Nº do andar: ", "Valor inválido. Tente novamente"); 
        
        possui = Main.getSNString("Possui garagem? (S/N): ", "Valor inválido. Tente novamente.");
        possuiGaragem = (possui.equals("S") || possui.equals("s")) ? true : false;
        
        l = new LojaHabitavel(id, rua, preco, precoMin, area, possuiWC, tipo, numPorta, tipos[tIndex - 1],
                              areaAp, numQuartos, numWCs, numAndar, possuiGaragem);
                        
        return l;
    }
    
    /**
     * @brief Método responsável pelo registo de um imóvel da classe Terreno na aplicação.
     * 
     * Primeiro, pede-se ao utilizador que insira os campos do terreno que prentede registar, exibindo-se as 
     * opções possíveis para os tipos e sendo tratados os casos em que se insiram valores inválidos. Por fim, 
     * cria-se uma nova entidade da classe Terreno cujos campos correspondem aos passados como parâmetro (os 
     * comuns à superclasse Imovel) e respondidos pelo utilizador (os específicos à classe Terreno). Por fim,
     * é devolvido este novo terreno.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     * @return m       Nova instância criada da classe Moradia.
     */     
    public static Imovel registarTerreno(String id, String rua, double preco, double precoMin) {
        Terreno.TipoTerreno[] tipos = Terreno.TipoTerreno.values();
        int tIndex = 0;
        double diametro = 0;
        double kWh = 0;
        boolean existeAcesso = false;
        String existe = "";
        Terreno t = null;
        
        for (Terreno.TipoTerreno tp : tipos) {
            out.printf("%d - %s\n", tp.ordinal() + 1, tp.name());
        }
        
        tIndex = Main.getIntInterval(1, tipos.length, "Tipo de terreno: ", "Tipo inválido. Tente novamente.");
        diametro = Main.getDoubleInterval(1, "Diâmetro das canalizações: ", "Valor inválido. Tente novamente");
        kWh = Main.getDoubleInterval(1, "KWh suportados pela rede eléctrica: ",
                                     "Valor inválido. Tente novamente");
        
        existe = Main.getSNString("Existe acesso à rede de esgotos? (S/N): ", "Valor inválido. Tente novamente.");
        existeAcesso = (existe.equals("S") || existe.equals("s")) ? true : false;
        
        t = new Terreno(id, rua, preco, precoMin, tipos[tIndex - 1], diametro, kWh, existeAcesso); 
      
        return t;
    }
    
    /**
     * @brief Método responsável pela exibição da lista das consultas a um vendedor registado dos imóveis que tem
     *        para venda.
     * 
     * Primeiro acede-se à lista de consultas dos imóveis que o vendedor tem para venda. Fazendo-se o tratamento
     * da exceção SemAutorizacao que ocorre quando não é um vendedor a aceder a esta funcionalidade. De seguida,
     * são exibidas sequencialmente estas mesmas consultas, sendo formatadas de forma ilustrativa.
     */
    public static void getConsultas() {
        ArrayList<Consulta> cs = null;
        ArrayList<String> lst = null;
        SimpleDateFormat f = new SimpleDateFormat("dd-MM-yyyy HH:mm");
        
        Main.clearTerminal();
        
        try {
            cs = (ArrayList<Consulta>) im.getConsultas();
            lst = new ArrayList<>();
            
            for (Consulta c : cs) {
                StringBuilder sb = new StringBuilder();
                
                f.setTimeZone(c.getData().getTimeZone());
                
                sb.append("Email: " + c.getEmail());
                sb.append(" ---- Data: " + f.format(c.getData().getTime()));
                sb.append("\n-------------------------------------------------\n");
                
                lst.add(sb.toString());
            }
            
            lst.forEach(s -> out.print(s));
        }
        catch (SemAutorizacaoException e) {
            out.println("Só vendedores registados é que podem obter as consultas dos seus imóveis!");
        }
    }
    
    /**
     * @brief Método responsável pela alteração do estado de um imóvel.
     * 
     * Primeiro pergunta-se ao utilizador qual o código de identificação do imóvel a que se pretende alterar o
     * estado e para que estado se pretende alterar. Faz-se o tratamento das exceções relativas à falta de
     * autorização para aceder a esta funcionalidade, à não existência do imóvel e à inserção de um estado
     * inválido.
     */
    public static void setEstado() {
        String idImovel = "";
        String estado = "";
        int op = 0;
        
        Main.clearTerminal();
        
        out.print("Id do imóvel : ");
        idImovel = Input.lerString("Id inválido!", "Id do imóvel: ");
        
        out.print("1- Em venda.\n2 - Reservado.\n3 - Vendido\n");
        op = Main.getIntInterval(1, 3, "Estado: ", "Estado inválido. Tente novamente.");
        
        switch (op) {
            case 1 : estado = Imovel.emVenda;
                     break;
            case 2 : estado = Imovel.reservado;
                     break;
            case 3 : estado = Imovel.vendido;
        }
        
        try {
            im.setEstado(idImovel, estado);
            Main.save();
        }
        catch (SemAutorizacaoException e) {
            out.println("Não tem autorização para alterar o estado de um imóvel!");
        }
        catch (ImovelInexistenteException e) {
            out.println("O imóvel não existe!");
        }
        catch (EstadoInvalidoException e) {
            out.println("O estado introduzido não é válido.");
        }
    }
    
    /**
     * @brief Método responsável pela exibição e obtenção de informações relativas à possibilidade de um vendedor
     *        visualizar os imóveis que tem em venda e que têm mais que n consultas.
     *        
     * Primeiro pergunta-se qual o limite mínimo de consultas que têm de ter os imóveis para serem exibidos,
     * fazendo-se o tratamento dos casos em que o valor inserido é inválido. Chama-se o método getTopImoveis() 
     * da classe Imoobiliaria, exibem-se os códigos dos imóveis resultantes, recorrendo-se ao método Paginacao.
     */
    public static void getTopImoveis() {
        int n = 0;
        HashSet<String> set = null;
        ArrayList<String> lst = new ArrayList<>();
        
        Main.clearTerminal();
        
        n = Main.getIntInterval(0, "Número de consultas: ", "Valor inválido. Tente novamente.");
        
        set = (HashSet<String>) im.getTopImoveis(n);
        
        set.forEach(s -> lst.add("Código do imóvel: " + s));
        
        Main.paginacao(lst, "Imóveis "); 
    }
    
    /**
     * @brief Método responsável pela exibição e obtenção de informações relativas à possibilidade de um
     *        qualquer utilizador pesquisar um imóvel.
     *        
     * Primeiro pergunta-se qual o tipo de imóvel que o utilizador pretende pesquisar e o preço do mesmo. Faz-se o
     * tratamento dos casos em que se inserem valores inválidos e efetua-se a pesquisa correspondente aos dados
     * inseridos. Por fim, são convertidos os imóveis resultantes da pesquisa numa lista de strings que é utilizada
     * pelo metodo Paginacao para exibir ao utilizador.
     */
    public static void pesquisarImoveis() {
        int preco = 0;
        ArrayList<Imovel> imoveis = null;
        ArrayList<String> lst = null;
        int tipo = 0;
        String aux = "1 - Moradia.\n2 - Apartamento.\n3 - Loja.\n4 - Loja Habitável.\n5 - Terreno.\n6 - Habitável.\nTipo : ";
        
        Main.clearTerminal();
        
        out.print("Preço pretendido: ");
        preco = Input.lerInt("Valor inválido!", "Preço pretendido: ");
       
        tipo = Main.getIntInterval(1, 6, aux, "Tipo inválido. Tente novamente");
            
        switch (tipo) {
            case 1 : imoveis = (ArrayList<Imovel>) im.getImovel("Moradia", preco);
                     break;
            case 2 : imoveis = (ArrayList<Imovel>) im.getImovel("Apartamento", preco);
                     break;
            case 3 : imoveis = (ArrayList<Imovel>) im.getImovel("Loja", preco);
                     break;
            case 4 : imoveis = (ArrayList<Imovel>) im.getImovel("LojaHabitavel", preco);
                     break;
            case 5 : imoveis = (ArrayList<Imovel>) im.getImovel("Terreno", preco);
                     break;
            case 6 : imoveis = (ArrayList<Imovel>) im.getHabitaveis(preco);
                     break;
        }
      
        lst = Main.toImovelStringList(imoveis);
        Main.paginacao(lst, "Imóveis ");
        Main.save();
    }
    
    /**
     * Obtém o mapeamento entre os imóveis e os respetivos vendedores e converte-os numa lista de strings.
     */
    public static void mapeamentoImoveis() {
        HashMap<Imovel, Vendedor > map = (HashMap<Imovel, Vendedor>) im.getMapeamentoImoveis();
        ArrayList<String> lst = Main.toMapeamentoStringList(map);
        
        Main.paginacao(lst, "Mapeamentos ");
    }
    
    /**
     * Obtém a lista de imóveis em venda de um vendedor e converte-os numa lista de strings.
     */
    public static void portfolioImoveis() {
        ArrayList<Imovel> imoveis = null;
        ArrayList<String> lst = null;
        
        Vendedor v = (Vendedor) im.getUtilizador();
        
        if (v != null) {
            imoveis = (ArrayList<Imovel>) v.getPortfolio();
            lst = Main.toImovelStringList(imoveis);
            
            Main.paginacao(lst, "Imóveis ");
        }
    }
    
    /**
     * Obtém a lista de imóveis vendidos de um vendedor e converte-os numa lista de strings.
     */    
    public static void historicoImoveis() {
        ArrayList<Imovel> imoveis = null;
        ArrayList<String> lst = null;
        
        Vendedor v = (Vendedor) im.getUtilizador();
        
        if (v != null) {
            imoveis = (ArrayList<Imovel>) v.getHistorico();
            lst = Main.toImovelStringList(imoveis);
            
            Main.paginacao(lst, "Imóveis ");
        }
    }
    
    /**
     * @brief Método responsável pela exibição e inserção das informações relativas à possibilidade dos compradores
     *        de adicionarem um imóvel à sua lista de favoritos.
     *        
     * Primeiro pede-se o código de identificação do imóvel que o utilizador pretende adicionar aos favoritos e
     * faz-se o tratamentos do caso em que se insira um código inválido. Por fim, tenta-se inserir o imóvel à lista
     * de favoritos do comprados, fazendo o tratamento das exceções que ocorrem quando algum utilizador que não um
     * comprador registado tenta aceder a esta funcionalidade ou quando se tenta adicionar aos favoritos um imóvel
     * que não exista na aplicação.
     */
    public static void adicionarImovelFavorito() {
        String idImovel = "";
        
        Main.clearTerminal();
        out.print("Id do imóvel: ");
        idImovel = Input.lerString("Id inválido!", "Id do imóvel: ");
        
        try {
            im.setFavorito(idImovel);
            Main.save();
        }
        catch (SemAutorizacaoException e) {
            out.println("Só os compradores registados é que podem marcar imóveis como favoritos!");
        }
        catch (ImovelInexistenteException e) {
            out.println("O imóvel não existe!");
        }
    }
    
    /**
     * Obtém a lista de imóveis favoritos de um comprador e converte-os numa lista de strings.
     */ 
    public static void imoveisFavoritos() {
        TreeSet<Imovel> fav = null;
        ArrayList<Imovel> imoveis = new ArrayList<>();
        ArrayList<String> lst = null;
        
        Main.clearTerminal();
        
        try {
            fav = (TreeSet<Imovel>) im.getFavoritos();
            
            fav.forEach(i -> imoveis.add(i));
            
            lst = Main.toImovelStringList(imoveis);
            
            Main.paginacao(lst, "Imóveis ");
        }
        catch (SemAutorizacaoException e) {
            out.println("Só pode criar leilões dos seus imóveis para venda!");
        }
    }
    
    /**
     * @brief Método responsável pela exibição e inserção das informações necessárias para o início de um leilão.
     * 
     * Primeiro pergunta-se ao utilizador o código de identificação do imóvel que se pretende leiloar, tratando-se
     * dos casos em que se insere um código errado ou inválido. De seguida, pede-se a duração do leilão. Tenta-se
     * depois iniciar o leilão chamando-se a função respetiva e tratando-se do exceção que ocorre quando algum
     * utilizador que não um vendedor registado tenta aceder a esta funcionalidade. Depois, é exibido o menu dos
     * leilões que permite ao vendedor inserir um comprador ou encerrar o leilão e obter o vencedor.
     */
    public static void leilao() {
        String idImovel = "";
        int duracao = 0;
        Imovel i = null;
        boolean ok = false;
        
        Main.clearTerminal(); 
       
        do {
            out.print("Id do imóvel para o leilão: ");
            idImovel = Input.lerString("Id inválido!", "Id do imóvel para o leilão: ");
            
            try {
                i = im.getImovelById(idImovel);
                ok = true;
            }
            catch (NullPointerException e) {
                out.println("Imóvel inválido. Tente novamente.");
            }
            
        } while(!ok);
        
        
        duracao = Main.getIntInterval(1, "Duração do leilão: ", "Valor inválido. Tente novamente.");
        
        try {
            im.iniciaLeilao(i, duracao);
        }
        catch (SemAutorizacaoException e) {
            out.println("Não tem autorização para leiloar esse imóvel!");
            return;
        }
        
        do {
            menuLeilao.executa("Leilão");
            
            switch (menuLeilao.getOpcao()) {
                case 1 : Main.insereCompradorLeilao();
                         break;
                case 2 : Main.vencedorLeilao();
            } 
        } while (menuLeilao.getOpcao() != 0 && menuLeilao.getOpcao() != 2);
        
        if (menuLeilao.getOpcao() == 0) {
            try {
                im.encerraLeilao();
            }
            catch (LeilaoTerminadoException | SemAutorizacaoException e) {
                out.println("O leilao já terminou...");
            }
        }
    }
    
    /**
     * @brief Método que permite a inserção de um comprador num leilão.
     * 
     * Primeiro pede-se ao utilizador que insira os dados do comprador que se pretende inserir ao leilão, tratando-se
     * os casos em que são inseridos valores inválidos. De seguida, tenta-se chamar a função que adiciona um comprador,
     * tratando-se das exceções que ocorrem quando o leilão em causa já terminou ou quando o utilizador é alguém que não
     * um vendedor registado.
     */
    public static void insereCompradorLeilao() {
        String idComprador = "";
        double limite = 0;
        double incrementos = 0;
        double minutos = 0;
        
        out.print("Email do comprador: ");
        idComprador = Input.lerString("Email inválido!", "Email do comprador: ");
        
        limite = Main.getDoubleInterval(1, "Valor máximo que o comprador pretente gastar num leilão.",
                                        "Valor inválido. Tente novamente.");
                                        
        incrementos = Main.getDoubleInterval(1, "Valor máximo que o comprador pretente gastar num leilão.",
                                             "Valor inválido. Tente novamente.");
                                        
        minutos = Main.getDoubleInterval(1, "Tempo de duração entre incrementos",
                                         "Valor inválido. Tente novamente.");
     
        try {
            im.adicionaComprador(idComprador, limite, incrementos, minutos);
        }
        catch (LeilaoTerminadoException e) {
            out.println("Não existem leilões disponíveis neste momento...");
        }
        catch (SemAutorizacaoException e) {
            out.println("Só vendedores registados podem adicionar compradores a leilões!");
        }
    }
    
    /**
     * Imprime as diferentes licitações e determina, caso exista, o comprador vencedor.
     */
    public static void vencedorLeilao() {
        Leilao l = im.getLeilao();
        HashMap<Comprador, Double> montantes = null;
        
        Main.clearTerminal();
        
        if (l != null) {
            out.print("Resultados do leilão!\n\nImóvel: ");
            out.print(l.getImovel().getId() + " - " + l.getImovel().getPrecoMin() + " euros.\n");
            
            montantes = (HashMap<Comprador, Double>) l.getMontantes();
            
            out.println("\nCompradores e suas propostas: ");
            montantes.forEach((k, v) -> out.print(k.getEmail() + " - " + v + " euros.\n"));
            
            try {
                Comprador c = im.encerraLeilao();
                
                if (c != null) {
                    out.println("\n\n------------- Vencedor -------------");
                    out.println("Email: " + c.getEmail() + "\nNome: " + c.getNome());
                }
                else {
                    out.println("O imóvel não foi reservado...");
                }
            }
            catch (SemAutorizacaoException | LeilaoTerminadoException e) {
                out.println("O leilao já terminou...");
            }
        }
    }
    
    
    // Métodos privados
    
    private Main() { }
    
    /**
     * @return Devolve uma representação textual da classe Imovel.
     */    
    private static String toImovelString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        
        sb.append("Tipo de imóvel: " + i.getClass().getName() + ".\n");
        sb.append("Id imóvel: " + i.getId() + ".\n");
        sb.append("Rua: " + i.getRua() + ".\n");
        sb.append("Preço: " + i.getPreco() + " euros.\n");
        sb.append("Preço mímimo: " + i.getPrecoMin() + " euros.\n");
        sb.append("Estado: " + i.getEstado() + ".\n");
        
        if (i instanceof Moradia) {
            sb.append(Main.toMoradiaString(i));
        }
        else if (i instanceof Apartamento) {
            sb.append(Main.toApartamentoString(i));
        }
        else if (i instanceof LojaHabitavel) {
            sb.append(Main.toLojaHabitavelString(i));
        }
        else if (i instanceof Loja) {
            sb.append(Main.toLojaString(i));
        }
        else if (i instanceof Terreno) {
            sb.append(Main.toTerrenoString(i));
        }
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual da classe Moradia.
     */    
    private static String toMoradiaString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        Moradia m = (Moradia) i;
            
        sb.append("Tipo de moradia: " + m.getTipo().name() + ".\n");
        sb.append("Área de implantação: " + m.getAreaImplantacao() + " m2.\n");
        sb.append("Área total: " + m.getAreaTotal() + " m2.\n");
        sb.append("Área do terreno: " + m.getAreaTerreno() + " m2.\n");
        sb.append("Nº de quartos: " + m.getNumQuartos() + ".\n");
        sb.append("Nº de WCs: " + m.getNumWCs() + ".\n");
        sb.append("Nº de porta: " + m.getNumPorta() + ".\n");
        sb.append("--------------------------------------------------------------------\n\n");
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual da classe Apartamento.
     */    
    private static String toApartamentoString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        Apartamento a = (Apartamento) i;
         
        sb.append("Tipo de apartamento: " + a.getTipo().name() + ".\n");
        sb.append("Área total: " + a.getAreaTotal() + " m2.\n");
        sb.append("Nº de quartos: " + a.getNumQuartos() + ".\n");
        sb.append("Nº de WCs: " + a.getNumWCs() + ".\n");
        sb.append("Nº de porta: " + a.getNumPorta() + ".\n");
        sb.append("Nº de porta: " + a.getNumAndar() + ".\n");
        
        if (a.possuiGaragem()) {
            sb.append("Possui garagem.\n");
        }
        
        sb.append("--------------------------------------------------------------------\n\n");
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual da classe LojaHabitavel.
     */    
    private static String toLojaHabitavelString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        LojaHabitavel l = (LojaHabitavel) i;
    
        sb.append("Área: " + l.getArea() + " m2.\n");
        
        if (l.possuiWC()) {
            sb.append("Possui wc.\n");
        }
        
        sb.append("Tipo de negócio: " + l.getTipo() + ".\n");
        sb.append("Nº de porta: " + l.getNumPorta() + ".\n");
        sb.append("Tipo de apartamento: " + l.getTipoAp().name() + ".\n");
        sb.append("Área do apartamento: " + l.getAreaAp() + " m2.\n");
        sb.append("Nº de quartos do apartamento: " + l.getNumQuartos() + ".\n");
        sb.append("Nº de WCs do apartamento: " + l.getNumWCs() + ".\n");
        sb.append("Nº do andar do apartamento: " + l.getNumAndar() + ".\n");
        
        if (l.possuiGaragem()) {
            sb.append("Possui garagem.\n");
        }
        
        sb.append("--------------------------------------------------------------------\n\n");
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual da classe Loja.
     */    
    private static String toLojaString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        Loja l = (Loja) i;
            
        sb.append("Área: " + l.getArea() + " m2.\n");
        
        if (l.possuiWC()) {
            sb.append("Possui wc.\n");
        }
        
        sb.append("Tipo de negócio: " + l.getTipo() + ".\n");
        sb.append("Nº de porta: " + l.getNumPorta() + ".\n");
        sb.append("--------------------------------------------------------------------\n\n");
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual da classe Terreno.
     */    
    private static String toTerrenoString(Imovel i) {
        StringBuilder sb = new StringBuilder();
        Terreno t = (Terreno) i;
           
        sb.append("Tipo de terreno: " + t.getTipo().name() + ".\n");
        sb.append("Diâmetro das canalizações: " + t.getDiametro() + " mm.\n");
        sb.append("Máximo de kWh suportados pela rede elétrica: " + t.getKWh() + " kWh.\n");
        
        if (t.existeAcesso()) {
            sb.append("Possui acesso à rede de esgotos.\n");
        }
        
        sb.append("--------------------------------------------------------------------\n\n");
        
        return sb.toString();
    }
    
    /**
     * @return Devolve uma representação textual de uma lista de entidades da classe Imovel.
     */    
    private static ArrayList<String> toImovelStringList(ArrayList<Imovel> imoveis) {
        ArrayList<String> lst = new ArrayList<>();
        
        imoveis.forEach(i -> lst.add(Main.toImovelString(i)));
        
        return lst;
    }
    
    /**
     * @return Devolve uma representação textual de um mapeamento entre imóveis e respetivos vendedores.
     */    
    private static ArrayList<String> toMapeamentoStringList(HashMap<Imovel, Vendedor> map) {
        ArrayList<String> lst = new ArrayList<>();
        
        for (Imovel i : map.keySet()) {
            StringBuilder sb = new StringBuilder("Vendedor: ");
            sb.append(map.get(i).getEmail() + "\n");
            
            sb.append(Main.toImovelString(i));
            
            lst.add(sb.toString());
        }
        
        return lst;
    }
    
    /**
     * Recebe uma lista de strings e permite ao utilizador navegar nela. Permite ir para a página seguinte, para a
     * página anterior ou uma qualquer página explicitada pelo utilizador.
     */    
    private static void paginacao(ArrayList<String> lst, String message) {
        Paginacao p = new Paginacao(5, lst);
        String op = "";
        int pag = 1;
        int items = 0;
        
        Main.clearTerminal();
        
        items = p.nextPage();
        
        if (items < p.getNumElements()) {
            do {
                out.println(message + "" + items + " de " + p.getNumElements() + ".\n"); 
                out.println("n - Próxima página.");
                out.println("p - Página anterior.");
                out.println(pag + " - " + p.getNumPags() + " Ir para a página.");
                out.println("0 - Sair.");
                
                op = Input.lerString("Opção inválida!", "Opção: ");
                
                if (!op.equals("0")) {
                    if (op.equals("n") || op.equals("N")) {
                        if (pag == p.getNumPags()) {
                            op = "-";
                        }
                        else {
                            Main.clearTerminal();
                            items += p.nextPage();
                            pag++;
                        }
                    }
                    else if (op.equals("p") || op.equals("P")) {
                        if (pag == 1) {
                            op = "-";
                        }
                        else {
                            Main.clearTerminal();
                            items -= p.previousPage();
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
                                Main.clearTerminal();
                                items = p.goToPage(pag);
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
    
    /**
     * Obtém um inteiro que seja superior ao parâmetro min.
     * 
     * @param min          Valor mínimo.
     * @param message      Mensagem para pedir um novo inteiro.
     * @param errorMessage Mensagem de erro.
     */
    private static int getIntInterval(int min, String message, String errorMessage) {
        int res = 0;
        
        do {
            out.print(message);
            res = Input.lerInt(errorMessage, message);
            
            if (res < min) {
                out.println(errorMessage);
            }
        } while (res < min);
        
        return res;
    }
    
    /**
     * Obtém um inteiro que esteja entre os parâmetros min e max.
     * 
     * @param min          Valor mínimo.
     * @param max          Valor máximo.
     * @param message      Mensagem para pedir um novo inteiro.
     * @param errorMessage Mensagem de erro.
     */    
    private static int getIntInterval(int min, int max, String message, String errorMessage) {
        int res = 0;
        
        do {
            out.print(message);
            res = Input.lerInt(errorMessage, message);
            
            if (res < min || res > max) {
                out.println(errorMessage);
            }
        } while (res < min || res > max);
        
        return res;
    }
    
    /**
     * Obtém um double que seja superior ao parâmetro min.
     * 
     * @param min          Valor mínimo.
     * @param message      Mensagem para pedir um novo inteiro.
     * @param errorMessage Mensagem de erro.
     */    
    private static double getDoubleInterval(double min, String message, String errorMessage) {
        double res = 0;
        
        do {
            out.print(message);
            res = Input.lerDouble(errorMessage, message);
            
            if (res < min) {
                out.println(errorMessage);
            }
        } while (res < min);
        
        return res;
    }
    
    /**
     * Obtém um double que esteja entre os parâmetros min e max.
     * 
     * @param min          Valor mínimo.
     * @param max          Valor máximo.
     * @param message      Mensagem para pedir um novo inteiro.
     * @param errorMessage Mensagem de erro.
     */    
    private static double getDoubleInterval(double min, double max, String message, String errorMessage) {
        double res = 0;
        
        do {
            out.print(message);
            res = Input.lerDouble(errorMessage, message);
            
            if (res < min || res > max) {
                out.println(errorMessage);
            }
        } while (res < min || res > max);
        
        return res;
    }
    
    /**
     * Obtém uma string do tipo "S/N" ou "s/n".
     * 
     * @param message      Mensagem para pedir um novo inteiro.
     * @param errorMessage Mensagem de erro.
     */    
    private static String getSNString(String message, String errorMessage) {
        String res = "";
        
        do {
            out.print(message);
            res = Input.lerString(errorMessage, message);
            
            if (!res.equals("S") && !res.equals("s") && !res.equals("N") && !res.equals("n")) {
                out.println(errorMessage);
            }
        } while(!res.equals("S") && !res.equals("s") && !res.equals("N") && !res.equals("n"));
        
        return res;
    }
    
    /**
     * Limpa o terminal.
     */    
    private static void clearTerminal() {
        out.print('\u000C');
    }
    
    /**
     * Muda o ficheiro objeto da aplicação.
     */
    private static void setFile(String file) {
        Main.file = file;
    }
    
} 