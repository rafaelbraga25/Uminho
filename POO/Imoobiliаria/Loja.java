
/**
 * Classe que define um imóvel do tipo Loja.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

import java.util.Arrays;

public class Loja extends Imovel
{   
    // Variáveis de instância
    
    private double area;
    private boolean possuiWC;
    private String tipo;      // Indica o tipo de negócio viável para a loja.
    private int numPorta;
    
       
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param idImovel  Código de identificação
     * @param rua       Rua onde se localiza a loja.
     * @param preco     Preço pedido pela loja.
     * @param precoMin  Preço mínimo pedido pelo vendedor.
     * @param area      Área da loja.
     * @param possuiWC  Se possui casa de banho ou não.
     * @param tipo      Tipo de negócio da loja.
     * @param numPorta  Número de porta.
     */
    public Loja(String idImovel, String rua, double preco, double precoMin, double area, boolean possuiWC, 
                String tipo, int numPorta) {
        super(idImovel, rua, preco, precoMin);
        this.setArea(area);
        this.possuiWC = possuiWC;
        this.tipo = tipo;
        this.numPorta = numPorta;
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param l Uma loja.
     */
    public Loja(Loja l) { 
        super(l);
        tipo = l.getTipo();
        area = l.getArea();
        possuiWC = l.possuiWC();
        tipo = l.getTipo();
        numPorta = l.getNumPorta();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "area" de uma loja.
     */
    public double getArea() { 
        return area; 
    }
    
    
    /**
     * @return Devolve o campo "possuiWC" de uma loja.
     */
    public boolean possuiWC() { 
        return possuiWC; 
    }
    
    
    /**
     * @return Devolve o campo "tipo" de uma loja.
     */
    public String getTipo() { 
        return tipo; 
    }
    
    
    /**
     * @return Devolve o campo "numPorta" de uma loja.
     */
    public int getNumPorta() { 
        return numPorta; 
    }
    
    
    /**
     * Altera o campo "area" de uma loja.
     */
    public void setArea(double area) {
        this.area = (area >= 0) ? area : 0;
    }
    
    
    /**
     * Altera o campo "possuiWC" de uma loja.
     */
    public void setPossuiWC(boolean possuiWC) {
        this.possuiWC = possuiWC;
    }
    
    
    /**
     * Altera o campo "tipo" de uma loja.
     */
    public void setTipo(String tipo) {
        this.tipo = tipo;
    }
    
    
    /**
     * Altera o campo "numPorta" de uma loja.
     */
    public void setNumPorta(int numPorta) {
        this.numPorta = (numPorta >= 0) ? numPorta : 0;
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
        
        Loja l = (Loja) o;
        
        return (super.equals(l) && area == l.getArea() && possuiWC == l.possuiWC() && tipo == l.getTipo() 
                && numPorta == l.getNumPorta());
    }
    
    /**
     * @return Devolve o código de hash relativo a uma loja.
     */
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { area, possuiWC, tipo, numPorta }) + super.hashCode(); 
    }
    
    
    /**
     * @return Devolve uma representação textual de loja.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append("Loja: ");
        sb.append(area);
        sb.append(" ");
        sb.append(possuiWC);        
        sb.append(" ");
        sb.append(tipo);        
        sb.append(" ");
        sb.append(numPorta); 
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de uma loja.
     */
    public Loja clone() { 
        return new Loja(this); 
    }
}
