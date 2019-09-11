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
    Mat src,dst,dst2,hsv,hsi,dst3,dst4,dst5,dst6;
    Mat h1,h2,resultado, resultado2,resultado3,resultado4,resultado5,resultado6;
//    Mat lower_blue [1][3];
  //  Mat upper_blue [1][3];
   //  Mat_<float>h3,h4,h5,h6,h7,h8,h9,h10,den,num,val_nitidez;
     Mat_<double>p1;
    vector<Mat> RGB(3), min_val(3),HSV(3),inv(3);//creo la matriz para los canales
    src = imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\f2.jpg");

    cvtColor(src, hsv, CV_RGB2HSV);
    cvtColor(src, hsi, CV_RGB2HLS);

    split(src,RGB);//divido

    namedWindow("Imagen Original",WINDOW_NORMAL);
    imshow("Imagen Original",src);
 //   imshow("HSV",hsv);
 //   imshow("HSI",hsi);

    //Filtro para Uvas
    inRange(hsv,Scalar(45,00,185),Scalar(95,235,255), dst);//verdes

    //Filtro para Uvas2
    inRange(hsv,Scalar(20,0,100),Scalar(90,80,240), dst4);//verdes

    //Filtro para Durazno1
    inRange(hsv,Scalar(115,100,110),Scalar(130,255,255), dst2);//

    //Filtro para Durazno2
    inRange(hsv,Scalar(105,120,248),Scalar(115,255,255), dst3);//


   //aplico bitwise para Uvas
    bitwise_and(src,src, resultado,dst=dst);

    //aplico bitwise para Uvas
     bitwise_and(src,src, resultado4,dst4=dst4);

    //aplico bitwise para Durazno1
     bitwise_and(src,src, resultado2,dst2=dst2);

     //aplico bitwise para Durazno2
      bitwise_and(src,src, resultado3,dst3=dst3);

     //Grafico

   namedWindow("Uvas",WINDOW_NORMAL);
   imshow("Uvas",resultado);
   namedWindow("Durazno",WINDOW_NORMAL);
   imshow("Durazno",resultado2);

      namedWindow("Durazno2",WINDOW_NORMAL);
      imshow("Durazno2",resultado3);

      namedWindow("Uvas2",WINDOW_NORMAL);
      imshow("Uvas2",resultado4);

   resultado5=src+550*resultado2+500*resultado+500*resultado3+500*resultado4;
   namedWindow("Filtro Final",WINDOW_NORMAL);
   imshow("Filtro Final",resultado5);

   waitKey(0);
}
