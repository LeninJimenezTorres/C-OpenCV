#include <iostream>
#include <stdlib.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(-1); //espacio de video
    Mat src,clara,oscura,src1,resta,gray,umbral,blurr,blurr2, blurgausiano,dst,dst2,dst3,final,gray2,gray3,canny,canny2,sobel,sobel2;
    int kernel_size = 3;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    while(true)
    {
     cap>>src;
     imshow("Video Original",src);

     //Gris
     cvtColor(src,gray,CV_BGR2GRAY);
    // imshow("Video Gray",gray);

     //Filtro -binarizacion
    blur(gray,gray2,Size(3,3),Point(-1,-1));
    threshold(gray2,dst,150,255,CV_THRESH_OTSU);
    adaptiveThreshold(gray2,dst2,255,ADAPTIVE_THRESH_GAUSSIAN_C,0,3,2);
    dst3=dst&dst2;
    imshow("Filtro",dst3);


    //Canny
    Canny(gray2,canny,0,255,kernel_size);
    imshow("Metodo Canny",canny);

    //Sobel
    double minVal=0, maxVal=255;
    Sobel(gray2,sobel,CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    imshow("Metodo Sobel",sobel);

    Canny(dst3,canny2,0,255,kernel_size);
    imshow("Metodo Canny",canny2);

    Sobel(dst3,sobel2,CV_8U, 255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
    imshow("Metodo Sobel",sobel2);


    findContours(canny2,contours, hierarchy,CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(-1, -1) );

     Mat drawing = Mat::zeros( canny2.size(), CV_8UC3 );
    int contMonedas5=0;
    int contMonedas10=0;
    int contMonedas50=0;
 int area;
    for(int i=0;i<contours.size();i++){
        //Scalar color=Scalar(rng.uniform(0,255),rng.uniform(0,255),rng.uniform(0,255));
        //drawContours(drawing,contours,i,color,2,8,hierarchy,0,Point());
        area = contourArea(contours[i]);
        if((area>1000)&&(area<3500)){
            contMonedas5=contMonedas5+1;
        }
        if((area<700)&&(area>100)){
          //  if((area>4900)){
            contMonedas10=contMonedas10+1;
        }
        if((area>3500)){
            contMonedas50=contMonedas50+1;
        }

        //cout << "Contornos  "<<area<<endl;
    }
    string valor="Area  "+ to_string(area);
    putText(drawing,valor,Point(0,15),FONT_HERSHEY_COMPLEX_SMALL,1,CV_RGB(0,0,255),1);
    namedWindow("Contornos",CV_WINDOW_AUTOSIZE);
    imshow("Contornos",drawing);
    cout <<"\n";
    cout << "Monedas 5  "<<contMonedas5/2<<endl;
    cout <<"\n";
    cout << "Monedas 10 "<<contMonedas10/2<<endl;
    cout <<"\n";
    cout << "Monedas 1 dolar "<<(contMonedas50)<<endl;


    cout <<"\n";
    cout <<"\n";
    cout << "Dinero en Monedas 5  "<<(contMonedas5/2)*5<<" ctvs"<<endl;
    cout <<"\n";
    cout << "Dinero en Monedas 10  "<<(contMonedas10/2)*10<<" ctvs"<<endl;
    cout <<"\n";
    cout << "Dinero en Monedas 1 dolar  "<<(contMonedas50/2)*100<<" ctvs"<<endl;

    if (waitKey(1)=='q')
    {
        break;
        return 0;
    }
   }
return 0;
}
