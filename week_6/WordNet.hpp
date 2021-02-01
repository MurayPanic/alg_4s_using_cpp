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
		std::unordered_map<int, std::string> synset_map;
		std::unordered_set<std::string> noun_set;
		Digraph graph_data;



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

		if(synsets_file.peek()==EOF){break;}
		
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
		std::pair<int, std::string> num_noun_pair = std::make_pair(num, noun_str);
		this->noun_set.insert(noun_str);
		this->synset_map.insert(num_noun_pair);
	}
	synsets_file.close();


	std::ifstream hypernyms_file;
	hypernyms_file.open(hypernyms_path);
	if(hypernyms_file.fail()){
		throw std::invalid_argument("The provided hypernyms file name is not valid");
	}
	
	int noun_num = this->synset_map.size();
	Digraph tmp_graph(noun_num);
	this->graph_data = tmp_graph;

	
	
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
			this->graph_data.addEdge(num_vec[0], num_vec[i]);
		}
	}	


	
}

std::unordered_set<std::string >WordNet::nouns(){
	
	return this->noun_set;
}


bool WordNet::isNoun(std::string word){

	return this->noun_set.contains(word);
}
