/**
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * 
 * @version 09.06.2016
 */

package gerevendas;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.util.function.Function;
import java.io.File;

public class Ficheiros {
    
    private Ficheiros() {} /* Garante que não existirão instâncias de Ficheiros. */
    
    /*
     * Função de leitura de linhas de um dado ficheiro.
     * É aplicada uma função a cada linha lida.
     */
    public static void readLines(String ficheiro, Function<String, Boolean> f) {
        
        BufferedReader inStream;
        String linha;

        try {
           inStream = new BufferedReader(new FileReader(ficheiro));
              
            while((linha = inStream.readLine()) != null) 
            { 
                f.apply(linha.split("\r\n")[0]);
            }

            inStream.close();
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
    }
    
    
    public static boolean existeFicheiro(String ficheiro) {
        File f = new File(ficheiro);
        
        if(f.exists() && !f.isDirectory()) { 
            return true;
        }
        
        System.out.println("O ficheiro " + ficheiro + " não existe.");
        return false;
    }
    
    
    /*
     * Guarda todo o estado do Hipermercado em disco.
     */
    public static void guardarHipermercado(String ficheiro, Hipermercado h) {
        
        try { 
            gravaObj(ficheiro, h);
        }
        catch(IOException e) {
            System.out.println("Não foi possível guardar os dados.");
        }
    }
    
    /*
     * Carrega o último estado do Hipermercado para memória.
     */
    public static Hipermercado carregarHipermercado(String ficheiro) {
        Hipermercado h;
        
        try {
             h = leObj(ficheiro);
        }
        catch (IOException e) {
             h = new Hipermercado();
            System.out.println("Não foi possível ler os dados: Erro de leitura.");
        } 
        catch (ClassNotFoundException e) {
             h = new Hipermercado();
            System.out.println("Não foi possível ler os dados!: Ficheiro com formato desconhecido.");
        }
        catch (ClassCastException e) {
             h = new Hipermercado();
            System.out.println("Não foi possível ler os dados!: Erro de formato.");        
        }
        
        return h;
    }
    
    /*
     * Grava objecto passado como argumento em disco.
     */
    private static void gravaObj(String ficheiro, Hipermercado h) throws IOException 
    { 
        ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(ficheiro)); 
        oos.writeObject(h);
        oos.flush(); 
        oos.close(); 
    } 
    
    /*
     * Devolve o objecto em disco.
     */
    private static Hipermercado leObj(String ficheiro) throws IOException, ClassNotFoundException 
    {
        ObjectInputStream ois = new ObjectInputStream(new FileInputStream(ficheiro));
        Hipermercado h = (Hipermercado) ois.readObject();
        ois.close();
        return h;
    }
}
