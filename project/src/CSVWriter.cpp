#include "CSVWriter.hpp"

void exportCSV(const std::vector<std::vector<int>> &filteredImage)
{
    std::ofstream myfile;
    myfile.open("FilteredImage.csv");
    for (int i = 0; i < filteredImage.size(); i++)
    {
        myfile << "\n";
        for (int j = 0; j < filteredImage[0].size(); j++)
        {
            if (j == filteredImage[0].size() - 1)
            {
                // last column
                myfile << filteredImage[i][j];
                break;
            }
            myfile << filteredImage[i][j];
            myfile << ",";
        }
    }
    myfile.close();
}