/**
* @file tripleFloat.cpp
*
* Definição dos métodos da classe TripleFloat.
*
* @author Carlos Pereira - A61887
* @author João Barreira  - A73831
* @author Rafael Braga   - A61799
*
* @version 06-05-2017
*/


#include <vector>
#include <sstream>
#include "tripleFloat.h"


class TripleFloat::TripleFloatImpl {
	float f1;  // Primeiro float
	float f2;  // Segundo float
	float f3;  // terceiro float

public:

	/**
	* Construtor por defeito.
	*/
	TripleFloatImpl(void)
	{
		f1 = f2 = f3 = 0.0f;
	}


	/**
	* Construtor por parâmetros.
	*
	* @param f1 Primeiro float.
	* @param f2 Segundo float.
	* @param f3 Terceiro float.
	*/
	TripleFloatImpl(float f1, float f2, float f3)
	{
		this->f1 = f1;
		this->f2 = f2;
		this->f3 = f3;
	}


	/**
	* Devolve o primeiro float.
	*/
	float getF1(void)
	{
		return f1;
	}


	/**
	* Devolve o segundo float.
	*/
	float getF2(void)
	{
		return f2;
	}


	/**
	* Devolve o terceiro float.
	*/
	float getF3(void)
	{
		return f3;
	}


	/**
	* Altera o valor do primeiro float.
	*/
	void setF1(float f1)
	{
		this->f1 = f1;
	}


	/**
	* Altera o valor do segundo float.
	*/
	void setF2(float f2)
	{
		this->f2 = f2;
	}


	/**
	* Altera o valor do terceiro float.
	*/
	void setF3(float f3)
	{
		this->f3 = f3;
	}


	/**
	* Devolve uma representação textual da classe TripleFloat.
	*/
	std::string toString(void)
	{
		std::stringstream aux;

		aux << f1 << " " << f2 << " " << f3;

		return aux.str();
	}


	/**
	* Destrutor por defeito.
	*/
	~TripleFloatImpl(void) = default;
};


/**
* Construtor por defeito.
*/
TripleFloat::TripleFloat(void)
{
	pimpl = new TripleFloatImpl();
}


/**
* Construtor por parâmetros.
*
* @param f1 Primeiro float.
* @param f2 Segundo float.
* @param f3 Terceiro float.
*/
TripleFloat::TripleFloat(float f1, float f2, float f3)
{
	pimpl = new TripleFloatImpl(f1, f2, f3);
}


/**
* Construtor de cópia da classe TripleFloat.
*
* @param t Objeto da classe TripleFloat a ser copiado.
*/
TripleFloat::TripleFloat(const TripleFloat& t)
{
	pimpl = new TripleFloatImpl(t.pimpl->getF1(), t.pimpl->getF2(), t.pimpl->getF3());
}


/**
* Devolve o primeiro float.
*/
float TripleFloat::getF1(void)
{
	return pimpl->getF1();
}


/**
* Devolve o segundo float.
*/
float TripleFloat::getF2(void)
{
	return pimpl->getF2();
}


/**
* Devolve o terceiro float.
*/
float TripleFloat::getF3(void)
{
	return pimpl->getF3();
}


/**
* Altera o valor do primeiro float.
*/
void TripleFloat::setF1(float f1)
{
	pimpl->setF1(f1);
}


/**
* Altera o valor do segundo float.
*/
void TripleFloat::setF2(float f2)
{
	pimpl->setF2(f2);
}


/**
* Altera o valor do terceiro float.
*/
void TripleFloat::setF3(float f3)
{
	pimpl->setF3(f3);
}


/**
* Devolve uma representação textual da classe TripleFloat.
*/
std::string TripleFloat::toString(void)
{
	return pimpl->toString();
}


/**
* Destrutor da classe TripleFloat.
* Liberta a memória alocada pelo apontador da parte privada da classe
* TripleFloat.
*/
TripleFloat::~TripleFloat(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}
