#include <iostream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include <opencv/cv.h>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;


int main()
{
    Mat src,dst,dst2,th_binario,umbral1,umbral2,th_binario_inv,resultado;
    int a;
    src=imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\009.jpg");
    cvtColor(src,dst,CV_BGR2GRAY);
    namedWindow("Imagen Original",WINDOW_NORMAL);
    namedWindow("Imagen Gray",WINDOW_NORMAL);
    imshow("Imagen Original",src);
    imshow("Imagen Gray",dst);

    threshold(dst,th_binario,70,255,0);
   //namedWindow("Imagen Binario",WINDOW_NORMAL);
   //imshow("Imagen Binario",th_binario);

   namedWindow("Umbral 1",WINDOW_NORMAL);
   imshow("Umbral 1",th_binario);

   threshold(dst,th_binario_inv,100,255,1);
   namedWindow("Umbral 2",WINDOW_NORMAL);
   imshow("Umbral 2",th_binario_inv);

   resultado=(th_binario) & th_binario_inv;
   namedWindow("Filtro Umbral",WINDOW_NORMAL);
   imshow("Filtro Umbral",resultado);

   inRange(src,Scalar(20,0,128),Scalar(25, 2, 145), dst2);
   namedWindow("Filtro",WINDOW_NORMAL);
   imshow("Filtro",dst2);
   //

    waitKey(0);
}
