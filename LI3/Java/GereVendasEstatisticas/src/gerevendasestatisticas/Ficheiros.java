/**
 * @author Carlos Pereira - A61887
 * @author Diogo Silva    - A76407
 * @author Rafael Braga   - A61799
 * 
 * @version 09.06.2016
 */

package gerevendasestatisticas;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.function.Function;
import java.util.ArrayList;

public class Ficheiros {
    
    private Ficheiros() {} /* Garante que não existirão instâncias de Ficheiros. */
    
    /*
     * Função de leitura de linhas de um dado ficheiro.
     * É aplicada uma função a cada linha lida.
     */
    public static void readLines(String ficheiro, Function<String, Void> f) {
        
        BufferedReader inStream;
        String linha;

        try {
           inStream = new BufferedReader(new FileReader(ficheiro));
              
            while((linha = inStream.readLine()) != null) { 
                f.apply(linha.split("\r\n")[0]);
            }

            inStream.close();
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
    }
    
    
    /**
     * @param ficheiro Ficheiro a ler.
     * @return Devolve um ArrayList com todas as linhas lidas. 
     */
    public static ArrayList<String> 
            readLinesWithScanner(String ficheiro) { 
        ArrayList<String> linhas = new ArrayList<>(); 
        Scanner scanFile = null; 
        
        try { 
            scanFile = new Scanner(new FileReader(ficheiro)); 
            scanFile.useDelimiter("\n\r"); 
            while(scanFile.hasNext()) {
                linhas.add(scanFile.nextLine());
            }
        } 
        catch(IOException ioExc) { 
            System.out.println(ioExc.getMessage()); 
            return null; 
        } 
        finally { 
            if(scanFile != null) {
                scanFile.close(); 
            }
        }
        
        return linhas; 
    } 
            
            
    /**
     * @param ficheiro Ficheiro a ler.
     * @return Devolve um ArrayList com todas as linhas lidas. 
     */
    public static ArrayList<String> readLinesWithBuff(String fich) { 
        ArrayList<String> linhas = new ArrayList<>();
        BufferedReader inStream = null;  
        String linha = null; 

        try { 
            inStream = new BufferedReader(new FileReader(fich)); 
            
            while( (linha = inStream.readLine()) != null) { 
                linhas.add(linha); 
            }
        } 
        catch(IOException e) { 
            System.out.println(e.getMessage()); 
            return null; 
        }
        
        return linhas;   
    } 
}
