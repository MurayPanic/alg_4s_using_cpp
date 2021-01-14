#include "Point.hpp"
#include "LineSegment.hpp"
#include <string>
#include <vector>
#include <map>
#include "matplotlib-cpp/matplotlibcpp.h"
#ifndef DRAW_HPP
#define DRAW_HPP

namespace plt = matplotlibcpp;




void draw(Point);
void draw(LineSegment);
void show();


#endif

void draw(Point point_ins){
	std::vector<int> x_vec{point_ins.x};
	std::vector<int> y_vec{point_ins.y};
	double size=10;
	std::map<std::string, std::string> keywords{};
	keywords["c"]="b";
	keywords["marker"]="^";
	plt::scatter(x_vec, y_vec, size, keywords);
	

}

void draw(LineSegment LS_ins){
	std::vector<int> x_vec{};
	std::vector<int> y_vec{};
	auto p= *LS_ins.p;
	auto q= *LS_ins.q;
	x_vec.push_back(p.x);
	x_vec.push_back(q.x);
	y_vec.push_back(p.y);
	y_vec.push_back(q.y);
	std::map<std::string, std::string> keywords{};
	keywords["c"]="r";
	plt::plot(x_vec, y_vec, keywords);	
}


void show(){
	plt::show();
}




