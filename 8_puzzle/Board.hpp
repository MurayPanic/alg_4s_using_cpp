#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <cmath>
#include <unordered_map>
#include <utility>
#include <random>

#ifndef BOARD_HPP
#define BOARD_HPP

//Class declaration
class Board;

#endif


//Class definition
class Board{
	public:
		Board();
		Board(std::vector<int>);
		Board(std::vector<std::vector<int> >);
		~Board();

		std::string toString() const;
		int dimension() const;
		int hamming();
		int manhattan();
		bool isGoal();
		bool operator == (const Board& ) const;
		std::vector<Board> neighbors();
		Board twin();
	private:
		std::vector<std::vector<int> > data;
		std::unordered_map<int, std::pair<int, int>> goal;
		std::pair<int, int> blank_tile;
		int hamming_dist;
		int manhattan_dist;
				

};

//class constructor

Board::Board(){


};




Board::Board(std::vector<int> num_vec): hamming_dist(-1), manhattan_dist(-1){
	int vec_len = num_vec.size();
	auto dim = std::sqrt(vec_len);
	bool square_or_not = dim - std::ceil(dim); 
	if(square_or_not){
		throw std::invalid_argument("The provided vector is not in correct dimension.");
	}
	
	std::vector<int> check_vec{};
	for(int i=0; i!= vec_len; ++i){
		check_vec.push_back(i);
	}
	if(!std::is_permutation(num_vec.begin(), num_vec.end(), check_vec.begin() )){
		throw std::invalid_argument("The provided numbers include duplication.");
	
	}
	
	std::vector<int> row(dim,-1);
		

	int col_index{0};
	int row_index{0};
	for (auto iter= num_vec.begin();iter!= num_vec.end(); ++iter){
		row[col_index]= (*iter);
		if(*iter==0){
			this->blank_tile= std::make_pair(row_index, col_index);
		}
		++col_index;

		if(col_index==dim){
			
			data.push_back(row);
			col_index = 0;
			row_index+=1;
		}
		
	        	

	}

	//initial goal
	int goal_num{1};
	for(int i=0; i!=dim; ++i){
		for(int j=0; j!=dim; ++j){
			std::pair<int, int> coor = std::make_pair(i,j);
			if(i==(dim-1) && j==(dim-1) ){
				goal[0]=coor;
			}else{
				goal[goal_num]=coor;
			}
			++goal_num;
			
		}
	}

		
	
	

};

Board::Board(std::vector<std::vector<int> >  input_data): hamming_dist(-1), manhattan_dist(-1){
	data= input_data;
		
	int dim= this->dimension();
	bool break_loop_flag{true};
	for(int i=0;i<dim && break_loop_flag; ++i){
		for(int j=0; j<dim && break_loop_flag ; ++j){
			if(this->data[i][j] ==0){
				this->blank_tile = std::make_pair(i,j);
				break_loop_flag = false;
			}
		}
	}
	//initial goal
	int goal_num{1};
	for(int i=0; i!=dim; ++i){
		for(int j=0; j!=dim; ++j){
			std::pair<int, int> coor = std::make_pair(i,j);
			if(i==(dim-1) && j==(dim-1) ){
				goal[0]=coor;
			}else{
				goal[goal_num]=coor;
			}
			++goal_num;
			
		}
	}
	
}

Board::~Board(){}

// Display the board with string
std::string Board::toString() const {


	int dim = dimension();
	std::string str_rep{};
	str_rep = std::to_string(dim) +"\n";
     
	for(auto& row : data){
		for(auto col_iter= row.begin(); col_iter!= row.end();){
			str_rep+= std::to_string(*col_iter);
			++col_iter;
			if (col_iter!= row.end()){
				str_rep+=" ";
			}else{
				str_rep+="\n";
			}
		
		}
	}
	
	return str_rep;
}

//Return the dimension of the board
int Board::dimension() const {
	int dim= data[0].size();

	return dim;
}

//Number of tiles out of place
int Board::hamming(){
	
	if(this->hamming_dist != -1){ return this->hamming_dist;}
	int i=1;
	int dist=0;
	for (auto& row: data){
		for(auto col : row){
			if(col != i){dist +=1 ;}
			i+=1;
		}
	}
	int last_index= dimension()-1;
	if(data[last_index][last_index] == 0){dist -= 1; }

	this->hamming_dist = dist;

	return this->hamming_dist;
}


//sum of manhattan distances between tiles and goal
int Board::manhattan(){

	if (this->manhattan_dist!= -1){return this->manhattan_dist;}

        int m_dist{0};
	int dim = dimension();
	for(int i=0; i<dim;++i){
		for(int j=0; j<dim; ++j){
			int num= data[i][j];
			if(num){
			auto coor = goal[ num ];
			
			auto tmp_dist= std::abs(i-coor.first) + std::abs(j-coor.second);
			m_dist += tmp_dist;

			//Output for debugging
			/*
			std::cout<<"Now calculate the distance of: "<<data[i][j]<<std::endl;
			std::cout<<"Its current coor is: "<<"("<<i<<","<<j<<")"<<std::endl;
			std::cout<<"Its goal coor is: "<<"("<<coor.first<<","<<coor.second<<")"<<std::endl;
			std::cout<<"The distance is: "<<tmp_dist<<std::endl;
			*/

			}
		}
	
	}

	this->manhattan_dist = m_dist;

	return this->manhattan_dist;

}


//is this board the goal board?
bool Board::isGoal(){
	if (  hamming()){
		return false;
	}else{
		return true;
	}
}

//does this board equal y?
bool Board::operator == (const Board& that_board_ins) const{
	if( this->toString() == that_board_ins.toString() ){
		return true;
	}else{
		return false;
	}
}

//all neighboring boards
std::vector<Board> Board::neighbors(){
	std::vector<Board> neighbor_vec{};

	std::vector<std::pair<int, int> > coor_list{ 
		std::make_pair(blank_tile.first-1, blank_tile.second),
	        std::make_pair(blank_tile.first+1,blank_tile.second), 
		std::make_pair(blank_tile.first, blank_tile.second-1),
		std::make_pair(blank_tile.first, blank_tile.second+1)
						   };

	for(auto coor : coor_list){
		try{
			//create new data board
			std::swap( this->data[blank_tile.first][blank_tile.second],
				   this->data.at(coor.first).at(coor.second));

		}
		//Prevent out of range
		catch(std::out_of_range){
			continue;
		}


		Board temp_board(this->data);
		neighbor_vec.push_back(temp_board);

		//Recover the original data
		std::swap( this->data[blank_tile.first][blank_tile.second],
		this->data.at(coor.first).at(coor.second));
		
	}


       return neighbor_vec; 

}

// a board that is obtained by exchanging any pair of tiles
Board Board::twin(){
	std::random_device rd;
	std::mt19937 gen(rd());
	int dim = this->dimension();
	std::uniform_int_distribution<> dist(0,dim-1);
	
	std::pair<int, int> first_tile = std::make_pair(dist(gen),dist(gen));
	std::pair<int, int> second_tile = std::make_pair(dist(gen),dist(gen));

	while(first_tile == this->blank_tile){
		first_tile= std::make_pair( dist(gen), dist(gen) );
	}

	while(second_tile == this->blank_tile || second_tile == first_tile){
		second_tile = std::make_pair( dist(gen), dist(gen) );
	}

	std::swap(data[first_tile.first][first_tile.second], 
		  data[second_tile.first][second_tile.second]);

	Board result_board(this->data);

	std::swap(data[first_tile.first][first_tile.second], 
		  data[second_tile.first][second_tile.second]);

	return result_board;
}
