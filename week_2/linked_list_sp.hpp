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
		std::unique_ptr < Node<T> > next;

};

template <class T>
class LinkedList{
	public:
		LinkedList();
		LinkedList(T);
		
		~LinkedList();
		std::unique_ptr < Node<T> > head;
		std::unique_ptr < Node<T> > tail;
};

#endif

template <class T>
Node<T>::Node(){
	data=T{};
	next=nullptr;
};

template <class T>
Node<T>::Node(const Node<T> & node_obj){
	data=node_obj.data;
	
	next=node_obj.next;
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
	auto temp = std::make_unique<Node<T>>();
	head = std::move(temp);
	//tail= head;
};

template <class T>
LinkedList<T>::~LinkedList(){
	while(head){
		head= std::move(head->next);
	}

};

template <class T>
LinkedList<T>::LinkedList(T val){
	auto temp = std::make_unique<Node<T>>(val);
	head= std::move(temp);
	//tail= head;
};


