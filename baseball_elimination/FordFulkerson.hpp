#include <iostream>
#include <queue>
#include <vector>
#include <limits>
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
	    bool check();
		void validate(int);
		bool isFeasible();
		double excess(int);
		

		

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

	if(input_source == input_target){
		throw std::invalid_argument("Source equals sink");
	}
	if(!this->isFeasible() ){
		throw std::invalid_argument("Initial flow is infeasible");
	}


	
	
	for(int i{0}; i<this->FN_data.V(); ++i){
		this->marked.push_back(false);
		FlowEdge empty_edge;
		this->edgeTo.push_back(empty_edge);
	}

	int counter{0};
	while(this->hasAugmentedPath() ){
		//Finde the bottleneck on the augmented path
		double bottle = std::numeric_limits<double>::max();

		for(int cur_node = this->target; cur_node!= this->source; cur_node = this->edgeTo[cur_node].other(cur_node)){
			
			
				bottle = std::fmin(this->edgeTo[cur_node].residualCapacityTo(cur_node), bottle);
			

		}

		//Reduce the capacity accordingly

		for(int cur_node = this->target; cur_node!= this->source; cur_node = this->edgeTo[cur_node].other(cur_node) ){
			
			
			


			edgeTo[cur_node].addResidualFlowTo(cur_node, bottle);

			
			
		}


		//Update residual graph
		FlowNetwork updated_graph(this->FN_data.V());
		std::vector<FlowEdge> aug_path{};
		for(int index = this->target; index!= this->source; index = this->edgeTo[index].other(index)){
						aug_path.push_back(this->edgeTo[index]);
					}

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
				
				bool same_edge = false;
				for(auto item : aug_path){
					if (edge.to()==item.to()  && edge.from()==item.from() ){
						updated_graph.addEdge(item);
						same_edge =true;
					}
				}
				if(!same_edge){updated_graph.addEdge(edge);}
			}
		}

		this->FN_data = updated_graph;
		this->max_flow_value += bottle;
		

		


	}

	this->check();

}

FordFulkerson::~FordFulkerson(){}

//Member function

bool FordFulkerson::hasAugmentedPath(){
	std::queue<int> helper_queue{};
	this->edgeTo.clear();
	this->marked.clear();

	for(int i{0}; i<this->FN_data.V(); ++i){
		this->marked.push_back(false);
		FlowEdge empty_edge(0,0,0,0);
		this->edgeTo.push_back(empty_edge);
	}


	helper_queue.push(this->source);
	this->marked[this->source]=true;

	while(!helper_queue.empty() && !this->marked[this->target]){
		int cur_node = helper_queue.front();
		helper_queue.pop();

			
		std::vector<FlowEdge> edge_list = this->FN_data.adj(cur_node);
		
		for(FlowEdge FE_item : edge_list ){
			int next_node = FE_item.other(cur_node);


			if(!this->marked[next_node ] && FE_item.residualCapacityTo(next_node )>0.0 ){
				

				this->marked[next_node]=true;
				this->edgeTo[next_node] = FE_item;
				helper_queue.push(next_node );
			}
			
		}

		
	}

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

double FordFulkerson::excess(int v){
	double excess{0.0};
	for (FlowEdge e : this->FN_data.adj(v)){
		if (v == e.from()) {
			excess -= e.flow();
		}else{       
			excess += e.flow();
		}
	}
	return excess;
}

bool FordFulkerson::isFeasible(){
    
	// check that capacity constraints are satisfied
	for(int v{0}; v< this->FN_data.V(); ++v){
		for(FlowEdge e : this->FN_data.adj(v)){
			if(e.flow()< -1E-10 || e.flow() >e.capacity() + 1E-10){
				std::cout<<"Edge does not satisfy capacity constraints: "
						 <<e.toString() <<std::endl;
			    return false;
			}

		}
	}

	/// check that net flow into a vertex equals zero, except at source and sink
    if (std::abs(this->max_flow_value + this->excess(this->source)) > 1E-11) {
            std::cout<<"Excess at source = "<< std::to_string( excess(this->source) ) <<std::endl;
            std::cout<< "Max flow         = " <<this->max_flow_value <<std::endl;
            return false;
        }
	
	if (std::abs(this->max_flow_value - this->excess(this->target)) > 1E-11) {
            std::cout<<"Excess at sink = "<< std::to_string( excess(this->target) ) <<std::endl;
            std::cout<< "Max flow         = " <<this->max_flow_value <<std::endl;
            return false;
        }
	
	 for (int v = 0; v < this->FN_data.V(); v++) {
            if (v == this->source || v == this->target) {continue;}
            else if (std::abs(excess( v)) > 1E-10) {
                std::cout<<"Net flow out of "<< std::to_string(v) << " doesn't equal zero" <<std::endl;
                std:: cout<<"The excess value is: " <<std::to_string(excess(v)) <<std::endl;
				
				return false;
            }
        }


	return true;
	
}

bool FordFulkerson::check(){
	if(!isFeasible()){
		std::cout<<"Flow is infeasible"<<std::endl;
		return false;
	}

	if(!inCut(this->source)){
		std::cout<<"source "<< std::to_string(this->source) 
		<<" is not on source side of min cut" <<std::endl;
		return false;
	}

	if(inCut(this->target)){
		std::cout<<"sink "<< std::to_string(this->target) 
		<<" is on source side of min cut" <<std::endl;
		return false;
	}

	// check that value of min cut = value of max flow
        double mincutValue = 0.0;
        for (int v = 0; v < this->FN_data.V(); v++) {
            for (FlowEdge e : this->FN_data.adj(v)) {
                if ((v == e.from()) && inCut(e.from()) && !inCut(e.to()))
                    mincutValue += e.capacity();
            }
        }

        if (std::abs(mincutValue - this->max_flow_value) > 1E-10) {
            std::cout<< "Max flow value = " << std::to_string(this->max_flow_value)
			<< ", min cut value = " << std::to_string(mincutValue) <<std::endl;
            return false;
        }

        return true; 


}


