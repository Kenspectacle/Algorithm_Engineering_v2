#ifndef PPMCONVERTER_H
#define PPMCONVERTER_H

/**
<<<<<<< HEAD
 * @brief 
 * 
 * @param imageName 
 * @param numRows 
 * @param numCols 
=======
 * @brief
 *
 * @param imageName
 * @param numRows
 * @param numCols
>>>>>>> a8016c6a12931bc51b6455dc01e109f71a96cb91
 */
void ocv_getImgInformation(std::string imageName, int *numRows, int *numCols);

/**
<<<<<<< HEAD
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
=======
 * @brief
 *
 * @param imageMatrix
 * @param paddedImageMatrix
 * @param numRows
 * @param numCols
 */
void ocv_importImageToVector(std::vector<std::vector<int>> imageMatrix,
                             std::vector<std::vector<int>> paddedImageMatrix,
                             const int *numRows, const int *numCols);
>>>>>>> a8016c6a12931bc51b6455dc01e109f71a96cb91

#endif