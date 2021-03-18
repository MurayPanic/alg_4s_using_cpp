#include<iostream>
#include<string>
#include<vector>
#include<filesystem>
#include<fstream>
#include<exception>
#include <climits>
#include "FlowNetwork.hpp"
#include "FordFulkerson.hpp"

#pragma once
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
            FlowNetwork FN_data;
            FlowNetwork construct_graph(int);

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


//Member Function

FlowNetwork BaseballElimination::construct_graph(int target_team){
        //The game vertices can be calculated by 
        //the diagnols of the generated matrix, then half the total number
        //of the remain elements
        int game_vertices= ( (this->number_of_teams)*(this->number_of_teams) 
                             - (this->number_of_teams) )/2;
        int team_vertices = this->number_of_teams;
        
        //Add two dummy vertices for source and sink
        //the 0 node will be used for source
        //the last node will be use for sink
        int total_num_of_nodes = game_vertices + team_vertices +2;
        

        FlowNetwork FN_data(total_num_of_nodes);

        //Connect source with game/team vertices
        //The node number of game vertices start from 1;
        //The node numer of team vertices star from game_vertices+1
        

        int k{1}; //pointer in grapth node
        for(int col{0}; col< this->number_of_teams; ++col){
                if (col==target_team){
                        ++k;
                        continue;
                }
                for(int row=col; row<this->number_of_teams; ++row){
                        if(row==target_team){
                                 ++k;
                                continue;
                        }
                        if(col==row){
                                
                                continue;
                        }

                        //Connect source with game vertices
                        FlowEdge source_game_edge(0, k, this->against_array[row][col], 0.0);
                        FN_data.addEdge(source_game_edge);

                        //Connect  game vertices with team vertice
                        FlowEdge game_team_edge_1(k, 1+game_vertices+row, DBL_MAX, 0.0);
                        FlowEdge game_team_edge_2(k, 1+game_vertices+col, DBL_MAX, 0.0);
                        FN_data.addEdge(game_team_edge_1);
                        FN_data.addEdge(game_team_edge_2);

                        ++k;


                }
        }

        // Connect team vertices and target
        int max_target_team_total_win = this->win_vec[target_team] + this->remaining_vec[target_team];
        for(int i{0}; i<team_vertices; ++i){
                if(i== target_team){continue;}
                int tmp_capacity = max_target_team_total_win - win_vec[i] >=0 ? max_target_team_total_win - win_vec[i] : 0;
                
                if(tmp_capacity<0){
                        std::cout<<"I finid some negative capacity"<<tmp_capacity<<std::endl;
                }

                FlowEdge team_target_edge (i + game_vertices, total_num_of_nodes-1, tmp_capacity,0 );
                FN_data.addEdge(team_target_edge);
        }

        return FN_data;




}

bool BaseballElimination::isElimination(std::string team_name){
        std::vector<std::string>  certificate=this->certificateOfElimination(team_name);


        return !certificate.empty();
        
}

std::vector<std::string> BaseballElimination::certificateOfElimination(std::string team_name){
        //Find team index
        auto team_iter = std::find(this->name_of_teams.begin(),this->name_of_teams.end(), team_name );
        int team_index = std::distance(this->name_of_teams.begin(), team_iter);

        //Construct residual grapth
        FlowNetwork FN_data = this->construct_graph( team_index );
        FordFulkerson FF_ins(FN_data, 0, FN_data.V()-1 );

        //Get teams
        std::vector<std::string> certificate{};
        int game_vertices= ( (this->number_of_teams)*(this->number_of_teams) 
                             - (this->number_of_teams) )/2;
        for(auto team_i{0}; team_i<this->number_of_teams; ++ team_i){
                if(team_i==team_index){continue;}
                if(FF_ins.inCut(1 + game_vertices + team_i) ){
                        certificate.push_back(this->name_of_teams[team_i]);
                };
        }

        return certificate;
}