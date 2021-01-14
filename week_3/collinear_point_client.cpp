#include<iostream>
#include "BruteCollinearPoints.hpp"
#include "FastCollinearPoints.hpp"
#include "draw.hpp"
#include <filesystem>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
	std::cout<< "This program is to find out collinear points on a plane and draw it out"
		<<std::endl;
	
	std::filesystem::path input_file_path(argv[1]);
	std::ifstream input_file;
	input_file.open(input_file_path);
	int point_num{0};
	std::string point_num_str;
	input_file>>point_num_str;
	point_num = std::stoi(point_num_str);
	std::vector<Point > vec_point;
	while(!input_file.eof()){
		std::string temp_str_x;
		std::string temp_str_y;
		input_file>>temp_str_x;
		input_file>>temp_str_y;
		if(input_file.peek()==EOF){break;}
		int x = std::stoi(temp_str_x);
		int y = std::stoi(temp_str_y);
		Point temp_point(x,y);
		vec_point.push_back(temp_point);
		
	}
	
	std::cout<<"The input points are: ";
	for (auto& item : vec_point){
		std::cout<< item.toString()<<" ";
	}
	std::cout<<std::endl;

	std::cout<<"Now fined collinear points with Brute search..." <<std::endl;
	BruteCollinearPoints BCP_ins(vec_point);
	std::cout<< "Line segment found: "<<BCP_ins.numberOfSegments()<<std::endl;
	auto vec_lineSeg= BCP_ins.segments();
	std::cout<<"The line segments are: "<<std::endl;
	for (auto& item : vec_lineSeg){
		std::cout << item.toString() << std::endl;
	}

	std::cout<<"Now find collinear points with Fast search that based on sorting..." <<std::endl;
	FastCollinearPoints FCP_ins(vec_point);
	std::cout<< "Line segment found: "<<FCP_ins.numberOfSegments()<<std::endl;
	auto vec_lineSeg_2 = FCP_ins.segments();
	std::cout<<"The linesegments are: " <<std::endl;
	for(auto& item :vec_lineSeg_2){
		std::cout<<item.toString() << std::endl;
	}

	std::cout<<"Now visualize the point and line segments..."<<std::endl;
	for (auto& point_ins : vec_point){
		draw(point_ins);
	}

	for (auto& LS_ins : vec_lineSeg_2 ){
		draw(LS_ins);
	}

	show();


	return 0;
}
