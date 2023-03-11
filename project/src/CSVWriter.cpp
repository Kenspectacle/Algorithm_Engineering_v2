#include "CSVWriter.hpp"

void exportCSV(std::vector<std::vector<int>> filteredImage, int numCols, int numRows)
{   std::cout << "test";
    std::ofstream myfile;
    myfile.open("FilteredImage.csv");
    std::cout << "vsize:" << filteredImage.size() << " rows: " << filteredImage[0].size();

    for (int i = 0; i < filteredImage.size(); i++) {
        myfile << "\n";
        for (int j = 0; j < filteredImage[0].size(); j++) {
            if(j == numCols - 1) {
                //last column
                myfile << filteredImage[i][j];
                break;
            }
            myfile << filteredImage[i][j];
            myfile << ",";
        }
    }
    myfile.close();
}