// Elo Maluco
// application.cpp
// Prof. Giovani Bernardes Vitor
// ECOI24 - 2019

#include <stdlib.h>
#include <stdio.h>
#include "application.hpp"
#include "arcball.h"

double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_cube1 = 0.0;
double rotate_cube4 = 0.0;
double old_mousex = 0.0;
double old_mousey = 0.0;
vec eye(50.0, 50.0, 0.0);
vec up(0.0,0.0,1.0);
const float SPHERE_RADIUS = 0.0f;
int w1 = 0;
int h1 = 0;



///////////////////////////////////////////////////////////////////////
// Application Class
Application::Application(int argc, char **argv, string state[4][4])
{

    for (int i=0; i<4;i++){
        for (int j=0;j<4;j++){
            this->state[i][j] = state[i][j];
        } 
    }
    this->flag = check_win();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ELO MALUCO");
    glEnable(GL_DEPTH_TEST);
    Inicializa();
}

//---------------------------------------------------------------------
Application::~Application()
{
}
//---------------------------------------------------------------------
void Application::Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    xf = 50.0f;
    yf = 50.0f;
    win = 250.0f;
    time = 0;
}

//---------------------------------------------------------------------
//void Application::DisplayFunc()
//{
//	glutDisplayFunc(Application::Desenha);
//}
//---------------------------------------------------------------------

void Application::draw()
{
    glPushMatrix();
	glDisable( GL_DEPTH_TEST );
	glTranslatef( eye.x, eye.y, eye.z );
    arcball_rotate();
	glEnable( GL_DEPTH_TEST );
	glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0,1,0,1,-1,1);
            // setup texture mapping
    glDisable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );
    if (this->flag)
        glBindTexture( GL_TEXTURE_2D, 15);
    else
        glBindTexture( GL_TEXTURE_2D, 14);

    glPushMatrix();
    glBegin( GL_QUADS );
    glTexCoord2f(0.0,0.0); glVertex2f(0.0,0.0);
    glTexCoord2f(1.0,0.0); glVertex2f(1.0,0.0);
    glTexCoord2f(1.0,1.0); glVertex2f(1.0,1.0);
    glTexCoord2f(0.0,1.0); glVertex2f(0.0,1.0);
    glEnd();
    glDisable (GL_TEXTURE_2D);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);

    resize(view_w, view_h);
    //declaração dos cubos
    cube cubo1(0.0, 0.0, 15.0, 10.0, state, 0);
    cube cubo2(0.0, 0.0, 5.0, 10.0, state, 1);
    cube cubo3(0.0, 0.0, -5.0, 10.0, state, 2);
    cube cubo4(0.0, 0.0, -15.0, 10.0, state, 3);
    arcball_rotate();
    //rotaciona cubo1
    glPushMatrix();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_cube1, 0.0, 0.0, 1.0);
    cubo1.draw();
    glPopMatrix();

    //rotaciona cubo2
    //glPushMatrix();
    cubo2.draw();
    //glPopMatrix();

    //rotaciona cubo3
    //glPushMatrix();
    cubo3.draw();
    //glPopMatrix();
    
    //rotaciona cubo4
    glPushMatrix();
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_cube4, 0.0, 0.0, 1.0);
    cubo4.draw();
    glPopMatrix();
    gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, 0, 0, 1);
    glFlush();
    glutSwapBuffers();
}

//---------------------------------------------------------------------

void Application::resize(GLsizei w, GLsizei h)
{
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;

    //Inicializa o sistema de coordenadas
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluOrtho2D (-win, win, -win, win);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLdouble)view_w / view_h, 1, 100);

    double rate = 2.5;
    gluLookAt(eye.x, eye.y, eye.z, 0, 0, 0, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    arcball_setzoom( SPHERE_RADIUS, eye, up);
    glLoadIdentity();
}

//---------------------------------------------------------------------

void Application::KeyboardHandle(unsigned char key, int x, int y)
{
    std::string aux;
    int posx,posy;
    switch (key)
    {
    case 'w':
    case 'W':
        for (int i=0;i<18;i++){
            rotate_cube1 += 5;
            draw();
        }
        rotate_cube1=0;
        draw();
        aux=state[0][3];
        state[0][3]=state[0][2];
        state[0][2]=state[0][1];
        state[0][1]=state[0][0];
        state[0][0]=aux;
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 'Q':
    case 'q':
        for (int i=0;i<18;i++){
            rotate_cube1 -= 5;
            draw();
        }
        rotate_cube1=0;
        draw();
        aux=state[0][0];
        state[0][0]=state[0][1];
        state[0][1]=state[0][2];
        state[0][2]=state[0][3];
        state[0][3]=aux;
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 'S':
    case 's':
            for (int i=0;i<18;i++){
            rotate_cube4 += 5;
            draw();
        }
        rotate_cube4=0;
        draw();
        aux=state[3][3];
        state[3][3]=state[3][2];
        state[3][2]=state[3][1];
        state[3][1]=state[3][0];
        state[3][0]=aux;
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 'A':
    case 'a':
        for (int i=0;i<18;i++){
            rotate_cube4 -= 5;
            draw();
        }
        rotate_cube4=0;
        draw();
        aux=state[3][0];
        state[3][0]=state[3][1];
        state[3][1]=state[3][2];
        state[3][2]=state[3][3];
        state[3][3]=aux;
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 'U':
    case 'u':
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(state[i][j] == "vzo")
                {
                    posx=i;
                    posy=j;
                    i=4;
                    j=4;
                }
            }
        }
        if(posx == 3)
            std::cout<<"\nLimite inferior atingido!\n";
        else
        {
            state[posx][posy] = state[(posx+1)][posy];
            state[(posx+1)][posy] = "vzo";
        }
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 'J':
    case 'j':
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(state[i][j] == "vzo")
                {
                    posx=i;
                    posy=j;
                    i=4;
                    j=4;
                }
            }
        }
        if(posx == 0)
            std::cout<<"\nLimite superior atingido!\n";
        else
        {
            state[posx][posy] = state[(posx-1)][posy];
            state[(posx-1)][posy] = "vzo";
        }
        this->flag = check_win();
        if (this->flag)
            cout << "GANHOU" << endl;
        break;
    case 27: // tecla Esc (encerra o programa)
        exit(0);
        break;
    }
}

void Application::drag_scene(int x, int y)
{
	int invert_y = (view_h - y) - 10;
	arcball_move(x,invert_y);
}

//---------------------------------------------------------------------
void Application::MouseHandle(int x, int y){
    drag_scene(x,y);
}


//---------------------------------------------------------------------
void Application::SpecialKeyHandle(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        //win -= 20;
        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        //gluOrtho2D (-win, win, -win, win);
        insert_object();
    }
    if (key == GLUT_KEY_DOWN)
    {
        //win += 20;
        //glMatrixMode(GL_PROJECTION);
        //glLoadIdentity();
        //gluOrtho2D (-win, win, -win, win);
    }
}
//---------------------------------------------------------------------
void Application::update(int value, void (*func_ptr)(int))
{
    glutPostRedisplay();
    glutTimerFunc(30, func_ptr, time);
}
//---------------------------------------------------------------------
bool Application::insert_object(void)
{
    cube *obj;
    //Objects * node = reinterpret_cast<Objects*>(obj);
    list_.push_back(new cube(0.0,0.0,0.0,15.0, state, 1));
    std::cout << " insert: " << list_.size() << std::endl;

    return true;
}

bool Application::check_win(){
    for (int i=0;i<4;i++){
        if (this->state[0][i] == "vms"){
            if (this->state[1][i] == "vmm"){
                if (this->state[2][i] == "vmm"){
                    if (this->state[3][i] != "vmi")
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
            
        }
        else if (this->state[0][i] == "vds"){
            if (this->state[1][i] == "vdm"){
                if (this->state[2][i] == "vdm"){
                    if (this->state[3][i] != "vdi")
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
            
        }
        else if (this->state[0][i] == "ams"){
            if (this->state[1][i] == "amm"){
                if (this->state[2][i] == "amm"){
                    if (this->state[3][i] != "ami")
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
            
        }
        else if (this->state[0][i] == "brs"){
            if (this->state[1][i] == "brm"){
                if (this->state[2][i] == "bri"){
                    if (this->state[3][i] != "vzo")
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
        }

        else if (this->state[0][i] == "vzo"){
            if (this->state[1][i] == "brs"){
                if (this->state[2][i] == "brm"){
                    if (this->state[3][i] != "bri")
                        return false;
                }
                else
                    return false;
            }
            else
                return false;
            
        }
        else
            return false;
    }
    return true;
}