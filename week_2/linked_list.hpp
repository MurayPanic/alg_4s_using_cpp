#include <memory>
#include<string>

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <class T>
class Node{
	public:
		Node();
		//Node(T T_val);
		Node(T);
		~Node();
		T data;
		Node<T>* next;

};

template <class T>
class LinkedList{
	public:
		LinkedList();
		LinkedList(T);
		~LinkedList();
		std::shared_ptr< Node<T> > head;
		std::shared_ptr< Node<T> > tail;
};

#endif

template <class T>
Node<T>::Node(){};

/*
template <class T>
Node<T>::Node(T T_val){
	data=T_val;
	next= new T;
};
*/

template <class T>
Node<T>::Node(T val){
	data=val;
	
	next=nullptr;
	
	
	

}

template <class T>
Node<T>::~Node(){
	std::string val = std::to_string(data);
	std::cout<<"Now delete the: "<< val <<std::endl;
	std::cout<<this<<std::endl;
	//next=nullptr;
	
	std::cout << "Object deleted" <<std::endl;
	std::cout << "-----------" <<std::endl;
};

template <class T>
LinkedList<T>::LinkedList(){
	std::cout<< "Now initialize the linkedlist 1"<<std::endl;
	head = std::make_shared< Node<T> >();
	tail= head;
};

template <class T>
LinkedList<T>::~LinkedList(){};

template <class T>
LinkedList<T>::LinkedList(T val){
	std::cout<< "Now initialize the linkedlist 1"<<std::endl;
	Node<T> head_node= Node<T>(val);
	head= std::make_shared<Node<T> >( head_node);
	tail= head;
};
