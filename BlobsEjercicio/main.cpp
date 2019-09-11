/*#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;
int main( int argc, char** argv )
{
    // Read image
    Mat im;
    VideoCapture cap(-1);
    while (true) {
        cap>>im;
//        im = imread( "C:\\OptativaVision\\CapturaImagen\\Histograma\\blob.jpg", IMREAD_GRAYSCALE );
       // Setup SimpleBlobDetector parameters.
       SimpleBlobDetector::Params params;

       // Change thresholds
       params.minThreshold = 10;
       params.maxThreshold = 200;

       // Filter by Area.
       params.filterByArea = false;
       params.minArea = 1500;

       // Filter by Circularity
       params.filterByCircularity = false;
       params.minCircularity = 0.1;

       // Filter by Convexity
       params.filterByConvexity = false;
       params.minConvexity = 1.1;

       // Filter by Inertia
       params.filterByInertia = false;
       params.minInertiaRatio = 0.01;

       // Storage for blobs
       vector<KeyPoint> keypoints;


       #if CV_MAJOR_VERSION < 3   // If you are using OpenCV 2
           // Set up detector with params
           SimpleBlobDetector detector(params);
           // Detect blobs
           detector.detect( im, keypoints);
       #else

       // Set up detector with params
       Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create(params);

       // Detect blobs
       detector->detect( im, keypoints);
       #endif


       // Draw detected blobs as red circles.
       // DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures
       // the size of the circle corresponds to the size of blob

       Mat im_with_keypoints;
       drawKeypoints( im, keypoints, im_with_keypoints, Scalar(0,0,255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS );

       // Show blobs
       imshow("keypoints", im_with_keypoints );
       //waitKey(0);

       if(waitKey(1)==27){
           break;
       }

    }

    return 0;
}
*/

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
using namespace cv;

static String Legende(SimpleBlobDetector::Params &pAct)
{
    String s = "";
    if (pAct.filterByArea)
    {
        String inf = static_cast<const ostringstream&>(ostringstream() << pAct.minArea).str();
        String sup = static_cast<const ostringstream&>(ostringstream() << pAct.maxArea).str();
        s = " Area range [" + inf + " to  " + sup + "]";
    }
    if (pAct.filterByCircularity)
    {
        String inf = static_cast<const ostringstream&>(ostringstream() << pAct.minCircularity).str();
        String sup = static_cast<const ostringstream&>(ostringstream() << pAct.maxCircularity).str();
        if (s.length() == 0)
            s = " Circularity range [" + inf + " to  " + sup + "]";
        else
            s += " AND Circularity range [" + inf + " to  " + sup + "]";
    }
    if (pAct.filterByColor)
    {
        String inf = static_cast<const ostringstream&>(ostringstream() << (int)pAct.blobColor).str();
        if (s.length() == 0)
            s = " Blob color " + inf;
        else
            s += " AND Blob color " + inf;
    }
    if (pAct.filterByConvexity)
    {
        String inf = static_cast<const ostringstream&>(ostringstream() << pAct.minConvexity).str();
        String sup = static_cast<const ostringstream&>(ostringstream() << pAct.maxConvexity).str();
        if (s.length() == 0)
            s = " Convexity range[" + inf + " to  " + sup + "]";
        else
            s += " AND  Convexity range[" + inf + " to  " + sup + "]";
    }
    if (pAct.filterByInertia)
    {
        String inf = static_cast<const ostringstream&>(ostringstream() << pAct.minInertiaRatio).str();
        String sup = static_cast<const ostringstream&>(ostringstream() << pAct.maxInertiaRatio).str();
        if (s.length() == 0)
            s = " Inertia ratio range [" + inf + " to  " + sup + "]";
        else
            s += " AND  Inertia ratio range [" + inf + " to  " + sup + "]";
    }
    return s;
}



int main()
{
Mat img;
VideoCapture cap(0);
while(true){
    cap >> img;
    SimpleBlobDetector::Params pDefaultBLOB;
    // This is default parameters for SimpleBlobDetector
    pDefaultBLOB.thresholdStep = 10;
    pDefaultBLOB.minThreshold = 10;
    pDefaultBLOB.maxThreshold = 220;
    pDefaultBLOB.minRepeatability = 2;
    pDefaultBLOB.minDistBetweenBlobs = 10;
    pDefaultBLOB.filterByColor = false;
    pDefaultBLOB.blobColor = 0;
    pDefaultBLOB.filterByArea = false;
    pDefaultBLOB.minArea = 2500;
    pDefaultBLOB.maxArea = 10000;
    pDefaultBLOB.filterByCircularity = false;
    pDefaultBLOB.minCircularity = 0.9f;
    pDefaultBLOB.maxCircularity = (float)1e37;
    pDefaultBLOB.filterByInertia = false;
    pDefaultBLOB.minInertiaRatio = 0.1f;
    pDefaultBLOB.maxInertiaRatio = (float)1e37;
    pDefaultBLOB.filterByConvexity = false;
    pDefaultBLOB.minConvexity = 0.95f;
    pDefaultBLOB.maxConvexity = (float)1e37;
    // Descriptor array for BLOB
    vector<String> typeDesc;
    // Param array for BLOB
    vector<SimpleBlobDetector::Params> pBLOB;
    vector<SimpleBlobDetector::Params>::iterator itBLOB;
    // Color palette
    vector< Vec3b >  palette;
    for (int i = 0; i<255; i++)
    {
        palette.push_back(Vec3b((uchar)rand(), (uchar)rand(), (uchar)rand()));
    }

    // These descriptors are going to be detecting and computing BLOBS with 6 different params
    // Param for first BLOB detector we want all
    typeDesc.push_back("BLOB");    // see http://docs.opencv.org/trunk/d0/d7a/classcv_1_1SimpleBlobDetector.html
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByArea = false;
    pBLOB.back().minArea = 5000;
    pBLOB.back().maxArea = float(img.rows*img.cols);
    // Param for second BLOB detector we want area between 500 and 2900 pixels
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByArea = true;
    pBLOB.back().minArea = 4000;
    pBLOB.back().maxArea = 9700;

    // Param for third BLOB detector we want only circular object
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByCircularity = false;
    // Param for Fourth BLOB detector we want ratio inertia
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByInertia = false;
    pBLOB.back().minInertiaRatio = 0;
    pBLOB.back().maxInertiaRatio = (float)0.2;
    // Param for fifth BLOB detector we want ratio inertia
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByConvexity = false;
    pBLOB.back().minConvexity = 0.;
    pBLOB.back().maxConvexity = (float)0.9;
    // Param for six BLOB detector we want blob with gravity center color equal to 0 bug #4321 must be fixed
    typeDesc.push_back("BLOB");
    pBLOB.push_back(pDefaultBLOB);
    pBLOB.back().filterByColor = false;
    pBLOB.back().blobColor = 0;
    itBLOB = pBLOB.begin();
    Ptr<Feature2D> b;
    String label;
    // Descriptor loop
    vector<String>::iterator itDesc;
    for (itDesc = typeDesc.begin(); itDesc != typeDesc.end(); ++itDesc)
    {
        if (*itDesc == "BLOB")
        {
            b = SimpleBlobDetector::create(*itBLOB);
            label = Legende(*itBLOB);
            ++itBLOB;
        }
        try
        {
            // We can detect keypoint with detect method
            vector<KeyPoint>  keyImg;
            Mat result(img.rows, img.cols, CV_8UC3);
            if (b.dynamicCast<SimpleBlobDetector>() != NULL)
            {
                Ptr<SimpleBlobDetector> sbd = b.dynamicCast<SimpleBlobDetector>();
                sbd->detect(img, keyImg, Mat());
                drawKeypoints(img, keyImg, result);
                int i = 0;
                for (vector<KeyPoint>::iterator k = keyImg.begin(); k != keyImg.end(); ++k, ++i)
                    circle(result, k->pt, (int)k->size, palette[i % 65536]);
            }
            if(pBLOB.back().minArea==5000 & pBLOB.back().maxArea==1000){
               putText(result, "Objeto2", Point(0,20), FONT_HERSHEY_COMPLEX_SMALL, 1, CV_RGB(0,0,255),1);
            }
            namedWindow(*itDesc + label, WINDOW_AUTOSIZE);
            imshow(*itDesc + label, result);
            //imshow("Original", img);
        }
        catch (Exception& e)
        {
            cout << "Feature : " << *itDesc << "\n";
            cout << e.msg << endl;
        }
    }
if(waitKey(1)==27){
    break;
}
}
    return 0;
}
