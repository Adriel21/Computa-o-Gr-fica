//////////////////////////////////////////////////////////////////////////////////
//                   Autor/Author: Adriel de Oliveira Araujo                    //
//           Universidade Estadual do Ceará / Ceara State University            //
//                     Computação Gráfica / Computer Graphics                   //
//    *Esse código tem a intenção de implementar a animação de uma casa num     //
//                                   quadro 2D.*                                //
//          *This code is intended to implement a house animation in 2D.*       //
//////////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include <iostream>
using namespace std;

#define LARGURA  500		/* Width */
#define ALTURA   500		/* Heigth */

/* Variaveis para controlar a Animação */
int pos_x  = 40;						// Posição do desenho em X
int passox = 1;							// Define o sentido em X
int pos_y  = 120;						// Posição do desenho em Y
int passoy = 1;							// Define o sentido em Y
int x_positivo = 0;						// Verifica se a última parte da extremidade tela tocada foi a da direita
int x_negativo = 1;						// Verifica se a última parte da extremidade tela tocada foi a da esquerda
int y_positivo = 0;						// Verifica se a última parte da extremidade tela tocada foi a de cima
int y_negativo = 0;						// Verifica se a última parte da extremidade tela tocada foi a de baixo

// Desenha o muro da frente da casa na cor azul
void Desenha_Muro()
{
	/* Define a cor do desenho para azul */
	glColor3f(0.0f, 0.0f, 1.0f);

	/* Desenha um quadrado na cor corrente */
	glBegin(GL_POLYGON);
		glVertex2i(100, 100);
		glVertex2i(100, 180);
		glVertex2i(200, 180);
		glVertex2i(200, 100);
	glEnd();
}

// Desenha o telhado da casa em vermelho
void Desenha_Telhado(){

	/* Define a cor do desenho para vermelha */
	glColor3f(1.0f, 0.0f, 0.0f);

	/* Desenha um triângulo na cor corrente */
	glBegin(GL_TRIANGLES);
		glVertex2i(100, 180);
		glVertex2i(150, 220);
		glVertex2i(200, 180);
	glEnd();

}

// Desenha a porta da casa em branco
void Desenha_Porta(){

	/* Define a cor do desenho para branca */
	glColor3f(1.0f, 1.0f, 1.0f);

	/* Desenha um quadrado na cor corrente */
	glBegin(GL_POLYGON);
		glVertex2i(140, 102);
		glVertex2i(140, 160);
		glVertex2i(160, 160);
		glVertex2i(160, 102);
	glEnd();

}

// Desenha a janela da casa em braco com as astes azuis.
void Desenha_Janela(){

	/* Define a cor do desenho para branca */
	glColor3f(1.0f, 1.0f, 1.0f);

	/* Desenha um quadrado na cor corrente */
	glBegin(GL_POLYGON);
		glVertex2i(170, 140);
		glVertex2i(170, 160);
		glVertex2i(190, 160);
		glVertex2i(190, 140);
	glEnd();

	/* Define a cor das astes da janela para azul */
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2i(170, 150);
		glVertex2i(190, 150);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(180, 140);
		glVertex2i(180, 160);
	glEnd();

}

/* Função callback chamada para fazer o desenho */
void Desenha(void)
{
	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /* Transformar para animar */
    glTranslatef(pos_x, pos_y, 0.0);

	Desenha_Muro();
	Desenha_Telhado();
	Desenha_Porta();
	Desenha_Janela();

	/* Executa os comandos OpenGL */
	glutSwapBuffers();
}

void Anima(int value)  /* Usada quando se usar glutTimerFunc() */
{
	pos_x += passox;							// Objeto se move em relação a X baseado na variável "passox"
	pos_y += passoy;							// Objeto se move em relação a X baseado na variável "passox"

	if(pos_x > 300){							// Verifica se a casa chegou na extremidade direita da tela
		if(y_negativo == 1)						// Verifica se a última extremidade da tela tocada foi a inferior
			passox = (-1)*passox;				// Faz o X voltar e o Y continuar subindo
		else if(y_positivo == 1)				// Verifica se a última extremidade da tela tocada foi a superior
			passox = (-1)*passox;				// Faz o X voltar e o Y continuar descendo

		// Atualiza as variáveis afim de dizer que a última extremidade da tela tocada foi a atual (a extremidade direita)
		x_positivo = 1;
		y_positivo = 0;
		x_negativo = 0;
		y_negativo = 0;
	}
	else if(pos_x < -100){						// Verifica se a casa chegou na extremidade esquerda da tela
		if(y_negativo == 1)						// Verifica se a última extremidade da tela tocada foi a inferior
			passox = (-1)*passox;				// Faz o X voltar e o Y continuar subindo
		else if(y_positivo == 1)				// Verifica se a última extremidade da tela tocada foi a superior
			passox = (-1)*passox;				// Faz o X voltar e o Y continuar descendo

		// Atualiza as variáveis afim de dizer que a última extremidade da tela tocada foi a atual (a extremidade direita)
		x_positivo = 0;
		y_positivo = 0;
		x_negativo = 1;
		y_negativo = 0;
	}
	else if(pos_y > 300){						// Verifica se a casa chegou na extremidade superior da tela
		if(x_negativo == 1)						// Verifica se a última extremidade da tela tocada foi a esquerda
			passoy = (-1)*passoy;				// Faz o Y voltar e o X continuar indo pra direita
		else if(x_positivo == 1)				// Verifica se a última extremidade da tela tocada foi a direita
			passoy = (-1)*passoy;				// Faz o Y voltar e o X continuar indo pra esquerda

		// Atualiza as variáveis afim de dizer que a última extremidade da tela tocada foi a atual (a extremidade direita)
		x_positivo = 0;
		y_positivo = 1;
		x_negativo = 0;
		y_negativo = 0;
	}
	else if(pos_y < -100){						// Verifica se a casa chegou na extremidade inferior da tela
		if(x_negativo == 1)						// Verifica se a última extremidade da tela tocada foi a esquerda
			passoy = (-1)*passoy;				// Faz o Y voltar e o X continuar indo pra direita
		else if(x_positivo == 1)				// Verifica se a última extremidade da tela tocada foi a direita
			passoy = (-1)*passoy;				// Faz o Y voltar e o X continuar indo pra esquerda

		// Atualiza as variáveis afim de dizer que a última extremidade da tela tocada foi a atual (a extremidade direita)
		x_positivo = 0;
		y_positivo = 0;
		x_negativo = 0;
		y_negativo = 1;
	}

	glutPostRedisplay();
	glutTimerFunc(1, Anima, 1);
}

/* Inicializa parâmetros de rendering */
void Inicializa (void)
{
    /* Define a cor de fundo da janela de visualização como branca */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Modo de projecao ortogonal */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, LARGURA, 0, ALTURA);
}

/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Animacao Quadrado 2D");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutTimerFunc(100, Anima, 1);
	glutMainLoop();
}

