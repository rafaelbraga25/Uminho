/**
 * Classe auxiliar para a exibição de resultados por página.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendas;

import static java.util.stream.Collectors.joining;

import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.function.Function;

public class Paginacao
{
    // Variáveis de instância
    
    int tamanhoPag;   // Número de elementos a exibir por cada página.
    int numPags;      // Número total de páginas.
    int pag;          // Página atual.
    int index;        // Índice atual da lista de strings.
    List<String> lst; // Lista de strings dos elementos a exibir.
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param tamanhoPag Número de elementos a exibir por cada página.
     * @param lst        Lista de strings dos elementos a exibir.
     */    
    public Paginacao(int tamanhoPag, List<String> lst) {
        this.tamanhoPag = tamanhoPag;
        this.lst = new ArrayList<>(lst);
        index = 0;
        pag = 1;
        this.calcNumPags();
    }
    
    /**
     * Construtor de cópia.
     * 
     * @param g Uma instância da classe Paginacao.
     */
    public Paginacao(Paginacao p) {
        tamanhoPag = p.getTamanhoPag();
        numPags = p.getNumPags();
        index = p.getIndex();
        lst = p.getLst();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve campo "tamanhoPag" de uma instância da classe Paginacao.
     */    
    public int getTamanhoPag() {
        return tamanhoPag;
    }
    
    /**
     * @return Devolve campo "numPags" de uma instância da classe Paginacao.
     */    
    public int getNumPags() {
        return numPags;
    }
    
    /**
     * @return Devolve campo "pag" de uma instância da classe Paginacao.
     */    
    public int getPag() {
        return pag;
    }
    
    /**
     * @return Devolve campo "index" de uma instância da classe Paginacao.
     */     
    public int getIndex() {
        return index;
    }
    
    /**
     * @return Devolve campo "lst" de uma instância da classe Paginacao.
     */     
    public List<String> getLst() {
        return lst;
    }
    
    /**
     * @return Devolve o número de elementos presentes no campo "lst" de uma instância da classe Paginacao.
     */     
    public int getNumElements() {
        return lst.size();
    }
    
    /**
     * Exibe a página seguinte.
     * 
     * @param f Função a aplicar a cada elemento da lista de Strings.
     * @return i Devolve o número de elementos impressos.
     */
    public int nextPage(Function<String, Void> f) {
        int i = 0;
        
        if (pag <= numPags) {
            for (; i < tamanhoPag && index < lst.size(); i++, index++) {
                f.apply(lst.get(index));
            }
        
            pag++;
        }
        
        return i;
    }
    
    /**
     * Exibe a página anterior.
     * 
     * @param f Função a aplicar a cada elemento da lista de Strings.
     * @return elUltimaPag Número de elementos presentes na última página.
     */
    public int previousPage(Function<String, Void> f) {
        int elUltimaPag = 0;
        int ret = 0;
     
        if (pag > 1) {
            if (pag == numPags) {
                elUltimaPag = lst.size() - (tamanhoPag * (numPags - 1));
                ret = elUltimaPag;
                elUltimaPag += tamanhoPag;
                    
                index -= elUltimaPag;
            }
            else {
                index -= (2 * tamanhoPag);
                ret = tamanhoPag;
            }
        
            pag--;
            
            for (int i = 0; i < tamanhoPag && index < lst.size(); i++, index++) {
                f.apply(lst.get(index));
            }
        }
        
        return ret;
    }
    
    /**
     * Permite ir para a página recebida como parâmetro.
     *
     * @param pag Número da página.
     * @param f Função a aplicar a cada elemento da lista de Strings.
     */
    public int goToPage(int pag, Function<String, Void> f) {
        int i = 0;
        
        if (pag <= numPags && pag > 0) {
            this.pag = pag;
            index = (pag - 1) * tamanhoPag;
            
            for (; i < tamanhoPag && index < lst.size(); i++, index++) {
                f.apply(lst.get(index));
            }
        }
        
        return index;
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Paginacao.
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
        
        Paginacao p = (Paginacao) o;
        
        return (tamanhoPag == p.getTamanhoPag() && numPags == p.getNumPags() && pag == p.getPag() &&
                index == p.getIndex() && lst.equals(p.getLst()));
    }
    
    
    /**
     * @return Devolve um código de hash relativo a uma instância da classe Paginacao.
     */ 
    public int hashCode() {
        return Arrays.hashCode(new Object[] { tamanhoPag, numPags, pag, index, lst });
    }
    
    
    /**
     * @return Devolve uma representação textual de uma instância da classe Paginacao.
     */ 
    public String toString() {
        StringBuilder sb = new StringBuilder("Paginacao: ");
        
        sb.append(tamanhoPag);
        sb.append(" ");
        sb.append(numPags);
        sb.append(" ");
        sb.append(pag);
        sb.append(" ");
        sb.append(index);
        sb.append("\n");
        
        sb.append(lst.stream()
                     .collect(joining("\n")));
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um imóvel.
     */ 
    public Paginacao clone() {
        return new Paginacao(this);
    }
    
    
    // Métodos privados
    
    /**
     * Calcula o número de paginas necessárias para exibir as strings da lista dos elementos, colocando o
     * resultado no campo "numPags".
     */
    private void calcNumPags() {
        double aux = lst.size();
      
        /* Divide o tamanho da lista de strings pelo número de elementos a exibir por página */
        
        numPags = (int) Math.ceil(aux / tamanhoPag);
    }
    
}
