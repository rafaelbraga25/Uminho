/**
 * @file frustumCulling.h
 *
 * @brief M�dulo que apresenta m�todos que permitem verificar a posi��o de uma
 *        primitiva relativamente � janela vis�vel (dentro ou fora do campo 
 *        vis�vel).
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
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
	 * Construtor de c�pia.
	 * 
	 * @param f Objeto da classe FrustumCulling a copiar.
	 */
	FrustumCulling(const FrustumCulling& f);


	/**
	 * Altera a perpectiva do campo vis�vel de acordo com os crit�rios
	 * recebidos. Esta fun��o deve ser invocada sempre que se invoca a 
	 * fun��o gluPerspective.
	 *
	 * @param angle Fovy.
	 * @param ratio R�cio da janela.
	 * @param near  Posi��o do plano near no eixo dos zz.
	 * @param far   Posi��o do plano far no eixo dos zz.
	 */
	void setPerspective(float angle, float ratio, float near, float far);

	
	/**
	 * Altera as defini��es da camera. Esta fun��o deve ser invocada sempre
	 * que se invoca a fun��o gluLookAt.
	 *
	 * @param pos  Posi��o da camera.
	 * @param look Posi��o para onde a camera est� apontada.
	 * @param up   Normal da camera.
	 */
	void setCam(TripleFloat pos, TripleFloat look, TripleFloat up);


	/**
	 * Testa se um ponto se situa no campo vis�vel.
	 *
	 * @param point Ponto a testar.
	 */
	bool pointInFrustum(TripleFloat point);


	/**
	 * Testa se uma esfera se situa no campo vis�vel.
	 *
	 * @param point  Origem da esfera.
	 * @param radius Raio da esfera.
	 */
	bool sphereInFrustum(TripleFloat point, float radius);


	/**
	 * Devolve as coordenadas atualizadas ap�s a �ltima transla��o.
	 */
	TripleFloat getCoords(void);


	/**
	 * Atualiza o centro onde as primitivas s�o desenhadas conforme as suas
	 * transla��es e rota��es. Deve ser invocada sempre que ocorre uma 
	 * pushMatrix.
	 */
	void pushCoords(void);


	/**
	 * Remove da stack as �ltimas coordenadas respetivas a transla��es e 
	 * rota��es. Deve ser invocada sempre que ocorre uma popMatrix.
	 */
	void popCoords(void);


	/**
	 * Translada o centro onde ser�o desenhadas as primitivas. Deve ser 
	 * invocada sempre que ocorre uma glTranslate.
	 */
	void translateCoords(float x, float y, float z);


	/**
	 * Efetua uma rota��o sobre o centro onde ser�o desenhadas as primitivas. 
	 * Deve ser invocada sempre que ocorre uma glRotate.
	 */
	void rotateCoords(float axisX, float axisY, float axisZ, float angle);


	/**
	 * Destrutor.
	 */
	~FrustumCulling(void);

};


#endif 
