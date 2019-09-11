#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;
int main ()
{
  Mat src, dst,dst1,gray,adap,dst2;
  src = imread("C:\\OptativaVision\\II_Parcial_Deberes\\lena15.jpg");
  cvtColor(src,gray,CV_BGR2GRAY,0);
  if( !src.data )
  { return -1; }

  float cuadrado[5][5]={{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};

  float vertical[15][5]={{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},
                        {1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},
                        {1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}};

  float horinzontal[5][15]={{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};

  Mat verticalFiltro=Mat(15,5,CV_32FC1,vertical)/ (float)(15*5);
  Mat cuadradoFiltro=Mat(5,5,CV_32FC1,cuadrado)/ (float)(5*5);
  Mat HorinFiltro=Mat(5,15,CV_32FC1,horinzontal)/ (float)(5*15);

  filter2D(src, dst,-1,verticalFiltro);
  filter2D(src, dst1,-1,HorinFiltro);
  filter2D(src, dst2,-1,cuadradoFiltro);

  imshow("Original",src);
  imshow("Cuadrado", dst2);
  imshow("Deformacion Vertical", dst);
  imshow("Deformacion Horinzontal", dst1);
  waitKey(0);

  return 0;
}
