#include <iostream>
#include "Point.hpp"

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

//class declaration

class LineSegment;

#endif

//class definition
class LineSegment {
	public:
		LineSegment();
		LineSegment(const Point& , const Point&);
		~LineSegment();
		std::string toString() const;	
		bool operator == (const LineSegment&) const;
		const Point* p;
		const Point* q;


};


//constructer
LineSegment::LineSegment(): p(nullptr),q(nullptr){};

LineSegment::LineSegment(const Point& point_ins_1, const Point& point_ins_2)
	:p( &point_ins_1),q( &point_ins_2){
};

//deconstructer
LineSegment::~LineSegment(){};

//return a string that represent the line segment
std::string LineSegment::toString() const{
	std::string result;
	if(p&&q){
		result = p->toString() + "->" + q->toString();
	}
	return result;
}

//equal operator
bool LineSegment::operator == (const LineSegment& that_LS_ins)const{
	bool criti_match = ( *(this->p) == *(that_LS_ins.p)) && (*(this->q) == *(that_LS_ins.q));
	bool criti_miss_match = (*(this->p) == (*that_LS_ins.q)) && (*(this->q) == *(that_LS_ins.p));
	return criti_match || criti_miss_match;
}
