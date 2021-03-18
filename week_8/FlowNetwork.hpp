#include<iostream>
#include<vector>
#include <random>
#include <string>
#include "FlowEdge.hpp"

#pragma once

#ifndef FLOWNETWORK_HPP
#define FLOWNETWORK_HPP

//Class declaration
class FlowNetwork;

#endif


//Class Definition

class FlowNetwork{

	public:
		FlowNetwork();
		FlowNetwork(int);
		FlowNetwork(int, int);
		~FlowNetwork();
		int V() const;
		int E() const;
		std::vector<FlowEdge> adj(int) const;
		std::vector<FlowEdge> edges() const;
		void addEdge(FlowEdge);
		std::string toString();
		
		
	private:
		int num_of_v;
		int num_of_e;
		std::vector< std::vector<FlowEdge> > adj_list;
		void validateVertex(int) const;
		

};

//Constructor and Deconstructor

FlowNetwork::FlowNetwork(){}



FlowNetwork::FlowNetwork(int V){
	if (V<0){
		throw std::invalid_argument("Number of vertices in a Graph must be non-negative");
	}
	
	this->num_of_v = V;
	this->num_of_e = 0;

	for(int i =0; i<num_of_v; ++i){
		std::vector<FlowEdge> tmp_list;
		this->adj_list.push_back(tmp_list);
	}


}

FlowNetwork::FlowNetwork(int V, int E){
	if (V<0 || E<0){
		throw std::invalid_argument("Number of vertices in a Graph must be non-negative");
	}
	
	this->num_of_v = V;
	this->num_of_e = 0;

	//Generate random edge
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, this->num_of_v-1);
	std::uniform_real_distribution<double> rand_capacity(0.0, 100.0);
	for(int i =0; i<this->num_of_v; ++i){
		std::vector<FlowEdge> tmp_list;
		this->adj_list.push_back(tmp_list);
	}

	for(int i{0}; i< E; ++i){
		
		int head = distrib(gen);
		int tail = distrib(gen);
		int capacity = rand_capacity(gen);
		FlowEdge tmp_edge(head, tail, capacity);
		this->addEdge(tmp_edge);
		
	}

}


FlowNetwork::~FlowNetwork(){}

//Memberfunction

int FlowNetwork::V() const {
	return this->num_of_v;

}

int FlowNetwork::E() const{
	return this->num_of_e;
}

void FlowNetwork::validateVertex(int vertex) const{
	if ( (vertex<0)  || ( vertex>= (this->num_of_v) ) ) {
		std::string msg = "vertex " + std::to_string(vertex) + " is not between 0 and " + std::to_string(this->num_of_v -1) ;

		throw std::invalid_argument(msg);
	
	}

}

std::vector<FlowEdge> FlowNetwork::adj(int vertex) const{
	this->validateVertex(vertex);

	return this->adj_list[vertex];
}

std::vector<FlowEdge> FlowNetwork::edges() const {

	std::vector<FlowEdge> edge_list{};
	
	for(int vertex{0}; vertex<this->V(); ++vertex){
		std::vector<FlowEdge> v_adj_list= this->adj(vertex);
		for(FlowEdge edge : v_adj_list){
			//exclude self loop
			if(edge.to()!=vertex){
				edge_list.push_back(edge);
			}
		}
	}
	return edge_list;
}

void FlowNetwork::addEdge(FlowEdge FE_ins){
	int head = FE_ins.from();
	int tail = FE_ins.to();
	this->validateVertex(head);
	this->validateVertex(tail);
	this->adj_list[head].push_back(FE_ins);
	this->adj_list[tail].push_back(FE_ins);
        ++this->num_of_e;

} 

std::string FlowNetwork::toString(){
	std::string result{};
	result= std::to_string(this->num_of_v) +" " +std::to_string(this->num_of_e) +"\n";
	for(int i=0; i< this->num_of_v; ++i){
		result+= (std::to_string(i)+ ": ");
		for(FlowEdge FE_item : this->adj_list[i] ){
			if(FE_item.from()==i){
				result += (FE_item.toString() +" ");
			}
		}
		result += "\n";
	
	}
	return result;


}
