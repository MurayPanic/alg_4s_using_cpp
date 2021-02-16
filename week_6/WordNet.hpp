#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <exception>
#include <ranges>
#include "Digraph.hpp"
#include "SAP.hpp"


#pragma once
#ifndef WORDNET_HPP
#define WORDNET_HPP

//Class declaration
class WordNet;

#endif

//Class definition
class WordNet{
	public:
		WordNet();
		WordNet(std::string, std::string);
		~WordNet();
		std::unordered_set<std::string> nouns();
		bool isNoun(std::string);
		int distance(std::string, std::string);
		std::string sap(std::string, std::string);
	private:
		//A map from node number to noun
		std::unordered_map<int, std::vector<std::string> > synset_map;
		//A map from noun to node number
		std::unordered_map<std::string, std::vector<int> > synset_map_noun_to_num;
		//The set that hold all the nouns
		std::unordered_set<std::string> noun_set;

		SAP sap_ins;



};

//Constructor and deconstructor

WordNet::WordNet(){}

WordNet::~WordNet(){}

WordNet::WordNet(std::string synsets, std::string hypernyms){
	std::string cur_path = std::filesystem::current_path();
	std::string synsets_path_str = cur_path+"/"+synsets;
	std::string hypernyms_path_str = cur_path+"/"+hypernyms;
	std::filesystem::path synsets_path(synsets_path_str);
	std::filesystem::path hypernyms_path(hypernyms_path_str);

	std::ifstream synsets_file;
	synsets_file.open(synsets_path);
	if(synsets_file.fail()){
		throw std::invalid_argument("The provided synsets file name is not valid");
	}


	std::string line;
	while(std::getline(synsets_file, line) ){

		
		int first_comma_pos=line.find(",");
		std::string num_str= line.substr(0, first_comma_pos);

		int second_comma_pos = line.find(",", first_comma_pos+1);
		int noun_len = second_comma_pos- first_comma_pos;
		
		//A little bit triky. Think about how many times the pointer need to move 
		std::string noun_str = line.substr( first_comma_pos+1,noun_len-1);
		
		//Test output
		/*
		std::cout<<"The line is"<<line<<std::endl;
		std::cout<<num_str<<" "<<noun_str<<std::endl;
		*/
		
		int num = std::stoi(num_str);
		
		//split the long string and extract each word
		auto noun_str_range = noun_str | std::ranges::views::split(' ');

		std::vector<std::string> noun_list{};

		for (auto noun_item_range : noun_str_range){
			std::string noun_item{};
			for(auto& character : noun_item_range){
				noun_item += character;
			}

			this->noun_set.insert(noun_item);
			noun_list.push_back(noun_item);

			if(this->synset_map_noun_to_num.contains(noun_item) ){
				this->synset_map_noun_to_num[noun_item].push_back(num);
			}else{
				std::vector<int> tmp_num_list{num};
				std::pair<std::string, std::vector<int> > noun_num_list_pair = std::make_pair(noun_item, tmp_num_list);
	
				this->synset_map_noun_to_num.insert(noun_num_list_pair);
			}
		}

		
		std::pair<int, std::vector<std::string> > num_noun_pair = std::make_pair(num, noun_list);

		this->synset_map.insert(num_noun_pair);

		if(synsets_file.peek()==EOF){break;}
	}
	
	synsets_file.close();


	std::ifstream hypernyms_file;
	hypernyms_file.open(hypernyms_path);
	if(hypernyms_file.fail()){
		throw std::invalid_argument("The provided hypernyms file name is not valid");
	}
	
	int noun_num = this->synset_map.size();
	Digraph tmp_graph(noun_num);
	//this->graph_data = tmp_graph;

	
	
	while(std::getline(hypernyms_file, line)){
		
		//std::cout<<"The line is: "<<line<<std::endl;
		auto num_range = line | std::ranges::views::split(',');
		std::vector<int> num_vec{};
		for(auto sub_range : num_range){
			std::string num_str{};
			for(auto& digit: sub_range){
			num_str+=digit;
			}
			int num = std::stoi(num_str);
			num_vec.push_back(num);
		}
		
		for (int i=1; i<num_vec.size(); ++i){
			tmp_graph.addEdge(num_vec[0], num_vec[i]);
		}
	}	


	SAP tmp_sap_ins(tmp_graph);
	this->sap_ins = tmp_sap_ins;

	
}

std::unordered_set<std::string >WordNet::nouns(){
	
	return this->noun_set;
}


bool WordNet::isNoun(std::string word){

	return this->noun_set.contains(word);
}

int WordNet::distance(std::string nounA, std::string nounB){
	auto query_A = this->synset_map_noun_to_num[nounA];
	auto query_B = this->synset_map_noun_to_num[nounB];
	return this->sap_ins.length(query_A, query_B);

}

std::string WordNet::sap(std::string nounA, std::string nounB){

	auto query_A = this->synset_map_noun_to_num[nounA];
	auto query_B = this->synset_map_noun_to_num[nounB];
	int sca = this->sap_ins.ancestor(query_A,query_B);
	std::vector<std::string> synset_str = synset_map[sca];
	std::string result;
	
	for(auto item : synset_str ){
		result += item;
		result += " ";
	}
	result.pop_back();
	return result;
}



