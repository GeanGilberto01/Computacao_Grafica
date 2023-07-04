#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.1415

using namespace std;

// Instânciação dos métodos

void Inicializa(void);								// Método responsável por inicializar o ambiente OpenGL
void AlteraTamanhoJanela(int w, int h);				// Método chamado quando o tamanho da janela é alterado
void Desenha(void);									// Método responsável por desenhar a cena
void Teclado (unsigned char key, int x, int y);		// Método chamado quando uma tecla comum é pressionada
void TeclasEspeciais (int key, int x, int y);		// Método chamado quando uma tecla especial é pressionada
void Atualiza(int valor);							//Timer para controlar o giro do objeto

// Variáveis Globais
GLint size= 2; // Tamanho do bule

GLfloat obs[3] = {0.0,7.0,0.0}; // Coordenadas da posição do observador
GLfloat olho[3] = {0.0,3.0,0.0}; // Coordenadas do ponto para onde o observador está olhando

GLfloat luzAmbiente[4] = {0.2,0.2,0.2,1.0};
GLfloat luzDifusa[4] = {0.7,0.7,0.7,1.0};
GLfloat luzEspecular[4] = {1.0, 1.0, 1.0,1.0};

GLfloat posicao_luz0[]    = { 0.0, 10.0, -7.0, 1.0}; // Posição da luz 0
GLfloat posicao_luz1[]    = { 0.0, 10.0,  7.0, 1.0}; // Posição da luz 1

GLfloat cor_luz0[]        = { 1.0, 0.0, 0.0, 1.0}; // Cor da luz 0
GLfloat cor_luz1[]        = { 0.0, 0.0, 1.0, 1.0}; // Cor da luz 1

GLfloat tetaxz=0; // Rotação do objeto no plano XZ
GLfloat raioxz=6; // Raio do objeto no plano XZ

bool gira; // Controle de rotação do objeto
GLfloat angulo; // angulo de rotacão do objeto
GLfloat alfa; // angulo de rotacão do objeto
GLfloat velocidadeRotacao = 2.0f; // Velocidade de rotação do objeto

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                          			// Inicializa a GLUT
    glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);		// Modo de operação da GLUT
    glutInitWindowPosition(350, 100);               			// posiciona a janela na tela. A referência é o canto superior esquerdo
    glutInitWindowSize(640, 480);                   			// tamanho em pixels da janela
    if(!glutCreateWindow("Exercicio 11")){						// Cria a janela passando como argumento o título da mesma
	    fprintf(stderr,"Erro ao tentar abrir o programa\n");	// Caso de erro na criação da janela apresenta a mensagem 
	    exit(-1);												// Fecha o sistema 
  	}               	
    Inicializa();												// Inicializa as variaveis				
    glutReshapeFunc(AlteraTamanhoJanela);						// Configura janela de exibição
    glutDisplayFunc(Desenha);                       			// Registra função de redesenho
	glutKeyboardFunc(Teclado); 									// Registra função de teclado
	glutSpecialFunc(TeclasEspeciais);							// Registra função de teclas especiais
    glutMainLoop();                                 			// Inicia o processamento e aguarda interações do usuário
    return 0;
}

// Método responsável por inicializar o ambiente OpenGL
void Inicializa(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Define a cor de fundo para preto
    gira = false;
    angulo = 0.0f;
    alfa = 0.5f;

    // Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    // Define as propriedades da luz ambiente global
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define as propriedades da luz 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicao_luz0 );
	
    // Define as propriedades da luz 1 (spotlight)
    glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT1, GL_POSITION, posicao_luz1 );

    // Define o modelo de shading (flat ou gouraud)
    glShadeModel(GL_SMOOTH);

    // Habilita o teste de profundidade
    glEnable(GL_DEPTH_TEST);

    // Habilita a iluminação de duas faces dos objetos
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}

// Método chamado quando o tamanho da janela é alterado
void AlteraTamanhoJanela(int w, int h)
{
    glViewport(0, 0, w, h); // Define as dimensões da viewport igual ao tamanho da janela

    glMatrixMode(GL_PROJECTION); // Define a matriz atual como a matriz de projeção
    glLoadIdentity(); // Carrega a matriz identidade

    gluPerspective(70.0, (GLfloat)w / (GLfloat)h, 0.1, 30.0); // Define a projeção perspectiva

    glMatrixMode(GL_MODELVIEW); // Define a matriz atual como a matriz de visualização
}

// Método responsável por redesenhar a cena na janela de visualização
void Desenha()
{
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade
    glEnable(GL_LIGHTING); // Habilita a iluminação

    glDepthMask(GL_TRUE); // Habilita a gravação no buffer de profundidade
    glClearColor(1.0, 1.0, 1.0, 1.0); // Define a cor de fundo como branco
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer de cor e o buffer de profundidade

    glPushMatrix();

    /* Calcula a posição do observador */
    obs[0] = raioxz * cos(2 * PI * tetaxz / 360);
    obs[2] = raioxz * sin(2 * PI * tetaxz / 360);

    gluLookAt(obs[0], obs[1], obs[2], olho[0], olho[1], olho[2], 0.0, 1.0, 0.0); // Define a posição e orientação do observador

//    /* Desenha o plano */
//    glNormal3f(0, 1, 0);
//    glBegin(GL_QUADS);
//    glVertex3f(-10, 0, 10);
//    glVertex3f(10, 0, 10);
//    glVertex3f(10, 0, -10);
//    glVertex3f(-10, 0, -10);
//    glEnd();

    glPushMatrix();
    glTranslatef(posicao_luz0[0], posicao_luz0[1], posicao_luz0[2]);
    glColor3f(1, 0, 0);
    glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz0);
    glutSolidSphere(0.3, 5, 5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posicao_luz1[0], posicao_luz1[1], posicao_luz1[2]);
    glMaterialfv(GL_FRONT, GL_EMISSION, cor_luz1);
    glutSolidSphere(0.3, 5, 5);
    glPopMatrix();
    
    
    glPushMatrix();
	glTranslatef(0.0,3.0,0.0);
    if(gira){
        angulo += 0.5;
    }    
    glRotatef(angulo, 0.0f, 1.0f, 0.0f);
    glColor4f(0.0f, 0.0f, 1.0f, alfa);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glutSolidTeapot(size);
    glDisable(GL_BLEND);
    glPopMatrix();

    glDisable(GL_LIGHTING); // Desabilita a iluminação
    glDisable(GL_DEPTH_TEST); // Desabilita o teste de profundidade

    glPopMatrix();

    glFlush(); // Força o desenho das primitivas

    glutSwapBuffers(); // Troca os buffers de desenho (utilizado quando se está utilizando double buffering)
}

// Função para reconhecer o comando do teclado
void Teclado(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            // Tecla ESC pressionada
            exit(0); // Encerra o programa
            break;
        case 'D':
        case 'd': // D = Alterna entre habilitar e desabilitar a luz superior direita
            if (glIsEnabled(GL_LIGHT0))
                glDisable(GL_LIGHT0);
            else
                glEnable(GL_LIGHT0);
            break;
        case 'E':
        case 'e': // E = Alterna entre habilitar e desabilitar a luz superior esquerda
            if (glIsEnabled(GL_LIGHT1))
                glDisable(GL_LIGHT1);
            else
                glEnable(GL_LIGHT1);
            break;
        case 'G':
        case 'g': // G = Coloca figura para girar em torno do eixo Y
            gira = !gira;
            if (gira) {
		        glutTimerFunc(0, Atualiza, 0); // Inicia o temporizador imediatamente
		    }
            break;
        case 'T': // T = Aumenta a transparência do objeto
		    if(alfa < 1.0){
		        alfa += 0.1;
		    }    
            break;
        case 't': // t = Diminui a transparência do objeto
		    if(alfa > 0.0){
		        alfa -= 0.1;
		    }    
            break;
    }
    glutPostRedisplay(); // Marca a janela como necessitando de redesenho
}

// Método responsável por tratar eventos de teclas especiais (setas do teclado, F1, F2, etc.)
void TeclasEspeciais(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            // Aumenta a coordenada y do ponto de observação
            obs[1] += 1;
            break;
        case GLUT_KEY_DOWN:
            // Diminui a coordenada y do ponto de observação
            obs[1] -= 1;
            break;
        case GLUT_KEY_LEFT:
            // Rotaciona o ângulo tetaxz para a esquerda
            tetaxz += 2;
            break;
        case GLUT_KEY_RIGHT:
            // Rotaciona o ângulo tetaxz para a direita
            tetaxz -= 2;
            break;
    }    
    glutPostRedisplay(); // Marca a janela como necessitando de redesenho
}

void Atualiza(int valor)
{
	if (!gira) {
        return; // Retorna se a rotação automática não estiver ativada
    }
    
    angulo += velocidadeRotacao;

    glutPostRedisplay(); // Solicita um novo redesenho da cena

    // Define a próxima chamada da função de temporizador
    glutTimerFunc(16, Atualiza, 0); // 16 ms = aproximadamente 60 FPS
}

