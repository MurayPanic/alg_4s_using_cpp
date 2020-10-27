#include<iterator>
#include "linked_list.hpp"

#ifndef TWO_QUEUES_HPP
#define TWO_QUEUES_HPP

template <class T>  
class DequeIterator
{
    public:
	    DequeIterator();
	    ~DequeIterator();
};

template <class T> class Deque{
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
		DequeIterator<T> iterator();
};



#endif

template<class T>
Deque<T>::Deque(){
}

template<class T>
Deque<T>::~Deque(){
}

template<class T>
Deque<T>::Deque(T){
	LinkedList(T);
}

