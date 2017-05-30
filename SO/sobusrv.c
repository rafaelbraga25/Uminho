#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdbool.h>
#include <ctype.h>
#include <dirent.h>


#define SIZE 256
#define MAX_LINE 256


char path[SIZE]; /* Caminho /home/usr/. */
int num_process; /* Número de operações a correrem no servidor. */
int fd_request;  /* Decritor do FIFO. */


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
 * Função que fecha o descritor do FIFO. Apenas é chamada quando o
 * servidor receber o sinal SIGINT.
 *
 * @return Void.
 */
void close_fd()
{
	close(fd_request);
	_exit(0);
}


/**
 * Decrementa o número de operações a correrem no servidor.
 * É chamada quando um filho termina e é enviado o sinal
 * SIGCHLD.
 *
 * @return Void.
 */
static void decreaseProcess()
{
	num_process--;
}


/**
 * Substitui todos os mesmos carateres de um array de carateres
 * por um outro caratere.
 *
 *
 * @param file_path Array de carateres.
 * @param from      Caratere a ser substituído
 * @param to        Novo caratere.
 * @return Void.
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
 * Atualiza para uma variável o caminho de um ficheiro.
 *
 * @param aux     Variável que vai guardar o caminho do ficheiro.
 * @param folder  Nomes das diretorias desde /home/usr/ e o
 *                ficheiro. 
 * @param file    Nome do ficheiro.
 * @return Void.
 */
static void updatePath(char *aux, const char *folder, const char *file)
{
	strcpy(aux, path);
	strcat(aux, folder);
	strcat(aux, file);
}


/**
 * A partir do nome de um ficheiro, remove o link para a sua
 * cópia de segurança. 
 *
 * @param file   Nome do ficheiro a remover.
 * @param pid    ID do processo que chama esta função.
 * @return Void.
 */
static void delFile(char *file, int pid)
{
	int status = 0;             /* Resultado da função unlink. */
	char link_path[SIZE] = "";  /* Caminho absoluto para o link. */

	/* Criação do caminho. */	

	updatePath(link_path, "/.Backup/metadata/", file); 

	/* Apenas tenta remover caso  exista um ficheiro com o 
	 * nome fornecido. */  

	if (access(link_path, F_OK) != -1) { 

		/* Remoção do link. */		

		status = unlink(link_path); 
		
		if (status == 0) { 

			/* Caso seja bem sucedido, é enviado para 
			 * o processo que chamou a função delFile o sinal SIGUSR1. */

			kill(pid, SIGUSR1);
		}
		else {

			/* Caso contrário, é enviado SIGUSR2. */

			kill(pid, SIGUSR2); 
		}
	}
	else {

		/* Caso não exista um ficheiro com o nome recebido, é enviado
		 * para o processo que chamou a função delFile o sinal SIGUSR2. */

		kill(pid, SIGUSR2); 
	}
}


/**
 * Cria as diretorias originais de um ficheiro.
 * 
 * @param file  Caminho absoluto do ficheiro.
 * @return Void.
 */
static void createFolders(const char *file)
{
	char *folders[SIZE];       /* Nomes de todas as diretorias que contêm o 
	                            * ficheiro.*/
	unsigned int i = 0;        /* Variável de ciclo. */
	unsigned int n = 0;        /* Número de diretorias a criar. */
	char file_path[SIZE] = ""; /* Caminho absoluto do ficheiro. */
	char curr_path[SIZE] = ""; /* Caminho atual. */
    
	strcpy(file_path, file);
        
	/* Guarda-se na matriz folders o nome de todas as diretorias. 
	 * A diretoria em folders[n] será uma sub-diretoria de
	 * folders[n - 1]. */

	folders[n] = strtok(file_path, "/");

	while (folders[n] != NULL) {
		folders[++n] = strtok(NULL, "/");
	}    
    
	/* A cada linha de folders, cria-se uma diretoria com esse nome.
	 * Vai-se guardando o caminho a ser construído à medida que se
	 * vão criando sub-diretorias.*/
    
	for (i = 0; i < n - 1; i++) {
		strcat(curr_path, "/");
		strcat(curr_path, folders[i]);
		mkdir(curr_path, S_IREAD | S_IWRITE | S_IEXEC);
	}
}


/**
 * Recupera um ficheiro.
 * 
 * @param file Nome do ficheiro a recuperar.
 * @param pid  ID do processo que chamou restoreFile.
 * @return Void.
 *
 */
static void restoreFile(char *file, int pid)
{
	int fp_link = 0;               /* Descritor do link. */
	int fp = 0;                    /* Descritor de ficheiro. */
	int status = 0;                /* Resultado da função execlp. */
	char link_path[SIZE] = "";     /* Caminho absoluto para o link. */
	char new_file_path[SIZE] = ""; /* Caminho original do ficheiro. */
	
	updatePath(link_path, "/.Backup/metadata/", file);

	/* Apenas tenta recuperar caso exista um link com o nome recebido. */

	if (access(link_path, F_OK) != -1) { 

		if (fork() == 0) {

			/* Abertura do link. */

			fp_link = open(link_path, O_RDONLY); 

			/* Redirecionamento da entrada do
			 * gunzip para o descritor do link. */		    

			dup2(fp_link, 0); 
			close(fp_link);   

			/* Substituição do caratere '>' por '/' no nome do link. */   

			replace(file, '>', '/'); 

			/* Criação das sub-diretorias que continham o ficheiro
			 * original. */			

			createFolders(file); 

			/* O nome do link corresponde ao caminho
			 * absoluto original do ficheiro. */			

			strcpy(new_file_path, file); 
			   
			/* Criação do novo ficheiro. */

			fp = open(new_file_path, O_CREAT | O_WRONLY, 0664);
			
			/* Redirecionamento da saída do gunzip para 
			 * o descritor do novo ficheiro. */		

			dup2(fp, 1);
			close(fp); 

			/* Execução do gunzip. */			

			execlp("gunzip", "gunzip", NULL); 
			
			/* Termina-se o processo atual. */

			_exit(1); 
		}
		else {

			/* O pai espera pelo resultado do filho. */

			wait(&status); 

			if (WEXITSTATUS(status) == 0) {

				/* Caso seja bem sucedido, é 
				 * enviado para o processo que 
				 * chamou a função restoreFile o 
				 * sinal SIGUSR1. */

				kill(pid, SIGUSR1); 
			}
			else {

				/* Caso contrário, é enviado SIGUSR2. */

				kill(pid, SIGUSR2); 
			}
		}
	}
	else {

		/* Caso não exista um link com o nome
		 * recebido,  é enviado para o processo 
		 * que chamou a função restoreFile o sinal
		 * SIGUSR2. */

		kill(pid, SIGUSR2); 
	}
}


/**
 * Recupera um ficheiro ou uma diretoria.
 * 
 * @param str   Nome do ficheiro ou diretoria a recuperar.
 * @param pid   ID do processo que chamou a função restore.
 * @return Void.
 *
 */
static void restore(char *str, int pid)
{
	DIR *dir_ptr = NULL;           /* Apontador para uma diretoria. */
	struct dirent *file = NULL;    /* Estrutura que representa o conteúdo
	                                * de um elemento da diretoria. */
	char path_metadata[SIZE] = ""; /* Caminho absoluto para o link na
                                     * diretoria metadata. */
	int file_exist = 0;

	strcpy(path_metadata, path);
	strcat(path_metadata, "/.Backup/metadata/");

	/* Abertura da diretoria metadata. */    

	dir_ptr = opendir(path_metadata); 
   
	if (dir_ptr != NULL) {
		while ((file = readdir(dir_ptr))) {
		
			/* Enquanto existirem links na metadata, compara o 
			 * caminho absoluto do ficheiro recebido com o nome
			 * de cada link.
			 * Caso o nome do link comece pelo caminho do ficheiro
			 * (ou seja o nome do ficheiro), então faz-se a
			 * recuperação do ficheiro ligado por esse link.
			 * Não vai chamar a função de recuperação quando se 
			 * tratarem das diretorias "."(atual) e ".."(anterior)
			 * que são sempre listadas com o readdir.*/
				
			if (strcmp(file->d_name, ".") != 0 && 
			    strcmp(file->d_name, "..") != 0) {
       		
       			if (strncmp(file->d_name, str, strlen(str)) == 0) {
					file_exist = 1;
					restoreFile(file->d_name, pid);
				}
			}
		}
		
		if (file_exist == 0) {

			/* Caso não exista um link com o nome
			 * recebido,  é enviado para o 
			 * processo que chamou a função 
			 * restore o sinal SIGUSR2. */

			kill(pid, SIGUSR2);  
		}

		/* Fecha-se o apontador para a diretoria.*/

		closedir(dir_ptr); 
	}
	else {

		/* Caso não exista a diretoria
		 * /.Backup/metadata/,  é enviado para o 
		 * processo que chamou a função restore 
		 * o sinal SIGUSR2. */

		kill(pid, SIGUSR2);  
	}
}


/**
 * Comprime um ficheiro e dá-lhe o nome do digest do ficheiro 
 * original.
 *
 * @param digest Resultado da função sha1sum no ficheiro original.
 * @param file   Nome do ficheiro a comprimir.
 * @param pid    ID do processo que chama a função zipFile.
 * @return Void.
 */
static void zipFile(const char *digest, const char *file, int pid)
{
	int fp_file = 0;             /* Descritor do ficheiro original. */
	int fp_digest = 0;           /* Descritor do ficheiro comprimido.*/
	char path_digest[SIZE] = ""; /* Caminho absoluto para o ficheiro 
	                              * que resulta da compressão. */
	int status = 0;              /* Resultado da função execlp. */
	
	/* Cálculo do caminho absoluto para o ficheiro 
	 * comprimido a ser criado. */
     
	updatePath(path_digest, "/.Backup/data/", digest);

	/* Apenas tenta comprimir caso não exista uma cópia de segurança com o 
	 * nome igual ao digest do ficheiro. */

	if (access(path_digest, F_OK) == -1) { 

		/* Apenas tenta comprimir caso exista um ficheiro com o
		 * nome recebido. */    

		if (access(file, F_OK) != -1) { 
			if (fork() == 0) {          

				/* Abertura do ficheiro a comprimir. */

				fp_file = open(file, O_RDONLY); 

				/* Redirecionamento da entrada do		       
				 * gzip para o descritor do ficheiro. */

				dup2(fp_file, 0); 
				close(fp_file);   
		       
				/* Abertura do ficheiro comprimido. */
			    
				fp_digest = open(path_digest, O_CREAT | O_WRONLY, 0664);

				/* Redirecionamento da saída do gzip 	
				 * para o descritor do novo ficheiro. */

				dup2(fp_digest, 1);
				close(fp_digest);  

				/* Execução do gzip. */		         

				execlp("gzip", "gzip", NULL); 

				/* Termina-se o processo atual. */			

				_exit(1); 
			}
			else {
	
				/* O pai espera pelo resultado do filho. */

				wait(&status); 
		
				if (WEXITSTATUS(status) != 0) {

					/* Caso não seja bem sucedido, é 
					 * enviado para o processo que 
					 * chamou a função zipFile o sinal SIGUSR2. */

					kill(pid, SIGUSR2); 
				}
			}
		}
		else {

			/* Caso não exista um ficheiro com o nome
			 * recebido, é enviado para o processo 
			 * que chamou a função zipFile o sinal SIGUSR2. */

			kill(pid, SIGUSR2); 
		}
	}
}


/**
 * Cria um link para um ficheiro na diretoria data. Guarda esse link
 * na diretoria metadata.
 *
 * @param file   Caminho absoluto do ficheiro original.
 * @param digest Digest do ficheiro original.
 * @param pid    ID do processo que chama a função createMetadata.
 * @return Void.
 */
static void createMetadata(char *file, const char *digest, int pid)
{
	char path_file[SIZE] = "";   /* Caminho absoluto do link. */
	char path_digest[SIZE] = ""; /* Caminho absoluto do ficheiro 
	                              * comprimido. */
	int status = 0;              /* Resultado da função execlp. */
	
	/* Substituição do caratere '>' por '/' no nome do caminho absoluto do
	 * ficheiro original. */

	replace(file,'/','>'); 
	
	updatePath(path_file, "/.Backup/metadata/", file);
	updatePath(path_digest, "/.Backup/data/", digest);        

	/* Apenas tenta criar o link caso exista um ficheiro
	 * de nome digest na pasta metadata. */

	if (access(path_file, F_OK) == -1) { 
		if(fork() == 0) {
		
			/* Execução do comando ln -s. */
			
			execlp("ln", "ln", "-s", path_digest, path_file, NULL);

			/* Termina-se o processo atual. */			          
                    
			_exit(1); 
		}
		else {

			/* O pai espera pelo resultado do filho. */

			wait(&status); 

			if (WEXITSTATUS(status) == 0) {

				/* Caso seja bem sucedido, é 
				 * enviado para o processo que 
				 * chamou a função createMetadata 
				 * o sinal SIGUSR1. */
			
				kill(pid, SIGUSR1);  
			}
			else {

				/* Caso contrário, é enviado SIGUSR2. */

				kill(pid, SIGUSR2);  
			}			
		}
	}
	else {

		/* Caso não exista um ficheiro de nome
		 * digest na diretoria metadata, é
		 *  enviado para o processo que chamou a
		 * função createMetadata o sinal
		 * SIGUSR2. */

		kill(pid, SIGUSR2); 
	}
}


/**
 * Faz a cópia de segurança de um ficheiro. Invoca as funções
 * necessárias para calcular o digest, comprimir ficheiros e criar
 * links.
 * 
 * @param str   Caminho absoluto do ficheiro a comrpimir.
 * @param pid   ID do processo que chama esta função.
 * @return Void.
 *
 */
static void backup(char *str, int pid)
{
	int pfd[2];                   /* Descritor de um pipe anónimo. */
	char buffer[MAX_LINE] = "";   /* Buffer que guarda o conteúdo lido 
	                               * do pipe anónimo. */
	char digest[MAX_LINE] = "";   /* Resultado da função sha1sum no
	                               * ficheiro pretendido. */
	char aux_file[MAX_LINE] = ""; /* Nome do ficheiro resultante do 
	                               * sha1sum. */
	char file[MAX_LINE] = "";     /* Nome do ficheiro. */
	int status_pipe = 0;          /* Resultado da criação do pipe anónimo. */
	int status_sha1sum = 0;
	unsigned int i = 1;           /* Variável de ciclo. */
	
	
	replace(str, '>', '/');
	
	status_pipe = pipe(pfd);

	/* Caso o pipe anónimo tenha sido criado. */	

	if (status_pipe == 0) { 

		/* Apenas comprime um ficheiro caso ele exista na 
		 * diretoria esperada.*/

		if (access(str, F_OK) != -1) { 

			if (fork() == 0) {

				/* Redirecionamento da saída do sha1sum para a entrada do 
				 * pipe. */

				dup2(pfd[1], 1); 
				close(pfd[1]);   

				/* Execução do sha1sum. */		

				execlp("sha1sum", "sha1sum", str, NULL);

				/* Termina-se o processo atual. */			    

				_exit(1); 
			}
			else {

				/* Fecha-se a entrada do pipe. O pai 
				 * apenas vai ler do pipe e não vai escrever. */

				close(pfd[1]); 

				/* O pai espera pelo resultado do 
				 * filho.*/			    

				wait(&status_sha1sum); 
		
				/* Caso o sha1sum tenha executado corretamente. */
		
				if (WEXITSTATUS(status_sha1sum) == 0) {
			                                     
					/* Lê-se o conteúdo do pipe anónimo. */
			        
					read(pfd[0], buffer, MAX_LINE);

					/* Fecha-se a saída do pipe. */		

					close(pfd[0]); 

					/* Copia-se o digest para a variável 
					 * correspondente.*/
					
					strcpy(digest, strtok(buffer, " ")); 
			        			        
					/* Copia-se o nome do ficheiro do sha1sum para
					 * uma variável auxiliar.*/
			        
					strcpy(aux_file, strtok(NULL, "\r\n"));
		       
					for (; i < strlen(aux_file); i++) {
			        
						/* Copia-se para a variável correspondente ao
						 * nome do ficheiro a que se aplica o 
						 * sha1sum. Retiram-se os carateres 
						 * desnecessários.*/
			             
						file[i - 1] = aux_file[i];
					}

					/* Chama-se a função que comprime ficheiros.*/

					zipFile(digest, file, pid); 
			
					/*Cria-se o link para o ficheiro comprimido.*/
			                                           
					createMetadata(file, digest, pid);
				}  
				else {

					/* Caso o sha1sum não tenha sido bem sucedido, é 
					 * enviado para o processo que chamou a função 
					 * backup o sinal SIGUSR2. */

					kill(pid, SIGUSR2); 
				}
			}
		}
		else {

			/* Caso o ficheiro não exista, é enviado para o processo que 
			 * chamou a função backup o sinal SIGUSR2.*/

			kill(pid, SIGUSR2); 
		}
	}
	else {

		/* Caso o pipe anónimo não tenha sido criado, é enviado para o 	
		 * processo que chamou a função backup o sinal SIGUSR2.*/

		kill(pid, SIGUSR2); 
	}
}


/**
 * Verifica, recursivamente, se um ficheiro na pasta data tem um 
 * link para si na diretoria metadata e suas sub-diretorias.
 *
 * @param folder  Nome da diretoria onde procurar.
 * @param file    Nome do ficheiro a comparar.
 * @return bool true  o ficheiro tem pelo menos um link em metadata
 *              false caso contrário
 */
static bool existFile(char *folder, char *file)
{
	DIR *dptr = NULL;            /* Apontador para uma diretoria. */
	struct dirent *link = NULL;  /* Estrutura que representa o conteúdo
	                              * de um elemento da diretoria. */
	char aux_folder[SIZE] = "";  /* Caminho da diretoria onde 
	                              * procurar.*/
	char link_buffer[SIZE] = ""; /* Nome de um elemento da diretoria.*/
	bool b = false;              /* Valor a retornar. */

	/* Abertura da diretoria recebida. */

	dptr = opendir(folder); 

	if (dptr != NULL) { 

		/* Caso exista uma diretoria folder. */

		while ((link = readdir(dptr))) {
		
			/* Enquanto existirem elementos na diretoria atual,
			 * verifica se se trata de um ficheiro ou de uma
			 * sub-diretoria.
			 * Caso seja uma diretoria, chama de a função existFile
			 * para que procure nessa sub-diretoria.
			 * Caso seja um ficheiro, compara o nome desse ficheiro
			 * com o nome recebido.
			 * Não vai chamar nenhuma função quando se se tratarem
			 * das diretorias "." (atual) e ".." (anterior) que são 
			 * sempre listadas com o readdir. */

			if (strcmp(link->d_name, ".") != 0 && 
			    strcmp(link->d_name, "..") != 0) {
				
				/* Acrescenta ao nome recebido, o nome lido da
				 * diretoria. */
       		     
				strcpy(aux_folder, folder);
				strcat(aux_folder, link->d_name);

				if (link->d_type == DT_DIR) {
				 
					/* Caso o elemento se trate de uma diretoria,
					 * chama a função atual para essa sub-diretoria. */
				
					strcat(aux_folder, "/");

					b = existFile(aux_folder, file);

					if (b == true) {

						/* Sai do ciclo quando existir pelo 
						 * menos um link para o ficheiro.*/

						break; 
					}
				}
				else {
					readlink(aux_folder, link_buffer, SIZE);

					/* Caso o elemento se trate de um ficheiro,
					 * compara esse nome com o nome do ficheiro 
					 * recebido.*/	

					if (strcmp(link_buffer, file) == 0) {
						b = true;

						/* Sai do ciclo quando existir pelo 
						 * menos um link para o ficheiro.*/

						break; 
					}					
				}
			}
		}

		/* Fecha-se o apontador para a diretoria. */

		closedir(dptr); 
	}

	return b;
}


/**
 * Elimina os ficheiros comprimidos que não tenham links para eles.
 *
 * @pid    ID do processo que chama esta função.
 * @return Void.
 */
static void gc(int pid) 
{
	char data_path[SIZE] = "";     /* Caminho absoluto para a diretoria 
	                                * data.*/
	char metadata_path[SIZE] = ""; /* Caminho absoluto para a 
	                                * diretoria metadata.*/
	char file_path[SIZE] = "";     /* Caminho absoluto para um ficheiro 
	                                * da diretoria data.*/
	DIR *data = NULL;              /* Apontador para a diretoria data. */
	struct dirent *file = NULL;    /* Estrutura que representa o conteúdo
	                                * de um elemento da diretoria data.*/

	/* Cria-se o caminho para data.*/

	strcpy(data_path, path);
	strcat(data_path, "/.Backup/data/"); 

	/* Cria-se o caminho para metadata.*/

	strcpy(metadata_path, path);
	strcat(metadata_path, "/.Backup/metadata/"); 

	/* Abertura da diretoria data. */

	data = opendir(data_path); 

	if (data != NULL) { 

		/* Caso a diretoria data exista. */

		while ((file = readdir(data))) { 
			/* Enquanto existirem elementos na diretoria data,
			 * chama-se a função que verifica se existe pelo menos
			 * um link para esse elemento na diretoria metadata.
			 * Não vai chamar nenhuma função quando se se tratarem
			 * das diretorias "." (atual) e ".." (anterior) que são 
			 * sempre listadas com o readdir.*/
		
			if (strcmp(file->d_name, ".") != 0 && 
                   strcmp(file->d_name, "..") != 0) {
                
				/* Acrescenta ao nome recebido, o nome lido da
				 * diretoria. */
                   
				strcpy(file_path, data_path);
				strcat(file_path, file->d_name);

				if (existFile(metadata_path, file_path) == false) {

					/* Caso não exista nenhum link, elimina o 
					 * elemento atual. */
					
					unlink(file_path);
				}
			}	
		}

		/* Fecha-se o apontador para a diretoria.*/

		closedir(data); 
	}

	/* Quando acabar de eliminar os ficheiros, é 
	 * enviado para o processo que chamou
	 * a função gc o sinal SIGUSR1.*/	

	kill(pid, SIGUSR1); 
}


/**
 * Função principal do servidor.
 * Lê os dados de um FIFO e separa-os. A partir do comando recebido,
 * chama a função adequeada. Informa o cliente através de sinais se
 * executou corretamente (ou não) o comando.
 *
 * @return 0 significa que terminou. Comunica os resultados ao cliente
 *         através de sinais.
 */
int main(void)
{
	char request[SIZE] = "";     /* Conteúdo lido do FIFO. */
	char command[SIZE] = "";     /* Comando a ser executado. É enviado 
	                              * pelo FIFO. */
	char file[SIZE] = "";        /* Nome do ficheiro a executar o 
	                              * comando. É enviado pelo FIFO. */
	char aux_request[SIZE] = ""; /* Caminho absoluto até ao FIFO. Por 
	                              * defeito é guardado em
	                              * /home/usr/.Backup/*/
	int pid = 0;                 /* ID do processo que vai executar o
	                              * comando. */

	/* Contador do número de processos a serem 
	 * executados ao mesmo tempo. Por defeito, 
	 * quando for igual a 5, os processos a não serem
	 * executados esperam. */

	num_process = 0; 

	/* Copia o caminho /home/usr/ para uma variável global path.*/       
      
	calcDest(); 

	/* Inicializa-se a variável global que é o descritor do FIFO. */    

	fd_request = 0; 

	/* Quando for para fechar o servidor,
	 * recebe-se o sinal SIGINT e fecha-se
	 * o descritor do FIFO. */    

	signal(SIGINT, close_fd); 
    
    
	/* Cria o caminho absoluto para o FIFO. */
	
	strcpy(aux_request, path);
	strcat(aux_request, "/.Backup/");
	strcat(aux_request, "p_request");

	/* Criação do FIFO. O servidor apenas lê do FIFO.*/

	mkfifo(aux_request, 0777); 

	/* Define-se que quando se receber SIGCHLD, o contador 
	 * de número de processos a serem executados é decrementado.*/    

	signal(SIGCHLD, decreaseProcess); 

	while (1) {

		/* Caso o número de processos a serem 
		 * executados seja menos que 5. */

		if (num_process < 5) { 

			/* Incrementa o número de processos. */

			num_process++; 

			if (fork() == 0) {
				fd_request = open(aux_request, O_RDONLY);

				/* Lê-se o conteúdo do FIFO. */
 
				read(fd_request, request, SIZE); 


				/* Guardam-se nas variáveis correspondentes, o ID
				 * do processo que escreveu no FIFO como também o 
				 * comando a executar. */

				pid = atoi(strtok(request, " "));
				strcpy(command, strtok(NULL, " "));

				/* Caso o comando seja backup, restore ou delete,
				 * guarda-se na variável corresponde o ficheiro a 
				 * aplicar a função. Depois envia-se para a função
				 * adequada com os parâmetros adequados. */
                
				if (strcmp(command, "backup") == 0) {  
					strcpy(file, strtok(NULL, "\n"));
					backup(file, pid);
				}
				else if (strcmp(command, "restore") == 0) {
				    strcpy(file, strtok(NULL, "\n"));
					restore(file, pid);
				}	
				else if (strcmp(command, "delete") == 0) {
					strcpy(file, strtok(NULL, "\n"));
					delFile(file, pid);
				}
				
				
				/* Caso o comando seja gc, não existem ficheiros a 
				 * aplicar a função. Chama-se a função adequada com 
				 * o parâmetro adequado. */
				
				else if (strcmp(command, "gc") == 0) {
				    gc(pid);
				}

				/* Termina-se o processo atual. */	

				_exit(0); 	
			}
		}
	}

	return 0;
}


