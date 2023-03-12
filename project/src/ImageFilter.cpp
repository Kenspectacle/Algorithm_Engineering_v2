#include "ImageFilter.hpp"

#define KERNEL_SIZE 3

std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>>& paddedImageVect, const int numRows, const int numCols, const double sigma)
{
    std::vector<std::vector<int>> blurredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<double>> kernel(numRows, std::vector<double>(numCols, 0));
    double sum = 0.0;

    // Construct Gaussian kernel
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            double x = (double)i - (double)numRows / 2.0;
            double y = (double)j - (double)numCols / 2.0;
            double val = exp(-(x * x + y * y) / (2.0 * sigma * sigma));
            kernel[i][j] = val;
            sum += val;
        }
    }

    // Normalize kernel
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            kernel[i][j] /= sum;
        }
    }

    // Apply Gaussian filter to each pixel
    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            double currentVal = 0.0;
            // Convolve kernel with input image
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    currentVal += paddedImageVect[i + x][j + y] * kernel[i + x][j + y];
                }
            }
            // Store blurred pixel value in output image
            blurredImage[i][j] = (int)round(currentVal);
        }
    }
    return blurredImage;
}


std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect, const int &numRows, const int &numCols)
{
    std::vector<std::vector<int>> blurredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> kernel{
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}};
    int currentVal = 0;

    // Apply Gaussian filter to each pixel
    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            currentVal = 0;
            // Convolve kernel with input image
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    currentVal += paddedImageVect[i + x][j + y] * kernel[x + 1][y + 1];
                }
            }
            // Normalize pixel value and store in output image
            blurredImage[i][j] = currentVal / 16;
        }
    }
    return blurredImage;
}

std::vector<std::vector<int>> customFilter(const std::vector<std::vector<int>> &blurredImage,
                                           const std::vector<std::vector<int>> &imageVect,
                                           const int &numRows, const int &numCols)
{
    std::vector<std::vector<int>> filteredImage(numRows, std::vector<int>(numCols, 0));
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            double d = imageVect[i][j] / (blurredImage[i][j] + 0.0000000001);
            double m = std::min(255.0, d * 255 + 0.0000000001);
            double gamma = 0.05 * (m / 255.0) * m * m / 65025; // gamma correction
            m = pow((m / 255.0), (1 / (gamma + 0.00000000001))) * 255.0;
            filteredImage[i][j] = m;
        }
    }
    return filteredImage;
}

// TURN csv to array
// int *flat_img = new int[img.rows * img.cols];
// int k = 0;
// for (int i = 0; i < img.rows; i++)
// {
//     for (int j = 0; j < img.cols; j++)
//     {
//         flat_img[k] = imageVect[i][j];
//         k++;
//     }
// }