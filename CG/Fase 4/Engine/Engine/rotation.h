/**
 * @file rotation.h
 *
 * @brief M�dulo que apresenta m�todos para se efetuar uma rota��o em OpenGL.
 *
 * Uma rota��o pode ser definida � custa de um �ngulo e � escolha de um dos
 * tr�s eixos: x, y ou z.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 29-04-2017
 */


#ifndef rotation_h
#define rotation_h


#include "glOperation.h"


class Rotation : public GLOperation {
	class RotationImpl;   // Implementa��o da classe Rotation
	RotationImpl* pimpl;  // Apontador para a implementa��o da classe Rotation


public:

	/**
	 * Construtor por defeito.
	 */
	Rotation(void);


	/**
	 * Construtor por par�metros.
	 *
	 * @param angle     �ngulo de uma rota��o.
	 * @param totalTime Tempo total de uma rota��o.
	 * @param x         Valor de uma rota��o em x.
	 * @param y         Valor de uma rota��o em y.
	 * @param z         Valor de uma rota��o em z.
	 */
	Rotation(float angle, float totalTime, float x, float y, float z);


	/**
	 * Construtor de c�pia.
	 *
	 * @param r Objeto da classe Rotation a copiar.
	 */
	Rotation(const Rotation& r);


	/**
	 * Devolve o valor do �ngulo de uma rota��o.
	 */
	float getAngle(void);


	/**
	 * Devolve o valor de uma rota��o em x.
 	 */ 
	float getX(void);


	/**
	 * Devolve o valor de uma rota��o em y.
	 */
	float getY(void);


	/**
	 * Devolve o valor de uma rota��o em z.
 	 */
	float getZ(void);


	/**
	 * Devolve o valor do tempo total de uma rota��o.
	 */
	float getTotalTime(void);


	/**
	 * Altera o valor do �ngulo de uma rota��o.
	 */
	void setAngle(float);


	/**
	 * Altera o valor de uma rota��o em x.
	 */
	void setX(float);


	/**
	 * Altera o valor de uma rota��o em y.
	 */
	void setY(float);


	/**
	 * Altera o valor de uma rota��o em z.
	 */
	void setZ(float);


	/**
	 * Altera o valor do tempo total de uma rota��o.
	 */
	void setTotalTime(float);


	/**
	 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(void);


	/**
	 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(FrustumCulling* f);


	/**
	 * Destrutor da classe Rotation.
	 */
	~Rotation(void);
};


#endif
