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

Mat CalculoHistograma(Mat ImagenRecivida);
Mat valor,filtro;
Point corner1;
vector<Mat> DivididaRGB(3),bajo(3),alto(3);//creo la matriz para los canales

static void mause_callback(int event,int x, int y, int, void *);

int main()
{
    Mat src,dst;
    Mat histograma;
    //vector<Mat> IntensidadRGB();//creo la matriz para los canales

    src = imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\009.jpg",1);
    namedWindow("Imagen Cargada",WINDOW_NORMAL);
    imshow("Imagen Cargada",src);

    // cvtColor(src,dst,CV_BGR2GRAY);
     inRange(src,Scalar(20,150,65),Scalar(80, 270, 180), dst);
     namedWindow("Filtro",WINDOW_NORMAL);
     imshow("Filtro",dst);
     //



    if (src.data)
    {
        split(src,DivididaRGB);//divido
        cout<<"Imagen cargada\n";
        cout<<"\n";
    }

   histograma=CalculoHistograma(src);
   namedWindow("Histograma",WINDOW_NORMAL);
   imshow("Histograma",histograma);
     setMouseCallback("Imagen Cargada",mause_callback);
     waitKey(0);
}

Mat CalculoHistograma(Mat ImagenRecivida)
{
    //recibo la imagen y la divido en tres canales RGB
    vector<Mat> ImagenDivididaRGB(3);//creo la matriz para los canales
    split(ImagenRecivida,ImagenDivididaRGB);//divido
    /*
    imshow("Canal R",ImagenDivididaRGB[2]);//muestro canal rojo
    imshow("Canal G",ImagenDivididaRGB[1]);//muestro canal verde
    imshow("Canal B",ImagenDivididaRGB[0]);//muestro canal azul
    */
    //creo las matrices que contendran el histograma de cada canal
    Mat HistogramaR, HistogramaG, HistogramaB;

    //Calculo el histograma con la funcion de qcreator
        //declaro variables requeridas por la funcion
        int histSize = 255;
        float range[] = {0,255};
        const float* histRanges = {range};
        bool uniform = true;
        bool accumulate = false;
    calcHist(&ImagenDivididaRGB[2],1,0,Mat(),HistogramaR,1,&histSize,&histRanges,uniform,accumulate);
    calcHist(&ImagenDivididaRGB[1],1,0,Mat(),HistogramaG,1,&histSize,&histRanges,uniform,accumulate);
    calcHist(&ImagenDivididaRGB[0],1,0,Mat(),HistogramaB,1,&histSize,&histRanges,uniform,accumulate);
    //Grafico los puntos mediante un lazo repetitivo

    int hist_w = 800;//ancho de la grafica
    int hist_h = 400;//alto de la grafica
    int delta = cvRound((double) hist_w/histSize);

    Mat histImgen(hist_h,hist_w,CV_8UC3,Scalar(0,0,0));

        normalize(HistogramaB, HistogramaB, 0,histImgen.rows,NORM_MINMAX, -1, Mat());
        normalize(HistogramaG, HistogramaG, 0,histImgen.rows,NORM_MINMAX, -1, Mat());
        normalize(HistogramaR, HistogramaR, 0,histImgen.rows,NORM_MINMAX, -1, Mat());

        for(int i = 1; i < histSize ; i++){
            line( histImgen,
                          Point( delta*(i-1), hist_h - cvRound(HistogramaB.at<float>(i-1)) ) ,
                          Point( delta*(i), hist_h - cvRound(HistogramaB.at<float>(i)) ),
                          Scalar( 255, 0, 0), 2, 8, 0  );
                    line( histImgen, Point( delta*(i-1), hist_h - cvRound(HistogramaG.at<float>(i-1)) ) ,
                          Point( delta*(i), hist_h - cvRound(HistogramaG.at<float>(i)) ),
                          Scalar( 0, 255, 0), 2, 8, 0  );
                    line( histImgen, Point( delta*(i-1), hist_h - cvRound(HistogramaR.at<float>(i-1)) ) ,
                          Point( delta*(i), hist_h - cvRound(HistogramaR.at<float>(i)) ),
                          Scalar( 0, 0, 255), 2, 8, 0  );
        }
    return histImgen;
}
static void mause_callback(int event, int x, int y, int, void *)
{
    if (event==EVENT_LBUTTONDOWN)
    {
        corner1.x=x;
        corner1.y=y;
        cout<<"Posicion en x="<< x << "  Posicion en y="<< y <<endl;
        cout <<"Intensidad de valor canal R: " <<static_cast<unsigned>(DivididaRGB[2].at<uchar>(x,y)) <<endl;
        cout <<"Intensidad de valor canal B: " <<static_cast<unsigned>(DivididaRGB[0].at<uchar>(x,y)) <<endl;
        cout <<"Intensidad de valor canal G: " <<static_cast<unsigned>(DivididaRGB[1].at<uchar>(x,y)) <<endl;
        cout <<" "<<endl;
    }
}
