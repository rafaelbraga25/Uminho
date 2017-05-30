/**
 * Classe referente à exceção que ocorre quando se tenta registar um utilizador já exista.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


public class UtilizadorExistenteException extends Exception
{
   // Construtores
   
   public UtilizadorExistenteException() {
       super();
   }
   
   
   public UtilizadorExistenteException(String msg) {
       super(msg);
   }
}
