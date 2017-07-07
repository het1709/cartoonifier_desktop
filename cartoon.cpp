#include "opencv2/opencv.hpp"
#include "cartoon.h"

using namespace cv;
using namespace std;

const int MEDIAN_BLUR_FILTER_SIZE = 7;
const int LAPLACIAN_FILTER_SIZE = 5;
const int EDGES_THRESHOLD = 100;

void cartoonify(Mat blankFrame, Mat newFrame) {

    // GENERATE REGULAR SKETCH
    // Convert from BGR to Grayscale
    Mat gray, edges;
    cvtColor(blankFrame, gray, CV_BGR2GRAY);

    // Remove pixel noise with a Median filter, before we detect edges
    medianBlur(gray, gray, MEDIAN_BLUR_FILTER_SIZE);

    Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE); // Laplacian produces edges with varying brightness
    Mat mask;
    
    threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV); // Apply a binary threshold to make edges either white or black

    // GENERATING A COLOR PAINTING

    Size size = blankFrame.size();
    Size smallSize;
    // Scale the frame down to provide for more efficient filtering
    smallSize.width = size.width/2;
    smallSize.height = size.height/2;
    Mat smallImg = Mat(smallSize, CV_8UC3);
    resize(blankFrame, smallImg, smallSize, 0, 0, INTER_LINEAR);

    Mat tmp = Mat(smallSize, CV_8UC3);
    int repetitions = 5; // Repetitions for strong cartoon effect
    for (int i = 0; i < repetitions; i++) {
        int ksize = 7; // Filter size
        double sigmaColor = 9; // Filter color strength
        double sigmaSpace = 5; // Spatial strength
        bilateralFilter(smallImg, tmp, ksize, sigmaColor, sigmaSpace);
        bilateralFilter(tmp, smallImg, ksize, sigmaColor, sigmaSpace);
    }

    Mat bigImg;
    resize(smallImg, bigImg, size, 0, 0, INTER_LINEAR); // Get the original size back
    newFrame.setTo(0);
    bigImg.copyTo(newFrame, mask);
}
