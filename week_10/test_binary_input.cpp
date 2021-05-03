#include<iostream>
#include<bitset>
#include<vector>
#include<string>

int main(int argc, char* argv[]){
	std::vector<std::bitset<1> > bit_stream;
	unsigned char input;

	while(std::cin>>input){	
		std::bitset<8> input_bit(input);
		std::cout<<"Bit representation:"<<input_bit<<std::endl;
		for(int i=0; i<8;++i){
			std::cout<<"bit pos value: "<<input_bit[i]<<std::endl;
			std::bitset<1> bit(input_bit[i]);
			bit_stream.push_back( bit);
		}
	}

	for(auto item : bit_stream){
		std::cout<< item;
	}
	std::cout<<std::endl;

}
