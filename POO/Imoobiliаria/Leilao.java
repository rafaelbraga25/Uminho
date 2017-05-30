
/**
 * Classe que define um leilão. 
 * 
 * @author Ana Paula Carvalho
 * @author João Pires Barreira
 * @author Rafael Braga
 * @version 21.05.2016
 */

import static java.util.stream.Collectors.joining;

import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.stream.Collectors;
import java.util.Calendar;
import java.util.GregorianCalendar;
import java.io.Serializable;

public class Leilao implements Serializable
{
    // Variáveis de instância
    
    private List<Comprador> compradores;      // Lista dos compradores inscritos no leilão. 
    private Map<Comprador, Double> montantes; // Mapeamento entre todos os compradores e os seus respetivos
                                              // montantes.
    private Imovel imovel;                    // Imóvel leiloado.
    private int horas;                        // Duração do leilão.
    private double montante;                  // Montante fornecido pelo comprador vencedor.
    private GregorianCalendar inicio;         // Contém a hora do início do leilão.
    
    
    // Construtores
    
    /**
     * Construtor por partes.
     * 
     * @param imovel  Imóvel leiloado.
     * @param horas   Duração do leilão.
     */
    public Leilao(Imovel imovel, int horas) {
        this.imovel = imovel.clone();
        this.horas = horas;
        compradores = new ArrayList<>();
        montantes = new HashMap<>();
        montante = 0;
        
        /* Inicia as horas do leilão. */
        
        inicio = new GregorianCalendar();
    }
    
    
    /**
     * Construtor de cópia.
     * 
     * @param l Um leilão.
     */
    public Leilao(Leilao l) {
        imovel = l.getImovel();
        horas = l.getHoras();
        compradores = l.getCompradores();
        montantes = l.getMontantes();
        montante = l.getMontante();
        inicio = l.getInicio();
    }
    
    
    // Métodos de instância
    
    /**
     * @return Devolve um imóvel.
     */
    public Imovel getImovel() {
        return imovel.clone();
    }
    
    
    /**
     * @return Devolve o campo "horas" de um leilão.
     */
    public int getHoras() {
        return horas;
    }
    
    
    /**
     * @return Devolve o maior montante fornecido entre os compradores do leilão.
     */
    public double getMontante() {
        return montante;
    }
    
    
    /**
     * @return Devolve a data de ínicio do leilão.
     */
    public GregorianCalendar getInicio() {
        return inicio;
    }
    
    
    /**
     * @return Devolve a lista de compradores que licitaram no leilão.
     */
    public List<Comprador> getCompradores() {
        return compradores.stream().map(Comprador::clone).collect(Collectors.toList());
    }
    
    
    /**
     * @return Devolve o mapeamemto entre todos os compradores registados no leilão e seus respetivos montantes.
     */
    public Map<Comprador, Double> getMontantes() {
        Map<Comprador, Double> temp = new HashMap<>();
        
        for (Comprador c : montantes.keySet()) {
            temp.put(c.clone(), montantes.get(c));
        }
        
        return temp;
    }
    
    
    /**
     * Adiciona um comprador à lista de compradores que participam leilão.
     */
    public void addComprador(Comprador c) {
        compradores.add(c.clone());
        
        /* Adiciona o comprador e o seu previsto montante ao mapa de compradores e seus montantes. */
        
        montantes.put(c.clone(), this.calcMontante(c));
    }
    
    
    /**
     * Percorre a lista dos compradores inscritos no leilão e calcula os seus totais gastos para licitar o
     * o imóvel leiloado. 
     * 
     * @return Devolve o email do comprador vencedor.
     */
    public String getVencedor() {
        String id = "";   // Email do comprador vencedor. 
        double aux = 0;   // Variável auxiliar ao montante máximo.
        double max = 0;   // Valor máximo fornecido pelos compradores.
        double h = horas; // Variável auxiliar para conversão entre o valor inteiro das horas para um double.
        double inc = 0;   // Total do tempo de duração entre incrementos de cada
                          // comprador convertidos para horas.
        
        for (Comprador c : compradores) {
            
            /* Calcula o montante do comprador. */
            
            aux = this.calcMontante(c);
            
            /* Se o valor fornecido pelo comprador for maior que o valor fornecido por todos os outros, então
             * este é comprador vencedor. 
             */
            
            if (aux > max) {
                max = aux;
                id = c.getEmail();
            }
        }
        
        montante = max;
        
        return id;
    }
    
    
    /**
     * @return Devolve True se o leilão terminou ou False caso contrário.
     */
    public boolean leilaoTerminado() {
        GregorianCalendar f = new GregorianCalendar();
        
        /* Calcula a diferença entre a data de "agora" e a data do início do leilão. */
        
        int diff = (int)((f.getTime().getTime() / 60000) - (inicio.getTime().getTime() / 60000));
        
        return (diff >= horas);
    }
    
    
    // Métodos complementares comuns
    
    /**
     * @return Devolve o código de hash relativo a um leilão.
     */
    public int hashCode() {
        return Arrays.hashCode(new Object[] { compradores, imovel, horas, montante, montantes});
    }
    
    
    /**
     * Verifica se um objecto é igual a uma instância da classe Leilao.
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
        
        Leilao l = (Leilao) o;
        ArrayList<Comprador> cp = (ArrayList<Comprador>) l.getCompradores();  
        
        return (horas == l.getHoras() && imovel.equals(l.getImovel()) && 
                montante == l.getMontante() && compradores.equals(l.getCompradores()) && 
                montantes.equals(l.getMontantes()));
    }
    
    
    /**
     * @return Devolve uma representação textual do leilão.
     */
    public String toString() {
        StringBuilder sb = new StringBuilder("Leilao: ");
        
        sb.append(imovel.toString());
        sb.append(horas);
        sb.append(" ");
        sb.append(montante);
        sb.append("\n");
        
        sb.append(compradores.stream()
                             .map(Comprador::toString)
                             .collect(joining("\n")));
        
        return sb.toString();
    }
    
    
    /**
     * @return Devolve uma cópia de um leilão.
     */
    public Leilao clone() {
        return new Leilao(this);
    }
    
    
    // Métodos privados
    
    /*
     * @return Devolve o total forncido por um comprador.
     */
    private double calcMontante(Comprador c) {
        double m = 0;        // Montante do comprador.
        double h = horas;    // Variável auxiliar para conversão entre o valor inteiro das horas para um double.
        double minutos = 0;  // Total do tempo de duração entre incrementos de cada 
                             // comprador convertidos para horas.
        
        /* Converte o tempo de duração entre incrementos de cada utilizador para horas. */
            
        minutos = ((double) c.getMinutos() / 60);
            
        /* Ciclo for que soma cada duração entre licitações de cada comprador enquanto esta for menor
         * que o número de horas do leilão.
         */
            
        for (double j = 0; j <= h; j += minutos) {
            if (m >= c.getLimite()) {
                    
                /* O valor nunca pode passar do valor limite imposto pelo comprador. */
                    
                m = c.getLimite();
                break;
            }
           
            /* Soma ao valor total disposto pelo comprador o incremento de uma licitação. */
                
            m += c.getIncrementos();
        }
        
        return m;
    }
}
