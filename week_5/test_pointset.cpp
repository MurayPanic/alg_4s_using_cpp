#include <iostream>
#include <gtest/gtest.h>
#include "PointSET.hpp"
#define GTEST_COUT std::cout<< "[CUSTOM INFO] "

TEST(PointSET_constructor,case_1){
	PointSET PS_1{};
}

TEST(PointSET_insert, case_1){
	PointSET PS_1{};
	Point2D point_ins(1.0,2.0);
	PS_1.insert(point_ins);
}

TEST(PointSET_isEmpty, case_1){
	PointSET PS_1{};
	EXPECT_TRUE(PS_1.isEmpty());
	Point2D point_ins(1.0,2.0);
	PS_1.insert(point_ins);
	EXPECT_FALSE(PS_1.isEmpty() );
}

TEST(PointSet_size, case_1){
	PointSET PS_1{};
	EXPECT_EQ(0, PS_1.size() );
	Point2D point_ins(1.0,2.0);
	PS_1.insert(point_ins);
	EXPECT_EQ(1, PS_1.size() );
}

TEST(PointSet_constains, case_1){

	PointSET PS_1{};
	Point2D point_ins(1.0,2.0);
	EXPECT_FALSE(PS_1.contains(point_ins));
	PS_1.insert(point_ins);
	EXPECT_TRUE(PS_1.contains(point_ins));
}

TEST(PointSet_range, case_1){
	PointSET PS_1{};
	Point2D point_ins_1(1.0,2.0);
	Point2D point_ins_2(3.0,4.0);
	Point2D point_ins_3(5.0,6.0);
	Point2D point_ins_4(7.0,8.0);
	Point2D point_ins_5(1.50,2.56);

	PS_1.insert(point_ins_1);
	PS_1.insert(point_ins_2);
	PS_1.insert(point_ins_3);
	PS_1.insert(point_ins_4);
	PS_1.insert(point_ins_5);

	RectHV rect_ins(1.0,2.0,3.0,4.0);
	auto result_vec= PS_1.range(rect_ins);

	GTEST_COUT<< "The points are:" <<std::endl;

	for(auto item : result_vec){
		GTEST_COUT << item.toString() << std::endl;
	}

	std::vector<Point2D> ref_vec{};
	ref_vec.push_back(point_ins_1);
	ref_vec.push_back(point_ins_5);
	ref_vec.push_back(point_ins_2);
	EXPECT_EQ(result_vec, ref_vec);
}

TEST(PointSET_nearest, case_1){
	
	PointSET PS_1{};
	Point2D point_ins_1(1.0,2.0);
	Point2D point_ins_2(3.0,4.0);
	Point2D point_ins_3(5.0,6.0);
	Point2D point_ins_4(7.0,8.0);
	Point2D point_ins_5(1.50,2.56);

	PS_1.insert(point_ins_1);
	PS_1.insert(point_ins_2);
	PS_1.insert(point_ins_3);
	PS_1.insert(point_ins_4);
	PS_1.insert(point_ins_5);

	Point2D point_ins_test(1.3, 2.3);
	auto result_point = PS_1.nearest(point_ins_test);
	EXPECT_EQ(point_ins_5, result_point);

	auto result_point_2 = PS_1.nearest(point_ins_3);
	EXPECT_EQ(point_ins_3.toString(), result_point_2.toString());


}


int main(int argc, char* argv[]){
	std::cout<<"This script is to test the PoinSET headfile."
		<< std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

