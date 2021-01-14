#include <iostream>
#include <gtest/gtest.h>
#include "FastCollinearPoints.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(FCPTest, Constructor){
	try {
		FastCollinearPoints FCP_ins{};
	}catch(std::invalid_argument& err){
		GTEST_COUT<< err.what()<<std::endl;
	}
	EXPECT_THROW(FastCollinearPoints(), std::invalid_argument);
}

TEST(FCPTest, constructorWithAugument){
		Point p_1(19000,10000);
		Point p_2(18000,10000);
		Point p_3(32000,10000);
		Point p_4(21000,10000);
		Point p_5(1234, 5678);
		Point p_6(14000,10000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6};
		FastCollinearPoints FCP_ins(vec_points);
		
	
}

TEST(FCPTest, input6){
		Point p_1(19000,10000);
		Point p_2(18000,10000);
		Point p_3(32000,10000);
		Point p_4(21000,10000);
		Point p_5(1234, 5678);
		Point p_6(14000,10000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6};
		FastCollinearPoints FCP_ins(vec_points);
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
	
}

TEST(FCPTest, input8){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points);
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
}

TEST(FCPTest, selection_sort){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "selection_sort");
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
}


TEST(FCPTest, insertion_sort){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "insertion_sort");
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
}



TEST(FCPTest, shell_sort){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "shell_sort");
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
}

TEST(FCPTest, merge_sort_recur_ver){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "merge_sort_recur_ver");
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
		std::cout<<std::endl;
}

TEST(FCPTest, merge_sort_bu_ver_sort){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "merge_sort_bu_ver");
		GTEST_COUT<<"Line segments found: "<<FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
}


TEST(FCPTest, quick_sort){
		Point p_1(10000,0);
		Point p_2(0,10000);
		Point p_3(3000,7000);
		Point p_4(7000,3000);
		Point p_5(20000,21000);
		Point p_6(3000,4000);
		Point p_7(14000,15000);
		Point p_8(6000,7000);
		std::vector<Point> vec_points{p_1,p_2,p_3,p_4,p_5,p_6,p_7,p_8};
		FastCollinearPoints FCP_ins(vec_points, "quick_sort");
		GTEST_COUT<<"Line segments found: "<< FCP_ins.numberOfSegments()<<std::endl;
		std::vector<LineSegment> vec_lineSeg= FCP_ins.segments();
		GTEST_COUT<<"The line segments are: ";
		for(auto& item : vec_lineSeg){
			std::cout<<item.toString()<<std::endl;
		}
}


int main(int ac, char* av[]){
	std::cout<< "This script is to test the FastCollinearPoints head file"
		<<std::endl;
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
