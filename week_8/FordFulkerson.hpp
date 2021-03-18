#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#include "FlowNetwork.hpp"

#pragma once
#ifndef FORDFULKERSON_HPP
#define FORDFULERSON_HPP

//Class declaration
class FordFulkerson;

#endif


//Class definition
class FordFulkerson{
	public:
		FordFulkerson();
		FordFulkerson(FlowNetwork&, int, int);
		~FordFulkerson();
		bool inCut(int);
		double value();
	private:
		FlowNetwork FN_data;
		double max_flow_value;
		std::vector<bool> marked; // is there a path s->v ?
		std::vector<FlowEdge> edgeTo; // last edge on the shortested s-v path
		int source;
		int target;
		bool hasAugmentedPath();
		void check();
		void validate(int);
		

		

};

//Constructor and deconstructor

FordFulkerson::FordFulkerson(){}

FordFulkerson::FordFulkerson(FlowNetwork& FN_ins, int input_source, int input_target): 
										max_flow_value(0)
{
	this->FN_data = FN_ins;
	this->validate(input_source);
	this->validate(input_target);
	this->source = input_source;
	this->target = input_target;
	
	for(int i{0}; i<this->FN_data.V(); ++i){
		this->marked.push_back(false);
		FlowEdge empty_edge;
		this->edgeTo.push_back(empty_edge);
	}

	int counter{0};
	while(this->hasAugmentedPath() ){
		//std::cout<<"The "<< counter++ << " iteration;"<<std::endl;
		//Finde the bottleneck on the augmented path
		double bottle = DBL_MAX;

		for(int cur_node = this->target; cur_node!= this->source; cur_node = this->edgeTo[cur_node].other(cur_node)){
			if (this->edgeTo[cur_node].residualCapacityTo(cur_node)<bottle){
				bottle = this->edgeTo[cur_node].residualCapacityTo(cur_node);
			}

		}
		//std::cout<< "I am place 2"<<std::endl;

		//Reduce the capacity accordingly

		for(int cur_node = this->target; cur_node!= this->source; cur_node = this->edgeTo[cur_node].other(cur_node) ){
			edgeTo[cur_node].addResidualFlowTo(cur_node, bottle);
			
		}

		/*
		std::cout<< "I am place 3"<<std::endl;
		std::cout<< "The reduce capacity is: "<<std::endl;
		for (auto edge : this->edgeTo){
			std::cout<<edge.toString()<<std::endl;
		}
		*/

		//Update residual graph
		FlowNetwork updated_graph(this->FN_data.V());
		for(int i{0}; i< this->FN_data.V(); ++i){
			std::vector<FlowEdge> tmp_edge_list = this->FN_data.adj(i);
			bool self_loop_found{false};
			for(FlowEdge edge : tmp_edge_list){
				if(edge.to() !=i){continue;}
				
				if(edge.to()==edge.from()){
					if(self_loop_found){
						continue;
					}else{
						self_loop_found = true;
					}
				}
				
				//std::cout<< "I am in  "<<i<<" Now process tmp edge: " <<edge.toString()<<std::endl;
				
				bool same_edge = edge.to()==edgeTo[i].to()  && edge.from()==edgeTo[i].from() ;
				if(same_edge){
					updated_graph.addEdge(edgeTo[i]); 
				}else{
					updated_graph.addEdge(edge); 
				}
				
			}
			//std::cout<< "current updated_graph is" <<updated_graph.toString()<<std::endl;
			//std::cout<<"------------"<<std::endl;
		}

		this->FN_data = updated_graph;
		//std::cout<< "the updated_grapth is "<< this->FN_data.toString() <<std::endl;

        //Update max flow
		this->max_flow_value += bottle;

		


	}

	//std::cout<<"The final flow graph is:"<<FN_data.toString()<<std::endl;
	//this->check();

}

FordFulkerson::~FordFulkerson(){}

//Member function

bool FordFulkerson::hasAugmentedPath(){
	std::queue<int> helper_queue;
	this->edgeTo.clear();
	this->marked.clear();

	for(int i{0}; i<this->FN_data.V(); ++i){
		this->marked.push_back(false);
		FlowEdge empty_edge;
		this->edgeTo.push_back(empty_edge);
	}


	helper_queue.push(this->source);
	this->marked[this->source]=true;

	while(!helper_queue.empty() && !this->marked[this->target]){
		int cur_node = helper_queue.front();
		helper_queue.pop();

		//std::cout<<"The cur_node is: "<<cur_node << std::endl;
			
		std::vector<FlowEdge> edge_list = this->FN_data.adj(cur_node);
		
		for(FlowEdge FE_item : edge_list ){
			int next_node = FE_item.other(cur_node);
			if(!this->marked[next_node ] && FE_item.residualCapacityTo(next_node )>0 ){
				
				this->marked[next_node]=true;
				this->edgeTo[next_node] = FE_item;
				helper_queue.push(next_node );
			}
			
		}

		
	}

	//test output 
	/*
	std::cout<< "The following is the marked matrix"<<std::endl;
	for(auto item : this-> marked){
		std::cout<<item<<std::endl;
	}

	
	std::cout<< "The following is the EdgeTO matrix"<<std::endl;
	for(auto item : this-> edgeTo){
		std::cout<<item.toString()<<std::endl;
	}
	*/
	return this->marked[this->target];


}

void FordFulkerson::validate(int vertex){
	if(vertex<0 || vertex>= this->FN_data.V()){
		std::string msg = "vertex " + std::to_string(vertex) + " is not between 0 and " + std::to_string(this->FN_data.V() -1) ;

		throw std::invalid_argument(msg);
	}
}

double FordFulkerson::value(){
	return this->max_flow_value;
}

bool FordFulkerson::inCut(int vertex){
	this->validate(vertex);
	return this->marked[vertex];
}






