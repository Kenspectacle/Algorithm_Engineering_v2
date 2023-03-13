#include "ImageFilter.hpp"

/**
 * @brief ToDo at Kenny.
 *
 * @param paddedImageVect
 * @param numRows
 * @param numCols
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect, const int &numRows, const int &numCols)
{
    std::vector<std::vector<int>> blurredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> kernel{
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}};
    int currentVal = 0;

    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            currentVal = 0;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    currentVal += paddedImageVect[i + x][j + y] * kernel[x + 1][y + 1];
                }
            }
            blurredImage[i][j] = currentVal / 16;
        }
    }
    return blurredImage;
}

/**
 * @brief ToDo at Kenny.
 *
 * @param blurredImage
 * @param imageVect
 * @param numRows
 * @param numCols
 * @return std::vector<std::vector<int>>
 */
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
            double gamma = 0.1 * (m / 255.0) * m * m / 65025;
            m = pow((m / 255.0), (1 / (gamma + 0.00000000001))) * 255.0;
            filteredImage[i][j] = m;
        }
    }
    return filteredImage;
}