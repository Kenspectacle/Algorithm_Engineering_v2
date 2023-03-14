#include "Benchmark.hpp"
#include "PPMConverter.hpp"
#include "JPGConverter.hpp"
#include "ImageFilter.hpp"
#include "CSVWriter.hpp"

#include <unistd.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include <string>

template <typename T>
using Vec2D = std::vector<std::vector<T>>;

struct argumentsStruct
{
    std::string fileName;
    int numThreads;
    bool isExtremeMode;
};

argumentsStruct parseArguments(const int argc, char **argv);

int main(const int argc, char **argv)
{
    /* 0. Setup */
    argumentsStruct arguments = parseArguments(argc, argv);
    Benchmark benchmark;

    /* 1. Step import and convert image */
    benchmark.startBenchmark();
    PPMConverter ppmConverter(arguments.fileName);
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
    benchmark.stopBenchmark("Gaussian Filter");

    benchmark.startBenchmark();
    Vec2D<int> medianedImage = medianFilter(blurredImage, imageVect, numRows, numCols);
    benchmark.stopBenchmark("Median Filter");

    Vec2D<int> filteredImage;
    if (arguments.isExtremeMode)
    {
        benchmark.startBenchmark();
        filteredImage = customFilterExtreme(medianedImage, imageVect, numRows, numCols);
        benchmark.stopBenchmark("Custom Filter");
    }
    else
    {
        benchmark.startBenchmark();
        filteredImage = customFilter(medianedImage, imageVect, numRows, numCols);
        benchmark.stopBenchmark("Custom Filter Extreme");
    }

    /* 4. Convert pixel matrix back to ppm and Export */
    benchmark.startBenchmark();
    ppmConverter.convertToPPM(filteredImage);
    benchmark.stopBenchmark("Exporting PPM");

    benchmark.finishBenchmark();
    benchmark.exportCSV(arguments.numThreads);
    std::cout << "Job Done !" << std::endl;

    return 0;
}

/**
 * $ ./main
 * --fileName=fileName
 * --num_threads=n
 * --extremeMode
 * --help
 */
argumentsStruct parseArguments(const int argc, char **argv)
{
    argumentsStruct arguments;
    arguments.isExtremeMode = false;
    arguments.numThreads = -1;
    int c;

    while ((c = getopt(argc, argv, "f:n:eh")) != -1)
    {
        switch (c)
        {
        case 'f':
            arguments.fileName = optarg;
            break;
        case 'n':
            arguments.numThreads = std::stoi(optarg);
            omp_set_num_threads(arguments.numThreads);
            break;
        case 'e':
            arguments.isExtremeMode = true;
            break;
        case 'h':
            std::cout << "Run: ./main -f=file_name -n=num_threads -e (extreme mode) -h (help)" << std::endl;
            exit(0);
            break;
        default:
            abort();
        }
    }

    if (arguments.fileName.empty())
    {
        std::cout << "No file_name given, using /static/text-from-book-big.ppm" << std::endl;
        arguments.fileName = "text-from-book-big.ppm";
    }

    if (arguments.numThreads < 0)
    {
        std::cout << "No thread_num given, using 4 deafault threads." << std::endl;
        omp_set_num_threads(4);
        arguments.numThreads = 4;
    }

    if (arguments.isExtremeMode)
    {
        std::cout << "Using extreme mode for very spooky dark images." << std::endl;
    }

    // Sorry but i want that new line.
    if (arguments.fileName.empty() || arguments.numThreads < 0 || arguments.isExtremeMode)
    {
        std::cout << std::endl;
    }

    return arguments;
}
