#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

void Inicializa(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Teclado (unsigned char key, int x, int y);
void MenuCor(int colors);
void MenuFigura(int op);
void PosicionaObservador(void);
void EspecificaParametrosVisualizacao(void);

// Variáveis Globais
bool gira; // Controle de rotação do objeto
GLfloat angulo; // angulo de rotacão do objeto
GLfloat escala; // escala de tamanho do objeto
GLfloat r, g, b;  // variaveis de controle de cor do objeto
GLint figura; // Controle de figura que sera desenhada
GLdouble size; // raio de uma esfera que envolta o objeto (bule, cubo)
GLdouble radius;; // raio (esfera, cone)
GLint slices; // linhas longitudinais (esfera, cone)
GLint stacks; // linhas latitudinais (esfera, cone)
GLdouble height; // altura cone
GLint rings; // número de seções para formar o torus
GLint nsides; // número de subdivisões de cada seção (torus)
GLdouble innerRadius; // raio interno (torus)
GLdouble outerRadius; // raio externo (torus)
GLdouble eyex, eyey, eyez; // Controle do Observador
GLfloat angle, fAspect; // Cotrole da Perspectiva

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                          				// Inicializa a GLUT
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);    	// Modo de operação da GLUT
    glutInitWindowPosition(350, 100);               				// posiciona a janela na tela. A referência é o canto superior esquerdo
    glutInitWindowSize(640, 480);                   				// tamanho em pixels da janela
    glutCreateWindow("Exercicio 9");                				// Cria a janela passando como argumento o título da mesma
    Inicializa();													// Inicializa as variaveis				
    glutReshapeFunc(AlteraTamanhoJanela);							// Configura janela de exibição
    glutDisplayFunc(Desenha);                       				// Registra função de redesenho
	glutKeyboardFunc(Teclado); 										// Registra função de teclado
    glEnable(GL_DEPTH_TEST);										// Habilita o teste de profundidade
    glutMainLoop();                                 				// Inicia o processamento e aguarda interações do usuário
    return 0;
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Fundo Preto
    
    //***********************************************************//
    //					CORES DO OBJETO							 //
    //***********************************************************//
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;
    //***********************************************************//
    
    //***********************************************************//
    //					ROTAÇÃO DO OBJETO						 //
    //***********************************************************//
    angulo = 0.0f;
    gira = false;
    //***********************************************************//
    
    //***********************************************************//
    //					ESCALA DO OBJETO						 //
    //***********************************************************//
    escala = 1.0f;
    //***********************************************************//
    
    //***********************************************************//
    //					RAIO DO OBJETO						     //
    //***********************************************************//
	size = 0.5f;
	radius = 0.5f;
    //***********************************************************//
    
    //***********************************************************//
    //			LINHAS DO OBJETO (CONE, ESFERA)				     //
    //***********************************************************//
	slices = 20;
	stacks = 20;
    //***********************************************************//
    
    //***********************************************************//
    //				VARIAVEIS DO OBJETO TORUS				     //
    //***********************************************************//
    rings = 20;
	nsides = 20;
	innerRadius = 0.1f;
	outerRadius = 0.3f;
    //***********************************************************//
    
    //***********************************************************//
    //					ALTURA DO OBJETO CONE				     //
    //***********************************************************//
	height = 1.0f;	
    //***********************************************************//
    
    //***********************************************************//
    //					CONTROLE DO OBSERVADOR				     //
    //***********************************************************//
    eyex = 0.0f;
	eyey = 0.0f;
	eyez = -2.5f;
    //***********************************************************//	
    
    //***********************************************************//
    //					CONTROLE DA PESPECTIVA				     //
    //***********************************************************//    
    angle = 45.0f;
    //***********************************************************//	
    
    //***********************************************************//
    //				FIGURA DO OBJETO INICIALIZAÇÃO			     //
    //***********************************************************//
    figura = 0;
	MenuFigura(figura);
    //***********************************************************//
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Evita a divisao por zero
    if (h == 0)
        h = 1;

    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    fAspect = (GLfloat)w/(GLfloat)h;
    EspecificaParametrosVisualizacao();
}

// Função de redesenho da janela de visualização
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    EspecificaParametrosVisualizacao();
    
	// Aplica transformações de escala e rotação
    glPushMatrix();
    glScalef(escala, escala, escala);
    
    if(gira){
        angulo += 0.5;
    }    
    glRotatef(angulo, 0.0f, 1.0f, 0.0f);
    
    // Define a cor do objeto atual
    glColor3f(r,g,b);
     
	// Desenha o objeto atual
	MenuFigura(figura);
	
    glPopMatrix();
	
	glFlush();
    glutSwapBuffers();
    
}

//Função para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	
    switch (key) {
        case 27: // Esc = sair da aplicação
            exit(0);
            break;
        case '0': // 0 = Diminui a escala da figura
            escala *= 0.5f;
            break;
        case '1': // 1 = mostrar o bule
            figura = 0;
            break;
        case '2': // 2 = mostrar o cubo
            figura = 1;
            break;
        case '3': // 3 = mostrar a esfera
            figura = 2;
            break;
        case '4': // 4 = mostrar o cone
            figura = 3;
            break;
        case '5': // 5 = mostrar o torus
            figura = 4;
            break;
        case '6': // 6 = Pinta a figura de vermelho
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            break;
        case '7': // 7 = Pinta a figura de verde
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            break;
        case '8': // 8 = Pinta a figura de azul
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            break;
        case '9': // 9 = Aumenta a escala da figura
            escala *= 1.5f;
            break;
        case 'B':
        case 'b': // B = mover para baixo
            eyey -= 0.1f;
            break;
        case 'C':
        case 'c': // C = mover para cima
            eyey += 0.1f;
            break;
        case 'D':
        case 'd': // D = mover para direita
            eyex += 0.1f;
            break;
        case 'E':
        case 'e': // E = mover para esquerda
            eyex -= 0.1f;
            break;
        case 'F':
        case 'f': // F = mover para frente
            eyez -= 0.1f;
            break;
        case 'G':
        case 'g': // G = Coloca figura para girar em torno do eixo Y
            gira = !gira;
            break;
        case 'I':
        case 'i': // I = - slices
            slices -= 1;
            break;
        case 'M':
        case 'm': // M = - nsides
            nsides -= 1;
            break;
        case 'N':
        case 'n': // N = + nsides
            nsides += 1;
            break;
        case 'O':
        case 'o': // O = + stacks
            stacks += 1;
            break;
        case 'P':
        case 'p': // P = - stacks
            stacks -= 1;
            break;
        case 'R':
        case 'r': // R = + rings
            rings += 1;
            break;
        case 'T':
        case 't': // T = mover para trás
            eyez += 0.1f;
            break;
        case 'U':
        case 'u': // U = + slices
            slices += 1;
            break;
        case 'Y':
        case 'y': // Y = - rings
            rings -= 1;
            break;
    }
	EspecificaParametrosVisualizacao();   
	glutPostRedisplay();
	
}
   
// Define as cores
void MenuCor(int colors)
{
	switch(colors) {
        case 0:  //VERMELHO
            r = 1.0f;
            g = 0.0f;
            b = 0.0f;
            break;
        case 1: //VERDE
            r = 0.0f;
            g = 1.0f;
            b = 0.0f;
            break;
        case 2: //AZUL
            r = 0.0f;
            g = 0.0f;
            b = 1.0f;
            break;
        case 3: //AMARELO
            r = 1.0f;
            g = 1.0f;
            b = 0.0f;
            break;
        case 4: //MAGENTA
            r = 1.0f;
            g = 0.0f;
            b = 1.0f;
            break;
    }
    glutPostRedisplay();
}

// Define a figura que será redesenhada
void MenuFigura(int op)
{
    switch(op) {
        case 0: 
            glutWireTeapot(size); //bule
            break;
        case 1:
            glutWireCube(size); //cubo
            break;
        case 2:
            glutWireSphere(radius, slices, stacks); //esfera
            break;
        case 3:
            glutWireCone(radius, height, slices, stacks); //cone
            break;
        case 4:
            glutWireTorus(innerRadius, outerRadius, nsides, rings); //torus
            break;
    }
    glutPostRedisplay();
}

void PosicionaObservador(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez,  	// Posição do observador
              0.0f, 0.0f, 0.0f,     // Ponto para onde o observador está olhando
              0.0f, 1.0f, 0.0f);    // Vetor que define a orientação da câmera

}

void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,fAspect,0.5,500); 
	PosicionaObservador();
}
