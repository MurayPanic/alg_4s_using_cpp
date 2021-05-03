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
		void main(std::string&, std::string);
	private:
		std::string  data;
		CircularSuffixArray* CSA_ins_ptr;
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
	
	
	for( unsigned int i{0}; i<this->CSA_ins_ptr->length(); ++i){
	        unsigned int index_val = this->CSA_ins_ptr->index(i);
		if(index_val==0){
		

			this->digit.integer=i;
			std::cout<<this->digit.char_byte[3]
			         <<this->digit.char_byte[2]
					<<this->digit.char_byte[1]
					<<this->digit.char_byte[0];
			
			break;
		}
		
	}


	//The index return value-1 equals the original index of the last letter
	for(int i{0}; i<this->CSA_ins_ptr->length(); ++i){
		int original_row = this->CSA_ins_ptr->index(i);
		int original_index = original_row==0 ? CSA_ins_ptr->length()-1 : original_row-1;
		std::cout<< this->data.at(original_index);
	
		
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
	std::vector<unsigned char>  last_col( this->data.begin()+4, this->data.end() );
	
	
	

	//Deduct the first column of the suffix array
	//first_col: first column of the sorted suffixes array
	//	      must use unsigned char array, can not use string directly
	//	      Because string is a char array. The data conversion may 
	//	      may the program unapplicable to non text data.
	std::vector<unsigned char> first_col(last_col.begin(), last_col.end() );
	std::sort(first_col.begin(), first_col.end());

	


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

	

	//Recover the message
	unsigned int index =first;
	for(int i{0}; i< first_col.size();++i){
		
		std::cout << (unsigned char) first_col.at(index);
		index = next.at(index);
	
	}

	

}

void BurrowsWheeler::main(std::string& file_str, std::string args){
	this->data = file_str;
	
	if(args=="-"){
		CircularSuffixArray CSA_tmp(file_str);
		this->CSA_ins_ptr = &CSA_tmp;
		this->transform();
	}else if(args=="+"){
		this->inverseTransform();
	}else{
		throw std::invalid_argument("Invalid arguments");
	}

}

int main(int argc, char* argv[]){
	

	std::string indicator = argv[1];
	std::string file_str="";
	while(std::cin.peek() != EOF){
		file_str += std::cin.get();
		
	}


	BurrowsWheeler BW_ins{};
	BW_ins.main(file_str, indicator);
}

