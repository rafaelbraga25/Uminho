/**
 * @file scale.h
 *
 * @brief M�dulo que apresenta m�todos para se efetuar uma escala em OpenGL.
 *
 * Uma escala pode ser definida � custa de um certo valor de x, y, ou z.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#ifndef scale_h
#define scale_h

#include "glOperation.h"


class Scale : public GLOperation {
	class ScaleImpl;   // Implementa��o da classe Scale
	ScaleImpl* pimpl;  // Apontador para a implementa��o da classe Scale

public:

	/**
	 * Construtor por defeito.
	 */
	Scale(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param x Valor de uma escala em x.
	 * @param y Valor de uma escala em y.
	 * @param z Valor de uma escala em z.
	 */
	Scale(float x, float y, float z);


	/**
	 * Construtor de c�pia.
	 *
	 * @param s Objeto da classe Scale a copiar.
	 */
	Scale(const Scale& s);


	/**
	 * Devolve o valor de uma escala em x.
	 */
	float getX(void);


	/**
	 * Devolve o valor de uma escala em y.
	 */
	float getY(void);


	/**
	 * Devolve o valor de uma escala em z.
	 */
	float getZ(void);


	/**
	 * Altera o valor de uma escala em x.
	 */
	void setX(float);


	/**
	 * Altera o valor de uma escala em y.
	 */
	void setY(float);


	/**
	 * Altera o valor de uma escala em z.
	 */
	void setZ(float);


	/**
	 * Efetua uma escala em x, y ou z em OpenGL.
	 */
	void execute(void);


	/**
	 * Destrutor da classe Scale.
	 */
	~Scale(void);
};


#endif


