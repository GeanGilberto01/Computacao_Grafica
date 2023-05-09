#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

bool rotaciona = false;
bool escala = false;
bool outroponto = false;

// Fun��o respons�vel pela Terra
void Triangulo(void){
    glBegin(GL_TRIANGLES);
	    glColor3f(1,0,0); //vermelho
	    glVertex3f(-0.5,-0.5,0);
	    glColor3f(0,1,0); //verde
	    glVertex3f( 0.0, 0.5,0);
	    glColor3f(0,0,1); //azul
	    glVertex3f( 0.5,-0.5,0);
    glEnd();
}

// Fun��o de redesenho da janela de visualiza��o
void Desenha(void){
	glClearColor(1,1,1,0);  // branco
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpe a tela e o buffer
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);            // Indique que os dois lados de qualquer superf�cie devem ser representados.    
	glLoadIdentity();                                           // Resete a corrente Modelview Matrix
	
	//implementa desenhos dos objetos
	if(rotaciona){
        glRotatef(180, 0, 0, 1);
    }
    
    if(escala){
        glScalef(1.5, 1.5, 1.0);
    }
    
    if(outroponto){
        glTranslatef(-0.4,0.4,0.0);
    }
    
    Triangulo();
	glFlush(); 
	
	glutSwapBuffers();                                          // Troque os buffers.
}

//Fun��o para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
	if(key == 27) // ESC
        exit(0);
    else if(key == 82 || key == 114) // R - Rotaciona 180�
        rotaciona = !rotaciona;
    else if(key == 83 || key == 115) // S - Aumenta a escala
        escala = !escala;
    else if(key == 84 || key == 116) // T - Move para outro ponto da tela
        outroponto = !outroponto;
}

// Inicializa par�metros de rendering
void Inicializa (void){   
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Evita a divisao por zero
	if(h == 0) h = 1;
	
	// Especifica as dimens�es da Viewport
	glViewport(0, 0, w, h);
	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Estabelece a janela de sele��o (left, right, bottom, top)
	if (w <= h) 
		gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
	else
		gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}

// Programa Principal
int main(int argc, char** argv) { 
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Modo de opera��o da GLUT
	glutInitWindowPosition(350, 100); //posiciona a janela na tela. A refer�ncia � o canto superior esquerdo
	glutInitWindowSize(640,480); // tamanho em pixels da janela
	glutCreateWindow("Exercicio 3"); // Cria a janela passando como argumento o t�tulo da mesma
	glutDisplayFunc(Desenha); // Registra fun��o de redesenho
	glutKeyboardFunc(Teclado); // Registra fun��o de teclado
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutIdleFunc(Desenha);
	glutMainLoop(); // Inicia o processamento e aguarda intera��es do usu�rio
	return 0;
}
