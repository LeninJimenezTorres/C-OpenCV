#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int tipo = 0; // initial value
int valor = 0;  // initial value
int tipo2 = 0; // initial value
int valor2 = 0;  // initial value


Mat src, src_gray, dst,dst2,producto,suma;
int a;

int main(  )
{
    src = imread("C:\\OptativaVision\\CapturaImagen\\Histograma\\f.jpg",1);
    namedWindow("Imagen Cargada",WINDOW_NORMAL);
    imshow("Imagen Cargada",src);
    cvtColor( src, src_gray, COLOR_BGR2GRAY ); // Convert the image to Gray
    namedWindow("Imagen Gris",WINDOW_NORMAL);
    imshow("Imagen Gris",src_gray);

while(true)
{
    namedWindow("thewindow");
    createTrackbar("Tipo", "thewindow", &tipo, 4);
    createTrackbar("Valor", "thewindow", &valor, 255);
    createTrackbar("Tipo2", "thewindow", &tipo2, 4);
    createTrackbar("Valor2", "thewindow", &valor2, 255);

    Scalar lower(tipo,valor,tipo2,valor2);
    //Scalar upper(200,100,80,20);

    threshold( src_gray, dst, valor,255,tipo);
    threshold( src_gray, dst2, valor2,255,tipo2);

    producto=dst & dst2;
    suma=dst | dst2;

    imshow("thewindow", dst );
    imshow("Filtro 2", dst2 );
    imshow("And", producto );
    imshow("Suma", suma );


    for(;;)
      {
        char c = (char)waitKey( 20 );
        if( c == 27 )
      { break; }
      }
}
}
