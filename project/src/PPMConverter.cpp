#include "PPMConverter.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <omp.h>

/**
 * @brief Importer and Exporter for .ppm image files.
 * Extracts the meta data from a file given to the constructor and stores it.
 * Extracts the pixel using (@extractPixelMatrix(...)) for further processing
 * and stitches a processed matrix back together with the meta data using (@convertToPPM).
 *
 * @param imgName Name of the image with extension .ppm
 */
PPMConverter::PPMConverter(const std::string imgName)
{
    if (!this->endsWith(imgName, ".ppm"))
    {
        throw std::runtime_error("Error: " + imgName + " is not a .ppm file.");
    }

    this->imgName = imgName;
    this->imgPath = "static/" + imgName;
    this->imgStream.open(this->imgPath, std::ios::in | std::ios::binary);
    this->getImgMetaData();
}

/**
 * @brief Extracts and saves header information from a .ppm image.
 * Expects the ppm file to be in P6 and therefore binary format,
 * throws exception if not in this format. Width is multiplied by 3
 * for all 3 values of a pixel.
 *
 * @return imgMetaDataStruct struct with the image meta data
 */
imgMetaDataStruct PPMConverter::getImgMetaData()
{
    this->checkStream();

    std::string s_width, s_height, s_max;

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

    // Width times 3 for the r, g, b values per pixel
    this->imgMetaData.width = stoi(s_width) * 3;
    this->imgMetaData.height = stoi(s_height);
    this->imgMetaData.max = stoi(s_max);

    std::cout << "Header info: " << this->imgMetaData.mode << " " << s_width << " " << s_height << " " << s_max << std::endl;

    return this->imgMetaData;
}

/**
 * @brief Extracts the pixels from the .ppm bytestream. @(ifstream) doesnt accept unsigned chars,
 * as given in the image. So we have to use an unsigned char buffer and cast them back
 * to signed chars.
 * All 3 values per pixel (r, g, b) are set to the same grey value.
 *
 * @param imageMatrix for the values to be stored in
 * @param paddedImageMatrix the same matrix with padding
 */
void PPMConverter::extractPixelMatrix(std::vector<std::vector<int>> &imageMatrix,
                                      std::vector<std::vector<int>> &paddedImageMatrix)
{
    this->checkStream();

    int sizeStream = this->imgMetaData.width * this->imgMetaData.height;
    char *pixelArray = new char[sizeStream];
    this->imgStream.read(pixelArray, sizeStream);

#pragma omp parallel for collapse(2)
    for (int i = 0; i < this->imgMetaData.height; i++)
    {
        for (int j = 0; j < this->imgMetaData.width; j += 3) // Jump over 3 values of one pixel
        {
            int rgb[3];
            int idx = (i * this->imgMetaData.width) + j;
#pragma omp simd
            for (int k = 0; k < 3; k++) // Calculate the greyValue using r, g and b of one pixel
            {
                unsigned char pixelValue = (unsigned char)pixelArray[idx + k];
                rgb[k] = (int)pixelValue;
            }

            int greyValue = (rgb[0] * 0.299) + (rgb[1] * 0.587) + (rgb[2] * 0.114);
#pragma omp simd
            for (int k = 0; k < 3; k++)
            {
                imageMatrix[i][j + k] = greyValue;
                paddedImageMatrix[i + 1][j + k + 1] = greyValue;
            }
        }
    }
    delete[] pixelArray;
}

/**
 * @brief Takes the meta data and transformed pixel matrix
 * and returns the new and improved ppm image.
 *
 * Hard to optimize because we must write serialized to the imgStreamOut,
 * so we dont do that here.
 *
 * @param imageMatrix
 */
void PPMConverter::convertToPPM(const std::vector<std::vector<int>> &imageMatrix)
{
    std::string imgPath = "static/enhanced_" + this->imgName;
    std::ofstream imgStreamOut(imgPath, std::ios::out | std::ios::trunc | std::ios::binary);

    if (!imgStreamOut.is_open() || imgStreamOut.fail())
    {
        throw std::runtime_error("Error: " + imgPath + " could not be opened for exporting.");
    }

    imgStreamOut << this->imgMetaData.mode << "\n";
    // Dont forget to divide by 3 again for the pixels.
    imgStreamOut << this->imgMetaData.width / 3 << "\n";
    imgStreamOut << this->imgMetaData.height << "\n";
    imgStreamOut << this->imgMetaData.max << "\n";

    for (int i = 0; i < this->imgMetaData.height; i++)
    {
        for (int j = 0; j < this->imgMetaData.width; j += 3)
        {
            for (int k = 0; k < 3; k++)
            {
                imgStreamOut << (unsigned char)imageMatrix[i][j + k];
            }
        }
    }

    imgStreamOut.flush();
    imgStreamOut.close();
}

/**
 * @brief PPM allows for comments starting with # in the header at any place.
 * BUG: 2 or more comments at once are not eaten.
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

bool PPMConverter::endsWith(std::string const &str, std::string const &suffix)
{
    if (str.length() < suffix.length())
    {
        return false;
    }
    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}