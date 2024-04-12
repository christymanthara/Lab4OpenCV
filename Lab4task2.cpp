
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
Mat grayImage,bluredImage,detected_edges, final, croppedframe;

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
// //creating the trackbar and calling it
// createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);


// i used threshold to segment out only the white lines using appropriate threshold values .
Mat thresh1;
threshold(grayImage, thresh1, 240, 255, cv::THRESH_BINARY);
imshow("thresh1",thresh1);

//cropping the frame to select only the bottom half of the image as the road will be on the bottom half roughly
// croppedframe = grayImage(Rect(0,grayImage.rows/2,grayImage.cols,grayImage.rows/2));

// imshow("cropped Image",croppedframe);
//creating a final bnw image to write the pixels to this file.
Mat final(colorImage.size().height, colorImage.size().width, CV_8UC1, cv::Scalar(0));

// i used threshold to segment out only the white lines using appropriate threshold values .
// threshold(croppedframe, croppedframe, 240, 255, cv::THRESH_BINARY);
// imshow("threshcropped",croppedframe);

// now i am going to select a region of interest by specifying the coordinates to create a mask

    Point P1(2, 366);
    Point P2(539, 194);
    Point P3(632, 197);
    Point P4(828, 373);


   vector< vector<Point> >  co_ordinates; //vector of vector points. this is named as co_ordinates
   co_ordinates.push_back(vector<Point>());
   co_ordinates[0].push_back(P1);
   co_ordinates[0].push_back(P2);
   co_ordinates[0].push_back(P3);
   co_ordinates[0].push_back(P4);

   fillPoly(final, co_ordinates, cv::Scalar(255,255,255));// in the image named final we are drawing the coordinates and filling it with the color specified



    imshow("fillpoly",final);



    Mat maskedIm = thresh1.clone();
    bitwise_and(thresh1, final, maskedIm); // using and operation with the mask on the filled polygon
    imshow("masked final",maskedIm);




waitKey(0);
return(0);

}

