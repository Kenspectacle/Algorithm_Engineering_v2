
#include <iomanip>
#include <iostream>
#include <omp.h>

using namespace std;

void integral_pi_sequential();
void integral_pi_parallel();

/*
    Warmup Aufgabe 1 - Parallelisiere PI mit einer! extra Line:
    - integral_pi_sequential() is there to compare the speed increase.
    - integral_pi_parallel() imlements the solution, using # pragma for reduce.
*/
int main()
{
    double start_time = omp_get_wtime();
    integral_pi_sequential();
    double run_time = omp_get_wtime() - start_time;
    cout << " with runTime sequential: " << run_time << " seconds\n";

    start_time = omp_get_wtime(); // wall clock time in seconds
    integral_pi_parallel();
    run_time = omp_get_wtime() - start_time;
    cout << " with runTime parallel: " << run_time << " seconds\n";
}

void integral_pi_sequential()
{
    int num_steps = 100000000;              // amount of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle
    double sum = 0.0;                       // for summing up all heights of rectangles

    for (int i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * width;      // midpoint
        sum = sum + (1.0 / (1.0 + x * x)); // add new height of a rectangle
    }
    double pi = sum * 4 * width; // compute pi

    cout << "pi with " << num_steps << " steps is " << setprecision(17)
         << pi << " in " << setprecision(6);
}

void integral_pi_parallel()
{
    int num_steps = 100000000;              // amount of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle
    double sum = 0.0;                       // for summing up all heights of rectangles

#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < num_steps; i++)
    {
        double x = (i + 0.5) * width;      // midpoint
        sum = sum + (1.0 / (1.0 + x * x)); // add new height of a rectangle
    }
    double pi = sum * 4 * width; // compute pi
    cout << "pi with " << num_steps << " steps is " << setprecision(17)
         << pi << " in " << setprecision(6);
}
