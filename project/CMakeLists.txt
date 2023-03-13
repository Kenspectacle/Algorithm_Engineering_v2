cmake_minimum_required(VERSION 2.8)
project( ImageEnhancing )
find_package(OpenMP REQUIRED)

add_executable( main
    src/PPMConverter.cpp 
    src/JPGConverter.cpp
    src/ImageFilter.cpp 
    src/CSVWriter.cpp
    src/main.cpp )
target_include_directories(main PRIVATE include/)
add_compile_options( -O0 -g3 )
add_compile_options( -fopenmp )
target_link_libraries( main ${OpenCV_LIBS} )
target_link_libraries(main PRIVATE OpenMP::OpenMP_CXX)