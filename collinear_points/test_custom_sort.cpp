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

bool cmp_by_slope_func(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
		return pair_1.second < pair_2.second;
}

struct cmp_by_point{
                bool operator()(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
                        return (pair_1.first)< (pair_2.first);
                }
        };

bool cmp_by_point_func(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
			return (pair_1.first) < (pair_2.first);
}

TEST(selection_sort, sortIntegerVector){
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

TEST(selection_sort, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.520);
	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6};
	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);

	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	selection_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	selection_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}

TEST(insertion_sort, sortIntegerVector){
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	insertion_sort(int_vec.begin(), int_vec.end());
	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(insertion_sort, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.520);
	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6};
	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);

	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	insertion_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	insertion_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}

TEST(h_sort, sortIntegerVector){
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	h_sort(int_vec.begin(), int_vec.end(),1);
	EXPECT_NE(int_vec, int_vec_ref);

	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}


TEST(h_sort, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.520);
	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6};
	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);

	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	h_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_slope_func,1);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	h_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_point_func,1);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}


TEST(shell_sort, sortIntegerVector){
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23,123,42,5,23,1,42,32,4,56,54,2,34,5,3,5,6,3,2,6,6,777,3,1,2,5,3,6,4,76,2,3,5,1,12,44,2,2,335,6,666};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	shell_sort(int_vec.begin(), int_vec.end());
	EXPECT_NE(int_vec, int_vec_ref);

	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(shell_sort, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.525);
	point_slope_pair PS_7(Point(125,130), 1.111);
	point_slope_pair PS_8(Point(140,135), 0.520);

	point_slope_pair PS_9(Point(130,140), 0.668);
	point_slope_pair  PS_10(Point(150,160), 3.314);
	point_slope_pair PS_11(Point(150,170), -4.212);
	point_slope_pair PS_12(Point(170,180), -0.334);
	point_slope_pair PS_13(Point(190,200), 1.131);
	point_slope_pair PS_14(Point(210,220), 2.520);
	point_slope_pair PS_15(Point(230,100), 1.3311);
	point_slope_pair PS_16(Point(240,120), 0.672);

	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6, PS_7,PS_8, PS_9, PS_10, PS_11, PS_12, PS_13, PS_14, PS_15, PS_16};

	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);

	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	shell_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	shell_sort(PS_vec_2.begin(), PS_vec_2.end(), cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}

TEST(merge_sort_recur_ver, sortIntegerVector){
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23,123,42,5,23,1,42,32,4,56,54,2,34,5,3,5,6,3,2,6,6,777,3,1,2,5,3,6,4,76,2,3,5,1,12,44,2,2,335,6,666};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	merge_sort_recur_ver(int_vec.begin(), int_vec.end()-1);
	EXPECT_NE(int_vec, int_vec_ref);

	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"The correct vector is: ";
	for(auto item : int_vec_ref){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(merge_sort_recur_ver, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.525);
	point_slope_pair PS_7(Point(125,130), 1.1661);
	point_slope_pair PS_8(Point(140,135), 0.520);

	point_slope_pair PS_9(Point(130,140), 0.668);
	point_slope_pair  PS_10(Point(150,160), 3.314);
	point_slope_pair PS_11(Point(150,170), -4.212);
	point_slope_pair PS_12(Point(170,180), -0.334);
	point_slope_pair PS_13(Point(190,200), 1.131);
	point_slope_pair PS_14(Point(210,220), 2.520);
	point_slope_pair PS_15(Point(230,100), 1.3311);
	point_slope_pair PS_16(Point(240,120), 0.672);

	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6, PS_7,PS_8, PS_9, PS_10, PS_11, PS_12, PS_13, PS_14, PS_15, PS_16};

	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);


	merge_sort_recur_ver(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	merge_sort_recur_ver(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}

TEST(merge_sort_bu_ver, sortIntegerVector){

	 
	std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23,123,42,5,23,1,42,32,4,56,54,2,34,5,3,5,6,3,2,6,6,777,3,1,2,5,3,6,4,76,2,3,5,1,12,44,2,2,335,6};
	//std::vector<int> int_vec{8,6,22,5,0,9,2,6,22,5,0,9,2};
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	merge_sort_bu_ver(int_vec.begin(), int_vec.end()-1);
	EXPECT_NE(int_vec, int_vec_ref);

	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(merge_sort_bu_ver, sortPointVector){
	
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.525);
	point_slope_pair PS_7(Point(125,130), 1.1661);
	point_slope_pair PS_8(Point(140,135), 0.520);

	point_slope_pair PS_9(Point(130,140), 0.668);
	point_slope_pair  PS_10(Point(150,160), 3.314);
	point_slope_pair PS_11(Point(150,170), -4.212);
	point_slope_pair PS_12(Point(170,180), -0.334);
	point_slope_pair PS_13(Point(190,200), 1.131);
	point_slope_pair PS_14(Point(210,220), 2.520);
	point_slope_pair PS_15(Point(230,100), 1.3311);
	point_slope_pair PS_16(Point(240,120), 0.672);

	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6, PS_7,PS_8, PS_9, PS_10, PS_11, PS_12, PS_13, PS_14, PS_15, PS_16};

        /*
	point_slope_pair PS_1(Point(6000,7000),-1.75);
	point_slope_pair PS_2(Point(7000,3000),-1);
	point_slope_pair PS_3(Point(3000,7000),-1);
	point_slope_pair PS_4(Point(0,1000),-1);
	point_slope_pair PS_5(Point(3000,4000),-0.571429);
	point_slope_pair PS_6(Point(20000,21000),2.1);
	point_slope_pair PS_7(Point(14000,15000),3.75);
	std::vector<point_slope_pair> PS_vec{PS_1, PS_2,PS_3,PS_4,PS_5,PS_6,PS_7};



	point_slope_pair PS_1(Point(7000,3000),-1.75);
	point_slope_pair PS_2(Point(3000,7000),-1);
	point_slope_pair PS_3(Point(10000,0),-1);
	

	std::vector<point_slope_pair> PS_vec{PS_1, PS_2,PS_3};
	*/

	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	//EXPECT_FALSE(PS_vec== PS_vec_2);


	merge_sort_bu_ver(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	GTEST_COUT<<"(by slope)PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"(by slope)PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	//EXPECT_FALSE(PS_vec == PS_vec_2);
	merge_sort_bu_ver(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);


	GTEST_COUT<<"(by point)PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"(by point)PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

}

TEST(quick_sort, sortIntegerVector){

	 
	 
	  std::vector<int> int_vec{1,6,3,7,9,2,4,9,58,23,123,42,5,23,1,42,32,4,56,54,2,34,5,3,5,6,3,2,6,6,777,3,1,2,5,3,6,4,76,2,3,5,1,12,44,2,2,335,6,666};
	 
	 
	std::vector<int> int_vec_ref=int_vec;

	GTEST_COUT<<"The original vector is: ";
	for(auto item :int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;

	quick_sort(int_vec.begin(), int_vec.end()-1);
	EXPECT_NE(int_vec, int_vec_ref);

	std::sort(int_vec_ref.begin(), int_vec_ref.end());

	GTEST_COUT<<"The sorted vector is: ";
	for(auto item : int_vec){
		std::cout<<item<<",";
	}
	std::cout<<std::endl;
 	EXPECT_EQ(int_vec, int_vec_ref);

}

TEST(quick_sort, sortPointVector){
	point_slope_pair PS_1(Point(10,20), 0.618);
	point_slope_pair  PS_2(Point(30,40), 1.314);
	point_slope_pair PS_3(Point(50,60), -1.212);
	point_slope_pair PS_4(Point(70,80), 0.334);
	point_slope_pair PS_5(Point(90,100), 1.111);
	point_slope_pair PS_6(Point(110,120), 0.525);
	point_slope_pair PS_7(Point(125,130), 1.1661);
	point_slope_pair PS_8(Point(140,135), 0.520);

	point_slope_pair PS_9(Point(130,140), 0.668);
	point_slope_pair  PS_10(Point(150,160), 3.314);
	point_slope_pair PS_11(Point(150,170), -4.212);
	point_slope_pair PS_12(Point(170,180), -0.334);
	point_slope_pair PS_13(Point(190,200), 1.131);
	point_slope_pair PS_14(Point(210,220), 2.520);
	point_slope_pair PS_15(Point(230,100), 1.3311);
	point_slope_pair PS_16(Point(240,120), 0.672);

	std::vector<point_slope_pair> PS_vec{PS_1,PS_2,PS_3,PS_4,PS_5,PS_6, PS_7,PS_8, PS_9, PS_10, PS_11, PS_12, PS_13, PS_14, PS_15, PS_16};

	std::vector<point_slope_pair> PS_vec_2=PS_vec;
	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_slope());
	EXPECT_FALSE(PS_vec== PS_vec_2);


	quick_sort(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_slope_func);
	EXPECT_TRUE(PS_vec==PS_vec_2);
	
	GTEST_COUT<<"PS_vec: ";
	for(auto item: PS_vec){
		std::cout<< item.first.toString()
			<<":"<< item.second<<",";
	}
	std::cout<<std::endl;

	GTEST_COUT<<"PS_vec_2: ";
	for(auto item: PS_vec_2){
		std::cout<< item.first.toString()
			<<":"<<item.second<<",";
	}
	std::cout<<std::endl;

	std::sort(PS_vec.begin(), PS_vec.end(), cmp_by_point());
	EXPECT_FALSE(PS_vec == PS_vec_2);
	quick_sort(PS_vec_2.begin(), PS_vec_2.end()-1, cmp_by_point_func);
	EXPECT_TRUE(PS_vec == PS_vec_2);



}

int main(int argc, char* argv[]){
	std::cout<< "This script is to test the custom_sort head file"
		<<std::endl;
	::testing::InitGoogleTest(&argc, argv);
	//::testing::GTEST_FLAG(filter)
	return RUN_ALL_TESTS();

}
