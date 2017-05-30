/**
 * Classe referente à exceção que ocorre quando se tenta registar um imóvel que já exista.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


/**
 * Write a description of class ImovelExisteException here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class ImovelExisteException extends Exception
{
    // Construtores
   
   public ImovelExisteException() {
       super();
   }
   
   
   public ImovelExisteException(String msg) {
       super(msg);
   }
}
