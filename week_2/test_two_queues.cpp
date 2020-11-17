#include <iostream>
#include <memory>
#include "two_queues.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <exception>
#include <algorithm>


int main(int ac, char* av[]){

	std::cout<<"This script is to test the two_queues head file"
		<<std::endl;
	::testing::InitGoogleTest(&ac,av);

	return RUN_ALL_TESTS();

}

TEST(DequeTest, checkConstructor){
	Deque<int> deque_ins{};
	//Node<int>  head_node{2};
	Deque<int> deque_ins_2(2);
}

TEST(DequeTest,checkDequeMember){
	Deque<int> deque_ins{};
	ASSERT_EQ(nullptr,deque_ins.head);
	ASSERT_EQ(nullptr,deque_ins.tail);
        Deque<int> deque_ins_2(20);
	EXPECT_EQ(20, deque_ins_2.head->data);
	EXPECT_EQ(20, deque_ins_2.tail->data);
}

TEST(DequeTest, checkEmpty){
 	Deque<int> deque_ins{};
	EXPECT_TRUE(deque_ins.isEmpty());
	Deque<int> deque_ins_2{20};
	EXPECT_FALSE(deque_ins_2.isEmpty());
}

TEST(DequeTest, checkSize){
	Deque<int> deque_ins{};
	EXPECT_EQ(0, deque_ins.size());
	Deque<int> deque_ins_2{20};
	EXPECT_EQ(1, deque_ins_2.size());
}

TEST(DequeTest,checkAddFirst){
	Deque<int> deque_ins{};
	EXPECT_EQ(0, deque_ins.size());
	deque_ins.addFirst(20);
	EXPECT_EQ(1, deque_ins.size());
	EXPECT_EQ(20, deque_ins.head->data);
	deque_ins.addFirst(30);
	EXPECT_EQ(2,deque_ins.size());
	EXPECT_EQ(30, deque_ins.head->data);
	Deque<int> deque_ins_2{66};
	EXPECT_EQ(1, deque_ins_2.size());
	deque_ins_2.addFirst(77);
	EXPECT_EQ(2, deque_ins_2.size());
	EXPECT_EQ(77, deque_ins_2.head->data);
}

TEST(DequeTest,checkAddLast){
	Deque<int> deque_ins{};
	EXPECT_EQ(0, deque_ins.size());
	deque_ins.addLast(10);
	EXPECT_EQ(1, deque_ins.size());
	EXPECT_EQ(10,deque_ins.tail->data);
	deque_ins.addLast(20);
	EXPECT_EQ(2,deque_ins.size());
	EXPECT_EQ(20, deque_ins.tail->data);
	Deque<int> deque_ins_2{66};
	EXPECT_EQ(1, deque_ins_2.size());
	deque_ins_2.addLast(77);
	EXPECT_EQ(2, deque_ins_2.size());
	EXPECT_EQ(77, deque_ins_2.tail->data);
}

TEST(DequeTest, checkRemoreFirst){
        Deque<int> deque_ins{};
		EXPECT_THROW(deque_ins.removeFirst(), NoSuchElementException);
		deque_ins.addFirst(10);
		deque_ins.addLast(20);
		EXPECT_EQ(10, deque_ins.head->data);
		EXPECT_EQ(20, deque_ins.tail->data);
		deque_ins.addFirst(30);
		deque_ins.addLast(40);
		EXPECT_EQ(30, deque_ins.head->data);
		EXPECT_EQ(40, deque_ins.tail->data);
		deque_ins.removeFirst();
		EXPECT_EQ(10, deque_ins.head->data);
		deque_ins.removeFirst();
		EXPECT_EQ(20, deque_ins.head->data);
		deque_ins.removeFirst();
		EXPECT_EQ(40, deque_ins.head->data);
		deque_ins.removeFirst();
		EXPECT_EQ(0,deque_ins.size());
		EXPECT_THROW(deque_ins.removeFirst(), NoSuchElementException);
		
}

TEST(DequeTest, checkRemoveLast){
		Deque<int> deque_ins{};
		EXPECT_THROW(deque_ins.removeLast(), NoSuchElementException);
		deque_ins.addFirst(10);
		deque_ins.addLast(20);
		EXPECT_EQ(10, deque_ins.head->data);
		EXPECT_EQ(20, deque_ins.tail->data);
		deque_ins.addFirst(30);
		deque_ins.addLast(40);
		EXPECT_EQ(30, deque_ins.head->data);
		EXPECT_EQ(40, deque_ins.tail->data);
		deque_ins.removeLast();
		EXPECT_EQ(20, deque_ins.tail->data);
		deque_ins.removeLast();
		EXPECT_EQ(10, deque_ins.tail->data);
		deque_ins.removeLast();
		EXPECT_EQ(30, deque_ins.tail->data);
		deque_ins.removeLast();
		EXPECT_EQ(0,deque_ins.size());
		EXPECT_THROW(deque_ins.removeLast(), NoSuchElementException);

}

TEST (DequeTest, checkIterator){
	Deque<int> deque_ins(10);
	EXPECT_EQ(10, deque_ins.head->data);
	//std::cout<< "The head is :"<<deque_ins.head->data <<std::endl;
	auto iter_1 = deque_ins.iterator();
	//std::cout<< "The iter is: "<< iter_1.iter->data <<std::endl;
	EXPECT_EQ(10, iter_1.iter->data);
	Deque<int> deque_ins_2{};
	auto iter_2= deque_ins_2.iterator();
	EXPECT_EQ(nullptr, iter_2.iter );
	deque_ins_2.addLast(20);
	deque_ins_2.addLast(30);
	deque_ins_2.addLast(40);
	auto iter_3 = deque_ins_2.iterator();
	EXPECT_EQ(20, iter_3.iter->data);
	++iter_3;
	EXPECT_EQ(30, iter_3.iter->data);
	DequeIterator<int> iter_4{};
	iter_4= iter_3++;
	EXPECT_EQ(30, iter_4.iter->data);
	EXPECT_THROW(++iter_3, NoSuchElementException);
	
	

}

TEST (RandomizedQueueTest, checkConstructor){
	RandomizedQueue<int> RQ_ins{};
	//EXPECT_EQ(nullptr, RQ_ins.arr);
	RandomizedQueue<int> RQ_ins_2(10);
	//EXPECT_EQ(10, RQ_ins.arr[0]);
	//EXPECT_EQ(0, RQ_ins.arr[1]);
	//EXPECT_EQ(NULL, RQ_ins.arr[1]);

}

TEST (RandomizeQueueTest, checkSize){
	RandomizedQueue<int> RQ_ins{};
	EXPECT_EQ(0, RQ_ins.size());
	RandomizedQueue<int> RQ_ins_2(10);
	EXPECT_EQ(1, RQ_ins_2.size());
}

TEST (RandomizedQueueTest, checkEnqueue){
	RandomizedQueue<int> RQ_ins{};
	RQ_ins.enqueue(10);
	EXPECT_EQ(1, RQ_ins.size() );
	RQ_ins.enqueue(20);
	EXPECT_EQ(2, RQ_ins.size());
	std::cout<<"Now need to double the stack"<<std::endl;
	RQ_ins.enqueue(30);
	EXPECT_EQ(3, RQ_ins.size());
	RQ_ins.enqueue(40);
	EXPECT_EQ(4, RQ_ins.size());
	RQ_ins.enqueue(50);
	EXPECT_EQ(5, RQ_ins.size());

	RQ_ins.enqueue(60);
	EXPECT_EQ(6, RQ_ins.size());

	RQ_ins.enqueue(70);
	EXPECT_EQ(7, RQ_ins.size());

	RQ_ins.enqueue(80);
	EXPECT_EQ(8, RQ_ins.size());

}

TEST(RandomizedQueueTest, checkDequeue){
	RandomizedQueue<int> RQ_ins{};
	EXPECT_THROW( RQ_ins.dequeue(),NoSuchElementException);
	RQ_ins.enqueue(10);
	auto temp = RQ_ins.dequeue();
	EXPECT_EQ(10, temp);
	EXPECT_EQ(0, RQ_ins.size());
	EXPECT_THROW( RQ_ins.dequeue(),NoSuchElementException);
	RQ_ins.enqueue(20);
	auto temp_2 = RQ_ins.dequeue();
	EXPECT_EQ(20, temp_2);
	EXPECT_EQ(0, RQ_ins.size());
	EXPECT_THROW( RQ_ins.dequeue(),NoSuchElementException);
        
	std::vector<int> test_vec{1,2,3,4,5,6,7,8,9,10};
	for(auto item : test_vec){
		RQ_ins.enqueue(item);
	}
	std::vector<int> deque_vec{};
	std::cout << "Deque order: ";
	for(auto i=0;i<10;++i){
	        auto temp = RQ_ins.dequeue();
		deque_vec.push_back(temp);
		std::cout<<temp<<" ";
	}
	std::cout<<std::endl;

	EXPECT_NE(test_vec, deque_vec);
	std::sort(deque_vec.begin(), deque_vec.end());
	EXPECT_EQ(test_vec, deque_vec);


}

TEST(RandomizedQueueTest, checkSample){
	RandomizedQueue<int> RQ_ins{};
	EXPECT_THROW(RQ_ins.sample(), NoSuchElementException);
	RQ_ins.enqueue(10);
	auto sample_item = RQ_ins.sample();
	EXPECT_EQ(10, sample_item);
	RQ_ins.dequeue();
	EXPECT_THROW(RQ_ins.sample(),NoSuchElementException);
	RQ_ins.enqueue(20);
	auto sample_item_2 = RQ_ins.sample();
	EXPECT_EQ(20, sample_item_2);
	RQ_ins.enqueue(30);
	
}

TEST(RandomizedQueueTest, checkIterator){
	RandomizedQueue<int> RQ_ins{};
	auto iter_1 = RQ_ins.iterator();
	EXPECT_THROW(*iter_1, NoSuchElementException);
	RandomizedQueue<int> RQ_ins_2(10);
	auto iter_2 = RQ_ins_2.iterator();
	EXPECT_EQ(10, *iter_2);
	RQ_ins.enqueue(20);
	RQ_ins.enqueue(30);
	RQ_ins.enqueue(40);
	RQ_ins.enqueue(50);
	RQ_ins.enqueue(60);
	RQ_ins.enqueue(70);
	auto iter_3= RQ_ins.iterator();
	EXPECT_THROW(*iter_1, NoSuchElementException);
	std::vector<int> test_vec{20, 30, 40, 50, 60, 70};
	std::vector<int> result_vec{};
	std::cout<<"The now print the item randomly: ";
	while(iter_3.has_next()){
		auto item = *iter_3;
		result_vec.push_back(item);
		++iter_3;
		std::cout<< item <<" ";
	}
	std::cout<<std::endl;
	auto iter_4 = RQ_ins.iterator();
	std::vector<int> result_vec_2{};
	std::cout<<"The now print the item with another iterator randomly: ";
	while(iter_4.has_next()){
		auto item = *iter_4;
		result_vec_2.push_back(item);
		++iter_4;
		std::cout<< item <<" ";
	}
	std::cout<<std::endl;
	EXPECT_NE(result_vec, result_vec_2);
	EXPECT_NE(test_vec, result_vec);
	std::sort(result_vec.begin(), result_vec.end());
	EXPECT_EQ(test_vec, result_vec);

}
