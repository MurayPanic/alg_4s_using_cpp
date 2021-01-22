#include <iostream>
#include <gtest/gtest.h>
#include <exception>
#include "KdTree.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(KdTreeNode_constructor,case_1){
	KdTreeNode KTN_ins_1{};
}

TEST(KdTreeNode_constructor, case_2){
	Point2D point_ins(0.5,0.5);
	RectHV  rect_ins(1,2,3,4);
		
	EXPECT_THROW(KdTreeNode(point_ins, rect_ins, true), std::invalid_argument );
}

TEST(KdTreeNode_constructor, case_3){
	Point2D point_ins(1.5,2.5);
	RectHV  rect_ins(1,2,3,4);
	EXPECT_THROW(KdTreeNode(point_ins, rect_ins, true), std::invalid_argument );
}

TEST(KdTreeNode_constructor, case_4){

	Point2D point_ins(0.8,0.7);
	RectHV  rect_ins(1,2,3,4);
	EXPECT_THROW(KdTreeNode(point_ins, rect_ins, true), std::invalid_argument );
}


TEST(KdTreeNode_constructor, case_5){

	Point2D point_ins(0.8,0.7);
	RectHV  rect_ins(0.5,0.5,1,1);
	KdTreeNode KTN(point_ins, rect_ins, true);
}


TEST(KdTree_constructor, case_1){
	KdTree KT_ins{};

}

TEST(KdTree_isEmpty, case_1){
	KdTree KT_ins{};
	EXPECT_TRUE(KT_ins.isEmpty());
}

TEST(KdTree_isEmpty, case_2){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	KT_ins.insert(point_ins);
	EXPECT_FALSE(KT_ins.isEmpty());
}

TEST(KdTree_isEmpty, case_3){
	KdTree KT_ins{};
	Point2D point_ins_1(0.7,0.2);
	Point2D point_ins_2(0.5,0.4);
	Point2D point_ins_3(0.2,0.3);
	Point2D point_ins_4(0.4,0.7);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
	EXPECT_FALSE(KT_ins.isEmpty());
}

TEST(KdTree_size, case_1){
	KdTree KT_ins{};
	EXPECT_EQ(0, KT_ins.size());
}

TEST(KdTree_size, case_2){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	KT_ins.insert(point_ins);
	EXPECT_EQ(1, KT_ins.size());
}

TEST(KdTree_size, case_3){
	KdTree KT_ins{};
	Point2D point_ins_1(0.7,0.2);
	Point2D point_ins_2(0.5,0.4);
	Point2D point_ins_3(0.2,0.3);
	Point2D point_ins_4(0.4,0.7);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
	EXPECT_EQ(4, KT_ins.size());
}

TEST(KdTree_insert, case_1){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	KT_ins.insert(point_ins);
}

TEST(KdTree_insert, case_2){
	KdTree KT_ins{};
	Point2D point_ins_1(0.7,0.2);
	Point2D point_ins_2(0.5,0.4);
	Point2D point_ins_3(0.2,0.3);
	Point2D point_ins_4(0.4,0.7);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
}

TEST(KdTRee_contains, case_1){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	EXPECT_FALSE(KT_ins.contains(point_ins));
}

TEST(KdTRee_contains, case_2){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	KT_ins.insert(point_ins);
	EXPECT_TRUE(KT_ins.contains(point_ins));
}


TEST(KdTree_contains, case_3){
	KdTree KT_ins{};
	Point2D point_ins_1(0.7,0.2);
	Point2D point_ins_2(0.5,0.4);
	Point2D point_ins_3(0.2,0.3);
	Point2D point_ins_4(0.4,0.7);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);

	EXPECT_TRUE(KT_ins.contains(point_ins_1));
	EXPECT_TRUE(KT_ins.contains(point_ins_2));
	EXPECT_TRUE(KT_ins.contains(point_ins_3));
	EXPECT_TRUE(KT_ins.contains(point_ins_4));
}


TEST(KdTree_draw, case_1){
	KdTree KT_ins{};
	KT_ins.draw();
}


TEST(KdTree_draw, case_2){
	KdTree KT_ins{};
	Point2D point_ins(0.5,0.5);
	KT_ins.insert(point_ins);
	KT_ins.draw();
}

TEST(KdTree_draw, case_3){
	KdTree KT_ins{};
	Point2D point_ins_1(0.7,0.2);
	Point2D point_ins_2(0.5,0.4);
	Point2D point_ins_3(0.2,0.3);
	Point2D point_ins_4(0.4,0.7);
	Point2D point_ins_5(0.9,0.6);
	
	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
	KT_ins.insert(point_ins_5);
	
	KT_ins.draw();
}

TEST(KdTree_draw, circle10){
	KdTree KT_ins{};
	
	Point2D point_ins_1(0.206107, 0.095492);
	Point2D point_ins_2(0.975528, 0.654508);
	Point2D point_ins_3(0.024472, 0.345492);
	Point2D point_ins_4(0.793893, 0.095492);
	Point2D point_ins_5(0.793893, 0.904508);
	Point2D point_ins_6(0.975528, 0.345492);
	Point2D point_ins_7(0.206107, 0.904508);
	Point2D point_ins_8(0.500000, 0.000000);
	Point2D point_ins_9(0.024472, 0.654508);
	Point2D point_ins_10(0.500000, 1.000000);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
	KT_ins.insert(point_ins_5);
	KT_ins.insert(point_ins_6);
	KT_ins.insert(point_ins_7);
	KT_ins.insert(point_ins_8);
	KT_ins.insert(point_ins_9);
	KT_ins.insert(point_ins_10);

	KT_ins.draw();

}

TEST(KdTree_nearest, circle10){
	KdTree KT_ins{};
	
	Point2D point_ins_1(0.206107, 0.095492);
	Point2D point_ins_2(0.975528, 0.654508);
	Point2D point_ins_3(0.024472, 0.345492);
	Point2D point_ins_4(0.793893, 0.095492);
	Point2D point_ins_5(0.793893, 0.904508);
	Point2D point_ins_6(0.975528, 0.345492);
	Point2D point_ins_7(0.206107, 0.904508);
	Point2D point_ins_8(0.500000, 0.000000);
	Point2D point_ins_9(0.024472, 0.654508);
	Point2D point_ins_10(0.500000, 1.000000);

	KT_ins.insert(point_ins_1);
	KT_ins.insert(point_ins_2);
	KT_ins.insert(point_ins_3);
	KT_ins.insert(point_ins_4);
	KT_ins.insert(point_ins_5);
	KT_ins.insert(point_ins_6);
	KT_ins.insert(point_ins_7);
	KT_ins.insert(point_ins_8);
	KT_ins.insert(point_ins_9);
	KT_ins.insert(point_ins_10);

	Point2D test_point_p(0.81,0.3);
	auto nearest_point =KT_ins.nearest(test_point_p);
	GTEST_COUT<<"The result point:"<< nearest_point.toString()<<std::endl;
	GTEST_COUT<<"The expect point:"<< point_ins_6.toString()<<std::endl;
	EXPECT_TRUE(nearest_point==point_ins_6);
	

}


int main(int argc, char* argv[]){
	std::cout << "This script is to test the KTtree head file"
		  << std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
