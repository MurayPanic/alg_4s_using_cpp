#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <type_traits>
#include "Point.hpp"
#ifndef CUSTOM_SORT_HPP
#define CUSTOM_SORT_HPP



template<typename Iterator, typename T>
void selection_sort(Iterator, Iterator, bool (*cmp_func)(T,T) );

template<typename Iterator>
void selection_sort(Iterator, Iterator);

template<typename Iterator>
void insertion_sort(Iterator, Iterator);

template<typename Iterator, typename T>
void insertion_sort(Iterator, Iterator, bool(*cmp_func)(T,T) );


template<typename Iterator>
void h_sort(Iterator, Iterator, int);

template<typename Iterator, typename T>
void h_sort(Iterator, Iterator, bool (*cmp_func)(T, T), int h);

template<typename Iterator>
void shell_sort(Iterator, Iterator);

template<typename Iterator, typename T>
void shell_sort(Iterator, Iterator, bool (*cmp_func)(T, T));

template<typename Iterator, typename T>
void merge(Iterator, Iterator, Iterator);

template<typename Iterator, typename T>
void merge(Iterator, Iterator, Iterator, bool (*cmp_func)(T,T) );

template<typename Iterator>
void merge_sort_recur_ver(Iterator, Iterator);

template<typename Iterator, typename T>
void merge_sort_recur_ver(Iterator, Iterator, bool (*cmp_func)(T,T));

template<typename Iterator>
void merge_sort_bu_ver(Iterator, Iterator);

template<typename Iterator, typename T>
void merge_sort_bu_ver(Iterator, Iterator, bool (*cmp_func)(T,T) );

template<typename Iterator>
void quick_sort(Iterator, Iterator);

template<typename Iterator, typename T>
void quick_sort(Iterator, Iterator, bool (*cmp_func)(T,T) );

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


template<typename Iterator >
void insertion_sort(Iterator head_iter, Iterator tail_iter){

	for(auto iter = head_iter; iter!=tail_iter; ++iter){
		auto cur_iter =iter;
		while(cur_iter!=head_iter && *cur_iter < *(cur_iter-1)   ){
			std::swap(*cur_iter, *(cur_iter-1));
			--cur_iter;
		}
	}
};

template<typename Iterator, 
	 typename T = typename std::iterator_traits<Iterator>::value_type
	 >
void insertion_sort(Iterator head_iter,
	       	    Iterator tail_iter,
		    bool(*cmp_func)(T T_ins_1,T T_ins_2) ){
	for(auto iter = head_iter; iter!= tail_iter; ++iter){
		auto cur_iter = iter;
		while(cur_iter!=head_iter && cmp_func(*cur_iter, *(cur_iter-1))){
		std::swap(*cur_iter, *(cur_iter-1));
		--cur_iter;	
		}
	}

};







template<typename Iterator>
void h_sort(Iterator head_iter, Iterator tail_iter, int h){
	
	for(auto iter = head_iter; tail_iter-iter>=h;iter+=h ){
		auto cur_iter = iter;
		while( cur_iter - head_iter>=h && *cur_iter < *(cur_iter-h) ){
			std::swap(*cur_iter, *(cur_iter-h));
			cur_iter-=h;
		}
	}
}

template<typename Iterator,
	 typename T = typename std::iterator_traits<Iterator>::value_type
	 >
void h_sort(Iterator head_iter,
	    Iterator tail_iter,
	    bool (*cmp_func)(T T_ins_1, T T_ins_2),
	    int h){


	for(auto iter = head_iter; tail_iter-iter>=h; iter+=h ){
		auto cur_iter = iter;
		while( cur_iter - head_iter>=h && cmp_func(*cur_iter, *(cur_iter-h)) ){
			std::swap(*cur_iter, *(cur_iter-h));
			cur_iter-=h;
		}
	}
}

template<typename Iterator>
void shell_sort(Iterator head_iter, Iterator tail_iter){
        h_sort(head_iter, tail_iter, 13);
        h_sort(head_iter, tail_iter, 7);
        h_sort(head_iter, tail_iter, 3);
        h_sort(head_iter, tail_iter, 1);
}

template<typename Iterator,
	 typename T = typename std::iterator_traits<Iterator>::value_type 
	 >
void shell_sort(Iterator head_iter, 
		Iterator tail_iter,
		bool (*cmp_func)(T T_ins_1, T T_ins_2)){
	h_sort(head_iter,tail_iter, cmp_func, 13);
	h_sort(head_iter,tail_iter, cmp_func, 7);
	h_sort(head_iter,tail_iter, cmp_func, 3);
	h_sort(head_iter,tail_iter, cmp_func, 1);
}

template<typename Iterator, 
         typename T = typename std::iterator_traits<Iterator>::value_type >
void merge (Iterator head_iter, Iterator mid_iter,Iterator tail_iter){
	
	std::vector<T> tmp_vec{};
	
	Iterator iter_left= head_iter;
	Iterator iter_right= mid_iter+1;
	//std::cout<< "head: " << *head_iter <<std::endl;
	//std::cout<< "mid: " << *mid_iter << std::endl;
	//std::cout<< "tail: " << *tail_iter <<std::endl;

	while(true){
		if(*iter_left < *iter_right ){
			tmp_vec.push_back(*iter_left);
			if(iter_left!=mid_iter){++iter_left;}
			else{
				
				while(iter_right!=tail_iter){
					tmp_vec.push_back(*iter_right);
					++iter_right;
				}
				tmp_vec.push_back(*iter_right);

				break;}
		}else{
			tmp_vec.push_back(*iter_right);
			if(iter_right!=tail_iter){++iter_right;}
			else{
				
				while(iter_left!=mid_iter){
					tmp_vec.push_back(*iter_left);
					++iter_left;
					}
				tmp_vec.push_back(*iter_left);
				
				break;}
		}
	}

	//push the value back to the original place;
	int i=0;
	for(auto iter= head_iter; iter!=tail_iter; ++iter){
		*iter= tmp_vec[i];
		++i;
	}
	*tail_iter= tmp_vec[i];

	
}



template<typename Iterator >
void merge_sort_recur_ver(Iterator head_iter, Iterator tail_iter){

   	int len = (tail_iter- head_iter);
	if(!len) {return;}
        Iterator mid_iter= head_iter + len/2;
	
	merge_sort_recur_ver(head_iter, mid_iter);
        merge_sort_recur_ver(mid_iter+1, tail_iter);
	merge(head_iter, mid_iter, tail_iter);	
}



template<typename Iterator, 
         typename T = typename std::iterator_traits<Iterator>::value_type >
void merge (Iterator head_iter, Iterator mid_iter,Iterator tail_iter,
	    bool (*cmp_func)(T T_ins_1, T T_ins_2)){

	//Noted: The enter mid iter is the last element of the first 
	//sub array
	
	std::vector<Iterator> tmp_vec{};
	
	Iterator iter_left= head_iter;
	Iterator iter_right= mid_iter+1;

	while(true){
		if(cmp_func(*iter_left, *iter_right) ){
			tmp_vec.push_back(iter_left);
			if(iter_left!=mid_iter){++iter_left;}
			else{
				
				while(iter_right!=tail_iter){
					tmp_vec.push_back(iter_right);
					++iter_right;
				}
				tmp_vec.push_back(iter_right);

				break;}
		}else{
			tmp_vec.push_back(iter_right);
			if(iter_right!=tail_iter){++iter_right;}
			else{
				
				while(iter_left!=mid_iter){
					tmp_vec.push_back(iter_left);
					++iter_left;
					}
				tmp_vec.push_back(iter_left);
				
				break;}
		}
	}

	//push the value back to the original place;
	std::vector<std::remove_cvref_t<T> > result_arr_ptr{};
        for (auto item :tmp_vec){
		std::remove_cvref_t<T> tmp_pair= *item;
		result_arr_ptr.push_back(tmp_pair);
	} 



	int i{0};
	for(auto iter= head_iter; iter!=tail_iter; ++iter){
		*iter= (result_arr_ptr[i]);
		++i;
	}
	
	*tail_iter= (result_arr_ptr[i]);
	
}


template<typename Iterator,
	typename T= typename std::iterator_traits<Iterator>::value_type
	>
void merge_sort_recur_ver(Iterator head_iter, Iterator tail_iter,
		          bool (*cmp_func)(T T_ins_1, T T_ins_2 ) ){

   	int len = (tail_iter- head_iter);
	if(!len) {return;}
        Iterator mid_iter= head_iter + len/2;
	
	merge_sort_recur_ver(head_iter, mid_iter, cmp_func);
        merge_sort_recur_ver(mid_iter+1, tail_iter, cmp_func);
	merge(head_iter, mid_iter, tail_iter, cmp_func);	
}


template<typename Iterator>
void merge_sort_bu_ver(Iterator head_iter, Iterator tail_iter)	{
	int len= tail_iter - head_iter;
	for (auto iter=head_iter; iter!= tail_iter; ++iter){
		merge(iter, iter, iter+1);
		if(iter+1 != tail_iter){++iter;} //Detail point: Never move the
						//iterator out of range
	}

	 
        //Output for debugging
	/*
	std::cout<<"Now print the initial result:";
	int k=1;
        for(auto iter = head_iter; iter!= tail_iter; ++iter){
			std::cout<<*iter<<",";
			if(k%2==0){std::cout<<"|";}
			++k;
		}	       
	std::cout << *tail_iter;
	std::cout << std::endl;
        */
	
	
	for(int i=2; i<len; i*=2){
		
		//Output for debugging
		/*
	        std::cout<< "Now merge sub arrays that has length: "
			<< i 
			<< std::endl;	
		*/

		auto lo_iter = head_iter;
		Iterator mid_iter;
		Iterator hi_iter;
		while(tail_iter - lo_iter>=i){
			//detail point: because our merge function, 
			//the mid_iter requires the last element of 
			//the first subarray
			mid_iter = lo_iter+i-1;

			//Be careful when you assign the hi_iter
			//Reason same as above
			if(tail_iter-mid_iter>=i){
			 	hi_iter  = mid_iter+i; 
			}else{
			 	hi_iter = tail_iter;
			}


			merge(lo_iter, mid_iter, hi_iter );

			//Be careful when you assign the new lo_iter
			//Reason same as above
			if(hi_iter!=tail_iter){
				lo_iter = hi_iter+1;}
			else{
				break;
			}
		}

		
              
	      //Output for debugging	
	      /*
	      std::cout<<"Now print the merge result:";
	       int j=1;
                for(auto iter = head_iter; iter!= tail_iter; ++iter){
			std::cout<<*iter<<",";
			if(j%(i*2)==0){std::cout<<"|";}
			++j;
		}	       
	       std::cout << *tail_iter;
	       std::cout << std::endl;
	       */
	}
        
		

	
}


template<typename Iterator, typename T>
void merge_sort_bu_ver(Iterator head_iter, Iterator tail_iter, 
		bool (*cmp_func)(T T_ins_1, T T_ins_2) ){
	//Combine the subarray of lenth 1
	for(auto iter = head_iter; iter!=tail_iter; ++iter){
		merge(iter, iter, iter+1, cmp_func);
		if(iter+1!= tail_iter){++iter;}
	}

	//Combine the subarray of length 2,4,8...
	int len = tail_iter - head_iter;
        
	//detail point: i should be less or equal to len!!!
	for(int i=2; i<=len; i*=2){
		auto lo_iter = head_iter;
		Iterator mid_iter;
		Iterator hi_iter;

		while(tail_iter - lo_iter>=i){
			mid_iter= lo_iter+i-1;

			if(tail_iter- mid_iter>i){
			    hi_iter = mid_iter +i;	
			}else{
			    hi_iter=tail_iter;
			}
		 
			merge(lo_iter, mid_iter, hi_iter, cmp_func);

			if(hi_iter!= tail_iter){
				lo_iter = hi_iter +1;
			}else{
				break;
			}
		}

  
         	/*
	      std::cout<<"Now print the merge result:";
	       int j=1;
                for(auto iter = head_iter; iter!= tail_iter; ++iter){
			std::cout<<iter->first.toString() 
				  <<":"<<iter->second<<", ";
			if(j%(i*2)==0){std::cout<<"|";}
			++j;
		}	       
	       std::cout << tail_iter->first.toString()
		         <<":"<<tail_iter->second;
	       std::cout << std::endl;
		*/
	}


};


template<typename Iterator>
void quick_sort(Iterator head_iter, Iterator tail_iter){
	if(head_iter==tail_iter){return;}
	auto pivtol = head_iter;
	auto lo_iter= head_iter+1;
	auto hi_iter= tail_iter;

	while(lo_iter<hi_iter){
		while((*lo_iter) <= (*pivtol) && lo_iter!=tail_iter){
			++lo_iter;}
		while(*hi_iter > *pivtol && hi_iter != head_iter+1){
			-- hi_iter;
		}
		if(lo_iter < hi_iter){
		     std::swap(*lo_iter, *hi_iter);
		     if(lo_iter!= tail_iter){++lo_iter;}
		     if(hi_iter!= head_iter+1){--hi_iter;}
		}	
	}
	
	
	if(*hi_iter< *pivtol){
			std::swap(*pivtol, *hi_iter);
		}
	

        /*Output for debugging
        std::cout<<"Current result: ";
	for (auto iter = head_iter; iter!= tail_iter; ++iter){
		std::cout<<*iter<<",";
	}
	std::cout<<*tail_iter<<std::endl;
        */
	if(hi_iter!=head_iter){ quick_sort(pivtol, hi_iter-1); }
	if(hi_iter!=tail_iter){quick_sort(hi_iter+1, tail_iter); }
}

template<typename Iterator, 
	typename T = typename std::iterator_traits<Iterator>::value_type>
void quick_sort(Iterator head_iter, 
		Iterator tail_iter, 
		bool (*cmp_func)(T T_ins_1, T T_ins_2) ){
	
	if(head_iter==tail_iter){return;}

	auto pivtol = head_iter;
	Iterator lo_iter = head_iter+1;
	Iterator hi_iter = tail_iter;
       
       	/*
	std::cout <<"current pivtol: "<< pivtol->second << std::endl;
        std::cout<<"Before sort: ";
	
	for (auto iter = head_iter; iter!= tail_iter; ++iter){
		std::cout<<iter->second <<",";
	}
	std::cout<<tail_iter->second  <<std::endl;
	*/

	while(true){

		while(cmp_func(*lo_iter,*pivtol) && lo_iter != tail_iter){
		    	++lo_iter;
		}

		while(!cmp_func(*hi_iter,*pivtol) &&   hi_iter != head_iter+1){
			--hi_iter;
		}

		if(lo_iter<hi_iter){
			std::swap(*lo_iter, *hi_iter);
			if(lo_iter!=tail_iter){++lo_iter;}
			if(hi_iter!= head_iter+1){--hi_iter;}
		}else{break;}
	}

	if( cmp_func(*hi_iter, *pivtol) ){
		std::swap(*pivtol, *hi_iter);
	}

	/*
        std::cout<<"Current result: ";
	for (auto iter = head_iter; iter!= tail_iter; ++iter){
		std::cout<<iter->second <<",";
	}
	std::cout<<tail_iter->second  <<std::endl;
	*/
	if(hi_iter!= head_iter){  quick_sort(head_iter, hi_iter-1, cmp_func);  }
	if(hi_iter!= tail_iter){  quick_sort(hi_iter, tail_iter, cmp_func);}
	

};
