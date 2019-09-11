#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"  // Include header files from OpenCV directory
#include "opencv2/highgui.hpp"   // required to stitch images.
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

// Definir el modo para la costura com opanorámica
// Función Stitcher
Stitcher::Mode mode = Stitcher::PANORAMA;

// Vector de imágenes
vector<Mat> imgs;

int main(int argc, char* argv[])
{
    // Lista de imágenes a unir
    //CASA
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0085.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0086.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0087.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0088.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0089.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0090.jpg"));
    imgs.push_back(imread("C:\\OptativaVision\\II_Parcial_Deberes\\DSC_0091.jpg"));


    // Define objeto paraguardar la imagen cosida
    Mat pano;

    // Create a Stitcher class object with mode panoroma
    Ptr<Stitcher> stitcher = Stitcher::create(mode, false);

    // Comando para coser todas las imágenes en la matriz de imágenes
    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        // Aviso si no se pueden pegar las imágenes
        cout << "Can't stitch images\n" ;
        return -1;
    }
    // Almacena una nueva imagen pegada a la imagen dada
    //Conjunto de imágenes como resultado.jpg"
    imwrite("result.jpg", pano);

    // Mostrar el resultado
    resize(pano,pano,Size(1300,800),1,1,INTER_LINEAR);
    imshow("Result", pano);

    waitKey(0);
    return 0;
}

