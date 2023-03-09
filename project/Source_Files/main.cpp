#include "PPMConverter.hpp"
#include "ImageFilter.hpp"

#include <iostream>

// using std::vector<std::vector<int>> as Vec2i

int main(int argc, const char **argv)
{
    // 1. Step import and convert image
    int *numRows, *numCols;
    ocv_getImgInformation("name", numRows, numCols);
    std::vector<std::vector<int>> imageMatrix(*numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> paddedImageMatrix(*numRows + 2, std::vector<int>(numCols + 2, 0));
    ocv_importImageToVector(imageMatrix, paddedImageMatrix, numRows, numCols);

    // 2. Step transformations

    std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageMatrix, *numRows, *numCols);

    std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageMatrix, *numRows, *numCols);

    // 3. Convert image back to ppm

    // 4. Export image

    return 0;
}