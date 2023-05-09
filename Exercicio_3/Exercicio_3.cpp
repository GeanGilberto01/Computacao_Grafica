#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

bool rotaciona = false;
bool escala = false;
bool outroponto = false;

// Função responsável pela Terra
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

// Função de redesenho da janela de visualização
void Desenha(void){
	glClearColor(1,1,1,0);  // branco
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpe a tela e o buffer
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);            // Indique que os dois lados de qualquer superfície devem ser representados.    
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

//Função para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
	if(key == 27) // ESC
        exit(0);
    else if(key == 82 || key == 114) // R - Rotaciona 180º
        rotaciona = !rotaciona;
    else if(key == 83 || key == 115) // S - Aumenta a escala
        escala = !escala;
    else if(key == 84 || key == 116) // T - Move para outro ponto da tela
        outroponto = !outroponto;
}

// Inicializa parâmetros de rendering
void Inicializa (void){   
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	// Evita a divisao por zero
	if(h == 0) h = 1;
	
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h) 
		gluOrtho2D (0.0f, 250.0f, 0.0f, 250.0f*h/w);
	else
		gluOrtho2D (0.0f, 250.0f*w/h, 0.0f, 250.0f);
}

// Programa Principal
int main(int argc, char** argv) { 
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Modo de operação da GLUT
	glutInitWindowPosition(350, 100); //posiciona a janela na tela. A referência é o canto superior esquerdo
	glutInitWindowSize(640,480); // tamanho em pixels da janela
	glutCreateWindow("Exercicio 3"); // Cria a janela passando como argumento o título da mesma
	glutDisplayFunc(Desenha); // Registra função de redesenho
	glutKeyboardFunc(Teclado); // Registra função de teclado
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutIdleFunc(Desenha);
	glutMainLoop(); // Inicia o processamento e aguarda interações do usuário
	return 0;
}
