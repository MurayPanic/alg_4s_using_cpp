#include <iostream>
#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

#define private public
        #include "BurrowsWheeler.cpp"
#undef private

TEST(BurrowWheelers_constructor, case_1){
	BurrowsWheeler BW_ins{};
}

TEST(BurrowWheelers_transform, case_1){
	
	BurrowsWheeler BW_ins{};
 	std::string test_str = "ABRACADABRA!";
	BurrowsWheeler.main(test_str, "-");
}



int main(int argc, char* argv[]){
        std::cout<<"This script is to test the BurrowsWheeler.hpp head file."
                << std::endl;
        ::testing::InitGoogleTest( &argc, argv);
        return RUN_ALL_TESTS();

}

