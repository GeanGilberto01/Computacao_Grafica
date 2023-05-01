#include <gl/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

// Fun��o respons�vel pela Terra
void Terra(void){
	glColor3f(0.2, 0.8, 0.2);  // Verde
		
    glBegin(GL_QUADS); // define o in�cio de um pol�gono com quatro v�rtices
	    glVertex2f(-1.0, -0.6); // define o primeiro v�rtice
	    glVertex2f(1.0, -0.6); // define o segundo v�rtice
	    glVertex2f(1.0, -1.0); // define o terceiro v�rtice
	    glVertex2f(-1.0, -1.0); // define o quarto v�rtice
    glEnd(); // define o fim do pol�gono
}

// Fun��o respons�vel pela casa
void Casa(void){		
    // Desenha a parede da casa
	glColor3f(0.5, 0.8, 1.0);  // Azul
		
    glBegin(GL_POLYGON);
	    glVertex2f(-0.2, -0.6); // Canto inferior esquerdo
	    glVertex2f(0.8, -0.6); // Canto inferior direito
	    glVertex2f(0.8, 0.4); // Canto superior direito
	    glVertex2f(-0.2, 0.4); // Canto superior esquerdo
    glEnd();

	glColor3f(0.6, 0.3, 0.0);  // Marrom
		
	// Desenha a porta da casa
    glBegin(GL_POLYGON);
	    glVertex2f(0.2, -0.6); // Canto inferior esquerdo
	    glVertex2f(0.4, -0.6); // Canto inferior direito
	    glVertex2f(0.4, -0.1); // Canto superior direito
	    glVertex2f(0.2, -0.1); // Canto superior esquerdo
    glEnd();
    
	// Desenha a janela da casa
	glBegin(GL_QUADS); // define o in�cio de um pol�gono com quatro v�rtices
		glVertex2f(-0.1, 0.1); // define o primeiro v�rtice
		glVertex2f(0.1, 0.1); // define o segundo v�rtice
		glVertex2f(0.1, 0.3); // define o terceiro v�rtice
		glVertex2f(-0.1, 0.3); // define o quarto v�rtice
	glEnd(); // define o fim do pol�gono
	
	glBegin(GL_QUADS); // define o in�cio de um pol�gono com quatro v�rtices
		glVertex2f(0.5, 0.1); // define o primeiro v�rtice
		glVertex2f(0.7, 0.1); // define o segundo v�rtice
		glVertex2f(0.7, 0.3); // define o terceiro v�rtice
		glVertex2f(0.5, 0.3); // define o quarto v�rtice
	glEnd(); // define o fim do pol�gono
    
	// Desenha o telhado da casa
	glBegin(GL_TRIANGLES); // define o in�cio de um pol�gono com quatro v�rtices
		glVertex2f(-0.3, 0.4); // define o primeiro v�rtice
		glVertex2f(0.3, 0.9); // define o segundo v�rtice
		glVertex2f(0.9, 0.4); // define o terceiro v�rtice
	glEnd(); // define o fim do pol�gono
}

// Fun��o respons�vel pela arvore
void Arvore(void){
	
	// Desenha a base da arvore
	glColor3f(0.6, 0.3, 0.0);  // Marrom
		
    glBegin(GL_POLYGON);
	    glVertex2f(-0.7, -0.6); // Canto inferior esquerdo
	    glVertex2f(-0.8, -0.6); // Canto inferior direito
	    glVertex2f(-0.8, -0.1); // Canto superior direito
	    glVertex2f(-0.7, -0.1); // Canto superior esquerdo
    glEnd();
    
    //Desenha o topo da arvore
	glColor3f(0.2, 0.8, 0.2);  // Verde
		
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(cos(rad) * 0.1 - 0.75, sin(rad) * 0.1 - 0.1);
    }                                                         
    glEnd();     
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(cos(rad) * 0.1 - 0.85, sin(rad) * 0.1 - 0.05);
    }                                                         
    glEnd();  
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(cos(rad) * 0.1 - 0.75, sin(rad) * 0.1 - 0.0);
    }                                                         
    glEnd();  
    
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(cos(rad) * 0.1 - 0.65, sin(rad) * 0.1 - 0.05);
    }                                                         
    glEnd();  
}

// Fun��o respons�vel pelo sol
void Sol(void){
	glColor3f(1.0, 1.0, 0.0);  // Amarelo
		
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(cos(rad) * 0.1 - 0.8, sin(rad) * 0.1 + 0.8);
    }                                                          
    glEnd();    
    
    // Linha Embaixo
	glBegin(GL_LINES);
		glVertex2f(-0.80,0.69);  
		glVertex2f(-0.80,0.59);
	glEnd();        
	
	glBegin(GL_LINES);
		glVertex2f(-0.85,0.70);  
		glVertex2f(-0.90,0.60);
	glEnd(); 
	
	glBegin(GL_LINES);
		glVertex2f(-0.90,0.75);  
		glVertex2f(-0.98,0.70);
	glEnd(); 
	
    // Linha Esquerda
	glBegin(GL_LINES);
		glVertex2f(-0.91,0.80);  
		glVertex2f(-1.01,0.80);
	glEnd();  
	
	glBegin(GL_LINES);
		glVertex2f(-0.90,0.85);  
		glVertex2f(-0.98,0.90);
	glEnd(); 
	
	glBegin(GL_LINES);
		glVertex2f(-0.85,0.90);  
		glVertex2f(-0.90,0.99);
	glEnd(); 
	
    // Linha Cima
	glBegin(GL_LINES);
		glVertex2f(-0.80,0.91);  
		glVertex2f(-0.80,1.01);
	glEnd();   
	
	glBegin(GL_LINES);
		glVertex2f(-0.75,0.90);  
		glVertex2f(-0.70,0.99);
	glEnd();  
	
	glBegin(GL_LINES);
		glVertex2f(-0.70,0.86);  
		glVertex2f(-0.60,0.91);
	glEnd(); 
	
    // Linha Direita
	glBegin(GL_LINES);
		glVertex2f(-0.69,0.80);  
		glVertex2f(-0.59,0.80);
	glEnd();  
	
	glBegin(GL_LINES);
		glVertex2f(-0.70,0.74);  
		glVertex2f(-0.60,0.69);
	glEnd();   
	
	glBegin(GL_LINES);
		glVertex2f(-0.75,0.70);  
		glVertex2f(-0.70,0.61);
	glEnd();                                              
}                                                              

// Fun��o de redesenho da janela de visualiza��o
void Desenha(void){
	glClearColor(1,1,1,0);  // branco
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Limpe a tela e o buffer
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);            // Indique que os dois lados de qualquer superf�cie devem ser representados.    
	glLoadIdentity();                                           // Resete a corrente Modelview Matrix
	
	//implementa desenhos dos objetos
	Terra(); 
	Casa();
	Arvore();
	Sol();
	glFlush(); 
	
	glutSwapBuffers();                                          // Troque os buffers.
}

//Fun��o para reconhecer o comando do teclado
void Teclado (unsigned char key, int x, int y) {
	if(key == 27)
		exit(0);	
}

// Fun��o respons�vel por desenhar os circulos
void DesenhaCirculo(float cx, float cy, float r, int num_segmentos){
	glBegin(GL_LINE_LOOP); // desenha o c�rculo
	for(int ii = 0; ii < num_segmentos; ii++){
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segmentos); 
		float x = r * cosf(theta); //calcular o componente x
		float y = r * sinf(theta); //calcular o componente y
		glVertex2f(x + cx, y + cy); //vertices de sa�da
	}
	glEnd();
	glBegin(GL_POLYGON);  // preenche o c�rculo
	for (int i = 0; i < 360; i++) {
		float angle_theta = i * 3.142 / 180;
		glVertex2f(cx + r * cos(angle_theta), cy + r * sin(angle_theta));
	}
	glEnd();
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
	glutCreateWindow("Exercicio 1"); // Cria a janela passando como argumento o t�tulo da mesma
	glutDisplayFunc(Desenha); // Registra fun��o de redesenho
	glutKeyboardFunc(Teclado); // Registra fun��o de teclado
	glutReshapeFunc(AlteraTamanhoJanela);
	Inicializa();
	glutIdleFunc(Desenha);
	glutMainLoop(); // Inicia o processamento e aguarda intera��es do usu�rio
	return 0;
}
