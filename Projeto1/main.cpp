//#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif
#include "bitmapload.hpp"
#include <iostream>
#include "main.h"
#include "mygl.h"
#include "definitions.h"
#include <stdlib.h>
#include <vector>




//-----------------------------------------------------------------------------


void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
/**Cores para testes*/

switch(option){ //alterna modo de exibição da imagem
case 0:
DrawTela();//imprime imagem normal
break;
case 1:
DrawTelaN();//imprime a imagem negativa
break;
case 2:
DrawTelaGS();//imprime a imagem em escala de cinza
break;
case 3:
DrawTelaR();//imprime a imagem só com o canal red ativo
break;
case 4:
DrawTelaG();//imrpime a imagem só com o canal green ativo
break;
case 5:
DrawTelaB();//imprime a imagem só com o canal blue ativo
}

}

//-----------------------------------------------------------------------------
int main(int argc, char **argv){
	// Inicializações.
	InitOpenGL(&argc, argv);
	InitCallBacks();
	glutSpecialFunc(TeclasEspeciais);
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}

