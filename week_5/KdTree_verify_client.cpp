#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include "gtest/gtest.h"

#include "KdTree.hpp"
#include "PointSET.hpp"
#define GTEST_COUT std::cout<< "[CUSTOM INFO] "


//Global variables for testing
std::vector<Point2D> vec_point;
KdTree KT_ins{};
PointSET PS_ins{};

TEST(Nearest,fixed_point){
	Point2D test_point_p(0.81,0.3);
	auto KT_start = std::chrono::system_clock::now();
	auto KT_nearest_point = KT_ins.nearest(test_point_p);
	auto KT_end = std::chrono::system_clock::now();
	auto KT_duration = std::chrono::duration_cast<std::chrono::microseconds>(KT_end-KT_start);
	GTEST_COUT<< "Time consumption with KDTree: "
		  <<double(KT_duration.count()) <<std::endl;

	auto PS_start = std::chrono::system_clock::now();
	auto PS_nearest_point = PS_ins.nearest(test_point_p);
	auto PS_end = std::chrono::system_clock::now();
	auto PS_duration = std::chrono::duration_cast<std::chrono::microseconds>(PS_end-PS_start);
	GTEST_COUT<< "Time consumption with PointSET: "
		  <<double(PS_duration.count()) <<std::endl;

	EXPECT_TRUE(KT_nearest_point == PS_nearest_point);
	
}

TEST(Nearest, random_point){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0 , 1.0);
	double x = dis(gen);
	double y = dis(gen);

	Point2D test_point_p(x,y);
	auto KT_start = std::chrono::system_clock::now();
	auto KT_nearest_point = KT_ins.nearest(test_point_p);
	auto KT_end = std::chrono::system_clock::now();
	auto KT_duration = std::chrono::duration_cast<std::chrono::microseconds>(KT_end-KT_start);
	GTEST_COUT<< "Time consumption with KDTree: "
		  <<double(KT_duration.count()) <<std::endl;

	auto PS_start = std::chrono::system_clock::now();
	auto PS_nearest_point = PS_ins.nearest(test_point_p);
	auto PS_end = std::chrono::system_clock::now();
	auto PS_duration = std::chrono::duration_cast<std::chrono::microseconds>(PS_end-PS_start);
	GTEST_COUT<< "Time consumption with PointSET: "
		  <<double(PS_duration.count()) <<std::endl;

	EXPECT_TRUE(KT_nearest_point == PS_nearest_point);
}

TEST(Range,fixed_rect){
	RectHV test_rect(0.5,0.5,0.95,0.95);
	GTEST_COUT <<"The fixed rectangle is: " <<test_rect.toString() <<std::endl;
	auto KT_start = std::chrono::system_clock::now();
	auto KT_contain_point_list = KT_ins.range(test_rect);
	auto KT_end = std::chrono::system_clock::now();
	auto KT_duration = std::chrono::duration_cast<std::chrono::microseconds>(KT_end-KT_start);
	GTEST_COUT<< "Time consumption with KDTree: "
		  <<double(KT_duration.count()) <<std::endl;

	
	std::sort(KT_contain_point_list.begin(), KT_contain_point_list.end());
	/*
	GTEST_COUT<<"Result by KDTree: ";
	for(auto item : KT_contain_point_list){
		std::cout<< item.toString();
	}
	std::cout<<std::endl;
	*/

	auto PS_start = std::chrono::system_clock::now();
	auto PS_contain_point_list = PS_ins.range(test_rect);
	auto PS_end = std::chrono::system_clock::now();
	auto PS_duration = std::chrono::duration_cast<std::chrono::microseconds>(PS_end-PS_start);
	GTEST_COUT<< "Time consumption with PointSET: "
		  <<double(PS_duration.count()) <<std::endl;


	std::sort(PS_contain_point_list.begin(), PS_contain_point_list.end());
	/*
	GTEST_COUT<<"Result by PointSET: ";
	for(auto item : PS_contain_point_list){
		std::cout<< item.toString();
	}
	std::cout<<std::endl;
	*/

	GTEST_COUT<<"KT result len: "<<KT_contain_point_list.size()<<std::endl;
	GTEST_COUT<<"PS result len: "<<PS_contain_point_list.size()<<std::endl;
	EXPECT_TRUE(KT_contain_point_list == PS_contain_point_list);
	
}

TEST(Range, random_rect){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis_1(0.0 , 0.5);
	std::uniform_real_distribution<> dis_2(0.6 , 1.0);
	double xmin = dis_1(gen);
	double ymin = dis_1(gen);
	double xmax = dis_2(gen);
	double ymax = dis_2(gen);

	RectHV test_rect(xmin,ymin,xmax,ymax);
	GTEST_COUT << "The random rectangle is: "<< test_rect.toString()<<std::endl;
	auto KT_start = std::chrono::system_clock::now();
	auto KT_contain_point_list = KT_ins.range(test_rect);
	auto KT_end = std::chrono::system_clock::now();
	auto KT_duration = std::chrono::duration_cast<std::chrono::microseconds>(KT_end-KT_start);
	GTEST_COUT<< "Time consumption with KDTree: "
		  <<double(KT_duration.count()) <<std::endl;

	auto PS_start = std::chrono::system_clock::now();
	auto PS_contain_point_list = PS_ins.range(test_rect);
	auto PS_end = std::chrono::system_clock::now();
	auto PS_duration = std::chrono::duration_cast<std::chrono::microseconds>(PS_end-PS_start);
	GTEST_COUT<< "Time consumption with PointSET: "
		  <<double(PS_duration.count()) <<std::endl;

	std::sort(KT_contain_point_list.begin(), KT_contain_point_list.end());
	std::sort(PS_contain_point_list.begin(), PS_contain_point_list.end());
	
	GTEST_COUT<<"KT result len: "<<KT_contain_point_list.size()<<std::endl;
	GTEST_COUT<<"PS result len: "<<PS_contain_point_list.size()<<std::endl;
	EXPECT_TRUE(KT_contain_point_list == PS_contain_point_list);
}
int main(int argc, char* argv []){
	std::cout<<"This script is to verify the KdTree with the PointSET file "
		 <<"based on the dataset provided on coursera. "
		 <<std::endl;
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"The test procedure are as follow:"<<std::endl;
	std::cout<<"(1) Draw the KdTree according to the point data"<<std::endl
		<<"(2) Build the PointSEt to restore the point data"<<std::endl
		<<"(3) Test the nearest and contains function of both headfile"<<std::endl
		<<"(4) Compare the result and timing"<<std::endl;

	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"Now load the data..."<<std::endl;

	std::filesystem::path input_file_path(argv[1]);
	std::ifstream input_file;
	input_file.open(input_file_path);
	while(!input_file.eof()){
		std::string temp_str_x;
		std::string temp_str_y;
		input_file>>temp_str_x;
		input_file>>temp_str_y;
		if(input_file.peek()==EOF){break;}
		double x = std::stod(temp_str_x);
		double y = std::stod(temp_str_y);
		Point2D temp_point(x,y);
		vec_point.push_back(temp_point);
	
	}

	std::cout<<"Data load complete..."<<std::endl;
	std::cout<<vec_point.size()<<" points are imported"<<std::endl;
	std::cout<<"------------------------------------------"<<std::endl;
	std::cout<<"Now prepare the data for testing..."<<std::endl;
	
	auto start = std::chrono::system_clock::now();
	for(auto point : vec_point){
		PS_ins.insert(point);
	}
	auto end = std::chrono::system_clock::now();
	auto duration = duration_cast<std::chrono::microseconds>(end - start);
	std::cout<<"Pointset prepare complete!"<<std::endl;
	std::cout<<"Pointset data preparation consumption: "<< double(duration.count()) << std::endl;
		

	start = std::chrono::system_clock::now();
	for(auto point : vec_point){
		KT_ins.insert(point);
	}
	end = std::chrono::system_clock::now();
	duration = duration_cast<std::chrono::microseconds>(end - start);
	std::cout<<"KdTree prepare complete!"<<std::endl;
	std::cout<<"KdTRee data preparation consumption: "<< double(duration.count()) << std::endl;

	std::cout<<"KdTRee prepare complete!"<<std::endl;
	std::cout<<"The KdTree is shown in new window"<<std::endl
		<<"Press any key to continue the test"<<std::endl;	
	KT_ins.draw();

	std::cout<<"------------------------------------------"<<std::endl;

	std::cout<<"Now start test with google test framework..."<<std::endl;


	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();


}

