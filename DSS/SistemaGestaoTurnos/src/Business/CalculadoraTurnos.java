package Business;


import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;


public final class CalculadoraTurnos {
    
    public static void calcTurnos(Map<String, Aluno> alunos, 
            Map<String, UC> ucs) {
        List<UC> list = 
                CalculadoraTurnos.getUCsOrdenadas(ucs);
        
        list.forEach(u -> {
            Map<String, Turno> turnosTeo = u.getTurnosTeoricos();
            Map<String, Aluno> alunosInscritos = 
                    CalculadoraTurnos.filtrarAlunosInscritos(alunos, u);
            List<Aluno> alunosInscritosList = 
                    new ArrayList<>(alunosInscritos.values());
            
            if (turnosTeo.size() > 0) {
                CalculadoraTurnos.calcTurnosTEO(u.getNome(), 
                        turnosTeo, alunosInscritosList);
            }
        });
        
        list.forEach((u) -> {  
            Map<String, Turno> turnosPraticos = u.getTurnosPraticos();
            Map<String, Aluno> alunosInscritos = 
                    CalculadoraTurnos.filtrarAlunosInscritos(alunos, u);
            
            alunosInscritos.values().forEach((a) -> {
                CalculadoraTurnos.calcTurnosPraticos(
                        u.getNome(), turnosPraticos, a, ucs, alunosInscritos);
            });
        });
    }
    
    
    private static List<UC> 
        getUCsOrdenadas(Map<String, UC> ucs) {
        List<UC> list = new ArrayList<>();
        
        ucs.values().forEach((u) -> {
            list.add(u);
        });
        
        Collections.sort(list, new UCComparator());
        
        return list;
    }
        
        
    private static Map<String, Aluno>
            filtrarAlunosInscritos(Map<String, Aluno> alunos, UC u) {
        Map<String, Aluno> map = new TreeMap<>(new AlunoComparator());
        
        alunos.values().stream()
                .filter((a) -> (u.alunoInscrito(a.getUsername())))
                .forEachOrdered((a) -> {
            map.put(a.getUsername(), a);
        });
        
        return map;
    }
            
    
    private static void calcTurnosTEO(String UC, 
                Map<String, Turno> turnosTeo, List<Aluno> alunos) {
        int alunosPorTurno = alunos.size() / turnosTeo.size();
        int i = 0;
        Turno ultimoTurno = null;
        
        for (Turno t : turnosTeo.values()) {
            ultimoTurno = t;
            
            for (int j = 0; i < alunos.size() && j < alunosPorTurno; i++, j++) {
                t.addAluno(alunos.get(i).getUsername());
                alunos.get(i).addTurno(UC, t.getNomeTurno());
            }
        }
        
        if (i < alunos.size() - 1 && ultimoTurno != null) {
            for (; i < alunos.size(); i++) {
                ultimoTurno.addAluno(alunos.get(i).getUsername());
                alunos.get(i).addTurno(UC, ultimoTurno.getNomeTurno());
            }
        }
    }
    
    
    private static void calcTurnosPraticos(String UC, 
            Map<String, Turno> turnosPraticos, Aluno aluno, 
            Map<String, UC> ucs, Map<String, Aluno> alunosInscritos) {
        List<Turno> turnosAluno = CalculadoraTurnos.getTurnosAluno(aluno, ucs);
        boolean b = false;
        
        for (Turno t : turnosPraticos.values()) {
            if (!t.turnoCheio()) {
                for (int i = 0; i < turnosAluno.size(); i++) { 
                    if (t.colide(turnosAluno.get(i))) {
                        break;
                    }
                    
                    if (i == turnosAluno.size() - 1) {
                        b = true;
                    }
                }
     

                if (b) {
                    t.addAluno(aluno.getUsername());
                    aluno.addTurno(UC, t.getNomeTurno());
                    break;
                }
            }
        }
        
        if (!b) {
            for (Turno t : turnosPraticos.values()) {
                if (t.turnoCheio() && 
                        turnosAluno.stream().allMatch(tA -> !tA.colide(t))) {
                    if (CalculadoraTurnos.trocarAluno(t, UC, turnosPraticos, 
                            alunosInscritos, ucs)) {
                        t.addAluno(aluno.getUsername());
                        aluno.addTurno(UC, t.getNomeTurno());
                        b = true;
                    }
                }
                
                if (b) {
                    break;
                }
            }
        }
        
        if (!b) {
            for (Turno t : turnosPraticos.values()) {
                if (!t.turnoCheio()) {
                    t.addAluno(aluno.getUsername());
                    aluno.addTurno(UC, t.getNomeTurno());
                    break;
                }
            }
        }
    }
    
    
    private static List<Turno> getTurnosAluno(Aluno a, Map<String, UC> ucs) {
        List<Turno> turnosAluno = new ArrayList<>();
        Map<String, List<String>> auxTurnosAluno = a.getTurnos();
        
        auxTurnosAluno.keySet().forEach((u) -> {
            List<String> auxList = auxTurnosAluno.get(u);
            Map<String, Turno> turnosUC = ucs.get(u).getTurnos();
            
            auxList.forEach((t) -> {
                turnosAluno.add(turnosUC.get(t));
            });
        });
        
        return turnosAluno;
    }
    
    
    private static boolean trocarAluno(Turno t, String UC, 
            Map<String, Turno> turnosP, Map<String, Aluno> alunos,
            Map<String, UC> ucs) {
        boolean trocaEfetuada = false;
        List<Pair<String, Integer>> alunosTurno = t.getAlunos();
        
        for (Pair<String, Integer> p : alunosTurno) {
            if (trocaEfetuada) {
                break;
            }
            
            Aluno aluno = alunos.get(p.getLeft());
            Map<String, List<String>> mapTurnos = aluno.getTurnos();
            List<Turno> turnosAluno = new ArrayList<>();
            
            mapTurnos.keySet().forEach((uc) -> {
                mapTurnos.get(uc)
                        .stream()
                        .filter((tu) -> 
                                (!(uc.equals(uc) && 
                                        tu.equals(t.getNomeTurno()))))
                        .forEachOrdered((tu) -> {
                    turnosAluno.add(ucs.get(uc).getTurnos().get(tu));
                });
            });
            
            
            for (Turno turno : turnosP.values()) {
                if (!turno.getNomeTurno().equals(t.getNomeTurno())) {
                    if (turnosAluno.stream()
                            .allMatch(tA -> !tA.colide(turno))) {
                        trocaEfetuada = true;
                        t.removeAluno(aluno.getUsername());
                        turno.addAluno(aluno.getUsername());
                        aluno.addTurno(UC, turno.getNomeTurno());
                        break;
                    }
                }
            }
        }
        
        return trocaEfetuada;
    }
}
