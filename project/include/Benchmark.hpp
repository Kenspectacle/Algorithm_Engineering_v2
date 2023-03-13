#ifndef OMPBenchmark_H
#define OMPBenchmark_H

#include <vector>
#include <string>
#include <fstream>

struct BenchmarkStruct
{
    std::vector<double> start;
    std::vector<double> end;
    std::vector<std::string> task;
};

class Benchmark
{
private:
    int structIdx;
    double programStartTime;
    BenchmarkStruct benchmarkStruct;

public:
    Benchmark();

    void finishBenchmark();
    void startBenchmark();
    void stopBenchmark(std::string name);
    void exportCSV(int numThreads);
};

#endif