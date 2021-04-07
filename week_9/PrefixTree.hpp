#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "TernaryTrieNode.hpp"

#ifndef PREFIXTREE_HPP
#define PREFIXTREE_HPP

//Class declaration
class PrefixTree;

#endif

//Class definition

class PrefixTree{
	public:
		PrefixTree();
		PrefixTree(std::vector<std::string>);
		~PrefixTree();
		bool has_word_with_prefix(std::string);
	private:
		TernaryTrieNode* root;
		void put(std::string, int);
		TernaryTrieNode* put(TernaryTrieNode*, std::string&, int, int);
		TernaryTrieNode* search_prefix_node(TernaryTrieNode*, 
						std::string&,int);
		bool BFS_from_prefix_node(TernaryTrieNode*);
};

//Constructor and deconstructor

PrefixTree::PrefixTree(){}

PrefixTree::PrefixTree(std::vector<std::string> input_dict){
		
	this->root = nullptr;	
	int index{0};	
	for(auto& word : input_dict){
			this->put(word, index);
			++index;
	
	}

}

PrefixTree::~PrefixTree(){}

//member function
void PrefixTree::put(std::string  word, int index){
	this->root = this->put(this->root, word, index, 0);
}

TernaryTrieNode* PrefixTree::put(TernaryTrieNode* node_ptr, 
				std::string& word,
				int index,
				int d){
	char character= word.at(d);
	if(node_ptr==nullptr){

		node_ptr= new TernaryTrieNode(character);
	}

	if(character < node_ptr->character){
		node_ptr->left = put(node_ptr->left, word, index, d);
	}

	else if(character > node_ptr->character){
		node_ptr->right = put(node_ptr->right, word, index, d);
	}

	else if( (character == node_ptr->character)  && (d < word.length()-1) ){
		node_ptr->mid = put( node_ptr->mid, word, index, d+1);
	}else{
		node_ptr->value = index;
	}

	return node_ptr;
}


bool PrefixTree::has_word_with_prefix(std::string prefix){
	


	
	TernaryTrieNode*  prefix_node = this->search_prefix_node(this->root, prefix, 0);
		
	if(prefix_node==nullptr){
		return false;
	}
	
	return this->BFS_from_prefix_node(prefix_node);

	
}

TernaryTrieNode* PrefixTree::search_prefix_node(TernaryTrieNode* node_ptr,
		                                std::string& prefix,
						int prefix_char_index){
	
	if(node_ptr==nullptr){return nullptr;}

	char character = prefix[ prefix_char_index ];

	if(character < node_ptr->character){
		return search_prefix_node(node_ptr->left, prefix, prefix_char_index);
	}
	else if(character > node_ptr->character){
		return search_prefix_node(node_ptr->right, prefix, prefix_char_index);
	}
	else if(prefix_char_index < prefix.length()-1){
		return search_prefix_node(node_ptr->mid, prefix, prefix_char_index+1);
	}
	else{
		return node_ptr;
	}


}

bool PrefixTree::BFS_from_prefix_node(TernaryTrieNode* prefix_node){
	std::queue<TernaryTrieNode*> node_queue{};
	node_queue.push(prefix_node);

	while(!node_queue.empty()){
		auto cur_node = node_queue.front();
		node_queue.pop();
		if(cur_node->left){node_queue.push(cur_node->left); }
		if(cur_node->mid){node_queue.push(cur_node->mid); }
		if(cur_node->right){node_queue.push(cur_node->right); }
		
		if (cur_node->value!= -1){ return true;}
	
	}

	return false;

}
