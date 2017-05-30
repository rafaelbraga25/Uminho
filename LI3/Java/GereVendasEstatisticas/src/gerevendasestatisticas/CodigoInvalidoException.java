/**
 * Classe derivada da classe Exception que representa a exceção lançada
 * por um códido de produto ou de cliente inválido. Um código é inválido
 * se for vazio.
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */


package gerevendasestatisticas;


public class CodigoInvalidoException extends Exception {
    
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public CodigoInvalidoException() {
        super();
    }
    
    
    /**
     * Construtor por partes.
     * 
     * @param message Mensagem que pode ser mostrada em ecrã quando a exceção
     *                é lançada.
     */
    public CodigoInvalidoException(String message) {
        super(message);
    }
}
