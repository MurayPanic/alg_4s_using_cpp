#include <exception>
#include <iterator>
#include <memory>
#include <random>
#include <algorithm>
#include <climits>
#include "linked_list.hpp"
#ifndef TWO_QUEUES_HPP
#define TWO_QUEUES_HPP

template <typename T > 
class DequeIterator: public std::iterator< std::forward_iterator_tag, T >
{   
	


    public:
	    DequeIterator();
		DequeIterator (const DequeIterator& );
		DequeIterator (Node<T>*  );
	    ~DequeIterator();
		DequeIterator& operator= (const DequeIterator<T>& );
		DequeIterator& operator++();
		DequeIterator& operator++(int);
                bool has_next();
                void next();		
	
		Node<T>* iter;

};

template <typename T> 
class Deque: public DoublyLinkedList<T>{
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
	private:
		int deque_len;
};

template<typename T>
class RandomizedQueueIterator;

			       
template<typename T>
class RandomizedQueue {
	public:
		RandomizedQueue();
		RandomizedQueue(T);
		~RandomizedQueue();
		int size();
		void enqueue(T);
		T dequeue();
		T sample();
		friend class RandomizedQueueIterator<T>;
		RandomizedQueueIterator<T> iterator();
	private:
		std::unique_ptr<T[]> arr;
		int RQ_len;
		int AV_len;
};


class NoSuchElementException: public std::exception
{
	
		const char* what() const throw ();
};

class IllegalArgumentException: public std::exception
{
		const char* what() const throw();
};



#endif

template<typename T>
Deque<T>::Deque(){
	deque_len=0;
}

template<typename T>
Deque<T>::~Deque(){
}

template<typename T>
Deque<T>::Deque(T val):DoublyLinkedList<T>(val){
	deque_len=1;
}
template<typename T>
bool Deque<T>::isEmpty(){
        return DoublyLinkedList<T>::head == nullptr;
}

template<typename T>
int Deque<T>::size(){
	/*int length{0};
	if(isEmpty()){return length;}

	Node<T>* tmp= LinkedList<T>::head;
	while(tmp!= nullptr){
		tmp=tmp->next;
		++length;
	}
	return length;
	*/
	return deque_len;
}

template<typename T>
void Deque<T>::addFirst(T const& val){
	Node<T>* new_head= new Node<T>(val);

	if(!isEmpty()){
		new_head->next=DoublyLinkedList<T>::head;
		DoublyLinkedList<T>::head->prev=new_head;
	}else{
		DoublyLinkedList<T>::tail = new_head;
	}
	DoublyLinkedList<T>::head = new_head;
	deque_len+=1;
}

template<typename T>
void Deque<T>::addLast(T const& val){
	Node<T>* new_tail= new Node<T>(val);
	
	if(!isEmpty()){
		DoublyLinkedList<T>::tail->next =  new_tail;
		new_tail->prev= DoublyLinkedList<T>::tail;
	}else{
		DoublyLinkedList<T>::head= new_tail;
	}
	DoublyLinkedList<T>::tail = new_tail;
	++deque_len;

}

template<typename T>
T Deque<T>::removeFirst(){
	if(isEmpty()){
		throw NoSuchElementException();
	}
	T first_item = DoublyLinkedList<T>::head->data;
	Node<T>* old_head= DoublyLinkedList<T>::head;
	DoublyLinkedList<T>::head= DoublyLinkedList<T>::head->next;
	if(!isEmpty()){
		DoublyLinkedList<T>::head->prev=nullptr;
	}
	delete old_head;
	--deque_len;
	return first_item;
}

template<typename T>
T Deque<T>::removeLast(){
	
	if(isEmpty()){
		throw NoSuchElementException();
	}
	T last_item = DoublyLinkedList<T>::tail->data;
	Node<T>* old_tail = DoublyLinkedList<T>::tail;
	DoublyLinkedList<T>::tail = DoublyLinkedList<T>::tail->prev;
	if (DoublyLinkedList<T>::tail==nullptr){DoublyLinkedList<T>::head=nullptr;}
	else{DoublyLinkedList<T>::tail->next=nullptr;}
	delete old_tail;
	--deque_len;
	return last_item;
}

template<typename T>
DequeIterator<T> Deque<T>::iterator(){
	DequeIterator<T> iter_ins( DoublyLinkedList<T>::head);
	return iter_ins;
}


template<typename T>
DequeIterator<T>::DequeIterator(){
	iter= nullptr;
}

template<typename T>
DequeIterator<T>::~DequeIterator(){
	
}
template<typename T>
DequeIterator<T>::DequeIterator( Node<T>* head_pointer){
	iter= head_pointer;
}

template<typename T>
DequeIterator<T>& DequeIterator<T>::operator ++ (){
		if (iter->next != nullptr){
			iter=iter->next;
			return *this;
		}else{
			//throw std::logic_error("EndOfDeque");
			throw NoSuchElementException();
		}
		
}

template<typename T>
DequeIterator<T>& DequeIterator<T>::operator ++ (int){
		
		if (iter->next != nullptr){
			DequeIterator<T>* temp = new DequeIterator<T>(iter);
			iter= iter->next;
			return *temp;
		}else{
			//throw std::logic_error("EndOfDeque");
			throw NoSuchElementException();
		}
		
}

template<typename T>
DequeIterator<T>& DequeIterator<T>::operator = (const DequeIterator<T>&  DI_ins){
            iter = DI_ins.iter;
			return *this;

}


const char* NoSuchElementException::what() const throw(){
         return "No such an element";

}

const char* IllegalArgumentException::what() const throw(){
         return "Null element is not allowed";

}


template<typename T>
RandomizedQueue<T>:: RandomizedQueue(){
     arr=nullptr;
     RQ_len=0;
     AV_len=0;

}

template<typename T>
RandomizedQueue<T>::~RandomizedQueue(){
     

}

template<typename T>
RandomizedQueue<T>:: RandomizedQueue(T val){
	 
     arr=std::make_unique<T[]>(2);
	 arr[0]=val;
     RQ_len=1;
     AV_len=2;

}

template<typename T>
int RandomizedQueue<T>::size(){
     return RQ_len;
	
}

template<typename T>
void RandomizedQueue<T>::enqueue(T item){
	if (arr==nullptr){
		arr=std::make_unique<T[]>(2);
		AV_len=2;
	}
	//int arr_len= sizeof(&arr)/ sizeof(arr[0]);
	//std::cout<<"arr size: "<<sizeof(arr)<<std::endl;
	//std::cout<<"arr[0] size: "<< sizeof(arr[0])<<std::endl;
	//std::cout<<"The curent array size is: "<<AV_len<<std::endl;
	//std::cout<<"The current RQ_len is: "<<RQ_len<<std::endl;
	if (RQ_len == AV_len) {
	  //std::cout<<"Now need to double the array size"<<std::endl;
	  AV_len= 2*RQ_len;
	  auto temp= std::make_unique<T[]>(AV_len);
	  //std::cout<<"temp size: "<<sizeof(&temp)<<std::endl;
	  for(int i=0; i< RQ_len; ++i){
		  temp[i]= arr[i];
	  }
          arr=std::move(temp);
	}
	arr[RQ_len]=item;
	++RQ_len;

	
}

template<typename T>
T RandomizedQueue<T>::dequeue(){
	if(arr==nullptr || RQ_len==0){
		throw NoSuchElementException();
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0,RQ_len-1);
	int selected_index = dis(gen);
	T selected_item = arr[selected_index];
	std::swap(arr[selected_index], arr[RQ_len-1]);
	arr[RQ_len-1]= T{};
	RQ_len-=1;
	return selected_item;

	

}

template<typename T>
T RandomizedQueue<T>::sample(){
	if(arr==nullptr || RQ_len==0){
		throw NoSuchElementException();
	}
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, RQ_len-1);
	int selected_index = dis(gen);
	T selected_item = arr[selected_index];
	return selected_item;
}

template<typename T>
RandomizedQueueIterator<T> RandomizedQueue<T>::iterator(){
	RandomizedQueueIterator<T> iter(*this);
	
	return iter;

}

template<typename T>
class RandomizedQueueIterator: public std::iterator< std::forward_iterator_tag, T>
{
	public: 
		RandomizedQueueIterator();
		RandomizedQueueIterator(RandomizedQueue<T>&);
		~RandomizedQueueIterator();
		T operator*();
		RandomizedQueueIterator<T>& operator=(const RandomizedQueueIterator<T>&);
		RandomizedQueueIterator<T>& operator++();
		RandomizedQueueIterator<T>& operator++(int);
		bool has_next();
	private:
		std::vector<int> order_arr;
		RandomizedQueue<T>& RQ_ref;
		std::vector<int>::iterator pos;
		
};

template<typename T>
RandomizedQueueIterator<T>::RandomizedQueueIterator(){
	
}

template<typename T>
RandomizedQueueIterator<T>::RandomizedQueueIterator(RandomizedQueue<T>& RQ_ins)
: RQ_ref(RQ_ins), pos(nullptr),order_arr(){
	int RQ_len= RQ_ref.RQ_len;
	if(RQ_len ==0){
		return;
		
	}else{
               
		std::random_device rd;
		std::mt19937 gen(rd());
		for (int i=0; i< RQ_len; ++i){
			order_arr.push_back(i);
	        	std::uniform_int_distribution<> dis(0, i);
			int selected_index= dis(gen);
			std::swap(order_arr[selected_index], order_arr[i]);
		}
	
	}
	pos= order_arr.begin();

}


template<typename T>
RandomizedQueueIterator<T>::~RandomizedQueueIterator(){
}

template<typename T>
T RandomizedQueueIterator<T>::operator*(){
	if (pos==order_arr.end()){
		throw NoSuchElementException();}
	int index= *pos;

	return RQ_ref.arr[index];	
}

template<typename T>
RandomizedQueueIterator<T>& RandomizedQueueIterator<T>::operator=(const RandomizedQueueIterator<T>& RQI_ins){
	   order_arr=RQI_ins.order_arr;
	   pos=RQI_ins.pos;
	   return *this;
	
}



template<typename T>
RandomizedQueueIterator<T>& RandomizedQueueIterator<T>::operator++(){
	
	++pos;
	return *this;

}

template<typename T>
RandomizedQueueIterator<T>& RandomizedQueueIterator<T>::operator++(int){
	if(pos!=order_arr.end()){
		RandomizedQueueIterator<T> temp = new RandomizedQueueIterator<T> (*this);
		++pos;
		return *temp;
	}else{
		throw NoSuchElementException();
	}

}

template<typename T>
bool RandomizedQueueIterator<T>::has_next(){
	if (pos != order_arr.end()){
		return true;
	}else{
		return false;
	}
}
