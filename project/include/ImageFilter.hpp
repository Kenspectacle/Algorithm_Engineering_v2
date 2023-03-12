#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <vector>
#include <algorithm> // std::min
#include <cmath>     // pow

std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect,
                                             const int numRows, const int numCols, const double sigma);
std::vector<std::vector<int>> gaussianFilter(const std::vector<std::vector<int>> &paddedImageVect,
                                             const int &numRows, const int &numCols);
std::vector<std::vector<int>> customFilter(const std::vector<std::vector<int>> &blurredImage,
                                           const std::vector<std::vector<int>> &imageVect,
                                           const int &numRows, const int &numCols);

#endif