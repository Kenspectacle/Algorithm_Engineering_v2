## Efficient Image Filter Using OpenMP

This is a project made to implement image filtering and enhancing algorithm in a highly efficient manner. The main idea is to utilize the advancement in hardware parallelism by utilizing multiple threads in a parallel program. 

## Setup

In order to use this library, you must first install OpenCV and OpenMP

### OpenCV Quick Start

Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip

Download and unpack sources:
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
unzip opencv.zip

Create build directory:
mkdir -p build && cd build

Configure:
cmake  ../opencv-4.x


Build:
cmake --build .

