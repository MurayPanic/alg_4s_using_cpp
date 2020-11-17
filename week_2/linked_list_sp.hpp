#include <memory>

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <class T>
class Node{
	public:
		Node();
		Node(T);
		Node(const Node<T> &);
		~Node();
		T data;
		std::shared_ptr < Node<T> > next;
		std::weak_ptr <Node<T> > prev;

};

template <class T>
class LinkedList{
	public:
		LinkedList();
		LinkedList(T);
		
		~LinkedList();
		std::shared_ptr < Node<T> > head;
		std::shared_ptr < Node<T> > tail;
};

#endif

template <class T>
Node<T>::Node(): data(),next(nullptr), prev(std::weak_ptr<Node<T>>()){
	//data=T{};
	//next=nullptr;
	//prev=nullptr;
};

template <class T>
Node<T>::Node(const Node<T> & node_obj){
	data=node_obj.data;
	
	next=node_obj.next;
	prev= node_obj.prev;

};

template <class T>
Node<T>::Node(T val){
	data=val;
	
	next=nullptr;
	

}

template <class T>
Node<T>::~Node(){
};

template <class T>
LinkedList<T>::LinkedList(){
	auto temp = std::make_shared<Node<T>>();
	head = std::move(temp);
	tail= std::move(temp);
};

template <class T>
LinkedList<T>::~LinkedList(){
	while(head){
		head= std::move(head->next);
	}

};

template <class T>
LinkedList<T>::LinkedList(T val){
	auto temp = std::make_shared<Node<T>>(val);
	head= std::move(temp);
	tail= std::move(temp);
};


