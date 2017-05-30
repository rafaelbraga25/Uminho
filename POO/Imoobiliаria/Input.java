/**
 * Classe que abstrai a utilização da classe Scanner, escondendo todos os
 * problemas relacionados com excepções, e que oferece métodos simples e
 * robustos para a leitura de valores de tipos simples e String.
 *
 * É uma classe de serviços, como Math e outras de Java, pelo que devem ser
 * usados os métodos de classe implementados.
 *
 * Utilizável em BlueJ, NetBeans, CodeBlocks ou Eclipse.
 * 
 * Utilização típica:  int x = Input.lerInt();
 *                               String nome = Input.lerString();
 * 
 * Nota: esta classe foi adaptada por Ana Paula Carvalho, João Pires Barreira e Rafael Braga como auxílio para 
 * este trabalho.
 * 
 * @author F. Mário Martins
 * @version 1.0 (6/2006)
 */

import static java.lang.System.out;
import static java.lang.System.in;
import java.util.Scanner;
import java.util.InputMismatchException;
import java.util.GregorianCalendar;
import java.text.SimpleDateFormat;
import java.text.ParseException;

public class Input {

     /*
      * Métodos de Classe
      */
        
     public static String lerString(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         String txt = "";
         
         while(!ok) {
             try {
                 txt = input.nextLine();
                 ok = true;
             }
             catch(InputMismatchException e) 
                 { out.println(errorMessage); 
                   out.print(newMessage);
                   input.nextLine(); 
                 }
         }
         
         input.close();
         return txt;
     } 
    
     
     public static int lerInt(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         int i = 0; 
         
         while(!ok) {
             try {
                 i = input.nextInt();
                 ok = true;
             }
             catch(InputMismatchException e) { 
                 out.println(errorMessage); 
                 out.print(newMessage);
                 input.nextLine(); 
             }
         }
         
         input.close();
         return i;
     } 
      
      
     public static double lerDouble(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         double d = 0.0; 
         
         while(!ok) {
             try {
                 d = input.nextDouble();
                 ok = true;
             }
             catch(InputMismatchException e) { 
                 out.println(errorMessage); 
                 out.print(newMessage);
                 input.nextLine(); 
             }
         }
         
         input.close();
         return d;
     }  
      
     public static float lerFloat(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         float f = 0.0f; 
         
         while(!ok) {
             try {
                 f = input.nextFloat();
                 ok = true;
             }
             catch(InputMismatchException e) { 
                 out.println(errorMessage); 
                 out.print(newMessage);
                 input.nextLine(); 
             }
         }
         
         input.close();  
         return f;
     }  
      
     
     public static boolean lerBoolean(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         boolean b = false; 
         
         while(!ok) {
             try {
                 b = input.nextBoolean();
                 ok = true;
             }
             catch(InputMismatchException e) { 
                 out.println(errorMessage); 
                 out.print(newMessage);
                 input.nextLine(); 
             }
         }
         
         input.close();
         return b;
     } 
     
     
     public static short lerShort(String errorMessage, String newMessage) {
         Scanner input = new Scanner(in);
         boolean ok = false; 
         short s = 0; 
         
         while(!ok) {
             try {
                 s = input.nextShort();
                 ok = true;
             }
             catch(InputMismatchException e) { 
                 out.println(errorMessage); 
                 out.print(newMessage);
                 input.nextLine(); 
             }
         }
         
         input.close();
         return s;
     }  
      
     
     /**
      * Este método tenta, sucessivamente, ler uma data válida, devolvendo-a no final da execução.
      * 
      * @param errorMessage Mensagem a apresentar em caso de erro.
      * @param message      Mensagem a apresentar para a obtenção de uma nova data.
      * @return date        Devolve a data lida.
      * 
      * @author Ana Paula Carvalho
      * @author João Pires Barreira
      * @author Rafael Braga
      */
     public static GregorianCalendar lerData(String errorMessage, String message) {
         Scanner input = new Scanner(in);
         boolean ok = false;
         GregorianCalendar date = null;
         SimpleDateFormat ft = new SimpleDateFormat("dd-MM-yyyy");
         String str = "";
         String[] fields;
         int d = 0;
         int m = 0;
         int y = 0;
         
         /* enquanto não for inserida uma data válida */
         while (!ok) {
             /* Lê-se a data */
             str = Input.lerString(errorMessage, message);
                
             ft.setLenient(false);
             
             /* Faz-se o parsing da string lida para o tipo SimpleDateFormat. */
             
             try {
                 ft.parse(str);
             }
             
             /* Caso a data não seja válida, é exibida a mensagem de erro e é pedido que se insira uma nova 
              * data. */
             
             catch (ParseException e) {
                 out.println(errorMessage);
                 out.print(message);
                 continue;
             }
             
             /* Separam-se os campos pelo carater "-". */
             
             fields = str.split("-");
             
             /* São lançadas as exceções relativas à leitura de um inteiro para cada um dos três campos. */
             
             try {
                 d = Integer.parseInt(fields[0].trim());
             }
             catch (NumberFormatException | NullPointerException e) {
                 out.println(errorMessage);
                 out.print(message);
                 continue;
             }
             
             try {
                 m = Integer.parseInt(fields[1].trim());
             }
             catch (NumberFormatException | NullPointerException e) {
                 out.println(errorMessage);
                 out.print(message);
                 continue;
             }
             
             try {
                 y = Integer.parseInt(fields[2].trim());
             }
             catch (NumberFormatException | NullPointerException e) {
                 out.println(errorMessage);
                 out.print(message);
                 continue;
             }
             
             /* O boolean ok é posto a true, indicando que foi lida uma data válida. */
             
             ok = true;
         }
         
         /* É criada a variável referente à data que foi lida e é devolvida no return. */
         
         date = new GregorianCalendar(y, --m, d); 
         
         input.close();
         return date;
     }
}
