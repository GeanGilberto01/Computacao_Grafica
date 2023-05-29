#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

void Inicializa (void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Teclado (unsigned char key, int x, int y);

// Vari�veis para controlar o tamanho e a posi��o dos tri�ngulos
float tamanhoTrianguloEsquerda = 1.0f;
float posicaoTrianguloDireita = 0.0f;
float angulo = 0.0f;

// Programa Principal
int main(int argc, char** argv) { 
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Modo de opera��o da GLUT
	glutInitWindowPosition(350, 100); //posiciona a janela na tela. A refer�ncia � o canto superior esquerdo
	glutInitWindowSize(640,480); // tamanho em pixels da janela
	glutCreateWindow("Exercicio 6"); // Cria a janela passando como argumento o t�tulo da mesma
	Inicializa();
	glutReshapeFunc(AlteraTamanhoJanela);
	glutKeyboardFunc(Teclado); // Registra fun��o de teclado
	glutDisplayFunc(Desenha); // Registra fun��o de redesenho
	glutMainLoop(); // Inicia o processamento e aguarda intera��es do usu�rio
	return 0;
}

// Inicializa par�metros de rendering
void Inicializa (void){   
	// Define a cor de fundo da janela de visualiza��o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glutIdleFunc(Desenha);
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
	glOrtho(-2.0f, 2.0f, -2.0f, 2.0f, -1.0f, 1.0f);
}

// Fun��o de redesenho da janela de visualiza��o
void Desenha(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // Desenha o tri�ngulo da esquerda
    glPushMatrix();
    glScalef(tamanhoTrianguloEsquerda, tamanhoTrianguloEsquerda, tamanhoTrianguloEsquerda);
    glColor3f(1.0f, 0.0f, 0.0f); // Cor vermelha para o tri�ngulo da esquerda
    glBegin(GL_TRIANGLES);
	    glVertex3f(-1.00,-0.25,0);
	    glVertex3f(-0.75, 0.25,0);
	    glVertex3f(-0.50,-0.25,0);
    glEnd();
    glPopMatrix();

	
    // Desenha o tri�ngulo do meio
    glPushMatrix();
    glRotatef(angulo, 0, 0, 1); //controle do G e R
    glColor3f(0.0f, 0.0f, 1.0f); // Cor azul para o tri�ngulo do meio
    glBegin(GL_TRIANGLES);
	    glVertex3f(-0.25, 0.25,0);
	    glVertex3f( 0.00, 0.75,0);
	    glVertex3f( 0.25, 0.25,0);
    glEnd();
    glPopMatrix();

    // Desenha o tri�ngulo da direita
    glPushMatrix();
    glTranslatef(posicaoTrianguloDireita, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f); // Cor verde para o tri�ngulo da direita
    glBegin(GL_TRIANGLES);
	    glVertex3f(1.00,-0.25,0);
	    glVertex3f(0.75, 0.25,0);
	    glVertex3f(0.50,-0.25,0);
    glEnd();
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

//Fun��o para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
	if(key == 27) // Esc = sair da aplica��o
        exit(0);
    else if(key == 65 || key == 97){ // A - aumentar o tri�ngulo da esquerda
    	tamanhoTrianguloEsquerda *= 1.5f;
    }
    else if(key == 66 || key == 98){ // B -  Mover o tri�ngulo da direita para esquerda
    	posicaoTrianguloDireita -= 0.1f;
    }
    else if(key == 67 || key == 99){ // C - Mover o tri�ngulo da direita para direita
    	posicaoTrianguloDireita += 0.1f;;
    }
    else if(key == 68 || key == 100){ // D - diminuir o tri�ngulo da esquerda
    	tamanhoTrianguloEsquerda *= 0.5f;
    }
    else if(key == 71 || key == 103){ // G - rotacionar para esquerda o tri�ngulo do meio
        angulo -= 1.0;        
    }
    else if(key == 82 || key == 114){ // R - rotacionar para direita o tri�ngulo do meio
        angulo += 1.0;
    }
    else if(key == 79 || key == 111){ // O - restaurar imagem original
        tamanhoTrianguloEsquerda = 1.0f;
        posicaoTrianguloDireita = 0.0f;
    }
	glutPostRedisplay();
}
