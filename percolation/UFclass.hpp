#include<vector>
#include <iostream>
#include<map>


//UFclass declaration

#ifndef UFCLASS_H
#define UFCLASS_H

class UFclass{

	public:
		UFclass();
                UFclass(int N);
		~UFclass();
		std::vector<int> data;
		virtual void union2c(int p, int q);
		virtual bool connected(int p, int q)=0;
		void print_component();

};

class QuickFindUF : public UFclass{

	public:
		QuickFindUF();
		QuickFindUF(int N);
		~QuickFindUF();
		void union2c(int p, int q);
		bool connected(int p, int q);
	

};

class QuickUnionUF : public UFclass{
	
	public:
		QuickUnionUF();
		QuickUnionUF(int N);
		~QuickUnionUF();
		void union2c(int p, int q);
		bool connected(int p, int q);
		int root(int index);
};

class WeightedQuickUnionUF : public QuickUnionUF{
      public:
	  	WeightedQuickUnionUF();
		WeightedQuickUnionUF(int N);
		~WeightedQuickUnionUF();
		std::vector<int> tree_sz;
		void union2c(int p, int q);  
		//bool connected(int p, int q); //Use parents' method directly
		//int root(int index);
};

class WeightedQuickUnionUFwithPC : public WeightedQuickUnionUF {
      public:
	  	WeightedQuickUnionUFwithPC();
		WeightedQuickUnionUFwithPC(int N);
		~WeightedQuickUnionUFwithPC();
		//std::vector<int> tree_sz;
		//void union2c(int p, int q);  
		//bool connected(int p, int q); //Use parents' method directly
		int root(int index);
};
#endif

//UFclass definition

UFclass::UFclass(int N){
	//Constructor function
	for (int i=0; i<N; ++i){
	    data.push_back(i);
	}
}
UFclass::UFclass(){}

UFclass::~UFclass(){
}

void UFclass::union2c(int p, int q){
}

void UFclass::print_component(){
	std::map<int, std::vector<int> > component_dict;
	for (int i =0; i< (int)data.size(); ++i){
		if(component_dict.count(data[i]) ){
			component_dict[data[i]].push_back(i);

		}else{
			component_dict[data[i]]= std::vector<int> {i};
		}
	}
	

	for (auto& [key, val] : component_dict){

		std::cout<<"{";

		for(auto num : val){
			std::cout<< num;
		}
		std::cout<<"}"<<std::endl;
	}
}

QuickFindUF::QuickFindUF(int N):UFclass(N){
}

QuickFindUF::~QuickFindUF(){
}

void QuickFindUF::union2c(int p, int q){

     int p_id= data[p];
     int q_id= data[q];
     for(auto& item : data){
	     item = item==p_id ? q_id : item; 
     }
}

bool QuickFindUF::connected(int p, int q){
	return data[p]==data[q];
}

QuickUnionUF::QuickUnionUF(int N):UFclass(N){
}
QuickUnionUF::QuickUnionUF(){
}

QuickUnionUF::~QuickUnionUF(){
}

void QuickUnionUF::union2c(int p, int q){
	int root_p = root(p);
	int root_q = root(q);
	data[root_p]=root_q;
}

bool QuickUnionUF::connected(int p, int q){
	return root(p)==root(q);
}

int QuickUnionUF::root(int index){
     int node_index{index};
     while(node_index!=data[node_index]){
        node_index=data[node_index];
     }
     return node_index;
}


WeightedQuickUnionUF::WeightedQuickUnionUF(int N) : QuickUnionUF(N){
	 tree_sz=std::vector<int> (N,1);
}

WeightedQuickUnionUF::WeightedQuickUnionUF(){
	
}

WeightedQuickUnionUF::~WeightedQuickUnionUF(){
	
}

void WeightedQuickUnionUF::union2c(int p, int q){
	int root_p= QuickUnionUF::root(p);
	int root_q = QuickUnionUF::root(q);
	if (root_p==root_q){return;}
	if (tree_sz[root_p]< tree_sz[root_q]){
		data[root_p]=root_q;
		tree_sz[root_q]+=tree_sz[root_p];
	}else{
		data[root_q]=root_p;
		tree_sz[root_p]+=tree_sz[root_q];
	}

}

WeightedQuickUnionUFwithPC::WeightedQuickUnionUFwithPC(){

}

WeightedQuickUnionUFwithPC::WeightedQuickUnionUFwithPC(int N) : WeightedQuickUnionUF(N){

}

WeightedQuickUnionUFwithPC::~WeightedQuickUnionUFwithPC(){

}

int WeightedQuickUnionUFwithPC:: root(int index){
	int node_index{index};
     while(node_index!=data[node_index]){
		 data[node_index] =data[data[node_index]];
        node_index=data[node_index];
     }
     return node_index;
}
