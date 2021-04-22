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

};


//Member function
void MoveToFront::encode(){
	int radix[256];
	for(int i{0}; i<256; ++i){
		radix[i]=i;
	}

	for (unsigned char character : data){
		int index = character;
		int pos = radix[index];
		//To display result in hexidecimal
		//std::cout<<std::hex << pos<<" ";

		//output the result in binary
		std::bitset<8> bin_pos(pos);
		std::cout <<  bin_pos;

		for(int i{0}; i<256; ++i){
			radix[i]= radix[i]<pos? radix[i]+1 : radix[i] ;
		}
		radix[index]=0;
	}

	//std::cout<<std::endl;
	
}

void MoveToFront::decode(){

	int pos[256];
	for(int i{0}; i<256; ++i){
		pos[i]=i;
	}
	
	
	std::string tmp="";
	int counter{0};
	for (char character : data){
		++counter;
		tmp+=character;
		if( counter%8 ==0){
			std::bitset<8> bin_index(tmp);
			int index = bin_index.to_ulong();
			unsigned char radix = pos[index];
			std::cout << radix;
			for(int i=index; i>0; --i){
				pos[i]= pos[i-1];
			}
			pos[0]= radix;
			tmp.clear();
		}

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
	/* if(argc==1){
                throw std::invalid_argument("Invalid arguments");
        }

        std::string indicator = argv[1];
        std::string filename = argv[2];

        std::string path_str = std::filesystem::current_path();
        path_str += filename;
        std::filesystem::path complete_path(path_str);
        std::ifstream input_file;
        input_file.open(complete_path, std::ios::in | std::ios::binary);
        if(input_file.fail()){
                throw std::invalid_argument("the provide data file open failed");
        }

        MoveToFront MTF_ins{};

	std::string file_str="";
        while(!input_file.eof()){
                char tmp;
                input_file.read(&tmp, sizeof(tmp));
                if(input_file.fail()){break;}
                file_str+= tmp;

        }
        //file_str.pop_back();
	*/
	
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
