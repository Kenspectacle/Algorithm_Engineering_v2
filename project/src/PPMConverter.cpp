#include "PPMConverter.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

/**
 * ToDo
 * 1. get header info
 * 2. turn img to grayscale matrix
 * 3. stitch vector back to ppm
 */

PPMConverter::PPMConverter(std::string imgName)
{
    this->imgPath = "static/" + imgName;
    this->imgStream.open(this->imgPath, std::ios::in | std::ios::binary);
    this->getImgMetaData();
}

/**
 * Extracts and saves header information from ppm image.
 * Expects the ppm file to be in P6 and therefore binary format,
 * throws exception if not given.
 */
imgMetaDataStruct PPMConverter::getImgMetaData()
{
    this->checkStream();

    std::string mode, s_width, s_height, s_max;

    this->imgStream >> this->imgMetaData.mode;
    eatNextComment();
    this->imgStream >> s_width;
    eatNextComment();
    this->imgStream >> s_height;
    eatNextComment();
    this->imgStream >> s_max;
    eatNextComment();

    if (this->imgMetaData.mode != "P6")
    {
        throw std::runtime_error("Error: " + this->imgPath + " is not in P6 format.");
    }

    this->imgMetaData.width = stoi(s_width);
    this->imgMetaData.height = stoi(s_height);
    this->imgMetaData.max = stoi(s_max);

    std::cout << "Header info: " << mode << " " << s_width << " " << s_height << " " << s_max << std::endl;

    return this->imgMetaData;
}

/**
 * Extracts the pixels from the .ppm bytestream. ifstream doesnt accept unsigned chars,
 * as given in the image. So we have to use an unsigned char buffer and cast them back
 * to signed chars.
 * All 3 values of one pixeel (r, g, b) are summed and devided by 3 for one gray value.
 */
void PPMConverter::extractPixelMatrix(std::vector<std::vector<int>> &imageMatrix,
                                      std::vector<std::vector<int>> &paddedImageMatrix)
{
    this->checkStream();

    // PPM width * PPM height * 3 for each pixel
    int sizeStream = this->imgMetaData.width * this->imgMetaData.height * 3;

    char *pixelArray = new char[sizeStream];
    this->imgStream.read(pixelArray, sizeStream);

    for (int i = 0; i < this->imgMetaData.height; i++) // loop width
    {
        for (int j = 0; j < this->imgMetaData.width; j++) // loop height
        {
            int greySum = 0;

            for (int k = 0; k < 3; k++) // loop 3 pixels
            {
                int idx = (i * this->imgMetaData.width * 3) + (j * 3) + k;
                unsigned char pixelValue = (unsigned char)pixelArray[idx];
                greySum += (int)pixelValue;
            }
            int greyValue = greySum / 3;

            imageMatrix[j][i] = greyValue;
            paddedImageMatrix[j + 1][i + 1] = greyValue;
            greySum = 0;
        }
    }
}

/**
 * Takes the meta information and transformed pixel matrix,
 * and returns the new and improved ppm image.
 */
void PPMConverter::convertToPPM(std::vector<std::vector<int>> &imageMatrix)
{
    std::string imgPath = "static/TEST_FILE.ppm";
    std::ofstream imgStreamOut(imgPath, std::ios::out | std::ios::trunc | std::ios::binary);

    if (!imgStreamOut.is_open() || imgStreamOut.fail())
    {
        throw std::runtime_error("Error: " + imgPath + " could not be opened for exporting.");
    }

    imgStreamOut << this->imgMetaData.mode << "\n";
    imgStreamOut << this->imgMetaData.width << "\n";
    imgStreamOut << this->imgMetaData.height << "\n";
    imgStreamOut << this->imgMetaData.max << "\n";

    for (int i = 0; i < this->imgMetaData.height; i++) // loop width
    {
        for (int j = 0; j < this->imgMetaData.width; j++) // loop height
        {
            for (int k = 0; k < 3; k++) // loop 3 pixels
            {
                imgStreamOut << (unsigned char)imageMatrix[j][i];
            }
        }
    }

    imgStreamOut.close();
}

/**
 * PPM allows for comments starting with # in the header at any place.
 * Todo:
 * - Bug: Multiline comments are not removed
 */
void PPMConverter::eatNextComment()
{
    char linebuf[1024];
    char nextToken;
    while (nextToken = this->imgStream.peek(), nextToken == '\n' || nextToken == '\r')
    {
        this->imgStream.get();
    }
    if (nextToken == '#')
    {
        this->imgStream.getline(linebuf, 1023);
    }
}

void PPMConverter::checkStream()
{
    if (!this->imgStream.is_open() || this->imgStream.fail())
    {
        throw std::runtime_error("Error: " + this->imgPath + " could not be opened.");
    }
}