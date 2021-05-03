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
		union {
			unsigned int integer;
			unsigned char char_byte[4];
		}digit;
		

};

//constructor and deconstructor
BurrowsWheeler::BurrowsWheeler(){}

BurrowsWheeler::~BurrowsWheeler(){}

//Member function
void BurrowsWheeler::transform(){
	//std::cout<<"Transform is called" <<std::endl;

	//Find the first
	
	for( unsigned int i{0}; i<this->CSA_ins.length(); ++i){
	        unsigned int index_val = this->CSA_ins.index(i);
		if(index_val==0){
			/*
			std::bitset<32> bin_i(i);
			std::cout<<bin_i;
			*/

			this->digit.integer=i;
			std::cout<<this->digit.char_byte[3]
			         <<this->digit.char_byte[2]
					<<this->digit.char_byte[1]
					<<this->digit.char_byte[0];
			
			

			break;
		}
		
	}


	//The index return value-1 equals the original index of the last letter
	for(int i{0}; i<this->CSA_ins.length(); ++i){
		int original_row = this->CSA_ins.index(i);
		int original_index = original_row==0 ? CSA_ins.length()-1 : original_row-1;
		std::cout<< this->data.at(original_index);
		/*
		int int_char = this->data.at(original_index);
		std::bitset<8> bin_val(int_char );
		std::cout<< bin_val;
		*/
	}
	
}

void BurrowsWheeler::inverseTransform(){

	//Get the first from the data string
	std::string first_str= this->data.substr(0,4);
	digit.char_byte[3]= first_str[0];
	digit.char_byte[2]= first_str[1];
	digit.char_byte[1]= first_str[2];
	digit.char_byte[0]= first_str[3];

	unsigned int first = this->digit.integer;

	
	//last_col: last column of the sorted suffixes array
	auto last_col = this->data;
	last_col.erase(0,4);
	
	/*
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
			unsigned char character = digit_int;
			last_col+= ( character );
			tmp.clear();
		}
	}
	*/
	//std::cout<< "Last col:"<<last_col<<std::endl;	

	//Deduct the first column of the suffix array
	//first_col: first column of the sorted suffixes array
	//	      must use unsigned char array, can not use string directly
	//	      Because string is a char array. The data conversion may 
	//	      may the program unapplicable to non text data.
	std::vector<unsigned char> first_col;
	for(unsigned char item : last_col){
		first_col.push_back(item);
	}
	std::sort(first_col.begin(), first_col.end());

	/*
	for(auto character : first_col_of_sorted_suffixes){
		std::cout<<character;
	}
	std::cout<<std::endl;
	*/


	//Deduct the next[] array
	std::vector<unsigned int> next(first_col.size(), -1);
	std::vector<unsigned int>  freq(257,0); // extra one space is needed for frequency counting
	
	//Generate frequency table of the first column
	//It is equivalent to record the first position of a series of consequent characters
	for(unsigned int i{0}; i<first_col.size();++i){
		
		unsigned char first_character = first_col.at(i);
		unsigned int pos = first_character;
		//increase the end position:
		++(freq.at(pos+1) );
	}

	
	//Accoumulate the frequency table
	for(unsigned int i{1};i<freq.size();++i){
		freq.at(i) += freq.at(i-1);
	
	}

	
	for(unsigned int i{0}; i<last_col.size(); ++i){
		unsigned char last_character = last_col.at(i);
		unsigned int pos = last_character;
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
	unsigned int index =first;
	for(int i{0}; i< first_col.size();++i){
		unsigned char character = first_col.at(index);
		std::cout<< character;
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

