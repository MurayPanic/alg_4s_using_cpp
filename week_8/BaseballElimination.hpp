#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>

#ifndef BASEBALLELLIMINATION_HPP
#define BASEBALLELLIMINATION_HPP

//Class declaration
class BaseballElimination;

#endif

//Class definition

class BaseballElimination{
    public:
            BaseballElimination();
            BaseballElimination(std::string);
            ~BaseballElimination();
            
            std::vector<std::string> teams();
            int wins(std::string);
            int losses(std::string);
            int remaining(std::string);
            int against(std::string, std::string);
            bool isElimination(std::string);
            std::vector<std::string> certificateOfElimination(std::string);
    
    private:
            int number_of_teams;
            std::vector<std::string> name_of_teams;
            std::vector<int> win_vec;
            std::vector<int> loses_vec;
            std::vector<int> remaining_vec;
            std::vector<std::vector<int> > against_array;

};

//Constructor and deconstructor

BaseballElimination::BaseballElimination(){}

BaseballElimination::BaseballElimination(std::string filename){

        std::string  path_str = std::filesystem::current_path();
        path_str += filename;
        std::filesystem::path  complete_path(path_str);
        std::ifstream input_file;
        input_file.open(complete_path);
        std::string tmp_number_or_teams;
        input_file >> tmp_number_or_teams;
        this->number_of_teams = std::stoi(tmp_number_or_teams);
        //need to read the remain record March 09 2021

}

BaseballElimination::~BaseballElimination(){}