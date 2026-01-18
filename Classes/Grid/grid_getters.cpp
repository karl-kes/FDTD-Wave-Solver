#include "grid.hpp"

// Getters:
// Dimensions
std::size_t Grid::Nx() const {
    return Nx_;
}

std::size_t Grid::Ny() const {
    return Ny_;
}

std::size_t Grid::Nz() const {
    return Nz_;
}

// Grid Size:
double Grid::dx() const {
    return dx_;
}

double Grid::dy() const {
    return dy_;
}

double Grid::dz() const {
    return dz_;
}

// Wave Constants:
double Grid::eps() const {
    return eps_;
}

double Grid::mu() const {
    return mu_;
}

double Grid::c() const {
    return c_;
}

double Grid::c_sq() const {
    return c_*c_;
}

// Time Step:
double Grid::dt() const {
    return dt_;
}

double &Grid::Jx( std::size_t x, std::size_t y, std::size_t z ) {
    return Jx_[idx(x, y, z)];
}

double &Grid::Jy( std::size_t x, std::size_t y, std::size_t z ) {
    return Jy_[idx(x, y, z)];
}

double &Grid::Jz( std::size_t x, std::size_t y, std::size_t z ) {
    return Jz_[idx(x, y, z)];
}