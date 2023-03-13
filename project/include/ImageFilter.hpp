#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <vector>
#include <cmath>

std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect,
                                             const int numRows, const int numCols);
std::vector<std::vector<int>> customFilter(const std::vector<std::vector<int>> &blurredImage,
                                           const std::vector<std::vector<int>> &imageVect,
                                           const int numRows, const int numCols);
std::vector<std::vector<int>> customFilterExtreme(const std::vector<std::vector<int>> &blurredImage,
                                                  const std::vector<std::vector<int>> &imageVect,
                                                  const int numRows, const int numCols);
std::vector<std::vector<int>> medianFilter(const std::vector<std::vector<int>> &blurredImage,
                                           const std::vector<std::vector<int>> &imageVect,
                                           const int numRows, const int numCols);

#endif