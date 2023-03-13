#include "Benchmark.hpp"

#include "omp.h"

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
    this->benchmarkStruct.end.push_back(omp_get_wtime());
    this->benchmarkStruct.task.push_back("Whole program");
    std::cout << this->benchmarkStruct.task[this->structIdx] << " time elapsed: "
              << this->benchmarkStruct.end[this->structIdx] - this->programStartTime
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