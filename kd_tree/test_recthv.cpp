#include <iostream>
#include <gtest/gtest.h>
#include <exception>
#include "RectHV.hpp"

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(RectHV_constructor, case_1){
	RectHV rect_ins{};
	RectHV rect_ins_1(1.00,2.00,3.00,4.00);
	EXPECT_THROW(RectHV(3.00,4.00,1.00,2.00), std::invalid_argument );
}

TEST(RectHV_coord_func, case_1){

	RectHV rect_ins(1.00,2.00,3.00,4.00);
	EXPECT_EQ(1.00, rect_ins.xmin() );
	EXPECT_EQ(2.00, rect_ins.ymin() );
	EXPECT_EQ(3.00, rect_ins.xmax() );
	EXPECT_EQ(4.00, rect_ins.ymax() );
}

TEST(RectHV_equal_operator, case_1){
	RectHV rect_ins_1(1.00,2.00,3.00,4.00);
	RectHV rect_ins_2(1.00,2.00,3.00,4.00);
	RectHV rect_ins_3(0.00,0.00,0.168,3.14);
	EXPECT_TRUE(rect_ins_1 == rect_ins_1);
	EXPECT_TRUE(rect_ins_1 == rect_ins_2);
	EXPECT_FALSE(rect_ins_1 == rect_ins_3);
}

TEST(RectHV_contains, case_1){
	RectHV rect_ins_1(1.00,2.00,3.00,4.00);
	Point2D p_1(0.618, 3.14);
	Point2D p_2(1.5,2.5);
	Point2D p_3(1.00, 2.5);
	Point2D p_4(1.00,2.00);
	EXPECT_TRUE( rect_ins_1.contains(p_2) );
	EXPECT_TRUE( rect_ins_1.contains(p_3) );
	EXPECT_TRUE( rect_ins_1.contains(p_4) );
	EXPECT_FALSE( rect_ins_1.contains(p_1) );
}

TEST(RectHV_toString, case_1){
	RectHV rect_ins_1(0.618,3.14,11.11,12.12);
	std::string expect_str="[0.618000,11.110000] x [3.140000,12.120000]";
	EXPECT_EQ(expect_str, rect_ins_1.toString());
}


TEST(RectHV_intersects, case_1){
	RectHV rect_ins_1(1,2,3,4);
	RectHV rect_ins_2(1.5,2.5, 1.8,2.8);
	
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_2));

	RectHV rect_ins_3(3,4,5,6 );
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_3) );

	RectHV rect_ins_4(3,2,5,4);
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_4) );

	RectHV rect_ins_5(1,2,5,6);
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_5) );
	
	RectHV rect_ins_6(7,8,9,10);
	EXPECT_FALSE(rect_ins_1.intersects(rect_ins_6) );

}

TEST(RectHV_intersects, case_2){
	RectHV rect_ins_1(0.1,0.1,0.6,0.6);
	RectHV rect_ins_2(0,0, 0.7,1.0);
	
	GTEST_COUT<<"The first rect: " <<rect_ins_1.toString()<<std::endl;
	GTEST_COUT<<"The second rect: " <<rect_ins_2.toString()<<std::endl;
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_2));
	EXPECT_TRUE(rect_ins_2.intersects(rect_ins_1));

}

TEST(RectHV_intersects, case_3){
	RectHV rect_ins_1(0.5,0.5,0.95,0.95);
	RectHV rect_ins_2(0.740877,0.345492, 0.793893, 1.000000);
	
	GTEST_COUT<<"The first rect: " <<rect_ins_1.toString()<<std::endl;
	GTEST_COUT<<"The second rect: " <<rect_ins_2.toString()<<std::endl;
	EXPECT_TRUE(rect_ins_1.intersects(rect_ins_2));
	EXPECT_TRUE(rect_ins_2.intersects(rect_ins_1));

}



TEST(RectHV_distanceTo, case_1){
	RectHV rect_ins_1(0.4, 0.3, 0.8, 0.6);
	
	Point2D p_1(0.1,0.4);
	double dist_1= rect_ins_1.distanceTo(p_1);
	double square_dist_1 = rect_ins_1.distanceSquaredTo(p_1);
	EXPECT_DOUBLE_EQ(0.3, dist_1);
	EXPECT_DOUBLE_EQ(0.09, square_dist_1);

	Point2D p_2(0.0,0.0);
	double dist_2= rect_ins_1.distanceTo(p_2);
	double square_dist_2 = rect_ins_1.distanceSquaredTo(p_2);
	EXPECT_DOUBLE_EQ(0.5, dist_2);
	EXPECT_DOUBLE_EQ(0.25, square_dist_2);

	Point2D p_3(0.6,0.5);
	double dist_3= rect_ins_1.distanceTo(p_3);
	double square_dist_3 = rect_ins_1.distanceSquaredTo(p_3);
	EXPECT_DOUBLE_EQ(0.1, dist_3);
	EXPECT_DOUBLE_EQ(0.01, square_dist_3);
}

int main(int argc, char* argv[] ){
	std::cout <<"This script is to test the RectHV head file."
		<< std::endl;

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

