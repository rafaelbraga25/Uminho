/**
 * Classe referente à exceção que ocorre quando se tenta inserir um estado inválido (i.e. diferente de
 * emVenda, vendido ou reservado).
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


/**
 * Write a description of class EstadoInvalidoException here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class EstadoInvalidoException extends Exception
{
    // Construtores
   
   public EstadoInvalidoException() {
       super();
   }
   
   
   public EstadoInvalidoException(String msg) {
       super(msg);
   }
}
