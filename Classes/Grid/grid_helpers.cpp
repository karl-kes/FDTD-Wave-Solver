#include "grid.hpp"

std::size_t Grid::idx( std::size_t const x, std::size_t const y, std::size_t const z ) const {
    return x + Nx() * ( y + Ny() * z );
}

double Grid::curl_x( double const Y_0, double const Y_1,
                     double const Z_0, double const Z_1 ) const {
    double dZdY{ ( Z_1 - Z_0 ) / dy() };
    double dYdZ{ ( Y_1 - Y_0 ) / dz() };

    return ( dZdY - dYdZ );
}

double Grid::curl_y( double const X_0, double const X_1,
                     double const Z_0, double const Z_1 ) const {
    double dXdZ{ ( X_1 - X_0 ) / dz() };
    double dZdX{ ( Z_1 - Z_0 ) / dx() };

    return ( dXdZ - dZdX );
}

double Grid::curl_z( double const Y_0, double const Y_1,
                     double const X_0, double const X_1 ) const {
    double dYdX{ ( Y_1 - Y_0 ) / dx() };
    double dXdY{ ( X_1 - X_0 ) / dy() };

    return ( dYdX - dXdY );
}

double Grid::field( char field, char component, 
                    std::size_t x, std::size_t y, std::size_t z ) const {
    std::size_t i{ idx(x, y, z) };
    
    if ( field == 'e' ) {
        switch ( component ) {
            case 'x': return Ex_[i];
            case 'y': return Ey_[i];
            case 'z': return Ez_[i];
        }
    } else if ( field == 'b' ) {
        switch ( component ) {
            case 'x': return Bx_[i];
            case 'y': return By_[i];
            case 'z': return Bz_[i];
        }
    }
    throw std::invalid_argument("Invalid field or component specifier");
}

double &Grid::field( char field, char component,
                     std::size_t x, std::size_t y, std::size_t z ) {
    std::size_t i{ idx(x, y, z) };
    
    if ( field == 'e' ) {
        switch ( component ) {
            case 'x': return Ex_[i];
            case 'y': return Ey_[i];
            case 'z': return Ez_[i];
        }
    } else if ( field == 'b' ) {
        switch ( component ) {
            case 'x': return Bx_[i];
            case 'y': return By_[i];
            case 'z': return Bz_[i];
        }
    }
    throw std::invalid_argument("Invalid field or component specifier");
}

double Grid::field_magnitude(char field, std::size_t x, std::size_t y, std::size_t z) const {
    double Fx{ this->field( field, 'x', x, y, z ) };
    double Fy{ this->field( field, 'y', x, y, z ) };
    double Fz{ this->field( field, 'z', x, y, z ) };

    return std::sqrt( Fx*Fx + Fy*Fy + Fz*Fz );
}

double Grid::total_energy() const {
    double energy{};
    double dV{ dx() * dy() * dz() };

    #pragma omp parallel for collapse( 2 ) reduction( +:energy )
    for ( std::size_t z = 0; z < Nz(); ++z ) {
        for ( std::size_t y = 0; y < Ny(); ++y ) {
            #pragma omp simd
            for ( std::size_t x = 0; x < Nx(); ++x ) {
                std::size_t i = idx(x,y,z);

                double E_sq{ Ex_[i]*Ex_[i] + Ey_[i]*Ey_[i] + Ez_[i]*Ez_[i] };
                double B_sq{ Bx_[i]*Bx_[i] + By_[i]*By_[i] + Bz_[i]*Bz_[i] };

                energy += 0.5 * ( eps() * E_sq + B_sq / mu() );
            }
        }
    }
    return energy * dV;
}