
/**
 * Classe que define um vendedor.
 * Extende a classe vendedor.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import static java.util.stream.Collectors.joining;

import java.util.GregorianCalendar;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.Arrays;

public class Vendedor extends Utilizador
{
    // Variáveis de instância
    
    List<Imovel> portfolio; // Lista de imóveis em venda.
    List<Imovel> historico; // Lista de imóveis vendidos.
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param email          Email do vendedor.
     * @param nome           Nome do vendedor.
     * @param password       Password.
     * @param morada         Morada do vendedor.
     * @param dataNascimento Data de nascimento do vendedor.
     */    
    public Vendedor(String email, String nome, String password, String morada, 
                    GregorianCalendar dataNascimento) {
        super(email, nome, password, morada, dataNascimento);
        portfolio = new ArrayList<>();
        historico = new ArrayList<>();
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param v Um vendedor.
     */   
    public Vendedor(Vendedor c) { 
        super(c); 
        this.portfolio = c.getPortfolio();
        this.historico = c.getHistorico();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve a lista dos imóveis em venda de um vendedor.
     */ 
    public List<Imovel> getPortfolio() {
        return portfolio.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * @return Devolve a lista dos imóveis vendidos de um vendedor.
     */   
    public List<Imovel> getHistorico() {
        return historico.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * Altera a lista dos imóveis em venda de um vendedor.
     */       
    public void setPortfolio(List<Imovel> portfolio) {
        this.portfolio = portfolio.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * Altera a lista dos imóveis vendidos de um vendedor.
     */      
    public void setHistorico(List<Imovel> historico) {
        this.historico = historico.stream().map(Imovel::clone).collect(Collectors.toList());
    }
    
    
    /**
     * Adiciona um imóvel à lista dos imóveis em venda de um vendedor.
     * 
     * @param i Imóvel a adicionar à lista dos imóveis em venda.
     */      
    public void addPortfolio(Imovel i) {
        portfolio.add(i.clone());
    }
    
    
    /**
     * Remove um imóvel da lista de imóveis em venda de um vendedor
     * 
     * @param i Imóvel a remover da lista de imóveis em venda.
     */
    public void removePortfolio(Imovel i) {
        for (int j = 0; j < portfolio.size(); j++) {
            if (i.getId().equals(portfolio.get(j).getId())) {
                portfolio.remove(j);
                break;
            }
        }
    }
    
    
    /**
     * Verifica se um dado imóvel existe na lista dos imóveis em venda de um vendedor.
     * 
     * @param i O imóvel.
     */     
    public boolean containsPortfolio(Imovel i) {
        return portfolio.contains(i);
    }
    
    
    /**
     * Verifica se um dado imóvel existe na lista dos imóveis em venda de um vendedor.
     * 
     * @param idImovel Código de identifição do imóvel.
     */     
    public boolean containsPortfolio(String idImovel) {
        boolean b = false;
        
        for (Imovel i : portfolio) {
            if (i.getId().equals(idImovel)) {
                b = true;
                break;
            }
        }
        
        return b;
    }
    
    
    /**
     * Adiciona um imóvel à lista dos imóveis vendidos de um vendedor.
     * 
     * @param i Imóvel a adicionar à lista de imóveis vendidos.
     */    
    public void addHistorico(Imovel i) {
        historico.add(i.clone());
    }
    
    
    /**
     * Devolve o número de imóveis vendidos por um vendedor.
     */    
    public int getNumImoveisVendidos() {
        return historico.size();
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Vendedor.
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
        
        Vendedor v = (Vendedor) o;   
        
        return (super.equals(v) && portfolio.equals(v.getPortfolio()) && historico.equals(v.getHistorico()));
    }
    
    
    /**
     * @return Devolve um código de hash relativo a um vendedor.
     */        
    public int hashCode() {
        return Arrays.hashCode(new Object[] { portfolio, historico }) + super.hashCode();
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Vendedor.
     */    
    public String toString() {
        StringBuilder sb = new StringBuilder(super.toString());
        
        sb.append(portfolio.stream()
                           .map(Imovel::toString)
                           .collect(joining("\n")));
                           
        sb.append(historico.stream()
                           .map(Imovel::toString)
                           .collect(joining("\n")));
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um vendedor.
     */     
    public Vendedor clone() {
        return new Vendedor(this);
    }
}