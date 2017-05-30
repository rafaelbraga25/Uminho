/**
 * @file popMatrix.h
 *
 * M�dulo que representa uma opera��o de popMatrix em OpenGL.
 *
 * @author Carlos Pereira - A61887
 * @author Jo�o Barreira  - A73831
 * @author Rafael Braga   - A61799
 * 
 * @version 26-03-2017
 */


#ifndef popMatrix_h
#define popMatrix_h


#include "glOperation.h"


class PopMatrix : public GLOperation {

public:


	/**
	 * Construtor por defeito.
	 */
	PopMatrix(void) = default;


	/**
	 * Executa uma opera��o de popMatrix em OpenGL.
	 */
	void execute(void)
	{
		glPopMatrix();
	}


	/**
	 * Destrutor (por defeito em c++).
	 */
	~PopMatrix(void) = default;
};

#endif 

