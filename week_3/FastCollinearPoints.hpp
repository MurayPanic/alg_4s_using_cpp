#include<iostream>
#include<vector>
#include "LineSegment.hpp"

#ifndef FASTCOLLINEARPOINTS_HPP
#define FASTCOLLINEARPOINTS_HPP

//Class declaration
class FastCollinearPoints;

#endif

//Class Definition

class FastCollinearPoints{
	public:
		FastCollinearPoints();
		FastCollinearPoints(std::vector<Point>& );
		~FastCollinearPoints();
		int numberOfSegments();
		std::vector<LineSegment> segments();
};

//Class Constructor
FastCollinearPoints::FastCollinearPoints(){
	throw std::invalid_argument("IllegalArgumentException: Null argument is not acceptatble");
}

FastCollinearPoints::FastCollinearPoints(std::vector<Point>& vec_point){
	
}

//Class Diconstructor
FastCollinearPoints::~FastCollinearPoints(){}

//Return the number of Segments
int FastCollinearPoints::numberOfSegments(){
	return 0;
}


