#include <iostream>
#include <gtest/gtest.h>
#include "Point2D.hpp"
#define GTEST_COUT  std::cout<<"[CUSTOM INFO] "


TEST(Point2d_constructor, case_1){
	Point2D point_ins_1{};
	Point2D point_ins_2(3.0,4.0);
	
}

TEST(Point2d_xandy,case_1){
	Point2D point_ins_1(3.0,4.0);
	EXPECT_EQ(3.0, point_ins_1.x() );
	EXPECT_EQ(4.0, point_ins_1.y() );
}

TEST(Point2d_distanceTo, case_1){
	Point2D point_ins_1(0,0);
	Point2D point_ins_2(3,4);
	double dist = point_ins_1.distanceTo(point_ins_2);
	EXPECT_EQ(5,dist);

}

TEST(Point2d_distanceSquaredTo, case_1){
	Point2D point_ins_1(0,0);
	Point2D point_ins_2(3,4);
	double dist = point_ins_1.distanceSquaredTo(point_ins_2);
	EXPECT_EQ(25,dist);
}

TEST(Point2D_less_than_operator, case_1){
	Point2D point_ins(10,20);
	Point2D point_ins_ver(10,0);
	Point2D point_ins_hoz(30,20);
	Point2D point_ins_same(10,20);
	EXPECT_TRUE(point_ins_ver < point_ins);
	EXPECT_TRUE(point_ins < point_ins_hoz);
	EXPECT_TRUE(point_ins == point_ins);
	EXPECT_TRUE(point_ins == point_ins_same);


}

TEST(Point2D_toString, case_1){
	std::string expect_str="(3.140000,4.260000)";
	Point2D point_ins(3.14, 4.26);
	EXPECT_EQ(expect_str, point_ins.toString());

}

int main(int argc, char* argv[]){
	std::cout<< "This script is to test the Point2D.hpp head file"
		<< std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
