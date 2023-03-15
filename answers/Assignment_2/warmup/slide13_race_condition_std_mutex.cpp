#include <iostream>
#include <mutex>
#include <omp.h>
#include <iomanip>

using namespace std;

std::mutex m;

/**
 * @brief Coding Warump 2.1 Fix  the race condition bug on slide 13,
 * using std::mutex. Solution is to surround pi with a mutex lock.
 */
int main()
{
    double pi = 0.0;
    int num_steps = 100000000;
    double width = 1.0 / double(num_steps);

#pragma omp parallel num_threads(4)
    {
        int num_steps = 100000000;
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        double sum_local = 0.0;

        for (int i = thread_id; i < num_steps; i += num_threads)
        {
            double x = (i + 0.5) * width;                  // midpoint
            sum_local = sum_local + (1.0 / (1.0 + x * x)); // add new height
        }
        m.lock();
        pi += sum_local * 4 * width;
        m.unlock();
    }

    cout << "PI with #" << num_steps << " steps is " << setprecision(17)
         << pi << endl;
}
