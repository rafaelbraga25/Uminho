
/**
 * Classe que define uma imobiliaria. Contém toda a informação relativa aos utilizadores de uma imobiliária
 * (compradores e vendedores), bem como todos os imóveis disponíveis na imobiliaria.
 * Implementa a classe Serializable.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */


import static java.util.stream.Collectors.toMap;
import static java.util.stream.Collectors.joining;

import java.util.Map;
import java.util.TreeMap;
import java.util.HashMap;
import java.util.List;
import java.util.ArrayList;
import java.util.Set;
import java.util.TreeSet;
import java.util.HashSet;
import java.util.Comparator;
import java.util.stream.Collectors;
import java.util.Iterator;
import java.util.Arrays;

import java.util.Calendar;
import java.util.GregorianCalendar;

import java.io.Serializable;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.io.FileOutputStream;

import ImoobiliariaExceptions.UtilizadorExistenteException;
import ImoobiliariaExceptions.SemAutorizacaoException;
import ImoobiliariaExceptions.ImovelExisteException;
import ImoobiliariaExceptions.ImovelInexistenteException;
import ImoobiliariaExceptions.EstadoInvalidoException;
import ImoobiliariaExceptions.LeilaoTerminadoException;

public class Imoobiliaria implements Serializable
{   
    // Variáveis de instância
   
    private Map<String, Utilizador> utilizadores; // Mapeamento entre os utilizadores e os respetivos emails.
    private List<Imovel> imoveis;                 // Lista de todos os imóveis.
    private Utilizador utilizador;                // Guarda o utilizador com sessão iniciada.
    private Leilao leilao;                        // Guarda o último leilão.
    
    
    // Construtores
    
    /**
     * Construtor vazio.
     */   
    public Imoobiliaria() { 
        utilizadores = new TreeMap<String, Utilizador>();
        imoveis = new ArrayList<>();
        utilizador = null;
        leilao = null;
    }
    
    
     /**
     * Construtor por partes.
     * 
     * @param utilizadores Mapeamento dos utilizadores e emails.
     * @param imoveis      Lista de todos os imóveis.
     * @param utilizador   Utilizador com sessão iniciada.
     * @param leilao       Último leilão.
     */    
    public Imoobiliaria(Map<String, Utilizador> utilizadores, List<Imovel> imoveis, Utilizador utilizador,
                        Leilao leilao) {
        this.setUtilizadores(utilizadores);
        this.setImoveis(imoveis);
        this.setUtilizador(utilizador);
        this.leilao = leilao.clone();
    }
    
    
    /**
     * Construtor por cópia.
     * 
     * @param i Imoobiliaria i.
     */
    public Imoobiliaria(Imoobiliaria i) {
        utilizadores = i.getUtilizadores();
        imoveis = i.getImoveis();
        utilizador = i.getUtilizador();
        leilao = i.getLeilao();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "utilizadores".
     */ 
    public Map<String, Utilizador> getUtilizadores() {
        Map<String, Utilizador> temp = new TreeMap<String, Utilizador>();
        
        for (String str : utilizadores.keySet()) {
            temp.put(str, utilizadores.get(str).clone());
        }
        
        return temp;
    }
    
    
    /**
     * @return Devolve o campo "imoveis".
     */ 
    public List<Imovel> getImoveis() {
        return imoveis.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * @return Devolve o campo "utilizador" ou null caso o utilizador seja nulo.
     */   
    public Utilizador getUtilizador() {
        return (utilizador != null) ? utilizador.clone() : null;
    }
    
    
    /**
     * @return Devolve o campo "leilao" ou null caso o leilão seja nulo.
     */
    public Leilao getLeilao() {
        return (leilao != null) ? leilao.clone() : null;
    }
    
 
    /**
     * @brief Devolve uma lista com as datas (e emails, caso exista essa informação) das
     *        10 últimas consultas aos imóveis que um vendedor tem para venda.
     * 
     * Cria-se um comparador de forma a ordenar as datas por ordem cronológica. De seguida,
     * para cada imóvel verifica-se se o vendedor com sessão iniciada (caso não seja um vendedor, 
     * lança-se a exceção SemAutorizacao) tem esse imóvel na sua lista de imóveis em venda e,
     * em caso afirmativo, adicionam-se as consultas feitas a esse imóvel ao TreeSet das consultas,
     * que fica ordenado pelo comparador. Finalmente, adicionam-se as últimas 10 consultas de cada
     * imóvel ao ArrayList que depois é devolvido. 
     * 
     * @return ret ArrayList que contém as 10 últimas consultas dos imóveis da lista de
     *             imóveis em venda do vendedor.
     */    
    public List<Consulta> getConsultas() throws SemAutorizacaoException {
        Set<Consulta> temp;                 // Set auxiliar para ordenar as consultas por data.
        List<Consulta> ret;                 // Lista final de consultas.
        Comparator<Consulta> consultaComp;  // Comparador de duas consultas.
        Iterator<Consulta> it;              // Iterador do set de consultas.
        int j = 0;                          // Controlo das 10 posições do set de consultas. 
        
        if (utilizador instanceof Vendedor) {
            
            /* Comparador para ordenar as consultas por ordem decrescente. */
            
            consultaComp = (c1, c2) -> {
                if (c1.getData().compareTo(c2.getData()) < 0) return 1;
                if (c1.getData().compareTo(c2.getData()) > 0) return -1;
                else return 0;
            };
            
            temp = new TreeSet<>(consultaComp);
            ret = new ArrayList<>();
                
            for (Imovel i : imoveis) {
                if (((Vendedor) utilizador).containsPortfolio(i)) {
                    temp.addAll(i.getConsultas());
                }
            }
            
            it = temp.iterator();
            
            /* Adiciona as últimas 10 consultas realizadas. */
            
            while (it.hasNext() && j < 10) {
                ret.add(it.next().clone());
                j++;
            }
            
            return ret;
        }
        else {
            
            /* Se o utilizador não é um vendedor a excessão é lançada. */
            
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @brief Devolve um conjunto com os códigos dos imóveis mais consultados de um vendedor
     *        (ou seja, com mais de N consultas).
     *        
     * Através de um stream() e de um filter(), filtram-se os imóveis com um número
     * de consultas superior ao parâmetro n e, de seguida, com o auxílio de um map()
     * adicionam-se ao TreeSet retornado os seus códigos de identificação.
     * 
     * @param n Limite mínimo de consultas.
     * @return set. 
     */     
    public Set<String> getTopImoveis(int n) {
        Set<String> set = new HashSet<>();
        
        set = imoveis.stream()
                     .filter(i -> i.getConsultas().size() > n)
                     .map(i -> i.getId())
                     .collect(Collectors.toSet());
        
        return set;
    }
    
    
    /**
     * @brief Consulta a lista de todos os imóveis de um dado tipo (Terreno, Moradia, etc.)
     *        e até um certo preço.
     *        
     * Para todos os imóveis, verifica-se se correspondem a uma dada classe recebida como
     * parâmetro e se o preco é inferior ao preço recebido como parâmetro. Em caso afirmativo,
     * adiciona-se uma nova consulta com a data atual e o email do utilizador com sessão
     * iniciada. Por fim, retorna-se a um ArrayList com o resultado da pesquisa.
     * 
     * @param classe Classe de imóveis a pesquisar.
     * @param preco  Preço máximo dos imóveis a pesquisar.
     * @return ret ArrayList com o resultado da pesquisa dos imóveis.
     */   
    public List<Imovel> getImovel(String classe, int preco) {
        List<Imovel> ret = new ArrayList<>();
        String email = (utilizador == null) ? "" : utilizador.getEmail();
        
        for (Imovel i : imoveis) {
            if (i.getClass().getName().equals(classe) && i.getPreco() <= preco) {
                i.addConsulta(new Consulta(email, new GregorianCalendar()));
                ret.add(i.clone());
            }
        }
        
        return ret;
    }
    
    
    /**
     * @brief Devolve a lista de todos os imóveis habitáveis (até um certo preço)
     *        
     * Para cada imóvel, verifica-se se é do tipo Habitavel e se o seu preço está abaixo
     * do preço máximo recebido como parâmetro. Em caso afirmativo, adiciona-se uma nova
     * consulta com a data atual e o email do utilizador com sessão iniciada. Por fim,
     * retorna-se a um ArrayList com o resultado da pesquisa.
     * 
     * @param preco Preço máximo dos imóveis a pesquisar.
     * @return ret ArrayList com o resultado da pesquisa dos imóveis.
     */      
    public List<Imovel> getHabitaveis(int preco) {
        List<Imovel> ret = new ArrayList<>();
        String email = (utilizador == null) ? "" : utilizador.getEmail();
        
        for (Imovel i : imoveis) {
            if (i instanceof Habitavel && i.getPreco() <= preco) {
                i.addConsulta(new Consulta(email, new GregorianCalendar()));
                ret.add(i.clone());
            }
        }
        
        return ret;
    }
    
    
    /**
     * @brief Devolve um imóvel através do seu id, caso este exista.
     * 
     * Devolve uma cópia do imóvel correspondente ao id recebido. Caso o imóvel não exista é lançada a
     * excesso NullPointerException.
     * 
     * @param idImovel Id do imóvel pretendido.
     * @return Cópia do imóvel correspondente ao id recebido.
     */
    public Imovel getImovelById(String idImovel) throws NullPointerException {
        Imovel i = null;
        
        for (Imovel im : imoveis) {
            if (im.getId().equals(idImovel)) {
                i = im;
                break;
            }
        }
        
        return i.clone();
    }
    
    
    /**
     * @brief Devolve um mapeamento entre todos os imóveis e respetivos vendedores.
     *       
     * Para cada imóvel e para cada vendedor, verifica-se se este contém o imóvel na sua lista de
     * imóveis em venda. Em caso afirmativo, adiciona-se a um Map uma cópia desse mesmo
     * vendedor. Por fim, retorna-se o Map que faz corresponder a cada imóvel o seu respetivo vendedor.
     * 
     * @return ret Map que faz corresponder a cada imóvel o seu respetivo vendedor.
     */   
    public Map<Imovel, Vendedor> getMapeamentoImoveis() {
        Map<Imovel, Vendedor> map = new HashMap<Imovel, Vendedor>();
        
        for (Imovel i : imoveis) {
            for (Utilizador u : utilizadores.values()) {
                if (u instanceof Vendedor) {
                    if (((Vendedor) u).containsPortfolio(i)) {
                        map.put(i.clone(), ((Vendedor) u).clone());
                        break;
                    }
                }
            }
        }
        
        return map;
    }
    
    
    /**
     * @brief Permite a um comprador consultar os seus imóveis favoritos ordenados por preço.
     *       
     * Primeiro cria-se um comparador para ordenar os imóveis por preço. Se o utilizador for
     * um comprador (caso não o seja, é lançada a exceção SemAutorizacao), vai-se à sua lista
     * de favoritos e adiciona-se uma cópia de cada um dos imóveis favoritos a um TreeSet 
     * ordenado pelo comparador. Por fim, devolve-se o TreeSet.
     * 
     * @return set TreeSet dos imóveis favoritos do comprador.
     */     
    public TreeSet<Imovel> getFavoritos() throws SemAutorizacaoException {
        
        /* Comparador que ordena um TreeSet por ordem decrescente de preço. */
        
        Comparator<Imovel> cmpImovel = (i1, i2) -> {
            if (i1.getPreco() < i2.getPreco()) return -1;
            if (i1.getPreco() > i2.getPreco()) return 1;
            else return 0;
        };
        
        TreeSet<Imovel> set = null;
        Iterator it = null;
        
        if (utilizador instanceof Comprador) {
            set = new TreeSet<>(cmpImovel);
            
            it = ((Comprador) utilizador).getFavoritos().iterator();
            
            while (it.hasNext()) {
                set.add(((Imovel) it.next()).clone());
            }
           
            return set;
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @param email Email do utilizador que se pretende obter.
     * @return Devolve um utilizador correspondente a um email caso este exista.
     */
    public Utilizador getUtilizadorByEmail(String email) throws NullPointerException {
        try {
            return utilizadores.get(email).clone();
        }
        catch (NullPointerException e) {
            return null;
        }
    }
    
    
    /**
     * Altera o campo "utilizadores" da Imoobiliaria.
     */
    public void setUtilizadores(Map<String, Utilizador> utilizadores) {
        this.utilizadores = utilizadores.values()
                                        .stream()
                                        .collect(toMap(Utilizador::getEmail, Utilizador::clone));
    }
    
    
    /**
     * Altera o campo "imoveis" da Imoobiliaria.
     */   
    public void setImoveis(List<Imovel> imoveis) {
        this.imoveis = imoveis.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * Altera o campo "utilizador" da Imoobiliaria.
     */ 
    public void setUtilizador(Utilizador utilizador) {
        this.utilizador = utilizador.clone();
    }
    
    
    /**
     * @brief Altera o estado de um imóvel, de acordo com as acções feitas sobre ele.
     * 
     * Primeiro verifica-se se o utilizador com sessão iniciado é um vendedor - se não o for
     * é lançada a exceção SemAutorizacao. De seguida, verifica-se se o vendedor contém na sua
     * lista de imóveis em venda o imóvel cujo código de identificação é passado como parâmetro
     * - caso não contenha, é lançada a exceção ImovelInexistente. Além disso, é validado o estado
     * recebido como parâmetro - caso não seja válido é lançada a exceção EstadoInvalido. Após o
     * tratamento das exceções, procura-se o imóvel cujo código de identificação é passado ao método
     * e altera-se o seu estado para o pretendido. Por fim, caso se tenha alterado o estado do imóvel
     * para "vendido", é adicionado o imóvel à lista de imóveis vendidos do vendedor.
     * 
     * @param idImovel Imóvel do qual se pretende alterar o estado.
     * @param estado   Estado para o qual se pretende alterar.
     */
    public void setEstado(String idImovel, String estado) throws ImovelInexistenteException,
                                                                 SemAutorizacaoException,
                                                                 EstadoInvalidoException 
    {
        Imovel im = null;
        Vendedor v = null;
        
        if (utilizador instanceof Vendedor) {
            if (!((Vendedor) utilizador).containsPortfolio(idImovel)) {
                
                /* O imóvel não pertente ao vendedor logo é lançada a excessão. */
                
                throw new ImovelInexistenteException();
            }
            else {
                if (!Imovel.estadoValido(estado)) {
                    throw new EstadoInvalidoException();
                }
                else {
                    for (Imovel i : imoveis) {
                        
                        /* Altera-se o estado do imóvel. */
                        
                        if (i.getId().equals(idImovel)) {
                            i.setEstado(estado);
                            im = i.clone();
                            break;
                        }
                    }
                    
                    if (estado.equals(Imovel.vendido) || estado.equals(Imovel.reservado)) {
                        for (Utilizador u : utilizadores.values()) {
                            if ((u instanceof Vendedor) && u.getEmail().equals(utilizador.getEmail())) {
                                v = (Vendedor) utilizadores.get(u.getEmail());
                                
                                /* Se o estado for alterado para vendido adicona-se este imóvel ao histórico
                                 * de imóveis vendidos.
                                 */
                                
                                if (estado.equals(Imovel.vendido)) {
                                    v.addHistorico(im);
                                }
                                
                                /* Remove-se o imóvel dos imóveis em venda do vendedor. */
                                
                                v.removePortfolio(im);
                                
                                /* Atualiza o vendedor. */
                                
                                utilizadores.put(u.getEmail(), v.clone());
                                utilizador = v.clone();
                                break;
                            }
                        }
                    }
                }
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @brief Permite a um comprador marcar um imóvel como favorito.
     * 
     * Primeiro verifica-se se o utilizador com sessão iniciada é um comprador - caso não o seja
     * é lançada a exceção SemAutorizacao. De seguida, verifica-se se o código de identificação
     * recebido como parâmetro corresponde a algum dos imóveis no campo "imoveis" da Imoobiliaria
     * - caso não exista, é lançada a exceção ImovelInexistente. Em caso afirmativo, faz-se uma
     * cópia desse imóvel e adiciona-se esse imóvel à lista de favoritos do comprador.
     * 
     * @param idImovel Código de identificação do imóvel que se pretende adicionar aos favoritos
     */
    public void setFavorito(String idImovel) throws ImovelInexistenteException,
                                                    SemAutorizacaoException {
        Imovel aux = null;
                                                        
        if (utilizador instanceof Comprador) {
            if (imoveis.stream().anyMatch(i -> i.getId().equals(idImovel))) {
                for (Imovel im : imoveis) {
                    if (im.getId().equals(idImovel)) {
                        aux = im;
                        break;
                    }
                }
                
                ((Comprador) utilizador).addFavorito(aux.clone());
            }
            else {
                throw new ImovelInexistenteException();
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * Primeiro verifica-se se a lista de utilizadores já contém o utilizador que se pretende
     * registar - caso já contenha, é lançada a exceção UtilizadorExistente. Caso contrário é
     * adicionado o utilizador passado como parâmetro à lista de utilizadores da Imoobiliaria.
     *  
     * @param utilizador Utilizador que se pretende registar
     */
    public void registarUtilizador(Utilizador utilizador) throws UtilizadorExistenteException {
        if (utilizadores.containsKey(utilizador.getEmail())) {
            throw new UtilizadorExistenteException();
        }
        else {
            utilizadores.put(utilizador.getEmail(), utilizador.clone());
        }
    }
    
    
    /**
     * Primeiro verifica-se se o utilizador está registado (i.e. se o seu email consta na lista de utilizadores 
     * da Imoobiliaria) e se a password recebida como parâmetro correponde à que consta na lista dos utilizadores.
     * Caso algum destes casos não se verifique, é lançada a exceção SemAutorizacao. Se o utilizador estiver 
     * registado, é adicionado ao campo "utilizador" da Imoobiliaria.
     * 
     * @param email    Email do utilizador que pretende iniciar sessão.
     * @param password Password do utilizador que pretende iniciar sessão.
     */
    public void iniciaSessao(String email, String password) throws SemAutorizacaoException {
        if (!utilizadores.containsKey(email) || !utilizadores.get(email).getPassword().equals(password)) {
                throw new SemAutorizacaoException();
        }
        else {
            utilizador = utilizadores.get(email).clone();
        }
    }
    
    
    /**
     * Fecha a sessão do utilizador atual, colocando o campo "utilizador" da Imoobiliaria a null.
     */
    public void fechaSessao() {
        utilizador = null;
    }
    
    
    /**
     * @brief Permite a um vendedor colocar um imóvel à venda.
     * 
     * Primeiro verifica-se se o imóvel já existe na lista de imóveis da Imoobiliaria - caso já exista
     * é lançada a exceção ImovelExiste. De seguida, verifica-se se o utilizador com sessão iniciada
     * é um vendedor - caso não o seja, é lançada a exceção SemAutorizacao. Depois percorre-se todos os
     * utilizadores à procura do vendedor com sessão iniciada e adiciona-se este novo imóvel à sua lista
     * de imóveis em venda. Por fim, são atualizados os dados do vendedor na lista de utilizadores da
     * Imoobiliaria, de forma a que contenha esta alteração no seu portfólio.
     * 
     * @param im Imóvel que se pretende registar.
     */
    public void registaImovel(Imovel im) throws ImovelExisteException, SemAutorizacaoException {
        
        if (imoveis.stream().anyMatch(i -> i.getId().equals(im.getId()))) {
            throw new ImovelExisteException();
        }
        
        if (utilizador instanceof Vendedor) {
            imoveis.add(im.clone());
            Vendedor v;
            
            for (Utilizador u : utilizadores.values()) {
                if ((u instanceof Vendedor) && u.getEmail().equals(utilizador.getEmail())) {
                    v = (Vendedor) utilizadores.get(u.getEmail());
                    
                    /* Adiciona o imóvel ao portfólio do vendedor e atualiza o mesmo. */
                    
                    v.addPortfolio(im);
                    utilizadores.put(u.getEmail(), v.clone());
                    utilizador = v.clone();
                    break;
                }
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @brief Permite a um vendedor colocar um imóvel em leilão.
     * 
     * Primeiro verifica-se se o utilizador com sessão iniciada é um vendedor - caso não seja é lançada a
     * exceção SemAutorizacao. Inicia-se o leilão e percorre-se a lista de utilizadores de forma a encontrar
     * todos os compradores que participem no leilão (i.e. os que contêm o campo "participaLeilao" a true) e a 
     * adicioná-los à lista de compradores do leilão.
     * 
     * @param im    Imóvel que se pretende leiloar.
     * @param horas Duração, em horas, do leilão.
     */
    public void iniciaLeilao(Imovel im, int horas) throws SemAutorizacaoException {
        if (utilizador instanceof Vendedor) {
            if (((Vendedor) utilizador).containsPortfolio(im)) {
                leilao = new Leilao(im, horas);
                
                for (Utilizador u : utilizadores.values()) {
                    if (u instanceof Comprador) {
                        Comprador c = (Comprador) u;
                        
                        if (c.participaLeilao()) {
                            leilao.addComprador(c);
                        }
                    }
                }
            }
            else {
                throw new SemAutorizacaoException();
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @brief Permite a um vendedor adicionar um comprador a um leilão.
     * 
     * Primeiro verifica-se se o utilizador com sessão iniciada é um vendedor - caso não seja é lançada a exceção
     * SemAutorizacao. Caso o leilão não exista ou já tenha terminado é lançada a exceção LeilaoTerminado. Depois,
     * caso o comprador exista na lista dos utilizadores da Imoobiliaria, é adicionado o comprador ao leilão.
     * 
     * @param idComprador Código de identicação do comprador que se pretende adicionar ao leilão.
     * @param limite      Quantia máxima que o comprador pretende gastar por um imóvel num leilão.
     * @param incrementos Valor de incremento entre as licitações num leilão.
     * @param minutos     Tempo entre as licitações do comprador.
     */
    public void adicionaComprador(String idComprador, double limite, 
                                  double incrementos, double minutos) throws SemAutorizacaoException,
                                                                             LeilaoTerminadoException {
        if (utilizador instanceof Vendedor) {
            if (leilao == null || leilao.leilaoTerminado()) {
                throw new LeilaoTerminadoException();
            }
            else {
                if (utilizadores.containsKey(idComprador)) {
                    try { 
                        Comprador c = (Comprador) this.getUtilizadorByEmail(idComprador);
                        
                        c.setLimite(limite);
                        c.setIncrementos(incrementos);
                        c.setMinutos(minutos);
                        
                        leilao.addComprador(c);
                    }
                    
                    /* A excessão é "apanhada" mas não é necessário realizar qualquer operação ficando a função
                     * sem efeito neste caso.
                     */
                    
                    catch (NullPointerException e) { }
                }
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @brief Permite a um vendedor encerrar um leilão.
     * 
     * Primeiro verifica-se se o utilizador com sessão iniciada é um vendedor - caso não seja é lançada a
     * exceção SemAutorizacao. Caso o leilão não exista (i.e. seja igual a "null") é lançada a exceção
     * LeilaoTerminado. De seguida, cria-se um cópia do comprador que venceu o leilão e muda-se o estado
     * do imóvel leiloado para reservado. Por fim, retorna-se a cópia do comprador vencedor.
     * 
     * @return c Comprador que venceu o leilão.
     */
    public Comprador encerraLeilao() throws LeilaoTerminadoException, SemAutorizacaoException {
        if (utilizador instanceof Vendedor) {
            if (leilao == null) {
                throw new LeilaoTerminadoException();
            }
            else {
                Comprador c = (Comprador) utilizadores.get(leilao.getVencedor()).clone();
                
                try {
                    
                    /* Se o montante recebido no leilão for igual ou superior à quantidade mínima requerida
                     * pelo vendedor, então imóvel passa a estar reservado.
                     */
                    
                    if (leilao.getMontante() >= leilao.getImovel().getPrecoMin()) {
                        this.setEstado(leilao.getImovel().getId(), Imovel.reservado);
                    }
                    else {
                        c = null;
                    }
                }
                
                /* As excessões provenientes da função "setEstado" são "apanhadas" para a integridade do programa
                 * embora não surtam qualquer efeito neste contexto.
                 */
                
                catch (SemAutorizacaoException | ImovelInexistenteException | EstadoInvalidoException e) {
                    
                }
                
                leilao = null;
                return c;
            }
        }
        else {
            throw new SemAutorizacaoException();
        }
    }
    
    
    /**
     * @param email Email a procurar.
     * @return Devolve true se existir um utilizador com o email recebido no Map de utilizadores ou false
     *         caso contrário.
     */
    public boolean containsUser(String email) {
        return utilizadores.containsKey(email);
    }
    
    
    // Métodos complementares comuns
    
    /**
     * @return Devolve um código de hash relativo a um utilizador.
     */   
    public int hashCode() {
        return Arrays.hashCode(new Object[] { imoveis, utilizadores, utilizador, leilao });
    }
    
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Imoobiliaria.
     * 
     * @param o Objeto ao qual se quer efetuar a comparação.
     * @return Devolve true caso o objeto seja igual ou false, caso contrário.
     */   
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        Imoobiliaria i = (Imoobiliaria) o;
        
        return (utilizadores.equals(i.getUtilizadores()) && imoveis.equals(i.getImoveis()) && 
                utilizador.equals(i.getUtilizador()) && leilao.equals(i.getLeilao()));
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Imoobiliaria.
     */  
    public String toString() {
        StringBuilder sb = new StringBuilder("Imoobiliaria: \n");
        
        if (utilizador != null) {
            sb.append(utilizador.toString());
            sb.append("\n");
        }
        
        if (leilao != null) {
            sb.append(leilao.toString());
            sb.append("\n");
        }
        
        sb.append(imoveis.stream()
                         .map(Imovel::toString)
                         .collect(joining("\n")));
        
        sb.append(utilizadores.values()
                              .stream()
                              .map(Utilizador::toString)
                              .collect(joining("\n")));
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de uma Imoobiliaria.
     */   
    public Imoobiliaria clone() {
        return new Imoobiliaria(this);
    }
    
    
    /**
     * Grava os campos da instância Imoobiliaria num ficheiro objeto.
     */
    public void gravaObj(String file) throws IOException {
        ObjectOutputStream oout = new ObjectOutputStream(new FileOutputStream(file));
        
        try {
            oout.writeObject(this);
        }
        catch (IOException e) {
            throw e;
        }
        
        oout.flush();
        oout.close();
    }
}
