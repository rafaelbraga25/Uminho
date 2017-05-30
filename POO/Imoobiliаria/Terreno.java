
/**
 * Classe que define um imóvel do tipo Terreno.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import java.util.Arrays;

public class Terreno extends Imovel
{
    // Variáveis de classe
    
    public enum TipoTerreno {
        Habitacao, Armazem
    }
    
    
    // Variáveis de instância
    
    private TipoTerreno tipo;     // Tipo de terreno (i.e. habitação ou armazém).
    private double diametro;      // Diâmetro das canalizações.
    private double kWh;           // KWh máximos suportados pela rede elétrica.
    private boolean existeAcesso; // Indica se existe acesso à rede de esgotos.
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param idImovel     Código de identificação do terreno.
     * @param rua          Rua onde se localiza o terreno.
     * @param preco        Preço do terreno.
     * @param precoMin     Preço mínimo do terreno.
     * @param tipo         Tipo do terreno.
     * @param diametro     Diametro das canalizações.
     * @param kWh          Capacidade máxima da rede elétrica.
     * @param existeAcesso Se existe, ou não, acesso à rede de esgotos.
     */    
    public Terreno(String idImovel, String rua, double preco, double precoMin, TipoTerreno tipo, 
                   double diametro, double kWh, boolean existeAcesso) { 
        super(idImovel, rua, preco, precoMin);
        this.tipo = tipo;
        this.setDiametro(diametro);
        this.setKWh(kWh);
        this.existeAcesso = existeAcesso;
    }

    
    /**
     * Construtor de cópia.
     * 
     * @param t Um terreno.
     */        
    public Terreno(Terreno t) { 
        super(t);
        tipo = t.getTipo();
        diametro = t.getDiametro();
        kWh = t.getKWh();
        existeAcesso = t.existeAcesso();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "tipo" de um terreno.
     */    
    public TipoTerreno getTipo() { 
        return tipo; 
    }
    
    
    /**
     * @return Devolve o campo "diametro" de um terreno.
     */        
    public double getDiametro() { 
        return diametro; 
    }
    
    
    /**
     * @return Devolve o campo "kWh" de um terreno.
     */        
    public double getKWh() { 
        return kWh; 
    }
    
    
    /**
     * @return Devolve o campo "existeAcesso" de um terreno.
     */        
    public boolean existeAcesso() { 
        return existeAcesso; 
    }
    
    
    /**
     * Altera o valor do campo "tipo".
     */     
    public void setTipo(TipoTerreno tipo) {
        this.tipo = tipo;
    }
    
    
    /**
     * Altera o valor do campo "diametro".
     */    
    public void setDiametro(double diametro) {
        this.diametro = (diametro >= 0) ? diametro : 0;
    }
    
    
    /**
     * Altera o valor do campo "kWh".
     */    
    public void setKWh(double kWh) {
        this.kWh = (kWh >= 0) ? kWh : 0;
    }
    
    
    /**
     * Altera o valor do campo "existeAcesso".
     */     
    public void setExisteAcesso(boolean existeAcesso) {
        this.existeAcesso = existeAcesso;
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Terreno.
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
        
        Terreno t = (Terreno) o;
        
        return (super.equals(t) && tipo == t.getTipo() && diametro == t.getDiametro() && 
                kWh == t.getKWh() && existeAcesso == t.existeAcesso());
    }
    
    
    /**
     * @return Devolve o código de hash relativo a um terreno.
     */
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { tipo, diametro, kWh, existeAcesso}) + super.hashCode(); 
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Terreno.
     */        
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append("Terreno: ");
        sb.append(tipo.name());
        sb.append(" ");
        sb.append(diametro);
        sb.append(" ");
        sb.append(kWh);
        sb.append(" ");
        sb.append(existeAcesso);        
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um terreno.
     */    
    public Terreno clone() { 
        return new Terreno(this); 
    }
}
