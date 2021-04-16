#include <iostream>

#include "gtest/gtest.h"

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

#define private public
	#include "CircularSuffixArray.hpp"
#undef private

TEST(CircularSuffixArray_constructor, case_1){
	CircularSuffixArray CSA_ins{};	

}

TEST(CircularSuffixArray_constructor, case_2){
	std::string test_str="ABRACADABRA!";
	CircularSuffixArray CSA_ins(test_str);

}

TEST(CircularSuffixArray_index, case_1){
	std::string test_str="ABRACADABRA!";
	CircularSuffixArray CSA_ins(test_str);
	EXPECT_EQ(CSA_ins.index(0),11);
	EXPECT_EQ(CSA_ins.index(1),10);
	EXPECT_EQ(CSA_ins.index(2),7);
	EXPECT_EQ(CSA_ins.index(3),0);
	EXPECT_EQ(CSA_ins.index(4),3);
	EXPECT_EQ(CSA_ins.index(5),5);
	EXPECT_EQ(CSA_ins.index(6),8);
	EXPECT_EQ(CSA_ins.index(7),1);
	EXPECT_EQ(CSA_ins.index(8),4);
	EXPECT_EQ(CSA_ins.index(9),6);
	EXPECT_EQ(CSA_ins.index(10),9);
	EXPECT_EQ(CSA_ins.index(11),2);

}


TEST(CircularSuffixArray_index, case_2){
	std::string test_str="ABRACADABRA!";
	CircularSuffixArray CSA_ins(test_str);
	EXPECT_EQ(CSA_ins.index(11),2);

}

TEST(CircularSuffixArray_length, case_1){
	std::string test_str="ABRACADABRA!";
	CircularSuffixArray CSA_ins(test_str);
	EXPECT_EQ(CSA_ins.length(),12);

}

int main(int argc, char* argv[]){
	std::cout<<"This script is to test the CircularSuffixArray.hpp head file."
		<< std::endl;
	::testing::InitGoogleTest( &argc, argv);
	return RUN_ALL_TESTS();

}

