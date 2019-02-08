#include <GL/glut.h>

#define LARGURA  500		
#define ALTURA   500		

// Função para desenhar as duas linhas
void Desenha_linha()
{
	
	glColor3f(0.0, 1.0, 0.0);                                       //Degradê verde na primeira linha

	glBegin(GL_LINE_STRIP);											//Permite fazer outra linha a partir do último ponto da primeira
		glVertex2i(100, 100);		
		glColor3f(0.0, 0.0, 0.0);									//Completa o degradê com preto
		glVertex2i(300, 300);
		glVertex2i(230,0);
		
	glEnd();
}

//Função para desenhar o triângulo branco
void Desenha_triangulo()
{
	
	glColor3f(1.0f, 1.0f, 1.0f);									//Cor do triângulo branca

	glBegin(GL_TRIANGLES);
		
		glVertex2i(250, 500);
		glVertex2i(0, 250);
		glVertex2i(500, 250);

	glEnd();
}

//Função para desenhar dois triângulos em sequência, um branco e um com o degradê azul
void Desenha_triangulo2()
{
	
	glColor3f(1.0f, 1.0f, 1.0f);									//Cor do primeiro triângulo branca

	
	glBegin(GL_TRIANGLE_STRIP);										//Liga um terceiro ponto aos últimos dois do último triângulo, formando assim um terceiro.
		
		glVertex2i(250, 500);
		glVertex2i(0, 250);
		glVertex2i(500, 250);
		glColor3f(0.0f, 0.0f, 1.0f);								//Degradê azul
		glVertex2i(250, 0);
	glEnd();
}

//Função para desenhar o quadrado com quatro cores
void Desenha_quadrado(){

	glColor3f(1.0f, 0.0f, 0.0f);									//Cor do quadrado vermelha

	glBegin(GL_QUADS);

		glVertex2i(250, 250);
		glColor3f(0.0f, 0.0f, 0.0f);								//Cor do segundo ponto: preto		
		glVertex2i(250, 500);
		glColor3f(0.0f, 1.0f, 0.0f);								//Cor do terceiro ponto: verde
		glVertex2i(500, 500);
		glColor3f(1.0f, 1.0f, 1.0f);								//Cor do quarto ponto: branca
		glVertex2i(500, 250);

	glEnd();
}

//Função para declaração
void Desenha(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 250, 250, 250);									//Separa o triângulo branco para o primeiro quadrante da tela
	Desenha_triangulo();

	glViewport(250, 250, 250, 250);									//Separa o "quadrado" branco com azul para o segundo quadrante da tela
	Desenha_triangulo2();

	glViewport(0, 0, 250, 250);										//Separa as linhas para o terceiro quadrante a tela
	glScissor(0, 0, 250, 250);										//Separa o terceiro quadrante para poder alocar outra cor
	glEnable(GL_SCISSOR_TEST);
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);							//Aloca a cor verde como a cor de fundo do terceiro quadrante
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_linha();

	glViewport(250, 0, 250, 250);									//Separa o quadrado multicolor para o quarto quadrante a tela
	glScissor(250, 0, 250, 250);									//Separa o quarto quadrante para poder alocar outra cor
	glEnable(GL_SCISSOR_TEST);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);							//Aloca a cor branca como a cor de fundo do quarto quadrante
	glClear(GL_COLOR_BUFFER_BIT);
	Desenha_quadrado();


	
	glFlush();
}

//Inicializa a tela na cor vermelha
void Inicializa (void)
{
    
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);

    
    glOrtho(0, LARGURA, 0, ALTURA, -1 ,1);
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Poligonos:");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
}

