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
    this->imgStream.open(this->imgPath, std::ios::binary);
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

    this->imgStream >> mode;
    eatNextComment(); 
    this->imgStream >> s_width;
    eatNextComment(); 
    this->imgStream >> s_height;
    eatNextComment(); 
    this->imgStream >> s_max;
    eatNextComment(); 

    if (mode != "P6")
    {
        throw std::runtime_error("Error: " + this->imgPath + " is not in P6 format.");
    }

    this->imgMetaData.width = stoi(s_width);
    this->imgMetaData.height = stoi(s_height);
    this->imgMetaData.max = stoi(s_max);

    std::cout << "Header info: " << mode << " " << s_width << " " << s_height << " " << s_max << std::endl;

    return this->imgMetaData;
}

void PPMConverter::extractPixelMatrix(std::vector<std::vector<int>> &imageMatrix,
                                      std::vector<std::vector<int>> &paddedImageMatrix)
{
    this->checkStream();

    int sizeStream = this->imgMetaData.width * this->imgMetaData.height;
    std::cout << "Stream size " << sizeStream << std::endl;

    char* pixelArray = new char[sizeStream];
    this->imgStream.read(pixelArray, sizeStream);

    for(int i = 0; i < this->imgMetaData.height; i++)           // loop width
    {
        for(int j = 0; j < this->imgMetaData.width; j++)        // loop height
        {
            int greySum = 0;

            for(int k = 0; k < 3; k++)                          // loop 3 pixels
            {
                int idx = (i * this->imgMetaData.width*3) + (j*3) + k;
                // signed char or something idk, that sould work though
                greySum += (int)pixelArray[idx] + 128;
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
void convertToPPM(std::vector<std::vector<int>> &imageMatrix)
{
    
}

/**
 * PPM allows for comments starting with # in the header at any place.
 * Todo:
 * - Bug: Multiline comments are not removed
 */
void PPMConverter::eatNextComment()
{
    char linebuf[2024];
    char nextToken;
    while (nextToken = this->imgStream.peek(), nextToken == '\n' || nextToken == '\r')
    {
        this->imgStream.get();
    }
    if (nextToken == '#')
    {
        this->imgStream.getline(linebuf, 2023);
    }
}

void PPMConverter::checkStream()
{
    if ( !this->imgStream.is_open() || this->imgStream.fail() ) {
        throw std::runtime_error("Error: " + this->imgPath + " could not be opened.");
    }
}