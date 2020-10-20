#include<iostream>
#include<filesystem>
#include<fstream>
#include<string>
#include "UFclass.h"

int main(int argc, char* argv[]){
	std::cout<< "This program is to test the algorithm for dynamic connection problem"<<std::endl;
	std::filesystem::path input_file_path("./input.txt");
	std::ifstream input_file;
	std::cout<<input_file_path<<std::endl;
	input_file.open(input_file_path);
	std::string record_num;
	input_file >> record_num;
	int N = std::stoi(record_num);
	WeightedQuickUnionUFwithPC QFUF_ins(N);
	while(!input_file.eof()){
	  std::string tmp_a, tmp_b;
	  input_file>>tmp_a >>tmp_b;
	  if(input_file.peek()==EOF){break;}
	  std::cout << tmp_a <<" is connected to "<< tmp_b <<std::endl;
	  
	  int p = std::stoi(tmp_a);
	  int q = std::stoi(tmp_b);
	  if(!QFUF_ins.connected(p,q)){
	  	QFUF_ins.union2c(p,q);
	  }
	}

	std::cout<<"Is 3 and 4 connected?: "<< QFUF_ins.connected(3,4)
		<<std::endl;
	std::cout<<"Is 5 and 3 connected?: " << QFUF_ins.connected(5,3)
		<< std::endl;

	
	std::cout<< "The components are shown below: " <<std::endl;

	QFUF_ins.print_component();
	


	return 0;

}
