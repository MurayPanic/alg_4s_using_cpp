#include <iostream>
#include <vector>
#include <queue>
#include <bitset>

//Class declaration
class Huffman;

//Class definition



class Huffman{
	
	public:
		Huffman();
		~Huffman();
		void main(std::string, std::string);
		void compress();
		void expand();
	private:
		class Node{
			public:
				Node();
				Node(unsigned char, int, Huffman::Node*, Huffman::Node*);
				~Node();
				
				unsigned char ch;
				unsigned int freq;
				Node* left;
				Node* right;
				bool operator< (const Huffman::Node&) const;
				bool isLeaf();
		
		};	

		
		
		Node* buildTrie( std::vector<unsigned int> );
		void writeTrie(Huffman::Node*);
		Huffman::Node* readTrie( std::string::iterator& );
		void buildCode(std::vector<std::string>&, Huffman::Node*,std::string );
	
		std::string data;
		std::vector<std::bitset<1> > data_bin;
		std::string output_str;

		union {
			unsigned int integer;
			unsigned char char_byte;
		}digit;

		union {
			unsigned int integer;
			unsigned char char_byte[4];
		}len;
	

};

//Constructor and deconstructor;
Huffman::Huffman(){};

Huffman::~Huffman(){};


Huffman::Node::Node(){

};

Huffman::Node::Node(unsigned char input_ch, int input_freq, Node* input_left, Node* input_right){
		this->ch = input_ch;
		this->freq = input_freq;
		this->left = input_left;
		this->right = input_right;

}

Huffman::Node::~Node(){}

//Member Function

bool Huffman::Node::operator<(const Huffman::Node& that) const {

	//Overload the operator into greater than
	return this->freq < that.freq;

}

bool Huffman::Node::isLeaf(){
	return (this->left==nullptr) && (this->right==nullptr);
}



Huffman::Node* Huffman::buildTrie( std::vector<unsigned int> freq){

	class greater_than{
		public:
			bool operator()(Huffman::Node* node_A, Huffman::Node* node_B){
				if(node_A->freq == node_B->freq){
					return node_A->ch >= node_B->ch;
				}

				return (node_A->freq >= node_B->freq);
			}	
	};

	std::priority_queue< Huffman::Node*, std::vector<Huffman::Node*>, greater_than > node_queue;
	
	unsigned int i{0};
	for(auto char_freq : freq){
		if(char_freq!=0){
			Huffman::Node* node_ptr= new Huffman::Node((unsigned char)i, char_freq, nullptr, nullptr );
			node_queue.push(node_ptr);
		}
		++i;
	}

	while(node_queue.size()>1){
		Huffman::Node* left_node_ptr = node_queue.top();
		node_queue.pop();

		
		Huffman::Node* right_node_ptr = node_queue.top();
		node_queue.pop();
		int total_freq = left_node_ptr->freq + right_node_ptr->freq;
		
		Huffman::Node* internal_node_ptr =  new Huffman::Node('\0', total_freq, left_node_ptr, right_node_ptr );		
		node_queue.push(internal_node_ptr);
		
		
	
	}

	return node_queue.top();
}


void Huffman::writeTrie(Huffman::Node* node_x_ptr){
	if ( node_x_ptr->isLeaf()){
		this->output_str+='1';	
		std::bitset<8> ch_bin( (unsigned int)node_x_ptr->ch );
		this->output_str+= (ch_bin.to_string());
		
		return;
	}

	this->output_str+='0';
	writeTrie(node_x_ptr -> left);
	writeTrie(node_x_ptr -> right);

}

Huffman::Node* Huffman::readTrie( std::string::iterator& data_ptr ){
			
		
		bool isLeaf= (*data_ptr)=='1';
	
		if(isLeaf==true){
			std::string character_bin_str(data_ptr+1, data_ptr+9);
			
			std::bitset<8> character_bin(character_bin_str);
			unsigned int character_int = character_bin.to_ulong();
			unsigned char character = character_int;
			
			data_ptr+=9;
			return new Huffman::Node(character, -1, nullptr, nullptr);

		}else{
			++data_ptr;
			
			return new Huffman::Node('\0', -1, this->readTrie(data_ptr), this->readTrie(data_ptr) );
		}


}


void Huffman::buildCode(std::vector<std::string>& ST, Huffman::Node* node_ptr, std::string cur_str){
	if(!node_ptr->isLeaf()){
		this->buildCode(ST, node_ptr->left, cur_str+'0');
		this->buildCode(ST, node_ptr->right, cur_str+'1');
	}
	else{	

		unsigned int char_index = node_ptr->ch;
		ST.at(char_index) = cur_str;
	}
}

void Huffman::compress(){
	

	//Count character frequency
	std::vector<unsigned int> freq(256,0);
	for(unsigned char character : this->data){
		unsigned int index = character;
		
		++freq.at(index);
	}

	

	//Build trie and code table
	Huffman::Node* root=this->buildTrie(freq);
	std::vector<std::string> ST(256,"");
	std::string empty_str="";
       	this->buildCode(ST,root, empty_str);

	//Print the trie first
	this->writeTrie(root);	
	
	// print number of bytes in original uncompressed message
	std::bitset<32> len(this->data.size());

	 this->output_str += len.to_string();

	for(unsigned char character : this->data){
		unsigned int index = character;
		//std::cout<< character <<": "<<ST.at(character) <<std::endl;
		this->output_str +=ST.at(index);
	}

	//convert the binary string to char code
	std::string tmp="";
	for(auto character : output_str){
		tmp+=character;
		if(tmp.length()==8){
			std::bitset<8> tmp_bin(tmp);
			unsigned char tmp_ch = (unsigned int)tmp_bin.to_ulong();
			std::cout<<tmp_ch;
			tmp.clear();
		}
	}
	
	if(tmp.length()>0){
		while(tmp.length()!=8){
			tmp+='0';
		}
		
		std::bitset<8> tmp_bin(tmp);
		unsigned char tmp_ch = (unsigned int)tmp_bin.to_ulong();
		std::cout<<tmp_ch;
		tmp.clear();
	}



}

void Huffman::expand(){
	//convert the string to bit stream string
	std::string data_bin="";
	for(auto character : this->data){
		std::bitset<8> character_bin(character);
		data_bin += character_bin.to_string();
	
	}
	this->data = data_bin;

	 // read in Huffman trie from input stream
	 	auto data_ptr = this->data.begin();
        Huffman::Node* root = this->readTrie(data_ptr);
	
	//read data length;
	int pos = std::distance(this->data.begin(),data_ptr );
	
	std::string encoded_data_length_str = this->data.substr(pos, 32 );
	std::bitset<32> encoded_data_length_bin(encoded_data_length_str) ;
	int  encoded_data_length= encoded_data_length_bin.to_ullong();

	//Move data_ptr and skip the data length
	data_ptr += 32;


	//decode using the Huffman trie
	int counter = encoded_data_length;
	for(auto iter= data_ptr; iter!= this->data.end(); ){
		Huffman::Node* node_ptr = root;
		
		while(!node_ptr->isLeaf()){
			
			if(*iter =='0'){
				node_ptr = node_ptr->left;;
			}else{
				node_ptr = node_ptr->right;
			}

			++iter;
		}

		std::cout<<node_ptr->ch;
		--counter;
		if(counter==0){
			return;
		}

	}


	
}

void Huffman::main(std::string file_str, std::string args){
	this->data = file_str;

	

        if(args=="-"){
                this->compress();
        }else if(args=="+"){
                this->expand();
        }else{
                throw std::invalid_argument("Illegal command line argument");
        }


}


int main(int argc, char* argv[]){
	std::string indicator = argv[1];
        std::string file_str="";
        std::string tmp="";
	
        while(std::cin.peek() != EOF){
                tmp = std::cin.get();
                file_str+=tmp;
        }
	Huffman H_ins{};
        H_ins.main(file_str, indicator);


}
