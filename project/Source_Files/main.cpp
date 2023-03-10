#include "../Header_Files/PPMConverter.hpp"
#include "../Header_Files/ImageFilter.hpp"

#include <iostream>
#include <vector>

// using std::vector<std::vector<int>> as Vec2i

int main(const int argc, const char **argv)
{
    // 1. Step import and convert image
    PPMConverter ppmConverter("input_image_1.ppm");

    const int numRows = ppmConverter.imgMetaData.width;
    const int numCols = ppmConverter.imgMetaData.height;

    // 2. Extract pixel matrix from image
    std::vector<std::vector<int>> imageMatrix(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> paddedImageMatrix(numRows + 2, std::vector<int>(numCols + 2, 0));
    ppmConverter.extractPixelMatrix(imageMatrix, paddedImageMatrix);

    // 3. Step Filter Transformations

    std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageMatrix, numRows, numCols);

    std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageMatrix, numRows, numCols);

    // 4. Convert pixel matrix back to ppm

    // 5. Export image

    std::cout << "Job Done !" << std::endl;

    return 0;
}