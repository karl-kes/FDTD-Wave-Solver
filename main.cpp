#include <iostream>
#include <memory>

class Grid {
private:
    int Nx_, Ny_, Nz_;                          // Grid Size
    double dx_, dy_, dz_, dt;                   // Differentials
    std::unique_ptr<double[]> Ex_, Ey_, Ez_;    // Electric Field
    std::unique_ptr<double[]> Bx_, By_, Bz_;    // Magnetic Field

public:
    // Constructor:
    Grid( int new_Nx, int new_Ny, int new_Nz = 1,
          double new_dx, double new_dy, double new_dz ):
    Nx_{ new_Nx }, Ny_{ new_Ny }, Nz_{ new_Nz },
    dx_{ new_dx }, dy_{ new_dy }, dz_{ new_dz } {
        
        int grid_size{ Nx_ * Ny_ * Nz_ };
        Ex_ = std::make_unique<double[]>( grid_size );
        Ey_ = std::make_unique<double[]>( grid_size );
        Ez_ = std::make_unique<double[]>( grid_size );
        Bx_ = std::make_unique<double[]>( grid_size );
        By_ = std::make_unique<double[]>( grid_size );
        Bz_ = std::make_unique<double[]>( grid_size );

        for ( int i{}; i < grid_size; ++i ) {
            Ex_[i] = 0.0;
            Ey_[i] = 0.0;
            Ez_[i] = 0.0;
            Bx_[i] = 0.0;
            By_[i] = 0.0;
            Bz_[i] = 0.0;
        }
    }
};

int main() {

    return 0;
}