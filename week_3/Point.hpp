#include <iostream>
#include <climits>
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
        int compareTo(Point&);
        double slopeTo(Point&);
        bool operator < (const Point&); 


    
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

//the slope between this point and that point
double Point::slopeTo(Point& that_point_ins){
    double result{0.0};
    int denominator =  that_point_ins.x-x;
    int fraction = that_point_ins.y-y;
    if(denominator==0){
        if(fraction==0){result = -DBL_MAX;}
        result = DBL_MAX;
        
    }else{
        result= fraction / denominator;
    }
    return result;
}


//compare opeator
bool Point::operator < (const Point& that_point_ins){
    return true;
} 