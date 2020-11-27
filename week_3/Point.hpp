#include <iostream>
#include <climits>
#include <string>
#ifndef POINT_HPP
#define POINT_HPP

//Class declaration
class Point;

#endif

//Class definition
class Point{
    public:
        Point();
        Point(int, int);
        ~Point();
	std::string toString() const;

        //int compareTo(Point&);
        double slopeTo(const Point&);
        bool operator < (const Point&) const; 
	bool operator == (const Point&) const;
	bool slopeOrder(const Point&, const Point&);


        int x;
        int y;

};

//Constructor
Point::Point():x(INT_MAX),y(INT_MAX){

}

Point::Point(int x_val, int y_val): x(x_val), y(y_val){

}

//Deconstructor
Point::~Point(){

}

//compare two points by y-coordinates, breaking ties by x-coordinates
/*
int  Point::compareTo(Point& point_ins){
        int result;
        if(x==point_ins.x && y== point_ins.y){result=0;}
        if(y<point_ins.y ||(y==point_ins.y && x<point_ins.x)){
            result=-1;
        }else{
            result=1;
        }
        return result;
}
*/



//the slope between this point and that point
double Point::slopeTo(const Point& that_point_ins){
    double result{0.0};
    int denominator =  that_point_ins.x-x;
    int fraction = that_point_ins.y-y;
    if(denominator==0){
        if(fraction==0){result = -DBL_MAX;}
	else{result = DBL_MAX;}
        
    }else{
        result= fraction / denominator;
    }
    return result;
}


//Compare opeator
bool Point::operator < (const Point& that_point_ins) const {
        if(y< that_point_ins.y ||(y==that_point_ins.y && x<that_point_ins.x)){
            return true;
        }else{
            return false;
        }


}

//Equal operator

bool Point::operator == (const Point& that_point_ins) const{
	if (y==that_point_ins.y && x==that_point_ins.x){
		return true;
	}else{
		return false;
	}
}

//Compare two points by the slope they make with this point
bool Point::slopeOrder(const Point& point_ins_1, const Point& point_ins_2){
	double slope_1 = slopeTo(point_ins_1);
	double slope_2 = slopeTo(point_ins_2);
	return slope_1<slope_2;
}

//Return a string of the point
std::string Point::toString() const {
	std::string result="("+std::to_string(x)+","+ std::to_string(y)+")";
	return result;
}
