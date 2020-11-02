#include <iostream>
#include <memory>
#include "two_queues.hpp"
#include <gtest/gtest.h>
#include <vector>
#include <exception>

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
	EXPECT_THROW(deque_ins.removeFirst(), std::logic_error);
}
