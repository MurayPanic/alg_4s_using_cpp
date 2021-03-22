#include<iostream>
#include<string>
#include "BaseballElimination.hpp"

int main(int argc, char* argv[]){
	std::string filename = argv[1];
	if(filename.empty()){
		throw std::invalid_argument("Please provide data file directory.");
	}
	BaseballElimination division( filename);
	for(std::string team : division.teams()){
		if(division.isEliminated(team)){
			std::cout<< team << " is eliminated by the subset R = {";
			for(std::string t : division.certificateOfElimination(team)){
				std::cout<<t<<" ";
			}
		std::cout<<"}"<<std::endl;
		}
		else{
			std::cout<<team<<" is not eliminated"<<std::endl;
		}
	}
}
