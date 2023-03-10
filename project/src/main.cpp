#include "PPMConverter.hpp"
#include "ImageFilter.hpp"

#include <iostream>
#include <vector>

// using std::vector<std::vector<int>> as Vec2i

int main(int argc, const char **argv)
{
    // 1. Step import and convert image
    imageStruct imageInformation = getImgInformation("name");
    int numRows = imageInformation.numRows;
    int numCols = imageInformation.numRows;

    std::cout << imageInformation.numRows;

    std::vector<std::vector<int>> imageMatrix(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> paddedImageMatrix(numRows + 2, std::vector<int>(numCols + 2, 0));
    importImageToVector(imageMatrix, paddedImageMatrix, numRows, numCols);

    // 2. Step transformations

    std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageMatrix, numRows, numCols);

    std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageMatrix, numRows, numCols);

    // 3. Convert image back to ppm

    // 4. Export image

    std::cout << "Job Done !" << std::endl;

    return 0;
}