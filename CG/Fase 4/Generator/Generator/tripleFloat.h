/**
* @file tripleFloat.h
*
* @brief M�dulo que representa um conjunto de tr�s floats.
*
* @author Carlos Pereira - A61887
* @author Jo�o Barreira  - A73831
* @author Rafael Braga   - A61799
*
* @version 06-05-2017
*/


#ifndef tripleFloat_h
#define tripleFloat_h


#include <string>


class TripleFloat {
	class TripleFloatImpl;
	TripleFloatImpl* pimpl;

public:

	/*
	* Construtor por defeito.
	*/
	TripleFloat(void);


	/**
	* Construtor por par�metros.
	*
	* @param f1 Primeiro float.
	* @param f2 Segundo float.
	* @param f3 Terceiro float.
	*/
	TripleFloat(float f1, float f2, float f3);


	/*
	* Construtor de c�pia.
	*
	* @param t Objeto da classe TripleFloat a ser copiado.
	*/
	TripleFloat(const TripleFloat& t);


	/**
	* Devolve o primeiro float.
	*/
	float getF1(void);


	/**
	* Devolve o segundo float.
	*/
	float getF2(void);


	/**
	* Devolve o terceiro float.
	*/
	float getF3(void);


	/**
	* Altera o valor do primeiro float.
	*/
	void setF1(float f1);


	/**
	* Altera o valor do segundo float.
	*/
	void setF2(float f2);


	/**
	* Altera o valor do terceiro float.
	*/
	void setF3(float f3);


	/**
	* Devolve uma representa��o textual da classe TripleFloat.
	*/
	std::string toString();


	/**
	* Destrutor da classe TripleFloat.
	*/
	~TripleFloat(void);
};

#endif 


