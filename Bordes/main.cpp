#include <iostream>
#include <stdlib.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
   float horinzontal[3][3]={{-1,-1,-1},{0,0,0},{1,1,1}};
    float diagonal1[3][3]={{-1,-1,0},{-1,0,1},{0,1,1}};
    float diagonal2[3][3]={{0,1,1},{-1,0,1},{-1,-1,0}};
    float vertical[3][3]={{-1,0,1},{-1,0,1},{-1,0,1}};

    Mat HorinFiltro=Mat(3,3,CV_32FC1,horinzontal);
    Mat DiagonalFiltro2=Mat(3,3,CV_32FC1,diagonal2);
    Mat DiagonalFiltro1=Mat(3,3,CV_32FC1,diagonal1);
    Mat VerticalFiltro=Mat(3,3,CV_32FC1,vertical);
    Mat src,dst,dst1,gray,dst2,dst3;


/*
    float horinzontal[5][5]={{-1,-1,-1,-1,-1},{0,0,0,0,0},{1,1,1,1,1}};
    float diagonal1[5][5]={{-1,-1,-1,-1,0},{-1,-1,0,1,1},{0,1,1,1,1}};
    float diagonal2[5][5]={{0,1,1,1,1},{-1,-1,0,1,1},{-1,-1,-1,-1,0}};
    float vertical[5][5]={{-1,0,0,0,1},{-1,0,0,0,1},{-1,0,0,0,1}};

    Mat HorinFiltro=Mat(5,5,CV_32FC1,horinzontal);
    Mat DiagonalFiltro2=Mat(5,5,CV_32FC1,diagonal2);
    Mat DiagonalFiltro1=Mat(5,5,CV_32FC1,diagonal1);
    Mat VerticalFiltro=Mat(5,5,CV_32FC1,vertical);
    Mat src,dst,dst1,gray,dst2,dst3;
*/

    src=imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\kernel.jpg");
    cvtColor(src,gray,CV_BGR2GRAY,0);
    filter2D(src, dst, -1, HorinFiltro);
    filter2D(src, dst1, -1, VerticalFiltro);
    filter2D(src, dst3, -1, DiagonalFiltro1);
    filter2D(src, dst2, -1, DiagonalFiltro2);
    imshow( "Original", src );
    imshow("Horinzontal", dst);
    imshow("Vertical", dst1);
    imshow("Diagonal", dst3);
    imshow("Diagonal1", dst2);
    Mat or1,or2,final;
    or1=dst|dst1;
    or2=dst3|dst2;
    final=or1|or2;
    imshow("resultado",final);
      waitKey(0);
}

