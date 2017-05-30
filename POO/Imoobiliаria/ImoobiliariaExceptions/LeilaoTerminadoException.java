/**
 * Classe referente à exceção que ocorre quando um utilizador tenta participar num leilão que já tenha
 * terminado.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


/**
 * Write a description of class LeilaoTerminadoException here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */

public class LeilaoTerminadoException extends Exception
{
   // Construtores
   
   public LeilaoTerminadoException() {
       super();
   }
   
   
   public LeilaoTerminadoException(String msg) {
       super(msg);
   }
}
