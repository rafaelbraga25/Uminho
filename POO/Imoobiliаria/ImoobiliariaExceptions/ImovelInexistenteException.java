/**
 * Classe referente à exceção que ocorre quando se tenta aceder a um imóvel que não exista.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


/**
 * Write a description of class ImovelInexistenteException here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ImovelInexistenteException extends Exception
{
     // Construtores
   
   public ImovelInexistenteException() {
       super();
   }
   
   
   public ImovelInexistenteException(String msg) {
       super(msg);
   }
}
