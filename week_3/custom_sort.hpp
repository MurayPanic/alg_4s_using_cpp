#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include "Point.hpp"
#ifndef CUSTOM_SORT_HPP
#define CUSTOM_SORT_HPP



template<typename Iterator, typename T>
void selection_sort(Iterator, Iterator, bool (*cmp_func)(T,T) );

template<typename Iterator>
void selection_sort(Iterator, Iterator);

void merge_sort(std::vector<std::pair<Point, double> >&);
void quick_sort(std::vector<std::pair<Point, double> >&);

#endif

template<typename Iterator,
	 typename T= typename std::iterator_traits<Iterator>::value_type >
void selection_sort( Iterator head_iter, 
		     Iterator tail_iter,
		    bool (*cmp_func) (T T_ins_1, T T_ins_2)){
	for(auto iter= head_iter; iter!=tail_iter;++iter){
		auto tmp_iter= std::min_element(iter, tail_iter, cmp_func);
		std::swap(*iter, *tmp_iter);
	}

};

template<typename Iterator >
void selection_sort(Iterator head_iter, Iterator tail_iter){

     for(auto iter= head_iter; iter!= tail_iter; ++iter){
	     auto tmp_iter= std::min_element(iter, tail_iter);
	     std::swap(*iter, *tmp_iter);
     }
     
};

