#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#define KERNEL_SIZE 3
#define PAD_SIZE

using namespace cv;

std::vector<std::vector<int>> gaussian_filter(std::vector<std::vector<int>> paddedImageVect, int numRows, int numCols)
{
    std::vector<std::vector<int>> filteredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> kernel{
        {1 / 16, 1 / 8, 1 / 16},
        {1 / 8, 1 / 4, 1 / 8},
        {1 / 16, 1 / 8, 1 / 16}};
    int currentVal = 0;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            currentVal = 0;
            // convolution
            for (int x = 0; x < KERNEL_SIZE; x++)
            {
                for (int y = 0; y < KERNEL_SIZE; y++)
                {
                    currentVal += paddedImageVect[i + x][j + y] * kernel[x][y];
                }
            }
            filteredImage[i][j] = currentVal;
        }
    }
    return filteredImage;
}

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

    std::vector<std::vector<int>> imageVect(img.rows, std::vector<int>(img.cols, 0));
    std::vector<std::vector<int>> paddedImageVect(img.rows + 2, std::vector<int>(img.cols + 2, 0));

    std::cout << "testing vector:" << std::endl;
    std::cout << "imagevect size: " << imageVect.back().size() << "\n"
              << "paddedImageVect Size: " << paddedImageVect.back().size();

    // Convert from Mat object to 2D Array

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            int extracted = img.at<uchar>(i, j);
            // std::cout << extracted << std::endl;
            imageVect[i][j] = extracted;
            paddedImageVect[i + 1][j + 1] = extracted;
        }
    }

    // TO BE REFACTORED!!!

    // for (int i = 1; i)

    // Convert from 2D Array to Mat object
    int *flat_img = new int[img.rows * img.cols];

    int k = 0;
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            flat_img[k] = imageVect[i][j];
            k++;
        }
    }

    Mat A(img.rows, img.cols, CV_8U, flat_img);
    std::cout << "A cols: " << A.cols << "\n";
    std::cout << "A rows: " << A.rows << "\n";
    std::cout << "img cols: " << img.cols << "\n";
    std::cout << "img rows: " << img.rows << "\n";
    std::cout << "Squares:" << imageVect[0][2];

    // Clean up when done
    std::cout << "test line " << __LINE__ << "\n";

    std::cout << "test line " << __LINE__ << "\n";

    delete[] flat_img;
    std::cout << "test line " << __LINE__ << "\n";

    std::vector<std::vector<int>> filteredImage = gaussian_filter(paddedImageVect, numRows, numCols);
    // std::cout << filteredImage;
    // Mat A(img.rows, img.cols, CV_8U, filteredImage);
    // imshow("Display window", A);
    // int wait = waitKey(0); // Wait for a keystroke in the window

    // // imageArr = nullptr;
    // imshow("Display window", A);
    // std::cout<<"test line "<<__LINE__<<"\n";
    // int wait = waitKey(0); // Wait for a keystroke in the window
    // std::cout<<"test line "<<__LINE__<<"\n";

    // testing small image
    // int test_image_array[4]; // row major
    // test_image_array = [255, 255, 0, 0];
    return 0;
}