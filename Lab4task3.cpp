// Now detect white markings using the Hough transform. Check online sources and apply it
// using the cv::HoughLines() function. Suggestion: consider the two strongest lines detected,
// and select their orientation. Color in red the area between the lines - example below.





#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>



using namespace std;
using namespace cv;

Mat colorImage;
Mat grayImage,bluredImage,detected_edges,outImage, final;

int lowThreshold = 0;
const int max_lowThreshold = 100;
// const int ratio = 3;
const int kernel_size = 3;
// const char* window_name = "Canny Image";


cv::Mat coloredImage(Mat outImage,Mat final)
{
     for(int i=0; i<outImage.rows; i++)
    {
        bool checked = 0;
        int startingX = 0, stopingX = 0;

    for(int j=0; j<outImage.cols; j++)
        {

                //checking to see red pixel values in the last image
                if(outImage.at<cv::Vec3b>(cv::Point(j,i))[0] == 0 && outImage.at<cv::Vec3b>(cv::Point(j,i))[1]== 0 && outImage.at<cv::Vec3b>(cv::Point(j,i))[2] == 255)
                {
                    checked = 1;

                    if(startingX)
                        stopingX = j;

                }
                else if(checked)
                {
                    if(startingX == 0)
                    startingX = j;

                    checked = 0;
                }
        }
        if(startingX && stopingX) //starting and stoping values are 1 then enter loop
        {
            for(int k=startingX; k<stopingX; k++)
            {
                final.at<cv::Vec3b>(cv::Point(k,i))[0] = 0;
                final.at<cv::Vec3b>(cv::Point(k,i))[1] = 0;
                final.at<cv::Vec3b>(cv::Point(k,i))[2] = 255;

            }
        }
    }
    return final;
}



int main(int argc, char** argv)
{
colorImage = cv::imread("street_scene.png", IMREAD_COLOR);
imshow("Original image",colorImage);


outImage = colorImage.clone();

//step1: convert to grayscale 
cvtColor(colorImage,grayImage, COLOR_BGR2GRAY);
// namedWindow( window_name, WINDOW_AUTOSIZE );

// Step 2: applying threshhold
threshold(grayImage, grayImage, 243 , 255, cv::THRESH_BINARY); 

//Step 3: bluring
// GaussianBlur( grayImage, grayImage, Size( 7,7), 0, 0 );

medianBlur(grayImage,grayImage,5);

imshow("gray blur image",grayImage);

// Probabilistic Hough Line Transform
 vector<Vec4f> lines; // will hold the results of the detection

// this is perfect
 HoughLinesP(grayImage, lines, 10, CV_PI/180, 50, 100, 70 ); // runs the actual detection



for(int i =0; i<(int)lines.size();i++)
{
    cv::line(outImage,cv::Point(lines[i][0],lines[i][1]), cv::Point(lines[i][2],lines[i][3]),cv::Scalar(0, 0, 255),5,LINE_8,0);
}


imshow("lined image",outImage);

final = outImage.clone();

final = coloredImage(outImage,final);
imshow("final output image",final);


waitKey(0);
return(0);

}

