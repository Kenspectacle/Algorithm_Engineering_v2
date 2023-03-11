#include "PPMConverter.hpp"
#include "JPGConverter.hpp"
#include "ImageFilter.hpp"
#include "CSVWriter.hpp"

#include <iostream>
#include <vector>

template<typename T>
using Vec2D = std::vector<std::vector<T>>;

int main(const int argc, const char **argv)
{
    /* 1. Step import and convert image */

    /* 1.1 For ppm files */
    // PPMConverter ppmConverter("input_image_1.ppm");
    // const int numRows = ppmConverter.imgMetaData.width;
    // const int numCols = ppmConverter.imgMetaData.height;

    /* 1.2 For jpg files */
    jpgMetaDataStruct jpgMetaData = getJpgMetaData("input_image_1.jpg");
    const int numRows = jpgMetaData.numRows;
    const int numCols = jpgMetaData.numCols;

    std::cout << "MetaData extraction done!" << std::endl;

    /* 2. Extract pixel matrix from image */
    Vec2D<int> imageVect(numRows, std::vector<int>(numCols, 0));
    Vec2D<int> paddedImageVect(numRows + 2, std::vector<int>(numCols + 2, 0));

    /* 2.1 For ppm files */
    // ppmConverter.extractPixelMatrix(imageVect, paddedImageVect);

    /* 2.2 For jpg files */
    extractJpgPixelMatrix(numRows, numCols, imageVect, paddedImageVect);

    std::cout << "Pixel extraction done!" << std::endl;

    /* 3. Step Filter Transformations */

    Vec2D<int> blurredImage = gaussianFilter(paddedImageVect, numRows, numCols);
    std::cout << "Applied Gaussian Filter!" << std::endl;

    Vec2D<int> filteredImage = customFilter(blurredImage, imageVect, numRows, numCols);
    std::cout << "Applied Custom Filter!" << std::endl;

    /* 4. Convert pixel matrix back to ppm */

    // 5. Export image
    std::cout << "img cols:" << numCols << std::endl;
    std::cout << "img rows:" << numRows << std::endl;

    exportCSV(filteredImage);

    std::cout << "Job Done !" << std::endl;

    return 0;
}