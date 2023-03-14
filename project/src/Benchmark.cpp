#include "Benchmark.hpp"

#include <omp.h>
#include <iostream>
#include <vector>
#include <string>

Benchmark::Benchmark()
{
    this->structIdx = 0;
    this->programStartTime = omp_get_wtime();
}

void Benchmark::finishBenchmark()
{
    this->benchmarkStruct.start.push_back(this->programStartTime);
    this->benchmarkStruct.end.push_back(omp_get_wtime());
    this->benchmarkStruct.task.push_back("Whole program");
    std::cout << std::endl
              << this->benchmarkStruct.task[this->structIdx] << " time elapsed: "
              << this->benchmarkStruct.end[this->structIdx++] - this->programStartTime
              << std::endl;
}

void Benchmark::startBenchmark()
{
    this->benchmarkStruct.start.push_back(omp_get_wtime());
}

void Benchmark::stopBenchmark(std::string name)
{
    this->benchmarkStruct.end.push_back(omp_get_wtime());
    this->benchmarkStruct.task.push_back(name);
    std::cout << this->benchmarkStruct.task[this->structIdx] << " time elapsed: "
              << this->benchmarkStruct.end[this->structIdx] -
                     this->benchmarkStruct.start[this->structIdx++]
              << std::endl;
}

void Benchmark::exportCSV(int numThreads)
{
    std::ofstream myfile;
    myfile.open("Benchmark_Result.csv");
    myfile << "Task,Time_Elapsed,Num_Threads\n";
    for (int i = 0; i < this->structIdx; i++)
    {
        myfile << this->benchmarkStruct.task[i];
        myfile << ",";
        myfile << this->benchmarkStruct.end[i] - this->benchmarkStruct.start[i];
        myfile << ",";
        myfile << numThreads;
        myfile << "\n";
    }
}