/**
 * @file light.cpp
 *
 * Definição de todos os métodos para se representar uma luz em
 * OpenGL.
 * 
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include <cstddef>
#include "light.h"


#define MAX_LIGHTS 8


int Light::currentLight = -1;


class Light::LightImpl {

	TripleFloat pos;  // Posição da luz
	TripleFloat diff; // Cor difusa da luz
	TripleFloat spec; // Cor especular da luz
	TripleFloat ambt; // Cor ambiente da luz
	float constant;   // Atenuação constante
	float linear;     // Atenuação linear
	float quadratic;  // Atenuação quadratica


public:

	/**
	 * Construtor por defeito.
	 */
	LightImpl(void) 
	{
		pos.setF1(0.0f);
		pos.setF2(0.0f);
		pos.setF3(1.0f);

		diff.setF1(1.0f);
		diff.setF2(1.0f);
		diff.setF3(1.0f);

		spec.setF1(1.0f);
		spec.setF2(1.0f);
		spec.setF3(1.0f);

		ambt.setF1(0.0f);
		ambt.setF2(0.0f);
		ambt.setF3(0.0f);

		constant = 1.0f;
		linear = 0.0f;
		quadratic = 0.0f;
	}


	/**
	 * Construtor por parâmetros.
	 *
	 * @param pos       Posição da luz.
	 * @param diff      Cor difusa da luz.
	 * @param spec      Cor especular da luz.
	 * @param ambt      Cor ambiente da luz.
	 * @param constant  Atenuação constante.
	 * @param linear    Atenuação linear.
	 * @param quadratic Atenuação quadratica.
	 */
	LightImpl(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
		      float constant, float linear, float quadratic)
	{
		this->pos.setF1(pos.getF1());
		this->pos.setF2(pos.getF2());
		this->pos.setF3(pos.getF3());

		this->diff.setF1(diff.getF1());
		this->diff.setF2(diff.getF2());
		this->diff.setF3(diff.getF3());

		this->spec.setF1(spec.getF1());
		this->spec.setF2(spec.getF2());
		this->spec.setF3(spec.getF3());

		this->ambt.setF1(ambt.getF1());
		this->ambt.setF2(ambt.getF2());
		this->ambt.setF3(ambt.getF3());

		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}


	/**
	 * Devolve a posição da luz.
	 */
	TripleFloat getPos(void)
	{
		return pos;
	}


	/**
	 * Devolve a cor difusa da luz.
	 */
	TripleFloat getDiff(void)
	{
		return diff;
	}


	/**
	 * Devolve a cor espcular da luz.
	 */
	TripleFloat getSpec(void)
	{
		return spec;
	}


	/**
	 * Devolve a cor ambiente da luz.
	 */
	TripleFloat getAmbt(void)
	{
		return ambt;
	}


	/**
	 * Devolve o valor da atenuação constante.
	 */
	float getConstant(void)
	{
		return constant;
	}


	/**
	 * Devolve o valor da atenuação linear.
	 */
	float getLinear(void)
	{
		return linear;
	}


	/**
 	 * Devolve o valor da atenuação quadratica.
	 */
	float getQuadratic(void)
	{
		return quadratic;
	}


	/**
	 * Altera a posição da luz.
	 */
	void setPos(TripleFloat pos)
	{
		this->pos.setF1(pos.getF1());
		this->pos.setF2(pos.getF2());
		this->pos.setF3(pos.getF3());
	}


	/**
	 * Altera a cor difusa da luz.
	 */
	void setDiff(TripleFloat diff) 
	{
		this->diff.setF1(diff.getF1());
		this->diff.setF2(diff.getF2());
		this->diff.setF3(diff.getF3());
	}


	/**
	 * Altera a cor especular da luz.
	 */
	void setSpec(TripleFloat spec)
	{
		this->spec.setF1(spec.getF1());
		this->spec.setF2(spec.getF2());
		this->spec.setF3(spec.getF3());
	}


	/**
	 * Altera a cor ambiente da luz.
	 */
	void setAmbt(TripleFloat ambt)
	{
		this->ambt.setF1(ambt.getF1());
		this->ambt.setF2(ambt.getF2());
		this->ambt.setF3(ambt.getF3());
	}


	/**
	 * Altera o valor da atenuação constante.
	 */
	void setConstant(float constant)
	{
		this->constant = constant;
	}


	/**
	 * Altera o valor da atenuação linear.
	 */
	void setLinear(float linear)
	{
		this->linear = linear;
	}


	/**
	 * Altera o valor da atenuação quadratica.
	 */
	void setQuadratic(float quadratic)
	{
		this->quadratic = quadratic;
	}


	/**
	 * Destrutor da classe Light.
	 */
	~LightImpl(void) = default;

};




/**
 * Construtor por defeito.
 */
Light::Light(void)
{
	pimpl = new LightImpl();
}


/**
 * Construtor por parâmetros.
 *
 * @param pos       Posição da luz no eixo dos xx.
 * @param diff      Cor difusa da luz.
 * @param spec      Cor especular da luz.
 * @param ambt      Cor ambiente da luz.
 * @param constant  Atenuação constante.
 * @param linear    Atenuação linear.
 * @param quadratic Atenuação quadratica.
 */
Light::Light(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
	         float constant, float linear, float quadratic)
{
	pimpl = new LightImpl(pos, diff, spec, ambt, constant, linear, quadratic);
}


/**
 * Construtor de cópia.
 *
 * @param l Objeto da classe Light a copiar.
 */
Light::Light(const Light& l)
{
	pimpl = new LightImpl(l.pimpl->getPos(), l.pimpl->getDiff(),
		                  l.pimpl->getSpec(), l.pimpl->getSpec(),
		                  l.pimpl->getConstant(), l.pimpl->getLinear(),
		                  l.pimpl->getQuadratic());
}


/**
 * Devolve a posição da luz.
 */
TripleFloat Light::getPos(void)
{
	return pimpl->getPos();
}


/**
 * Devolve a cor difusa da luz.
 */
TripleFloat Light::getDiff(void)
{
	return pimpl->getDiff();
}


/**
* Devolve a cor especular da luz.
*/
TripleFloat Light::getSpec(void)
{
	return pimpl->getSpec();
}


/**
 * Devolve a cor ambiente da luz.
 */
TripleFloat Light::getAmbt(void)
{
	return pimpl->getAmbt();
}


/**
 * Devolve o valor da atenuação constante.
 */
float Light::getConstant(void)
{
	return pimpl->getConstant();
}


/**
 * Devolve o valor da atenuação linear.
 */
float Light::getLinear(void)
{
	return pimpl->getLinear();
}


/**
 * Devolve o valor da atenuação quadratica.
 */
float Light::getQuadratic(void)
{
	return pimpl->getQuadratic();
}


/**
 * Altera a posição da luz.
 */
void Light::setPos(TripleFloat pos)
{
	pimpl->setPos(pos);
}


/**
 * Altera a cor difusa da luz.
 */
void Light::setDiff(TripleFloat diff)
{
	pimpl->setDiff(diff);
}


/**
 * Altera a cor especular da luz.
 */
void Light::setSpec(TripleFloat spec)
{
	pimpl->setSpec(spec);
}


/**
 * Altera a cor ambiente da luz.
 */
void Light::setAmbt(TripleFloat ambt)
{
	pimpl->setAmbt(ambt);
}


/**
 * Altera o valor da atenuação constante.
 */
void Light::setConstant(float constant)
{
	pimpl->setConstant(constant);
}


/**
 * Altera o valor da atenuação linear.
 */
void Light::setLinear(float linear)
{
	pimpl->setLinear(linear);
}


/**
 * Altera o valor da atenuação quadratica.
 */
void Light::setQuadratic(float quadratic)
{
	pimpl->setQuadratic(quadratic);
}


/**
 * Destrutor da classe Light.
 */
Light::~Light(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}


/**
 * Devolve o tipo de luz a ser executado.
 */
GLenum Light::getLight(void)
{
	GLenum ret = 0;

	if (currentLight == 0) {
		ret = GL_LIGHT0;
	}
	else if (currentLight == 1) {
		ret = GL_LIGHT1;
	}
	else if (currentLight == 2) {
		ret = GL_LIGHT2;
	}
	else if (currentLight == 3) {
		ret = GL_LIGHT3;
	}
	else if (currentLight == 4) {
		ret = GL_LIGHT4;
	}
	else if (currentLight == 5) {
		ret = GL_LIGHT5;
	}
	else if (currentLight == 6) {
		ret = GL_LIGHT6;
	}
	else if (currentLight == 7) {
		ret = GL_LIGHT7;
	}

	return ret;
}


/**
 * Incrementa o valor da luz ou volta a zero caso se tenha atingido o máximo.
 */
void Light::updateCurrentLight(void)
{
	currentLight++;

	if (currentLight == MAX_LIGHTS) {
		currentLight = 0;
	}
}