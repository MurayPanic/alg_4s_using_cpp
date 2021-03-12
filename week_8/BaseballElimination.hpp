#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<exception>

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

        if(input_file.fail()){
                throw std::invalid_argument("Fail to open file.");
        }       

        std::string tmp_number_or_teams;
        input_file >> tmp_number_or_teams;
        this->number_of_teams = std::stoi(tmp_number_or_teams);
        for(int i{0}; i< this->number_of_teams; ++i){
                std::string tmp;
                input_file >> tmp;
                this->name_of_teams.push_back(tmp);

                input_file >>tmp;
                int win = std::stoi(tmp);
                this->win_vec.push_back(win);

                input_file >> tmp;
                int loss = std::stoi(tmp);
                this->loses_vec.push_back(loss);

                input_file >> tmp;
                int remaining = std::stoi(tmp);
                this->remaining_vec.push_back(remaining);

                std::vector<int> against_vec{};
                for(int j{0}; j< this->number_of_teams;++j){
                        input_file >>tmp;
                        int against = std::stoi(tmp);
                        against_vec.push_back(against);
                }
                this->against_array.push_back(against_vec);
                

        }

}

BaseballElimination::~BaseballElimination(){}