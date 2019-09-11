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

Point corner1;
static void mause_callback(int event,int x, int y, int, void *);
 vector<Mat> hsv2(3);

 Mat dst3,src3;
int main()
{
   // VideoCapture cap(0); //espacio de video
    Mat src,dst,dst2,hsv,hsi,I,S,H,minimo1,minimo2,aux1,aux2,max1,max2, inversa,j,k,l,umbralizada,src2,nitidez,result,output,previa,siguiente;
    Mat h1,h2,comp;
     Mat_<float>h3,h4,h5,h6,h7,h8,h9,h10,den,num,val_nitidez;
     Mat_<double>p1;
    vector<Mat> RGB(3), min_val(3),HSV(3),inv(3);//creo la matriz para los canales
    float umbral,alfa,beta,a;
    src = imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\009.jpg");

    //Declaracion de matriz vacia para nueva imagen
    Mat contraste_brillo = Mat::zeros( src.size(), src.type() );

    cvtColor(src, hsv, CV_RGB2HSV);
    cvtColor(src, hsi, CV_RGB2HLS);

    while (true) {


      //RGB
        split(src,RGB);//divido
       imshow("Imagen Original",src);
       /*       imshow("Capa R",RGB[2]);
              imshow("Capa G",RGB[1]);
              imshow("Capa B",RGB[0]);
       */

        j=RGB[0];
      //Formas HSV y HSI
       imshow("HSVImg", hsv);
       imshow("HSIImg", hsi);
         split(hsv,hsv2);//divido
         //imshow("H", hsi2[2]);

       //Obtengo la matriz HSI

          //Capa Intensidad:
               I=(RGB[0]+RGB[1]+RGB[2])/3;
        //       imshow("Capa Intensidad",I);

           //Capa Saturacion:
               minimo1=min(RGB[0],RGB[1]);
               minimo2=min(minimo1,RGB[2]);
               max1=max(RGB[0],RGB[1]);
               max2=max(max1,RGB[2]);
               aux1=(minimo2/I);
               S=max2-aux1;
              // S=minimo2-aux1;
       //        imshow("Capa Saturacion",S);

           //Capa Color:
               minimo2=comp;

          /*     if(comp==j)
               {
                   H=(RGB[1]-RGB[0])/(3*(RGB[2]+RGB[1]-2*RGB[0]));
                   a=2;
               }
              else if (minimo2==RGB[2])
               {
                   H=(RGB[0]-RGB[2])/(3*(RGB[1]+RGB[0]-2*RGB[2]))+(1/3);
               }
               else if (minimo2==RGB[1])
               {
                   H=(RGB[2]-RGB[1])/(3*(RGB[2]+RGB[0]-2*RGB[1]))+(2/3);
               }

               //imshow("Capa Color",H);
*/




      //Imagen Invertida NOT
      inv[0]=abs(255-RGB[0]);
      inv[1]=abs(255-RGB[1]);
      inv[2]=abs(255-RGB[2]);

        merge(inv,inversa);
        imshow("Imagen Inversa",inversa);



      //Umbralizacion
        umbral=150;
        //src2= imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\009.jpg",0);
        src2=src;
        threshold(src2,umbralizada, umbral,255,0);
        imshow("Filtro Umbral",umbralizada);



     //Contraste y brillo:
         //alfa=contraste, beta=brillo
         alfa=0.7;
         beta=-20;
        // contraste_brillo=(alfa*src)+beta;
         for( int y = 0; y < src.rows; y++ ) {
                 for( int x = 0; x < src.cols; x++ ) {
                     for( int c = 0; c < 3; c++ ) {
                         contraste_brillo.at<Vec3b>(y,x)[c] = saturate_cast<uchar>( alfa*( src.at<Vec3b>(y,x)[c] ) + beta );
                     }
                 }
             }

         imshow("Filtro Contraste & Brillo",contraste_brillo);



        //Nitidez:
        val_nitidez=2;
   /*
        for(int j=1; j<src.rows; j++) {
            src.at<Vec3b>(y,x)[c] =
            for( int x = 0; x < src.cols; x++ ) {

                }
            }
        }
*/

/*
        //Umbral con HSV
        inRange(hsv,Scalar(80,100,128),Scalar(120, 122, 145), dst);
        namedWindow("Filtro",WINDOW_NORMAL);
        imshow("Filtro",dst);
*/

        setMouseCallback("HSVImg",mause_callback);

        inRange(src,Scalar(90,92,240),Scalar(167, 97, 255), dst3);
        namedWindow("FiltroFruta",WINDOW_NORMAL);
        imshow("FiltroFruta",dst3);
       if (waitKey(1)=='q')
        {
            break;
            return 0;
        }
    }

 return 0;
}
static void mause_callback(int event, int x, int y, int, void *)
{
    if (event==EVENT_LBUTTONDOWN)
    {
        corner1.x=x;
        corner1.y=y;
        cout<<"Posicion en x="<< x << "  Posicion en y="<< y <<endl;
        cout <<"Intensidad de valor canal H: " <<static_cast<unsigned>(hsv2[2].at<uchar>(x,y)) <<endl;
        cout <<"Intensidad de valor canal S: " <<static_cast<unsigned>(hsv2[0].at<uchar>(x,y)) <<endl;
        cout <<"Intensidad de valor canal L: " <<static_cast<unsigned>(hsv2[1].at<uchar>(x,y)) <<endl;
        cout <<" "<<endl;
    }
}
