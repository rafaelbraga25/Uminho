/**
 * Classe auxiliar para comparar ParStringDouble.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */
package gerevendasestatisticas;

import java.util.Comparator;

public class ParStringDoubleComparator implements Comparator<ParStringDouble> {
    
    /**
     * Caso os dois ParStringDouble tenham o mesmo getReal então 
     * desempata-se com a variável de instância String dos dois argumentos.
     *
     * @param  p1 ParStringDouble a comparar.
     * @param  p2 ParStringDouble a comparar.
     * @return Resultado da comparação.
     */
    public int compare(ParStringDouble p1, ParStringDouble p2) {
        if (p1.getReal() < p2.getReal()) {
            return 1;
        }
        if (p1.getReal() > p2.getReal()) {
            return -1;
        }
        else {
            return p1.getString().compareTo(p2.getString());
        } 
    }
}
