#include "grid.hpp"

void Grid::add_source( std::unique_ptr<Source> source ) {
    sources_.push_back( std::move( source ) );
}

void Grid::apply_sources( double time_step ) {
    for ( auto& source : sources_ ) {
        source->apply( *this, time_step );
    }
}

void Grid::update_B() {
    // ∂B/∂t = -curl( E )
    #pragma omp parallel for collapse( 2 )
    // Start at 0; stagger for Yee-Cell grid.
    for ( std::size_t z = 0; z < Nz() - 1; ++z ) {
        for ( std::size_t y = 0; y < Ny() - 1; ++y ) {
            #pragma omp simd
            for ( std::size_t x = 0; x < Nx() - 1; ++x ) {
                // Take curl of components and apply B -= ∂B:
                // ∂B_x = ∂t * curl_x( E )
                Bx_[idx(x,y,z)] -= dt() * curl_x( Ey_[idx(x,y,z)], Ey_[idx(x,y,z+1)],
                                                  Ez_[idx(x,y,z)], Ez_[idx(x,y+1,z)] );

                // ∂B_y = ∂t * curl_y( E )
                By_[idx(x,y,z)] -= dt() * curl_y( Ex_[idx(x,y,z)], Ex_[idx(x,y,z+1)],
                                                  Ez_[idx(x,y,z)], Ez_[idx(x+1,y,z)] );

                // ∂B_z = ∂t * curl_z( E )
                Bz_[idx(x,y,z)] -= dt() * curl_z( Ey_[idx(x,y,z)], Ey_[idx(x+1,y,z)],
                                                  Ex_[idx(x,y,z)], Ex_[idx(x,y+1,z)] );
            }
        }
    }
}

void Grid::update_E() {
    // ∂E/∂t = c*c * curl(B)
    #pragma omp parallel for collapse( 2 )
    // Start at 1; stagger for Yee-Cell grid.
    for ( std::size_t z = 1; z < Nz(); ++z ) {
        for ( std::size_t y = 1; y < Ny(); ++y ) {
            #pragma omp simd
            for ( std::size_t x = 1; x < Nx(); ++x ) {
                // Curl of components and apply E += ∂E:
                // ∂E_x = ∂t * c*c * (∂E_z/∂y - ∂E_y/∂z)
                Ex_[idx(x,y,z)] += dt() * ( c_sq() * curl_x( By_[idx(x,y,z-1)], By_[idx(x,y,z)],
                                                             Bz_[idx(x,y-1,z)], Bz_[idx(x,y,z)] )
                                                    - Jx_[idx(x,y,z)] / eps() );

                // ∂E_y = ∂t * c*c * (∂Ex/∂z - ∂Ez/∂x)
                Ey_[idx(x,y,z)] += dt() * ( c_sq() * curl_y( Bx_[idx(x,y,z-1)], Bx_[idx(x,y,z)],
                                                             Bz_[idx(x-1,y,z)], Bz_[idx(x,y,z)] )
                                                    - Jy_[idx(x,y,z)] / eps() );

                // ∂E_z = ∂t * c*c * (∂Ex/∂y - ∂Ey/∂x)
                Ez_[idx(x,y,z)] += dt() * ( c_sq() * curl_z( By_[idx(x-1,y,z)], By_[idx(x,y,z)],
                                                             Bx_[idx(x,y-1,z)], Bx_[idx(x,y,z)] )
                                                    - Jz_[idx(x,y,z)] / eps() ) ;
            }
        }
    }
}

void Grid::step() {
    update_B();
    update_E();
}