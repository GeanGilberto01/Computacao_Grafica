#include <gl/glut.h>
#include <math.h>
#include <iostream>
#include <time.h>

using namespace std;

void Inicializa (void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Triangulo(void);
void Teclado (unsigned char key, int x, int y);
void Timer(int value);

GLfloat x, y, pX, pY, l, a;
GLsizei d;

// Programa Principal
int main(int argc, char** argv) { 
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Modo de operação da GLUT
	glutInitWindowPosition(350, 100); //posiciona a janela na tela. A referência é o canto superior esquerdo
	glutInitWindowSize(640,480); // tamanho em pixels da janela
	glutCreateWindow("Exercicio 5"); // Cria a janela passando como argumento o título da mesma
	Inicializa();
	glutReshapeFunc(AlteraTamanhoJanela);
	glutDisplayFunc(Desenha); // Registra função de redesenho
	glutKeyboardFunc(Teclado); // Registra função de teclado
	glutIdleFunc(Desenha);
	glutTimerFunc(0, Timer, 1);
	glutMainLoop(); // Inicia o processamento e aguarda interações do usuário
	return 0;
}

// Inicializa parâmetros de rendering
void Inicializa (void){   
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	x = 100.0;
	y = 150.0;
	d = 50;
	pX = 1.0;
	pY = 1.0;
	glutIdleFunc(Desenha);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h){
	
	l = w;
	a = h;
	
	// Evita a divisao por zero
	if(h == 0) 
		h = 1;
	
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Estabelece a janela de seleção (left, right, bottom, top)
	gluOrtho2D (0.0f, l, 0.0f, a);
		
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Função de redesenho da janela de visualização
void Desenha(void){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpe a tela e o buffer
    glMatrixMode(GL_MODELVIEW);              
	glLoadIdentity();                                           // Resete a corrente Modelview Matrix
	
	//implementa desenhos dos objetos
    Triangulo();
    
	glFlush();
	glutSwapBuffers();                                          // Troque os buffers.
}

// Função responsável pelo Triangulo
void Triangulo(void){
    glBegin(GL_TRIANGLES); //Controle com as setas do teclado
	    glColor3f(1,0,0); //vermelho
	    glVertex2i(x,y); //inf. esquerdo 
	    glColor3f(0,1,0); //verde
	    glVertex2i(x+d, y+d); //superior
	    glColor3f(0,0,1); //azul
	    glVertex2i(x+(2*d),y); //inf. direito
    glEnd();
}

//Função para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
	if(key == 27) // Esc = sair da aplicação
        exit(0);
}

// Função timer
void Timer(int value)
{
    // Atualiza as coordenadas do triângulo
	x += pX;
	y += pY;
	
    // Direção na borda esquerda ou direita
    if(x > l-(2*d) || x < 0)
        pX = -pX;

    // Direção na borda superior ou inferior
    if(y > a-d || y < 0)
        pY = -pY;
          
		glutPostRedisplay(); //Redesenha
	glutTimerFunc(5,Timer, 1); //Aguarda 33 ms e volta
}
