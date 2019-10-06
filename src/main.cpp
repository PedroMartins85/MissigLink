// Elo Maluco
// main.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2019

/*! \mainpage Projeto de Computação Gráfica
 *
 * \section intro_sec Introdução
 *
 * Esta documentação apresenta as diretivas básicas do desenvolvimento do projeto
 * Elo Maluco (Missing Ring) proposto na disciplina ECOi24.
 * O projeto se encontra em desenvolvimento e até a etapa atual, foram desenvolvidos os seguintes tópicos:
 \* Modelagem dos elementos do jogo de forma orientada a objetos;
 \* Leitura do arquivo .xml que apresenta a configuração do jogo.
 * 
 */

#include <iostream>
#include <thread>
#include <string>

#include "wraps.hpp"
#include "application.hpp"
#include "tinyxml2.h"
#include "arcball.h"
#include "tga.h"

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult)           \
     if (a_eResult != XML_SUCCESS)          \
     {                                      \
          printf("Error: %i\n", a_eResult); \
          return a_eResult;                 \
     }
#endif

using namespace tinyxml2;
using namespace std;

// Programa Principal

void glInit(void)
{
     if (!loadTGA("texturas/ams.tga", 1))
          printf("ams.tga not found!\n");
     if (!loadTGA("texturas/amm.tga", 2))
          printf("amm.tga not found!\n");
     if (!loadTGA("texturas/ami.tga", 3))
          printf("ami.tga not found!\n");
     if (!loadTGA("texturas/vms.tga", 4))
          printf("vms.tga not found!\n");
     if (!loadTGA("texturas/vmm.tga", 5))
          printf("vmm.tga not found!\n");
     if (!loadTGA("texturas/vmi.tga", 6))
          printf("vmi.tga not found!\n");
     if (!loadTGA("texturas/brs.tga", 7))
          printf("brs.tga not found!\n");
     if (!loadTGA("texturas/brm.tga", 8))
          printf("brm.tga not found!\n");
     if (!loadTGA("texturas/bri.tga", 9))
          printf("bri.tga not found!\n");
     if (!loadTGA("texturas/vrs.tga", 10))
          printf("vrs.tga not found!\n");
     if (!loadTGA("texturas/vrm.tga", 11))
          printf("vrm.tga not found!\n");
     if (!loadTGA("texturas/vri.tga", 12))
          printf("vri.tga not found!\n");
     if (!loadTGA("texturas/vzo.tga", 13))
          printf("vzo.tga not found!\n");
     if (!loadTGA("texturas/background.tga", 14))
          printf("background.tga not found!\n");
     if (!loadTGA("texturas/background1.tga", 15))
          printf("background1.tga not found!\n");
     if (!loadTGA("texturas/background2.tga", 16))
          printf("background2.tga not found!\n");
}

/*!
* \brief Execução principal da aplicação de jogo Elo Maluco (Missing Ring).
*/
int main(int argc, char **argv)
{
     string estado[4][4];
     string win[4][4];
     XMLDocument doc;
     XMLError eresult = doc.LoadFile("./data/EloMaluco_estadoAtual_exemplo.xml");
     XMLElement *estadoAtual = doc.FirstChildElement("EloMaluco")->FirstChildElement("EstadoAtual");
     XMLElement *linhas = estadoAtual->FirstChildElement("row");
     XMLElement *colunas = linhas->FirstChildElement("col");

     for (int i = 0; i < 4; i++)
     {
          for (int j = 0; j < 4; j++)
          {
               estado[i][j] = colunas->GetText();
               if (j < 3)
                    colunas = colunas->NextSiblingElement();
          }
          if (i < 3)
          {
               linhas = linhas->NextSiblingElement();
               colunas = linhas->FirstChildElement("col");
          }
     }

     eresult = doc.LoadFile("./data/EloMaluco_estadoVencedor.xml");
     estadoAtual = doc.FirstChildElement("EloMaluco")->FirstChildElement("EstadoAtual");
     linhas = estadoAtual->FirstChildElement("row");
     colunas = linhas->FirstChildElement("col");

     for (int i = 0; i < 4; i++)
     {
          for (int j = 0; j < 4; j++)
          {
               win[i][j] = colunas->GetText();
               if (j < 3)
                    colunas = colunas->NextSiblingElement();
          }
          if (i < 3)
          {
               linhas = linhas->NextSiblingElement();
               colunas = linhas->FirstChildElement("col");
          }
     }

     int time = 0;

     Application app(argc, argv, estado, win);
     ptr_ = &app;

     arcball_reset();
     glutDisplayFunc(draw);
     glutReshapeFunc(resize);
     glutKeyboardFunc(KeyboardHandle);
     glutMotionFunc(MouseHandle);
     //glutSpecialFunc(SpecialKeyHandle);
     glutTimerFunc(30, update, time);

     //carregando texturas
     glInit();

     glutMainLoop();

     return 0;
}
