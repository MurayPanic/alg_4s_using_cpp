#include<iostream>
#include<string>
#include<exception>
#include<filesystem>
#include<fstream>
#include<bitset>

//class declaration
class MoveToFront;

class MoveToFront{

	public:
		void encode();
		void decode();
		void main(std::string, std::string);

	private:
		std::string data;
		union {
			unsigned int integer;
			unsigned char char_byte;
		}digit;

};


//Member function
void MoveToFront::encode(){
	int radix[256];
	for(int i{0}; i<256; ++i){
		radix[i]=i;
	}

	for (unsigned char character : data){
		unsigned int index = character;
		int pos = radix[index];
		
		this->digit.integer=pos;
		std::cout << this->digit.char_byte;

		for(int i{0}; i<256; ++i){
			radix[i]= radix[i]<pos? radix[i]+1 : radix[i] ;
		}
		radix[index]=0;
	}


	
}

void MoveToFront::decode(){

	unsigned int pos[256];
	for(int i{0}; i<256; ++i){
		pos[i]=i;
	}
	
	
	for (char character : data){
			this->digit.char_byte=character;
		
			
			int index = this->digit.integer;
			unsigned char radix = pos[index];
			std::cout << radix;
			for(int i=index; i>0; --i){
				pos[i]= pos[i-1];
			}
			pos[0]= radix;
			
		

	}

}

void MoveToFront::main(std::string file_str, std::string args){
	this->data = file_str;

	if(args=="-"){
		this->encode();
	}else if(args=="+"){
		this->decode();
	}else{
		throw std::invalid_argument("Invalid arguments");
	}
	

}

int main(int argc, char* argv[]){
	
	
        std::string indicator = argv[1];
        MoveToFront MTF_ins{};
	std::string file_str="";
	std::string tmp="";

	while(std::cin.peek()!=EOF){
		tmp = std::cin.get();
		file_str += tmp;
	}

	MTF_ins.main(file_str, indicator);

}
