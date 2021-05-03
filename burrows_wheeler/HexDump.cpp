#include<iostream>
#include<string>
#include<bitset>

int main(int argc, char* argv[] ){
	/*
	char character;
	std::string tmp="";
	int counter{0};
	while(std::cin >> character){
		++counter;
		tmp+=character;
		if( (counter%8) == 0){
			std::bitset<8> bin_input(tmp);
			std::cout <<std::hex << bin_input.to_ulong()  << " ";
			
			tmp.clear();
		}

	}
	*/
	char character;
	while(std::cin >> character){
		
			std::bitset<8> bin_input(character);
			std::cout <<std::hex << bin_input.to_ulong()  << " ";
			
			
		}

	

	std::cout<<std::endl;

}
