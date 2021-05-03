#include <iostream>
#include <vector>
#include <exception>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <climits>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
#include "Digraph.hpp"

#pragma once
#ifndef SAP_HPP
#define SAP_HPP

//Class declaration
class SAP;
std::mutex mtx;
#endif

//Class definition



class SAP{
	public:
		SAP();
		SAP(Digraph);
		~SAP();
		int length(int, int);
		int ancestor(int, int);
		int length(std::vector<int>, std::vector<int> );
		int ancestor(std::vector<int>, std::vector<int> );
	
	private:

		Digraph graph_data;
		std::unordered_map<int, std::pair<int,int> > BreadthFirstSearch(int,  std::unordered_set<int>&, std::unordered_set<int>&);
		std::unordered_map<int, std::pair<int,int> > BreadthFirstSearch_MultiSource(std::vector<int>, std::unordered_set<int>&,  std::unordered_set<int>&);


		void parallel_BFS(int,int,
				   std::unordered_map<int, std::pair<int, int> >&,
				   std::unordered_map<int, std::pair<int, int> >&,
				   std::unordered_set<int>&
				
				);

		void parallel_BFS_MultiSource(std::vector<int>,
					      std::vector<int>,
				   std::unordered_map<int, std::pair<int, int> >&,
				   std::unordered_map<int, std::pair<int, int> >&,
				   std::unordered_set<int>&
				
				);




};

//Constructor and deconstructor
SAP::SAP(){}
SAP::~SAP(){}

SAP::SAP(Digraph D_ins){
	this->graph_data=D_ins;


}


int SAP::length(int v, int w){
	int result_len=-1;
	
	bool found_common_ancestor{false};
	std::unordered_set<int> common_ancestor_list;

	std::unordered_map<int, std::pair<int,int> > path_table_v;
	std::unordered_map<int, std::pair<int,int> > path_table_w;

	this->parallel_BFS(v,w,path_table_v, path_table_w,common_ancestor_list);
	

	if(!common_ancestor_list.empty()){
		
		result_len =INT_MAX;

		for(auto common_ancestor :common_ancestor_list){
			int tmp_len = path_table_w[common_ancestor].second + 
		             path_table_v[common_ancestor].second;
		
			result_len = tmp_len <result_len ? tmp_len :result_len;
		}

	}

	return result_len;

}

int SAP::length(std::vector<int> v, std::vector<int> w ){
	
	int shortest_len=-1;
		
	std::unordered_set<int> common_ancestor_list;

	std::unordered_map<int, std::pair<int,int> > path_table_v;
	std::unordered_map<int, std::pair<int,int> > path_table_w;

	this->parallel_BFS_MultiSource(v,w,path_table_v, path_table_w, common_ancestor_list);

	if(!common_ancestor_list.empty()){
		shortest_len= INT_MAX;

		for (int common_ancestor : common_ancestor_list){

		int tmp_len = path_table_w[common_ancestor].second + 
		             path_table_v[common_ancestor].second;
		//Debug output
		/*
		std::cout<<"The common ancestor candidate is: "<< common_ancestor<<std::endl;
		std::cout<<"tmp_len is :" <<tmp_len<<std::endl;
		*/
		shortest_len = tmp_len < shortest_len ? tmp_len : shortest_len;
		}
	
	}

	return shortest_len;
	

	//Implementation with BFS using single sources
	//Work but does not satisfied complexity requirement
	/*
	int shortest_len=INT_MAX;
	for(int  node_v : v){
		for(int  node_w: w){
		int tmp_len = this->length(node_v, node_w);
		shortest_len = tmp_len < shortest_len ? tmp_len : shortest_len;

		}
	}

	return shortest_len;
        */	
	
}

int SAP::ancestor(int v,int w){

	
	int shortest_common_ancestor{-1};
	int result_len = -1;

	std::unordered_set<int> common_ancestor_list;
	std::unordered_map<int, std::pair<int,int> > path_table_v;
	std::unordered_map<int, std::pair<int,int> > path_table_w;

	this->parallel_BFS(v,w,path_table_v, path_table_w,common_ancestor_list);


	if(!common_ancestor_list.empty()){
			
		result_len= INT_MAX;
		for(auto common_ancestor :common_ancestor_list){
			int tmp_len = path_table_w[common_ancestor].second + 
		             path_table_v[common_ancestor].second;
		
			shortest_common_ancestor = tmp_len < result_len ? common_ancestor : shortest_common_ancestor;
			result_len = tmp_len <result_len ? tmp_len :result_len;
		}
	
	}
	return shortest_common_ancestor;
}


int SAP::ancestor(std::vector<int> v, std::vector<int> w){
		
	std::unordered_set<int> common_ancestor_list;
	int shortest_common_ancestor{-1};
	int shortest_len=INT_MAX;

	std::unordered_map<int, std::pair<int,int> > path_table_v;
	std::unordered_map<int, std::pair<int,int> > path_table_w;

	this->parallel_BFS_MultiSource(v,w,path_table_v, path_table_w, common_ancestor_list);

	if(!common_ancestor_list.empty()){
		

		for (int common_ancestor : common_ancestor_list){

		int tmp_len = path_table_w[common_ancestor].second + 
		             path_table_v[common_ancestor].second;
		shortest_common_ancestor = tmp_len < shortest_len ? common_ancestor : shortest_common_ancestor;
		shortest_len = tmp_len < shortest_len ? tmp_len : shortest_len;
		}
	
	}
	

	return shortest_common_ancestor;
		

	//Implementation with single source BFS
	//Work but does not satisfiy complexity requirment
	
	/*		
	int shortest_len = INT_MAX;
	int shortest_common_ancestor=-1;

	for(int  node_v : v){
		for(int  node_w: w){
	
		bool found_common_ancestor{false};
		int common_ancestor=-1;

		std::unordered_map<int, std::pair<int,int> > path_table_v;
		std::unordered_map<int, std::pair<int,int> > path_table_w;

		this->parallel_BFS(node_v,node_w,path_table_v, path_table_w, found_common_ancestor,common_ancestor);
		
		int tmp_len = INT_MAX;
		if(found_common_ancestor){
			tmp_len = path_table_w[common_ancestor].second + 
		             	     path_table_v[common_ancestor].second;
	
		}
		
		
		shortest_common_ancestor = tmp_len < shortest_len ? common_ancestor : shortest_common_ancestor;

		shortest_len = tmp_len < shortest_len ? tmp_len : shortest_len;

		}
	}
	
	std::cout<<"The shortest_distance is: "<<shortest_len	<<std::endl;

	return shortest_common_ancestor;
	*/

	//Another Implementation with single source BFS
	//Work but does not satisfy complexity requirement
	/*	
	int shortest_len = INT_MAX;
	int shortest_common_ancestor=-1;

	for(int  node_v : v){
		for(int  node_w: w){
			int tmp_len = this->length(node_v, node_w);
			if(tmp_len==-1){continue;}
			if(tmp_len< shortest_len){
				shortest_common_ancestor = this->ancestor(node_v,node_w);
				shortest_len = tmp_len;
			}
		
		}
	
	}

	std::cout<<"The shortest_distance is: "<<shortest_len	<<std::endl;
	return shortest_common_ancestor;
	*/
}


//Breadth First Search from single source 
std::unordered_map<int, std::pair<int,int> > SAP::BreadthFirstSearch(
	      int source_node,
	      std::unordered_set<int>& shared_visited_node_list,
	      std::unordered_set<int>& common_ancestor_list){


	std::unordered_map<int, std::pair<int,int> > path_table;
	std::queue<int> helper_queue;


	//ED_pair is the abbreviation for edgeTo , distTo pair
	//The first int is the vertex it comes from
	//The second int is the distance from the source
	
	
	std::pair<int,int> source_ED_pair= std::make_pair(INT_MAX, 0);
	path_table[source_node] = source_ED_pair;
	helper_queue.push(source_node);
	


	while(!helper_queue.empty() ){
		int top_node = helper_queue.front();
		helper_queue.pop();
		
                
			
		int edgeTo = top_node;
		int distTo = path_table[top_node].second + 1;
		std::pair<int,int> ED_pair= std::make_pair(edgeTo, distTo);



		for (int neighbor_node : this->graph_data.adj(top_node) ){
			
			//if the node has already been visited, 
			//check whether recorded distance is the shortest
			
			if(path_table.contains(neighbor_node)){continue;}

			path_table[neighbor_node] = ED_pair;
			helper_queue.push(neighbor_node);
		}

		
		mtx.lock();
		if(shared_visited_node_list.contains(top_node)){
				common_ancestor_list.insert(top_node);	
		}else{
			shared_visited_node_list.insert(top_node);
		}
		mtx.unlock();
		
	}

	return path_table;
	
	
}

//Breadth First Search from multiple sources 
std::unordered_map<int, std::pair<int,int> > SAP::BreadthFirstSearch_MultiSource(
	      std::vector<int> source_nodes_set,
	      std::unordered_set<int>& shared_visited_node_list,
	      std::unordered_set<int>& common_ancestor_list){


	std::unordered_map<int, std::pair<int,int> > path_table;
	std::queue<int> helper_queue;
	// Use an internal list to mark the visited nodes by a BFS in a single thread
	// Avoid mistable termination of the search
	std::unordered_set<int> internal_visited_node_list;


	//ED_pair is the abbreviation for edgeTo , distTo pair
	//The first int is the vertex it comes from
	//The second int is the distance from the source
	
	for(int source_node: source_nodes_set){
		std::pair<int,int> source_ED_pair= std::make_pair(INT_MAX, 0);
		path_table[source_node] = source_ED_pair;
		helper_queue.push(source_node);
	}


	while(!helper_queue.empty() ){
		int top_node = helper_queue.front();
		helper_queue.pop();
		
                
			
		int edgeTo = top_node;
		int distTo = path_table[top_node].second + 1;
		std::pair<int,int> ED_pair= std::make_pair(edgeTo, distTo);



		for (int neighbor_node : this->graph_data.adj(top_node) ){
			
			//if the node has already been visited, 
			//check whether recorded distance is the shortest
			
			if(path_table.contains(neighbor_node)){
				if(path_table[neighbor_node].second < ED_pair.second){
			continue;
				}		
			}
			
			path_table[neighbor_node] = ED_pair;
			helper_queue.push(neighbor_node);
		}

		
		mtx.lock();
		if(shared_visited_node_list.contains(top_node)){
			if(!internal_visited_node_list.contains(top_node) ){
				common_ancestor_list.insert(top_node);
			}
			
		}else{
			internal_visited_node_list.insert(top_node);
			shared_visited_node_list.insert(top_node);
		}
		mtx.unlock();
	}

	return path_table;
	
	
}



void SAP::parallel_BFS(int v, 
		       int w,
		       std::unordered_map<int, std::pair<int, int> >& path_table_v,
		       std::unordered_map<int, std::pair<int, int> >& path_table_w,
		       std::unordered_set<int>& common_ancestor_list){


	std::unordered_set<int> shared_visited_node_list;
	
	
	std::future< std::unordered_map<int, std::pair<int, int> > > BFS_from_v = std::async(&SAP::BreadthFirstSearch, this, v, std::ref(shared_visited_node_list),  std::ref(common_ancestor_list) );

	std::future< std::unordered_map<int, std::pair<int, int> > > BFS_from_w = std::async(&SAP::BreadthFirstSearch, this, w, std::ref(shared_visited_node_list), std::ref(common_ancestor_list) );


	auto time_out = std::chrono::milliseconds(10);
	
	//Note that both thread need to complete before termination
	//therefore the condition shoud be OR(||) not AND(&&)
	while(BFS_from_v.valid() || BFS_from_w.valid() ){

	 	if(BFS_from_v.valid() && BFS_from_v.wait_for(time_out)== std::future_status::ready ){
		path_table_v = BFS_from_v.get();
		
		}
	
	 	if(BFS_from_w.valid() && BFS_from_w.wait_for(time_out)== std::future_status::ready ){
		path_table_w = BFS_from_w.get();
		
		}
	}


}



void SAP::parallel_BFS_MultiSource(std::vector<int> v, 
		       std::vector<int> w,
		       std::unordered_map<int, std::pair<int, int> >& path_table_v,
		       std::unordered_map<int, std::pair<int, int> >& path_table_w,
		       std::unordered_set<int>& common_ancestor_list){


	std::unordered_set<int> shared_visited_node_list;
	
	
	std::future< std::unordered_map<int, std::pair<int, int> > > BFS_from_v = std::async(&SAP::BreadthFirstSearch_MultiSource, this, v, std::ref(shared_visited_node_list),  std::ref(common_ancestor_list) );

	std::future< std::unordered_map<int, std::pair<int, int> > > BFS_from_w = std::async(&SAP::BreadthFirstSearch_MultiSource, this, w, std::ref(shared_visited_node_list), std::ref(common_ancestor_list) );


	auto time_out = std::chrono::milliseconds(10);
	
	//Note that both thread need to complete before termination
	//therefore the condition shoud be OR(||) not AND(&&)
	while(BFS_from_v.valid() || BFS_from_w.valid() ){

	 	if(BFS_from_v.valid() && BFS_from_v.wait_for(time_out)== std::future_status::ready ){
		path_table_v = BFS_from_v.get();
		
		}
	
	 	if(BFS_from_w.valid() && BFS_from_w.wait_for(time_out)== std::future_status::ready ){
		path_table_w = BFS_from_w.get();
		
		}
	}


}
