#include <iomanip>
#include <iostream>

using namespace std;

void integral_pi_sequential();
void integral_pi_parallel();
void calculate_sum_for_pi();

/*
    Warmup Aufgabe 2 - Parallelisiere PI nur mit standard C++ code.
    - integral_pi_sequential() is there to compare the speed increase.
    - integral_pi_parallel() imlements the solution, using multiple threads and a mutex.
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
    std::vector<std::thread> threads;

    int num_steps = 100000000;              // amount of rectangles
    double width = 1.0 / double(num_steps); // width of a rectangle
    double sum = 0.0;                       // for summing up all heights of rectangles

    for (int i = 0; i < num_steps; i++)
    {
        threads.push_back(std::thread(bar, Foo()));
        double x = (i + 0.5) * width;      // midpoint
        sum = sum + (1.0 / (1.0 + x * x)); // add new height of a rectangle
    }
    double pi = sum * 4 * width; // compute pi
    cout << "pi with " << num_steps << " steps is " << setprecision(17)
         << pi << " in " << setprecision(6);
}

void calculate_sum_for_pi()
{

}