// Task 1
// Write a program that loads the image provided (street_scene.png), shows it and evaluates
// the Canny image. To verify the effect on the final result, add one or more trackbar(s) 1 to
// control the parameters of the Canny edge detector. Move the trackbars and check how
// changing each parameter has an influence on the resulting image. Please note: the Canny
// image shall be refreshed every time a trackbar is modified.



#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>



using namespace std;
using namespace cv;

Mat colorImage;
Mat grayImage,bluredImage,detected_edges, final;

int lowThreshold = 0;
const int max_lowThreshold = 100;
// const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Canny Image";

static void CannyThreshold(int, void*)
{

//step2: we apply gaussian blur
GaussianBlur( grayImage, bluredImage, Size( 5,5), 0, 0 );

//step3:Apply Canny edge detection
Canny( bluredImage, detected_edges, lowThreshold, lowThreshold*3, kernel_size );

final = Scalar::all(0);
colorImage.copyTo( final, detected_edges);
imshow( window_name, final );

}

int main(int argc, char** argv)
{
colorImage = cv::imread("street_scene.png", IMREAD_COLOR);
imshow("Original image",colorImage);

//step1: convert to grayscale 
cvtColor(colorImage,grayImage, COLOR_BGR2GRAY);
namedWindow( window_name, WINDOW_AUTOSIZE );
//creating the trackbar and calling it
createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

CannyThreshold(0, 0);

waitKey(0);
return(0);

}

