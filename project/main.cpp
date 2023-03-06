#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main(int argc, const char **argv)
{

    std::string image_path = samples::findFile("static/input_image_1.jpg");
    std::cout << "Hello World" << std::endl;

    Mat img = imread(image_path, IMREAD_GRAYSCALE);

    // Error handling
    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    int numRows = img.rows;
    int numCols = img.cols;

    // Allocate

    int **squares = new int *[img.rows];

    for (int x = 0; x < img.rows; ++x)
    {
        squares[x] = new int[img.cols];
    }
    std::cout<<"test line "<<__LINE__<<"\n";

    // Convert from Mat object to 2D Array

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            int extracted = img.at<uchar>(i, j);
            std::cout << extracted << std::endl;
            squares[i][j] = extracted;
        }
    }

    // Convert from 2D Array to Mat object

    // malloc 

    // Mat A(img.rows, img.cols, CV_64F, squares);

    std::cout << "Squares:" << squares[0][2];
    // Clean up when done
    std::cout<<"test line "<<__LINE__<<"\n";

    for (int x = 0; x < img.rows; ++x)
    {
        delete[] squares[x];
    }
    std::cout<<"test line "<<__LINE__<<"\n";

    delete[] squares;
    std::cout<<"test line "<<__LINE__<<"\n";

    squares = nullptr;
    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}