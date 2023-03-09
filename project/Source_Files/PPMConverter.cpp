// Allocate

    std::vector<std::vector<int>> imageVect(img.rows, std::vector<int>(img.cols, 0));
    std::vector<std::vector<int>> paddedImageVect(img.rows + 2, std::vector<int>(img.cols + 2, 0));

    // Convert from Mat object to 2D Vectors

    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
        {
            int extracted = img.at<uchar>(i, j);
            // std::cout << extracted << std::endl;
            imageVect[i][j] = extracted;
            paddedImageVect[i + 1][j + 1] = extracted;
        }
    }
