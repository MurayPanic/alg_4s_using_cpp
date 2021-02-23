#include <iostream>
#include <vector>

#include "Picture.hpp"

#ifndef SEAMCARVER_HPP
#define SEAMCARVER_HPP

//Class declaration
class SeamCarver;

#endif

//Class definition

class SeamCarver{

        public:
            SeamCarver();
            SeamCarver(Picture);
            ~SeamCarver();
            Picture picture();
            int width();
            int height();
            double energy(int, int);
            std::vector<int> findHorizontalSeam();
            std::vector<int> findVerticalSeam();
            void removeHorizontalSeam( std::vector<int>);
            void removeVerticalSeam( std::vector<int> );
            

};