#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <exception>
#include "Point2D.hpp"

#pragma once
#ifndef RECTHV_HPP
#define RECTHV_HPP

//class declaration
class RectHV;
//const double eps= 1e-20;

#endif

class RectHV{
	public:
		RectHV();
		RectHV(double,double,double,double);
		~RectHV();

		double xmin() const;
		double ymin() const;
		double xmax() const;
		double ymax() const;

		bool contains( Point2D& );
		bool intersects (RectHV& );
		double distanceTo( Point2D );
		double distanceSquaredTo( Point2D );
		bool operator == (const RectHV&) const;
		std::string toString();
	private:
		double left_bottom_x;
		double left_bottom_y;
		double right_top_x;
		double right_top_y;

};

//Constructor and deconstructor
RectHV::RectHV(){}
RectHV::~RectHV(){}

RectHV::RectHV(double input_xmin, double input_ymin, double input_xmax, double input_ymax)
	: left_bottom_x(input_xmin), left_bottom_y(input_ymin), 
	  right_top_x(input_xmax), right_top_y(input_ymax){
		 if(input_xmin>input_xmax || input_ymin > input_ymax ){
			throw std::invalid_argument("The input coordinates are not legal.");
		  
		  }
}

double RectHV::xmin() const{ return this->left_bottom_x;}
double RectHV::ymin() const{ return this->left_bottom_y;}
double RectHV::xmax() const{ return this->right_top_x;}
double RectHV::ymax() const{ return this->right_top_y;}


bool RectHV::contains(Point2D& point_ins){
	auto px= point_ins.x();
	auto py= point_ins.y();
	return px>=this->xmin() && px<= this->xmax() 
	       && py>= this->ymin() && py<= this->ymax();
}

bool RectHV:: operator == (const RectHV& that ) const{
	return this->xmin()== that.xmin()
	       && this->xmax() == that.xmax()
	       && this->ymin() == that.ymin()
	       && this->ymax() == that.ymax();
}

std::string RectHV:: toString(){
	std::string rect_str{};
	rect_str= "["+ std::to_string(this->xmin())+","
		     + std::to_string(this->xmax())+"]"
	           +" x "+
	          "["+ std::to_string(this->ymin())+","
		     + std::to_string(this->ymax())+"]"  ;		  
	return rect_str;
}


bool RectHV::intersects (RectHV& that){
	bool intersect_in_x = (this->xmin()<= that.xmin() && that.xmin()<=this->xmax())  ||   (this->xmin() <= that.xmax() && that.xmax() <= this->xmax() );
	bool intersect_in_y = (this->ymin() <= that.ymin() && that.ymin() <= this->ymax() ) || (this->ymin() <= that.ymax() && that.ymax() <= this->ymax() );

	return intersect_in_x && intersect_in_y;


}

double RectHV::distanceTo (Point2D point_ins){
	double result{0};

	double dist_to_left = std::abs(point_ins.x() - this->xmin() );
	double dist_to_right = std::abs(point_ins.x()- this->xmax() ) ;
	double dist_to_bottom = std::abs(point_ins.y() - this->ymin() );
	double dist_to_top = std::abs(point_ins.y() - this->ymax() );
	
	std::vector<double> dist_edge_vec{dist_to_left,dist_to_right,dist_to_bottom, dist_to_top};
	std::sort(dist_edge_vec.begin(), dist_edge_vec.end());

	//Debug output
	/*	
	std::cout<<"The edge vec"<<std::endl;
	for(auto item : dist_edge_vec){
		std::cout<<item<<" ";
	}
	std::cout<<std::endl;
	*/

	if(this->contains(point_ins) ){
		result = *dist_edge_vec.begin();	
		return result;	
	}

	if(this->xmin() < point_ins.x() && point_ins.x() < this->xmax()){
		result = std::fmin(dist_to_bottom, dist_to_top);
		return result;
	}

	if(this->ymin()< point_ins.y() && point_ins.y() < this->ymax() ){
		result = std::fmin(dist_to_left, dist_to_right);
		return result;
	}

	Point2D leftbottom_p(this->xmin(), this->ymin() );
	Point2D rightbottom_p(this->xmax(), this->ymin() );
	Point2D lefttop_p(this->xmin(), this->ymax() );
	Point2D righttop_p(this->xmax(), this->ymax() );

	double dist_to_leftbottom = point_ins.distanceTo(leftbottom_p );
	double dist_to_rightbottom = point_ins.distanceTo(rightbottom_p );
	double dist_to_lefttop = point_ins.distanceTo(lefttop_p );
	double dist_to_righttop = point_ins.distanceTo(righttop_p );
	
	std::vector<double> dist_vex_vec{dist_to_leftbottom, dist_to_rightbottom, dist_to_lefttop, dist_to_righttop};

	std::sort(dist_vex_vec.begin(), dist_vex_vec.end() );

	/*Debug output
	std::cout<<"The vex vec"<<std::endl;
	for(auto item : dist_vex_vec){
		std::cout<<item<<" ";
	}
	std::cout<<std::endl;
	*/
	result= *dist_vex_vec.begin();

	return result;


}


double RectHV::distanceSquaredTo(Point2D point_ins){
	double dist = this->distanceTo(point_ins);
	return std::pow(dist,2);
	 

}

