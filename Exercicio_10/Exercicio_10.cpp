#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void Inicializa(void);
void AlteraTamanhoJanela(int w, int h);
void Desenha(void);
void DesenhaCorpo(void);
void DesenhaCabeca(void);
void DesenhaBase(void);
void DesenhaBracoDireito(void);
void DesenhaBracoEsquerdo(void);
void Teclado (unsigned char key, int x, int y);

// Variáveis Globais
static int ombro = 0, cotovelo = 0;

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                          	// Inicializa a GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    	// Modo de operação da GLUT
    glutInitWindowPosition(350, 100);               	// posiciona a janela na tela. A referência é o canto superior esquerdo
    glutInitWindowSize(640, 480);                   	// tamanho em pixels da janela
    glutCreateWindow("Exercicio 10");                	// Cria a janela passando como argumento o título da mesma
    Inicializa();										// Inicializa as variaveis				
    glutReshapeFunc(AlteraTamanhoJanela);				// Configura janela de exibição
    glutDisplayFunc(Desenha);                       	// Registra função de redesenho
	glutKeyboardFunc(Teclado); 							// Registra função de teclado
    glutMainLoop();                                 	// Inicia o processamento e aguarda interações do usuário
    return 0;
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Fundo Preto
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela (int w, int h){
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef (0.0, 0.0, -5.0);
}

// Função de redesenho da janela de visualização
void Desenha(void){
  glClear (GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  
  /* Desenha o robo */
  DesenhaCorpo();
  DesenhaCabeca();
  DesenhaBase();
  DesenhaBracoDireito();
  DesenhaBracoEsquerdo();

  /* origem volta para o sistema de coordenadas original */
  glPopMatrix();
  glutSwapBuffers();
}

// Desenha o corpo do robo
void DesenhaCorpo(void)
{
    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.0); // Move o corpo para a posição correta
    glScalef(0.5f, 2.5f, 0.5f);
    glutWireCube(1.0);
    glPopMatrix();
}

// Desenha a cabeça do robo
void DesenhaCabeca(void)
{
    glPushMatrix();
    glTranslatef(0.5f, 1.5f, 0.0f); // Posiciona a cabeça acima do corpo
    glutWireSphere(0.5, 10, 10); // Desenha uma esfera como cabeça do robô
    glPopMatrix();
}

// Desenha a base do robo
void DesenhaBase(void)
{
    glPushMatrix();
    glTranslatef(0.5f, -2.5f, 0.0f); // Posiciona a base abaixo do corpo
    glRotatef(90.0f, -90.0f, 1.0f, 0.0f); // Realiza a rotação de 90° no eixo Y
    glutWireCone(1.0, 1.5, 50, 50); // Desenha um cone como base do robô
    glPopMatrix();
}

// Desenha o braço direito do robo
void DesenhaBracoDireito(void)
{
    glPushMatrix();
    glTranslatef(-2.0, 1.0, 0.0); // Move o braço direito para a posição correta
    glScalef(4.0, 0.4, 1.0);
    glutWireCube(1.0);
    glPopMatrix();
}

// Desenha o braço esquerdo do robo
void DesenhaBracoEsquerdo(void){
  /* origem posicionada no ombro */
  glTranslatef (1.0, 1.0, 0.0);
  glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);

  /* origem posicionada no centro do braço */
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();

  /* origem posicionada no cotovelo */
  glTranslatef (1.0, 0.0, 0.0);
  glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
  glTranslatef (1.0, 0.0, 0.0);
  glPushMatrix();
  glScalef (2.0, 0.4, 1.0);
  glutWireCube (1.0);
  glPopMatrix();
}

//Função para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y){
  switch (key) {
  case 'o':
    ombro = (ombro + 5) % 360;
    glutPostRedisplay();
    break;
  case 'O':
    ombro = (ombro - 5) % 360;
    glutPostRedisplay();
    break;
  case 'c':
    cotovelo = (cotovelo + 5) % 360;
    glutPostRedisplay();
    break;
  case 'C':
    cotovelo = (cotovelo - 5) % 360;
    glutPostRedisplay();
    break;
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

