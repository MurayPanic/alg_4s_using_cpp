
#include "linked_list.hpp"
#include <iterator>

#ifndef TWO_QUEUES_HPP
#define TWO_QUEUES_HPP

template <class T > 
class DequeIterator: public std::iterator< std::forward_iterator_tag, T >
{   
	


    public:
	    DequeIterator();
		DequeIterator (const DequeIterator& );
	    ~DequeIterator();
		DequeIterator& operator= (const DequeIterator& );
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
		friend class DequeIterator<T>;
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
	LinkedList<T>();
}

