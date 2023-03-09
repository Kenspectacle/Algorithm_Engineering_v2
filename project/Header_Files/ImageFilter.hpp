#ifndef IMAGEFILTER_H
#define IMAGEFILTER_H

#include <vector>
#include <algorithm> // std::min
#include <cmath> // pow

std::vector<std::vector<int>> gaussianFilter(std::vector<std::vector<int>> paddedImageVect, int numRows, int numCols);
std::vector<std::vector<int>> customFilter(std::vector<std::vector<int>> blurredImage, std::vector<std::vector<int>> imageVect,int numRows, int numCols);

#endif