// Elo Maluco
// main.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2019

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "polygon.hpp"
#include "tga.h"
/*!
* \brief Construtor. Cria as seis faces de um cubo.
* \* As coordenadas (x,y,z) representam o centro de massa do cubo a ser criado.
* \* O argumento tam representa o tamanho da aresta do cubo.
*/

cube::cube(double x_cm, double y_cm, double z_cm, double tam, std::string state[4][4], int id)
{
	this->id = id;
	for (int i=0; i<4;i++){
        for (int j=0;j<4;j++){
            this->state[i][j] = state[i][j];
        } 
    }
	tam = tam/2;

	//primeira face - referencial z
	points_base[0] = glm::vec3( x_cm-tam, y_cm-tam, z_cm-tam);
    points_base[1] = glm::vec3( x_cm-tam, y_cm+tam, z_cm-tam);
	points_base[2] = glm::vec3( x_cm+tam, y_cm+tam, z_cm-tam);
    points_base[3] = glm::vec3( x_cm+tam, y_cm-tam, z_cm-tam);
	      
	points[0] = points_base[0];
	points[1] = points_base[1];
	points[2] = points_base[2];
	points[3] = points_base[3];
	//fim primeira face

	//segunda face
	points_base[4] = glm::vec3( x_cm-tam, y_cm-tam, z_cm+tam);
    points_base[5] = glm::vec3( x_cm-tam, y_cm+tam, z_cm+tam);
	points_base[6] = glm::vec3( x_cm+tam, y_cm+tam, z_cm+tam);
    points_base[7] = glm::vec3( x_cm+tam, y_cm-tam, z_cm+tam);
	      
	points[4] = points_base[4];
	points[5] = points_base[5];
	points[6] = points_base[6];
	points[7] = points_base[7];
	//fim segunda face

	//terceira face - referencial y
	points_base[8] = glm::vec3( x_cm-tam, y_cm-tam, z_cm-tam);
    points_base[9] = glm::vec3( x_cm-tam, y_cm-tam, z_cm+tam);
    points_base[10] = glm::vec3( x_cm+tam, y_cm-tam, z_cm+tam);
	points_base[11] = glm::vec3( x_cm+tam, y_cm-tam, z_cm-tam);
	      
	points[8] = points_base[8];
	points[9] = points_base[9];
	points[10] = points_base[10];
	points[11] = points_base[11];
	//fim terceira face

	//quarta face
	points_base[12] = glm::vec3( x_cm-tam, y_cm+tam, z_cm-tam);
    points_base[13] = glm::vec3( x_cm-tam, y_cm+tam, z_cm+tam);
    points_base[14] = glm::vec3( x_cm+tam, y_cm+tam, z_cm+tam);
	points_base[15] = glm::vec3( x_cm+tam, y_cm+tam, z_cm-tam);
	      
	points[12] = points_base[12];
	points[13] = points_base[13];
	points[14] = points_base[14];
	points[15] = points_base[15];
	//fim quarta face

	//quinta face - referencial x
	points_base[16] = glm::vec3( x_cm+tam, y_cm-tam, z_cm-tam);
    points_base[17] = glm::vec3( x_cm+tam, y_cm-tam, z_cm+tam);
    points_base[18] = glm::vec3( x_cm+tam, y_cm+tam, z_cm+tam);
	points_base[19] = glm::vec3( x_cm+tam, y_cm+tam, z_cm-tam);
	      
	points[16] = points_base[16];
	points[17] = points_base[17];
	points[18] = points_base[18];
	points[19] = points_base[19];
	//fim quinta face

	//sexta face
	points_base[20] = glm::vec3( x_cm-tam, y_cm-tam, z_cm-tam);
    points_base[21] = glm::vec3( x_cm-tam, y_cm-tam, z_cm+tam);
    points_base[22] = glm::vec3( x_cm-tam, y_cm+tam, z_cm+tam);
	points_base[23] = glm::vec3( x_cm-tam, y_cm+tam, z_cm-tam);
	      
	points[20] = points_base[20];
	points[21] = points_base[21];
	points[22] = points_base[22];
	points[23] = points_base[23];
	//fim sexta face
//	std::cout << "inicio: " << glm::to_string(points[0]);
	//points = *point_;

}
//---------------------------------------------------------------------
/*!
* \brief Destrutor
*/
cube::~cube()
{

}

//---------------------------------------------------------------------
/*!
* \brief Atualiza a posição do cubo.
*/
void cube::update(int value)
{
	x += value;
	y += value;

	transform();
}

//---------------------------------------------------------------------
/*!
* \brief Função de colisão (Ainda não implementada).
*/
void cube::colision(int x, int y)
{

	

}

//---------------------------------------------------------------------
/*!
* \brief Aplica as transformações no cubo.
\* Utilizada juntamente com a função update.
*/
void cube::transform(void)
{

	//glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
        glm::mat3 Model = glm::mat3(1.0);
        Model[2] = glm::vec3(x, y, 1.0);
	

	//std::cout << "tes: " << glm::to_string(Model[0]) << std::endl;
	//std::cout << "tes: " << glm::to_string(Model[1])<< std::endl;
	//std::cout << "tes: " << glm::to_string(Model[2])<< "\n" << std::endl;
	
        //glm::vec4 Transformed = Model * Position;


	for(int i=0; i < 24; i++)
	{
		points[i] = Model * points_base[i];

	}

}

/*!
* \brief Seleção de qual textura será aplicada à face.
* \* retorna as componentes RGB que irá preencher a face.
* \* Futuramente, ela selecionará a textura a ser aplicada na face.
*/
void color_select(std::string x, float res[3]){
	glEnable(GL_TEXTURE_2D);
	if (x=="ams"){
		glBindTexture(GL_TEXTURE_2D, 1);
		res[0]=0.9;
		res[1]=0.9;
		res[2]=0.2;
	}
	else if (x=="amm"){
		glBindTexture(GL_TEXTURE_2D, 2);
		res[0]=0.9;
		res[1]=0.8;
		res[2]=0.3;
	}
	else if (x=="ami"){
		glBindTexture(GL_TEXTURE_2D, 3);
		res[0]=0.9;
		res[1]=0.7;
		res[2]=0.4;
	}
	else if (x=="vms"){
		glBindTexture(GL_TEXTURE_2D, 4);
		res[0]=1.0;
		res[1]=0.5;
		res[2]=0.5;
	}
	else if (x=="vmm"){
		glBindTexture(GL_TEXTURE_2D, 5);
		res[0]=1.0;
		res[1]=0.4;
		res[2]=0.6;
	}
	else if (x=="vmi"){
		glBindTexture(GL_TEXTURE_2D, 6);
		res[0]=1.0;
		res[1]=0.3;
		res[2]=0.2;
	}
	else if (x=="brs"){
		glBindTexture(GL_TEXTURE_2D, 7);
		res[0]=0.9;
		res[1]=0.9;
		res[2]=0.9;
	}
	else if (x=="brm"){
		glBindTexture(GL_TEXTURE_2D, 8);
		res[0]=0.7;
		res[1]=0.7;
		res[2]=0.7;
	}
	else if (x=="bri"){
		glBindTexture(GL_TEXTURE_2D, 9);
		res[0]=0.5;
		res[1]=0.5;
		res[2]=0.5;
	}
	else if (x=="vds"){
		glBindTexture(GL_TEXTURE_2D, 10);
		res[0]=0.4;
		res[1]=0.8;
		res[2]=0.4;
	}
	else if (x=="vdm"){
		glBindTexture(GL_TEXTURE_2D, 11);
		res[0]=0.4;
		res[1]=0.7;
		res[2]=0.0;
	}
	else if (x=="vdi"){
		glBindTexture(GL_TEXTURE_2D, 12);
		res[0]=0.4;
		res[1]=0.5;
		res[2]=0.2;
	}
	else if (x=="vzo"){
		glBindTexture(GL_TEXTURE_2D, 13);
		res[0]=0.1;
		res[1]=0.1;
		res[2]=1.0;
	}
}

//---------------------------------------------------------------------
/*!
* \brief Desenha o cubo na tela.
\* O centro de massa do objeto resultante está sobre o ponto (0,0,0).
\* A orientação do objeto está sobre o eixo z.
*/
void cube::draw()
{
	float color[3];
	
	glLineWidth(3.0f);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//transform();
	//std::cout << "tes: " << glm::to_string(points[0]);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);  
	glVertex3f(points[0].x,points[0].y,points[0].z);
	glVertex3f(points[1].x,points[1].y,points[1].z);
	glVertex3f(points[2].x,points[2].y,points[2].z);
	glVertex3f(points[3].x,points[3].y,points[3].z);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);  
	glVertex3f(points[4].x,points[4].y,points[4].z);
	glVertex3f(points[5].x,points[5].y,points[5].z);
	glVertex3f(points[6].x,points[6].y,points[6].z);
	glVertex3f(points[7].x,points[7].y,points[7].z);
	glEnd();
	color_select(state[id][3], color);
	glBegin(GL_POLYGON);
	//glColor3f(color[0], color[1], color[2]);
	glTexCoord2f (1.0f,0.0f);
	glVertex3f(points[8].x,points[8].y,points[8].z);
	glTexCoord2f (1.0f,1.0f);
	glVertex3f(points[9].x,points[9].y,points[9].z);
	glTexCoord2f (0.0f,1.0f);
	glVertex3f(points[10].x,points[10].y,points[10].z);
	glTexCoord2f (0.0f,0.0f);
	glVertex3f(points[11].x,points[11].y,points[11].z);
	glEnd();
	glDisable (GL_TEXTURE_2D);
	color_select(state[id][1], color);
	glBegin(GL_POLYGON);
	//glColor3f(color[0], color[1], color[2]);
	glTexCoord2f (1.0f,0.0f);
	glVertex3f(points[12].x,points[12].y,points[12].z);
	glTexCoord2f (1.0f,1.0f);
	glVertex3f(points[13].x,points[13].y,points[13].z);
	glTexCoord2f (0.0f,1.0f);
	glVertex3f(points[14].x,points[14].y,points[14].z);
	glTexCoord2f (0.0f,0.0f);
	glVertex3f(points[15].x,points[15].y,points[15].z);
	glEnd();
	glDisable (GL_TEXTURE_2D);
	color_select(state[id][0],color);
	glBegin(GL_POLYGON); 
	//glColor3f(color[0], color[1], color[2]);
	glTexCoord2f (1.0f,0.0f);
	glVertex3f(points[16].x,points[16].y,points[16].z);
	glTexCoord2f (1.0f,1.0f);
	glVertex3f(points[17].x,points[17].y,points[17].z);
	glTexCoord2f (0.0f,1.0f);
	glVertex3f(points[18].x,points[18].y,points[18].z);
	glTexCoord2f (0.0f,0.0f);
	glVertex3f(points[19].x,points[19].y,points[19].z);
	glEnd();
	glDisable (GL_TEXTURE_2D);
	color_select(state[id][2], color);
	glBegin(GL_POLYGON);
	//glColor3f(color[0], color[1], color[2]);
	glTexCoord2f (1.0f,0.0f);
	glVertex3f(points[20].x,points[20].y,points[20].z);
	glTexCoord2f (1.0f,1.0f);
	glVertex3f(points[21].x,points[21].y,points[21].z);
	glTexCoord2f (0.0f,1.0f);
	glVertex3f(points[22].x,points[22].y,points[22].z);
	glTexCoord2f (0.0f,0.0f);
	glVertex3f(points[23].x,points[23].y,points[23].z);
	glEnd();
	glDisable (GL_TEXTURE_2D);
}
