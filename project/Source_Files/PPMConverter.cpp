#include "Header_Files/PPMConverter.hpp"

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

void ocv_getImgInformation(std::string imageName, int *numRows, int *numCols)
{
    std::string image_path = samples::findFile("static/" + imageName);

    Mat img = imread(image_path, IMREAD_GRAYSCALE);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    int numRows = img.rows;
    int numCols = img.cols;
}

void ocv_importImageToVector(std::vector<std::vector<int>> imageMatrix,
                             std::vector<std::vector<int>> paddedImageMatrix,
<<<<<<< HEAD
                             const int numRows, const int numCols);
=======
                             const int *numRows, const int *numCols);
>>>>>>> a8016c6a12931bc51b6455dc01e109f71a96cb91
{
    // Convert from Mat object to 2D Vectors
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
}