#include "PPMConverter.hpp"
#include "ImageFilter.hpp"
#include "CSVWriter.hpp"
     
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <vector>

using namespace cv;

template<typename T>
using Vec2D = std::vector<std::vector<T>>;

// using std::vector<std::vector<int>> as Vec2i

int main(const int argc, const char **argv)
{
    // 1. Step import and convert image
    // PPMConverter ppmConverter("input_image_1.ppm");

    // const int numRows = ppmConverter.imgMetaData.width;
    // const int numCols = ppmConverter.imgMetaData.height;
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
    int numRows = img.rows;
    int numCols = img.cols;

    // std::cout << imageInformation.numRows;

    // 2. Extract pixel matrix from image
    Vec2D<int> imageMatrix(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> imageVect(numRows, std::vector<int>(numCols, 0));
    Vec2D<int> paddedImageMatrix(numRows + 2, std::vector<int>(numCols + 2, 0));
    std::vector<std::vector<int>> paddedImageVect(numRows + 2, std::vector<int>(numCols + 2, 0));
    // importImageToVector(imageMatrix, paddedImageMatrix, numRows, numCols);
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
    // ppmConverter.extractPixelMatrix(imageMatrix, paddedImageMatrix);
    std::cout << "Pixel extraction done!" << std::endl;

    // 3. Step Filter Transformations

    // std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageMatrix, numRows, numCols);
    std::vector<std::vector<int>> blurredImage = gaussianFilter(paddedImageVect, numRows, numCols);
    std::cout << "Applied Gaussian Filter!" << std::endl;

    // std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageMatrix, numRows, numCols);
    std::vector<std::vector<int>> filteredImage = customFilter(blurredImage, imageVect, numRows, numCols);
    std::cout << "Applied Custom Filter!" << std::endl;

    // 4. Convert pixel matrix back to ppm

    // 5. Export image
    std::cout << "img cols:" << numCols << std::endl;
    std::cout << "img rows:" << numRows << std::endl;

    exportCSV(filteredImage, numRows, numCols);
    std::cout << "Job Done !" << std::endl;

    return 0;
}