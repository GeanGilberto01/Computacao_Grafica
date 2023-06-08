#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#define QUAD 1
#define TRIAN 2
#define LOSAN  3

using namespace std;

void Inicializa(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Quadrado(void);
void Triangulo(void);
void Losango(void);
void DesenhaTexto(char *string, char *nome);
void GerenciaMouse(int button, int state, int x, int y);
void MousePressionado(int x, int y);
void MouseSolto(int x, int y);
void MenuCor(int colors);
void MenuFigura(int op);
void MenuOutros(int op);
void NomeObjeto();
void MenuPrincipal(int op);
void Menu();

// Vari�veis Globais
bool exibirNomeFigura;
char texto[50], nome[50];
GLfloat win, r, g, b, angulo;
GLint figura;

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                // Inicializa a GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          // Modo de opera��o da GLUT
    glutInitWindowPosition(350, 100);                     // posiciona a janela na tela. A refer�ncia � o canto superior esquerdo
    glutInitWindowSize(640, 480);                         // tamanho em pixels da janela
    glutCreateWindow("Exercicio 8");                      // Cria a janela passando como argumento o t�tulo da mesma
    Inicializa();
    glutReshapeFunc(AlteraTamanhoJanela);
    glutDisplayFunc(Desenha);                              // Registra fun��o de redesenho
    glutMouseFunc(GerenciaMouse);                          // Gerencia Click do Mouse
    glutMotionFunc(MousePressionado);                         // Verifica a posicao do mouse quando o bot�o esquerdo est� pressionado
    glutPassiveMotionFunc(MouseSolto);             // Verifica a posicao do mouse quando nenhum bot�o est� pressionado
    glutMainLoop();                                        // Inicia o processamento e aguarda intera��es do usu�rio
    return 0;
}

// Inicializa par�metros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualiza��o como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    exibirNomeFigura = false;
	win=1.0f;
    figura = QUAD;
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    angulo = 0.0f;
    Menu();
    strcpy(texto, "Posi��o Atual: (0,0)");
}

// Fun��o callback chamada quando o tamanho da janela � alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0)
        h = 1;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de sele��o (left, right, bottom, top)
    gluOrtho2D(-win, win, -win, win);
}

// Fun��o de redesenho da janela de visualiza��o
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	
    glPushMatrix();
    glColor3f(r,g,b);
    glRotatef(angulo, 0, 0, 1);
     
	// Desenha figura
	switch (figura) {
	    case QUAD:  
			Quadrado();
	        break;
	    case TRIAN: 
			Triangulo();
	        break;
	    case LOSAN: 
			Losango();
	        break;
	}
    glPopMatrix();
	
	// Exibe a posi��o do mouse
	glColor3f(1.0f,1.0f,1.0f);
    glRotatef(0, 0, 0, 1);
	DesenhaTexto(texto, nome);
	
    glFlush();
    glutSwapBuffers();
}

// Desenha um quadrado
void Quadrado(void)
{
    glBegin(GL_QUADS);        // define o in�cio de um pol�gono com quatro v�rtices
    	glVertex2f(-0.30f, -0.30f);   // define o primeiro v�rtice
    	glVertex2f( 0.30f, -0.30f);   // define o segundo v�rtice
    	glVertex2f( 0.30f,  0.30f);   // define o terceiro v�rtice
    	glVertex2f(-0.30f,  0.30f);   // define o quarto v�rtice
    glEnd();                  // define o fim do pol�gono
}

// Desenha um tri�ngulo
void Triangulo(void)
{
     glBegin(GL_TRIANGLES);
        glVertex2f(-0.30f, -0.30f);
        glVertex2f( 0.00f,  0.30f);
        glVertex2f( 0.30f, -0.30f);
     glEnd();
}

// Desenha um losango
void Losango(void)
{
     glBegin(GL_POLYGON);
       glVertex2f(-0.30f,  0.00f);
       glVertex2f( 0.00f,  0.30f);
       glVertex2f( 0.30f,  0.00f);
       glVertex2f( 0.00f, -0.30f);
     glEnd();
}

// Desnha texto
void DesenhaTexto(char *string, char *nome)
{
    glPushMatrix();
    // Posi��o do texto (Sup, Esq)
    glRasterPos2f(-win,win-(win*0.08));
    // Exibe caracter
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*string++);
    glPopMatrix();
	
	if (exibirNomeFigura)
	{
		glPushMatrix();
	    // Posi��o do texto (Sup, Esq)
	    glRasterPos2f(-win,win-(win*0.2));
	    // Exibe caracter
	    while(*nome)
	        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,*nome++);
	    glPopMatrix();
	}
}

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // Botao direito do mouse pressionado
    {
    	sprintf(texto, "Mouse Pressionado (%d,%d)", x, y);
    	glutPostRedisplay();
    }    
}

void MousePressionado(int x, int y)
{
    sprintf(texto, "Mouse Pressionado (%d,%d)", x, y);
    glutPostRedisplay();
}

void MouseSolto(int x, int y)
{
    sprintf(texto, "Posicao Atual: (%d, %d)\n", x, y);
    glutPostRedisplay();
}
   
// Define as cores
void MenuCor(int colors)
{
	switch(colors) {
        case 0:
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            break;
        case 1:
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            break;
        case 2:
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            break;
    }
    glutPostRedisplay();
}

// Define a figura que ser� redesenhada
void MenuFigura(int op)
{
    switch(op) {
        case 0:
            figura = QUAD;
            break;
        case 1:
            figura = TRIAN;
            break;
        case 2:
            figura = LOSAN;
            break;
    }
    NomeObjeto();
    glutPostRedisplay();
}

// Define a op��o outros
void MenuOutros(int op)
{
    switch(op) {
        case 0:
        	exibirNomeFigura = !exibirNomeFigura;
        	NomeObjeto();
    		break;
        case 1:
        	angulo += 45;
            break;
    }
    glutPostRedisplay();
}    

// Gerenciamento do nome do objeto
void NomeObjeto()
{
	switch(figura) {
        case 1:
		    sprintf(nome, "Quadrado");
		    glutPostRedisplay();
            break;
        case 2:
		    sprintf(nome, "Tri�ngulo");
		    glutPostRedisplay();
            break;
        case 3:
		    sprintf(nome, "Losangolo");
		    glutPostRedisplay();
            break;
    }
}
    
// Gerenciamento do menu principal
void MenuPrincipal(int op)
{
    glutPostRedisplay();
}

// Fun��o para criar o menu
void Menu()
{
    int menu,submenu1,submenu2,submenu3;

    submenu1 = glutCreateMenu(MenuFigura);
    glutAddMenuEntry("Quadrado",0);
    glutAddMenuEntry("Tri�ngulo",1);
    glutAddMenuEntry("Losango",2);

    submenu2 = glutCreateMenu(MenuCor);
    glutAddMenuEntry("Vermelho",0);
    glutAddMenuEntry("Verde",1);
    glutAddMenuEntry("Azul",2);

    submenu3 = glutCreateMenu(MenuOutros);
    glutAddMenuEntry("Exibir Nome da Figura",0);
    glutAddMenuEntry("Rotacionar",1);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Figuras",submenu1);
    glutAddSubMenu("Cor",submenu2);
    glutAddSubMenu("Outros",submenu3);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

