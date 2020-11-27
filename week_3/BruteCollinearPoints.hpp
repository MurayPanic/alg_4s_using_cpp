#include <iostream>
#include <vector>
#include <algorithm>
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
		int numberofSegments();
		std::vector<LineSegment> segments();
};

//Class constructor
BruteCollinearPoints::BruteCollinearPoints(){
	throw std::invalid_argument("IllegalArgumentException: Null argument is not acceptable");
};

BruteCollinearPoints::BruteCollinearPoints(std::vector<Point>& vec_points){
	std::sort(vec_points.begin(), vec_points.end());
	std::vector<int> bitmap (vec_points.size(),0);
	for (int i =0; i<4;++i){
		bitmap[i]=1;
	}

	do{
	}

};

//Class deconstructor
BruteCollinearPoints::~BruteCollinearPoints(){};

