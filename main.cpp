#include <chrono>
#include <filesystem>

#include "Classes/grid.hpp"

int main() {
    /* 
        To compile and run.

        For No Parallel (NOT RECOMMENDED):
        g++ -std=c++17 main.cpp Classes/grid.cpp -o main.exe

        For Parallel (RECOMMENDED):
        g++ -std=c++17 main.cpp Classes/grid.cpp -o main.exe -fopenmp

        ./main.exe
    */

    std::filesystem::create_directories("output");
    Grid grid{ 50, 50, 50 };

    auto start = std::chrono::high_resolution_clock::now();
    for ( int t{}; t <= 1000; ++t ) {
        grid.inject_source( 5, 5, 1, 10 * std::sin( 0.5 * t ) );
        grid.inject_source( 45, 45, 1, 10 * std::sin( 0.5 * t ) );
        grid.step();
        if ( t % 10 == 0 ) {
            grid.output_slice( 1, "output/output" + std::to_string( t ) + ".csv" );
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << " ms" << std::endl;

    return 0;
}