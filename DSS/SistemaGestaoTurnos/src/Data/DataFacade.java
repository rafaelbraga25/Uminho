/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Data;

import Business.Aluno;
import Business.Horario;
import Business.Pair;
import Business.Turno;
import Business.UC;
import Business.Utilizador;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


/**
 *
 * @author rafae
 */
public class DataFacade {
    
    private final UCDAO ucDAO;
    private final AlunoDAO alunoDAO;
    private final DocenteDAO docenteDAO;
    private final LogDAO logDAO;
    
    
    public DataFacade() {
        logDAO = new LogDAO();
        ucDAO = new UCDAO();
        alunoDAO = new AlunoDAO();
        docenteDAO = new DocenteDAO();
    }
    
    
    public Map<String, Utilizador> getUtilizadores() {
        Map<String, Utilizador> map = new HashMap<>();
        Collection<Utilizador> alunos = alunoDAO.values();
        Collection<Utilizador> docentes = docenteDAO.values();
        
        alunos.forEach((u) -> {
            map.put(u.getUsername(), u);
        });
        
        docentes.forEach((u) -> {
            map.put(u.getUsername(), u);
        });
        
        return map;
    }
    
    
    public Utilizador getUtilizador(String nomeU, String password) {
        Utilizador u = alunoDAO.get(nomeU, password);
        
        if (u == null) {
            u = docenteDAO.get(nomeU, password);
        }
        
        return u;
    }
    
    
    public Map<String, UC> getUCs() {
        Map<String, UC> map = new HashMap<>();
        Collection<UC> ucs = ucDAO.values();
        
        ucs.forEach((u) -> {
            map.put(u.getNome(), u);
        });
        
        return map;
    }
    
    
    public void putUC(UC u) {
        ucDAO.put(u.getNome(), u);
    }
    
    
    public void putAllUCs(Map<String, UC> map) {
        ucDAO.putAll(map);
    }
    
    
    public void clearUCs() {
        ucDAO.clear();
    }
    
    
    public void clearUtilizadores() {
        alunoDAO.clear();
        docenteDAO.clear();
    }
    
    
    public void addTurno(String uc, Turno t) {
        TurnoDAO turnoDAO = new TurnoDAO();
        turnoDAO.add(uc, t);
    }
    
    
    public void addHorario(String uc, String turno, Horario h) {
        HorarioDAO horarioDAO = new HorarioDAO();
        horarioDAO.add(uc, turno, h);
    }
    
    
    public void addAlunoTurno(String uc, String turno, String aluno) {
        TurnoDAO turnoDAO = new TurnoDAO();
        turnoDAO.addAluno(uc, turno, aluno);
    }
    
    
    public void removeAlunoTurno(String uc, String turno, String aluno) {
        TurnoDAO turnoDAO = new TurnoDAO();
        turnoDAO.removeAluno(uc, turno, aluno);
    }
    
    
    public void addFalta(String uc, String turno, String aluno) {
        TurnoDAO turnoDAO = new TurnoDAO();
        turnoDAO.addFalta(uc, turno, aluno);
    }
    
    
    public void addPedidos(String uc, String turno, 
            List<Pair<String, Boolean>> pedidos) {
        PedidoDAO pedidoDAO = new PedidoDAO();
        pedidoDAO.add(uc, turno, pedidos);
    }
    
    
    public void removePedidosAluno(String uc, String aluno) {
        PedidoDAO pedidoDAO = new PedidoDAO();
        pedidoDAO.remove(uc, aluno);
    }
    
    
    public void removePedido(String uc, String turno, String aluno) {
        PedidoDAO pedidoDAO = new PedidoDAO();
        pedidoDAO.remove(uc, turno, aluno);
    }
    
    
    public Utilizador putUtilizador(String utilizador, String password) {
        Utilizador u = alunoDAO.get(utilizador);
        
        if (u != null && u.getPassword().equals("")) {
            u.setPassword(password);
            alunoDAO.put(u.getUsername(), u);
        } else {
            u = null;
        }
        
        return u;
    }
    
    
    public void putUtilizador(Utilizador u) {
        if (u instanceof Aluno) {
            alunoDAO.put(u.getUsername(), u);
        } else {
            docenteDAO.put(u.getUsername(), u);
        }
    }
    
    
    public void putAllUtilizadores(Map<String, Utilizador> map) {
        Map<String, Utilizador> alunos = new HashMap<>();
        Map<String, Utilizador> professores = new HashMap<>();
        
        map.values().forEach((u) -> {
            if (u instanceof Aluno) {
                alunos.put(u.getUsername(), u);
            } else {
                professores.put(u.getUsername(), u);
            }
        });
        
        alunoDAO.putAll(alunos);
        docenteDAO.putAll(professores);
    }
    
    
    public void writeLog(String uc, String turno, String log) {
        logDAO.write(uc, turno, log);
    }
    
    
    public List<Pair<String, String>> readLog(String uc, String turno) {
        return logDAO.read(uc, turno);
    }
}