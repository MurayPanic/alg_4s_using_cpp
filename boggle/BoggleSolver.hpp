#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<exception>
#include "BoggleBoard.hpp"
#include "PrefixTree.hpp"

#ifndef BOGGLESOLVER_HPP
#define BOGGLESOLVER_HPP

//Class declaration
class BoggleSolver;

#endif

//Class definition
class BoggleSolver{
	public:
		BoggleSolver();
		BoggleSolver(std::vector< std::string >);
		~BoggleSolver();
	
		std::unordered_set<std::string> getAllValidWords(BoggleBoard);
		int scoreOf(std::string);
	
	private:
		std::unordered_set<std::string> dictionary_set;
		PrefixTree dictionary_prefix_tree;
		void  DFS(BoggleBoard&, int, int,std::vector<std::vector<bool> >, std::unordered_set<std::string>&, std::string);
		std::vector<std::pair<int,int> > get_neibours(int, int);

};

//Constructor and Deconastructor

BoggleSolver::BoggleSolver(){}

BoggleSolver::BoggleSolver(std::vector<std::string> dictionary) 
			: dictionary_set(dictionary.begin(), dictionary.end()) ,
			 dictionary_prefix_tree(dictionary)
								
{
	
}

BoggleSolver::~BoggleSolver(){}

//Member function
std::unordered_set<std::string > BoggleSolver::getAllValidWords(BoggleBoard board){
	std::unordered_set<std::string> all_valid_words;
	
	std::vector<std::vector<bool> > marked;
	for(int row{0}; row< board.rows();++row){
		std::vector<bool> tmp( board.cols(),false ) ;
		marked.push_back(tmp);
		
	}

	std::string prefix="";

	for(int row{0}; row< board.rows(); ++row){
		for(int col{0}; col< board.cols(); ++col){
			
			prefix= board.getLetter(row,col);
			if(board.getLetter(row, col)=='Q'){
				prefix+='U';
			}

			
			this->DFS(board, row, col, marked, all_valid_words, prefix);

		}
	}
	


	return all_valid_words;

}

void BoggleSolver::DFS(BoggleBoard& board, int row, int col, 
			std::vector<std::vector<bool> > marked,
			std::unordered_set<std::string>& all_valid_words,
			std::string prefix
					   ){
	marked[row][col]=true;
	
	//get eight_neighbor
	auto neighbor_list = this->get_neibours(row, col);

	//check_neighbor
	for(auto& neighbor : neighbor_list){
		auto i = neighbor.first;
		auto j = neighbor.second;
		
		//Skip the invalid neighbor
		if(i<0 ||j<0 || i>=board.rows() || j>=board.cols()){
			continue;
		}

		try{
			if(!marked.at(i).at(j) ){
				auto character = board.getLetter(i, j);
				
				//handle the Qu case
				std::string word = character=='Q'? prefix+character+'U' : prefix+character ;

				if(this->dictionary_set.contains(word) && word.length()>2){
					all_valid_words.insert(word);
				}

				//if there are word with that prefix, extend the 
				//current path
				if(this->dictionary_prefix_tree.has_word_with_prefix(word)){
				this->DFS(board, i, j, marked, all_valid_words, word);
				}

			}
		}
		catch(std::out_of_range){
			continue;
		}
	}
	



}

std::vector<std::pair<int,int> > BoggleSolver::get_neibours(int row, int col){
	
	std::pair<int, int> top_left =std::make_pair(row-1, col-1);
	std::pair<int, int> top = std::make_pair(row-1, col);
	std::pair<int, int> top_right = std::make_pair(row-1, col+1);
	std::pair<int, int> left = std::make_pair(row, col-1);
	std::pair<int, int> right = std::make_pair(row, col+1);
	std::pair<int, int> bottom_left =std::make_pair(row+1, col-1);
	std::pair<int, int> bottom =std::make_pair(row+1, col);
	std::pair<int, int> bottom_right = std::make_pair(row+1, col+1);

	std::vector<std::pair<int,int> > neighbors{top_left, top, top_right, left, right, bottom_left, bottom, bottom_right};

	return neighbors;
}

int BoggleSolver::scoreOf(std::string word){
	int len= word.length();
	//std::cout<<"Len: "<<len<<std::endl;
	int score{0};
	switch (len){
		case 3: 
			score=1;
			break;
		case 4:
			score=1;
			break;
		case 5:	
			score=2;
			break;
		case 6:
			score=3;
			break;
		case 7:
			score=5;
	
	}
	if(len>=8){score=11;}

	return score;
	
}
