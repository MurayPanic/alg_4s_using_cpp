
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
		T* next;

};

template <class T>
class LinkedList{
	public:
		LinkedList();
		LinkedList(T);
		~LinkedList();
		Node<T>* head;
		Node<T>* tail;
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
Node<T>::Node(T){
	data=T();
	next=new T;

}

template <class T>
Node<T>::~Node(){};

template <class T>
LinkedList<T>::LinkedList(){};

template <class T>
LinkedList<T>::~LinkedList(){};

template <class T>
LinkedList<T>::LinkedList(T){
	head= new Node<T>();
	tail= new Node<T>();
};
