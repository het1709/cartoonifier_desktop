A simple program that uses Laplacian edge detection and bilateral filters in OpenCV to "cartoonify" a webcamera's stream.

# Compiling

 To compile go to the `cartoonifier_desktop` directory on your terminal and run:

 ```
 cmake .
 make
 ```

# Usage

 At this point, an executable called `CartoonifierDesktop` will be created which can be ran with:

 ```
 ./CartoonifierDesktop
 ```
This uses the default webcam detected by OpenCV (webcam number 0). If you have multiple webcameras then you can add the camera number as an argument to the call. For example, the following call in the terminal:

```
./CartoonifierDesktop 1
```
opens the program with webcam 1. If webcam 1 doesn't exist, then it'll open with the default webcam.

When the program is running, just press enter to take a photo from the webcam with the filter applied.

# Example

![](example_image.jpg)