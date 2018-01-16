package Business;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;


public class Turno {
    
    private final String nomeTurno;
    private final boolean isTeorico;
    private int capacidade;
    private final int numAulas;
    private final List<Horario> horarios;
    private final List<Pair<String, Integer>> alunos;
    private final List<Pair<String, Boolean>> pedidos;
    
    
    public Turno(String nomeTurno, boolean isTeorico, int capacidade,
            int numAulas) {
        this.nomeTurno = nomeTurno;
        this.isTeorico = isTeorico;
        this.capacidade = capacidade;
        this.numAulas = numAulas;
        horarios = new ArrayList<>();
        alunos = new ArrayList<>();
        pedidos = new ArrayList<>();
    }
    
    
    public Turno(Turno t) {
        nomeTurno = t.getNomeTurno();
        isTeorico = t.isTeorico;
        capacidade = t.getCapacidade();
        numAulas = t.getNumAulas();
        horarios = t.getHorarios();
        alunos = t.getAlunos();
        pedidos = t.getPedidos();
    }
    
    
    public String getNomeTurno() {
        return nomeTurno;
    }
    
    
    public boolean isTeorico() {
        return isTeorico;
    }
    
    
    public int getCapacidade() {
        return capacidade;
    }
    
    
    public int getNumAulas() {
        return numAulas;
    }
    
    
    public List<Horario> getHorarios() {
        List<Horario> list = new ArrayList<>();
        
        horarios.forEach(h -> list.add(h.clone()));
        
        return list;
    }
    
    
    public List<Pair<String, Integer>> getAlunos() {
        return new ArrayList<>(alunos);
    }
    
    
    public List<Pair<String, Boolean>> getPedidos() {
        return new ArrayList<>(pedidos);
    }
    
    
    public int getNumPessoas() {
        return alunos.size();
    }
    
    
    public int getNumPedido(String aluno) {
        int index = -1;
        
        for (int i = 0; i < pedidos.size(); i++) {
            if (pedidos.get(i).getLeft().equals(aluno)) {
                index = i;
                break;
            }
        }
        
        return index;
    }
    
    
    public void setCapacidade(int capacidade) {
        this.capacidade = capacidade;
    }
    
    
    public boolean turnoCheio() {
        return capacidade <= alunos.size();
    }
    
    
    public boolean colide(Turno t) {
        List<Horario> horariosT = t.getHorarios();
        boolean colide = false;
        
        for (int i = 0; i < horarios.size() && !colide; i++) {
            Horario h = horarios.get(i);
            
            for (int j = 0; j < horariosT.size() && !colide; j++) {
                colide = h.colide(horariosT.get(j));
            }
        }
        
        return colide;
    }
    
    
    public void addHorario(Horario h) {
        horarios.add(h.clone());
    }
    
    
    public void addAluno(String aluno) {
        alunos.add(new Pair<>(aluno, 0));
    }
    
    
    public void addAluno(String aluno, int faltas) {
        alunos.add(new Pair<>(aluno, faltas));
    }
    
    
    public boolean containsAluno(String aluno) {
        boolean b = false;
        
        for (Pair<String, Integer> p : alunos) {
            if (p.getLeft().equals(aluno)) {
                b = true;
                break;
            }
        }
        
        return b;
    }
    
    
    public void removeAluno(String aluno) {
        Iterator it = alunos.iterator();
        
        while (it.hasNext()) {
            Pair<String, Integer> p = (Pair<String, Integer>)it.next();
            
            if (p.getLeft().equals(aluno)) {
                it.remove();
                break;
            }
        }
    }
    
    
    public void addPedidoAluno(String aluno) {
        pedidos.add(new Pair<>(aluno, false));
    }

    
    public void addPedidoAlunoTE(String alunoTE) {
        boolean b = false;
        
        if (pedidos.size() > 0) {
            for (int i = 0; i < pedidos.size(); i++) {
                if (!pedidos.get(i).getRight()) {
                    pedidos.add(i, new Pair<>(alunoTE, true));
                    b = true;
                    break;
                }
            }
            
            if (!b) {
                pedidos.add(new Pair<>(alunoTE, true));
            }
        }
        else {
            pedidos.add(new Pair<>(alunoTE, true));
        }
    }
    
    
    public void removePedidos(String aluno){
        Iterator it = pedidos.iterator();
        
        while (it.hasNext()) {
            String a = ((Pair<String, Boolean>)it.next()).getLeft();
            
            if (a.equals(aluno)) {
                it.remove();
            }
        }
    }
    
    
    public void addFalta(String aluno) {
        for (Pair<String, Integer> p : alunos) {
            if (p.getLeft().equals(aluno)) {
                p.setRight(p.getRight() + 1);
                break;
            }
        }
    }
    
    
    @Override
    public int hashCode() {
        return Arrays.hashCode(new Object[] {
            nomeTurno,
            isTeorico,
            capacidade,
            numAulas,
            horarios,
            alunos,
            pedidos
        });
    }
    
   
    @Override
    public Turno clone() {
        return new Turno(this);
    }
}
