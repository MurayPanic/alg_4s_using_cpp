#include<iostream>
#include<string>
#include<vector>

#include<algorithm>

#ifndef CIRCULARSUFFIXARRAY_HPP
#define CIRCULARSUFFIXARRAY_HPP

//class declaration
class CircularSuffixArray;

#endif

//class definition

class CircularSuffixArray{
	public:
		CircularSuffixArray();
		CircularSuffixArray(std::string&);
		~CircularSuffixArray();
	
		int length();
		unsigned int index(unsigned int);
	
	private:
		class SuffixArray{
			public:
				SuffixArray(CircularSuffixArray&, unsigned int);
				bool operator<(const SuffixArray&);
				unsigned int value;
			private:
				CircularSuffixArray* parent_ptr;
		};
		std::vector<SuffixArray> suffix_list;
		std::vector<unsigned int> index_array;
		std::string* origin_str;
		void get_sorted_suffix_list();



};


//constructor and deconstructor

CircularSuffixArray::CircularSuffixArray(){}

CircularSuffixArray::CircularSuffixArray(std::string& input_str){
	for(unsigned int i{0}; i<input_str.size(); ++i){
		SuffixArray SA_ins(*this,i);
		this->suffix_list.push_back(SA_ins);
	}
	this->origin_str = &input_str;
	std::sort(this->suffix_list.begin(), this->suffix_list.end());
	this->get_sorted_suffix_list();

}

CircularSuffixArray::~CircularSuffixArray(){}

CircularSuffixArray::SuffixArray::SuffixArray(CircularSuffixArray& parent_class_ptr,unsigned int index): value(index), parent_ptr(&parent_class_ptr){

}

//member function

bool CircularSuffixArray::SuffixArray::operator<(const SuffixArray& SA_ins_that){
	int len = this->parent_ptr->origin_str->size();
	

	unsigned int i = this->value;
	unsigned int j = SA_ins_that.value;

	for(int k{0}; k<len; ++k){
		if(this->parent_ptr->origin_str->at(i) != this->parent_ptr->origin_str->at(j) ){
			unsigned char  char_i = this->parent_ptr->origin_str->at(i);
			unsigned char  char_j = this->parent_ptr->origin_str->at(j);

			return char_i < char_j ;
		}

		++i;
		++j;
		if(i==len){i=0;}
		if(j==len){j=0;}

	
	}

	return false;
}

void CircularSuffixArray::get_sorted_suffix_list(){
	for(auto& item : this->suffix_list){
		this->index_array.push_back(item.value  );
	
	}

}

int CircularSuffixArray::length(){

	return this->index_array.size();
}

unsigned int CircularSuffixArray::index(unsigned int i){
	return this->index_array.at(i);
}

