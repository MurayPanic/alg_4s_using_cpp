#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <exception>
#include <thread>
#include <future>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include <list>

#include "Board.hpp"

#ifndef SOLVER_HPP
#define SOLVER_HPP

//class declaration
class Solver;
//typedef std::pair<Board,int> board_move_pair;
class BoardNode;
class Hash_Board;

#endif

//class definition


class BoardNode{
	public:
		BoardNode();
		BoardNode(Board, BoardNode*,int);
		~BoardNode();
		bool operator == (const BoardNode& ) const;
		Board board_data;
		BoardNode* prev_node;
		int move_num;
};


//hash function for unordered_set
class Hash_Board_Node{
			public:
				std::size_t operator()(const BoardNode& board_node_ins)const{
					std::string board_str = board_node_ins.board_data.toString();
					std::hash<std::string> str_hasher;
					return str_hasher(board_str);
				
				}
				
		};

class Solver{

	public:
		Solver();
		Solver(Board);
		~Solver();

		bool isSolvable();
		int moves();
		std::vector<Board> solution();
	
	private:
		
		class hamming_priority{
			public:	
		
			bool operator()( BoardNode& BN_ins_1, 
					 BoardNode& BN_ins_2){
				int hp_1 = BN_ins_1.board_data.hamming() + BN_ins_1.move_num;
				int hp_2 = BN_ins_2.board_data.hamming() + BN_ins_2.move_num;
				//Noted that greater than is used here
				return hp_1 > hp_2;
			
			};
		
		};

		class manhattan_priority{
		 	public:
				
			bool operator()(BoardNode& BN_ins_1, 
					BoardNode& BN_ins_2){

				int md_1 = BN_ins_1.board_data.manhattan();
				int md_2 = BN_ins_2.board_data.manhattan();
				int mp_1 = md_1 + BN_ins_1.move_num;
				int mp_2 = md_2 + BN_ins_2.move_num;
				//Noted that greater than is used here
				//Break tie with manhattan distance
				return (mp_1 > mp_2)|| (mp_1==mp_2 && md_1>md_2);
			
			};
		};

		typedef std::priority_queue<BoardNode,
			            std::vector<BoardNode>, 
				    manhattan_priority > PQ;


		int move_num;
		std::vector<Board> solution_list;
		std::vector<Board> A_star_search(Board);

		Board root;
		//a flag indicates that whether it is called by a solvable function
		bool solvable_flag;
		
		//a flag to stop thread
		bool stop_thread;

};


//constructor & deconstructor

BoardNode::BoardNode(){};

BoardNode::BoardNode(Board board_data_input, 
		     BoardNode* prev_node_addr, 
		     int cur_move)
		    : board_data(board_data_input), prev_node(prev_node_addr), move_num(cur_move){};

BoardNode::~BoardNode(){};

//BoardNode equal operator
bool BoardNode::operator == (const BoardNode& that_BN_ins)const{
	bool result = this->board_data== that_BN_ins.board_data;
	return result;
}


Solver::Solver(){
	throw std::invalid_argument("IllegalArgumentException:: null argument is not allowed");
};

Solver::Solver(Board initial): move_num(0), 
			       solvable_flag(false),
  			       stop_thread(false),
			       root(initial){

	Board initial_twin= initial.twin();
	//std::cout<< "The twin board is: "<< initial_twin.toString()<< std::endl;
	
	//Find solution in single thread
	//this->solution_list = this->A_star_search(initial);

	//Find solutions in multi thread
	
	std::future< std::vector<Board> > fp= std::async(&Solver::A_star_search, this, initial);
	std::future< std::vector<Board> > fp_twin = std::async(&Solver::A_star_search, this, initial_twin);

	auto time_out = std::chrono::milliseconds(10);
	while( fp.valid() && fp_twin.valid()){
		if(fp.valid() && fp.wait_for(time_out) == std::future_status::ready ){
			this->solution_list=fp.get();
			this->solvable_flag=true;
			this->stop_thread = true;
			break;
		}
	
		if(fp_twin.valid() && fp_twin.wait_for(time_out) == std::future_status::ready ){
			this->stop_thread=true;
			break;
		}
	}

	
};

Solver::~Solver(){};

//min number of moves to solve initial board; -1 if unsolvable
int Solver::moves(){
	int result{-1};
	if(!this->solution_list.empty()){
		result = this->solution_list.size();
	}
	return result;

}

// sequence of boards in a shortest solution; null if unsolvable
std::vector<Board> Solver::solution(){
	
	return this->solution_list;

}

//is the initial board solvable?
bool Solver::isSolvable(){
	return this->solvable_flag;
}

//A* search algorithm
std::vector<Board> Solver::A_star_search(Board initial){
                std::list<Board> result_list{} ;	
		std::unordered_set<BoardNode, Hash_Board_Node> game_tree{};
		BoardNode BN_ins(initial, nullptr,0);
		PQ PQ_ins{};
		PQ_ins.push(BN_ins);
		auto least_priority_element = PQ_ins.top();
		int step{0};
		while(!PQ_ins.empty() && !this->stop_thread){

			least_priority_element= PQ_ins.top();
			/*
			std::cout<<"--------------------------------"<<std::endl;
			std::cout<<"Now the deque element is: "<<std::endl;
				auto the_top= least_priority_element;
				int move= the_top.move_num;
				int m_dist= the_top.board_data.manhattan();
				int h_dist = the_top.board_data.hamming();
				int priority= move+m_dist;
				
				
				std::cout<<"priority: "<<priority<<std::endl;
				std::cout<<"moves: "<< move<<std::endl;
				std::cout<<"Manhattan: "<<m_dist<<std::endl;
				std::cout<<"Hamming: "<<h_dist<<std::endl;
				
				if (the_top.prev_node){
					auto tmp_node = *(the_top.prev_node);
					std::cout<<"Prev node:"<<std::endl;
					std::cout<<tmp_node.board_data.toString()<<std::endl;
				}else{
					std::cout<<"The prev node is null"
						<<std::endl;
				}
			std::cout<< least_priority_element.board_data.toString()<<std::endl;
			std::cout<<"++++++++++++++++++++++++++++++"<<std::endl;
				
			std::cout<<"Now the content in PQ is:"<<std::endl;
			auto PQ_copy=PQ_ins;
			while(!PQ_copy.empty()){
				auto the_top= PQ_copy.top();
				int move= the_top.move_num;
				int m_dist= the_top.board_data.manhattan();
				int priority= move+m_dist;
				std::cout<<"priority: "<<priority<<std::endl;
				std::cout<<"moves: "<< move<<std::endl;
				std::cout<<"Manhattan: "<<m_dist<<std::endl;
				std::cout<<"Hamming: "<<h_dist<<std::endl;
				std::cout<<PQ_copy.top().board_data.toString()<<std::endl;
				PQ_copy.pop();
			}
			
			std::cout<<"-------------------------"<<std::endl;
			std::cout<<"The above is the "<<step<<" steps"<<std::endl;
			++step;
			std::string debug_str;
			std::cout<<"Press to continue"<<std::endl;
			std::cin>>debug_str;
			*/

			PQ_ins.pop();
			BoardNode* tree_node_ptr= new BoardNode(least_priority_element);	
			game_tree.insert(*tree_node_ptr);
			//BoardNode* tree_node_ptr = std::find(game_tree.begin(), game_tree.end(),least_priority_element.board_data.toString()]);

			if(least_priority_element.board_data.isGoal()){break;}
			
			int next_move = least_priority_element.move_num +1;

			//Insert neighbor
			for(auto board_ins : least_priority_element.board_data.neighbors() ){
			
			BoardNode tmp_node(board_ins, tree_node_ptr, next_move);	
			//if a board is previous search, then skip it
			if(game_tree.contains(tmp_node) ){continue;}			
			PQ_ins.push(tmp_node);
			
			}
		}

		while(least_priority_element.prev_node != nullptr){
			result_list.push_front(least_priority_element.board_data);
			least_priority_element= *(least_priority_element.prev_node);
			/*
			std::cout<<"Now tracing back the solution"<<std::endl;
			std::cout<<least_priority_element.board_data.toString()<<std::endl;
			auto tmp= *(least_priority_element.prev_node);
			std::cout<<"The pre node is: "<<std::endl;
			std::cout << tmp.board_data.toString() <<std::endl;
			std::string debug_str;
			std::cout<<"Press to continue"<<std::endl;
			std::cin>>debug_str;
			*/
		}

		std::vector<Board> result_vec(result_list.begin(), result_list.end());

		return result_vec;

}
