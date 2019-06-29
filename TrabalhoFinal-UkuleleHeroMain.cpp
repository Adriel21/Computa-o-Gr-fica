//////////////////////////////////////////////////////////////////////////////////
//                Autores/Authors: Adriel de Oliveira Araujo                    //
//                                 Antonio Sérgio A. Faheina                    //
//                                 Israel Ítalo Silva França                    //
//           Universidade Estadual do Ceará / Ceara State University            //
//                     Computação Gráfica / Computer Graphics                   //
// *Esse código tem a intenção de implementar um jogo chamado "Ukelele Hero" o  //
//   qual tem a óbvia intenção de fazer um jogo a semelhança do jogo "Guittar   //
//      Hero" porém aplicado, obviamente, ao instrumento musical, ukulele.*     //
//   *This code is intended to implement a game called "Ukelele Hero" that is   //
//   obviously a reference to the famous game "Guittar Hero" but aplicated to   //
//                    an musical instrument called "Ukelele"*                   //
//////////////////////////////////////////////////////////////////////////////////

#include <GL/glut.h>
#include <iostream>
#include "musicas.h"

using namespace std;

#define LARGURA  800											                            // Altura da tela
#define ALTURA   600												                        // Largura da tela

// VariÃ¡veis
double tamX = 1.0;
double tamY = 1.0;
double tamZ = 1.0;
int nvMusica = 2;
int pontuacao = 0;
double velocidadeMusica = 0;
char teclaAtual;
char teclaUltima;
GLfloat velocidadeAnimacao = 0.007;
GLfloat selecionadaCorA, selecionadaCorS, selecionadaCorD, selecionadaCorF;

// Desenho do braÃ§o e das cordas do Ukulele
void desenhoEsteira(GLfloat altura, GLfloat largura){
	glTranslatef(0,-1,0);                                                                   // Ajusta o braÃ§o e as cordas para ficarem abaixo das notas
	GLfloat emission[] = {1.0, 1.0, 1.0, 1.0};                                              // Define cor do braÃ§o como branca 
	glMaterialfv(GL_FRONT, GL_EMISSION, emission);                                          // Define o material
	glBegin(GL_QUADS);                                                                      // Cria o braÃ§o
		glVertex3i(largura, 0,altura);
		glVertex3i(largura, 0,-altura);
		glVertex3i(-largura, 0,-altura);
		glVertex3i(-largura, 0,altura);
	glEnd();

	glLineWidth(10);                                                                        // Largura da cordas a serem criadas
	//glColor3f(0,0,0);
	GLfloat emission2[] = {0.0, 0.0, 0.0, 1.0};                                             // Define cor das cordas como pretas
	glMaterialfv(GL_FRONT, GL_EMISSION, emission2);                                         // Define o material
	glBegin(GL_LINES);                                                                      // Cria corda 1
		glVertex3i(3, 0.03,20.99f);
		glVertex3i(3, 0.03,-altura);
	glEnd();
	glBegin(GL_LINES);                                                                      // Cria corda 2
		glVertex3i(1, 0.03,20.99f);
		glVertex3i(1, 0.03,-altura);
	glEnd();
	glBegin(GL_LINES);                                                                      // Cria corda 3
		glVertex3i(-1, 0.03,20.99f);
		glVertex3i(-1, 0.03,-altura);
	glEnd();
	glBegin(GL_LINES);                                                                      // Cria corda 4
		glVertex3i(-3, 0.03,20.99f);
		glVertex3i(-3, 0.03,-altura);
	glEnd();
	glTranslatef(0,1,0);
}


// Desenha esfera verde para nota
void desenhaNotaVerde(int posZ){
	GLfloat zAtual = posZ + velocidadeMusica;                                               // Nova posiÃ§Ã£o da nota a cada iteraÃ§Ã£o da variÃ¡vel "velocidadeMusica"
	if(zAtual < 24){                                                                        // Se a nota passou da posiÃ§Ã£o 24 em Z, ela jÃ¡ nÃ£o Ã© mais criada
		if(selecionadaCorA > 0.99){                                                         // Se a cor selecionada for a correspondente a tecla A, avanÃ§a
	        if((zAtual > 20.75)&&(zAtual < 21.9)){                                          // Se a tecla for acionada na regiÃ£o da argola correspondente, a nota foi acertada
	        	pontuacao += 10;                                                            // Por isso, pontua-se mais 10
	        }
	    }
		GLfloat emission[] = {0.0, 0.8, 0.0, 1.0};                                          // Desenha a esfera na cor verde
		glMaterialfv(GL_FRONT, GL_EMISSION, emission);
		glTranslatef(-3, 0, 0.0 + posZ);
		glutSolidSphere(0.5, 20, 20);
		glTranslatef(3, 0, 0.0 - posZ);
	}
}

// Desenha esfera vermelha para nota
void desenhaNotaVermelha(int posZ){
	GLfloat zAtual = posZ + velocidadeMusica;                                               // Nova posiÃ§Ã£o da nota a cada iteraÃ§Ã£o da variÃ¡vel "velocidadeMusica"
	if(zAtual < 24){                                                                        // Se a nota passou da posiÃ§Ã£o 24 em Z, ela jÃ¡ nÃ£o Ã© mais criada
		if(selecionadaCorS > 0.99){                                                         // Se a cor selecionada for a correspondente a tecla S, avanÃ§a
	        if((zAtual > 20.75)&&(zAtual < 21.9)){                                          // Se a tecla for acionada na regiÃ£o da argola correspondente, a nota foi acertada
	        	pontuacao += 10;                                                            // Por isso, pontua-se mais 10
	        }
	    }
		GLfloat emission2[] = {0.8, 0.0, 0.0, 1.0};                                         // Desenha a esfera na cor vermelha
		glMaterialfv(GL_FRONT, GL_EMISSION, emission2);
		glTranslatef(-1, 0, 0.0 + posZ);
		glutSolidSphere(0.5, 20, 20);
		glTranslatef(1, 0, 0.0- posZ);
	}
}

// Desenha esfera amarela para nota
void desenhaNotaAmarela(int posZ){
	//reflete a cor amarela
	GLfloat zAtual = posZ + velocidadeMusica;                                               // Nova posiÃ§Ã£o da nota a cada iteraÃ§Ã£o da variÃ¡vel "velocidadeMusica"
	if(zAtual < 24){                                                                        // Se a nota passou da posiÃ§Ã£o 24 em Z, ela jÃ¡ nÃ£o Ã© mais criada
		if(selecionadaCorD > 0.99){                                                         // Se a cor selecionada for a correspondente a tecla D, avanÃ§a
	        if((zAtual > 20.75)&&(zAtual < 21.9)){                                          // Se a tecla for acionada na regiÃ£o da argola correspondente, a nota foi acertada
	        	pontuacao += 10;                                                            // Por isso, pontua-se mais 10
	        }
	    }
		GLfloat emission3[] = {0.7, 0.7, 0.0, 1.0};                                         // Desenha a esfera na cor amarela
		glMaterialfv(GL_FRONT, GL_EMISSION, emission3);
		glTranslatef(1, 0, 0.0+ posZ);
		glutSolidSphere(0.5, 20, 20);
		glTranslatef(-1, 0, 0.0 - posZ);
	}
}

// Desenha esfera azul para nota
void desenhaNotaAzul(int posZ){
	//reflete a cor azul
	GLfloat zAtual = posZ + velocidadeMusica;                                               // Nova posiÃ§Ã£o da nota a cada iteraÃ§Ã£o da variÃ¡vel "velocidadeMusica"
	if(zAtual < 24){                                                                        // Se a nota passou da posiÃ§Ã£o 24 em Z, ela jÃ¡ nÃ£o Ã© mais criada
		if(selecionadaCorF > 0.99){                                                         // Se a cor selecionada for a correspondente a tecla F, avanÃ§a
	        if((zAtual > 20.75)&&(zAtual < 21.9)){                                          // Se a tecla for acionada na regiÃ£o da argola correspondente, a nota foi acertada
	        	pontuacao += 10;                                                            // Por isso, pontua-se mais 10
	        }
	    }
		GLfloat emission4[] = {0.0, 0.0, 0.7, 1.0};                                         // Desenha a esfera na cor azul
		glMaterialfv(GL_FRONT, GL_EMISSION, emission4);
		glTranslatef(3, 0, 0.0+ posZ);
		glutSolidSphere(0.5, 20, 20);
		glTranslatef(-3, 0, 0.0 - posZ);
	}

}

// Desenha as argolas para a seleÃ§Ã£o no tempo correto de cada nota
void selecaoNotas(){
	// Desenha a argola para seleÃ§Ã£o da nota verde
	GLfloat emission1[] = {0.0, selecionadaCorA, 0.0, 0.0f};                                // Usa a variÃ¡vel "selecionadaCorA" para quando a tecla A for acionada, a argola ficar verde
	glMaterialfv(GL_FRONT, GL_EMISSION, emission1);
	glTranslatef(-3, -1, +21);                                                              // Posiciona a argola na posiÃ§Ã£o correta
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glutSolidTorus(0.1, 0.7,10, 10);
	glRotatef(90.0f,-1.0f,0.0f,0.0f);
	glTranslatef(3, 1, -21);

	// Desenha a argola para seleÃ§Ã£o da nota vermelha
	GLfloat emission2[] = {selecionadaCorS, 0.0f, 0.0, 0.0f};                               // Usa a variÃ¡vel "selecionadaCorS" para quando a tecla A for acionada, a argola ficar vermelha
	glMaterialfv(GL_FRONT, GL_EMISSION, emission2);
	glTranslatef(-1, -1, +21);                                                              // Posiciona a argola na posiÃ§Ã£o correta
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glutSolidTorus(0.1, 0.7,10, 10);
	glRotatef(90.0f,-1.0f,0.0f,0.0f);
	glTranslatef(1, 1, -21);

	// Desenha a argola para seleÃ§Ã£o da nota amarela
	GLfloat emission3[] = {selecionadaCorD, selecionadaCorD, 0.0, 0.0f};                    // Usa a variÃ¡vel "selecionadaCorD" para quando a tecla D for acionada, a argola ficar amarela
	glMaterialfv(GL_FRONT, GL_EMISSION, emission3);
	glTranslatef(1, -1, +21);                                                               // Posiciona a argola na posiÃ§Ã£o correta
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glutSolidTorus(0.1, 0.7,10, 10);
	glRotatef(90.0f,-1.0f,0.0f,0.0f);
	glTranslatef(-1, 1, -21);

	// Desenha a argola para seleÃ§Ã£o da nota azul
	GLfloat emission4[] = {0.0, 0.0, selecionadaCorF, 0.0f};                                // Usa a variÃ¡vel "selecionadaCorF" para quando a tecla A for acionada, a argola ficar azul
	glMaterialfv(GL_FRONT, GL_EMISSION, emission4);
	glTranslatef(3, -1, +21);                                                               // Posiciona a argola na posiÃ§Ã£o correta
	glRotatef(90.0f,1.0f,0.0f,0.0f);
	glutSolidTorus(0.1, 0.7,10, 10);
	glRotatef(90.0f,-1.0f,0.0f,0.0f);
	glTranslatef(-3, 1, -21);
}

// ResponsÃ¡vel por criar tudo que Ã© atualizado a cada frame mas nÃ£o Ã© movimentado
void Update(){

	desenhoEsteira(24,4.5);
	selecaoNotas();

}

void ParametrosIluminacao()
{
	// ParÃ¢metros para a Luz GL_LIGHT0 sendo uma fonte de Luz Pontual
	GLfloat luzAmbiente[4]={1.0, 1.0, 1.0, 1.0};	                                        // Cor branca
	GLfloat luzDifusa[4]={1.0, 1.0, 1.0, 1.0};	  	                                        // Cor branca
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; 	                                        // Cor branca - brilho
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};	                                        // Fonte de Luz Pontual

	//Define os parÃ¢metros da luz de nÃºmero 0 (Luz Pontual)
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	//Ativa o uso de uma fonte de luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// CaracterÃ­sticas do material
	GLfloat ka[4]={0.0, 0.0, 0.0, 1.0};		                                                // Reflete porcentagens da cor ambiente
	GLfloat kd[4]={0.2, 0.2, 0.3, 1.0};		                                                // Reflete porcentagens da cor difusa
	GLfloat ks[4]={1.0, 1.0, 1.0, 1.0};		                                                // Reflete porcentagens da cor especular
	GLfloat shininess = 100.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ks);                                       // RefletÃ¢ncia do material
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);                                         // ConcentraÃ§Ã£o do brilho
}

// FunÃ§Ã£o que chama tudo que Ã© necessÃ¡rio para aparecer na tela
void Desenha(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                                     // Limpa a janela de visualizaÃ§Ã£o com a cor de fundo especificada

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 5.0, 30.0,	                                                            // Eye
    		  0.0, -5.0, 0.0,	                                                            // Look
    		  0.0, 1.0, 0.0);	                                                            // Up

	ParametrosIluminacao();

	glScalef(tamX, tamY, tamZ);

	// Itens que NÃƒO se movem ficam antes do translate
	Update();

	
	if(nvMusica == 1){                                                                      // Se o nÃ­vel de mÃºsica selecionado Ã© fÃ¡cil, entÃ£o prossegue
		glTranslatef(0.0, 0.0, velocidadeMusica);                                           // Inicia mÃºsica em velocidade normal
	    MusicaEASY();                                                                       // Chama a mÃºsica fÃ¡cil
	}
	else if(nvMusica == 2){                                                                 // Se o nÃ­vel de mÃºsica selecionado Ã© mÃ©dio, entÃ£o prossegue
		glTranslatef(0.0, 0.0, velocidadeMusica);                                           // Inicia mÃºsica em velocidade normal
		MusicaMEDIUM_BIB();                                                                 // Chama a mÃºsica Back In Black - ACDC de nÃ­vel mÃ©dio
	}
	else if(nvMusica == 3){                                                                 // Se o nÃ­vel de mÃºsica selecionado Ã© difÃ­cil, entÃ£o prossegue
		glTranslatef(0.0, 0.0, 3*velocidadeMusica);                                         // Inicia mÃºsica com 3 vezes a velocidade normal
		MusicaHARD();                                                                       // Chama a mÃºsica difÃ­cil
	}

	if(velocidadeMusica > 92.40 && velocidadeMusica < 92.41){                               // Se a Ãºltima nota entrou no interlavo, entÃ£o prossegue
		printf("%i\n", pontuacao);                                                          // Imprime a pontuaÃ§Ã£o

		if(pontuacao > 100)             printf("YOU ROCK!!!\n");                            // Se a pontuaÃ§Ã£o for maior que 100, entÃ£o imprime "YOU ROCK!!!"
		else if(pontuacao < 0)          printf("You're loser.\n");                          // Se a pontuaÃ§Ã£o for manor que 0, entÃ£o imprime "YOU'RE LOSER"
		else                            printf("Good!\n");                                  // SenÃ£o, imprime "GOOD!"
	}

	glFlush();
}

// FunÃ§ao callback de animaÃ§Ã£o
void Anima(int value){

	velocidadeMusica += 0.01;                                                               // As notas se movem em relaÃ§Ã£o ao eixo Z com a "velocidadeMusica"

    // IFs e ELSEs responsÃ¡veis por dar uma sensaÃ§Ã£o de degradÃª ao deixar de clicar na nota
	if(teclaAtual == 'a'){                                                                  // Se a tecla pressionada for "a", entÃ£o prossegue
		if(teclaAtual != teclaUltima){
			selecionadaCorA = 1.0f;
			teclaUltima = teclaAtual;
			pontuacao -= 3;
		}
	}
	else if(teclaAtual == 's'){                                                             // Se a tecla pressionada for "s", entÃ£o prossegue
		if(teclaAtual != teclaUltima){
			selecionadaCorS = 1.0f;
			teclaUltima = teclaAtual;
			pontuacao -= 3;
		}
	}
	else if(teclaAtual == 'd'){                                                             // Se a tecla pressionada for "d", entÃ£o prossegue
		if(teclaAtual != teclaUltima){
			selecionadaCorD = 1.0f;
			teclaUltima = teclaAtual;
			pontuacao -= 3;
		}
	}
	else if(teclaAtual == 'f'){                                                             // Se a tecla pressionada for "f", entÃ£o prossegue
		if(teclaAtual != teclaUltima){
			selecionadaCorF = 1.0f;
			teclaUltima = teclaAtual;
			pontuacao -= 3;
		}
	}
	if(selecionadaCorA > 0.0f){
		selecionadaCorA -= velocidadeAnimacao;
	}else{
		teclaUltima = 'k';
		teclaAtual = 'm';
	}

	if(selecionadaCorS > 0.0f){
		selecionadaCorS -= velocidadeAnimacao;
	}else{
		teclaUltima = 'k';
		teclaAtual = 'm';
	}

	if(selecionadaCorD > 0.0f){
		selecionadaCorD -= velocidadeAnimacao;
	}else{
		teclaUltima = 'k';
		teclaAtual = 'm';
	}

	if(selecionadaCorF > 0.0f){
		selecionadaCorF -= velocidadeAnimacao;
	}else{
		teclaUltima = 'k';
		teclaAtual = 'm';
	}
	/////////////////////////////////////
	glutPostRedisplay();
	glutTimerFunc(1, Anima, 1);
}

// Recebe entradas do teclado
void GerenciaTeclado(unsigned char teclaPressionada, int x, int y){

	teclaAtual = teclaPressionada;                                                          // Tecla atual Ã© recebe a Ãºltima tecla pressionada

	// NecessÃ¡rio chamar toda vez que se faz uma alteraÃ§Ã£o ou evento na janela
    glutPostRedisplay();
}

// FunÃ§Ã£o de InicializaÃ§Ã£o
void Inicializa(){

	// Define a cor de fundo da janela de visualizaÃ§Ã£o como preta
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Modo de projecao ortogonal (Default)
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0f, ((GLfloat)LARGURA/(GLfloat)ALTURA), 1, 50.0f);

	// Habilita o uso de iluminaÃ§Ã£o
	glEnable(GL_LIGHTING);
	// Habilita a luz de nÃºmero 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering para remoÃ§Ã£o de faces escondidas
	glEnable(GL_DEPTH_TEST);

	// Modelos de IluminaÃ§Ã£o Defaut
	glShadeModel(GL_SMOOTH);										                        // Gouraud
}

// ResponsÃ¡vel por receber as entradas 
void keyboard(int key, int x, int y)
{
    switch (key) {
		case GLUT_KEY_UP:	                                                                // Caso a tecla pressionada for a seta de cima o tamanho do jogo aumenta
			tamX += 0.1;                                                                    
			tamY += 0.1;
			tamZ += 0.1;
			break;

		case GLUT_KEY_DOWN:	                                                                // Caso a tecla pressionada for a seta de baixo o tamanho do jogo diminui
			tamX -= 0.1;
			tamY -= 0.1;
			tamZ -= 0.1;
			break;

		case 27:                                                                            // Caso clique no botÃ£o do menu "Sair", a tela fecha
            exit(0);
            break;	
    }

    // NecessÃ¡rio chamar toda vez que se faz uma alteraÃ§Ã£o ou evento na janela
   	glutPostRedisplay();
}

// ResponsÃ¡vel por obter as informaÃ§Ãµes pelo sub-menu "Musicas".
void menuMusicas(int escolhaMusica){

	switch(escolhaMusica){
		case 1:                                                                             // Caso a mÃºsica escolhida seja a fÃ¡cil, entÃ£o prossegue
			if(nvMusica == 1)                                                               // Se a mÃºsica atual jÃ¡ a de nÃ­vel fÃ¡cil, entÃ£o prossegue
				nvMusica = 1;                                                               // A mÃºsica continua a mesma e sem a necessidade de voltar ao inÃ­cio
			else if(nvMusica == 2){                                                         // Se a mÃºsica atual Ã© a mÃ©dia, entÃ£o prossegue
				nvMusica = 1;                                                               // Seta a mÃºsica atual para ser a fÃ¡cil
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}
			else if(nvMusica == 3){                                                         // Se a mÃºsica atual Ã© a difÃ­cil, entÃ£o prossegue
				nvMusica = 1;                                                               // Seta a mÃºsica atual para ser a fÃ¡cil
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}

			break;

		case 2:                                                                             // Caso a mÃºsica escolhida seja a mÃ©dia, entÃ£o prossegue
			if(nvMusica == 1){                                                              // Se a mÃºsica atual Ã© a fÃ¡cil, entÃ£o prossegue
				nvMusica = 2;                                                               // Seta a mÃºsica atual para ser a mÃ©dia
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}
			else if(nvMusica == 2)                                                          // Se a mÃºsica atual jÃ¡ a de nÃ­vel mÃ©dia, entÃ£o prossegue
				nvMusica = 2;                                                               // A mÃºsica continua a mesma e sem a necessidade de voltar ao inÃ­cio
			else if(nvMusica == 3){                                                         // Se a mÃºsica atual Ã© a difÃ­cil, entÃ£o prossegue
				nvMusica = 2;                                                               // Seta a mÃºsica atual para ser a mÃ©dia
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}	

			break;

		case 3:                                                                             // Caso a mÃºsica escolhida seja a difÃ­cil, entÃ£o prossegue
			if(nvMusica == 1){                                                              // Se a mÃºsica atual Ã© a fÃ¡cil, entÃ£o prossegue
				nvMusica = 3;                                                               // Seta a mÃºsica atual para ser a difÃ­cil
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}
			else if(nvMusica == 2){                                                         // Se a mÃºsica atual Ã© a mÃ©dia, entÃ£o prossegue
				nvMusica = 3;                                                               // Seta a mÃºsica atual para ser a difÃ­cil
				velocidadeMusica = 0;                                                       // ComeÃ§a do inicÃ­o
			}
			else if(nvMusica == 3)                                                          // Se a mÃºsica atual jÃ¡ a de nÃ­vel difÃ­cil, entÃ£o prossegue
				nvMusica = 3;                                                               // A mÃºsica continua a mesma e sem a necessidade de voltar ao inÃ­cio

			break;

		case 4:                                                                             // Caso selecionada a opÃ§Ã£o de reiniciar mÃºsica, entÃ£o prossegue
			velocidadeMusica = 0;                                                           // Volta ao inÃ­cio
			break;
	}
}

// ResponsÃ¡vel por obter as informaÃ§Ãµes pelo sub-menu "Zoom".
void menuEscalaJogo(int op){
    switch(op){
        case 1:                                                                             // Caso a primeira opÃ§Ã£o seja selecionada, entÃ£o prossegue
            keyboard(GLUT_KEY_UP, 1, 1);                                                    // Opera tal qual a tecla UP, na funÃ§Ã£o "keyboard()"
            break;
        case 2:                                                                             // Caso a segunda opÃ§Ã£o seja selecionada, entÃ£o prossegue
            keyboard(GLUT_KEY_DOWN, 1, 1);                                                  // Opera tal qual a tecla DOWN, na funÃ§Ã£o "keyboard()"
            break;
    }
}

// ResponsÃ¡vel por obter as informaÃ§Ãµes pelo menu principal
void menuPrincipal(int op) {
    switch(op){
        case 1:                                                                             // Caso a primeira opÃ§Ã£o seja selecionada, entÃ£o prossegue
            keyboard(27, 1, 1);                                                             // Opera tal qual o inteiro 27, na funÃ§Ã£o "keyboard()"
            break;
    }
}

// ResponsÃ¡vel por criar o menu
void criaMenu(){
    int subMenu1 = glutCreateMenu(menuEscalaJogo);                                          // Cria sub-menu "Zoom"
    glutAddMenuEntry("Zoom +", 1);                                                          // Aumentar zoom = opÃ§Ã£o 1
    glutAddMenuEntry("Zoom -", 2);                                                          // Aumentar zoom = opÃ§Ã£o 2
    int subMenu2 = glutCreateMenu(menuMusicas);                                             // Cria sub-menu "Musicas"
    glutAddMenuEntry("Facil", 1);                                                           // MÃºsica fÃ¡cil = opÃ§Ã£o 1
    glutAddMenuEntry("Medio", 2);                                                           // MÃºsica mÃ©dia (Back In Black - ACDC) = opÃ§Ã£o 2
    glutAddMenuEntry("Dificil", 3);                                                         // MÃºsica difÃ­cil = opÃ§Ã£o 3
    glutAddMenuEntry("Reiniciar Musica", 4);                                                // Reiniciar mÃºsica = opÃ§Ã£o 4
    int menu = glutCreateMenu(menuPrincipal);                                               // Cria Menu Principal
    glutAddSubMenu("Zoom", subMenu1);                                                       // Chama o sub-menu "Zoom"
    glutAddSubMenu("Musica", subMenu2);                                                     // Chama o sub-menu "Musica"
    glutAddMenuEntry("Exit (ESC)", 1);                                                      // Fechar tela = opÃ§Ã£o 1
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (LARGURA, ALTURA);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Ukulele Hero");
	glutDisplayFunc(Desenha);
	glutKeyboardFunc(GerenciaTeclado);
	glutSpecialFunc(keyboard);
	criaMenu();
	Inicializa();
	glutTimerFunc(500, Anima, 1);
	glutMainLoop();
	return 0;

}
