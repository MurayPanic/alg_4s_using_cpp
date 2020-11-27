#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>
#include <functional>
#include "LineSegment.hpp"

#ifndef BRUTECOLLINEARPOINTS_HPP
#define BRUTECOLLINEARPOINTS_HPP
//class declaration
class BruteCollinearPoints;

#endif

const double eps = 1e-20;

//hash function for unorderedset
class Hash_LineSegment{
	public:
	std::size_t operator()(const LineSegment& LS_ins)const{
		std::string LS_str= LS_ins.toString();
        std::hash<std::string> str_hasher;
		std::cout<< "The hasher is called: "<<LS_str<< " : "<< str_hasher(LS_str)<<std::endl;
		return str_hasher(LS_str);
	}
};



//Class definition
class BruteCollinearPoints{
	public: 
		BruteCollinearPoints();
		BruteCollinearPoints( std::vector<Point>&);
		~BruteCollinearPoints();
		int numberofSegments();
		std::vector<LineSegment> segments();
	private:
		std::unordered_set<LineSegment, Hash_LineSegment> set_lineSeg;
};

//Class constructor
BruteCollinearPoints::BruteCollinearPoints(){
	throw std::invalid_argument("IllegalArgumentException: Null argument is not acceptable");
};

BruteCollinearPoints::BruteCollinearPoints(std::vector<Point>& vec_points){
	
	std::sort(vec_points.begin(), vec_points.end());
	std::cout<< "The point vector: ";
	for (auto item :vec_points){
		std::cout<<item.toString();
	}
	std::cout<< std::endl;
	std::vector<int> bitmap (vec_points.size(),0);
	for (int i =0; i<4;++i){
		bitmap[i]=1;
	}

	do{
		int j=0;
		Point* four_point_arr[4];
		for(int i=0; i<vec_points.size();++i ){
			//Pick four points from the list
			
			if(bitmap[i]==1){
				four_point_arr[j]=&vec_points[i];
				++j;
			}

			
		}
		//Check slope
		double first_slope= four_point_arr[0]->slopeTo(*four_point_arr[1]);
		double second_slope= four_point_arr[1]->slopeTo(*four_point_arr[2]);
		double third_slope= four_point_arr[2]->slopeTo(*four_point_arr[3]);

		double diff_1st_and_2nd = std::abs(first_slope-second_slope);
		double diff_2nd_and_3rd = std::abs(second_slope- third_slope);



		if((diff_1st_and_2nd < eps) && (diff_2nd_and_3rd < eps)){
			LineSegment tmp_seg(*four_point_arr[0], *four_point_arr[3]);
			
			std::cout<< "One line segment find: "<<tmp_seg.toString()<<std::endl;
			std::cout<<"The complete line is: ";
			for(auto item :four_point_arr){
				std::cout<< item->toString()<<"->";
			}
			std::cout<<std::endl;

			std::cout<<"Before insertion: ";
			for(auto item : set_lineSeg){
				std::cout<< item.toString();
			}
			std::cout<<std::endl;
			

			set_lineSeg.insert(tmp_seg);
			std::cout<<"After insertion: ";
			for(auto item : set_lineSeg){
				std::cout<< item.toString();
			}
			std::cout<<std::endl;
		} 



	}while( std::ranges::prev_permutation(bitmap).found );

};

//Class deconstructor
BruteCollinearPoints::~BruteCollinearPoints(){};

//Return line segment:
std::vector<LineSegment> BruteCollinearPoints::segments(){
    
	 
     
	 std::cout<< "Before assign: ";
	 for (auto item : set_lineSeg){
		 std::cout<< item.toString(); 
	 }
	 std::cout<<std::endl;

	 std::vector<LineSegment> vec_lineSeg(set_lineSeg.begin(), set_lineSeg.end());
     //std::vector<LineSegment> vec_lineSeg;
	 //std::copy(set_lineSeg.begin(),set_lineSeg.end())
	 //vec_lineSeg.assign(set_lineSeg.begin(), set_lineSeg.end());
	 std::cout<< "Before return: ";
	 for (auto item : vec_lineSeg){
		 std::cout<< item.toString(); 
	 }
	 std::cout<<std::endl;


	return vec_lineSeg; 


}

//Return the number of line segment:
int BruteCollinearPoints::numberofSegments(){
	int result = set_lineSeg.size();
	return result;
}
