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

    // Clear previous and create new output folder.
    std::filesystem::remove_all("output");
    std::filesystem::create_directories("output");

    int constexpr elapsed_time{ 1000 };
    std::size_t constexpr Nx{ 50 }, Ny{ 50 }, Nz{ 50 };

    Grid grid{ Nx, Ny, Nz };
    grid.inject_source( 25, 25, 25, 100.0 );

    double initial_energy{ grid.total_energy() };
    double max_energy_drift{ initial_energy };

    auto start = std::chrono::high_resolution_clock::now();
    for ( int t{}; t <= elapsed_time; ++t ) {
        grid.step();

        // Max between current and previous max.
        max_energy_drift = std::max( grid.total_energy(), max_energy_drift );

        if ( t % 10 == 0 ) {
            std::string t_sec{ std::to_string( t ) };
            grid.magnitude_slice( 1, "output/E" + t_sec + ".csv", 'E' );
            grid.magnitude_slice( 1, "output/B" + t_sec + ".csv", 'B' );
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    double drift{ 100 * ( max_energy_drift - initial_energy ) / initial_energy };

    std::cout << "Physical Time Simulated: " << elapsed_time * grid.dt() << " s" << std::endl;
    std::cout << "Duration of Simulation: " << duration.count() << " ms" << std::endl;
    std::cout << "Max Energy Drift: " << drift << "%" << std::endl;

    return 0;
}