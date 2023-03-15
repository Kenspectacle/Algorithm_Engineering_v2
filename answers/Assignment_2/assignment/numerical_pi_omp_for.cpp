#include <iomanip>
#include <iostream>
#include <omp.h>

using namespace std;

/**
 * Assignment 2.1. Changes to old numerical PI can be seen in the comments.
 */
int main()
{
    int num_steps = 100000000;
    double width = 1.0 / double(num_steps);
    double sum = 0.0;
    double start_time = omp_get_wtime();

#pragma omp parallel num_threads(4)
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        double sum_local = 0.0;

#pragma omp for                             // CHANGE Added omp for to auto parallellize
        for (int i = 0; i < num_steps; ++i) // CHANGE made loop normal
        {
            double x = (i + 0.5) * width;
            sum_local = sum_local + (1.0 / (1.0 + x * x));
        }
#pragma omp atomic
        sum += sum_local;
    }
    double pi = sum * 4 * width;
    double run_time = omp_get_wtime() - start_time;

    cout << "PI with " << num_steps << " steps is " << setprecision(17) << pi
         << " in " << setprecision(6) << " with runTime parallel: " << run_time << " seconds\n";
}
