
/**
 * Classe que define a interface Habitavel que é comum às classes de todos os tipos de
 * imóveis que tenham uma parte habitável. Possui os protótipos dos métodos comuns às
 * classes deste tipo.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

public interface Habitavel
{
   /**
    * @return Devolve o campo "numQuartos" de um imóvel habitável.
    */      
   public int getNumQuartos();
   
   
   /**
    * @return Devolve o campo "numWCs" de um imóvel habitável.
    */   
   public int getNumWCs();
   
   
   /**
    * @return Devolve o campo "numPorta" de um imóvel habitável.
    */   
   public int getNumPorta();
   
   
   /**
    * Altera o valor do campo "numQuartos" de um imóvel habitável.
    */   
   public void setNumQuartos(int numQuartos);
   
   
   /**
    * Altera o valor do campo "numWCs" de um imóvel habitável.
    */   
   public void setNumWCs(int numWCs);
   
   
   /**
    * Altera o valor do campo "numPorta" de um imóvel habitável.
    */   
   public void setNumPorta(int numPorta);
}

