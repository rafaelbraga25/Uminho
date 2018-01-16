package Business;


import Data.DataFacade;
import java.util.List;
import java.util.Map;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rafae
 */
public final class GestaoTurnos {
    
    public static boolean 
        TrocarTurno(Aluno a, Map<String, Aluno> alunosUC, UC uc, 
            Turno tOrigem, Turno tDestino, DataFacade dataFacade) {
        boolean trocou = false;
        
        if (a.isTE()) {
            if (!tDestino.turnoCheio()) {
                GestaoTurnos.EfetuarTroca(a, uc, tOrigem, tDestino, dataFacade);
                trocou = true;
            }
        }
        
        if (!trocou) {
            List<Pair<String, Boolean>> pedidos = tOrigem.getPedidos();
            
            if (pedidos != null && pedidos.size() > 0) {
                String nomeAluno = pedidos.get(0).getLeft();
                
                if (tDestino.containsAluno(nomeAluno)) {
                    Aluno aluno = alunosUC.get(nomeAluno);
                    GestaoTurnos.EfetuarTroca(a, uc, tOrigem, tDestino, 
                            dataFacade);
                    GestaoTurnos.EfetuarTroca(aluno, uc, tDestino, tOrigem, 
                            dataFacade);
                    trocou = true;
                } 
            } 
        }
        
        if (!trocou) {
            if (a.isTE()) { 
                tDestino.addPedidoAlunoTE(a.getUsername());
            } else {
                tDestino.addPedidoAluno(a.getUsername());
            }
            
            a.addPedido(uc.getNome(), tDestino.getNomeTurno());
            
            dataFacade.addPedidos(uc.getNome(), tDestino.getNomeTurno(), 
                    tDestino.getPedidos());
        }
        
        return trocou;
    }
    
    
    public static boolean 
        TrocarAlunos(Aluno a1, String tA1, Aluno a2, String tA2, UC uc, 
                DataFacade dataFacade) {
        boolean trocou = false;
        Turno tAluno1 = uc.getTurnos().get(tA1);
        Turno tAluno2 = uc.getTurnos().get(tA2);
        
        if (tAluno1 != null && tAluno2 != null) {
            trocou = true;
            GestaoTurnos.EfetuarTroca(a1, uc, tAluno1, tAluno2, dataFacade);
            GestaoTurnos.EfetuarTroca(a2, uc, tAluno2, tAluno1, dataFacade);
        }
        
        return trocou;
    }
    
    
    private static void 
        EfetuarTroca(Aluno a, UC uc, Turno tOrigem, Turno tDestino, 
                DataFacade dataFacade) {
        tDestino.addAluno(a.getUsername());
        tOrigem.removeAluno(a.getUsername());
        uc.removePedidos(a.getUsername());
        a.removeTurno(uc.getNome(), tOrigem.getNomeTurno());
        a.addTurno(uc.getNome(), tDestino.getNomeTurno());
        
        dataFacade.removePedidosAluno(uc.getNome(), a.getUsername());
        
        dataFacade.removeAlunoTurno(uc.getNome(), tOrigem.getNomeTurno(), 
                a.getUsername());
        dataFacade.addAlunoTurno(uc.getNome(), tDestino.getNomeTurno(), 
                a.getUsername());
    }
}
