package Business;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;


public class Aluno extends Utilizador {
    
    private final boolean isTE;
    private final Map<String, List<String>> turnos;
    private final List<Pair<String, String>> pedidos;
    
    
    public Aluno(String nomeUtilizador, String password, boolean isTE) {
        super(nomeUtilizador, password);
        
        this.isTE = isTE;
        turnos = new HashMap<>();
        pedidos = new ArrayList<>();
    }
    
    
    public Aluno(String nomeUtilizador, String password, boolean isTE,
            Map<String, List<String>> turnos, 
            List<Pair<String, String>> pedidos) {
        super(nomeUtilizador, password);
        
        this.isTE = isTE;
        this.turnos = new HashMap<>();
        
        turnos.keySet().forEach((s) -> {
            this.turnos.put(s, new ArrayList<>(turnos.get(s)));
        });
        
        this.pedidos = new ArrayList<>(pedidos);
    }
    
    
    public Aluno(Aluno a) {
        super(a);
      
        isTE = a.isTE;
        turnos = a.getTurnos();
        pedidos = a.getPedidos();
    }
    
    
    public boolean isTE() {
        return isTE;
    }
    
    
    public Map<String, List<String>> getTurnos() {
        Map<String, List<String>> map = new HashMap<>();
        
        turnos.keySet().forEach((s) -> {
            map.put(s, new ArrayList<>(turnos.get(s)));
        });
         
        return map;
    }
    
    
    public List<Pair<String, String>> getPedidos() {
        return new ArrayList<>(pedidos);
    }
    
    
    public void addTurno(String uc, String turno) {
        List<String> turnosUC = turnos.get(uc);
        
        if (turnosUC == null) {
            turnosUC = new ArrayList<>();
            turnosUC.add(turno);
            turnos.put(uc, turnosUC);
        } else {
            turnosUC.add(turno);
        }
    }
    
    
    public void removeTurno(String uc, String turno) {
        List<String> turnosUC = turnos.get(uc);
        
        if (turnosUC != null) {
            turnosUC.remove(turno);
        }
    }
    
    
    public void addPedido(String uc, String turno) {
        if (!pertenceTurno(uc, turno)) {
            pedidos.add(new Pair(uc, turno));
        }
    }
    
    
    private boolean pertenceTurno(String uc, String turno) {
        boolean pertence = false;
        List<String> turnosUC = turnos.get(uc);
        
        if (turnosUC != null) {
            pertence = turnosUC.contains(turno);
        } 
            
        return pertence;
    }
    
    
    public void cancelarPedido(String uc, String turno) {
        Iterator it = pedidos.iterator();
        
        while (it.hasNext()) {
            Pair<String, String> p = (Pair<String, String>)it.next();
            
            if (p.getLeft().equals(uc) && p.getRight().equals(turno)) {
                it.remove();
                break;
            }
        }
    }
    
    
    @Override
    public int hashCode() {
        return super.hashCode() +
                Arrays.hashCode(new Object[] {
                    isTE
                });
    }
    
    
    @Override
    public Aluno clone() {
        return new Aluno(this);
    }
}
