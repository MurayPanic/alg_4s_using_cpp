#include <iostream>
#include <vector>
#include <exception>
#include "Digraph.hpp"

#pragma once
#ifndef SAP_HPP
#define SAP_HPP

//Class declaration
class SAP;

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
		void BFS(std::unordered_set<int> visited_node);



};

//Constructor and deconstructor
SAP::SAP(){
	
		throw std::invalid_argument("The argument is null");
	
}
SAP::~SAP(){}

SAP::SAP(Digraph D_ins){
	this->graph_data=D_ins;


}


int SAP::length(int v, int w){}

int SAP::ancestor(int v,int w){}


