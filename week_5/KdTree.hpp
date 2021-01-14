#include <iostream>
#include <exception>
#include <stack>
#include <vector>
#include <cfloat>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#include "Point2D.hpp"
#include "RectHV.hpp"

#pragma once
#ifndef KDTREE_HPP
#define KDTREE_HPP

//Class declaration
class KdTreeNode;
class KdTree;

#endif 

//Class definition

class KdTreeNode{
	public:
		KdTreeNode();
		KdTreeNode(Point2D, RectHV, bool);
		~KdTreeNode();

		Point2D point_data;
		RectHV rect_data;
		KdTreeNode* prev_node;
		KdTreeNode* left_child;
		KdTreeNode* right_child;
		bool jud_by_coor; // True for judge by x coordinate
				  // False for judge by y coordinate
};


class KdTree{
	public:
		KdTree();
		~KdTree();

		bool isEmpty();
		int size();
		void insert(Point2D);
		bool contains(Point2D);
		void draw();
		std::vector<Point2D> range(RectHV);
		Point2D nearest(Point2D);
	private:
		KdTreeNode* head;
		void search_tree_node(RectHV&, std::vector<Point2D>&, KdTreeNode*);
		void search_nearest_neighbor(Point2D&, Point2D, double&, KdTreeNode*);


};

//KdTreeNode: Constructor and deconstructor
KdTreeNode::KdTreeNode(){};

KdTreeNode::KdTreeNode(Point2D point_ins, RectHV rect_ins, bool jud_criteria):  
	    prev_node(nullptr), 
	    left_child(nullptr), right_child(nullptr),
	    jud_by_coor(jud_criteria)
{
	bool point_out_of_range= point_ins.x()<0 || point_ins.x()>1 || point_ins.y()<0 || point_ins.y()>1;
	if(point_out_of_range){
		throw std::invalid_argument("The provided point coordinates should be between 0 and 1.");
	}

	bool rect_out_of_range =
		rect_ins.xmax()<0 || rect_ins.xmax()>1 ||
		rect_ins.ymax()<0 || rect_ins.ymax()>1;
	if(rect_out_of_range){
		throw std::invalid_argument("The provided rectangle is not within a unit square.");
	}

	bool point_in_rect = rect_ins.contains(point_ins);

	if(!point_in_rect){
		throw std::invalid_argument("The provided point and rectangle are not matched");
	}

	point_data = point_ins;
	rect_data = rect_ins;

}


KdTreeNode::~KdTreeNode(){};


//KdTree: constructor and deconstructor

KdTree::KdTree():head(nullptr){};

KdTree::~KdTree(){};

//KdTree: other member function

bool KdTree::isEmpty(){
	return this->head == nullptr;
}

int KdTree::size(){
	int node_num{0};

	std::stack<KdTreeNode*> node_stack;
	if(this->head){node_stack.push(this->head);}

	while(!node_stack.empty()){
		auto cur_node_ptr= node_stack.top();
		node_stack.pop();
		node_num+=1;

		if(cur_node_ptr->left_child ){
			node_stack.push(cur_node_ptr->left_child);		
		}

		if(cur_node_ptr->right_child){
			node_stack.push(cur_node_ptr->right_child);
		}

	}

	return node_num;


}

void KdTree::insert(Point2D point_ins){
	KdTreeNode* cur_node_ptr = this->head;
	KdTreeNode* prev_node_ptr = nullptr;	
	bool left_right_marker=true; // true for left, false for right

	while(cur_node_ptr){
		prev_node_ptr= cur_node_ptr;
		if(cur_node_ptr->jud_by_coor)  //judge by x
		{
			if(point_ins.x()<  cur_node_ptr->point_data.x()  ){
				cur_node_ptr = cur_node_ptr->left_child;
				left_right_marker=true;
			}else{
				cur_node_ptr = cur_node_ptr->right_child;
				left_right_marker=false;
			}
		}
		else     //judge by y
		{
			if(point_ins.y() <  cur_node_ptr->point_data.y() ){
				cur_node_ptr= cur_node_ptr->left_child;
				left_right_marker=true;
			
			}else{
				cur_node_ptr = cur_node_ptr->right_child;
				left_right_marker=false;
			}
		
		
		}
	}

	RectHV tmp_rect(0,0,1,1);
	


	bool next_jud_by_coor = prev_node_ptr ? !prev_node_ptr->jud_by_coor : true;
	KdTreeNode* new_KT_node_ptr= new KdTreeNode(point_ins, tmp_rect, next_jud_by_coor);

	new_KT_node_ptr->prev_node = prev_node_ptr;

	if(prev_node_ptr){
		if(left_right_marker){
					
			if(prev_node_ptr->jud_by_coor){
				RectHV next_rect(prev_node_ptr->rect_data.xmin(),
						 prev_node_ptr->rect_data.ymin(),
						 prev_node_ptr->point_data.x(),
					    	 prev_node_ptr->rect_data.ymax()
						);
				new_KT_node_ptr->rect_data = next_rect;

			}else{
				RectHV next_rect(prev_node_ptr->rect_data.xmin(),
						 prev_node_ptr->rect_data.ymin(),
						 prev_node_ptr->rect_data.xmax(),
						 prev_node_ptr->point_data.y()
						);	
				new_KT_node_ptr->rect_data = next_rect;
			}

			prev_node_ptr->left_child = new_KT_node_ptr;

		}else{
			if(prev_node_ptr->jud_by_coor){
				RectHV next_rect(prev_node_ptr->point_data.x(),
						 prev_node_ptr->rect_data.ymin(),
						 prev_node_ptr->rect_data.xmax(),
					    	 prev_node_ptr->rect_data.ymax()
						);
				new_KT_node_ptr->rect_data = next_rect;

			}else{
				RectHV next_rect(prev_node_ptr->rect_data.xmin(),
						 prev_node_ptr->point_data.y(),
						 prev_node_ptr->rect_data.xmax(),
						 prev_node_ptr->rect_data.ymax()
						);	
				new_KT_node_ptr->rect_data = next_rect;
			}
			prev_node_ptr->right_child = new_KT_node_ptr;
		}
	}else{
		this->head=new_KT_node_ptr;
	}
	


}

bool KdTree::contains(Point2D point_ins){
	std::stack<KdTreeNode*> node_stack;

	if(this->head){
		node_stack.push(this->head);
	}else{
		return false;
	}

	while(!node_stack.empty()){
		auto cur_node_ptr = node_stack.top();
		node_stack.pop();
		if (cur_node_ptr->point_data == point_ins){return true;}

		if(cur_node_ptr->left_child){
			node_stack.push(cur_node_ptr->left_child);
		}

		if(cur_node_ptr->right_child){
			node_stack.push(cur_node_ptr->right_child);
		}
	}

	return false;
}

void KdTree::draw(){
	cv::Mat canvas(600,600, CV_8UC3, cv::Scalar(255,255,255));

	std::stack<KdTreeNode*> node_stack;

	if(this->head){
		node_stack.push(this->head);
	}

	while(!node_stack.empty()){
		KdTreeNode* cur_node_ptr = node_stack.top();
		node_stack.pop();

		//Pay attention that in opencv the origin is on the top left corner
		//Thereofore some special processing is necessary for the y coordinate.
		cv::Point cv_point_ins(cur_node_ptr->point_data.x()*600, 
			  600-cur_node_ptr->point_data.y() *600);
		cv::circle(canvas, cv_point_ins, 3, cv::Scalar(0,0,0), -1);
		cv::Point cv_line_p1;
		cv::Point cv_line_p2;
		cv::Scalar line_color;
		if(cur_node_ptr->jud_by_coor){
			cv_line_p1 = cv::Point(
					cur_node_ptr->point_data.x()*600,
					600-cur_node_ptr->rect_data.ymin()*600
					);
			cv_line_p2 = cv::Point(
						cur_node_ptr->point_data.x()*600,
						600-cur_node_ptr->rect_data.ymax()*600
						);
			line_color= cv::Scalar(0,0,255);
		}else{
		
			cv_line_p1 = cv::Point(
					     cur_node_ptr->rect_data.xmin()*600,
					     600-cur_node_ptr->point_data.y()*600
					     );
			cv_line_p2 = cv::Point(
					   cur_node_ptr->rect_data.xmax()*600,
					   600-cur_node_ptr->point_data.y()*600
					   );
			line_color = cv::Scalar(255,0,0);
		
		}
		cv::line(canvas,cv_line_p1, cv_line_p2,line_color,2);

		if(cur_node_ptr->left_child){
			node_stack.push(cur_node_ptr->left_child);
		}

		if(cur_node_ptr->right_child){
			node_stack.push(cur_node_ptr->right_child);
		}
	}

	cv::imshow("Kd-Tree",canvas);

	cv::waitKey(0);
}

std::vector<Point2D> KdTree::range(RectHV target_rect){
	std::vector<Point2D> result;
	KdTreeNode* cur_node_ptr = this->head;
	search_tree_node(target_rect, result, cur_node_ptr );

	return result;
}

void KdTree::search_tree_node(RectHV& target_rect,
			      std::vector<Point2D>&  result,
			      KdTreeNode* cur_node_ptr){
	if(cur_node_ptr){
		//Determine where current point is within the triangle
		if(target_rect.contains(cur_node_ptr->point_data) ){
			result.push_back(cur_node_ptr->point_data);		
		}

		//Search left child 
		if(cur_node_ptr->left_child){
			if(target_rect.intersects(cur_node_ptr->left_child->rect_data)){
			this->search_tree_node(target_rect, result, cur_node_ptr->left_child);
			}
		}

		//Search Right child

		if(cur_node_ptr->right_child){
			if(target_rect.intersects(cur_node_ptr->right_child->rect_data)){
			this->search_tree_node(target_rect, result, cur_node_ptr->right_child);
			}
		}


	}
	else{
		return;
	}

}

Point2D KdTree::nearest(Point2D point_ins){
	Point2D nearest_point;
	double shortest_dist(DBL_MAX);
	KdTreeNode* cur_node_ptr;

	search_nearest_neighbor(point_ins, nearest_point,shortest_dist,cur_node_ptr);

	return nearest_point;


}

void search_nearest_neighbor(
			     Point2D& target_point,
			     Point2D& nearest_point,
			     double&  shortest_dist,
			     KdTreeNode* cur_node_ptr){
	
	if(cur_node_ptr){
		//Decide whether to search that tree
		if(cur_node_ptr->rect_data.distanceTo(target_point) > shortest_dist ){
		return;

		}else{

		double&  tmp_dist = target_point.distanceTo(cur_node_ptr->point_data);
		if(tmp_dist< shortest_dist){
			nearest_point = cur_node_ptr->point_data;
			shortest_dist = tmp_dist;
		}

		//Search left subtree
		search_nearest_neighbor(target_point, nearest_point, shortest_dist,
					cur_node_ptr->left_child);

		//Search right subtree
		search_nearest_neighbor(target_point, nearest_point, shortest_dist,  					    cur_node_ptr->right_child);

		}

	}
	else{
		return;
	}

}
