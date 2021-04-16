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
		CircularSuffixArray(std::string);
		~CircularSuffixArray();
	
		int length();
		int index(int);
	
	private:
		class SuffixArray{
			public:
				SuffixArray(CircularSuffixArray&, int);
				bool operator<(const SuffixArray&);
				int value;
			private:
				CircularSuffixArray* parent_ptr;
		};
		std::vector<SuffixArray> suffix_list;
		std::vector<int> index_array;
		std::string* origin_str;
		void get_sorted_suffix_list();



};


//constructor and deconstructor

CircularSuffixArray::CircularSuffixArray(){}

CircularSuffixArray::CircularSuffixArray(std::string input_str){
	for(int i{0}; i<input_str.size(); ++i){
		SuffixArray SA_ins(*this,i);
		this->suffix_list.push_back(SA_ins);
	}
	this->origin_str = &input_str;
	std::sort(this->suffix_list.begin(), this->suffix_list.end());
	this->get_sorted_suffix_list();

}

CircularSuffixArray::~CircularSuffixArray(){}

CircularSuffixArray::SuffixArray::SuffixArray(CircularSuffixArray& parent_class_ptr,int index): value(index), parent_ptr(&parent_class_ptr){

}

//member function

bool CircularSuffixArray::SuffixArray::operator<(const SuffixArray& SA_ins_that){
	int len = this->parent_ptr->origin_str->size();
	/*std::vector<int> this_SA_index_list;
	for(int i=this->value; i<len; ++i){
		this_SA_index_list.push_back(i);
	}
	for(int i{0}; i<this->value; ++i){
	
		this_SA_index_list.push_back(i);
	}

	std::vector<int> that_SA_index_list(len);
	for(int j=SA_ins_that.value; j<len; ++j){
		that_SA_index_list.push_back(j);
	}
	for(int j{0}; j<SA_ins_that.value; ++j){
	
		that_SA_index_list.push_back(j);
	}

*/

	int i = this->value;
	int j= SA_ins_that.value;

	for(int k{0}; k<len; ++k){
		if(this->parent_ptr->origin_str->at(i) != this->parent_ptr->origin_str->at(j) ){
		
		return this->parent_ptr->origin_str->at(i) <this->parent_ptr->origin_str->at(j) ;
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

int CircularSuffixArray::index(int i){

	return this->index_array.at(i);
}

