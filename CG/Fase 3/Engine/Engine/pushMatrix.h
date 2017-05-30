/**
 * @file pushMatrix.h
 *
 * M�dulo que representa uma opera��o de pushMatrix em OpenGL. 
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799 
 *
 * @version 26-03-2017
 */


#ifndef pushMatrix_h
#define pushMatrix_h


#include "glOperation.h"


class PushMatrix : public GLOperation {

public:

	/**
	 * Construtor por defeito.
	 */
	PushMatrix(void) = default;


	/**
	 * Executa uma opera��o de pushMatrix em OpenGL.
	 */
	void execute(void)
	{
		glPushMatrix();
	}


	/**
	 * Destrutor (por defeito em c++).
	 */
	~PushMatrix(void) = default;
};


#endif
