// Elo Maluco
// application.hpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2019

#include <iostream>
#include <vector>
#include <list>

#include <GL/glut.h>

#include "tinyxml2.h"
#include "Objects.hpp"
#include "polygon.hpp"

#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

using namespace std;

/////////////////////////////////////////////////////////////

/*!
* \brief Classe Application, contém as primitivas que fazem a execução da aplicação.
\* Esta classe foi construida com o intuito de lidar com todas as funções que realizam alteração na tela.

*/
class Application
{
public:
	/*!
	* \brief Construtor da classe Application
	 */
	Application(int argc, char** argv, string state[4][4], string state_win[4][4]);
	/*!
	* \brief Destrutor da classe Application
	 */
	~Application(void);
	/*!
	* \brief Função para desenhar a aplicação na tela.
	\* Esta função gera os quatro cubos apresentados ao executar a aplicação.
	 */
	void draw();
	/*!
	* \brief Trabalha com as transformações relacionadas ao tamanho da viewport e da janela.
	*/
	void resize(GLsizei w, GLsizei h);
	/*!
	* \brief Função para lidar com as entradas vindas do teclado.
	\* (Q - W) Rotaciona o cubo superior para a direita ou esquerda.
	\* (A - S) Para rotacionar o segundo cubo.
	\* (U - J) Para mover uma face para cima ou para baixo.
	 */
	void KeyboardHandle(unsigned char key, int x, int y);
	/*!
	* \brief Função para reconhecimento do mouse. 
	\* Utiliza-se o recurso drag and drop para girar o objeto.
	\* [BUG] Ao movimentar o objeto pela primeira vez, uma transformação ocorre rotacionando a câmera.
	*/
	void drag_scene(int x, int y);
	/*!
	* \brief Função para lidar com as entradas vindas do mouse.
	\* A função de movimentação com o mouse será implementada para fazer a rotação dos quatro cubos.
	 */
	void MouseHandle(int x, int y);
	/*!
	* \brief Função para lidar com as entradas especiais.
	 */
	void SpecialKeyHandle(int key, int x, int y);
	/*!
	* \brief Função para atualizar os objetos dispostos na tela.
	\* Durante cada execução do loop do jogo, é feita uma atualização na tela com as novas posições dos objetos.
	 */
	void update(int value, void (*func_ptr)(int));

	bool check_win();

private:

	int time;
	bool flag = false;

	GLfloat xf;
	GLfloat yf;
	GLfloat win;
	GLint view_w;
	GLint view_h;
	string state[4][4];
	string state_win[4][4];

	list<Objects*> list_;

private:
	void Inicializa (void);
	bool insert_object(void);
	
	
};

#endif
