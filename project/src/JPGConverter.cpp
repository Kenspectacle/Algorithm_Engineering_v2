#include "JPGConverter.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

/**
 * Extracts and saves header information from ppm image.
 * Expects the ppm file to be in P6 and therefore binary format,
 * throws exception if not given.
 */
jpgMetaDataStruct getJpgMetaData(std::string imageName)
{
    // std::string image_path = samples::findFile("static/" + imageName);

    // Mat img = imread(image_path, IMREAD_GRAYSCALE);

    // if (img.empty())
    // {
    //     std::cout << "Could not read the image: " << image_path << std::endl;
    //     return 1;
    // }

    jpgMetaDataStruct jpgMetaData;

    jpgMetaData.numRows = 10; // = img.rows;
    jpgMetaData.numCols = 10; // = img.cols;

    return jpgMetaData;
}

void extractJpgPixelMatrix(const int numRows, const int numCols,
                           std::vector<std::vector<int>> &imageMatrix,
                           std::vector<std::vector<int>> &paddedImageMatrix)
{
    // for (int i = 0; i < numRows; i++)
    // {
    //     for (int j = 0; j < numCols; j++)
    //     {
    //         int extracted = img.at<uchar>(i, j);
    //         imageMatrix[i][j] = extracted;
    //         paddedImageMatrix[i + 1][j + 1] = extracted;
    //     }
    // }
}
