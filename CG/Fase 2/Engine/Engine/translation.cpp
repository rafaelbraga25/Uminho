/**
 * @file translation.cpp
 *
 * Definição de todos os métodos para se representar uma translação em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#include <cstddef>
#include "translation.h"


class Translation::TranslationImpl {
	float x;  // Valor de uma translação em x
	float y;  // Valor de uma translação em y
	float z;  // Valor de uma translação em z


public:

	/**
	 * Construtor por defeito.
	 */
	TranslationImpl(void)
	{
		x = y = z = 0.0;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Valor de uma translação em x.
	 * @param y Valor de uma translação em y.
	 * @param z Valor de uma translação em z.
	 */
	TranslationImpl(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}


	/**
	 * Devolve o valor de uma translação em x.
	 */
	float getX(void)
	{
		return x;
	}


	/**
	 * Devolve o valor de uma translação em y.
	 */
	float getY(void)
	{
		return y;
	}


	/**
	 * Devolve o valor de uma translação em z.
	 */
	float getZ(void)
	{
		return z;
	}


	/**
	 * Altera o valor de uma translação em x.
	 */
	void setX(float x)
	{
		this->x = x;
	}


	/**
	 * Altera o valor de uma translação em x.
	 */
	void setY(float y)
	{
		this->y = y;
	}


	/**
	 * Altera o valor de uma translação em x.
	 */
	void setZ(float z)
	{
		this->z = z;
	}


	/**
	 * Destrutor da classe TranslationImpl (por defeito em c++).
	 */
	~TranslationImpl(void) = default;
};


/**
 * Construtor por defeito. Inicializa o apontador para a implementação da
 * classe Translation.
 */
Translation::Translation(void)
{
	pimpl = new TranslationImpl();
}


/**
 * Construtor por parâmetros. Inicializa o apontador para a implementação da
 * classe Translation através dos parâmetros recebidos.
 *
 * @param x Valor de uma translação em x.
 * @param y Valor de uma translação em y.
 * @param z Valor de uma translação em z.
 */
Translation::Translation(float x, float y, float z)
{
	pimpl = new TranslationImpl(x, y, z);
}


/**
 * Construtor de cópia. Inicializa o apontador para a implementação da classe
 * Translation, recorrendo a uma deep copy de um objeto desta classe.
 *
 * @param t Objeto da classe Translation a copiar.
 */
Translation::Translation(const Translation& t)
{
	pimpl = new TranslationImpl(t.pimpl->getX(),
		                        t.pimpl->getY(), t.pimpl->getZ());
}


/**
 * Devolve o valor de uma translação em x.
 */
float Translation::getX(void)
{
	return pimpl->getX();
}


/**
 * Devolve o valor de uma translação em y.
 */
float Translation::getY(void)
{
	return pimpl->getY();
}


/**
 * Devolve o valor de uma translação em z.
 */
float Translation::getZ(void)
{
	return pimpl->getZ();
}


/**
 * Altera o valor de uma translação em x.
 */
void Translation::setX(float x)
{
	pimpl->setX(x);
}


/**
 * Altera o valor de uma translação em y.
 */
void Translation::setY(float y)
{
	pimpl->setY(y);
}


/**
 * Altera o valor de uma translação em z.
 */
void Translation::setZ(float z)
{
	pimpl->setZ(z);
}


/**
 * Executa uma translação em x, y ou z em OpenGL.
 */
void Translation::execute(void)
{
	glTranslatef(pimpl->getX(), pimpl->getY(), pimpl->getZ());
}


/**
 * Destrutor da classe Translation. Liberta a memória ocupada pelo apontador 
 * para a implementação da classe Translation.
 */
Translation::~Translation(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}