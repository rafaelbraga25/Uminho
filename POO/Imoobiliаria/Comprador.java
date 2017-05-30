
/**
 * Classe que define um comprador.
 * Extende a classe Utilizador.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import static java.util.stream.Collectors.joining;

import java.util.GregorianCalendar;
import java.util.List;
import java.util.Set;
import java.util.HashSet;
import java.util.stream.Collectors;
import java.util.Arrays;

public class Comprador extends Utilizador
{
    // Variáveis de instância
    
    private boolean participaLeilao; // Indica se o comprador pretende participar num leilão.
    private double limite;           // Quantia máxima que o comprador está disposto a dar num leilão.
    private double incrementos;      // Valor de incremento entre as licitações num leilão.
    private double minutos;          // Minutos entre licitações.
    private Set<Imovel> favoritos;   // Lista de imóveis favoritos de um comprador.
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param email           Email do comprador.
     * @param nome            Nome do comprador.
     * @param password        Password.
     * @param morada          Morada do comprador.
     * @param dataNascimento  Data de nascimento do comprador.
     * @param participaLeilao Se o comprador pretende participar num leilão
     * @param limite          Quantia máxima que o comprador está disposto a dar num leilão.
     * @param incrementos     Valor de incremento entre as licitações num leilão.
     * @param minutos         minutos do leilão.
     * @param favoritos       Lista dos imóveis favoritos do comprador.
     */    
    public Comprador(String email, String nome, String password, String morada, GregorianCalendar dataNascimento,
                     boolean participaLeilao, double limite, double incrementos, double minutos) {
        super(email, nome, password, morada, dataNascimento);
        this.participaLeilao = participaLeilao;
        this.limite = limite;
        this.incrementos = incrementos;
        this.minutos = minutos;
        favoritos = new HashSet<>();
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param c Um comprador.
     */   
    public Comprador(Comprador c) { 
        super(c); 
        this.participaLeilao = c.participaLeilao();
        this.limite = c.getLimite();
        this.incrementos = c.getIncrementos();
        this.minutos = c.getMinutos();
        this.favoritos = c.getFavoritos();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve o campo "participaLeilao" de um comprador.
     */    
    public boolean participaLeilao() {
        return participaLeilao;
    }
    
    
    /**
     * @return Devolve o campo "limite" de um comprador.
     */    
    public double getLimite() {
        return limite;
    }
   
    
    /**
     * @return Devolve o campo "incrementos" de um comprador.
     */    
    public double getIncrementos() {
        return incrementos;
    }
    
    
    /**
     * @return Devolve o campo "minutos" de um comprador.
     */    
    public double getMinutos() {
        return minutos;
    }
    
    
    /**
     * @return Devolve o campo "favoritos" de um comprador.
     */    
    public Set<Imovel> getFavoritos() {
        return favoritos.stream().map(Imovel::clone).collect(Collectors.toSet());
    }
    
    
    /**
     * Altera o valor do campo "participaLeilao".
     */    
    public void setParticipaLeilao(boolean participaLeilao) {
        this.participaLeilao = participaLeilao;
    }
    
    
    /**
     * Altera o valor do campo "limite".
     */    
    public void setLimite(double limite) {
        this.limite = limite;
    }
    
    
    /**
     * Altera o valor do campo "incrementos".
     */    
    public void setIncrementos(double incrementos) {
        this.incrementos = incrementos;
    }
    
    
    /**
     * Altera o valor do campo "minutos".
     */    
    public void setMinutos(double minutos) {
        this.minutos = minutos;
    }
    
    
    /**
     * Altera a lista de imóveis favoritos.
     */    
    public void setFavoritos(Set<Imovel> favoritos) {
        this.favoritos = favoritos.stream().map(Imovel::clone).collect(Collectors.toSet());
    }
    
    
     /**
     * Adiciona um novo favorito à lista de imóveis favoritos.
     */   
    public void addFavorito(Imovel i) {
        favoritos.add(i.clone());
    }
    
   
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Comprador.
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
        
        Comprador c = (Comprador) o;   
        
        return (super.equals(c) && favoritos.equals(c.getFavoritos()) && 
                participaLeilao == c.participaLeilao() && limite == c.getLimite() && 
                incrementos == c.getIncrementos() && minutos == c.getMinutos());
    }
    
    
    /**
     * @return Devolve um código de hash relativo a um comprador.
     */    
    public int hashCode() {
        return Arrays.hashCode(new Object[] { participaLeilao, favoritos, limite, incrementos, minutos }) + 
               super.hashCode();
    } 
    
    
    /**
     * @return Devolve uma representação textual da classe Comprador.
     */       
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append(participaLeilao);
        sb.append(" ");
        sb.append(limite);
        sb.append(" ");
        sb.append(incrementos);
        sb.append(" ");
        sb.append(minutos);
        sb.append("\n");
        
        sb.append(favoritos.stream()
                           .map(Imovel::toString)
                           .collect(joining("\n")));
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um comprador.
     */       
    public Comprador clone() {
        return new Comprador(this);
    }
}
