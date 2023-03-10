#include "../include/PPMConverter.hpp"

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

    this->imgMetaData.width = stoi(s_width);
    this->imgMetaData.height = stoi(s_height);
    this->imgMetaData.max = stoi(s_max);

    std::cout << "Header info: " << mode << " " << s_width << " " << s_height << " " << s_max << std::endl;

    return this->imgMetaData;
}

void PPMConverter::extractPixelMatrix(std::vector<std::vector<int>> imageMatrix,
                                      std::vector<std::vector<int>> paddedImageMatrix)
{
    this->checkStream();

    int sizeStream = this->imgMetaData.width * this->imgMetaData.height * 3;
    std::cout << "Stream size " << sizeStream << std::endl;

    char* pixelArray = new char[sizeStream];
    this->imgStream.read(pixelArray, sizeStream);

    int min = 0;
    int max = 0;

    // for(int i = 0; i < this->imgMetaData.height; i++)           // loop width
    // {
    //     for(int j = 0; j < this->imgMetaData.width; j++)        // loop height
    //     {
    //         for(int k = 0; k < 3; k++)                          // loop 3 pixels
    //         {
    //             int idx = i * this->imgMetaData.width*3 + j*3 + k;
    //             std::cout << idx << " ";
    //             int value = (int)pixelArray[idx];

    //             if (value > min)
    //             {
    //                 min = value;
    //             }
    //             if (value < max)
    //             {
    //                 max = value;
    //             }
    //         }    
    //         if (j == 2)
    //         {
    //             break;
    //         }
    //     }   
    // }

    for(int i = 0; i < sizeStream; i++)
    {
        int value = (int)pixelArray[i] + 128;
        // std::cout << pixelArray[i] << " ";

        if (value > min)
        {
            min = value;
        }
        if (value < max)
        {
            max = value;
        }
    }
    std::cout << min << " " << max << std::endl;

    // Convert from Mat object to 2D Vectors
    // for (int i = 0; i < numRows; i++)
    // {
    //     for (int j = 0; j < numCols; j++)
    //     {
    //         // int extracted = img.at<uchar>(i, j);
    //         int extracted = 1;
    //         imageMatrix[i][j] = extracted;
    //         paddedImageMatrix[i + 1][j + 1] = extracted;
    //     }
    // }
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