//////////////////////////////////////////////////////////////////
//                 Adriel de Oliveira Araujo                    //
//             Computação Gráfica - Exercício 02                //
//                    Comandos do teclado:                      //
//      w -> sobe; s -> desce; a -> esquerda; d -> direita;     //
//      + -> aumenta; "-" -> diminui; r -> levanta braço;       //
//f -> abaixa braço; R-> levante antebraço; F-> abaixa antebraço//
//////////////////////////////////////////////////////////////////

#include <GL/glut.h>

#define LARGURA  500		// Width 
#define ALTURA   500		// Heigth

//Variáveis necessárias para as transformações
double posicao_robo_x = 200.0;
double posicao_robo_y = 100.0;
double tamanho_robo_x = 0.5;
double tamanho_robo_y = 0.5;
double rotateB = 0;
double rotateA = 0;

//Função responsável por criar a cabeça
void Desenha_cabeca()
{
	/* Define da cabeça como cinza */
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2i(100, 500);
		glVertex2i(200, 500);
		glVertex2i(200, 400);
		glVertex2i(100, 400);
	glEnd();

	/* Define um ponto na cor preta para a criação dos olhos */
	glColor3f(0.0, 0.0, 0.0);
	/* Define o tamanho do ponto para 6x6 pixels */
	glPointSize(6);
	// Cria os dois olhos
	glBegin(GL_POINTS);
		glVertex2i(130, 475);
		glVertex2i(170, 475);
	glEnd();

	//Cria a boca
	glBegin(GL_LINE_STRIP);
		glVertex2i(130, 435);		
		glVertex2i(140, 425);
		glVertex2i(150, 425);
		glVertex2i(160, 435);
	glEnd();
}

//Função responsável por criar o tronco
void Desenha_tronco()
{
	// Define a cor do tronco como cinza
	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_QUADS);
		glVertex2i(75, 390);
		glVertex2i(75, 100);
		glVertex2i(225, 100);
		glVertex2i(225, 390);
	glEnd();

}

//Função responsável por criar o antebraço
void Desenha_antebraco()
{
	// Define a cor do tronco como vermelha
	glColor3f(1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
		glVertex2i(225, 250);
		glVertex2i(225, 150);
		// Define a cor branca como degradê
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2i(255, 150);
		glVertex2i(255, 250);
	glEnd();
}

//Função responsável por criar o braço
void Desenha_braco()
{
	// Define a cor do tronco como vermelha
	glColor3f(0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);
		glVertex2i(225, 390);
		glVertex2i(225, 250);
		// Define a cor branca como degradê
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2i(255, 250);
		glVertex2i(255, 390);
	glEnd();
}

//Função responsável por definir a função de cada tecla especificada
void GerenciaTeclado(unsigned char key, int x, int y){
	switch (key) {
		case 'w': //Caso 'w' o robô sobe
			posicao_robo_y += 5.0;
			break;
		case 's': //Caso 's' o robô desce
			posicao_robo_y -= 5.0;
			break;
		case 'a': //Caso 'a' o robô vai para esquerda
			posicao_robo_x -= 5.0;
			break;
		case 'd': //Caso 'd' o robô vai para direita
			posicao_robo_x += 5.0;
			break;
		case '+': //Caso '+' o robô aumenta de tamanho
			tamanho_robo_x *= 1.5;
			tamanho_robo_y *= 1.5;
			break;
		case '-': //Caso '-' o robô diminui de tamanho
			tamanho_robo_y /= 1.5;
			tamanho_robo_x /= 1.5;
			break;
		case 'r': //Caso 'r' o robô levanta o braço até certa altura
			if(rotateB > 135)
				break;
			else
			{
				rotateB += 3;
				break;
			}

		case 'f': //Caso 'r' o robô baixa o braço até encostar no tronco
			if(rotateB <= 0)
				break;
			else
			{
				rotateB -= 3;
				break;
			}
 
		case 'R': //Caso 'r' o robô levanta o antebraço até certa altura
			if(rotateA > 135)
				break;
			else
			{
				rotateA += 3;
				break;
			}

		case 'F': //Caso 'r' o robô baixa o antebraço até ficar reto com o braço
			if(rotateA <= 0)
				break;
			else
			{
				rotateA -= 3;
				break;
			}
		
    }

    glutPostRedisplay();
}

/* Função callback chamada para fazer o desenho */
void Desenha(void)
{
	/* Especifica que as transformações irão alterar os desenhos (modelos) */
	glMatrixMode(GL_MODELVIEW);  
	/* Carrega na matriz corrente a matriz identidade */
	glLoadIdentity();	

	/* Limpa a janela de visualização com a cor de fundo especificada */
	glClear(GL_COLOR_BUFFER_BIT);

	glScaled(tamanho_robo_x, tamanho_robo_y, 1.0);

	glTranslatef(posicao_robo_x, posicao_robo_y, 0.0);

	Desenha_cabeca();
	Desenha_tronco();

	//Translada o ponto pivô do braço pra origem, rotaciona e coloca no mesmo lugar novamente
	glTranslatef(240, 390, 0.0);
	glRotatef(rotateB, 0, 0, 1);
	glTranslatef(-240, -390, 0.0);
	Desenha_braco();

	//Translada o ponto pivô do antebraço pra origem, rotaciona e coloca no mesmo lugar novamente
	glTranslatef(240, 250, 0.0);
	glRotatef(rotateA, 0, 0, 1);
	glTranslatef(-240, -250, 0.0);
	Desenha_antebraco();

	/* Executa os comandos OpenGL */
	glFlush();
}

/* Inicializa parâmetros de rendering */
void Inicializa (void)
{
    /* Define a cor de fundo da janela de visualização como branca */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    /* Modo de projecao ortogonal */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, LARGURA, 0, ALTURA, -1 ,1);
}

/* Programa Principal */
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Robo: ");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutKeyboardFunc(GerenciaTeclado);
	glutMainLoop();
}

