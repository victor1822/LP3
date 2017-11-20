#ifndef _MYGL_H_
#define _MYGL_H_
#include <stdlib.h>
#include <math.h>
#include "definitions.h"
#include <vector>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

//Mat inputImage, outputImage, channel[3];
//std::string colorSpace;

using namespace std;
//subrotinas simples
int mod_(int v){
if(v<0)v*=-1;
return v;
}
int max_(int a,int b){
if(a>=b)return a;
else return b;
}
int min_(int a,int b){
if(a<=b)return a;
else return b;
}

void ab(int v){ //AJUSTA BRILHO ADITIVO
int tmp=0;
int x,y,offset;/*
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=FBptr[offset+3]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+3]=(unsigned char)tmp;
//FBptr[offset+3]=(unsigned char)tmp;

}
}*/
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=IMGptr[offset+0]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+0]=tmp;
tmp=IMGptr[offset+1]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+1]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;

}
}
}

void abm(int v){ //AJUSTA BRILHO MULTIPLICATIVO
double tmp=0;
int x,y,offset;
/*
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
if(v>0)tmp=FBptr[offset+3]*2;
if(v<0)tmp=FBptr[offset+3]/2;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+3]=(unsigned char)tmp;
//FBptr[offset+3]=(unsigned char)tmp;
}
}*/
int i=-9;
while(i<v){
i++;
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=IMGptr[offset+0]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+0]=tmp;
tmp=IMGptr[offset+1]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+1]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;

}
}
}
}




void aplica_contraste(){


double tmp=0;
int x,y,offset;
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp = IMGptr[offset+0]+IMGptr[offset+1]+IMGptr[offset+2]/3;
if(tmp>limiar){
tmp=FBptr[offset+3]+diferencial;
if(tmp>255)tmp=255;
IMGptr[offset+3]=tmp;
}else{
tmp=IMGptr[offset+3]-diferencial;
if(tmp<0)tmp=0;
IMGptr[offset+3]=tmp;
}

}
}

}

void altera_limiar(int v){
limiar=limiar+v;
aplica_contraste();
}

void altera_diferencial(int v){
diferencial=diferencial+v;
aplica_contraste();
}

void soma_imagem(){
double tr,tg,tb,ta;
int x,y,offset;

for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
offset = 4*x + 4*y*IMAGE_WIDTH;

tr=(IMGptr[offset+0]+Sptr[offset+0])/2;
tg=(IMGptr[offset+1]+Sptr[offset+1])/2;
tb=(IMGptr[offset+2]+Sptr[offset+2])/2;
ta=(IMGptr[offset+3]+Sptr[offset+3])/2;

IMGptr[offset+0]=(double)tr;
IMGptr[offset+1]=(double)tg;
IMGptr[offset+2]=(double)tb;
//IMGptr[offset+3]=(double)ta;

}
}
}

void ajusta_negativo(unsigned char v){//ALTERA BRILHO DA IMAGEM NO FRAMEBUFFER
unsigned char tmp=0;
int x,y,offset;
for(x=0;x<IMAGE_WIDTH;x++){
for(y=0;y<IMAGE_HEIGHT;y++){
int offset = 4*x + 4*y*IMAGE_WIDTH;
tmp=IMGptr[offset+0]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+0]=tmp;
tmp=IMGptr[offset+1]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+1]=tmp;
tmp=IMGptr[offset+2]+v;
if (tmp>255) tmp=255;
if (tmp<0) tmp=0;
IMGptr[offset+2]=tmp;

}
}
 
}



//========================= classes ============================
class cor{
private:
unsigned char r;
unsigned char g;
unsigned char b;
unsigned char a;
public:
cor(){
r=0;
g=0;
b=0;
a=0;
}
void set_color(unsigned char r_,unsigned char g_,unsigned char b_,unsigned char a_)
{
r=r_;
g=g_;
b=b_;
a=a_;
}
unsigned char get_r(){return r;}
unsigned char get_g(){return g;}
unsigned char get_b(){return b;}
unsigned char get_a(){return a;}
};

class ponto{
private:
int x;
int y;
public:
ponto()
{
    x=0;
    y=0;
}
void set_x_y(int x_,int y_)
{
x=x_;
y=y_;
}
int get_x(){return x;}
int get_y(){return y;}
};


void aplica_media(){
	Mat mat(512, 512, CV_8UC4);
	createAlphaMat(mat);
	
    //media

	createAlphaMat(mat);

	blur(mat,mat,Size(5,5));

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {

            Vec4b& rgba = mat.at<Vec4b>(i,j);//-(j-511)
			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0] = saturate_cast<uchar>((unsigned char)rgba[0]);
		IMGptr[offset+1] = saturate_cast<uchar>((unsigned char)rgba[1]);
		IMGptr[offset+2] = saturate_cast<uchar>((unsigned char)rgba[2]);           
		IMGptr[offset+3] = saturate_cast<uchar>((unsigned char)rgba[3]);	
        }
    } 	
}


void aplica_mediana(){

	Mat mat(512, 512, CV_8UC4);
	createAlphaMat(mat);
    //mediana
	createAlphaMat(mat);
		
	medianBlur(mat,mat,5);

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {

            Vec4b& rgba = mat.at<Vec4b>(i,j);//-(j-511)
			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		IMGptr[offset+0] = saturate_cast<uchar>((unsigned char)rgba[0]);
		IMGptr[offset+1] = saturate_cast<uchar>((unsigned char)rgba[1]);
		IMGptr[offset+2] = saturate_cast<uchar>((unsigned char)rgba[2]);           
		IMGptr[offset+3] = saturate_cast<uchar>((unsigned char)rgba[3]);		
        }   }	}


void aplica_GaussianNoise(){

	Mat mat(512, 512, CV_8UC4);
	//Mat result(512, 512, CV_8UC4);
	createAlphaMat(mat);

//=========== 
	
    //Gaussiano

	createAlphaMat(mat);
	Mat noise = Mat(mat.size(),CV_64F);
	randn(noise, 128, 30);
	double r,g,b;
	normalize(noise, noise, 0.0, 1.0, CV_MINMAX, CV_64F);

    for (int i = 0; i < IMAGE_WIDTH; ++i) {
        for (int j = 0; j < IMAGE_HEIGHT; ++j) {

            Vec4b& rgba = mat.at<Vec4b>(i,j);//-(j-511)
		Vec4b& rgba2 = noise.at<Vec4b>(i,j);//-(j-511)
			int offset= 4*i + 4*j*IMAGE_WIDTH;	
		r = saturate_cast<uchar>((rgba[0]+rgba2[0])/2);
		g = saturate_cast<uchar>((rgba[1]+rgba2[1])/2);
		b = saturate_cast<uchar>((rgba[2]+rgba2[2])/2);           
		if(r>255)r=255;
		if(r<0)r=0;
		if(g>255)g=255;
		if(g<0)g=0;
		if(b>255)b=255;
		if(b<0)b=0;
		IMGptr[offset+0]=r;
		IMGptr[offset+1]=g;
		IMGptr[offset+2]=b;
        }
    } 	
} 


void convert_RGB2YUVNSAVE(){
	Mat mat(512, 512, CV_8UC4);
	Mat matyuv(512, 512, CV_8UC4);
	Mat maty(512, 512, CV_8UC4);
	Mat matu(512, 512, CV_8UC4);
	Mat matv(512, 512, CV_8UC4);
	Mat inputImage(512, 512, CV_8UC4);

//=========== 
	
    //Conver a imagem para o espaço de cor YCrCb e salva os resultados separados em arquivos distintos.

	createAlphaMat(mat);
	//mat.convertTo(mat, -1, 1, 255-FBptr[3]);
	inputImage=mat.clone();

	//Salva YUV
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(100);//qualidade da imagem entre 0 e 120
	
	    try {
	 
        imwrite("yuv.jpeg", mat, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        return;
    }

    fprintf(stdout, "Saved JPEG file with alpha data.\n");
	cout<<"Arquivo Salvo"<<endl;


	Mat channel[3];

	cvtColor(inputImage, inputImage, COLOR_BGR2YCrCb);
	split(inputImage, channel);
	//showChannels(channel, hsv_labels, std_values, COLOR_YCrCb2BGR);

	Mat outputImage(512, 512, CV_8UC4);
	Mat aux[3];

//y
		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;    //retorna matriz de 1=Mat[3]= {1,1,1}
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;//{127.5,127.5,127.5}
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;//{127.5,127.5,127.5}
		aux[0] = channel[0];//canal y  
		// merge() une os canais de volta em output
		merge(aux, 3, outputImage);
//output image recebe os valores de aux[0] para seu primeiro canal, aux[1] para o segundo e aux[2] para o terceiro
		// convert from output color space to BGR

		cvtColor(outputImage, maty, COLOR_YCrCb2BGR);//converte para rgb

	    try {
        imwrite("y.jpeg", maty, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        return;
    }

    fprintf(stdout, "Saved JPEG file with y data.\n");
	cout<<"Arquivo y Salvo"<<endl;


//u
		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = channel[1];  

		merge(aux, 3, outputImage);
	
		cvtColor(outputImage, matu, COLOR_YCrCb2BGR);

	    try {
        imwrite("u.jpeg", matu, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        return;
    }

    fprintf(stdout, "Saved JPEG file with u data.\n");
	cout<<"Arquivo u Salvo"<<endl;

//v


		aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 127.5;
		aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * 1;
		aux[2] = channel[2];  

		merge(aux, 3, outputImage);

		cvtColor(outputImage, matv, COLOR_YCrCb2BGR);

	    try {
        imwrite("v.jpeg", matv, compression_params);
    }
    catch (runtime_error& ex) {
        fprintf(stderr, "Exception converting image to JPEG format: %s\n", ex.what());
        return;
    }

    fprintf(stdout, "Saved JPEG file with v data.\n");
	cout<<"Arquivo v Salvo"<<endl;	
}

//==============================================================

//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
void PutPixel(cor color,ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
unsigned char red = color.get_r();
unsigned char green = color.get_g();
unsigned char blue = color.get_b();
unsigned char alfa = color.get_a();
int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = green;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}


int ni=4;

void PutPixel2(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
double red =  IMGptr[offset2+0];
double green = IMGptr[offset2+1];
double blue =  IMGptr[offset2+2];
double alfa = IMGptr[offset2+3];

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = (unsigned char)red;
FBptr[offset + 1] = (unsigned char)green;
FBptr[offset + 2] = (unsigned char)blue;
FBptr[offset + 3] = (unsigned char)alfa;
}

void PutPixelRed(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =  IMGptr[offset2+0];
unsigned char alfa = IMGptr[offset2+3];

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = 0;
FBptr[offset + 2] = 0;
FBptr[offset + 3] = alfa;
}

void PutPixelGreen(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;

unsigned char green = IMGptr[offset2+1];
unsigned char alfa = IMGptr[offset2+3];

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = 0;
FBptr[offset + 1] = green;
FBptr[offset + 2] = 0;
FBptr[offset + 3] = alfa;
}

void PutPixelBlue(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;

unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = 0;
FBptr[offset + 1] = 0;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}


void PutPixelGrayScale(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =  IMGptr[offset2+0];
unsigned char green = IMGptr[offset2+1];
unsigned char blue =  IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];
unsigned char gs=floor((float)(red+green+blue)/3);

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = gs;
FBptr[offset + 1] = gs;
FBptr[offset + 2] = gs;
FBptr[offset + 3] = alfa;
}

void PutPixelNegativo(ponto p0)
{
int _x = p0.get_x();
int _y = p0.get_y();
int offset2 = ni*_y+ni*_x*IMAGE_WIDTH;
unsigned char red =   255 - IMGptr[offset2+0];
unsigned char green = 255 - IMGptr[offset2+1];
unsigned char blue =  255 - IMGptr[offset2+2];
unsigned char alfa = IMGptr[offset2+3];

int offset = 4*_x + 4*_y*IMAGE_WIDTH;
FBptr[offset + 0] = red;
FBptr[offset + 1] = green;
FBptr[offset + 2] = blue;
FBptr[offset + 3] = alfa;
}

void DrawTela(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixel2(px);
    }
}
}

void DrawTelaR(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelRed(px);
    }
}
}

void DrawTelaG(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelGreen(px);
    }
}
}

void DrawTelaB(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelBlue(px);
    }
}
}

void DrawTelaGS(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelGrayScale(px);
    }
}
}

void DrawTelaN(){
    ponto px;
for(int x=0;x<IMAGE_HEIGHT;x++){
    for(int y=0;y<IMAGE_WIDTH;y++){
    px.set_x_y(x,y);
    PutPixelNegativo(px);
    }
}
}


void AtribuiValorH(double h[3][3],double a1,double a2,double a3,double a4, double a5,double a6,double a7,double a8,double a9){
h[0][0]=a1;h[0][1]=a2;h[0][2]=a3; 
h[1][0]=a4;h[1][1]=a5;h[1][2]=a6;
h[2][0]=a7;h[2][1]=a8;h[2][2]=a9;
}

void Normaliza(double h[3][3]){
double soma=h[0][0]+h[0][1]+h[0][2]+ h[1][0]+h[1][1]+h[1][2]+h[2][0]+h[2][1]+h[2][2];
h[0][0]=h[0][0]/soma;
h[0][1]=h[0][1]/soma;
h[0][2]=h[0][2]/soma;
h[1][0]=h[1][0]/soma;
h[1][1]=h[1][1]/soma;
h[1][2]=h[1][2]/soma;
h[2][0]=h[2][0]/soma;
h[2][1]=h[2][1]/soma;
h[2][2]=h[2][2]/soma;
}


void ImprimeMatriz(double mask[3][3]){

cout<<"h="<<endl;
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
cout<<" "<<mask[i][j];
}
cout<<endl;
}

}


void Rebatimento(double mask[3][3]){
cout<<"Matriz Inicial"<<endl;
ImprimeMatriz(mask);
double tmp[3][3];
int k;
for(int i=0;i<3;i++){
k=2;
for(int j=0;j<3;j++){
tmp[i][j]=mask[i][k];
k--;
}
}
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
mask[i][j]=tmp[i][j];
}
}
cout<<"Matriz media"<<endl;
ImprimeMatriz(mask);
for(int i=0;i<3;i++){
k=2;
for(int j=0;j<3;j++){
tmp[j][i]=mask[k][i];
k--;
}
}
for(int i=0;i<3;i++){
for(int j=0;j<3;j++){
mask[i][j]=tmp[i][j];
}
}
cout<<"Matriz Final"<<endl;
ImprimeMatriz(mask);
}

void AplicaConvolucao(double mask[3][3]){
Rebatimento(mask);
int offset;
int s,t;
double a11,a12,a13,a21,a22,a23,a31,a32,a33;
unsigned char buffer[IMAGE_WIDTH][IMAGE_HEIGHT][3];
unsigned char tmpbuffer[IMAGE_WIDTH][IMAGE_HEIGHT][3];

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
for(int k=0;k<3;k++){
offset = 4*i + 4*j*IMAGE_WIDTH;
buffer[i][j][k]=IMGptr[offset+k];
}}}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
//offset = 4*i + 4*j*IMAGE_WIDTH;
for(int k=0;k<3;k++){

if(i!=0&&i!=IMAGE_HEIGHT&&j!=0&&j!=IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];
}
if(i==0){
if(j==IMAGE_WIDTH){
a11=0;a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=0;a33=0;
}
if(j==0){

a11=0;a12=0;a13=0;
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];

}
if(j!=0&&j!=IMAGE_WIDTH){
a11=0;a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];

}
}
if(i==IMAGE_WIDTH){
if(j==0){
a11=0;a12=0;a13=0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=0;
}
if(j==IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=0;a32=0;a33=0;
}
if(j!=0&&j!=IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];a13=0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=0;

}
}
int temp;
temp=a11*mask[0][0]+a12*mask[0][1]+a13*mask[0][2]+a21*mask[1][0]+a22*mask[1][1]+a23*mask[1][2]+a31*mask[2][0]+a32*mask[2][1]+a33*mask[2][2];
if(temp<0){temp=0;}
if(temp>255){temp=255;}
tmpbuffer[i][j][k]=temp;
}
}
}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
for(int k=0;k<3;k++){
offset = 4*i + 4*j*IMAGE_WIDTH;
IMGptr[offset+k]=tmpbuffer[i][j][k];
}}}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
offset = 4*i + 4*j*IMAGE_WIDTH;
IMGptr[offset]=TMPptr[offset];
}}

}

void AplicaMedia(double h[3][3]){
AtribuiValorH(h,
(double)1/9,(double)1/9,(double)1/9,
(double)1/9,(double)1/9,(double)1/9,
(double)1/9,(double)1/9,(double)1/9);
AplicaConvolucao(h);
}

void AplicaMedia2(double h[3][3]){
AtribuiValorH(h,
(double)1/9,(double)1/9,(double)1/9,
(double)1/9,(double)1/9,(double)1/9,
(double)1/9,(double)1/9,(double)1/9);
AplicaConvolucao(h);
AplicaConvolucao(h);
}


double Ordena(double mask[3][3])
{
vector<double> v;
	for(int i=0;i<3;i++){
	for(int j=0;j<3;j++){
	for(int k=0;k<9;k++){
	if(mask[i][j]!=0)
	v.push_back(mask[i][j]);}}}
	    int tmp,tmp1;
for(int i=1;i<v.size()-1;i++){
   tmp=v[i];
   int j=i;
   while( j>0 && v[j-1]>tmp){
    v[j]=v[j-1];
    j--;
    v[j]=tmp;
   }
}	
return v[v.size()-2/2];
}


void conv_mediana(double h[3][3]){
vector<double> vetor;
AtribuiValorH(h,
1,1,1,
1,1,1,
1,1,1);
int s,t;
double a11,a12,a13,a21,a22,a23,a31,a32,a33;
unsigned char buffer[IMAGE_WIDTH][IMAGE_HEIGHT][3];
unsigned char tmpbuffer[IMAGE_WIDTH][IMAGE_HEIGHT][3];

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
for(int k=0;k<3;k++){
int offset = 4*i + 4*j*IMAGE_WIDTH;
buffer[i][j][k]=IMGptr[offset+k];
}}}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
//offset = 4*i + 4*j*IMAGE_WIDTH;
for(int k=0;k<3;k++){

if(i!=0&&i!=IMAGE_HEIGHT&&j!=0&&j!=IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];
}
if(i==0){
if(j==IMAGE_WIDTH){
a11=0;a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=0;a33=0;
}
if(j==0){

a11=0;a12=0;a13=0;
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];

}
if(j!=0&&j!=IMAGE_WIDTH){
a11=0;a12=buffer[i][j-1][k];a13=buffer[i+1][j-1][k];
a21=0;a22=buffer[i][j][k];a23=buffer[i+1][j][k];
a31=0;a32=buffer[i][j+1][k];a33=buffer[i+1][j+1][k];

}
}
if(i==IMAGE_WIDTH){
if(j==0){
a11=0;a12=0;a13=0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=0;
}
if(j==IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=0;a32=0;a33=0;
}
if(j!=0&&j!=IMAGE_WIDTH){
a11=buffer[i-1][j-1][k];a12=buffer[i][j-1][k];a13=0;
a21=buffer[i-1][j][k];a22=buffer[i][j][k];a23=0;
a31=buffer[i-1][j+1][k];a32=buffer[i][j+1][k];a33=0;

}
}
double temp;
AtribuiValorH(h,
a11,a12,a13,
a21,a22,a23,
a31,a32,a33);

temp=Ordena(h);
if(temp<0){temp=0;}
if(temp>255){temp=255;}
tmpbuffer[i][j][k]=temp;
}
}
}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
for(int k=0;k<3;k++){
int offset = 4*i + 4*j*IMAGE_WIDTH;
IMGptr[offset+k]=tmpbuffer[i][j][k];
}}}

for(int i=0;i<IMAGE_WIDTH;i++){
for(int j=0;j<IMAGE_HEIGHT;j++){
int offset = 4*i + 4*j*IMAGE_WIDTH;
IMGptr[offset]=TMPptr[offset];
}}

}


void DrawLine(ponto p0,cor c0,ponto p1,cor c1)//p0 e sua respectiva cor cor, p1 e suacor.
{
    //para espelhar defini alguns ifs com algumas condições especificas para determinar
    //o quadrante que a reta se encontrava e setei um valor especifico de flag, para realizar
    //as operações inversas antes de passar as coordenadas x,y para o putpixel e o calculo do
    //offset para ser impresso no local aproximado em que sua reta é descrita matematicamente.

//variaveis para os casos de dx<dy para poder usar o segundo octante
int flag=0;
int temp;
int ft=0;//se mudar os pontos, muda as cores, muda as cores dos pixel iniciais pintados na tela
cor ct;//caso precise inverter a cor
//cores de entrada
float ri,gi,bi,ai,rf,gf,bf,af;
//variacao da cor da linha
float r_var,g_var,b_var,a_var;

ponto pxy;//para o loop
    //Po(x0,y0)
int x0=p0.get_x();
int y0=p0.get_y();
    //P1(x1,y1)
int x1=p1.get_x();
int y1=p1.get_y();
    //variação de x e de y
int dx = x1 - x0;
int dy = y1 - y0;

if(dy<0){
temp=x0;
x0=x1;
x1=temp;
temp=y0;
y0=y1;
y1=temp;
dx = x1 - x0;
dy = y1 - y0;
ct=c0;
c0=c1;
c1=ct;
ft=1;//flag de mudança de cor
}

if(dx<0&&dy>=0&&mod_(dx)>=mod_(dy)){flag+=2;
x0*=-1;
x1*=-1;
dx = x1 - x0;
dy = y1 - y0;
}

if(dx<dy&&dx>=0){
flag++;//caso o dx>dy, com x e y positivos, temos o segundo octante,
//flag serve para inverter o x pelo y na hora de chamar PutPixel(cor,ponto);
//troca x por y nos dois pontos e recalcula tudo normal
temp=x0;/**troca x pelo y**/
x0=y0;//x0 recebe y0
y0=temp;//y0 recebe x0
temp=x1;
x1=y1;//x1 recebe y1
y1=temp;//y1 recebe x1
dx = x1 - x0;// recalcula os valores de dx e dy
dy = y1 - y0;
}

if(dx<0&&dy>=0&&mod_(dx)<mod_(dy)){
flag+=5;
temp=x0;/**troca x pelo y**/
x0=y0;//x0 recebe y0
y0=temp;//y0 recebe x0
temp=x1;
x1=y1;//x1 recebe y1
y1=temp;//y1 recebe x1
x0*=-1;
x1*=-1;
x1+=512;
x0+=512;
dx = x1 - x0;
dy = y1 - y0;
if(dy<0){
temp=x0;
x0=x1;
x1=temp;
temp=y0;
y0=y1;
y1=temp;
dx = x1 - x0;
dy = y1 - y0;
ct=c0;
c0=c1;
c1=ct;
ft=1;//flag de mudança de cor
}
}
//cor de p0
ri=c0.get_r();
gi=c0.get_g();
bi=c0.get_b();
ai=c0.get_a();
//cor de p1
rf=c1.get_r();
gf=c1.get_g();
bf=c1.get_b();
af=c1.get_a();
//variação de cor
r_var=(float)(rf-ri)/(dx+0.00001);//+0.00001para evitar divisão por zero
g_var=(float)(gf-gi)/(dx+0.00001);
b_var=(float)(bf-bi)/(dx+0.00001);
a_var=(float)(af-ai)/(dx+0.00001);
//variavel de decisão para acender o pixel d
int dnew=2*dy-dx;//primeira variavel de decisão
int d_new;
int inc_e=2*dy;
int inc_ne=2*(dy-dx);
d_new=2*dy-dx;//primeiro dold
int x=x0;int y=y0;
cor cl;ponto pl;
//pinta pontos limite com cores invertidas ou não, dependendo do valor da flag de cor
if(ft==0){
PutPixel(c0,p0);
PutPixel(c1,p1);}
if(ft==1&&flag!=5){
PutPixel(c0,p1);
PutPixel(c1,p0);}
for(int i=x;i<x1;i++){
   if(d_new<=0){
    d_new+=inc_e;
    x++;
   }
   else{
    d_new+=inc_ne;
    x++;
    y++;
   }
   //variação das cores
    ri+=r_var;
    gi+=g_var;
    bi+=b_var;
    ai+=a_var;
   cl.set_color(ri,gi,bi,ai);
   if(flag==0){
    pl.set_x_y(x,y);
   }
   if(flag==1){
    pl.set_x_y(y,x);
   }
   if(flag==2){
    pl.set_x_y(-x,y);
   }
   if(flag==5){
    pl.set_x_y(y,-x+512);
   }
   PutPixel(cl,pl);
}
}




#endif // _MYGL_H_

