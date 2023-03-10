#include "../Header_Files/PPMConverter.hpp"

#include <iostream>


imageStruct getImgInformation(std::string imageName)
{
    // std::string image_path = samples::findFile("static/" + imageName);

    // Mat img = imread(image_path, IMREAD_GRAYSCALE);

    // if (img.empty())
    // {
    //     std::cout << "Could not read the image: " << image_path << std::endl;
    //     return 1;
    // }
    // int numRows = img.rows;
    // int numCols = img.cols;

    imageStruct imgStruct;
    imgStruct.numRows = 10;
    imgStruct.numCols = 10;
    return imgStruct;
}

void importImageToVector(std::vector<std::vector<int>> imageMatrix,
                             std::vector<std::vector<int>> paddedImageMatrix,
                             const int numRows, const int numCols)
{
    // Convert from Mat object to 2D Vectors
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // int extracted = img.at<uchar>(i, j);
            int extracted = 1;
            imageMatrix[i][j] = extracted;
            paddedImageMatrix[i + 1][j + 1] = extracted;
        }
    }
}