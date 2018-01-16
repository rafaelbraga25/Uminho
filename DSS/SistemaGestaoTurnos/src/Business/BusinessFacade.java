package Business;


import Data.DataFacade;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Set;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public class BusinessFacade extends Observable {
    
    private static final String ADMIN = "admin";
    private static final String PASSWORD = "pass";
    
    
    private final Map<String, Utilizador> utilizadores;
    private final Map<String, UC> ucs;
    private Utilizador utilizador;
    private final DataFacade dataFacade;
    
    
    public BusinessFacade() {
        utilizador = null;
        dataFacade = new DataFacade();
        utilizadores = dataFacade.getUtilizadores();
        ucs = dataFacade.getUCs();
    }
    
    
    public Utilizador registar(String nomeUtilizador, String password) 
            throws UtilizadorInvalido {
        utilizador = dataFacade.putUtilizador(nomeUtilizador, password);
        
        if (utilizador == null) {
            throw new UtilizadorInvalido();
        }
        
        return utilizador;
    }
   
    
    public Utilizador login(String username, String password) 
            throws UtilizadorInvalido {
        if (username.equals(ADMIN) && password.equals(PASSWORD)) {
            utilizador = new DirecaoCurso(username, password);
        } else {
            utilizador = dataFacade.getUtilizador(username, password);
        }
        
        if (utilizador == null) {
            throw new UtilizadorInvalido();
        }
        
        return utilizador.clone();
    }
    
    
    public void logout() {
        utilizador = null;
    }
    
    
    
    /*************************************************************************
     * DIREÇÃO DE CURSO
     *************************************************************************
    
    
    /**
     * 
     * @throws UtilizadorInvalido      */
    public void atribuirHorarios() throws UtilizadorInvalido {
        if (utilizador == null || !(utilizador instanceof DirecaoCurso)) {
            throw new UtilizadorInvalido();
        }
     
        Map<String, Aluno> alunos = new HashMap<>();
        
        utilizadores.values().stream()
                .filter((u) -> (u instanceof Aluno)).forEachOrdered((u) -> {
            alunos.put(u.getUsername(), (Aluno)u);
        });
        
        CalculadoraTurnos.calcTurnos(alunos, ucs);
        dataFacade.putAllUtilizadores(utilizadores);
        dataFacade.putAllUCs(ucs);
    }
    
    
    public void configurar() throws UtilizadorInvalido {
        if (utilizador == null || !(utilizador instanceof DirecaoCurso)) {
            throw new UtilizadorInvalido();
        }
        
        utilizadores.clear();
        ucs.clear();
        dataFacade.clearUCs();
        dataFacade.clearUtilizadores();
    }
    
    
    
    /**************************************************************************
     * 
     * Métodos ALUNO
     * 
     **************************************************************************/
    
    
    
    /**
     * 
     * @param nomesUCs Nomes das UCs 
     */
    public void inscreverUCs(List<String> nomesUCs) {
        if (utilizador != null && utilizador instanceof Aluno) {
            nomesUCs.stream()
                    .map((uc) -> ucs.get(uc))
                    .filter((u) -> (u != null)).forEachOrdered((u) -> {
                u.addAluno(utilizador.getUsername());
            });
            
            this.setChanged();
            this.notifyObservers();
            dataFacade.putAllUCs(ucs);
        }
    }
    
    
    /* Adicionar restrição do inicio das aulas */
    public boolean trocarTurno(String uc, String tOrigem, String tDestino) {
        boolean trocou = false;
        
        if (utilizador != null && utilizador instanceof Aluno) {
            UC u = ucs.get(uc);
            
            if (u != null) {
                Turno t1 = u.getTurnos().get(tOrigem);
                Turno t2 = u.getTurnos().get(tDestino);
                
                trocou = GestaoTurnos.TrocarTurno((Aluno)utilizador, 
                        this.getAlunosInsc(u), u, t1, t2, dataFacade);
            }
            
            this.setChanged();
            this.notifyObservers();
        }
        
        return trocou;
    }
    
    
    private Map<String, Aluno> getAlunosInsc(UC u) {
        Map<String, Aluno> alunos = new HashMap<>();
        List<String> nomesAlunos = u.getAlunos();
        
        nomesAlunos.forEach((a) -> {
            alunos.put(a, (Aluno)utilizadores.get(a));
        });
        
        return alunos;
    }
    
    
    public List<String> getAlunosInscritos(String uc) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getAlunos();
    }
    
   
    public void cancelarPedido(String uc, String turnoDestino) {
        if (utilizador != null && utilizador instanceof Aluno) {
            
            UC u = ucs.get(uc);
            
            if (u != null) {
                ((Aluno)utilizador).cancelarPedido(uc, turnoDestino);
                u.removePedido(utilizador.getUsername(), turnoDestino);
                
                dataFacade.removePedido(uc, turnoDestino, 
                    utilizador.getUsername());
                
                this.setChanged();
                this.notifyObservers();
            }
        }
    }
    
    
    
    /**************************************************************************
     * 
     * Métodos PROFESSOR
     * 
     **************************************************************************/
    
    
    /**
     * 
     * @param nAluno1
     * @param tAluno1
     * @param nAluno2
     * @param tAluno2
     * @param uc 
     * @return 
     */
    public boolean TrocarAlunos(String nAluno1, String tAluno1, String nAluno2,
            String tAluno2, String uc) {
        boolean trocou = false;
        
        if (utilizador != null && utilizador instanceof Docente) {
            Aluno a1 = (Aluno)utilizadores.get(nAluno1);
            Aluno a2 = (Aluno)utilizadores.get(nAluno2);
            UC u = ucs.get(uc);
                
            if (a1 != null && a2 != null && u != null) {
                trocou = GestaoTurnos
                        .TrocarAlunos(a1, tAluno1, a2, tAluno2, u, dataFacade);
            }
        }
        
        return trocou;
    }
    
    
    public void addAlunoTurno(String a, String t, String u) {
        if (utilizador != null && utilizador instanceof Docente) {
            UC uc = ucs.get(u);
            
            if (uc != null) {
                Aluno aluno = (Aluno)utilizadores.get(a);
                String turnoAntigo = uc.removeAlunoTurnoPratico(a);
                aluno.removeTurno(u, turnoAntigo);
                aluno.addTurno(u, t);
                
                uc.removePedidos(a);
                uc.addAlunoTurno(a, t);
                dataFacade.putUtilizador(aluno);
                dataFacade.putUC(uc);
            }
        }
    }
    
    
    public void removeAlunoTurno(String u, String t, String a) {
        if (utilizador != null && utilizador instanceof Docente) {
            UC uc = ucs.get(u);
            
            if (uc != null) {
                uc.removeAlunoTurno(t, a);
                
                Aluno aluno = (Aluno)utilizadores.get(a);
                aluno.removeTurno(u, t);
                dataFacade.removeAlunoTurno(u, t, a);
                this.setChanged();
                this.notifyObservers();
            }
        }
    }
    
    
    public void addFalta(String u, String t, String a) {
        if (utilizador != null && utilizador instanceof Docente) {
            UC uc = ucs.get(u);
            
            if (uc != null) {
                uc.addFalta(t, a);
                dataFacade.addFalta(u, t, a);
            }
        }
    }
    
    
    public void setCapacidade(String uc, String turno, int capacidade) 
            throws CapacidadeInvalida {
        if (utilizador != null && utilizador instanceof Docente) {
            UC u = ucs.get(uc);
            
            if (u != null) {
                u.setCapacidade(turno, capacidade);
                dataFacade.putUC(u);
            }
        }
    }
    
    
    public void removePedidosAluno(String uc, String aluno) 
            throws UtilizadorInvalido, UCInvalida {
        if (utilizador == null || !(utilizador instanceof Docente)) {
            throw new UtilizadorInvalido();
        }
        
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        u.removePedidos(aluno);
        dataFacade.removePedidosAluno(uc, aluno);
    }
    
    
    
    /*************************************************************************
     * POVOAMENTO
     *************************************************************************/
    
    
    /**
     * 
     * @param username
     * @param password
     * @param ucsLecionadas 
     */
    public void addProfessor(String username, String password, 
            List<String> ucsLecionadas) {
        Utilizador u = new Docente(username, password, ucsLecionadas);
        
        utilizadores.put(username, u);
        dataFacade.putUtilizador(u);
    }
    
    
    public void addAluno(String username, String password, boolean TE) {
        Utilizador u = new Aluno(username, password, TE);
        
        utilizadores.put(username, u);
        dataFacade.putUtilizador(u);
    }
    
    
    public void addUC(String nome, int ano, int semestre) {
        UC u = new UC(nome, ano, semestre);
        
        ucs.put(nome, u);
        dataFacade.putUC(u);
    }
    
    
    public void addTurno(String uc, String turno, boolean isTeorico, 
            int capacidade, int numAulas) {
        UC u = ucs.get(uc);
        
        if (u != null) {
            Turno t = new Turno(turno, isTeorico, capacidade, numAulas);
            u.addTurno(t);
            dataFacade.addTurno(uc, t);
        }
    }
    
    
    public void addHorario(String uc, String turno, 
            int diaSemana, int horaInicio, int horaFim) {
        UC u = ucs.get(uc);
        
        if (u != null) {
            Horario h = new Horario(diaSemana, horaInicio, horaFim);
            u.addHorario(turno, h);
            dataFacade.addHorario(uc, turno, h);
        }
    }
    
    
    /*************************************************************************
     * GETTERS
     *************************************************************************/
    
    
    /**
     * 
     * @return
     * @throws UtilizadorInvalido 
     */
    public List<String> getUCsDocente() throws UtilizadorInvalido {
        if (utilizador == null || !(utilizador instanceof Docente)) {
            throw new UtilizadorInvalido();
        }
        
        return ((Docente)utilizador).getUCs();
    }
    

    public Collection<IUC> getUCs() {
        Collection<IUC> col = new ArrayList<>();
        
        col.addAll(ucs.values());
        
        return col;
    }
    
    
    public boolean isTurnoPratico(String uc, String turno) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnosPraticos().containsKey(turno);
    }
    
    
    public Set<String> getTurnosUC(String uc) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnos().keySet();
    }
    
    
    public Set<String> getTurnosTeoricosUC(String uc) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnosTeoricos().keySet();
    }
    
    
    public String getTurnoPraticoAluno(String uc, String aluno) 
            throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        String t = "";
        Map<String, Turno> tPraticos = u.getTurnosPraticos();
        
        
        for (Turno turno : tPraticos.values()) {
            if (turno.containsAluno(aluno)) {
                t = turno.getNomeTurno();
                break;
            }
        }
        
        return t;
    }
    
    
    public String getTurnoTeoAluno(String uc, String aluno) 
            throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        String t = "";
        Map<String, Turno> tTeos = u.getTurnosTeoricos();
        
        
        for (Turno turno : tTeos.values()) {
            if (turno.containsAluno(aluno)) {
                t = turno.getNomeTurno();
                break;
            }
        }
        
        return t;
    }
    
    
    public Set<String> getTurnosPraticosUC(String uc) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnosPraticos().keySet();
    }
    
    
    public List<String> getTurnosLivres(String uc) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnosLivres();
    }
    
    
    public int getEstadoPedido(String uc, String turno) 
            throws UtilizadorInvalido, UCInvalida {
        if (utilizador == null || !(utilizador instanceof Aluno)) {
            throw new UtilizadorInvalido();
        }
        
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnos().get(turno).getNumPedido(utilizador.getUsername());
    }
    
    
    public int getCapacidadeTurno(String uc, String turno) throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getTurnos().get(turno).getCapacidade();
    }
    
    
    public List<Pair<String, String>> getPedidos() throws UtilizadorInvalido {
        if (utilizador == null || !(utilizador instanceof Aluno)) {
            throw new UtilizadorInvalido();
        }
        
        return ((Aluno)utilizador).getPedidos();
    }
    
    
    public List<Pair<String, Integer>> 
        getAlunosTurno(String uc, String turno) {
        UC u = ucs.get(uc);
        List<Pair<String, Integer>> alunos = null;
        
        if (u != null) {
            alunos = u.getTurnos().get(turno).getAlunos();
        }
        
        return alunos;
    }
    
    
    public int getAulasTurno(String uc, String turno) {
        int n = 0;
        UC u = ucs.get(uc);
        
        if (u != null) {
            n = u.getTurnos().get(turno).getNumAulas();
        }
        
        return n;
    }
    
    
    public List<Pair<String, Boolean>> getPedidosTurno(String uc, String turno) 
            throws UCInvalida {
        UC u = ucs.get(uc);
        
        if (u == null) {
            throw new UCInvalida();
        }
        
        return u.getPedidos(turno);
    }
    
    
    public IUC getUCInfo(String uc) throws NullPointerException {
        return ucs.get(uc).clone();
    }
    
    
    public Map<String, List<String>> getUCsInscritas() 
            throws UtilizadorInvalido {
        if (utilizador == null || !(utilizador instanceof Aluno)) {
            throw new UtilizadorInvalido();
        }
        
        Map<String, List<String>> map = ((Aluno)utilizador).getTurnos();
        
        if (map.isEmpty()) {
            for (UC u : ucs.values()) {
                if (u.alunoInscrito(utilizador.getUsername())) {
                    map.put(u.getNome(), new ArrayList<>());
                }
            }
        }
        
        return map;
    }
    
    
    public void writeLog(String uc, String turno, String log) {
        dataFacade.writeLog(uc, turno, log);
    }
    
    
    public List<Pair<String, String>> readLog(String uc, String turno) {
        return dataFacade.readLog(uc, turno);
    }
}
