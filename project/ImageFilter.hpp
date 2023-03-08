#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <vector>

std::vector<std::vector<int>> gaussianFilter(std::vector<std::vector<int>> paddedImageVect, int numRows, int numCols);

#endif