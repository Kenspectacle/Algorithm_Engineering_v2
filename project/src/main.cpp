#include "Benchmark.hpp"
#include "PPMConverter.hpp"
#include "JPGConverter.hpp"
#include "ImageFilter.hpp"
#include "CSVWriter.hpp"

#include <iostream>
#include <vector>
#include <string>

template <typename T>
using Vec2D = std::vector<std::vector<T>>;

int main(const int argc, const char **argv)
{
    /* 0. Setup */
    Benchmark benchmark;

    /* 1. Step import and convert image */
    benchmark.startBenchmark();
    PPMConverter ppmConverter("text-from-book-big.ppm");
    const int numRows = ppmConverter.imgMetaData.height;
    const int numCols = ppmConverter.imgMetaData.width;
    benchmark.stopBenchmark("MetaData extraction");

    /* 2. Extract pixel matrix from image */
    Vec2D<int> imageVect(numRows, std::vector<int>(numCols, 0));
    Vec2D<int> paddedImageVect(numRows + 2, std::vector<int>(numCols + 2, 0));

    /* 2.1 For ppm files */
    benchmark.startBenchmark();
    ppmConverter.extractPixelMatrix(imageVect, paddedImageVect);
    benchmark.stopBenchmark("Pixel extraction");

    /* 3. Step Filter Transformations */
    benchmark.startBenchmark();
    Vec2D<int> blurredImage = gaussianFilter(paddedImageVect, numRows, numCols);
    benchmark.stopBenchmark("Applied Gaussian");

    benchmark.startBenchmark();
    Vec2D<int> medianedImage = medianFilter(blurredImage, imageVect, numRows, numCols);
    benchmark.stopBenchmark("Applied Median");

    benchmark.startBenchmark();
    Vec2D<int> filteredImage = customFilter(medianedImage, imageVect, numRows, numCols);
    benchmark.stopBenchmark("Applied Custom");

    /* 4. Convert pixel matrix back to ppm and Export */
    benchmark.startBenchmark();
    ppmConverter.convertToPPM(filteredImage);
    benchmark.stopBenchmark("Exported resulting");

    // exportCSV(filteredImage);

    benchmark.finishBenchmark();
    std::cout << "Job Done !" << std::endl;

    benchmark.exportCSV();
    std::cout << "Export benchmark to CSV done\n";


    return 0;
}
