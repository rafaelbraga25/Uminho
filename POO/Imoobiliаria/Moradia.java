
/**
 * Classe que define um imóvel do tipo Moradia.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import java.util.Arrays;

public class Moradia extends Imovel implements Habitavel
{
    // Variáveis de classe
    
    public enum TipoMoradia {
        Isolada, Geminada, Banda, Gaveto
    }
    
    
    // Variáveis de instância
    
    private TipoMoradia tipo;       // Tipo da moradia (i.e. isolada, geminada, banda ou gaveto).
    private double areaImplantacao;
    private double areaTotal;
    private double areaTerreno;
    private int numQuartos;
    private int numWCs;    
    private int numPorta;
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param idImovel        Código de identificação da moradia.
     * @param rua             Rua onde se localiza a moradia.
     * @param preco           Preço da moradia.
     * @param precoMin        Preço mínimo da moradia.
     * @param tipo            Tipo da moradia.
     * @param areaImplantacao Área de implantação da moradia.
     * @param areaTotal       Área total da moradia.
     * @param areaTerreno     Área do terreno envolvente.
     * @param numQuartos      Número de quartos.
     * @param numWCs          Número de WCs.
     * @param numPorta        Número da porta.
     */     
    public Moradia(String idImovel, String rua, double preco, double precoMin, TipoMoradia tipo, 
                   double areaImplantacao, double areaTotal, double areaTerreno, int numQuartos, int numWCs, 
                   int numPorta) { 
        super(idImovel, rua, preco, precoMin);
        this.tipo = tipo;
        this.setAreaImplantacao(areaImplantacao);
        this.setAreaTotal(areaTotal);
        this.setAreaTerreno(areaTerreno);
        this.setNumQuartos(numQuartos);
        this.setNumWCs(numWCs);        
        this.setNumPorta(numPorta);
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param m Uma moradia.
     */      
    public Moradia(Moradia m) { 
        super(m);
        tipo = m.getTipo();
        areaImplantacao = m.getAreaImplantacao();
        areaTotal = m.getAreaTotal();
        areaTerreno = m.getAreaTerreno();
        numQuartos = m.getNumQuartos();
        numWCs = m.getNumWCs();        
        numPorta = m.getNumPorta();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "tipo" de uma moradia.
     */     
    public TipoMoradia getTipo() { 
        return tipo; 
    }
    
    
    /**
     * @return Devolve o campo "areaImplantacao" de uma moradia.
     */     
    public double getAreaImplantacao() { 
        return areaImplantacao; 
    }
    
    
    /**
     * @return Devolve o campo "areaTotal" de uma moradia.
     */      
    public double getAreaTotal() { 
        return areaTotal; 
    }
    
    
    /**
     * @return Devolve o campo "areaTerreno" de uma moradia.
     */      
    public double getAreaTerreno() { 
        return areaTerreno; 
    }
    
    
    /**
     * @return Devolve o campo "tipo" de uma moradia.
     */      
    public void setTipo(TipoMoradia tipo) {
        this.tipo = tipo;
    }
    
    
    /**
     * Altera o valor do campo "areaImplantacao".
     */    
    public void setAreaImplantacao(double areaImplantacao) {
        this.areaImplantacao = (areaImplantacao >= 0) ? areaImplantacao : 0;
    }
    
    
    /**
     * Altera o valor do campo "areaTotal".
     */        
    public void setAreaTotal(double areaTotal) {
        this.areaTotal = (areaTotal >= 0) ? areaTotal : 0;
    }
    
    
    /**
     * Altera o valor do campo "areaTerreno".
     */        
    public void setAreaTerreno(double areaTerreno) {
        this.areaTerreno = (areaTerreno >= 0) ? areaTerreno : 0;
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Moradia.
     * 
     * @param o Objeto ao qual se quer efetuar a comparação.
     * @return Devolve true caso o objeto seja igual ou false, caso contrário.
     */      
    public boolean equals(Object o) {
         if (this == o) {
            return true;
        }
        
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
        }
        
        Moradia m = (Moradia) o;
        
        return (super.equals(m) && tipo == m.getTipo() && areaImplantacao == m.getAreaImplantacao() && 
                areaTotal == m.getAreaTotal() && areaTerreno == m.getAreaTerreno() &&
                numQuartos == m.getNumQuartos() && numWCs == m.getNumWCs() && numPorta == m.getNumPorta());
    }
    
    
    /**
     * @return Devolve o código de hash relativo a uma moradia.
     */        
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { tipo, areaImplantacao, areaTotal, areaTerreno, numQuartos,
                                              numWCs, numPorta }) + super.hashCode();
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Moradia.
     */     
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append("Moradia: ");
        sb.append(tipo.name());
        sb.append(" ");
        sb.append(areaImplantacao);
        sb.append(" ");
        sb.append(areaTotal);
        sb.append(" ");
        sb.append(areaTerreno);
        sb.append(" ");
        sb.append(numQuartos);        
        sb.append(" ");
        sb.append(numWCs);        
        sb.append(" ");        
        sb.append(numPorta);        
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um terreno.
     */    
    public Moradia clone() { 
        return new Moradia(this); 
    }
    
    
    // Métodos que implementam uma interface
    
    /**
     * @return Devolve o campo "numQuartos" de uma moradia.
     */     
    public int getNumQuartos() { 
        return numQuartos; 
    }

    
    /**
     * @return Devolve o campo "numWCs" de uma moradia.
     */     
    public int getNumWCs() { 
        return numWCs; 
    }    
    
    
    /**
     * @return Devolve o campo "numPorta" de uma moradia.
     */     
    public int getNumPorta() { 
        return numPorta; 
    }
    
    
    /**
     * Altera o valor do campo "numQuartos".
     */    
    public void setNumQuartos(int numQuartos) {
        this.numQuartos = (numQuartos >= 0) ? numQuartos : 0;
    }
    
    
    /**
     * Altera o valor do campo "numWCs".
     */    
    public void setNumWCs(int numWCs) {
        this.numWCs = (numWCs >= 0) ? numWCs : 0;
    }    
    
    
    /**
     * Altera o valor do campo "numPorta".
     */    
    public void setNumPorta(int numPorta) {
        this.numPorta = (numPorta >= 0) ? numPorta : 0;
    }
}
