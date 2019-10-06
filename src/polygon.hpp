// Augmented reality
// triangle.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2019


#include "Objects.hpp"
#include <string>


#ifndef __POLYGON_HPP__
#define __POLYGON_HPP__

/////////////////////////////////////////////////////////////
/*!
* \brief Classe cube, responsável por todas as primitivas necessárias para construção de um cubo na tela.
*/
class cube: public Objects
{
public:	
	cube(double x, double y, double z, double tam, std::string state[4][4], int id);
	~cube();

	void draw();
	void update(int value);
	void colision(int x, int y);

private:

	int x,y,z;
	float theta;
	std::string state[4][4];
	int id;

	glm::vec3 points_base[24];
	glm::vec3 points[24];


private:

	void transform(void);
};

#endif
