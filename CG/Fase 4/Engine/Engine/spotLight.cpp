/**
 * @file spotLight.cpp
 *
 * Definição de todos os métodos para se representar uma luz do tipo spot
 * OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include "spotLight.h"


class SpotLight::SpotLightImpl {

	TripleFloat spotDir;  // Direção do spot
	float cutoff;         // Ângulo do spot
	float exponent;       // Expoente do spot

public:

	/**
	 * Construtor por defeito.
	 */
	SpotLightImpl(void) 
	{
		spotDir.setF1(0.0f);
		spotDir.setF2(0.0f);
		spotDir.setF2(-1.0f);

		cutoff = 180.0f;
		exponent = 0.0f;
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
	 * @param quadratic Atenuação quadrática.
	 * @param spotDir   Direção do spot.
	 * @param cutoff    Ângulo do spot.
	 * @param exponent  Expoente do spot.
	 */
	SpotLightImpl(TripleFloat spotDir, float cutoff, float exponent)
	{
		this->spotDir.setF1(spotDir.getF1());
		this->spotDir.setF2(spotDir.getF2());
		this->spotDir.setF3(spotDir.getF3());

		this->cutoff = cutoff;
		this->exponent = exponent;
	}


	/**
	 * Devolve a direção do spot.
	 */
	TripleFloat getSpotDir(void)
	{
		return spotDir;
	}


	/**
	 * Devolve o ângulo do spot.
	 */
	float getCutoff(void)
	{
		return cutoff;
	}


	/**
	 * Devolve o expoente do spot.
	 */
	float getExponent(void)
	{
		return exponent;
	}


	/**
	 * Altera a direção do spot.
	 */
	void setSpotDir(TripleFloat spotDir)
	{
		this->spotDir.setF1(spotDir.getF1());
		this->spotDir.setF2(spotDir.getF2());
		this->spotDir.setF3(spotDir.getF3());
	}


	/**
	 * Altera o ângulo do spot.
	 */
	void setCutoff(float cutoff)
	{
		this->cutoff = cutoff;
	}


	/**
	 * Altera o expoente do spot.
	 */
	void setExponent(float exponent)
	{
		this->exponent = exponent;
	}


	/**
	 * Destrutor.
	 */
	~SpotLightImpl(void) = default;
};


/**
 * Construtor por defeito.
 */
SpotLight::SpotLight(void)
{
	pimpl = new SpotLightImpl();
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
 * @param quadratic Atenuação quadrática.
 * @param spotDir   Direção do spot.
 * @param cutoff    Ângulo do spot.
 * @param exponent  Expoente do spot.
 */
SpotLight::SpotLight(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
	                 float constant, float linear, float quadratic,
	                 TripleFloat spotDir, float cutoff, float exponent)
{
	setPos(pos);
	setDiff(diff);
	setSpec(spec);
	setAmbt(ambt);
	setConstant(constant);
	setLinear(linear);
	setQuadratic(quadratic);

	pimpl = new SpotLightImpl(spotDir, cutoff, exponent);
}


/**
 * Construtor de cópia.
 *
 * @param s Objeto da classe SpotLight a copiar.
 */
SpotLight::SpotLight(const SpotLight& s) : Light(s) 
{
	pimpl = new SpotLightImpl(s.pimpl->getSpotDir(), s.pimpl->getCutoff(),
		                      s.pimpl->getExponent());
}


/**
 * Devolve a direção do spot.
 */
TripleFloat SpotLight::getSpotDir(void)
{
	return pimpl->getSpotDir();
}


/**
 * Devolve o ângulo do spot.
 */
float SpotLight::getCutoff(void)
{
	return pimpl->getCutoff();
}


/**
 * Devolve o expoente do spot.
 */
float SpotLight::getExponent(void)
{
	return pimpl->getExponent();
}


/**
 * Altera a direção do spot.
 */
void SpotLight::setSpotDir(TripleFloat spotDir)
{
	return pimpl->setSpotDir(spotDir);
}


/**
 * Altera o ângulo do spot.
 */
void SpotLight::setCutoff(float cutoff)
{
	return pimpl->setCutoff(cutoff);
}


/**
 * Altera o expoente do spot.
 */
void SpotLight::setExponent(float exponent)
{
	return pimpl->setExponent(exponent);
}


/**
 * Apresenta uma luz do tipo spot em OpenGL.
 */
void SpotLight::execute(void)
{
	TripleFloat p = getPos();
	TripleFloat d = getDiff();
	TripleFloat s = getSpec();
	TripleFloat a = getAmbt();
	TripleFloat spotAux = pimpl->getSpotDir();

	Light::updateCurrentLight();

	float pos[4] = { p.getF1(), p.getF2(), p.getF3(), 1.0f };
	float diff[4] = { d.getF1(), d.getF2(), d.getF3(), 1.0f };
	float spec[4] = { s.getF1(), s.getF2(), s.getF3(), 1.0f };
	float ambt[4] = { a.getF1(), a.getF2(), a.getF3(), 1.0f };

	float sP[3] = { spotAux.getF1(), spotAux.getF2(), spotAux.getF3() };

	glLightfv(Light::getLight(), GL_DIFFUSE, diff);
	glLightfv(Light::getLight(), GL_SPECULAR, spec);
	glLightfv(Light::getLight(), GL_AMBIENT, ambt);

	glLightf(Light::getLight(), GL_CONSTANT_ATTENUATION, getConstant());
	glLightf(Light::getLight(), GL_LINEAR_ATTENUATION, getLinear());
	glLightf(Light::getLight(), GL_QUADRATIC_ATTENUATION, getQuadratic());

	glLightfv(Light::getLight(), GL_POSITION, pos);
	glLightfv(Light::getLight(), GL_SPOT_DIRECTION, sP);
	glLightf(Light::getLight(), GL_SPOT_CUTOFF, pimpl->getCutoff());
	glLightf(Light::getLight(), GL_SPOT_EXPONENT, pimpl->getExponent());
}


/**
 * Apresenta uma luz do tipo spot em OpenGL.
 */
void SpotLight::execute(FrustumCulling* f)
{
	execute();
}


/**
 * Destrutor da classe SpotLight.
 */
SpotLight::~SpotLight(void)
{
	if (pimpl != NULL) {
		delete pimpl;
		pimpl = NULL;
	}
}