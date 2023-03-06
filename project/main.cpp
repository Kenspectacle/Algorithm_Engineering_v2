#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main (int argc, const char** argv) {

    std::string image_path = samples::findFile("static/input_image_1.jpg");
    std::cout << "Hello World"; 

    Mat img = imread(image_path, IMREAD_COLOR);

    // Error handling
    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window

    return 0;
}