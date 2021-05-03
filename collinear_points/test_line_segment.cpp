#include <iostream>
#include <gtest/gtest.h>
#include "LineSegment.hpp"
#define GTEST_COUT std::cout<<"[CUSTOM INFO]"

TEST(LineSegmentTest, constructor){
	LineSegment LS_ins{};
	EXPECT_EQ(nullptr, LS_ins.p);
	EXPECT_EQ(nullptr, LS_ins.q);
	Point p_ins_1(10,20);
	Point p_ins_2(30,40);
	LineSegment LS_ins_2(p_ins_1, p_ins_2);
	EXPECT_TRUE((*LS_ins_2.p)==p_ins_1);
	EXPECT_TRUE((*LS_ins_2.q)==p_ins_2);
	EXPECT_TRUE(p_ins_1<p_ins_2);
	EXPECT_TRUE(*LS_ins_2.p < p_ins_2);
}

TEST(LineSegmentTest, toString){
	Point p_ins_1(10,20);
	Point p_ins_2(30,40);
	Point p_ins_3(50,60);
	LineSegment LS_ins(p_ins_1, p_ins_2);
	GTEST_COUT<<"The line segment is" <<LS_ins.toString()<<std::endl;
	EXPECT_EQ("(10,20)->(30,40)",LS_ins.toString());
	LineSegment LS_ins_2(p_ins_2, p_ins_1);
	LineSegment LS_ins_3(p_ins_1, p_ins_3);
	EXPECT_TRUE(LS_ins==LS_ins_2);
	EXPECT_TRUE(LS_ins==LS_ins);
	EXPECT_TRUE(LS_ins_2==LS_ins);

	
}



int main(int ac, char* av[]){
	std::cout<<"This script is to test the LineSegment head file"
		<<std::endl;
	
	::testing::InitGoogleTest(&ac,av);
	return RUN_ALL_TESTS();
}
