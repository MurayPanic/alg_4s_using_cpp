#include <iostream>
#include "gtest/gtest.h"

#define private public
    #include "SeamCarver.hpp"
#undef private

#define GTEST_COUT std::Cout<< "[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[         ] "



int main(int argc, char* argv[]){

    std::cout<<"This script is to test the SeamCarver head file"
            <<std::endl;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}