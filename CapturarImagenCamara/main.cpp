#include <iostream>
#include <stdlib.h>
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cap(0); //espacio de video
    Mat src,clara,oscura,src1,resta;
    int i=0;
    while (true) {
        cap>>src1;
        clara=src*1.5;
        oscura=src*0.5;
        if(i==0)
        {
            cap>>src;
            i=1;
        }
        else
        {
            i=0;
        }
        cap>>src1;
        resta=src1-src;
        imshow("Video Resta",resta);

/*        imshow("Video Original",src);
        imshow("Video Claro",clara);
        imshow("Video Oscuro",oscura);
*/
        if (waitKey(1)=='q')
        {
            break;
            return 0;
        }
    }
 return 0;
}
