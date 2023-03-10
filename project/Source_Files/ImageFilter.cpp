#include "../Header_Files/ImageFilter.hpp"

#define KERNEL_SIZE 3

std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect, const int &numRows, const int &numCols)
{
    std::vector<std::vector<int>> blurredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> kernel{
        {1 / 16, 1 / 8, 1 / 16},
        {1 / 8, 1 / 4, 1 / 8},
        {1 / 16, 1 / 8, 1 / 16}};
    int currentVal = 0;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            currentVal = 0;
            // convolution
            for (int x = 0; x < KERNEL_SIZE; x++)
            {
                for (int y = 0; y < KERNEL_SIZE; y++)
                {
                    currentVal += paddedImageVect[i + x][j + y] * kernel[x][y];
                }
            }
            blurredImage[i][j] = currentVal;
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
            double d = imageVect[i][j] / (blurredImage[i][j] + 00000000001);
            double m = std::min(255.0, d * 255 + 00000000001);
            double gamma = 0.5 * (m / 255.0) * m * m / 65025;
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