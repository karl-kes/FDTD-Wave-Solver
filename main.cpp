#include <iostream>
#include <memory>
#include <cmath>

class Grid {
private:
    int Nx_, Ny_, Nz_;                          // Grid Size
    double dx_, dy_, dz_;                       // Spatial Differentials
    double c_;                                  // Light Speed
    double dt_;                                 // Time Differential
    std::unique_ptr<double[]> Ex_, Ey_, Ez_;    // Electric Field
    std::unique_ptr<double[]> Bx_, By_, Bz_;    // Magnetic Field

public:
    // Constructor:
    Grid( int new_Nx = 1, int new_Ny = 1, int new_Nz = 1,
          double new_dx = 1.0, double new_dy = 1.0, double new_dz = 1.0,
          double new_c = 1.0 ):
    Nx_{ new_Nx }, Ny_{ new_Ny }, Nz_{ new_Nz },
    dx_{ new_dx }, dy_{ new_dy }, dz_{ new_dz },
    c_{ new_c },
    dt_{ 0.99 / ( c() * std::sqrt( 1.0/(dx()*dx()) + 1.0/(dy()*dy()) + 1.0/(dz()*dz()) ) ) } {
        
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

    // Solving:
    void update_B() {

    }
    void update_E() {

    }

    // Getters:
    double dx() const {
        return dx_;
    }
    double dy() const {
        return dy_;
    }
    double dz() const {
        return dz_;
    }
    double c() const {
        return c_;
    }
    double dt() const {
        return dt_;
    }
    int Nx() const {
        return Nx_;
    }
    int Ny() const {
        return Ny_;
    }
    int Nz() const {
        return Nz_;
    }

    // Setters:

    // Helpers:
    double curl( double const dt ) {

    }
    std::size_t idx( std::size_t const x, std::size_t const y, std::size_t const z ) const {
        return x + Nx() * ( y + Ny() * z );
    }

};

int main() {

    return 0;
}