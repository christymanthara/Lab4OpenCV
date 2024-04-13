// Detect the road sign using the Hough circular transform - function cv::HoughCircles().

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;
Mat gray;
Mat img_blur;
int main(int argc, char** argv)
{   
    Mat colorImage;
    colorImage = cv::imread("street_scene.png", IMREAD_COLOR);
    imshow("Original image",colorImage);
    
    cv::cvtColor(colorImage,gray,COLOR_BGR2GRAY);
    cv::imshow("Original image revamped",gray);
    
    
    vector<Vec3f>  circles;
    cv::HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows/64, 200, 10, 8, 10);
    for(size_t i=0; i<circles.size(); i++) 
        {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(colorImage, center, radius, Scalar(0, 0, 255), FILLED, 8, 0);
        circle(gray, center, radius, Scalar(255, 255, 255), 2, 8, 0);
        }

    cv::imshow("Original image revamped2",colorImage);
    cv::imshow("BNW image revamped2",gray);
     waitKey(0);
        return 0;



}