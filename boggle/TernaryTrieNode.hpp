#include<iostream>

#ifndef TERNARYTRIENODE_HPP
#define TERNARYTRIENODE_HPP

//Class declaration
class TernaryTrieNode;

#endif

//Class definition
class TernaryTrieNode{
	public:
		TernaryTrieNode();
		TernaryTrieNode(char);
		TernaryTrieNode(char, int);
		~TernaryTrieNode();

		int value;
		char character;
		TernaryTrieNode* left;
		TernaryTrieNode* mid;
		TernaryTrieNode* right;

};

//Constructor and Deconstructor
TernaryTrieNode::TernaryTrieNode(): left(nullptr), mid(nullptr), right(nullptr), value(-1), character(){}

TernaryTrieNode::TernaryTrieNode(char input_char): left(nullptr), mid(nullptr), right(nullptr),value(-1), character(input_char) {}

TernaryTrieNode::TernaryTrieNode(char input_char, int input_val): left(nullptr), mid(nullptr), right(nullptr),value(input_val), character(input_char) {}

TernaryTrieNode::~TernaryTrieNode(){}

//Member function


