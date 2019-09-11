#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src; Mat src_gray,final,final2;
int thresh = 200;
int max_thresh = 255;
void thresh_callback(int, void* );
int main(  )
{
  VideoCapture cap(-1);

    while(true){
        cap >> src;
          cvtColor( src, src_gray, COLOR_BGR2GRAY );
          blur( src_gray, src_gray, Size(3,3) );
          const char* source_window = "Source";
          namedWindow( source_window, WINDOW_AUTOSIZE );
          imshow( source_window, src );
          createTrackbar( " Canny", "Source", &thresh, max_thresh, thresh_callback );
          thresh_callback( 0, 0 );

          if(waitKey(1)==27){
              return 0;
          break;
          }
  }
  return(0);
}
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  vector<Moments> mu(contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mu[i] = moments( contours[i], false ); }

  vector<Point2f> mc( contours.size() );
  for( size_t i = 0; i < contours.size(); i++ )
     { mc[i] = Point2f( static_cast<float>(mu[i].m10/mu[i].m00) , static_cast<float>(mu[i].m01/mu[i].m00) ); }
  Mat drawing = Mat::zeros( src.size(), CV_8UC3 );
  /*for( size_t i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( 0,255,0 );
       Scalar color1 = Scalar( 0,0,255 );
       drawContours( drawing, contours, (int)i, color, 2, 8, hierarchy, 0, Point() );
       circle( drawing, mc[i], 4, color1, -1, 8, 0 );
     }*/
  int monedas=0;
  int dolar=0;
  int diez=0;
  int uno=0;
  int cinco=0;
  int ventecinco=0;
  int area;
  for( size_t i = 0; i< contours.size(); i++ )
     {
      area=contourArea(contours[i]);
       if(area>4000 && area<5000){
           monedas=monedas+25;
           ventecinco=ventecinco+1;
       }
       if(area>3000 && area<3700){
           monedas=monedas+5;
           cinco=cinco+1;
       }
       if(area>2000 && area<2900){
           monedas=monedas+10;
           diez=diez+1;
       }
       if(area>7 && area<8){
           monedas=monedas+1;
           uno=uno+1;
       }
       if(area>10 && area<20){
           monedas=monedas+50;

       }
       if(area>6000 && area<7000){
           monedas=monedas+50;
           dolar=dolar+1;
       }
     }

  string letra="Dinero $:  "+to_string(monedas)+" Centavos";
  string letra1="1cent:"+to_string(uno)+" 5cent:"+to_string(cinco)+"  10cent:"+to_string(diez)+" 25cent:"+to_string(ventecinco)+"- 50cent:"+to_string(dolar);
  putText(src, letra, Point(0,20), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(0,0,255),1);
 // putText(canny_output, letra1, Point(0,50), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(0,0,255),1);

//    cvtColor( canny_output, final, COLOR_GRAY2RGB );

  putText(src, to_string(area), Point(0,50), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(0,0,255),1);

  //final2= src & final;

  namedWindow( "Contours", WINDOW_NORMAL );
  imshow( "Contours", src );
}
