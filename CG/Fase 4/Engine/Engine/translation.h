/**
 * @file translation.h
 *
 * @brief Módulo que apresenta métodos para se efetuar uma translação em OpenGL.
 *
 * Uma translação pode ser definida à custa dos valores de x, y e z.
 *
 * @author Carlos Pereira - A61887
 * @author João Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 06-05-2017
 */


#ifndef translation_h
#define translation_h


#include <vector>
#include "glOperation.h"
#include "tripleFloat.h"


class Translation : public GLOperation {
	class TranslationImpl;   // Implementação da classe Translation
	TranslationImpl* pimpl;  // Apontador para a implementação da classe 
	                         // Translation

public:

	/**
	 * Construtor por defeito.
	 */
	Translation(void);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x Valor de uma translação em x.
	 * @param y Valor de uma translação em y.
	 * @param z Valor de uma translação em z.
	 */
	Translation(float x, float y, float z);


	/**
	 * Construtor por parâmetros.
	 *
	 * @param x				Valor de uma translação em x.
	 * @param y				Valor de uma translação em y.
	 * @param z				Valor de uma translação em z.
	 * @param catmullPoints	Coordenadas dos pontos da curva Catmull-Rom.
	 * @param totalTime		Tempo total de translação.
	 */
	Translation(float x, float y, float z,
		        std::vector<TripleFloat> catmullPoints, float totalTime);


	/**
	 * Construtor de cópia.
	 *
	 * @param t Objeto da classe Translation a copiar.
	 */
	Translation(const Translation& t);


	/**
	 * Devolve o valor de uma translação em x.
	 */
	float getX(void);


	/**
	 * Devolve o valor de uma translação em y.
	 */
	float getY(void);


	/**
	 * Devolve o valor de uma translação em z.
	 */
	float getZ(void);


	/**
	 * Devolve um vector com as coordenadas dos pontos da curva.
	 */
	std::vector<TripleFloat> getCatmullPoints(void);


	/**
	 * Devolve o tempo total de translação na curva.
	 */
	float getTotalTime(void);


	/**
	 * Altera o valor de uma translação em x.
	 */
	void setX(float);


	/**
	 * Altera o valor de uma translação em y.
	 */
	void setY(float);


	/**
	 * Altera o valor de uma translação em z.
	 */
	void setZ(float);


	/**
	 * Altera o vector com as coordenadas dos pontos da curva.
	 */
	void setCatmullPoints(std::vector<TripleFloat>);


	/**
	 * Altera o tempo total de translação.
	 */
	void setTotalTime(float);


	/**
	 * Executa uma translação em x, y ou z em OpenGL.
	 */
	void execute(void);


	/**
	 * Executa uma translação em x, y ou z em OpenGL.
	 */
	void execute(FrustumCulling*);


	/**
	 * Destrutor da classe Translation.
	 */
	~Translation(void);
};


#endif

