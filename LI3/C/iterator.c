/**
 *  @file iterator.c
 *  @brief Iterador sobre qualquer tipo de elementos tendo por base um array.
 *
 *  Definição de todas as funções pertencentes à interface deste módulo, bem
 *  como todos os métodos auxiliares.
 *
 *  @author Carlos Pereira - A61887
 *  @author Diogo Silva    - A76407
 *  @author Rafael Braga   - A61799
 *
 *  @bug ?
 *  @version 2.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "iterator.h"


#define INIT_CAPACITY 10000    /* Capacidade inicial do iterador. */


struct iterator {
	void **vec;                  /* Array de elementos do iterador. */
	unsigned int index;          /* Posição atual do iterador. */
	unsigned int capacity;       /* Capacidade do vetor. */
	unsigned int last;           /* Última posição do vetor. */
	unsigned int value_size;     /* Tamanho de um elemento do vetor. */

	void (*print)(const void*);  /* Função para realizar a impressão de um
	                              * elemento. */
	void (*delete)(void*);       /* Função para apagar um elemento do iterador.
	                              * Esta função só é necessária para elementos
	                              * mais complexos. */
};



/*****************************************************************************
 * BEGIN PRIVATE                                                             *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS                                                        *
 *****************************************************************************/

/**
 *  Inicializa um elemento do iterador. A função fornece tratamento de erros
 *  para casos inesperados.
 *
 *  @param value      Valor a ser criado.
 *  @param value_size Tamanho do elemento a ser guardado no iterador.
 *  @return Retorna o novo elemento ou o programa é terminado caso haja algum
 *          erro de memória.
 */
static void* createValue(const void* value, const unsigned int value_size)
{
	void *new_value = malloc(value_size); /* Novo elemento no iterador. */

	if (new_value == NULL) {

		/* Se o malloc falhou tenta-se realocar espaço para o novo elemento. */

		new_value = realloc(new_value, value_size);

		/* O programa termina se o realloc falhar, havendo algum erro inesperado
		 * a nível de memória. */

		assert(new_value != NULL);
	}

	memcpy(new_value, value, value_size);

	return new_value;
}


/**
 *  Função por defeito para apagar um elemento do iterador.
 *
 *  @param value Valor a ser apagado.
 *  @return Void.
 */
static void defaultDestroy(void *value)
{
	if (value != NULL) {
		free(value);
		value = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS                                                          *
 *****************************************************************************/

/*****************************************************************************
 * END PRIVATE                                                               *
 *****************************************************************************/



/*****************************************************************************
 * BEGIN PUBLIC                                                              *
 *****************************************************************************/

/*****************************************************************************
 * BEGIN CONSTRUCTORS AND DESTRUCTORS                                        *
 *****************************************************************************/

/**
 *  @brief Cria um iterador com uma capacidade inicial.
 *
 *  Aloca espaço para um novo iterador com uma capacidade igual a
 *  INIT_CAPACITY. Sempre que se aloca espaço para alguma estrutura a função
 *  faz um tratamento de erros para casos em que essa alocação não foi bem
 *  sucedida.
 *  O iterador guarda o tamanho dos elementos que irá armazenar, bem como a
 *  função responsável para realizar a impressão de um elemento. Todas as
 *  posições do iterador são inicializadas a NULL.
 *
 *  @param value_size Tamanho dos elementos a guardar no iterador.
 *  @param print      Função para efetuar a impressão de um elemento.
 *  @return Retorna o novo iterador ou o programa é abortado caso haja algum
 *          erro a nível de memória.
 */
Iterator createIterator(const unsigned int value_size,
                        void (*print)(const void *value))
{
	Iterator it = malloc(sizeof(struct iterator)); /* É alocado espaço para um
	                                                * novo iterador. */

	if (it == NULL) {

		/* Se o malloc falhou tenta-se fazer um realloc. */

		it = realloc(it, sizeof(struct iterator));

		/* Se it for NULL após o realloc há problemas inesperados a nível de
		 * de memória e o program é abortado. */

		assert(it != NULL);
	}

	it->capacity = INIT_CAPACITY;

	/* Aloca-se espaço para o vetor do iterador, o tamanho do vetor é igual
	 * a INIT_CAPACITY. */

	it->vec = malloc(it->capacity * (sizeof(void*)));

	if (it->vec == NULL) {

		/* Se o malloc falhou tenta-se realocar memória para o vetor. */

		it->vec = realloc(it->vec, it->capacity * value_size);

		/* Se it->vec == NULL mesmo depois do realloc o programa é
		 * terminado. */

		assert(it->vec != NULL);
	}

	/* O índice do último elemento consultado e do último elemento é 0. */

	it->index = it->last = 0;
	it->value_size = value_size;
	it->print = print;
	it->delete = defaultDestroy;

	return it;
}


/**
 *  Liberta a memória de todo o iterador. Só faz o free de cada posição do
 *  iterador caso este tenha sido previamente inicializado e caso essa posição
 *  exista.
 *
 *  @param it Apontador para o iterador.
 *  @return Void.
 */
void destroyIterator(Iterator it)
{
	unsigned int i = 0; /* Varíavel para efetuar o controlo do ciclo for sobre
	                     * sobre todos os elementos do iterador. */

	if (it != NULL) {
		if (it->vec != NULL) {

			/* O iterador existe logo todos os seus elementos são apagados. */

			for (; i < it->last; i++) {
				if (it->vec[i] != NULL) {
					it->delete(it->vec[i]);
				}
			}

			/* Apaga-se todo o vetor do iterador. */

			free(it->vec);
			it->vec = NULL;
		}

		/* Finalmente liberta-se a memória ocupada pela estrutura do iterador. */

		free(it);
		it = NULL;
	}
}

/*****************************************************************************
 * END CONSTRUCTORS AND DESTRUCTORS                                          *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN GETS AND SETS                                                       *
 *****************************************************************************/

/**
 *  Devolve o número de elementos do iterador. Como it->last guarda a última
 *  posição disponível para a inserção de um novo elemento, basta retornar o
 *  valor deste não sendo necessário fazer uma travessia por todo o iterador
 *  para realizar a contagem dos seus elementos.
 *
 *  @param it Apontador para o iterador.
 *  @return Número de elementos do iterador ou 0 caso este não exista.
 */
unsigned int getSizeIterator(const Iterator it)
{
	unsigned int l = (it != NULL) ? it->last : 0;

	return l;
}


/**
 *  Devolve o índice relativo à última consulta efetuada num iterador.
 *
 *  @param it Apontador para o iterador.
 *  @return Índice da última consulta ou 0 caso o iterador não exista.
 */
unsigned int getIndexIterator(const Iterator it)
{
	unsigned int index = (it != NULL) ? it->index : 0;

	return index;
}


/**
 *  Avança uma posição no iterador.
 *
 *  @param it Apontador para o iterador.
 *  @return Void. O resultado é guardado em it.
 */
void nextIterator(Iterator it)
{
	if (it != NULL) {
		it->index++;
	}
}


/**
 *  Recua uma posição no iterador.
 *
 *  @param it Apontador para o iterador.
 *  @return Void. O resultado é guardado em it.
 */
void prevIterator(Iterator it)
{
	if (it != NULL) {
		it->index--;
	}
}


/**
 *  Navega para uma dada posição do iterador caso a posição recebida seja
 *  válida.
 *
 *  @param it    Apontador para o iterador.
 *  @param index Posição para onde se pretende navegar no iterador.
 *  @return Void. O resultado é guardado em it.
 */
void goToIterator(Iterator it, const unsigned int index)
{
	if (it != NULL && index < it->last) {
		it->index = index;
	}
}


/**
 *  Altera a função para libertar a memória de um elemento do iterador. Só
 *  é necessária para casos em que os elementos a guardar sejam estruturas de
 *  dados mais complexas.
 *
 *  @param it     Apontador para o iterador.
 *  @param delete Função para apagar um elemento do iterador.
 *  @return Void.
 */
void setDeleteIterator(Iterator it, void (*delete)(void *value))
{
	if (it != NULL) {
		it->delete = delete;
	}
}

/*****************************************************************************
 * END GETS AND SETS                                                         *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN ADD AND SEARCH                                                       *
 *****************************************************************************/

/**
 *  @brief Adiciona um novo elemento ao iterador caso este exista.
 *
 *  Adiciona um elemento ao iterador caso este tenha sido previamente
 *  inicializado.
 *  A inserção é direta pois value é adicionado na posição it->last que
 *  corresponde à primeira posição válida para inserir um novo elemento no
 *  iterador. Depois de uma inserção com sucesso o valor de it->last será,
 *  naturalmente, incrementado.
 *  Caso se tenha atingido a capacidade máxima do iterador então é efetuado
 *  um realocamento deste dobrando a sua capaciadade. Em caso de algum problema
 *  na efetuação deste processo o programa é abortado.
 *
 *  @param it    Apontador para o iterador.
 *  @param value Novo elemento a acrescentar ao iterador.
 *  @return Devolve o iterador.
 */
Iterator addIterator(Iterator it, const void *value)
{
	if (it != NULL) {
		if (it->last < it->capacity) {

			/* Não se excedeu a capaciadade do iterador logo é seguro a acrescentar
			 * mais um elemento a este. */

			it->vec[it->last++] = createValue(value, it->value_size);
		}
		else {
			/* Atingiu-se a capacidade máxima do iterador logo esta é duplicada e
			 * realoca-se memória para a nova capacidade do iterador. */

			it->capacity *= 2;
			it->vec = realloc(it->vec, it->capacity * sizeof(void*));

			/* Se a realocação de memória do iterador falhar então o programa é
			 * terminado. */

			assert(it->vec != NULL);

			it->vec[it->last++] = createValue(value, it->value_size);
		}
	}

	return it;
}


/**
 *  Adiciona um iterador a outro iterador. O iterador dest é criado conforme
 *  o iterador source caso este não exista.
 *
 *  @param dest   Apontador para o iterador onde se pretende adicionar
 *                outro iterador.
 *  @param source Iterador a acrescentar.
 *  @return Void. O resultador da adição é guardado em it.
 */
Iterator addCollectionIterator(Iterator dest, Iterator source)
{
	unsigned int i = 0;

	/* So adiciona elementos se source conter elementos. */

	if (source != NULL) {
		if (dest == NULL) {

			/* O iterador onde se pretende acrescentar elementos é nulo, logo
			 * este é criado com o mesmo tipo do iterador source. */

			dest = createIterator(source->value_size, source->print);
		}

		for (; i < source->last; i++) {
			addIterator(dest, source->vec[i]);
		}
	}

	return dest;
}

/**
 *  Verifica se o próximo índice do iterador corresponde a uma posição que
 *  contém um elemento não vazio.
 *
 *  @param it Apontador para o iterador.
 *  @return true caso o próximo índice contenha um elemento não vazio ou false
 *          caso contrário.
 */
bool hasNextIterator(Iterator it)
{
	bool b = false;

	if (it != NULL) {

		/* Para efetuar este teste basta testar se o índice é menor que
		 * it->last - 1, já que este corresponde à primeira posição livre do
		 * iterador para armazenar mais um elemento. */

		b = (it->index < it->last - 1) ? true : false;
	}

	return b;
}


/**
 *  Verifica se o índice anterior do iterador corresponde a uma posição que
 *  contém um elemento não vazio.
 *
 *  @param it Apontador para o iterador.
 *  @return true caso o índice anterior contenha um elemento não vazio ou false
 *          caso contrário.
 */
bool hasPrevIterator(Iterator it)
{
	bool b = false;

	if (it != NULL) {

		/* Para efetuar este teste basta testar se o índice é maior que 0,
		 * já que este corresponde à primeira posição do iterador. */

		b = (it->index > 0) ? true : false;
	}

	return b;
}

/*****************************************************************************
 * END ADD AND SEARCH                                                        *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN MAPS, FILTERS AND FOLDS                                             *
 *****************************************************************************/


/**
 *  Cria uma qualquer estrutura de dados caso o iterador exista.
 *
 *  @param it  Apontador para o iterador.
 *  @param acc Acumulador da nova estrutura de dados.
 *  @param f   Função para atualizar acc conforme cada elemento do iterador.
 *  @return Void. O resultado é guardado em acc.
 */
void foldIterator(const Iterator it, void *acc,
                  void (*f)(const void *value, void *acc))
{
	unsigned int i = 0;

	if (it != NULL) {
		for (; i < it->last; i++) {
			f(it->vec[i], acc);
		}
	}
}

/*****************************************************************************
 * END MAPS, FILTERS AND FOLDS                                               *
 *****************************************************************************/


/*****************************************************************************
 * BEGIN PRINT FUNCTIONS                                                     *
 *****************************************************************************/

/**
 *  Realiza a impressão da posição atual do iterador.
 *
 *  @param it Apontador para o iterador.
 *  @return Void.
 */
void printCurrentIterator(Iterator it)
{
	if (it != NULL) {
		it->print(it->vec[it->index]);
	}
}


/**
 *  Realiza a impressão de todos os elementos do iterador.
 *
 *  @param it Apontador para o iterador.
 *  @return Void.
 */
void printAllIterator(Iterator it)
{
	unsigned int i = 0;

	if (it != NULL) {
		for (; i < it->last; i++) {
			it->print(it->vec[i]);
		}
	}
}


/**
 *  Realiza a impressão de uma certa posição do iterador caso esta seja
 *  válida.
 *
 *  @param it    Apontador para o iterador.
 *  @param index Posição do iterador que se pretende realizar a impressão.
 *  @return Void.
 */
void printAtIterator(Iterator it, unsigned int index)
{

	/* Testa-se se o iterador existe e a index corresponde a uma posição válida
	 * do iterador. */

	if (it != NULL && index < it->last) {
		it->print(it->vec[index]);
	}
}

/*****************************************************************************
 * END PRINT FUNCTIONS                                                       *
 *****************************************************************************/

/*****************************************************************************
 * END PUBLIC                                                                *
 *****************************************************************************/
