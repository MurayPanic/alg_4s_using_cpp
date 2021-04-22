#include <iostream>
#include <ios>
#include <filesystem>
#include <fstream>
#include <string>
#include <exception>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <bitset>

#include "CircularSuffixArray.hpp"


//class declaration
class BurrowsWheeler;


//class definition
class BurrowsWheeler{
	public:
		BurrowsWheeler();
		~BurrowsWheeler();
		void transform();
		void inverseTransform();
		void main(std::string, std::string);
	private:
		std::string  data;
		CircularSuffixArray CSA_ins;

};

//constructor and deconstructor
BurrowsWheeler::BurrowsWheeler(){}

BurrowsWheeler::~BurrowsWheeler(){}

//Member function
void BurrowsWheeler::transform(){
	//std::cout<<"Transform is called" <<std::endl;

	//Find the first
	
	for(int i{0}; i<this->CSA_ins.length(); ++i){
		int index_val = this->CSA_ins.index(i);
		if(index_val==0){
			std::bitset<32> bin_i(i);
			std::cout<<bin_i;
			break;
		}
		
	}


	//The index return value-1 equals the original index of the last letter
	for(int i{0}; i<this->CSA_ins.length(); ++i){
		int original_row = this->CSA_ins.index(i);
		int original_index = original_row==0 ? CSA_ins.length()-1 : original_row-1;
		int int_char = this->data.at(original_index);
		std::bitset<8> bin_val(int_char );
		std::cout<< bin_val;
	}
	
}

void BurrowsWheeler::inverseTransform(){

	//Get the first from the data string
	std::string first_str= this->data.substr(0,32);
	std::bitset<32> first_bin(first_str);
	int first = first_bin.to_ulong();
	
	//last_col: last column of the sorted suffixes array
	auto last_col_bin = this->data;
	last_col_bin.erase(0,32);
	
	//Convert the binary string to ASCII string;
	std::string last_col="";
	std::string tmp="";
	int counter{0};
	for(auto digit: last_col_bin){
		++counter;
		tmp += digit;
		if( counter%8 == 0){
			std::bitset<8> digit_bin(tmp);
		       	int digit_int = digit_bin.to_ulong();
			char character = digit_int;
			last_col+= ( character );
			tmp.clear();
		}
	}

	//std::cout<< "Last col:"<<last_col<<std::endl;	

	//Deduct the first column of the suffix array
	//first_col: first column of the sorted suffixes array
	std::string first_col = last_col;
	std::sort(first_col.begin(), first_col.end());

	/*
	for(auto character : first_col_of_sorted_suffixes){
		std::cout<<character;
	}
	std::cout<<std::endl;
	*/


	//Deduct the next[] array
	std::vector<int> next(first_col.size(), -1);
	std::vector<int>  freq(257,0); // extra one space is needed for frequency counting
	
	//Generate frequency table of the first column
	//It is equivalent to record the first position of a series of consequent characters
	for(int i{0}; i<first_col.size();++i){
		
		unsigned char first_character = first_col.at(i);
		int pos = first_character;
		//increase the end position:
		++(freq.at(pos+1) );
	}

	std::cout<<"I am here"<<std::endl;
	//Accoumulate the frequency table
	for(int i{1};i<freq.size();++i){
		freq.at(i) += freq.at(i-1);
	
	}

	
	for(int i{0}; i<last_col.size(); ++i){
		unsigned char last_character = last_col.at(i);
		int pos = last_character;
		next.at( freq.at(pos) ) = i;
		//increase the start position:
		++freq.at(pos);
	
	}

	/*
	std::cout<< "The next is: " << std::endl;
	for (auto item : next){
		std::cout<<item<<std::endl;
	}
	*/

	//Recover the message
	auto index =first;
	for(int i{0}; i< first_col.size();++i){
		std::cout<< first_col[index];
		index = next[index];
	
	}

	

}

void BurrowsWheeler::main(std::string file_str, std::string args){
	this->data = file_str;
	
	if(args=="-"){
		CircularSuffixArray CSA_tmp(file_str);
		this->CSA_ins = CSA_tmp;
		this->transform();
	}else if(args=="+"){
		this->inverseTransform();
	}else{
		throw std::invalid_argument("Invalid arguments");
	}

}

int main(int argc, char* argv[]){
	/*	
	if(argc==1){	
		throw std::invalid_argument("Invalid arguments");
	}
	
	std::string indicator = argv[1];
	std::string filename = argv[2];
	
	std::string path_str = std::filesystem::current_path();
	path_str += filename;
	std::filesystem::path complete_path(path_str);
	std::ifstream input_file;
	input_file.open(complete_path, std::ios::in | std::ios::binary);
	if(input_file.fail()){
		throw std::invalid_argument("the provide data file open failed");
	}

	BurrowsWheeler BW_ins{};
	

	
	std::string file_str="";
	while(!input_file.eof()){
		char tmp;
		input_file.read(&tmp, sizeof(tmp));
		if(input_file.fail()){break;}
		file_str+= tmp;

	}	
	//file_str.pop_back();
	*/

	std::string indicator = argv[1];
	std::string file_str="";
	std::string tmp="";
	while(std::cin.peek() != EOF){
		tmp = std::cin.get();
		file_str+=tmp;
	}

	//file_str.pop_back();
	BurrowsWheeler BW_ins{};
	BW_ins.main(file_str, indicator);
}

