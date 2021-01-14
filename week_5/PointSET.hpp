#include <iostream>
#include <vector>
#include <set>
#include <cfloat>
#include "Point2D.hpp"
#include "RectHV.hpp"

#ifndef POINTSET_HPP
#define POINTSET_HPP

//Class declaration
class PointSET;

#endif

//class definition

class PointSET {
	public:
		PointSET();
		~PointSET();
		bool isEmpty();
		int size();
		void insert( Point2D );
		bool contains( Point2D& );
		std::vector<Point2D> range(RectHV);
		Point2D nearest( Point2D );
	private:
		std::set<Point2D> point_set;


};

//Constructor and deconstructor
PointSET::PointSET(): point_set(){}
PointSET::~PointSET(){}

bool PointSET::isEmpty(){
	return this->point_set.empty();
}

int PointSET::size(){
	return this->point_set.size();
}

void PointSET::insert(Point2D point_ins){
	this->point_set.insert(point_ins);
}

bool PointSET::contains(Point2D& point_ins){
	return this->point_set.contains(point_ins);
	
} 

//all points that are inside the rectangle (or on the boundary)
std::vector<Point2D> PointSET::range(RectHV rect_ins){
	std::vector<Point2D> result;
	for(auto item : this->point_set){
		if(rect_ins.contains(item)){
			result.push_back(item);
		} 
	}
	return result;
}

//a nearest neighbor in the set to point p; null if the set is empty
Point2D PointSET::nearest( Point2D point_ins){
	Point2D nearest_point;
	double  shortest_dist{DBL_MAX};
	for(auto item : this->point_set){
		auto dist = point_ins.distanceTo(item);
		if(dist < shortest_dist){
			nearest_point= item;
			shortest_dist= dist;
		}
	}
	return nearest_point;
}
