#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

void Inicializa(void);
void AlteraTamanhoJanela(GLsizei w, GLsizei h);
void Desenha(void);
void Quadrado(void);
void GerenciaMouse(int button, int state, int x, int y);
void MousePressionado(int x, int y);
void MouseSolto(int x, int y);

bool pressionado = false;
int iniX, iniY;
float QuadX = 0.0f;
float QuadY = 0.0f;

// Programa Principal
int main(int argc, char **argv)
{
    glutInit(&argc, argv);                                // Inicializa a GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);          // Modo de operação da GLUT
    glutInitWindowPosition(350, 100);                     // posiciona a janela na tela. A referência é o canto superior esquerdo
    glutInitWindowSize(640, 480);                         // tamanho em pixels da janela
    glutCreateWindow("Exercicio 7");                      // Cria a janela passando como argumento o título da mesma
    Inicializa();
    glutReshapeFunc(AlteraTamanhoJanela);
    glutDisplayFunc(Desenha);                              // Registra função de redesenho
    glutMouseFunc(GerenciaMouse);                          // Gerencia Click do Mouse
    glutMotionFunc(MousePressionado);                         // Verifica a posicao do mouse quando o botão esquerdo está pressionado
    glutPassiveMotionFunc(MouseSolto);             // Verifica a posicao do mouse quando nenhum botão está pressionado
    glutMainLoop();                                        // Inicia o processamento e aguarda interações do usuário
    return 0;
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutIdleFunc(Desenha);
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

    // Estabelece a janela de seleção (left, right, bottom, top)
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

// Função de redesenho da janela de visualização
void Desenha(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(QuadX, QuadY, 0.0f);

    Quadrado();

    glFlush();
    glutSwapBuffers();
}

// Função responsável pelo quadrado
void Quadrado(void)
{
    glColor3f(0.0, 0.0, 1.0); // Azul
    glBegin(GL_QUADS);        // define o início de um polígono com quatro vértices
    glVertex2f(-0.25, -0.25);   // define o primeiro vértice
    glVertex2f( 0.25, -0.25);   // define o segundo vértice
    glVertex2f( 0.25,  0.25);   // define o terceiro vértice
    glVertex2f(-0.25,  0.25);   // define o quarto vértice
    glEnd();                  // define o fim do polígono
}

void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // Botao esquerdo do mouse pressionado
    {
        // Normalizando a posição do mouse para variar de -1 a 1
        float NormalizaX = (x - 320.0f) / 320.0f;
        float NormalizaY = (240.0f - y) / 240.0f;

        // Check if the click is inside the square
        if (NormalizaX >= QuadX - 0.5f && NormalizaX <= QuadX + 0.5f &&
            NormalizaY >= QuadY - 0.5f && NormalizaY <= QuadY + 0.5f)
        {
            pressionado = true;
            iniX = x;
            iniY = y;
        }
        printf("\nBotao esquerdo.");
        printf("\nPressionado na posicao: %d , %d", x, y);
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) // Botao esquerdo do mouse solto
    {
        pressionado = false;
        printf("\nSolto na posicao: %d , %d", x, y);
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) // Botao direito do mouse pressionado
    {
        printf("\nBotao direito.");
    }
}

void MousePressionado(int x, int y)
{
    if (pressionado)
    {
        int dx = x - iniX;
        int dy = y - iniY;

        QuadX += dx / 320.0f;
        QuadY -= dy / 240.0f;

        iniX = x;
        iniY = y;

        printf("Mouse ANDANDO pressionado na janela. Posicao: (%d, %d)\n", x, y);

        glutPostRedisplay();
    }
}

void MouseSolto(int x, int y)
{
    printf("Mouse ANDANDO solto na janela. Posicao: (%d, %d)\n", x, y);
}
