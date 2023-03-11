#ifndef CSVWRITER_H
#define CSVWRITER_H

#include <fstream>
#include <vector>
#include <iostream>


void extern exportCSV(std::vector<std::vector<int>> filteredImage, int numCols, int numRows);

#endif