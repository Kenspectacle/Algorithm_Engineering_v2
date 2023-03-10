#include "PPMConverter.hpp"
#include "ImageFilter.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <vector>

using namespace cv;

// using std::vector<std::vector<int>> as Vec2i

int main(const int argc, const char **argv)
{
    // 1. Step import and convert image
    PPMConverter ppmConverter("input_image_1.ppm");

    const int numRows = ppmConverter.imgMetaData.width;
    const int numCols = ppmConverter.imgMetaData.height;
    std::cout << "MetaData extraction done!" << std::endl;
    // imageStruct imageInformation = getImgInformation("name");
    // int numRows = imageInformation.numRows;
    // int numCols = imageInformation.numRows;
    std::string imageName = "input_image_1.jpg";
    std::string image_path = samples::findFile("static/" + imageName);

    Mat img = imread(image_path, IMREAD_GRAYSCALE);

    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    // int numRows = img.rows;
    // int numCols = img.cols;

    // std::cout << imageInformation.numRows;

    // 2. Extract pixel matrix from image
    std::vector<std::vector<int>> imageMatrix(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> paddedImageMatrix(numRows + 2, std::vector<int>(numCols + 2, 0));
    // importImageToVector(imageMatrix, paddedImageMatrix, numRows, numCols);

    ppmConverter.extractPixelMatrix(imageMatrix, paddedImageMatrix);
    std::cout << "Pixel extraction done!" << std::endl;

    // 3. Step Filter Transformations

    std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageMatrix, numRows, numCols);
    std::cout << "Applied Gaussian Filter!" << std::endl;

    std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageMatrix, numRows, numCols);
    std::cout << "Applied Custom Filter!" << std::endl;

    // 4. Convert pixel matrix back to ppm

    // 5. Export image

    std::cout << "Job Done !" << std::endl;

    return 0;
}