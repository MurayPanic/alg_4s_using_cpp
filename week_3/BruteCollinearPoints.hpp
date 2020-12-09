#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <string>
#include "LineSegment.hpp"

#ifndef BRUTECOLLINEARPOINTS_HPP
#define BRUTECOLLINEARPOINTS_HPP
//class declaration
class BruteCollinearPoints;
#endif





//Class definition
class BruteCollinearPoints{
	public: 
		BruteCollinearPoints();
		BruteCollinearPoints( std::vector<Point>&);
		~BruteCollinearPoints();
		int numberOfSegments();
		std::vector<LineSegment> segments();
	private:

		//hash function for unorderedset
		class Hash_LineSegment{
			public:
				std::size_t operator()(const LineSegment& LS_ins)const{
				std::string LS_str= LS_ins.toString();
        			std::hash<std::string> str_hasher;
				return str_hasher(LS_str);
				}
			};
		std::unordered_set<LineSegment, Hash_LineSegment> set_lineSeg;
		bool collinearOrNot (const Point*[]);
		void removeDuplicateLines(LineSegment&);
		
		const double eps = 1e-20;
};

//Class constructor
BruteCollinearPoints::BruteCollinearPoints(){
	throw std::invalid_argument("IllegalArgumentException: Null argument is not acceptable");
};

BruteCollinearPoints::BruteCollinearPoints(std::vector<Point>& vec_points){
	
	std::sort(vec_points.begin(), vec_points.end());
	/*
	std::cout<< "The point vector: ";
	for (auto item :vec_points){
		std::cout<<item.toString();
	}
	std::cout<< std::endl;
	*/
	std::vector<int> bitmap (vec_points.size(),0);
	for (int i =0; i<4;++i){
		bitmap[i]=1;
	}

	do{
		int j=0;
		const Point* four_point_arr[4];
		for(int i=0; i<vec_points.size();++i ){
			//Pick four points from the list
			
			if(bitmap[i]==1){
				four_point_arr[j]=&vec_points[i];
				++j;
			}

			
		}


		if(collinearOrNot(four_point_arr)){

			LineSegment tmp_seg(*four_point_arr[0], *four_point_arr[3]);
	                //removeDuplicateLines(tmp_seg);
			set_lineSeg.insert(tmp_seg);
		
		}



	}while( std::ranges::prev_permutation(bitmap).found );
	

	//Delete duplicate line segments
	
};

//Helper function that check collinear
bool BruteCollinearPoints::collinearOrNot(const Point*  four_point_arr[4]){
	
		double first_slope= four_point_arr[0]->slopeTo(*four_point_arr[1]);
		double second_slope= four_point_arr[1]->slopeTo(*four_point_arr[2]);
		double third_slope= four_point_arr[2]->slopeTo(*four_point_arr[3]);
		double diff_1st_and_2nd = std::abs(first_slope-second_slope);
		double diff_2nd_and_3rd = std::abs(second_slope- third_slope);



		if((diff_1st_and_2nd < eps) && (diff_2nd_and_3rd < eps)){
			return true;
		}else{
			return false;
		}

}

//Helper function that remove duplicate line segmentsi
//Not required by the assignment. Therefore abandon
void BruteCollinearPoints:: removeDuplicateLines(LineSegment& tmp_seg){
	for(auto iter= set_lineSeg.begin(); iter!=set_lineSeg.end(); ++iter){
		const Point*  four_point_arr[4]{tmp_seg.p,tmp_seg.q, iter->p, iter->q};
	}
   	
}



//Class deconstructor
BruteCollinearPoints::~BruteCollinearPoints(){};

//Return line segment:
std::vector<LineSegment> BruteCollinearPoints::segments(){
    
	 
     	/*
	 std::cout<< "Before assign: ";
	 for (auto item : set_lineSeg){
		 std::cout<< item.toString(); 
	 }
	 std::cout<<std::endl;
	*/
	 std::vector<LineSegment> vec_lineSeg(set_lineSeg.begin(), set_lineSeg.end());
	 /*
	 std::cout<< "Before return: ";
	 for (auto item : vec_lineSeg){
		 std::cout<< item.toString(); 
	 }
	 std::cout<<std::endl;
	*/

	return vec_lineSeg; 


}

//Return the number of line segment:
int BruteCollinearPoints::numberOfSegments(){
	int result = set_lineSeg.size();
	return result;
}
