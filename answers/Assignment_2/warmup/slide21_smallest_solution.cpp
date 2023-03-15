#include <atomic>
#include <iostream>
#include <omp.h>

using namespace std;

/**
 * @brief Coding Warump 2.4 Find always the smallest number.
 * Solution is to only say we found a solution, if its smaller than the current solution.
 */

bool is_solution(int number)
{ // test if number solves the problem
    for (volatile int i = 10000000; i--;)
    {
    } // mock computation
    return number > 133 && number < 140;
}

int main()
{
    constexpr int biggest_possible_number = 10000;
    atomic<bool> solution_found(false); // if true than we found the solution
    atomic<int> final_solution(INT32_MAX);
    final_solution = biggest_possible_number;
    const double start = omp_get_wtime();

#pragma omp parallel for schedule(dynamic) // start parallel region
    for (int i = 0; i < biggest_possible_number; ++i)
    {
        if (solution_found) // we found the solution, just continue iterating
            continue;
        if (is_solution(i) && i <= final_solution)
        { // find some solution, not necessary the smallest
            solution_found = true;
            final_solution = i;
        }
    } // end parallel region
    // check if we've found a solution at all is omitted, you can add the check
    cout << "The solution is: " << final_solution << endl;
    cout << omp_get_wtime() - start << " seconds" << endl;
}
