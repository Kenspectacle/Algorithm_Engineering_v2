#ifndef PPMCONVERTER_H
#define PPMCONVERTER_H

/**
 * @brief 
 * 
 * @param imageName 
 * @param numRows 
 * @param numCols 
 */
void ocv_getImgInformation(std::string imageName, int *numRows, int *numCols);

/**
 * @brief 
 * 
 * @param imageMatrix 
 * @param paddedImageMatrix 
 * @param numRows 
 * @param numCols 
 */
void ocv_importImageToVector(std::vector<std::vector<int>> imageMatrix,
                             std::vector<std::vector<int>> paddedImageMatrix,
                             const int numRows, const int numCols);

#endif