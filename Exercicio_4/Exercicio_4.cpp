#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

void Inicializa (void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Triangulo(void);
void Teclado (unsigned char key, int x, int y);
void TeclasEspeciais (int key, int x, int y);
void GerenciaMouse (int button,int state, int x, int y);

bool gira;
GLfloat angulo, tx, ty, win, d, tam;


// Programa Principal
int main(int argc, char** argv) { 
	glutInit(&argc, argv); // Inicializa a GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Modo de operação da GLUT
	glutInitWindowPosition(350, 100); //posiciona a janela na tela. A referência é o canto superior esquerdo
	glutInitWindowSize(640,480); // tamanho em pixels da janela
	glutCreateWindow("Exercicio 4"); // Cria a janela passando como argumento o título da mesma
	Inicializa();
	glutReshapeFunc(AlteraTamanhoJanela);
	glutDisplayFunc(Desenha); // Registra função de redesenho
	glutKeyboardFunc(Teclado); // Registra função de teclado
	glutSpecialFunc(TeclasEspeciais); // Registra função de teclas especiais
	glutMouseFunc(GerenciaMouse);
	glutIdleFunc(Desenha);
	glutMainLoop(); // Inicia o processamento e aguarda interações do usuário
	return 0;
}

// Inicializa parâmetros de rendering
void Inicializa (void){   
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	tx = 0;
	ty = 0;
	angulo = 0;
	win = 1;
	d = 0.25;
	tam = 1.0;
	gira = false;
	glutIdleFunc(Desenha);
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

// Função de redesenho da janela de visualização
void Desenha(void){
//	glClearColor(1,1,1,0);  // branco
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpe a tela e o buffer
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);            // Indique que os dois lados de qualquer superfície devem ser representados.    
	glLoadIdentity();                                           // Resete a corrente Modelview Matrix
	
	gluOrtho2D (-win, win, -win, win);		//Controle do mouse
	glutPostRedisplay();
	
	//implementa desenhos dos objetos
	if (gira){
		angulo += 0.1;
	};
	
    glRotatef(angulo, 0, 0, 1); //controle do G e R
	
    glScalef(tam, tam, tam); // Controle do A e D
    Triangulo();
    
	glFlush();
	glutSwapBuffers();                                          // Troque os buffers.
}

// Função responsável pelo Triangulo
void Triangulo(void){
    glBegin(GL_TRIANGLES); //Controle com as setas do teclado
	    glColor3f(1,0,0); //vermelho
	    glVertex3f(tx-d,ty-d,0); //inf. esquerdo 
	    glColor3f(0,1,0); //verde
	    glVertex3f(tx, ty+d,0); //superior
	    glColor3f(0,0,1); //azul
	    glVertex3f(tx+d,ty-d,0); //inf. direito
    glEnd();
}

//Função para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
	if(key == 27) // Esc = sair da aplicação
        exit(0);
    else if(key == 65 || key == 97){ // A - aumentar a figura
    	tam += 0.1;
    }
    else if(key == 68 || key == 100){ // D - diminuir a figura
    	tam -= 0.1;
    }
    else if(key == 71 || key == 103){ // G - Colocar a figura para girar
        gira = !gira;        
    }
    else if(key == 82 || key == 114){ // R - rotacionar a figura manualmente
        angulo += 1.0;
    }
    else if(key == 79 || key == 111){ // O - restaurar imagem original
        Inicializa();
    }
}

void TeclasEspeciais (int key, int x, int y) {
	
	switch (key)
	{
		case GLUT_KEY_UP:{ // Seta para cima = mover figura para cima
			ty += 0.1;
			break;
		}
		case GLUT_KEY_DOWN:{ // Seta para baixo = mover figura para bsixo
			ty -= 0.1;
			break;
		}
		case GLUT_KEY_LEFT:{ // Seta para esquerda = mover figura para esquerda
			tx -= 0.1;
			break;
		}
		case GLUT_KEY_RIGHT:{ // Seta para direita = mover figura para direita
			tx += 0.1;
			break;
		}
	}
}

void GerenciaMouse (int button,int state, int x, int y) {
	
	switch (button)
	{
		case GLUT_LEFT_BUTTON:{ // Botao esquerdo do mouse = zoom out
			if (state == GLUT_DOWN){
				win -= 0.1;	
			}
			break;
		}
		case GLUT_RIGHT_BUTTON:{ // Botao direito do mouse = zoom in
			if (state == GLUT_DOWN){
				win += 0.1;	
			}
			break;
		}
	}
}
