#include "ImageFilter.hpp"
#include <algorithm>

/**
 * @brief ToDo at Kenny.
 *
 * @param paddedImageVect
 * @param numRows
 * @param numCols
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect,
                                             const int numRows, const int numCols)
{
    std::vector<std::vector<int>> blurredImage(numRows, std::vector<int>(numCols, 0));
    std::vector<std::vector<int>> kernel{
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}};

#pragma omp parallel for collapse(2)
    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            int currentVal = 0;
#pragma omp simd reduction(+ \
                           : currentVal)
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

static const double kernelValues[3][3] = {{-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1}};

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
                                           const int numRows, const int numCols)
{
    const int kernelSize = 3;
    const int maxPixelValue = 255;
    const double contrast = 1.6;

    std::vector<std::vector<int>> filteredImage(numRows, std::vector<int>(numCols, 0));

#pragma omp parallel for collapse(2)
    for (int i = 1; i < numRows - 1; i++)
    {
        for (int j = 1; j < numCols - 1; j++)
        {
            int pixelValue = 0;
            for (int ki = 0; ki < kernelSize; ki++)
            {
                for (int kj = 0; kj < kernelSize; kj++)
                {
                    int row = i + ki - 1;
                    int col = j + kj - 1;
                    pixelValue += blurredImage[row][col] * kernelValues[ki][kj];
                }
            }
            int contrastAdjusted = (int)(contrast * pixelValue);
            filteredImage[i][j] = std::max(0, std::min(maxPixelValue, contrastAdjusted));
        }
    }
    return filteredImage;
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
std::vector<std::vector<int>> customFilterExtreme(const std::vector<std::vector<int>> &blurredImage,
                                                  const std::vector<std::vector<int>> &imageVect,
                                                  const int numRows, const int numCols)
{
    std::vector<std::vector<int>> filteredImage(numRows, std::vector<int>(numCols, 0));

#pragma omp parallel for collapse(2)
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            double d = imageVect[i][j] / (blurredImage[i][j] + 0.0000000001);
            double m = std::min(255.0, d * 255 + 0.0000000001);
            double gamma = 0.02 * (m / 255.0) * m * m / 65025;
            m = pow((m / 255.0), (1 / (gamma + 0.00000000001))) * 255.0;
            filteredImage[i][j] = m;
        }
    }
    return filteredImage;
}

/**
 * @brief ToDo Write doc
 *
 * @param blurredImage
 * @param imageVect
 * @param numRows
 * @param numCols
 * @return std::vector<std::vector<int>>
 */
std::vector<std::vector<int>> medianFilter(const std::vector<std::vector<int>> &blurredImage,
                                           const std::vector<std::vector<int>> &imageVect,
                                           const int numRows, const int numCols)
{
    int filterSize = 3;
    int filterOffset = (filterSize - 1) / 2;
    std::vector<std::vector<int>> result(numRows, std::vector<int>(numCols, 0));

#pragma omp parallel for
    for (int row = 0; row < numRows; row++)
    {
        std::vector<int> neighborValues(filterSize * filterSize, 0);
        for (int col = 0; col < numCols; col++)
        {
            int neighborCount = 0;
            int sum = 0;

            for (int filterRow = -filterOffset; filterRow <= filterOffset; filterRow++)
            {
                int neighborRow = row + filterRow;

                if (neighborRow >= 0 && neighborRow < numRows)
                {
                    for (int filterCol = -filterOffset; filterCol <= filterOffset; filterCol++)
                    {
                        int neighborCol = col + filterCol;

                        if (neighborCol >= 0 && neighborCol < numCols)
                        {
                            neighborValues[neighborCount++] = blurredImage[neighborRow][neighborCol];
                        }
                    }
                }
            }

            for (int i = 0; i < filterSize * filterSize; i++)
            {
                for (int j = i + 1; j < filterSize * filterSize; j++)
                {
                    if (neighborValues[i] > neighborValues[j])
                    {
                        std::swap(neighborValues[i], neighborValues[j]);
                    }
                }
            }

            int median = neighborValues[(neighborCount - 1) / 2];
            result[row][col] = median;
        }
    }

    return result;
}
