//////////////////////////////////////////////////////////////////////////////////
//                   Autor/Author: Adriel de Oliveira Araujo                    //
//           Universidade Estadual do Ceará / Ceara State University            //
//                     Computação Gráfica / Computer Graphics                   //
//  *Esse código tem a intenção de implementar o símbolo das olímpiadas em 3D   //
//    com todos os tipos de parâmetros de luz, e característica de materiais    //
//     *This code is intended to implement the olympic games symbol in 3D*      //
//////////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>

#define LARGURA  600	// Width 
#define ALTURA   600	// Heigth 

void ParametrosIluminacao()
{
	// ParÃ¢metros para a Luz GL_LIGHT0 sendo uma fonte de Luz Pontual
	GLfloat luzAmbiente[4]={1.0, 1.0, 1.0, 1.0};	// Cor branca
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};	  	// Cor branca
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; 	// Cor branca - brilho
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};	// Fonte de Luz Pontual

	//Define os parÃ¢metros da luz de nÃºmero 0 (Luz Pontual)
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	//Ativa o uso de uma fonte de luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// CaracterÃ­sticas do material
	GLfloat ka[4]={0.0, 0.0, 0.0, 1.0};		// Reflete porcentagens da cor ambiente 
	GLfloat kd[4]={0.2, 0.2, 0.3, 1.0};		// Reflete porcentagens da cor difusa 
	GLfloat ks[4]={1.0, 1.0, 1.0, 1.0};		// Reflete porcentagens da cor especular 
	GLfloat shininess = 100.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks); // RefletÃ¢ncia do material
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);   // ConcentraÃ§Ã£o do brilho
}

// Desenha a argola da esquerda de cima
void Desenha_Argola1()
{
	// Define cor da argola como azul (reflete azul)
	GLfloat emission[] = {0.0, 0.0, 0.5, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	// Cria uma argola com raio interior de 0.4 e raio exterior total de 3
	// Translada a argola para posiÃ§Ã£o especificada
	glTranslatef(-7, 0, 0.0);
	glutSolidTorus(0.4, 3, 20, 20);
	glTranslatef(7, 0, 0.0);
}

// Desenha a argola do centro de cima
void Desenha_Argola2()
{
	// Define cor da argola como preta (reflete nenhuma)
	GLfloat emission[] = {0.0, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	// Cria uma argola com raio interior de 0.4 e raio exterior total de 3
	// Translada a argola para posiÃ§Ã£o especificada
	glutSolidTorus(0.4, 3, 20, 20);
}

// Desenha a argola da direita de cima
void Desenha_Argola3()
{
	// Define cor da argola como vermelha (reflete vermelho)
	GLfloat emission[] = {0.7, 0.0, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	// Cria uma argola com raio interior de 0.4 e raio exterior total de 3
	// Translada a argola para posiÃ§Ã£o especificada
	glTranslatef(7, 0, 0.0);
	glutSolidTorus(0.4, 3, 20, 20);
	glTranslatef(-7, 0, 0.0);
}

// Desenha a argola da esquerda de baixo
void Desenha_Argola4()
{
	// Define cor da argola como amarela (reflete amarelo)
	GLfloat emission[] = {0.7, 0.7, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	// Cria uma argola com raio interior de 0.4 e raio exterior total de 3
	// Translada a argola para posiÃ§Ã£o especificada
	glTranslatef(-3.5, -3, 1.0);
	glutSolidTorus(0.4, 3, 20, 20);
	glTranslatef(3.5, 3, -1.0);
}

// Desenha a argola da direita de baixo
void Desenha_Argola5()
{
	// Define cor da argola como verde (reflete verde)
	GLfloat emission[] = {0.0, 0.6, 0.0, 1.0};
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);
	// Cria uma argola com raio interior de 0.4 e raio exterior total de 3
	// Translada a argola para posiÃ§Ã£o especificada
	glTranslatef(3.5, -3, 1.0);
	glutSolidTorus(0.4, 3, 20, 20);
	glTranslatef(-3.5, 3, 1.0);
}

// FunÃ§Ã£o que chama tudo que Ã© necessÃ¡rio para aparecer na tela
void Desenha()
{

	// Limpa a janela de visualizaÃ§Ã£o com a cor de fundo especificada
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 30.0,	// Eye
    		  0.0, 0.0, 0.0,	// Look
    		  0.0, 1.0, 0.0);	// Up

	// Chama as funÃ§Ãµes necessÃ¡rias
    ParametrosIluminacao();
    Desenha_Argola1();
    Desenha_Argola2();
    Desenha_Argola3();
    Desenha_Argola4();
    Desenha_Argola5();
    
    // Executa os comandos OpenGL
	glFlush();
}

void Inicializa()
{
	// Define a cor de fundo da janela de visualizaÃ§Ã£o como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Modo de projecao ortogonal (Default)
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0f, ((GLfloat)LARGURA/(GLfloat)ALTURA), 1, 50.0f);

	// ParÃ¢metros de IluminaÃ§Ã£o
	// Habilita o uso de iluminaÃ§Ã£o 
	glEnable(GL_LIGHTING);
	// Habilita a luz de nÃºmero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering para remoÃ§Ã£o de faces escondidas
	glEnable(GL_DEPTH_TEST);

	// Modelos de IluminaÃ§Ã£o Defaut 
	glShadeModel(GL_SMOOTH);										// Gouraud
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Iluminacao");
	glutDisplayFunc(Desenha);
	Inicializa();
	glutMainLoop();
}
