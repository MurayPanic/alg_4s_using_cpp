#include <iostream>
#include <memory>
#include "linked_list.hpp"
#include <gtest/gtest.h>

 TEST(NodeTest,ConstructorTest){
    
    Node<int> node_ins{};
    //Node<int> node_ins_2(10);
    //Node<std::vector<int>> node_ins_3{};
    SUCCEED();


}

/*

TEST(NodeTest, DataMemberTest){
    Node<int> node_ins(10);
    EXPECT_EQ(10, node_ins.data);
    
    
} */

TEST(NodeTest, PointerMemeberTest){
    Node<int> node_ins(10);
    std::cout<<"First node address: "<< &node_ins <<std::endl;
    //std::cout<<"First node next address: "<< node_ins.next <<std::endl;
    //std::unique_ptr<Node<int>> empty_ptr();
    //EXPECT_EQ(empty_ptr, node_ins.next);

     Node<int> node_ins_2(20);

     std::cout<<"Second node address: "<< &node_ins_2 <<std::endl;
    //std::cout<<"Second node next address: "<< node_ins_2.next <<std::endl;
    
    node_ins.next=&node_ins_2;

    std::cout<<"reset complete" <<std::endl; 

    std::cout<<"--------------"<<std::endl;

    std::cout<<"Delete the first node"<<std::endl; 
    node_ins.~Node();

    std::cout<<"delete complete"<<std::endl;
    std::cout<<"+++++++++++++++"<<std::endl;

     std::cout<<"Delete the second node"<<std::endl; 
    node_ins_2.~Node();

    std::cout<<"delete complete"<<std::endl;
    std::cout<<"+++++++++++++++"<<std::endl;

    //node_ins.next.reset();
    

    
 

   /*
    std::cout<<"--------------"<<std::endl;
    std::cout<<"Delete the second node"<<std::endl;
    //node_ins_2.~Node(); */

    

    
    

    /* int val =node_ins.next->data ;
    EXPECT_EQ(20, val);  */ 
   

} 

/* TEST(LinkedListTest, ConstructorTest){
    LinkedList<int> int_linked_list{};
    //LinkedList< std::vector<int> > vector_linked_list{};
    SUCCEED();
} */


int main(int ac, char* av[]){

    std::cout<< "This script is to  test the linked_list head file"
             << std::endl;

    ::testing::InitGoogleTest(&ac, av);
    
    return RUN_ALL_TESTS();


    
}
