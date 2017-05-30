/**
 * Classe que guarda os códigos (de Produto ou de Cliente) pela ordem do seu
 * primeiro caractere. 
 * 
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * @version 2016.06.11
 */

package gerevendasestatisticas;

import java.util.Map;
import java.util.TreeMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.Arrays;
import java.io.Serializable;
import java.util.function.Function;

public class Catalogo implements Serializable {
	
    // Variáveis de instância
	
    private Map<Character, Set<String>> codigos;    //Códigos ordenados pelo
                                                    //seu primeiro caractere.
	
	
    // Construtores
    
    /**
     * Construtor vazio.
     */
    public Catalogo() {
	codigos = new TreeMap<>();
    }
	
    
    /**
     * Construtor com parâmetros.
     * 
     * @param cod Códigos ordenados pelo primeiro caractere.
     */
    public Catalogo(Map<Character, Set<String>> cod) {
	codigos = cod;
    }
	
    
    /**
     * Construtor a partir de outro Catalogo.
     * 
     * @param c Catalogo a guardar.
     */
    public Catalogo(Catalogo c) {
	codigos = c.getCodigos();
    }
	
	
    // Métodos de instância
    
    /**
     * Devolve o catálogo com os códigos já guardados. 
     */
    public Map<Character, Set<String>> getCodigos() {
	return codigos;
    }
	
    
    /**
     * Devolve o número de códigos guardados.
     * 
     * @return Número de códigos guardados. 
     */
    public int getTotalCodigos() {
        return codigos.values()
                      .stream()
                      .reduce(0, (s, v) -> s += v.size(), (s1, s2) -> s1 + s2);   
    }
    
    
    /**
     * Faz o set de um catálogo.
     * 
     * @param cod
     * @return void
     */
    public void setCodigos(Map<Character, Set<String>> cod) {
	codigos = cod;
    }
	

    /**
     * Adiciona um código ao catálogo.´
     * 
     * @param codigo Código a adicionar.
     * @throws CodigoInvalidoException Excepção para o caso do código não ser
     *                                 válido
     * @return void
     */
    public void addCodigo(String codigo) throws CodigoInvalidoException {
        
        
        if (!this.codigoValido(codigo)) {
            
            //Caso o código não seja válido, é lançada uma excepção.
            throw new CodigoInvalidoException();
        }
        else {
        
            Set<String> set = (TreeSet<String>) codigos.get(codigo.charAt(0));
            
            //Tenta adicionar o cógido na posição do primeiro caractere
            //correspondente
            try {
                set.add(codigo);
            }
            catch (NullPointerException e) { 
                
                //Caso não exista o TreeSet correspondente ao caractere, é
                //criado um novo e adiciona-se esse TreeSet ao HashMap.
                set = new TreeSet<>();
                
                set.add(codigo);
            }
            
            //O código é adicionado ao TreeSet correspondente.
            codigos.put(codigo.charAt(0), set);
        }
    }
	
    /**
     * Verifica se um código existe no catálogo.
     * 
     * @param codigo Código a procurar
     * @return true Caso o código exista no catálogo
     *         false caso contrário
     */
    public boolean containsCodigo(String codigo) {
	try {
            TreeSet<String> set = (TreeSet<String>) codigos.get(codigo.charAt(0));
			
            return set.contains(codigo);
	}
	catch (NullPointerException e) {
            return false;
	}
    }
    
    
    /**
     * Aplica um método a todos os elementos do catálogo.
     * 
     * @param f Método a aplicar a todos os elementos do catálogo.
     * @return void
     */
    public void mapCatalogo(Function<String, Boolean> f) {
        codigos.values().stream().forEach((s) -> {
            s.stream().forEach((prd) -> {
                f.apply(prd);
            });
        });
    }
    
	
    // Métodos complementares comuns
    
    
    /**
     * Compara um objeto com um elemento desta classe.
     * 
     * @param o Objeto a comparar.
     * @return true caso sejam iguais
     *         false caso contrário
     */
    public boolean equals(Object o) {
	if (this == o) {
            return true;
        }
		
        if (o == null || (this.getClass() != o.getClass())) {
            return false;
	}
		
	Catalogo c = (Catalogo) o;
		
	return codigos.equals(c.getCodigos());
    }
	
    
    /**
     * Faz o hash a partir das variáveis da classe.
     * 
     * @return Hash da classe.
     */
    public int hashCode() {
	return Arrays.hashCode(new Object[] { codigos });
    }
	
    
    /**
     * Passa para String um elemento da classe.
     * 
     * @return String do elemento
     */
    public String toString() {
	StringBuilder sb = new StringBuilder("Catalogo:\n");
		
	codigos.values().forEach(v -> v.forEach(cod -> {
            sb.append(cod);
            sb.append("\n");
        }));
		
	return sb.toString();
    }
	
    
    /**
     * Faz o clone de um elemento da classe.
     * 
     * @return Elemento clonado.
     */
    public Catalogo clone() {
	return new Catalogo(this);
    }
    
    
    // Métodos privados
    
    /*
     * Verifica se o código é válido.
     * 
     * @return true quando for válido
     *         false caso contrário
     */
    boolean codigoValido(String codigo) {
        return (codigo != null && codigo.length() > 0);
    }
}
