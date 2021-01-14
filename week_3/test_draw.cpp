#include <iostream>
#include <gtest/gtest.h>
#include "draw.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO]"

TEST(Draw, draw_a_point){
	Point point_ins(10, 20);
	Point point_ins_2(30,40);
	draw(point_ins);
	draw(point_ins_2);
	show();
		

}

TEST(Draw, draw_a_linesegment){
	Point point_ins_1(10,20);
	Point point_ins_2(30,40);
	Point point_ins_3(50,60);
	Point point_ins_4(70,80);

	LineSegment LS_ins_1(point_ins_1, point_ins_2);
	LineSegment LS_ins_2(point_ins_3, point_ins_4);

	draw(LS_ins_1);
	draw(LS_ins_2);
	show();
}

int main(int ac, char* av[]){

	std::cout<< "This script is to test the draw function "
		 << std::endl;

	::testing::InitGoogleTest(&ac, av);

	return RUN_ALL_TESTS();

}

