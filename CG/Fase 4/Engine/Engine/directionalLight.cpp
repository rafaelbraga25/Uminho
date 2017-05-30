/**
 * @file directionalLight.cpp
 *
 * Definição de todos os métodos para se representar uma luz direcional em
 * OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#include "directionalLight.h"


 /**
  * Construtor por defeito.
  */
DirectionalLight::DirectionalLight(void) = default;


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
 */
DirectionalLight::DirectionalLight(TripleFloat pos, TripleFloat diff, TripleFloat spec, TripleFloat ambt,
	                               float constant, float linear, float quadratic)
{
	setPos(pos);
	setDiff(diff);
	setSpec(spec);
	setAmbt(ambt);
	setConstant(constant);
	setLinear(linear);
	setQuadratic(quadratic);
}


/**
 * Construtor de cópia.
 *
 * @param d Objeto da classe DirectionalLight a copiar.
 */
DirectionalLight::DirectionalLight(const DirectionalLight& d) : Light(d) { }


/**
 * Apresenta uma luz direcional em OpenGL.
 */
void DirectionalLight::execute(void)
{
	TripleFloat p = getPos();
	TripleFloat d = getDiff();
	TripleFloat s = getSpec();
	TripleFloat a = getAmbt();

	// Muda a luz em OpenGL
	Light::updateCurrentLight();

	float pos[4] = { p.getF1(), p.getF2(), p.getF3(), 0.0f };
	float diff[4] = { d.getF1(), d.getF2(), d.getF3(), 1.0f };
	float spec[4] = { s.getF1(), s.getF2(), s.getF3(), 1.0f };
	float ambt[4] = { a.getF1(), a.getF2(), a.getF3(), 1.0f };

	glLightfv(Light::getLight(), GL_DIFFUSE, diff);
	glLightfv(Light::getLight(), GL_SPECULAR, spec);
	glLightfv(Light::getLight(), GL_AMBIENT, ambt);

	glLightf(Light::getLight(), GL_CONSTANT_ATTENUATION, getConstant());
	glLightf(Light::getLight(), GL_LINEAR_ATTENUATION, getLinear());
	glLightf(Light::getLight(), GL_QUADRATIC_ATTENUATION, getQuadratic());

	glLightfv(Light::getLight(), GL_POSITION, pos);
}


/**
 * Apresenta uma luz direcional em OpenGL.
 */
void DirectionalLight::execute(FrustumCulling* f)
{
	execute();
}


/**
 * Destrutor da classe DirectionalLight.
 */
DirectionalLight::~DirectionalLight(void) = default;