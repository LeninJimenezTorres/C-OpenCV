#include <iostream>
#include <stdlib.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); //espacio de video
    Mat src,clara,oscura,src1,resta,gray,umbral,blurr,blurr2, blurgausiano,dst,dst2,dst3,final,gray2,gray3,EG,R,G,B,Gray,acufor;
    vector<Mat> DivididaRGB(3);
    Mat r = Mat::zeros( src.size(), src.type() );


    while(true)
    {
     cap>>src;
     imshow("Video Original",src);
     cvtColor(src,gray,CV_BGR2GRAY);
     imshow("Video Gray",gray);

     split(src,DivididaRGB);
//     imshow("Video Capa R",DivididaRGB[2]);

     EG = (0.3)*DivididaRGB[2] + 0.59*DivididaRGB[1]+ 0.11*DivididaRGB[0];
     imshow("Video Gray Fórmula",EG);

     //Otra forma de hacer el filtro por pixel
     for(int i=0;i<src.rows;i++){
             for(int j=0;j<src.cols;j++){
                 r.at<uchar>(i,j)=DivididaRGB[0].at<uchar>(i,j)*0.11+DivididaRGB[1].at<uchar>(i,j)*0.59+DivididaRGB[2].at<uchar>(i,j)*0.3;
          //       acufor=r.at<uchar>(i,j);
                 //acufun=gray_funcion.at<uchar>(i,j);

             //    imshow("Video Gray Fórmula 2",r);
             }
         }

     if (waitKey(1)=='q')
     {
         break;
         return 0;
     }
    }
return 0;
}

/*
int fun(Mat img)
{

}*/
