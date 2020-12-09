#include<iostream>
#include<vector>
#include<unordered_set>
#include<string>
#include<utility>
#include<algorithm>
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
	private:
	//hash function for unordered set
		class Hash_LineSegment{
				public:
					std::size_t operator()(const LineSegment& LS_ins)const{
					std::string LS_str=LS_ins.toString();
	       				std::hash<std::string> str_hasher;
					return str_hasher(LS_str);		
				}
		};

		std::unordered_set<LineSegment, Hash_LineSegment> set_lineSeg;
		std::vector<Point>* vec_point_ptr;
		void default_sort(std::vector<std::pair<Point, double> > &);
		void extract_lineSeg(Point&,std::vector<std::pair<Point, double>>&);
		const double eps =1e-20;
		
};


//Class Constructor
FastCollinearPoints::FastCollinearPoints(): vec_point_ptr(nullptr){
	throw std::invalid_argument("IllegalArgumentException: Null argument is not acceptatble");
}

FastCollinearPoints::FastCollinearPoints(std::vector<Point>& vec_point):vec_point_ptr(&vec_point){
	for(auto iter_p = vec_point.begin(); iter_p!= vec_point.end(); ++iter_p){

		std::vector< std::pair< Point, double> > slope_vec;

		for(auto iter_q= vec_point.begin(); iter_q!=vec_point.end();++iter_q){
		if (iter_q==iter_p){continue;}
		else{
			double tmp_slope = iter_p->slopeTo(*iter_q);
			std::pair tmp_slope_pair= std::make_pair(*iter_q, tmp_slope);
			slope_vec.push_back(tmp_slope_pair);
		
			}
		}

		default_sort(slope_vec);
                extract_lineSeg(*iter_p,slope_vec);

		/*
		std::cout<<"The origin is"<<iter_p->toString()<<std::endl;		
		std::cout<<"Now print the slope map:";
	
		for (auto& item : slope_vec){
		std::cout<<"("<<item.first.toString()<<" "<<item.second<<") ";
		}	

		std::cout<<std::endl;
		*/

	}	
};



//Class Diconstructor
FastCollinearPoints::~FastCollinearPoints(){};


// sort the slope map by value with C++ defualt sort method
void FastCollinearPoints::default_sort(std::vector< std::pair<Point, double > >&  slope_vec){
	typedef  std::pair<Point, double> point_slope_pair;

	struct cmp_by_slope{
		bool operator()(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
			
			return  pair_1.second< pair_2.second;
		}
	};

	struct cmp_by_point{
		bool operator()(const point_slope_pair& pair_1, const point_slope_pair& pair_2){
			return (pair_1.first)< (pair_2.first);
		}
	};

	std::sort(slope_vec.begin(), slope_vec.end(), cmp_by_slope());

	auto head_iter = slope_vec.begin();
	auto tail_iter = head_iter;
	double cur_slope = head_iter->second;

	for(auto cur_iter =slope_vec.begin(); cur_iter!=slope_vec.end(); ++cur_iter){
	double slope_diff= std::abs(cur_iter->second - cur_slope);
	bool slope_equal = (slope_diff< eps);
	if(!slope_equal){
		std::sort(head_iter, cur_iter, cmp_by_point());

		head_iter=cur_iter;
		tail_iter=head_iter;
		cur_slope=cur_iter->second;
	

	}else{
		tail_iter=cur_iter;
	}

	}
     

}

//Extract the line segment and insert it to the set_lineSeg
void FastCollinearPoints::extract_lineSeg(Point& origin,
			std::vector<std::pair<Point, double> >& slope_vec  ){
	auto head_iter = slope_vec.begin();
	auto tail_iter = head_iter;
	double cur_slope = head_iter->second;
	for(auto cur_iter=slope_vec.begin(); cur_iter!=slope_vec.end(); ++cur_iter){
		double  slope_diff = std::abs(cur_iter->second-cur_slope);
		bool slope_equal = (slope_diff<eps);
		if(!slope_equal){

		       if(tail_iter-head_iter >1){

                       
                       const Point& line_head= (origin)< (head_iter->first) ? (origin) : *(std::find(vec_point_ptr->begin(),vec_point_ptr->end(), head_iter->first));
		       const Point& line_tail= origin < (tail_iter->first) ? *(std::find(vec_point_ptr->begin(), vec_point_ptr->end(),tail_iter->first) )  : origin;

		       LineSegment tmp_LS(line_head, line_tail);
		       //std::cout<<"One LS extract:"<< tmp_LS.toString()<<std::endl;
		       set_lineSeg.insert(tmp_LS);
		       }
		       head_iter=cur_iter;
		       tail_iter=head_iter;
		       cur_slope= cur_iter->second;
		       

		}else{
	       		tail_iter= cur_iter;
		}
	
    }



}
//Return line segment
std::vector<LineSegment> FastCollinearPoints::segments(){

	std::vector<LineSegment> vec_lineSeg(set_lineSeg.begin(), set_lineSeg.end());
	return vec_lineSeg;
}

//Return the number of line segment:

int FastCollinearPoints::numberOfSegments(){
	int result = set_lineSeg.size();
	return result;
}



