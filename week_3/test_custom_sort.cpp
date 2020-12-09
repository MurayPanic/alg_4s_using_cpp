#include<iostream>
#include<vector>
#include<gtest/gtest.h>
#include<algorithm>
#include "Point.hpp"
#include "custom_sort.hpp"
#define GTEST_COUT std::cout<<"[CUSTOM INFO]"

typedef  std::pair<Point, double> point_slope_pair;

struct cmp_by_slope{
                bool operator()(const point_slope_pair& pair_1, const point_slope_pair& pair_2){

                        return  pair_1.second< pair_2.second;
                }
        };

struct cmp_by_point{
                bool operator()(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
                        return (pair_1.first)< (pair_2.first);
                }
        };

TEST(insertion_sort, sortIntegerVector){
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	selection_sort(int_vec.begin(), int_vec.end());
	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(insertion_sort, sortPointVector){
	std::vector<point_slope_pair> PS_vec;
	point_slope_pair PS_1(Point(10,20), 0.618);

}

int main(int argc, char* argv[]){
	std::cout<< "This script is to test the custom_sort head file"
		<<std::endl;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();

}
