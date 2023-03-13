#include "PPMConverter.hpp"
#include "JPGConverter.hpp"
#include "ImageFilter.hpp"
#include "CSVWriter.hpp"
#include "omp.h"

#include <iostream>
#include <vector>
#include <string>

template <typename T>
using Vec2D = std::vector<std::vector<T>>;

int main(const int argc, const char **argv)
{   // benchmarks
    struct Benchmark {
        std::vector<double> start;
        std::vector<double> end;
        std::vector<std::string> task;
    };
    Benchmark benchmark;

    /* 0. Parse arguments ToDo */

    /* 1. Step import and convert image */
    benchmark.start.push_back(omp_get_wtime());
    PPMConverter ppmConverter("text-from-book-big.ppm");
    const int numRows = ppmConverter.imgMetaData.height;
    const int numCols = ppmConverter.imgMetaData.width;
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("MetaData extraction");
    std::cout << benchmark.task[0] << " done!" << std::endl;
    std::cout << benchmark.task[0] << " time elapsed: " << benchmark.end[0] - benchmark.start[0] << std::endl;

    /* 2. Extract pixel matrix from image */
    Vec2D<int> imageVect(numRows, std::vector<int>(numCols, 0));
    Vec2D<int> paddedImageVect(numRows + 2, std::vector<int>(numCols + 2, 0));

    /* 2.1 For ppm files */
    benchmark.start.push_back(omp_get_wtime());
    ppmConverter.extractPixelMatrix(imageVect, paddedImageVect);
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("Pixel extraction");
    std::cout << benchmark.task[1] << " done!" << std::endl;
    std::cout << benchmark.task[1] << " time elapsed: " << benchmark.end[1] - benchmark.start[1] << std::endl;


    /* 3. Step Filter Transformations */
    benchmark.start.push_back(omp_get_wtime());
    Vec2D<int> blurredImage = gaussianFilter(paddedImageVect, numRows, numCols);
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("Applied Gaussian Filter");
    std::cout << benchmark.task[2] << std::endl;
    std::cout << benchmark.task[2] << " time elapsed: " << benchmark.end[2] - benchmark.start[2] << std::endl;

    benchmark.start.push_back(omp_get_wtime());
    Vec2D<int> medianedImage = medianFilter(blurredImage, imageVect, numRows, numCols);
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("Applied Median Filter");
    std::cout << benchmark.task[3] << std::endl;
    std::cout << benchmark.task[3] << " time elapsed: " << benchmark.end[3] - benchmark.start[3] << std::endl;


    benchmark.start.push_back(omp_get_wtime());
    Vec2D<int> filteredImage = customFilter(medianedImage, imageVect, numRows, numCols);
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("Applied Custom Filter");
    std::cout << benchmark.task[3] << std::endl;
    std::cout << benchmark.task[3] << " time elapsed: " << benchmark.end[3] - benchmark.start[3] << std::endl;

    /* 4. Convert pixel matrix back to ppm and Export */
    benchmark.start.push_back(omp_get_wtime());
    ppmConverter.convertToPPM(filteredImage);
    benchmark.end.push_back(omp_get_wtime());
    benchmark.task.push_back("Exported resulting image to PPM");
    std::cout << benchmark.task[4] << std::endl;
    std::cout << benchmark.task[4] << " time elapsed: " << benchmark.end[4] - benchmark.start[4] << std::endl;


    // exportCSV(filteredImage);

    std::cout << "Job Done !" << std::endl;

    return 0;
}