#include <exception>
#include "linked_list.hpp"
#include <iterator>

#ifndef TWO_QUEUES_HPP
#define TWO_QUEUES_HPP

template <typename T > 
class DequeIterator: public std::iterator< std::forward_iterator_tag, T >
{   
	


    public:
	    DequeIterator();
		DequeIterator (const DequeIterator& );
	    ~DequeIterator();
		DequeIterator& operator= (const DequeIterator& );
};

template <typename T> class Deque: public LinkedList<T>{
	public:
		Deque();
		Deque(T);
		~Deque();
		bool isEmpty();
		int size();
		void addFirst(T const&);
		void addLast(T const&);
		T removeFirst();
		T removeLast();
		friend class DequeIterator<T>;
		DequeIterator<T> iterator();
};



#endif

template<typename T>
Deque<T>::Deque(){
}

template<typename T>
Deque<T>::~Deque(){
}

template<typename T>
Deque<T>::Deque(T val):LinkedList<T>(val){
	//Used the LinkedList constructor to initialized the 
	//head node and tail node
	
}

template<typename T>
bool Deque<T>::isEmpty(){
        return LinkedList<T>::head == nullptr;
}

template<typename T>
int Deque<T>::size(){
	int length{0};
	if(isEmpty()){return length;}

	Node<T>* tmp= LinkedList<T>::head;
	while(tmp!= nullptr){
		tmp=tmp->next;
		++length;
	}
	return length;
}

template<typename T>
void Deque<T>::addFirst(T const& val){
	Node<T>* new_head= new Node<T>(val);
	if(!isEmpty()){
		new_head->next=LinkedList<T>::head;
	}else{
		LinkedList<T>::tail = new_head;
	}
	LinkedList<T>::head = new_head;
}

template<typename T>
void Deque<T>::addLast(T const& val){
	Node<T>* new_tail= new Node<T>(val);
	if(!isEmpty()){
		LinkedList<T>::tail->next =  new_tail;
	}else{
		LinkedList<T>::head= new_tail;
	}
		LinkedList<T>::tail = new_tail;
}

template<typename T>
T Deque<T>::removeFirst(){
	if(isEmpty()){
		throw std::logic_error("emptyDequeError");
	}
	T first_item = LinkedList<T>::head->data;
	Node<T>* old_head= LinkedList<T>::head;
	LinkedList<T>::head= LinkedList<T>::head->next;
	delete old_head;
	return first_item;
}

template<typename T>
T Deque<T>::removeLast(){
	
	if(isEmpty()){
		throw std::logic_error("emptyDequeError");
	}
	T last_item = LinkedList<T>::tail->data;
	Node<T>* old_tail = LinkedList<T>::tail;
	Node<T>* pointer =  LinkedList<T>::head;
	while(pointer!=nullptr && pointer->next != old_tail){
		pointer=pointer->next;
	}
	LinkedList<T>::tail = pointer;
	if (LinkedList<T>::tail==nullptr){LinkedList<T>::head=nullptr;}
	delete old_tail;
	return last_item;
}

template<typename T>
DequeIterator<T>:: DequeIterator(){

}


