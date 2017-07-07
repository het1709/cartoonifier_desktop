#include <string>
#include <cstdlib>
#include "opencv2/opencv.hpp"
#include "cartoon.h"

int main(int argc, char** argv) {

    int cameraNumber = 0;
    if (argc > 1) {
        cameraNumber = atoi(argv[1]);
    }

    // Get access to the camera
    cv::VideoCapture camera;
    camera.open(cameraNumber);
    
    if (!camera.isOpened()) {
        std::cerr << "Error: Could not access the camera" << std::endl;
        exit(1);
    }
    
    // Set the camera resolution
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    int captureNum = 1;
    while (true) {
        // Get next camera frame
        cv::Mat cameraFrame;
        camera >> cameraFrame;
        if (cameraFrame.empty()) {
            std::cerr << "Error: Couldn't get a camera frame" << std::endl;
            exit(1);
        }
        cv::Mat displayedFrame(cameraFrame.size(), CV_8UC3);
        
        cartoonify(cameraFrame, displayedFrame);
        cv::Mat flipped;
        cv::flip(displayedFrame, flipped, 1);
        imshow("Cartoonifier", flipped);
        char key = cv::waitKey(20);
        if (key == 27) {
            break;
        } else if (key == 10) {
            std::string path = "image" + std::to_string(captureNum) + ".jpg";
            imwrite(path, flipped);
            printf("Saved! \n");
            captureNum++;
        }
    }
}
