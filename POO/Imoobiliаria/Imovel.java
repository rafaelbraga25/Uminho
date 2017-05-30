/**
 * Classe que define um imóvel.
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 18.05.2016
 */

import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.Arrays;
import java.io.Serializable;

public class Imovel implements Serializable
{
    // Variáveis de classe
    
    public static final String emVenda = "Em venda";
    public static final String reservado = "Reservado";
    public static final String vendido = "Vendido";
    
    
    // Métodos de classe
    
    /**
     * Verifica se um estado é válido.
     * 
     * @param estado Recebe uma string referente ao estado.
     * @return Devolve true se a o estado for válido (i.e. "emVenda", "reservado" ou "vendido")
     *         e false caso contrário.
     */
    public static boolean estadoValido(String estado) {
        return (estado.equals(emVenda) || estado.equals(reservado) || estado.equals(vendido));
    }
    
    
    // Variáveis de instância
   
    private String id;
    private String rua;
    private double preco;
    private double precoMin;
    private List<Consulta> consultas;
    private String estado;
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param id       Código de identificação do imóvel.
     * @param rua      Rua onde se localiza o imóvel.
     * @param preco    Preço do imóvel.
     * @param precoMin Preço mínimo do imóvel.
     */
    public Imovel(String id, String rua, double preco, double precoMin) {
        this.id = id;
        this.rua = rua;
        this.preco = preco;
        this.precoMin = precoMin;
        consultas = new ArrayList<>();
        estado = Imovel.emVenda;
    }

    
    /**
     * Construtor de cópia.
     * 
     * @param i Um imóvel.
     */    
    public Imovel(Imovel i) {
        id = i.getId();
        rua = i.getRua();
        preco = i.getPreco();
        precoMin = i.getPrecoMin();
        consultas = i.getConsultas();
        estado = i.getEstado();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve campo "id" de um imóvel.
     */
    public String getId() { 
        return id; 
    }
    
    
    /**
     * @return Devolve campo "rua" de um imóvel.
     */    
    public String getRua() { 
        return rua; 
    }
    
    
    /**
     * @return Devolve campo "preco" de um imóvel.
     */    
    public double getPreco() { 
        return preco; 
    }
    
    
    /**
     * @return Devolve campo "precoMin" de um imóvel.
     */        
    public double getPrecoMin() { 
        return precoMin; 
    }
    
    
    /**
     * @return Devolve campo "consultas" de um imóvel.
     */        
    public List<Consulta> getConsultas() {
        return consultas.stream().map(Consulta::clone).collect(Collectors.toList());
    }
    
    
    /**
     * @return Devolve o tamanho da lista de consultas de um imóvel.
     */        
    public int getNumConsultas() {
        return consultas.size();
    }
    
    
    /**
     * @return Devolve o estado de um imóvel.
     */         
    public String getEstado() {
        return estado;
    }
    
    
    /**
     * Altera o valor do campo "id".
     */
    public void setId(String id) { 
        this.id = id; 
    }
    
    
    /**
     * Altera o valor do campo "rua".
     */    
    public void setRua(String rua) { 
        this.rua = rua; 
    }
    
    
    /**
     * Altera o valor do campo "preco".
     */    
    public void setPreco(double preco) { 
        this.preco = preco; 
    }
    
    
    /**
     * Altera o valor do campo "precoMin".
     */    
    public void setPrecoMin(double precoMin) { 
        this.precoMin = precoMin; 
    }
    
    
    /**
     * Altera o valor do campo "consultas".
     */     
    public void setConsultas(List<Consulta> consultas) {
        this.consultas = consultas.stream().map(Consulta::clone).collect(Collectors.toList());
    }
    
    
    /**
     * Altera o valor do campo "estado".
     */     
    public void setEstado(String estado) {
        this.estado = Imovel.estadoValido(estado) ? estado : Imovel.emVenda;
    }
    
    
    /**
     * Adiciona uma nova consulta à lista de consultas de um imóvel.
     */     
    public void addConsulta(Consulta c) {
        consultas.add(c.clone());
    }
    
    
    // Métodos complementares comuns
    
    /**
     * Verifica se um objeto é igual a uma instância da classe Imovel.
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
        
        Imovel i = (Imovel) o;
        
        return (id.equals(i.getId()) && rua.equals(i.getRua()) && preco == i.getPreco() && 
                precoMin == i.getPrecoMin() && estado.equals(i.getEstado()));
    }
    
    
    /**
     * @return Devolve um código de hash relativo a um imóvel.
     */ 
    public int hashCode() { 
        return Arrays.hashCode(new Object[] { rua, preco, precoMin, estado });
    }
    
    
    /**
     * @return Devolve uma representação textual da classe Imovel.
     */     
    public String toString() {
        StringBuilder sb = new StringBuilder("Imovel = ");
        
        sb.append(id);
        sb.append(" ");
        sb.append(rua);
        sb.append(" ");
        sb.append(preco);
        sb.append(" ");
        sb.append(precoMin);
        sb.append(" ");
        sb.append(estado);
        sb.append("\n");
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um imóvel.
     */ 
    public Imovel clone() { 
        return new Imovel(this); 
    }
}
