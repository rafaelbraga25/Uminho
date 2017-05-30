#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <dirent.h>


#define SIZE 256

char path[SIZE];      /* Caminho /home/usr/. */
char file_name[SIZE]; /* Nome do ficheiro a apresentar nas mensagens
                       * de resposta a sinais. */
int num_waits;        /* Contador do número de forks criados na função 
                       * backupFile. */


/**
 * Copia para uma variável o conteúdo da variável de ambiente HOME.
 *
 * @return Void.
 */
static void calcDest(void)
{
	strcpy(path, getenv("HOME"));
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro ter sido copiado com sucesso.
 *
 * @return Void.
 */
static void backupOK()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	strcat(buffer, ": copiado\n");
	write(1, buffer, SIZE);
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro não ter sido copiado com sucesso.
 *
 * @return Void.
 */
static void backupError()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	strcat(buffer, ": não copiado\n");
	write(1, buffer, SIZE);
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro ter sido recuperado com sucesso.
 *
 * @return Void.
 */
static void restoreOK()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	strcat(buffer, ": recuperado\n");
	write(1, buffer, SIZE);
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro não ter sido recuperado com sucesso.
 *
 * @return Void.
 */
static void restoreError()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	write(1, buffer, SIZE);
	write(1, ": não recuperado.\n", strlen(": não recuperado.\n"));
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro ter sido apagado com sucesso.
 *
 * @return Void.
 */
static void deleteOK()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	strcat(buffer, ": apagado\n");
	write(1, buffer, SIZE);
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente ao ficheiro não ter sido apagado com sucesso.
 *
 * @return Void.
 */
static void deleteError()
{
	char buffer[SIZE] = "";

	strcpy(buffer, file_name);
	strcat(buffer, ": não apagado\n");
	write(1, buffer, SIZE);
}


/**
 * Mensagem a apresentar no ecrã quando o servidor envia o sinal
 * correspondente à execução correta do comando gc.
 *
 * @return Void.
 */
static void gcOK()
{
	char buffer[SIZE] = "";

	strcat(buffer, "sucesso\n");
	write(1, buffer, SIZE);
}


/**
 *  Substitui todos os mesmos carateres de um array de carateres
 *  por um outro caratere.
 *
 *
 *  @param file_path Array de carateres.
 *  @param from      Caratere a ser substituído
 *  @param to        Novo caratere.
 *  @return Void.
 */
static void replace(char *file_path, const char from, const char to)
{
	unsigned int i = 0;
	unsigned int size = (unsigned int) strlen(file_path);

	for(; i < size; i++) {
		if(file_path[i] == from) {
			file_path[i] = to;
		}
	}
}


/**
 *  A partir do nome de um ficheiro constrói o seu caminho absoluto.
 *  No fim substitui todos os carateres '/' no caminho absoluto
 *  por '>'.
 *
 *  @param file      Nome do ficheiro.
 *  @param file_path Variável que vai guardar o caminho absoluto do 
 *                   ficheiro com o caratere '/' substituído por '>'.
 *  @return Void.
 *
 */
static void buildPath(char *file, char *file_path)
{

     /* Começa por verificar se o nome recebido já tem o caminho
      * absoluto. */

	if (strncmp(file, path, strlen(path)) == 0) { 
		strcpy(file_path, file);
	}
	else {
	
  	     /* Caso o nome do ficheiro não tenha o caminho absoluto,
	      * acrescenta-lho através da variável de ambiente PWD. */
	
		strcpy(file_path, getenv("PWD"));
		strcat(file_path, "/");
		strcat(file_path, file);
	}


     /* Substitui os carateres '/' do caminho absoluto por '>'. */

	replace(file_path, '/', '>');
}


/**
 * Faz a cópia de segurança de um ficheiro (ou diretoria). 
 * 
 * @param file  Nome do ficheiro (ou diretoria).
 * @param fd    Descritor para um FIFO.
 * @return Void.
 */
static void backupFile(char *file, int fd)
{
	char command[SIZE] = "";
	char file_path[SIZE] = "";
    
	/* Construção do caminho absoluto do ficheiro. */	

	buildPath(file, file_path);	

	/* Contador do número de fork feitos no decorrer deste programa. */

	num_waits++; 

	if (fork() == 0) { 

		/* Cópia do nome do ficheiro para a variável utilizada nas
           * mensagens dos sinais. */ 
  
		strcpy(file_name, file);  

		/* Guarda-se o ID deste processo. */            
	
		sprintf(command, "%d ", getpid());  
        
		/* Guarda-se o comando recebido pelo terminal (neste caso será
	      * backup). */

		strcat(command, "backup ");	

		/* Guarda-se o caminho absoluto do ficheiro. */

		strcat(command, file_path); 
			
		/* Por fim guarda-se o delimitador no pipe. */

		strcat(command, "\n");    

		/* Escrita destas informações no FIFO. */

		write(fd, command, SIZE); 


		/* Define-se que SIGUSR1 corresponde a uma cópia com sucesso
           * e o SIGUSR2 corresponde a uma cópia sem sucesso. */

		signal(SIGUSR1, backupOK);
		signal(SIGUSR2, backupError);

		/* O processo espera por um sinal enviado pelo servidor. 
		 * Quando receber esse sinal, é apresentada no ecrã a mensagem 
		 * correspondente à cópia do ficheiro recebido. */

		pause(); 

		/* Termina-se o processo atual. */

		_exit(0); 
	}	
}
 

/**
 * Trata de fazer, recursivamente, a cópia de segurança de ficheiros 
 * e de diretorias. Termina quando uma diretoria já não tenha
 * mais elementos.
 *
 *  @param str    Nome do ficheiro a fazer uma cópia de segurança.
 *  @param fd     Descritor para um FIFO.
 *  @return Void.
 */
static void backup(char *str, int fd)
{
	DIR *dir_ptr = NULL;         /* Apontador para uma diretoria. */
	struct dirent *file = NULL;  /* Estrutura que representa o conteúdo
	                              * de um elemento da diretoria. */
	char folder_path[SIZE] = ""; /* Caminho absoluto para a diretoria.*/


	/* Abertura da diretoria recebida. */

	dir_ptr = opendir(str); 

	if (dir_ptr != NULL) { 

		/* Caso exista uma diretoria str. */        

		if(str[strlen(str) - 1] != '/') {

			/* Caso o último caratere do nome não seja um '/', 
			 * acrescenta-lho. */			

			strcat(str, "/"); 
		}
        
		while ((file = readdir(dir_ptr))) { 
		    
			/* Enquanto existirem elementos na diretoria atual,
			 * verifica-se se trata de um ficheiro ou de uma
			 * sub-diretoria e aplica-lhes uma função.
			 * Não vai chamar nenhuma função quando se tratarem
			 * das diretorias "." (atual) e ".." (anterior) que são 
			 * sempre listadas com o readdir. */
		    
			if (strcmp(file->d_name, ".") != 0 && 
				strcmp(file->d_name, "..") != 0) {
  
       		
				/* Acrescenta ao nome recebido, o nome lido da
				 * diretoria. */
  
				strcpy(folder_path, str);
				strcat(folder_path, file->d_name);

				if (file->d_type == DT_DIR) {	
                    
					/* Caso o elemento se trate de uma diretoria,
					 * chama a função atual para essa sub-diretoria. */

					backup(folder_path, fd);
				}
				else {

					/* Caso contrário, trata-se de um ficheiro e 
					 * chama a função que faz a cópia de segurança
					 * de ficheiros. */			
					
					backupFile(folder_path, fd);
				}
			}
		}

		/* Fecha-se o apontador para a diretoria. */		

		closedir(dir_ptr); 
	}
	else {

		/* Caso falhe é porque se trata de um ficheiro. */

		backupFile(str, fd); 
	}
}
 

/**
 * Verifica se o comando recebido pelo utilizador é válido.
 *
 * @param argc  Número de campos recebidos pelo utilizador.
 * @param cmmnd Comando recebido.
 * @param true caso o comando seja válido
 *        false caso contrário
 */
static bool verifyCommand(const int argc, const char *cmmnd)
{
	bool b = false; /* Variável a devolver. */

	if (argc >= 2) {
		if (argc == 2) {
		
			/* Caso o número de campos seja dois e o comando seja gc,
			 * a função vai devolver true. */

			b = (strcmp(cmmnd, "gc") == 0) ? true : false;
		}	
		else {

			/* Caso o número de campos seja superior a dois, é porque
			 * tem argumentos a seguir ao comando. A função vai
			 * devolver true caso o comando seja restore, backup ou 
			 * delete. */
		
			if (strcmp(cmmnd, "restore") == 0 || 
			    strcmp(cmmnd, "backup") == 0 || 
			    strcmp(cmmnd, "delete") == 0) {
				
				b = true;
			} 
			else {
				b = false;
			}
		}
	}    

	return b;
}


/**
 * Função principal do cliente.
 * A partir do comando recebido e dos nomes de ficheiros (caso sejam
 * precisos), envia para a função adequeada os dados necessários
 * de maneira que o servidor possa executar o comando.
 *
 * @param  argc Número de argumentos recebidos.
 * @param  argv Argumentos.
 * @return 0 caso o comando recebido seja válido
 *        -1 caso contrário
 */
int main(int argc, char *argv[])
{
	char command[SIZE] = "";   /* Linha com todos os dados a enviar 
	                            * para o FIFO. */
	int i = 0;                 /* Variável de ciclo. */
	int fd = 0;                /* Descritor do FIFO. */
	char pipe_path[SIZE] = ""; /* Caminho absoluto para o FIFO. */
	char file_path[SIZE] = ""; /* Caminho absoluto para o ficheiro. */


	/* Verificação da validade do comando recebido . */

	if (verifyCommand(argc, argv[1]) == false) {		
		
		write(1, "Parâmetros inválidos!\n", 
		      strlen("Parâmetros inválidos!\n"));
		return -1;
	}

	/* Inicialização do contador de forks criados quando o comando é 
	 * backup. */

	num_waits = 0; 

	/* Copia o caminho /home/usr/ para uma variável global path. */

	calcDest(); 
	
	/* Criação do caminho absoluto para o FIFO. */
	
	strcpy(pipe_path, path);
	strcat(pipe_path, "/.Backup/p_request");

	/* Abertura do FIFO. O cliente só escreve no FIFO. */

	fd = open(pipe_path, O_WRONLY); 


	if (argc == 2) { 

		/* O comando é gc. Não precisa de nomes de ficheiros. */
    
		if (fork() == 0) {

			/* Guarda-se o ID deste processo. */			

			sprintf(command, "%d ", getpid());

			/* Guarda-se o comando. */
 
			strcat(command, argv[1]);   

			/* Delimitador no FIFO.*/

			strcat(command, " \n");     

			/* Escrita destas informações no FIFO.*/

			write(fd, command, SIZE); 

			/* Define-se que SIGUSR1 corresponde a uma execução
			 * correta do comando.*/

			signal(SIGUSR1, gcOK); 

			/* O processo espera por um sinal enviado pelo 
			 * servidor. Quando receber esse sinal, é
			 * apresentado no ecrã a mensagem correspondente
			 * à eliminação de cópias de segurança 
			 * desnecessárias.*/	

			pause(); 
			          
			/* Termina-se o processo atual. */				

			_exit(0); 
		}
		else {

			/* O pai espera que o filho termine. */

			wait(NULL); 
		}
	}
    else { 

		/* O comando é backup, restore ou delete. */

		if (strcmp(argv[1], "backup") == 0) { 
			for (i = 2; i < argc; i++) {

				/* Caso seja backup, chama a função apropriada para cada
				 * ficheiro recebido pelo utilizador. */

				backup(argv[i], fd); 
			}
	        
	        
			/* Como não se sabe quantos ficheiros vão ser comprimidos
			 * (na possibilidade de serem diretorias), utiliza-se o 
			 * num_waits que tem o número de filhos criados na função
			 * que trata da cópia de ficheiros. */
	        
			for (i = 0; i < num_waits; i++) {

				/* O pai espera que os filhos terminem. */

				wait(NULL); 
			}
		}
		else {
			for (i = 2; i < argc; i++) {
				if (fork() == 0) {
		
					strcpy(file_name, argv[i]);

					/* Guarda-se o ID deste processo. */

					sprintf(command, "%d ", getpid()); 

					/* Guarda-se o comando. */			

					strcat(command, argv[1]); 
					strcat(command, " ");			

					/* Calcula-se o caminho absoluto 
					 * para o ficheiro (ou diretoria) recebido. */

					buildPath(argv[i], file_path);

					/* Copia-se o caminho. */

					strcat(command, file_path); 

					/* Delimitador no FIFO. */			

					strcat(command, "\n");    

					/* Escrita no FIFO.*/

					write(fd, command, SIZE); 
    			        
					if (strcmp(argv[1], "restore") == 0) {
						/* Define-se que SIGUSR1 corresponde a uma
						 * recuperação com sucesso e o SIGUSR2 
						 * corresponde a uma recuperação sem sucesso. */
				    
						signal(SIGUSR1, restoreOK);
						signal(SIGUSR2, restoreError);
					}
					else if (strcmp(argv[1], "delete") == 0) {

						/* Define-se que SIGUSR1 corresponde a uma
						 * eliminação com sucesso e o SIGUSR2 
						 * corresponde a uma eliminação sem sucesso.*/

						signal(SIGUSR1, deleteOK);
						signal(SIGUSR2, deleteError);
					}
		
					/* O processo espera por um sinal enviado
					 * pelo servidor. Quando receber esse
					 * sinal, é apresentado no ecrã a
					 * mensagem correspondente ao sucesso
					 * da execução do comando no ficheiro
					 * recebido. */	
		       	
					pause(); 

					/* Termina-se o processo atual. */

					_exit(0); 
				}
			}

			for (i = 2; i < argc; i++) {
		
				/* O pai espera que os filhos terminem. */

				wait(NULL); 
			}
		}
	}

	return 0;
}

