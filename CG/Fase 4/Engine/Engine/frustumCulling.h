/**
 * @file frustumCulling.h
 *
 * @brief Módulo que apresenta métodos que permitem verificar a posição de uma
 *        primitiva relativamente à janela visível (dentro ou fora do campo 
 *        visível).
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 12-05-2017
 */


#ifndef frustumCulling_h
#define frustumCulling_h


#include "tripleFloat.h"


class FrustumCulling {

	class FrustumCullingImpl;
	FrustumCullingImpl* pimpl;


public:


	/**
	 * Construtor por defeito.
	 */
	FrustumCulling(void);


	/**
	 * Construtor de cópia.
	 * 
	 * @param f Objeto da classe FrustumCulling a copiar.
	 */
	FrustumCulling(const FrustumCulling& f);


	/**
	 * Altera a perpectiva do campo visível de acordo com os critérios
	 * recebidos. Esta função deve ser invocada sempre que se invoca a 
	 * função gluPerspective.
	 *
	 * @param angle Fovy.
	 * @param ratio Rácio da janela.
	 * @param near  Posição do plano near no eixo dos zz.
	 * @param far   Posição do plano far no eixo dos zz.
	 */
	void setPerspective(float angle, float ratio, float near, float far);

	
	/**
	 * Altera as definições da camera. Esta função deve ser invocada sempre
	 * que se invoca a função gluLookAt.
	 *
	 * @param pos  Posição da camera.
	 * @param look Posição para onde a camera está apontada.
	 * @param up   Normal da camera.
	 */
	void setCam(TripleFloat pos, TripleFloat look, TripleFloat up);


	/**
	 * Testa se um ponto se situa no campo visível.
	 *
	 * @param point Ponto a testar.
	 */
	bool pointInFrustum(TripleFloat point);


	/**
	 * Testa se uma esfera se situa no campo visível.
	 *
	 * @param point  Origem da esfera.
	 * @param radius Raio da esfera.
	 */
	bool sphereInFrustum(TripleFloat point, float radius);


	/**
	 * Devolve as coordenadas atualizadas após a última translação.
	 */
	TripleFloat getCoords(void);


	/**
	 * Atualiza o centro onde as primitivas são desenhadas conforme as suas
	 * translações e rotações. Deve ser invocada sempre que ocorre uma 
	 * pushMatrix.
	 */
	void pushCoords(void);


	/**
	 * Remove da stack as últimas coordenadas respetivas a translações e 
	 * rotações. Deve ser invocada sempre que ocorre uma popMatrix.
	 */
	void popCoords(void);


	/**
	 * Translada o centro onde serão desenhadas as primitivas. Deve ser 
	 * invocada sempre que ocorre uma glTranslate.
	 */
	void translateCoords(float x, float y, float z);


	/**
	 * Efetua uma rotação sobre o centro onde serão desenhadas as primitivas. 
	 * Deve ser invocada sempre que ocorre uma glRotate.
	 */
	void rotateCoords(float axisX, float axisY, float axisZ, float angle);


	/**
	 * Destrutor.
	 */
	~FrustumCulling(void);

};


#endif 
