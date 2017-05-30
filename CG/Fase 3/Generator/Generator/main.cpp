/**
* @file main.cpp
*
* @brief Definição de todos métodos para o funcionamento do programa Generator.
*
* @author Carlos Pereira - A61887
* @author João Barreira  - A73831
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


// Uma Box possui 5 parâmetros: <dimX> <dimY> <dimZ> <numDiv (opcional)> <fich>  
#define BOX "box"
#define BOX_ARGS 5


// Um Cone possui 5 parâmetros: <radius> <height> <stacks> <slices> <fich>  
#define CONE "cone"
#define CONE_ARGS 5

// Dois argumentos do cone são valores inteiros (stacks e slices)
// Estes dois argumentos são recebidos como valores reias e posteriormente
// convertidos para valores inteiros
#define CONE_CEILS 2


// Um Plane possui 3 parâmetros: <dimX> <dimZ> <fich>  
#define PLANE "plane"
#define PLANE_ARGS 3
#define PLANE_CEILS 0


// Uma Sphere possui 4 parâmetros: <radius> <stacks> <slices> <fich>  
#define SPHERE "sphere"
#define SPHERE_ARGS 4

// Dois argumentos do cone são valores inteiros (stacks e slices)
// Estes dois argumentos são recebidos como valores reias e posteriormente
// convertidos para valores inteiros
#define SPHERE_CEILS 2


// O menor número de parâmetros recebidos possível é 5
// <nome do programa (Generator)> <nome da primitiva> e os argumentos do plano
#define MIN_PARAMS 5


std::vector<Vertex> vertices;  // Conjunto de vértices de uma primitiva
std::vector<size_t> indexes;   // Conjunto de índices dos vértices de uma 
							   // primitiva
std::string fileName;          // Nome do ficheiro que irá conter os vértices
							   // de uma primitiva
std::vector<float> arguments;  // Conjunto de argumentos numéricos de uma
							   // primitiva
Primitive *p = NULL;           // Primitiva a ser guardada


/**
 * Verifica se os argumentos fornecidos para o cálculo de uma primitiva
 * são válidos. Ou seja, a última posição do vetor de strings deverá conter o
 * nome ficheiro onde será guardada a informação dos vértices. As restantes
 * posições do vetor devem conter valores numéricos.
 *
 * @param params Lista de parâmetros de uma primitiva.
 * @param numParams Número de parâmetros válidos de uma primitiva.
 * @param ceilParams Número de parâmetros a serem convertidos para valores
 *                   inteiros arredondados para cima.
 *
 * @return Devolve falso se os parâmetros forem inválios ou verdadeiro caso
 *         contrário. Os valores numéricos são guardados em arguments.
 */
bool generateArgs(std::vector<std::string> params, const size_t numParams,
	const size_t ceilParams)
{
	bool ret = true; // Por defeito assume-se que os parâmetros são válidos

	// Testa-se primeiro se o número de parâmetros corresponde ao número de
	// parâmetros válidos de uma primitiva
	if (params.size() == numParams) {

		// Extrai-se o nome do ficheiro
		fileName = params.back();

		// Extraem-se todos os valores numéricos da primitiva
		for (size_t i = 0; i < params.size() - 1 && ret; i++) {
			std::stringstream ss(params.at(i));

			float flt = 0;

			// Se não se conseguir converter um valor o ciclo termina
			if (!(ss >> flt)) {
				ret = false;
			}
			else {

				// Arredonda os parâmetros necessários
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
 * Cria uma instância da classe Box bem como os seus vértices.
 *
 * @params Parâmetros de uma box.
 * @return Falso caso os parâmetros sejam inválidos ou verdadeiro caso
 *         contrário. Os vértices são guardados em vertices.
 */
bool generateBox(std::vector<std::string> params)
{
	bool ret = false;

	// Se foi dado como argumento o número de divisões da caixa, então
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
 * Cria uma instância da classe Cone bem como os seus vértices.
 *
 * @params Parâmetros de um cone.
 * @return Falso caso os parâmetros sejam inválidos ou verdadeiro caso
 *         contrário. Os vértices são guardados em vertices.
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
 * Cria uma instância da classe Plane bem como os seus vértices.
 *
 * @params Parâmetros de um plane.
 * @return Falso caso os parâmetros sejam inválidos ou verdadeiro caso
 *         contrário. Os vértices são guardados em vertices.
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
 * Cria uma instância da classe Sphere bem como os seus vértices.
 *
 * @params Parâmetros de uma sphere.
 * @return Falso caso os parâmetros sejam inválidos ou verdadeiro caso
 *         contrário. Os vértices são guardados em vertices.
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
 * Caso o tipo de primitiva seja válido então é feita a validade dos seus
 * parâmetros e respetiva geração dos seus vértices.
 *
 * @params primitive Tipo de primitiva.
 * @params Parâmetros de uma primitiva.
 * @return Falso caso o tipo de primitiva seja inválido ou verdadeiro caso
 *         contrário.
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
 * A partir dos vetores de vértices e índices, gera os pontos
 * correspondentes às patches de Bezier.
 *
 * @param pVertices Vetor de vértices
 * @param pIndexes  Vetor de índices
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
 * Lê os vértices e os índices de um ficheiro com a descrição
 * das patches de Bezier.
 *
 * @param fileName Nome do ficheiro que contém as patches
 * @param t        Valor da tesselagem
 *
 * @return Falso caso o ficheiro não tenha sido bem aberto
 */
bool readBezierPatches(char* fileName, size_t t)
{
	bool ret = true;

	std::fstream fp;

	std::string line;      // String auxiliar que irá corresponder a uma 
						   // linha do ficheiro
	std::stringstream ss;  // String auxiliar para converter texto em 
						   // valores numéricos

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

		// Lê linha a linha
		while (getline(fp, line)) {
			std::stringstream ss(line);

			// Entra em modo de leitura de índices caso encontre uma
			// linha vazia
			if (firstLine == true) {
				ss >> numPatches;
				firstLine = false;
			}

			// Se a linha atual estiver na zona dos índices
			if (lineNumber >= 1 && lineNumber <= numPatches) {
				std::string token;

				// Retiram-se os índices que se encontram separados
				// por vírgulas
				while (std::getline(ss, token, ',')) {
					std::stringstream aux(token);
					aux >> index;

					// Adiciona-se o índice retirado do ficheiro
					// ao vetor dos índices
					auxIndexes.push_back(index);
				}
			}

			// Se a linha atual estiver na zona dos vértices
			if (lineNumber > numPatches + 1) {
				std::string token;

				// Retiram-se os vértices que se encontram separados
				// por vírgulas
				while (std::getline(ss, token, ',')) {
					std::stringstream aux(token);
					aux >> coord[coordIndex];

					// Adicionam-se as coordenadas ao vetor de vértices
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

	// A partir dos vetores dos vértices e dos índices retirados do
	// ficheiro, são geradas as patches de Bezier
	generateBezierPatches(auxVertices, auxIndexes, t);

	return ret;
}


/**
 * Função principal do programa.
 *
 * @param argc Número de parâmetros recebidos.
 * @param argv Parâmetros recebidos.
 */
int main(int argc, char** argv)
{
	bool ok = false;
	std::ofstream file;
	size_t t = 0;

	// Começa-se por testar se o número de parâmetros recebidos é
	// superior ou igual ao número mínimo de parâmetros de uma primitiva
	if (argc >= MIN_PARAMS) {

		// O nome da primitiva corresponde ao primeiro parâmetro
		std::string primitive(argv[1]);

		std::transform(primitive.begin(), primitive.end(), primitive.begin(),
			tolower);


		// Os argumentos da primitiva correspondem a todos os outros
		// parâmetros
		std::vector<std::string> params;

		for (int i = 2; i < argc; i++) {
			params.push_back(argv[i]);
		}

		ok = generatePrimitive(primitive, params);
	}
	else if (argc == 4) {
		std::stringstream ss(argv[2]);

		// Lê-se o valor da tesselagem
		ss >> t;

		// Invoca-se a função de leitura do ficheiro de patches de Bezier
		ok = readBezierPatches(argv[1], t);

		fileName = argv[3];
	}

	// Se a primitiva foi bem gerada então, armazenam-se os seus vértices no
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