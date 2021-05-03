#include <iostream>
#include <string>
#include <cmath>
#pragma once
#ifndef POINT2D_HPP
#define POINT2D_HPP

//Class declaration
class Point2D;
const double eps = 1e-20;

#endif

//Class definition

class Point2D{
	public:
		Point2D();
		Point2D(double, double);
		~Point2D();

		double x() const;
		double y() const;
		double distanceTo(Point2D);
		double distanceSquaredTo(Point2D);
		bool operator < (const Point2D&) const;
		bool operator== (const Point2D&) const;
		std::string toString();
	private:
		double x_coor;
		double y_coor;
		
	
};

//Constructor and deconstructor
Point2D::Point2D(){}

Point2D::~Point2D(){}

Point2D::Point2D(double x_coor, double y_coor):x_coor(x_coor), y_coor(y_coor){}

double Point2D::x() const{
	return this->x_coor;
}

double Point2D::y()const{
	return this->y_coor;
}


double Point2D::distanceTo(Point2D that){
	double square_dist = this->distanceSquaredTo(that);
	double result = std::sqrt(square_dist);

	return result;
}


double Point2D::distanceSquaredTo(Point2D that){
	double x_1 = this->x_coor;
	double y_1 = this->y_coor;
	double x_2 = that.x();
	double y_2 = that.y();	
	double dist = std::pow( (x_1-x_2),2 ) + std::pow( (y_1-y_2), 2);

	return dist;

}

bool Point2D::operator< (const Point2D& that) const{
	if(this->y_coor< that.y() || ((this->y_coor== that.y()) && (this->x_coor < that.x()))){
	return true;
	}else{
	return false;
	}
}

bool Point2D::operator== (const Point2D& that) const{
	double x_1 = this->x_coor;
	double y_1 = this->y_coor;
	double x_2 = that.x();
	double y_2 = that.y();

	double x_diff = std::abs(x_1 - x_2);
	double y_diff = std::abs(y_1 - y_2);

	if(x_diff <eps  && y_diff < eps){
		return true;
	}else{
		return false;
	}
}

std::string Point2D::toString(){
	std::string point_str{};
	point_str= "("+ std::to_string(this->x_coor)+ ","+ std::to_string(this->y_coor)+")";
	return point_str;
}
