#include <iostream>
#include <stdlib.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); //espacio de video
    Mat src,clara,oscura,src1,resta,gray,umbral,blurr,blurr2, blurgausiano,dst,dst2,dst3,final,gray2,gray3;

    while(true)
    {
     cap>>src;
     imshow("Video Original",src);
     cvtColor(src,gray,CV_BGR2GRAY);
    // imshow("Video Gray",gray);

     threshold(gray,umbral,100,255,0);
   //  imshow("Video Umbral",umbral);

      blur(gray,gray2,Size(3,3),Point(-1,-1));

     threshold(gray2,dst,150,255,CV_THRESH_OTSU);
     imshow("Video OTSU",dst);

     adaptiveThreshold(gray2,dst2,255,ADAPTIVE_THRESH_GAUSSIAN_C,0,3,2);
    // imshow("Video Umbral Adaptativo",dst2);

     adaptiveThreshold(gray,gray3,255,ADAPTIVE_THRESH_GAUSSIAN_C,0,3,2);
     imshow("Video Umbral Adaptativo",gray3);

     dst3=dst&dst2;

     GaussianBlur(gray,blurgausiano,Size(7,7),0.5,0.5);
   //  imshow("Video GausianBlur",blurgausiano);


     imshow("Video Final",dst3);

     /*   blur(gray,blurr,Size(30,5),Point(-1,-1));
     imshow("Video Blur",blurr);
     blur(gray,blurr2,Size(5,30),Point(-1,-1));
     imshow("Video Blur2",blurr2);
     */

     if (waitKey(1)=='q')
     {
         break;
         return 0;
     }
    }
return 0;
}

