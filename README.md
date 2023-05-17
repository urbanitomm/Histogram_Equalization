# Histogram_Equalization
Lab for the Computer Vision exam (prof. Zanuttigh)

##Histogram Equalization

First I uploaded the image, then using the function _split_ it was possible to divide the image in the three channel (B, G and R).
To calculate the histograms I used the function _calcHist_ applied for each channel, and to visualize it I used the provided function _showHistogram_.
In the task 3 I had to equalize each channel, I used the function _equalizeHist_ and then I re-calculated each equalized histogram with the function _calcHist_. 
In the last task I converted the image in a different color space: Lab. As before I split the image in the three channels, in this case L, a and b. Then I equalized only the luminance channel.
To calculate the new histograms I created three new channels where the first one is the equalized luminance. I calculated the histograms with the function _calcHist_ and displayed the histograms as before.
Then i merged the three channels into a new _Mat_ and displayed the image after converting from Lab color space to BGR.

![Fig.1 - Original Image](https://github.com/urbanitomm/Histogram_Equalization/blob/main/Original.png?raw=true)
![Fig.2 - RGB Equalized](https://github.com/urbanitomm/Histogram_Equalization/blob/main/RGB_Equalized.png?raw=true)
![Fig.3 - Luminance Equalized](https://github.com/urbanitomm/Histogram_Equalization/blob/main/RGB_Equalized.png?raw=true)



##Image Fitering


###Median filter 
The first filter applied is the median filter,vI used the function _medianBlur_ from openCV which has only one parameter: the kernel size. A bigger kernel size leads to a more blurred image.
![Fig.4 - Median Filter](https://github.com/urbanitomm/Histogram_Equalization/blob/main/median_filter.png?raw=true)
 ###Gaussian Blur
The Gaussian blur is the second filter, with the openCV function _GaussianBlur_ I applied the filter to the image. It's possible to regulate the filter with two parameters: the kernel size and the sigma value.
![Fig.5 - Gaussian Filter](https://github.com/urbanitomm/Histogram_Equalization/blob/main/gaussian_filter.png?raw=true)
###Bilateral filter
The last filter applied is the bilateral filter I used the function _bilateralFilter_ which has three parameters: the kernel size, sigma range and sigma space.
![Fig.6 - Bilateral Filter](https://github.com/urbanitomm/Histogram_Equalization/blob/main/bilateral_filter.png?raw=true)

I used the trackbars creating a trackbar for each parameter of each filter using the openCV function _createTrackbar_. For each filter I created a function to manage the parameters and to display the filtered image with the updated parameters.

