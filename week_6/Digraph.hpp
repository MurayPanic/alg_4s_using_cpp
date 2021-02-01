#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include <ranges>

#pragma once
#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP


//Class declaration
class Digraph;

#endif

class Digraph {
	public:
		Digraph();
		Digraph(int);
		Digraph(std::ifstream&);
		~Digraph();
		void operator=(Digraph&);
		int V();
		int E();
		std::vector<int> adj(int);
		int indegree(int);
		int outdegree(int);
		Digraph reverse();
		void addEdge(int, int);
		std::string toString();

	private:
		int V_num;
		int E_num;
		std::vector< std::vector<int> > adj_list;
		std::vector<int> indegree_list;

		void validateVertex(int);

};

//Constructor and destructor
Digraph::Digraph(){};
Digraph::~Digraph(){};

Digraph::Digraph(int v): E_num(0){
	if(v<0 ){ 
		throw std::invalid_argument("The number of vertices is not positive integer");
	}
	this->V_num  = v;
	for(int vex{0}; vex<this->V_num; ++vex){
		std::vector<int> adj_list_of_vex{};
		this->adj_list.push_back(adj_list_of_vex);
		this->indegree_list.push_back(0);
	}



}

Digraph::Digraph(std::ifstream& input_data_flow):E_num(0){
	if(!input_data_flow){
		throw std::invalid_argument("argument is null");
	}

	std::string vertex_num_str;
	input_data_flow >> vertex_num_str;
	int vertex_num = std::stoi(vertex_num_str);
	if(vertex_num<0){
		throw std::invalid_argument("number of vertices in a Digraph must be non-negative")	;
	}

	std::string edge_num_str;
	input_data_flow >> edge_num_str;
	int edge_num = std::stoi(edge_num_str);
	if(edge_num<0){
		throw std::invalid_argument("number of edges in a Digraph must be non-negative")	;
	}

	this->V_num = vertex_num;
	//this->E = edge_num;

	for(int vex{0}; vex<this->V_num; ++vex){
		std::vector<int> adj_list_of_vex{};
		this->adj_list.push_back(adj_list_of_vex);
		this->indegree_list.push_back(0);
	}

	// The edge v->w. v is the tail, w is the head.
	while(!input_data_flow.eof()){
		std::string temp_tail_str;
		std::string temp_head_str;
		input_data_flow >> temp_tail_str;
		input_data_flow >> temp_head_str;
		if(input_data_flow.peek()==EOF){break;}


		int temp_tail = std::stoi(temp_tail_str);
		int temp_head = std::stoi(temp_head_str);
		
		this->addEdge(temp_tail, temp_head);	
		

	}

}

void Digraph::validateVertex(int v){
	if (v<0|| v>=this->V_num){
		std::string msg = "vertex " + std::to_string(v) + " is not between 0 and " + std::to_string(this->V_num -1);
		throw std::invalid_argument(msg);
	}
}

void Digraph::addEdge(int tail_v, int head_w){
	this->validateVertex(tail_v);
	this->validateVertex(head_w);
	this->adj_list[tail_v].push_back(head_w);
	++(this->indegree_list[head_w]);
	++ (this->E_num);
}

int Digraph::V(){
	return this->V_num;
}

int Digraph::E(){
	return this->E_num;
}

std::vector<int> Digraph::adj(int vex){
	this->validateVertex(vex);
	return adj_list[vex];
}

int Digraph::indegree(int vex){
	this->validateVertex(vex);
	return indegree_list[vex];
}

int Digraph::outdegree(int vex){
	this->validateVertex(vex);
	return adj_list[vex].size();
}

void Digraph::operator= (Digraph& D_ins){
	this->V_num = D_ins.V();
	this->E_num = D_ins.E();

	if(this->V_num<0){
		throw std::invalid_argument("Number of vertices in a Digraph must be non-negative");
	}
	
	this->adj_list.clear();
	this->indegree_list.clear();

	for (int v{0}; v< this->V_num; ++v){
		this->adj_list.push_back(D_ins.adj(v));
		this->indegree_list.push_back(D_ins.indegree(v));
	}

}

Digraph Digraph::reverse(){
	Digraph reverse_D_ins(this->V_num);
	for(int v{0}; v< this->V_num; ++v){
		for(auto w : this->adj_list[v]){
			if(w)
			reverse_D_ins.addEdge(w,v);
		}		
	
	}

	return reverse_D_ins;

}

std::string Digraph::toString(){
	std::string result;
	result = std::to_string(this->V_num) + " vertices, " + std::to_string(this->E_num) + " edges \n";

	//auto convert_int_to_str = [](int v ){return std::to_string(v);};	
	//Clang++ currently not completely support range library
	//Give up on using range
	for(int v{0}; v<this->V_num;++v){
		std::string adj_list_str=std::to_string(v)+": ";

		for(auto item : this->adj_list[v])
		{
			std::string tmp_str = std::to_string(item);
			adj_list_str+= tmp_str;
			adj_list_str+=" ";		
		}
		adj_list_str+="\n";
		result+= adj_list_str;
		
	}

	return result;
	
}
