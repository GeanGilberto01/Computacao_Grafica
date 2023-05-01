// Quadrado.c
// Um programa OpenGL simples que desenha um 
// quadrado em  uma janela GLUT.

#include <windows.h>
#include <gl/glut.h>

// Função callback chamada para fazer o desenho
void Desenha(void){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Limpa a janela de visualização
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Especifica que a cor corrente é vermelha
	//         R     G     B
	glColor3f(1.0f, 0.0f, 0.0f);
	
	// Desenha um quadrado na cor corrente
	glBegin(GL_QUADS);
		glVertex2i(100,150);
		glVertex2i(100,100);
		
		// Especifica que a cor corrente é azul
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(150,100);
		glVertex2i(150,150);               
	glEnd();
	
	// Executa os comandos OpenGL
	glFlush();
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
	glutInit(&argc, argv);                 // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400,350);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Quadrado");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutMainLoop();
}
