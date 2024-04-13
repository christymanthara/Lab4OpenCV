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


// Step 2: bluring
// medianBlur(grayImage,grayImage,5);

// GaussianBlur( grayImage, grayImage, Size( 11,11), 0, 0 );


blur(grayImage,grayImage,Size(3,3));


//Step 3: Edge detection

Canny( grayImage, grayImage, 50, 200, 3);
// imshow("before threshold",grayImage);


imshow("gray blur image",grayImage);
// Step 4:
// Standard Hough Line Transform
 vector<Vec2f> lines; // will hold the results of the detection



 HoughLines(grayImage, lines, 1, CV_PI/180, 150 ,0 , 0 ); // runs the actual detection
 for( size_t i = 0; i < lines.size(); i++ )
 {
 float rho = lines[i][0], theta = lines[i][1];
 Point pt1, pt2;
 double a = cos(theta), b = sin(theta);
 double x0 = a*rho, y0 = b*rho;

 if(theta>CV_PI/180*40 && theta<CV_PI/180*60)
 {
 pt1.x = cvRound(x0 + 300*(-b));
 pt1.y = cvRound(y0 + 300*(a));
 pt2.x = cvRound(x0 - 300*(-b));
 pt2.y = cvRound(y0 - 300*(a));
 line( outImage, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
 }

else if(theta>CV_PI/180*120 && theta<CV_PI/180*150)
{
 pt1.x = cvRound(x0 + 1000*(-b));
 pt1.y = cvRound(y0 + 1000*(a));
 pt2.x = cvRound(x0 - 1000*(-b));
 pt2.y = cvRound(y0 - 1000*(a));
 line( outImage, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
}
 }
imshow("lined image",outImage);

final = colorImage.clone();

final = coloredImage(outImage,final);
imshow("final output image",final);


waitKey(0);
return(0);

}

