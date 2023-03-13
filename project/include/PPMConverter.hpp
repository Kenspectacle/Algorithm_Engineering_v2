#ifndef PPMCONVERTER_H
#define PPMCONVERTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

/**
 * Meta data struct for the ppm format.
 */
struct imgMetaDataStruct
{
    std::string mode;
    int width, height, max;
};

class PPMConverter
{
private:
    std::string imgName;
    std::string imgPath;
    std::ifstream imgStream;

    void eatNextComment();
    void checkStream();
    bool endsWith(std::string const &str, std::string const &suffix);

public:
    imgMetaDataStruct imgMetaData;

    PPMConverter(const std::string imgName);

    imgMetaDataStruct getImgMetaData();
    void extractPixelMatrix(std::vector<std::vector<int>> &imageMatrix,
                            std::vector<std::vector<int>> &paddedImageMatrix);
    void convertToPPM(const std::vector<std::vector<int>> &imageMatrix);
};

#endif