/**
 * Classe referente à exceção que ocorre quando um utilizador tenta efetuar uma operação para a qual
 * não tem permissão.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

package ImoobiliariaExceptions;


/**
 * Write a description of class SemAutorizacaoException here.
 * 
 * @author (your name) 
 * @version (a version number or a date)
 */
public class SemAutorizacaoException extends Exception
{
   // Construtores
   
   public SemAutorizacaoException() {
       super();
   }
   
   
   public SemAutorizacaoException(String msg) {
       super(msg);
   }
}
