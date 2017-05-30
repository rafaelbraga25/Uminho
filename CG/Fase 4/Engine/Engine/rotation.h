/**
 * @file rotation.h
 *
 * @brief Módulo que apresenta métodos para se efetuar uma rotação em OpenGL.
 *
 * Uma rotação pode ser definida à custa de um ângulo e à escolha de um dos
 * três eixos: x, y ou z.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 29-04-2017
 */


#ifndef rotation_h
#define rotation_h


#include "glOperation.h"


class Rotation : public GLOperation {
	class RotationImpl;   // Implementação da classe Rotation
	RotationImpl* pimpl;  // Apontador para a implementação da classe Rotation


public:

	/**
	 * Construtor por defeito.
	 */
	Rotation(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param angle     Ângulo de uma rotação.
	 * @param totalTime Tempo total de uma rotação.
	 * @param x         Valor de uma rotação em x.
	 * @param y         Valor de uma rotação em y.
	 * @param z         Valor de uma rotação em z.
	 */
	Rotation(float angle, float totalTime, float x, float y, float z);


	/**
	 * Construtor de cópia.
	 *
	 * @param r Objeto da classe Rotation a copiar.
	 */
	Rotation(const Rotation& r);


	/**
	 * Devolve o valor do ângulo de uma rotação.
	 */
	float getAngle(void);


	/**
	 * Devolve o valor de uma rotação em x.
 	 */ 
	float getX(void);


	/**
	 * Devolve o valor de uma rotação em y.
	 */
	float getY(void);


	/**
	 * Devolve o valor de uma rotação em z.
 	 */
	float getZ(void);


	/**
	 * Devolve o valor do tempo total de uma rotação.
	 */
	float getTotalTime(void);


	/**
	 * Altera o valor do ângulo de uma rotação.
	 */
	void setAngle(float);


	/**
	 * Altera o valor de uma rotação em x.
	 */
	void setX(float);


	/**
	 * Altera o valor de uma rotação em y.
	 */
	void setY(float);


	/**
	 * Altera o valor de uma rotação em z.
	 */
	void setZ(float);


	/**
	 * Altera o valor do tempo total de uma rotação.
	 */
	void setTotalTime(float);


	/**
	 * Efetua uma rotação com um certo ângulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(void);


	/**
	 * Efetua uma rotação com um certo ângulo em torno dos eixos x, y ou z em
	 * OpenGL.
	 */
	void execute(FrustumCulling* f);


	/**
	 * Destrutor da classe Rotation.
	 */
	~Rotation(void);
};


#endif
