#include <memory>

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <class T>
class Node{
	public:
		Node();
		Node(T);
		~Node();
		T data;
		Node<T>* next;
		Node<T>* prev;

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

template <class T> class DoublyLinkedList;

#endif

template <class T>
Node<T>::Node(){
	data=T{};
	next=nullptr;
	prev=nullptr;
};


template <class T>
Node<T>::Node(T val){
	data=val;
	
	next=nullptr;
	prev=nullptr;

}

template <class T>
Node<T>::~Node(){
};

template <class T>
LinkedList<T>::LinkedList(){
	head = nullptr;
	tail= head;
};

template <class T>
LinkedList<T>::~LinkedList(){};

template <class T>
LinkedList<T>::LinkedList(T val){
	head=new  Node<T> (val);
	tail= head;
};

//Doubly Linked list Definition

template <class T>
class DoublyLinkedList{
	public:
		DoublyLinkedList();
		DoublyLinkedList(T);
		~DoublyLinkedList();
		Node<T>* head;
		Node<T>* tail;

};

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(): head(nullptr),tail(nullptr) {};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(T val): head(new Node<T>(val)){
	tail= head;
};

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){}
