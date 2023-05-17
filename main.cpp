// Computer Vision 2022 (P. Zanuttigh, code M. Carraro) - LAB 2
// Name: URBANI TOMMASO 
// Student ID: 2045244

//libraries needed
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

using namespace std;
using namespace cv;

//initializing some global variables for the trackbars and the second part of the task
Mat src, dst;  
int slider_median = 1;
int slider_gaussian =1 ; 
int sigma_gaussian = 1;  
int slider_bilateral = 1; 
int sigma_range = 1;
int sigma_space = 1;

//the provided function to display the histograms
void showHistogram(std::vector<cv::Mat>& hists)
{
    // Min/Max computation
    double hmax[3] = { 0,0,0 };
    double min;
    cv::minMaxLoc(hists[0], &min, &hmax[0]);
    cv::minMaxLoc(hists[1], &min, &hmax[1]);
    cv::minMaxLoc(hists[2], &min, &hmax[2]);

    std::string wname[3] = { "blue", "green", "red" };
    cv::Scalar colors[3] = { cv::Scalar(255,0,0), cv::Scalar(0,255,0),
                             cv::Scalar(0,0,255) };

    std::vector<cv::Mat> canvas(hists.size());

    // Display each histogram in a canvas
    for (int i = 0, end = hists.size(); i < end; i++)
    {
        canvas[i] = cv::Mat::ones(125, hists[0].rows, CV_8UC3);

        for (int j = 0, rows = canvas[i].rows; j < hists[0].rows - 1; j++)
        {
            cv::line(
                canvas[i],
                cv::Point(j, rows),
                cv::Point(j, rows - (hists[i].at<float>(j) * rows / hmax[i])),
                hists.size() == 1 ? cv::Scalar(200, 200, 200) : colors[i],
                1, 8, 0
            );
        }

        cv::imshow(hists.size() == 1 ? "value" : wname[i], canvas[i]);
    }
}

void on_trackbar_median(int, void*) {

    // if the module of the kernel size is even it takes the next number (odd), the kernel must be odd (1,3,5,7...)
    slider_median = slider_median % 2 == 0 ? slider_median + 1 : slider_median;  

    medianBlur(src, dst, slider_median);  //calling the openCV function for the median filter
    imshow("Median Blur", dst);           //display the filtered image
}

void on_trackbar_gaussian(int, void*) {

    // if the module of the kernel size is even it takes the next number (odd), the kernel must be odd (1,3,5,7...)
    slider_gaussian = slider_gaussian % 2 == 0 ? slider_gaussian + 1 : slider_gaussian;    

    GaussianBlur(src, dst, Size(slider_gaussian, slider_gaussian), sigma_gaussian, 0);  //calling the openCV function for the gaussian filter
    imshow("Gaussian Blur", dst);                                                       // display the filtered image

}

void on_trackbar_bilateral(int, void*) {

    bilateralFilter(src, dst, slider_bilateral, sigma_range, sigma_space);
    imshow("Bilateral Filter", dst);
}

int main(int argc, char** argv)
{
    
    //++++++++++++++++++++++++  PART 1  ++++++++++++++++++++++++++++++++
    // TASK 1 - Load the image
    Mat input_img = imread("barbecue.png");     
    imshow("Original image",input_img);         

    // TASK 2 - Print the histograms of the image
    vector<Mat> bgr_planes;                     // "bgr_planes" will contaion the B, R and G planes of the image 
    split(input_img, bgr_planes);               // split() spits the input image in the 3 different channels
    int histSize = 256;                         
    float range[] = {0, 256};                   
    const float* histRange = { range };         
    bool uniform = true;                        
    bool accumulate = false;
    vector<Mat> hists(3);
    //Calculate the histogram of each color
    calcHist(&bgr_planes[0], 1, 0, Mat(), hists[0], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), hists[1], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), hists[2], 1, &histSize, &histRange, uniform, accumulate);
    //Display the histograms of each color
    showHistogram(hists);
    waitKey(0);

    // TASK 3 - Equalize the histograms
    vector<Mat> eq_planes(3);
    vector<Mat> eq_hists(3);
    //Equalize the histogram of each color
    equalizeHist(bgr_planes[0], eq_planes[0]);
    equalizeHist(bgr_planes[1], eq_planes[1]);
    equalizeHist(bgr_planes[2], eq_planes[2]);
    //Calculates the histogram of each color
    calcHist(&eq_planes[0], 1, 0, Mat(), eq_hists[0], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&eq_planes[1], 1, 0, Mat(), eq_hists[1], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&eq_planes[2], 1, 0, Mat(), eq_hists[2], 1, &histSize, &histRange, uniform, accumulate);
  
    // TASK 4 - Show the equalized histograms
    showHistogram(eq_hists);
    waitKey(0);
    // Creating the image to display
    Mat EqualizedImage;
    merge(eq_planes, EqualizedImage);
    imshow("GRB Equalized Image", EqualizedImage);
    waitKey(0);

    // TASK 5 - convert the image to a different color space and equalize only the luminance
    Mat l_img;
    cvtColor(input_img, l_img, COLOR_BGR2Lab);
    vector<Mat> l_channels;
    // Separating the image into 3 channels in this case (L, a, and b)
    split(l_img, l_channels);
    Mat l_equalized;
    // Applying histogram equalization only to the Luminance channel (0)
    equalizeHist(l_channels[0], l_equalized);
    // Creating a 3 channels vector for the equalized images
    vector<Mat> img_equalized(3);
    img_equalized[0] = l_equalized;    //the only one to be equlized is the luminance channel
    img_equalized[1] = l_channels[1];
    img_equalized[2] = l_channels[2];
    //Calculating the histograms of the luminance equalized image 
    vector<Mat> l_eq_hists(3);
    calcHist(&img_equalized[0], 1, 0, Mat(), l_eq_hists[0], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&img_equalized[1], 1, 0, Mat(), l_eq_hists[1], 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&img_equalized[2], 1, 0, Mat(), l_eq_hists[2], 1, &histSize, &histRange, uniform, accumulate);
    showHistogram(l_eq_hists);
    waitKey(0);
    // Creating the equalized image to display (only luminance equalized)
    Mat luminanceEqualizedImage;
    merge(img_equalized, luminanceEqualizedImage);
    // Convert the image from Lab color space back to BGR color space
    cvtColor(luminanceEqualizedImage, luminanceEqualizedImage, COLOR_Lab2BGR);
    imshow("Luminance Equalized Image", luminanceEqualizedImage);    
    waitKey(0);
    



    //++++++++++++++++++++++++  PART 2  +++++++++++++++++++++++++++++++++++++++++

    src = imread("portello.png");     // load the noisy image 
    imshow("Original image", src);         // show the noisy image
    waitKey(0);

    // MEDIAN FILTER
    medianBlur(src, dst, slider_median);
    imshow("Median Filter", dst);                                                               //show the filtered image with the initial parameters (all equal to 1)
    createTrackbar("Kernal Size", "Median Filter", &slider_median, 100, on_trackbar_median);    //kernel size trackbar
    waitKey(0);

    // GAUSSIAN BLUR
    GaussianBlur(src, dst, Size(slider_gaussian, slider_gaussian), sigma_gaussian, 0);
    imshow("Gaussian Blur", dst);                                                                   //show the filtered image with the initial parameters (all equal to 1)
    createTrackbar("Kernel Size", "Gaussian Blur", &slider_gaussian, 100, on_trackbar_gaussian);    //kernel size trackbar
    createTrackbar("Sigma", "Gaussian Blur", &sigma_gaussian, 50, on_trackbar_gaussian);            //sigma value trackbar
    waitKey(0);
   
    // BILATERAL FILTER
    bilateralFilter(src, dst, slider_bilateral, sigma_range, sigma_space);
    imshow("Bilateral Filter", dst);                                                                //show the filtered image with the initial parameters (all equal to 1)
    createTrackbar("K_Size", "Bilateral Filter", &slider_bilateral, 100, on_trackbar_bilateral);    //kernel size trackbar
    createTrackbar("sigma_r", "Bilateral Filter", &sigma_range, 100, on_trackbar_bilateral);        //sigma range value trackbar
    createTrackbar("sigma_s", "Bilateral Filter", &sigma_space, 100, on_trackbar_bilateral);        //sigma space value trackbar
    waitKey(0);

    return 0;
}

