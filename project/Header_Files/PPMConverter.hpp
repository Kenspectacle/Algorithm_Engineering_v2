#ifndef PPMCONVERTER_H
#define PPMCONVERTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * Meta data for the ppm format. 
 */
struct imgMetaDataStruct
{
    std::string mode;
    int width, height, max;
};

class PPMConverter
{
private:
    std::string imgPath;
    std::ifstream imgStream;
    
    void eatNextComment();
    void checkStream();

public:
    imgMetaDataStruct imgMetaData;

    PPMConverter(std::string imgName);

    imgMetaDataStruct getImgMetaData();
    void extractPixelMatrix(std::vector<std::vector<int>> imageMatrix,
                            std::vector<std::vector<int>> paddedImageMatrix);

};

#endif