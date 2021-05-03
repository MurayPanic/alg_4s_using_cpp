#include<iostream>
#include<string>
#include<vector>
#include<random>
#include<algorithm>
#include<ranges>
#include<filesystem>
#include<fstream>
#include<exception>

#ifndef BOGGLEBOARD_HPP
#define BOGGLEBOARD_HPP

//class declaration
class BoggleBoard;

#endif

//class definition

class BoggleBoard{

	public:
		BoggleBoard();
		BoggleBoard(std::string);
		BoggleBoard(int, int);
		BoggleBoard(std::vector<std::string>);
		~BoggleBoard();

		int rows();
		int cols();
		char getLetter(int, int);
		std::string toString();

	private:
		
		 std::string  BOGGLE_1992[16]= {
 			       "LRYTTE", "VTHRWE", "EGHWNE", "SEOTIS",
        		       "ANAEEG", "IDSYTT", "OATTOW", "MTOICU",
        		       "AFPKFS", "XLDERI", "HCPOAS", "ENSIEU",
        		       "YLDEVR", "ZNRNHL", "NMIQHU", "OBBAOJ"
    		      };
		std::string BOGGLE_1983[16] = {
        			"AACIOT", "ABILTY", "ABJMOQ", "ACDEMP",
        			"ACELRS", "ADENVZ", "AHMORS", "BIFORX",
        			"DENOSW", "DKNOTU", "EEFHIY", "EGINTV",
        			"EGKLUY", "EHINPS", "ELPSTU", "GILRUW",
    		      };
		std::string BOGGLE_MASTER[25] = {
        			"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        			"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
        			"CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DHHLOR",
        			"DHHNOT", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        			"FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
    		      };
		std::string  BOGGLE_BIG[25] = {
        			"AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
        			"AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCENST",
			        "CEIILT", "CEILPT", "CEIPST", "DDHNOT", "DHHLOR",
        			"DHLNOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
        			"FIPRSY", "GORRVW", "IPRRRY", "NOOTUW", "OOOTTU"
    		      };
		const std::string  ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		const double FREQUENCIES[26]= {
        			0.08167, 0.01492, 0.02782, 0.04253, 0.12703, 0.02228,
        			0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025,
        			0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
        			0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
        			0.01974, 0.00074
    		      };

		int m;
		int n;
		std::vector< std::string> board;


};

//Constructor and deconstructor

BoggleBoard::BoggleBoard(): m(4),n(4){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(std::begin(this->BOGGLE_1992),std::end(this->BOGGLE_1992), gen);

	for (int i{0}; i< this->m; ++i){
		std::string row="";
		for(int j{0}; j< this->n; ++j){
			std::string letters = this->BOGGLE_1992[n*i+j];
			std::uniform_int_distribution<> dis(0, letters.length()-1);
			int r = dis(gen);
			row+=letters.at(r);
		
		}
		this->board.push_back(row);
	}
	
}

BoggleBoard::BoggleBoard(std::string filename){
	std::string path_str= std::filesystem::current_path();
	path_str += filename;

	std::filesystem::path complete_path(path_str);
	std::ifstream input_file;
	input_file.open(complete_path);
	if(input_file.fail()){
		throw std::invalid_argument("the provided data file open failed");
	}
	
	std::string m_str;
	input_file >> m_str;	
	this->m = std::stoi(m_str);

	std::string n_str;
	input_file >> n_str;
	this->n = std::stoi(n_str);
	
	if(this->m <=0 ){
		throw std::invalid_argument("number of rows must be a positive integer");
	}

	if(this->n <= 0){
		throw std::invalid_argument("number of columns must be a positive integer");
	}


	for (int i{0}; i<m; ++i){
		std::string row="";
		for(int j{0}; j<n; ++j){
			std::string letters;
		        input_file >>letters;
			if(letters=="Qu" || letters=="QU") {letters="Q";}
			if (this->ALPHABET.find(letters) == std::string::npos){
				throw std::invalid_argument("invalid character: "+ letters);
			}
			if(letters.length()>2){
				throw std::invalid_argument("invalid character: "+ letters);
			}
			row+=letters;
		
		}
		this->board.push_back(row);
	}


}


BoggleBoard::BoggleBoard(int input_m, int input_n): n(input_n), m(input_m){

	if(this->m <=0 ){
		throw std::invalid_argument("number of rows must be a positive integer");
	}

	if(this->n <= 0){
		throw std::invalid_argument("number of columns must be a positive integer");
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::discrete_distribution<> dis(std::begin(this->FREQUENCIES), std::end(this->FREQUENCIES)) ;

	for(int i{0}; i< this->m; ++i){
		std::string row{};
		for(int j{0}; j< this->n; ++j){
			int r = dis(gen);
			row+= this->ALPHABET.at(r);
		
		}
		this->board.push_back(row);
	}


}

BoggleBoard::BoggleBoard(std::vector<std::string> input_board){
		
	this->board = input_board;

	this->m = this->board.size();
	this->n = this->board.at(0).size();

}


BoggleBoard::~BoggleBoard(){}


//Member Function

int BoggleBoard::rows(){
	return this->m;
}

int BoggleBoard::cols(){
	return this->n;
}

char BoggleBoard::getLetter(int i, int j){
	return this->board.at(i).at(j);
}

std::string BoggleBoard::toString(){
	std::string str;
	str= std::to_string(this->m) +" "+ std::to_string(this->n) + "\n";
	for(auto& row : this->board){
		for(auto col :row){
			str+=col;
			if( col == 'Q' ){str+="u";}
			str+=" ";
		}
		str += "\n";
	}
	return str;

}
