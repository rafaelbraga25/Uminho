
/**
 * Classe que define um imóvel do tipo Loja.
 * Extende a classe Loja.
 * Implementa a classe Habitavel.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga 
 * @version 21.05.2016
 */

import java.util.Arrays;

public class LojaHabitavel extends Loja implements Habitavel
{   
    // Variáveis de instância
    
    private Apartamento apartamento; // Parte habitável da loja corresponde a um apartamento.
   
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param idImovel  Código de identificação.
     * @param rua       Rua onde se localiza a loja habitável.
     * @param preco     Preço pedido pela loja habitável.
     * @param precoMin  Preço mínimo pedido pelo vendedor.
     * @param area      Área da loja habitável.
     * @param possuiWC  Se possui casa de banho ou não.
     * @param tipo      Tipo de negócio da loja habitável.
     * @param numPorta  Número de porta.
     */
    public LojaHabitavel(String idImovel, String rua, double preco, double precoMin, double area, 
                         boolean possuiWC, String tipo, int numPorta, Apartamento.TipoApartamento tipoAp, 
                         double areaAp, int numQuartos, int numWCs, int numAndar, boolean possuiGaragem) {
        super(idImovel, rua, preco, precoMin, area, possuiWC, tipo, numPorta);
        apartamento = new Apartamento(idImovel, rua, preco, precoMin, tipoAp, areaAp, numQuartos, numWCs, 
                                      numPorta, numAndar, possuiGaragem);
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param l Uma loja habitável.
     */
    public LojaHabitavel(LojaHabitavel l) { 
        super(l);
        apartamento = l.getApartamento();
    }
    
    // Métodos de instância
    
    /**
     * @return Devolve o apartamento correspondente à parte habitável de uma loja habitável.
     */
    public Apartamento getApartamento() {
        return apartamento.clone();
    }
 
    
    /**
     * @return Devolve o campo "tipo" do apartamento correspondente a uma loja habitável.
     */
    public Apartamento.TipoApartamento getTipoAp() {
        return apartamento.getTipo();
    }
    
    
    /**
     * @return Devolve o campo "área" do apartamento correspondente a uma loja habitável.
     */
    public double getAreaAp() {
        return apartamento.getAreaTotal();
    }
    
    
    /**
     * @return Devolve o campo "numAndar" do apartamento correspondente a uma loja habitável.
     */
    public int getNumAndar() {
        return apartamento.getNumAndar(); 
    }
    
    
    /**
     * @return Devolve o campo "possuiGaragem" do apartamento correspondente a uma loja habitável.
     */
    public boolean possuiGaragem() {
        return apartamento.possuiGaragem();
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objecto é igual a uma instância da classe Loja.
     * 
     * @param o Objecto ao qual se quer efectuar a comparação.
     * @return  Devolve true caso o objecto seja igual ou false, caso contrário.
     */
    public boolean equals(Object o) {
         if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        LojaHabitavel l = (LojaHabitavel) o;
        
        return (super.equals(l) && apartamento.equals(l.getApartamento()));
    }
    
    
    /**
     * @return Devolve o código de hash relativo a uma loja habitável.
     */
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { apartamento }) + super.hashCode(); 
    }
    
    
    /**
     * @return Devolve uma representação textual de loja habitável.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
      
        sb.append("Loja Habitavel: \n");
        sb.append(apartamento.toString());
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de uma loja habitável.
     */
    public LojaHabitavel clone() { 
        return new LojaHabitavel(this); 
    }
    
    
    // Métodos que implementam uma interface
    
    /**
     * @return Devolve o campo "numQuartos" da parte habitável de uma loja habitável.
     */
    public int getNumQuartos() {
        return apartamento.getNumQuartos();
    }
    
    
    /**
     * @return Devolve o campo "numWCs" da parte habitável de uma loja habitável.
     */
    public int getNumWCs() {
        return apartamento.getNumWCs();
    }
    
    
    /**
     * @return Devolve o campo "numPorta" de uma loja habitável.
     */
    public int getNumPorta() {
        return apartamento.getNumPorta();
    }
    
    
    /**
     * Altera o campo "numQuartos" da parte habitável de uma loja habitável.
     */
    public void setNumQuartos(int numQuartos) {
        apartamento.setNumQuartos(numQuartos);
    }
    
    
    /**
     * Altera o campo "numWCs" da parte habitável de uma loja habitável.
     */
    public void setNumWCs(int numWCs) {
        apartamento.setNumWCs(numWCs);
    }
    
    
    /**
     * Altera o campo "numPorta" de uma loja habitável.
     */
    public void setNumPorta(int numPorta) {
        apartamento.setNumPorta(numPorta);
    }
}
