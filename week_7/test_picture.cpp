#include <iostream>
#include "gtest/gtest.h"

#define private public
    #include "Picture.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

int main(int argc, char* argv[]){

    std::cout<< "This script is to test the Picture head file"
            <<std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
