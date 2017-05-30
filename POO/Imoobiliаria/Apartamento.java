
/**
 * Classe que define um imóvel do tipo Apartamento.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.1016
 */

import java.util.Arrays;

public class Apartamento extends Imovel implements Habitavel
{
    // Variáveis de classe
    
    public enum TipoApartamento {
        Simples, Duplex, Triplex
    }
    
    
    // Variáveis de instância
    
    private TipoApartamento tipo; // Tipo de apartamento (i.e. Simples, Duplex, ou Triplex)
    private double areaTotal;
    private int numQuartos;
    private int numWCs;
    private int numPorta;
    private int numAndar;
    private boolean possuiGaragem;
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param idImovel      Código de identificação.
     * @param rua           Rua onde se localiza o apartamento.
     * @param preco         Preço pedido pelo apartamento.
     * @param precoMin      Preço mínimo pedido pelo vendedor.
     * @param tipo          Tipo de apartamento.
     * @param areaTotal     Área do apartamento.
     * @param numQuartos    Número de quartos.
     * @param numWCs        Número de casas de banho.
     * @param numPorta      Número de porta.
     * @param numAndar      Andar do apartamento.
     * @param possuiGaragem Se possui ou não garagem.
     */
    public Apartamento(String idImovel, String rua, double preco, double precoMin, TipoApartamento tipo, 
                       double areaTotal, int numQuartos, int numWCs, int numPorta, int numAndar, 
                       boolean possuiGaragem) {
        super(idImovel, rua, preco, precoMin);
        this.tipo = tipo;
        this.setAreaTotal(areaTotal);
        this.setNumQuartos(numQuartos);
        this.setNumWCs(numWCs);
        this.setNumPorta(numPorta);
        this.setNumAndar(numAndar);
        this.possuiGaragem = possuiGaragem;
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param a Um apartamento.
     */
    public Apartamento(Apartamento a) { 
        super(a);
        tipo = a.getTipo();
        areaTotal = a.getAreaTotal();
        numQuartos = a.getNumQuartos();
        numWCs = a.getNumWCs();
        numPorta = a.getNumPorta();
        numAndar = a.getNumAndar();
        possuiGaragem = a.possuiGaragem();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "tipo" de um apartamento.
     */
    public TipoApartamento getTipo() { 
        return tipo; 
    }
    
    
    /**
     * @return Devolve o campo "areaTotal" de um apartamento.
     */
    public double getAreaTotal() { 
        return areaTotal; 
    }
    
    
    /**
     * @return Devolve o campo "numAndar" de um apartamento.
     */
    public int getNumAndar() { 
        return numAndar; 
    }
    
    
    /**
     * @return Devolve o campo "possuiGaragem" de um apartamento.
     */
    public boolean possuiGaragem() { 
        return possuiGaragem; 
    }
    
    
    /**
     * Altera o campo "tipo" de um apartamento.
     */
    public void setTipo(TipoApartamento tipo) {
        this.tipo = tipo;
    }
    
    
    /**
     * Altera o campo "areaTotal" de um apartamento.
     */
    public void setAreaTotal(double areaTotal) {
        this.areaTotal = (areaTotal >= 0) ? areaTotal : 0;
    }
    
    
    /**
     * Altera o campo "numAndar" de um apartamento.
     */
    public void setNumAndar(int numAndar) {
        this.numAndar = (numAndar >= 0) ? numAndar : 0;
    }
    
    
    /**
     * Altera o campo "possuiGaragem" de um apartamento.
     */
    public void setPossuiGaragem(boolean possuiGaragem) { 
        this.possuiGaragem = possuiGaragem; 
    }  
   
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objecto é igual a uma instância da classe Apartamento.
     * 
     * @param o Objecto ao qual se quer efectuar a comparação.
     * @return Devolve true caso o objecto seja igual ou false, caso contrário.
     */
    public boolean equals(Object o) {
         if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        Apartamento a = (Apartamento) o;
        
        return (super.equals(a) && tipo == a.getTipo() && areaTotal == a.getAreaTotal() &&
                numQuartos == a.getNumQuartos() && numWCs == a.getNumWCs() && numPorta == a.getNumPorta() && 
                numAndar == a.getNumAndar() && possuiGaragem == a.possuiGaragem());
    }
    
    
    /**
     * @return Devolve o código de hash relativo a um apartamento.
     */
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { tipo, areaTotal, numQuartos, numWCs, numPorta, numAndar,
                                              possuiGaragem }) + super.hashCode();  
    }
    
    
    /**
     * @return Devolve uma representação textual de apartamento.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append("Apartamento = ");
        sb.append(tipo.name());
        sb.append(" ");
        sb.append(areaTotal);
        sb.append(" ");
        sb.append(numQuartos);        
        sb.append(" ");
        sb.append(numWCs);        
        sb.append(" ");
        sb.append(numPorta);
        sb.append(" ");
        sb.append(numAndar);        
        sb.append(" ");
        sb.append(possuiGaragem);        
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um apartamento.
     */
    public Apartamento clone() { 
        return new Apartamento(this); 
    }
    
    
    // Métodos que implementam uma interface
    
    /**
     * @return Devolve o campo "numQuartos" de um apartamento.
     */
     public int getNumQuartos() { 
        return numQuartos; 
    }
    
    
    /**
     * @return Devolve o campo "numWCs" de um apartamento.
     */
    public int getNumWCs() { 
        return numWCs; 
    }
    
    
    /**
     * @return Devolve o campo "numPorta" de um apartamento.
     */
    public int getNumPorta() { 
        return numPorta; 
    }
    
    
    /**
     * Altera o campo "numQuartos" de um apartamento.
     */
    public void setNumQuartos(int numQuartos) {
        this.numQuartos = (numQuartos >= 0) ? numQuartos : 0;
    }
    
    
    /**
     * Altera o campo "numWCs" de um apartamento.
     */
    public void setNumWCs(int numWCs) {
        this.numWCs = (numWCs >= 0) ? numWCs : 0;
    }
    
    
    /**
     * Altera o campo "numPorta" de um apartamento.
     */
    public void setNumPorta(int numPorta) {
        this.numPorta = (numPorta >= 0) ? numPorta : 0;
    }
}
