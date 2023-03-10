#ifndef PPMCONVERTER_H
#define PPMCONVERTER_H

#include <string>
#include <vector>

struct imageStruct
{
    int numRows, numCols;
};

imageStruct getImgInformation(std::string imageName);

void importImageToVector(std::vector<std::vector<int>> imageMatrix,
                             std::vector<std::vector<int>> paddedImageMatrix,
                             const int numRows, const int numCols);

#endif