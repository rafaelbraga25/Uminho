/**
* @file main.cpp
*
* @brief Defini��o de todos m�todos para o funcionamento do programa Generator.
*
* @author Carlos Pereira - A61887
* @author Jo�o Barreira  - A73831
* @author Rafael Braga   - A61799
*
* @version 29-4-2017
*/


#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "plane.h"
#include "box.h"
#include "cone.h"
#include "sphere.h"
#include "cubicCurves.h"


// Uma Box possui 5 par�metros: <dimX> <dimY> <dimZ> <numDiv (opcional)> <fich>  
#define BOX "box"
#define BOX_ARGS 5


// Um Cone possui 5 par�metros: <radius> <height> <stacks> <slices> <fich>  
#define CONE "cone"
#define CONE_ARGS 5

// Dois argumentos do cone s�o valores inteiros (stacks e slices)
// Estes dois argumentos s�o recebidos como valores reias e posteriormente
// convertidos para valores inteiros
#define CONE_CEILS 2


// Um Plane possui 3 par�metros: <dimX> <dimZ> <fich>  
#define PLANE "plane"
#define PLANE_ARGS 3
#define PLANE_CEILS 0


// Uma Sphere possui 4 par�metros: <radius> <stacks> <slices> <fich>  
#define SPHERE "sphere"
#define SPHERE_ARGS 4

// Dois argumentos do cone s�o valores inteiros (stacks e slices)
// Estes dois argumentos s�o recebidos como valores reias e posteriormente
// convertidos para valores inteiros
#define SPHERE_CEILS 2


// O menor n�mero de par�metros recebidos poss�vel � 5
// <nome do programa (Generator)> <nome da primitiva> e os argumentos do plano
#define MIN_PARAMS 5


std::vector<Vertex> vertices;  // Conjunto de v�rtices de uma primitiva
std::vector<size_t> indexes;   // Conjunto de �ndices dos v�rtices de uma 
							   // primitiva
std::string fileName;          // Nome do ficheiro que ir� conter os v�rtices
							   // de uma primitiva
std::vector<float> arguments;  // Conjunto de argumentos num�ricos de uma
							   // primitiva
Primitive *p = NULL;           // Primitiva a ser guardada


/**
 * Verifica se os argumentos fornecidos para o c�lculo de uma primitiva
 * s�o v�lidos. Ou seja, a �ltima posi��o do vetor de strings dever� conter o
 * nome ficheiro onde ser� guardada a informa��o dos v�rtices. As restantes
 * posi��es do vetor devem conter valores num�ricos.
 *
 * @param params Lista de par�metros de uma primitiva.
 * @param numParams N�mero de par�metros v�lidos de uma primitiva.
 * @param ceilParams N�mero de par�metros a serem convertidos para valores
 *                   inteiros arredondados para cima.
 *
 * @return Devolve falso se os par�metros forem inv�lios ou verdadeiro caso
 *         contr�rio. Os valores num�ricos s�o guardados em arguments.
 */
bool generateArgs(std::vector<std::string> params, const size_t numParams,
	const size_t ceilParams)
{
	bool ret = true; // Por defeito assume-se que os par�metros s�o v�lidos

	// Testa-se primeiro se o n�mero de par�metros corresponde ao n�mero de
	// par�metros v�lidos de uma primitiva
	if (params.size() == numParams) {

		// Extrai-se o nome do ficheiro
		fileName = params.back();

		// Extraem-se todos os valores num�ricos da primitiva
		for (size_t i = 0; i < params.size() - 1 && ret; i++) {
			std::stringstream ss(params.at(i));

			float flt = 0;

			// Se n�o se conseguir converter um valor o ciclo termina
			if (!(ss >> flt)) {
				ret = false;
			}
			else {

				// Arredonda os par�metros necess�rios
				if (i < params.size() - 1 - ceilParams) {
					arguments.push_back(flt);
				}
				else {
					arguments.push_back(ceil(flt));
				}
			}
		}
	}
	else {
		ret = false;
	}

	return ret;
}



/**
 * Cria uma inst�ncia da classe Box bem como os seus v�rtices.
 *
 * @params Par�metros de uma box.
 * @return Falso caso os par�metros sejam inv�lidos ou verdadeiro caso
 *         contr�rio. Os v�rtices s�o guardados em vertices.
 */
bool generateBox(std::vector<std::string> params)
{
	bool ret = false;

	// Se foi dado como argumento o n�mero de divis�es da caixa, ent�o
	// este deve ser convertido para um valor inteiro
	size_t boxCeils = (params.size() == BOX_ARGS) ? 1 : 0;

	if (params.size() >= BOX_ARGS - 1) {
		ret = generateArgs(params, params.size(), boxCeils);

		if (ret) {
			if (boxCeils == 0) {
				p = new Box(arguments.at(0), arguments.at(1), arguments.at(2));
			}
			else {
				p = new Box(arguments.at(0), arguments.at(1), arguments.at(2),
					(int)arguments.at(3));
			}

			vertices = p->getVertices();
			indexes = p->getIndexes();
		}
	}

	return ret;
}


/**
 * Cria uma inst�ncia da classe Cone bem como os seus v�rtices.
 *
 * @params Par�metros de um cone.
 * @return Falso caso os par�metros sejam inv�lidos ou verdadeiro caso
 *         contr�rio. Os v�rtices s�o guardados em vertices.
 */
bool generateCone(std::vector<std::string> params)
{
	bool ret = generateArgs(params, CONE_ARGS, CONE_CEILS);

	if (ret) {
		p = new Cone(arguments.at(0), arguments.at(1),
			(int)arguments.at(2), (int)arguments.at(3));

		vertices = p->getVertices();
		indexes = p->getIndexes();
	}

	return ret;
}


/**
 * Cria uma inst�ncia da classe Plane bem como os seus v�rtices.
 *
 * @params Par�metros de um plane.
 * @return Falso caso os par�metros sejam inv�lidos ou verdadeiro caso
 *         contr�rio. Os v�rtices s�o guardados em vertices.
 */
bool generatePlane(std::vector<std::string> params)
{
	bool ret = generateArgs(params, PLANE_ARGS, PLANE_CEILS);

	if (ret) {
		p = new Plane(arguments.at(0), arguments.at(1));

		vertices = p->getVertices();
		indexes = p->getIndexes();
	}

	return ret;
}


/**
 * Cria uma inst�ncia da classe Sphere bem como os seus v�rtices.
 *
 * @params Par�metros de uma sphere.
 * @return Falso caso os par�metros sejam inv�lidos ou verdadeiro caso
 *         contr�rio. Os v�rtices s�o guardados em vertices.
 */
bool generateSphere(std::vector<std::string> params)
{
	bool ret = generateArgs(params, SPHERE_ARGS, SPHERE_CEILS);

	if (ret) {
		p = new Sphere(arguments.at(0),
			(int)arguments.at(1), (int)arguments.at(2));

		vertices = p->getVertices();
		indexes = p->getIndexes();
	}

	return ret;
}


/**
 * Verifica o tipo de primitiva a ser gerada.
 * Caso o tipo de primitiva seja v�lido ent�o � feita a validade dos seus
 * par�metros e respetiva gera��o dos seus v�rtices.
 *
 * @params primitive Tipo de primitiva.
 * @params Par�metros de uma primitiva.
 * @return Falso caso o tipo de primitiva seja inv�lido ou verdadeiro caso
 *         contr�rio.
 */
bool generatePrimitive(std::string primitive, std::vector<std::string> params)
{
	bool ret = false;

	if (primitive.compare(BOX) == 0) {
		ret = generateBox(params);
	}
	else if (primitive.compare(CONE) == 0) {
		ret = generateCone(params);
	}
	else if (primitive.compare(PLANE) == 0) {
		ret = generatePlane(params);
	}
	else if (primitive.compare(SPHERE) == 0) {
		ret = generateSphere(params);
	}

	return ret;
}


/*
 * A partir dos vetores de v�rtices e �ndices, gera os pontos
 * correspondentes �s patches de Bezier.
 *
 * @param pVertices Vetor de v�rtices
 * @param pIndexes  Vetor de �ndices
 * @param t         Tesselagem
 */
void generateBezierPatches(std::vector<Vertex> pVertices,
	std::vector<size_t> pIndexes,
	size_t t)
{
	size_t i = 0;
	size_t j = 0;
	size_t w = 0;
	size_t z = 0;
	size_t start = 0;
	size_t index = 0;
	size_t patch = 0;

	float u = 0.0f;
	float v = 0.0f;

	float pos[3];
	float pMatrixX[4][4];
	float pMatrixY[4][4];
	float pMatrixZ[4][4];


	for (start = 0; start < pIndexes.size(); start += 16) {
		for (i = 0; i <= t; i++) {
			u = ((float)i) / ((float)t);

			for (j = 0; j <= t; j++) {
				v = ((float)j) / ((float)t);

				for (w = 0; w < 4; w++) {
					for (z = 0; z < 4; z++) {
						pMatrixX[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getX();
						pMatrixY[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getY();
						pMatrixZ[w][z] = pVertices.at(pIndexes.at(start + w * 4 + z)).getZ();
					}
				}

				getBezierPoint(u, v, (float**)pMatrixX, (float**)pMatrixY, (float**)pMatrixZ, pos);

				vertices.push_back(Vertex(pos[0], pos[1], pos[2]));
			}
		}
	}

	for (start = 0; start < pIndexes.size() / 16; start++) {
		patch = (t + 1) * (t + 1) * start;

		for (i = 0; i < t; i++) {
			for (j = 0; j < t; j++) {
				indexes.push_back(patch + ((t + 1) * i) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j + 1);
				indexes.push_back(patch + ((t + 1) * i) + j + 1);

				indexes.push_back(patch + ((t + 1) * i) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j);
				indexes.push_back(patch + (t + 1) * (i + 1) + j + 1);
			}
		}
	}
}


/*
 * L� os v�rtices e os �ndices de um ficheiro com a descri��o
 * das patches de Bezier.
 *
 * @param fileName Nome do ficheiro que cont�m as patches
 * @param t        Valor da tesselagem
 *
 * @return Falso caso o ficheiro n�o tenha sido bem aberto
 */
bool readBezierPatches(char* fileName, size_t t)
{
	bool ret = true;

	std::fstream fp;

	std::string line;      // String auxiliar que ir� corresponder a uma 
						   // linha do ficheiro
	std::stringstream ss;  // String auxiliar para converter texto em 
						   // valores num�ricos

	float coord[3];

	size_t coordIndex = 0;
	size_t index = 0;
	size_t numPatches = 0;
	size_t lineNumber = 0;

	bool firstLine = true;

	std::vector<Vertex> auxVertices;
	std::vector<size_t> auxIndexes;

	fp.open(fileName);

	// Testa se o ficheiro foi bem aberto e inicia a sua leitura
	if (fp.is_open()) {

		// L� linha a linha
		while (getline(fp, line)) {
			std::stringstream ss(line);

			// Entra em modo de leitura de �ndices caso encontre uma
			// linha vazia
			if (firstLine == true) {
				ss >> numPatches;
				firstLine = false;
			}

			// Se a linha atual estiver na zona dos �ndices
			if (lineNumber >= 1 && lineNumber <= numPatches) {
				std::string token;

				// Retiram-se os �ndices que se encontram separados
				// por v�rgulas
				while (std::getline(ss, token, ',')) {
					std::stringstream aux(token);
					aux >> index;

					// Adiciona-se o �ndice retirado do ficheiro
					// ao vetor dos �ndices
					auxIndexes.push_back(index);
				}
			}

			// Se a linha atual estiver na zona dos v�rtices
			if (lineNumber > numPatches + 1) {
				std::string token;

				// Retiram-se os v�rtices que se encontram separados
				// por v�rgulas
				while (std::getline(ss, token, ',')) {
					std::stringstream aux(token);
					aux >> coord[coordIndex];

					// Adicionam-se as coordenadas ao vetor de v�rtices
					if (++coordIndex == 3) {
						auxVertices.push_back(Vertex(coord[0], coord[1], coord[2]));
						coordIndex = 0;
					}
				}
			}

			lineNumber++;
		}

		fp.close();
	}
	else {
		ret = false;
	}

	// A partir dos vetores dos v�rtices e dos �ndices retirados do
	// ficheiro, s�o geradas as patches de Bezier
	generateBezierPatches(auxVertices, auxIndexes, t);

	return ret;
}


/**
 * Fun��o principal do programa.
 *
 * @param argc N�mero de par�metros recebidos.
 * @param argv Par�metros recebidos.
 */
int main(int argc, char** argv)
{
	bool ok = false;
	std::ofstream file;
	size_t t = 0;

	// Come�a-se por testar se o n�mero de par�metros recebidos �
	// superior ou igual ao n�mero m�nimo de par�metros de uma primitiva
	if (argc >= MIN_PARAMS) {

		// O nome da primitiva corresponde ao primeiro par�metro
		std::string primitive(argv[1]);

		std::transform(primitive.begin(), primitive.end(), primitive.begin(),
			tolower);


		// Os argumentos da primitiva correspondem a todos os outros
		// par�metros
		std::vector<std::string> params;

		for (int i = 2; i < argc; i++) {
			params.push_back(argv[i]);
		}

		ok = generatePrimitive(primitive, params);
	}
	else if (argc == 4) {
		std::stringstream ss(argv[2]);

		// L�-se o valor da tesselagem
		ss >> t;

		// Invoca-se a fun��o de leitura do ficheiro de patches de Bezier
		ok = readBezierPatches(argv[1], t);

		fileName = argv[3];
	}

	// Se a primitiva foi bem gerada ent�o, armazenam-se os seus v�rtices no
	// ficheiro especificado como argumento do programa
	if (ok) {
		file.open(fileName);

		for (size_t i = 0; i < vertices.size(); i++) {
			file << vertices.at(i).toString() << std::endl;
		}

		file << std::endl;

		for (size_t i = 0; i < indexes.size(); i++) {
			file << indexes.at(i) << std::endl;
		}

		file.close();

		if (p != NULL) {
			delete p;
			p = NULL;
		}

		std::cout << "Primitive generated successfully!" << std::endl;
	}
	else {
		std::cout << "Invalid Arguments!" << std::endl;
	}

	std::cout << "Press any key to continue..." << std::endl;

	getchar();
	return 0;
}