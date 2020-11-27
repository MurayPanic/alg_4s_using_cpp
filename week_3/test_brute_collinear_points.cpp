#include<iostream>
#include <gtest/gtest.h>
#include "BruteCollinearPoints.hpp"
#define GTEST_COUT std::cout << "[CUSTOM INFO] "

TEST(BCPTest, Constructor){
        try{
	    BruteCollinearPoints BCP_ins{};
	}
	catch(std::invalid_argument& err){
		GTEST_COUT<<err.what()<<std::endl;	
	}	
	EXPECT_THROW(BruteCollinearPoints(),std::invalid_argument);	
}

TEST(BCPTest, ConstructorWithAgument){

	Point point_ins_1(66,77);
	Point point_ins_2(88,99);
	Point point_ins_3(10,20);
	Point point_ins_4(20,40);
	Point point_ins_5(30,60);
	Point point_ins_6(40,80);
	
	std::vector<Point> vec_points{point_ins_1,
								point_ins_2,
								point_ins_3,
								point_ins_4,
								point_ins_5,
								point_ins_6};
	BruteCollinearPoints BCP_ins(vec_points);
	GTEST_COUT<< BCP_ins.numberofSegments()<<std::endl;
	EXPECT_EQ(1,BCP_ins.numberofSegments());


}

TEST(BCPTest, numberofSegments){
	Point point_ins_1(66,77);
	Point point_ins_2(88,99);
	Point point_ins_3(10,20);
	Point point_ins_4(20,40);
	Point point_ins_5(30,60);
	Point point_ins_6(40,80);
	
	std::vector<Point> vec_points{point_ins_1,
								point_ins_2,
								point_ins_3,
								point_ins_4,
								point_ins_5,
								point_ins_6};
	BruteCollinearPoints BCP_ins(vec_points);
	GTEST_COUT<<"Line Segment num: " <<BCP_ins.numberofSegments()<<std::endl;
	
	EXPECT_EQ(1,BCP_ins.numberofSegments());

}

TEST(BCPTest, segments){
	Point point_ins_1(66,77);
	Point point_ins_2(88,99);
	Point point_ins_3(10,20);
	Point point_ins_4(20,40);
	Point point_ins_5(30,60);
	Point point_ins_6(40,80);
	
	std::vector<Point> vec_points{point_ins_1,
								point_ins_2,
								point_ins_3,
								point_ins_4,
								point_ins_5,
								point_ins_6};
	BruteCollinearPoints BCP_ins(vec_points);
	std::vector<LineSegment> result_vec;
	result_vec = BCP_ins.segments();
	for (auto item : result_vec){
	GTEST_COUT<<"Line Segment: " <<item.toString()<<std::endl;
	}
	

}

int main(int ac, char* av[]){
	std::cout<< "This script is to test the BruteCollinearPoints head file"
		 << std::endl;
	::testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}
