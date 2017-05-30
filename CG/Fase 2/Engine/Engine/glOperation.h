/**
 * @file glOperation.h
 *
 * M�dulo que representa a classe base para uma opera��o qualquer em
 * OpenGL (transla��o, rota��o, desenho de primitivas, etc).
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 *
 * @version 26-03-2017
 */


#ifndef glOperation_h
#define glOperation_h


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


class GLOperation {

public:

	/**
	 * Construtor da classe Operation (por defeito em c++).
	 */
	GLOperation(void) = default;


	/**
	 * M�todo abstrato de uma qualquer opera��o em OpenGL.
	 */
	virtual void execute(void) = 0;


	/**
	 * Destrutor da classe Operation (por defeito em c++). Todas as classes
	 * derivadas desta classe implementam as suas vers�es deste destrutor.
	 */
	virtual ~GLOperation(void) = default;
};


#endif
