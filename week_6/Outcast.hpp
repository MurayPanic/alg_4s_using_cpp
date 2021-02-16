#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <numeric>
#include <algorithm>

#include "WordNet.hpp"

# pragma once
#ifndef OUTCAST_HPP

//Class declaration
class Outcast;

#endif

//Class definition

class Outcast{
	public:
		Outcast();
		Outcast(WordNet);
		~Outcast();
		std::string outcast(std::vector<std::string>);
	private:
		WordNet WN_data;

};

//Constructor and Deconstructor
Outcast::Outcast(){}

Outcast::Outcast(WordNet WN_ins): WN_data(WN_ins){}

Outcast::~Outcast(){}


//Member Functions

std::string Outcast::outcast(std::vector<std::string> nouns){
	int dim = nouns.size();
	std::vector<int> row(dim, 0);
	std::vector<std::vector<int> > dist_table(dim, row);
	for(int row{0}; row<dim; ++row){
		for(int col{0}; col<dim; ++col){
			if(row==col){continue;}
			if(dist_table.at(col).at(row)!=0 ){ 
				dist_table.at(row).at(col) = dist_table.at(col).at(row);
			}else{
				dist_table.at(row).at(col) = WN_data.distance(nouns.at(row), nouns.at(col));
			}

		}		
	}
	std::vector<int> dist_of_nouns;

	for(auto& row : dist_table){
		int total_dist = std::accumulate(row.cbegin(), row.cend(),0);
		dist_of_nouns.push_back(total_dist);
	}

	auto max_iter = std::max_element(dist_of_nouns.begin(), dist_of_nouns.end());
	int pos = max_iter - dist_of_nouns.begin();

	std::string result= nouns.at(pos);
	return result;

	

}
