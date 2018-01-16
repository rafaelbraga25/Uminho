package Business;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class UC implements IUC {
    private final String nome;
    private final int ano;
    private final int semestre;
    private final Map<String, Turno> turnos;
    private final List<String> alunos;
    
    
    public UC(String nome, int ano, int semestre) {
        this.nome = nome;
        this.ano = ano;
        this.semestre = semestre;
        this.turnos = new HashMap<>();
        this.alunos = new ArrayList<>();
    }
    
    
    public UC(String nome, int ano, int semestre, List<Turno> turnos) {
        this.nome = nome;
        this.ano = ano;
        this.semestre = semestre;
        this.turnos = new HashMap<>();
        this.alunos = new ArrayList<>();
        
        turnos.forEach(t -> this.turnos.put(t.getNomeTurno(), t.clone()));
    }
    
    
    public UC(UC u) {
        nome = u.getNome();
        ano = u.getAno();
        semestre = u.getSemestre();
        turnos = u.getTurnos();
        alunos = u.getAlunos();
    }
    
    
    @Override
    public String getNome() {
        return nome;
    }
    
    
    @Override
    public int getAno() {
        return ano;
    }
    
    
    @Override
    public int getSemestre() {
        return semestre;
    }
    
    
    public Map<String, Turno> getTurnos() {
        Map<String, Turno> map = new HashMap<>();
        
        turnos.values().forEach(v -> map.put(v.getNomeTurno(), v));
        
        return map; 
    }
    
    
    public Map<String, Turno> getTurnosTeoricos() {
        Map<String, Turno> map = new HashMap<>();
        
        turnos.values().stream()
                .filter((t) -> (t.isTeorico())).forEachOrdered((t) -> {
            map.put(t.getNomeTurno(), t);
        });
        
        return map;
    }
    
    
    public Map<String, Turno> getTurnosPraticos() {
        Map<String, Turno> map = new HashMap<>();
        
        turnos.values().stream()
                .filter((t) -> (!t.isTeorico())).forEachOrdered((t) -> {
            map.put(t.getNomeTurno(), t);
        });
        
        return map;
    }
    
    
    public List<String> getAlunos() {
        return new ArrayList<>(alunos);
    }
    
    
    public int getNumPessoasTurno(String turno) {
        Turno t = turnos.get(turno);
       
        return (t == null) ? 0 : t.getNumPessoas();
    }
    
    
    public List<String> getTurnosLivres() {
        List<String> list = new ArrayList<>();
        
        turnos.values().stream()
                .filter((t) -> 
                        (!t.isTeorico() && !t.turnoCheio()))
                .forEachOrdered((t) -> {
            list.add(t.getNomeTurno());
        });
        
        return list;
    }
    
    
    public List<Pair<String, Boolean>> getPedidos(String turno) {
        Turno t = turnos.get(turno);
        List<Pair<String, Boolean>> list = null;
        
        if (t != null) {
            list = t.getPedidos();
        }
        
        return list;
    }
    
    
    public void setCapacidade(String turno, int capacidade) 
            throws CapacidadeInvalida {
        Turno t = turnos.get(turno);
        int numTurnosPraticos = this.getTurnosPraticos().size();
        int numTurnosTeoricos = this.getTurnosTeoricos().size();
        
        if (t != null) {
            int capacidadeMin = (t.isTeorico()) 
                    ? alunos.size() / numTurnosTeoricos
                    : alunos.size() / numTurnosPraticos;
            
            if (capacidadeMin > capacidade) {
                throw new CapacidadeInvalida();
            } else {
                t.setCapacidade(capacidade);
            }
        }
    }
    
    
    public void addTurno(Turno t) {
        turnos.put(t.getNomeTurno(), t.clone());
    }
    
    
    public void addHorario(String turno, Horario h) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.addHorario(h);
        }
    }
    
    
    public boolean alunoInscrito(String aluno) {
        return alunos.contains(aluno);
    }
    
    
    public void addAluno(String aluno) {
        alunos.add(aluno);
    }
    
    
    public void addAlunoTE(String alunoTE) {
        alunos.add(0, alunoTE);
    }
    
    
    public void addAlunoTurno(String aluno, String turno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.addAluno(aluno);
        }
    }
    
    
    public String removeAlunoTurnoPratico(String aluno) {
        String t = "";
        
        for (Turno turno : this.getTurnosPraticos().values()) {
            if (turno.containsAluno(aluno)) {
                turno.removeAluno(aluno);
                t = turno.getNomeTurno();
                break;
            }
        }
        
        return t;
    }
    
    
    public void removeAlunoTurno(String turno, String aluno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.removeAluno(aluno);
        }
    }
    
    
    public void addPedido(String aluno, String turno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.addPedidoAluno(aluno);
        }
    }
    
    
    public void addPedidoTE(String alunoTE, String turno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.addPedidoAlunoTE(alunoTE);
        }
    }
    
    
    public void removePedido(String aluno, String turno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.removePedidos(aluno);
        }
    }
    
    
    public void removePedidos(String aluno) {
        turnos.values().forEach((t) -> {
            t.removePedidos(aluno);
        });
    }
    
    
    public void addFalta(String turno, String aluno) {
        Turno t = turnos.get(turno);
        
        if (t != null) {
            t.addFalta(aluno);
        }
    }
    
    
    @Override
    public int hashCode() {
        return Arrays.hashCode(new Object[] {
            nome,
            ano,
            semestre,
            turnos,
            alunos
        });
    }
    
    
    @Override
    public UC clone() {
        return new UC(this);
    }
}