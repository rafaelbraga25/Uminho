/**
 * @file rotation.cpp
 *
 * Defini��o de todos os m�todos para se representar uma rota��o em OpenGL.
 * 
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#include <cstddef>
#include "rotation.h"


class Rotation::RotationImpl {
	float angle;  // �ngulo de uma rota��o
	float x;      // Valor de uma rota��o em x
	float y;      // Valor de uma rota��o em y
	float z;      // Valor de uma rota��o em z


public:


	/**
	 * Construtor por defeito.
	 */
	RotationImpl(void)
	{
		angle = x = y = z = 0.0;
	}


	/**
	 * Construtor por par�metros.
	 *
	 * @param angle �ngulo de uma rota��o
	 * @param x     Valor de uma rota��o em x.
	 * @param y     Valor de uma rota��o em y.
	 * @param z     Valor de uma rota��o em z.
	 */
	RotationImpl(float angle, float x, float y, float z)
	{
		this->angle = angle;
		this->x = x;
		this->y = y;
		this->z = z;
	}


	/**
	 * Devolve o valor do �ngulo de uma rota��o.
	 */
	float getAngle(void)
	{
		return angle;
	}


	/**
	 * Devolve o valor de uma rota��o em x.
 	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma rota��o em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma rota��o em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor do �ngulo de uma rota��o.
	 */
	void setAngle(float angle)
	{
		this->angle = angle;
	}


	/**
	 * Altera o valor de uma rota��o em x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma rota��o em y.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma rota��o em z.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Destrutor da classe RotationImpl (por defeito em c++).
	 */
	~RotationImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementa��o da
 * classe Rotation.
 */
Rotation::Rotation(void)
{
	pimpl = new RotationImpl();
}


/**
 * Construtor por par�metros. Inicializa o apontador para a implementa��o da
 * classe Rotation atrav�s dos par�metros recebidos.
 *
 * @param angle �ngulo de uma rota��o.
 * @param x     Valor de uma rota��o em x.
 * @param y     Valor de uma rota��o em y.
 * @param z     Valor de uma rota��o em z.
 */
Rotation::Rotation(float angle, float x, float y, float z)
{
	pimpl = new RotationImpl(angle, x, y, z);
}


/**
 * Construtor de c�pia. Inicializa o apontador para a implementa��o da classe
 * Rotation, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param r Objeto da classe Rotation a copiar.
 */
Rotation::Rotation(const Rotation& r)
{
	pimpl = new RotationImpl(r.pimpl->getAngle(), r.pimpl->getX(), 
		                     r.pimpl->getY(), r.pimpl->getZ());
}


/**
 * Devolve o valor do �ngulo de uma rota��o.
 */
float Rotation::getAngle(void)
{
	return pimpl->getAngle();
}


/**
 * Devolve o valor de uma rota��o em x.
 */
float Rotation::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma rota��o em y.
 */
float Rotation::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma rota��o em z.
 */
float Rotation::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor do �ngulo de uma rota��o.
 */
void Rotation::setAngle(float angle)
{
	pimpl->setAngle(angle);
}


/**
 * Altera o valor de uma rota��o em x.
 */
void Rotation::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma rota��o em y.
 */
void Rotation::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma rota��o em z.
 */
void Rotation::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Efetua uma rota��o com um certo �ngulo em torno dos eixos x, y ou z em
 * OpenGL.
 */
void Rotation::execute(void)
{
	glRotatef(pimpl->getAngle(), pimpl->getX(), pimpl->getY(), pimpl->getZ());
}


/**
 * Destrutor da classe Rotation. Liberta a mem�ria ocupada pelo apontador para 
 * a implementa��o da classe Rotation.
 */
Rotation::~Rotation(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}