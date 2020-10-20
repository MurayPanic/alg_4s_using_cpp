#ifndef UFCLASS_H
#define UFCLASS_H
#include<vector>
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
