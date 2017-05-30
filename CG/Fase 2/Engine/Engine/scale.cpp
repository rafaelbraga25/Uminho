/**
 * @file scale.cpp
 *
 * Definição de todos os métodos para se representar uma escala em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#include <cstddef>
#include "scale.h"


class Scale::ScaleImpl {
	float x;  // Valor de uma escala em x
	float y;  // Valor de uma escala em y
	float z;  // Valor de uma escala em z


public:

	/**
	 * Construtor por defeito.
	 */
	ScaleImpl(void)
	{
		x = y = z = 0.0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Valor de uma escala em x.
	 * @param y Valor de uma escala em y.
	 * @param z Valor de uma escala em z.
	 */
	ScaleImpl(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	/**
	 * Devolve o valor de uma escala em x.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma escala em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma escala em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor de uma escala em x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma escala em x.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma escala em x.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Destrutor da classe ScaleImpl (por defeito em c++).
	 */
	~ScaleImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementação da 
 * classe Scale.
 */
Scale::Scale(void)
{
	pimpl = new ScaleImpl();
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe Scale através dos parâmetros recebidos.
 *
 * @param x Valor de uma escala em x.
 * @param y Valor de uma escala em y.
 * @param z Valor de uma escala em z.
 */
Scale::Scale(float x, float y, float z)
{
	pimpl = new ScaleImpl(x, y, z);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
 * Scale, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param s Objeto da classe Scale a copiar.
 */
Scale::Scale(const Scale& s)
{
	pimpl = new ScaleImpl(s.pimpl->getX(),
		                  s.pimpl->getY(), s.pimpl->getZ());
}


/**
 * Devolve o valor de uma escala em x.
 */
float Scale::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma escala em y.
 */
float Scale::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma escala em z.
 */
float Scale::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor de uma escala em x.
 */
void Scale::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma escala em y.
 */
void Scale::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma escala em z.
 */
void Scale::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Efetua uma escala em x, y ou z em OpenGL.
 */
void Scale::execute(void)
{
	glScalef(pimpl->getX(), pimpl->getY(), pimpl->getZ());
}


/**
 * Destrutor da classe Scale. Liberta a memória ocupada pelo apontador para a 
 * implementação da classe Scale.
 */
Scale::~Scale(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}