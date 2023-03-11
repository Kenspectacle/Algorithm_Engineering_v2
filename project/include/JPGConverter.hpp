#ifndef JPGCONVERTER_H
#define JPGCONVERTER_H

#include <iostream>
#include <string>
#include <vector>

/**
 * Meta data for the ppm format. 
 */
struct jpgMetaDataStruct
{
    int numRows, numCols;
};

jpgMetaDataStruct getJpgMetaData(std::string imageName);

void extractJpgPixelMatrix(const int numRows, const int numCols,
                    std::vector<std::vector<int>> &imageMatrix,
                    std::vector<std::vector<int>> &paddedImageMatrix);

#endif