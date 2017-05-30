/**
 * @file translation.h
 *
 * @brief Módulo que apresenta métodos para se efetuar uma translação em OpenGL.
 *
 * Uma translação pode ser definida à custa dos valores de x, y e z.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#ifndef translation_h
#define translation_h

#include "glOperation.h"


class Translation : public GLOperation {
	class TranslationImpl;   // Implementação da classe Translation
	TranslationImpl* pimpl;  // Apontador para a implementação da classe 
	                         // Translation

public:

	/**
	 * Construtor por defeito.
	 */
	Translation(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Valor de uma translação em x.
	 * @param y Valor de uma translação em y.
	 * @param z Valor de uma translação em z.
	 */
	Translation(float x, float y, float z);


	/**
	 * Construtor de cópia.
	 *
	 * @param t Objeto da classe Translation a copiar.
	 */
	Translation(const Translation& t);


	/**
	 * Devolve o valor de uma translação em x.
	 */
	float getX(void);


	/**
	 * Devolve o valor de uma translação em y.
	 */
	float getY(void);


	/**
	 * Devolve o valor de uma translação em z.
	 */
	float getZ(void);


	/**
	 * Altera o valor de uma translação em x.
	 */
	void setX(float);


	/**
	 * Altera o valor de uma translação em y.
	 */
	void setY(float);


	/**
	 * Altera o valor de uma translação em z.
	 */
	void setZ(float);


	/**
	 * Executa uma translação em x, y ou z em OpenGL.
	 */
	void execute(void);


	/**
	 * Destrutor da classe Translation.
	 */
	~Translation(void);
};


#endif

