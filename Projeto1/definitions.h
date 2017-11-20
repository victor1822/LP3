#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_

#define IMAGE_WIDTH  512 // número de colunas da imagem.
#define IMAGE_HEIGHT 512 // número de linhas da imagem.

unsigned char * FBptr;
unsigned char * IMGptr;
unsigned char * Sptr;
unsigned char * TMPptr;
//int alfa=1; int beta=0; Brilho e contraste
int option = 0;
double limiar = 180;
int diferencial=60;
clock_t Ticks[2];
double Tempo;

#endif // _DEFINITIONS_H_

