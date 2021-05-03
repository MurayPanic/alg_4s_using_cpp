#include<array>
#include <memory>
#include <vector>
#include <algorithm>
#include "UFclass.hpp"
#include <random>
#include <exception>

#ifndef PERCOLATION_HPP
#define PERCOLATION_HPP

class Percolation{
    public:
        // Constructor. creates n-by-n grid, with all sites initially blocked
        Percolation(int n);
        //Deconstructor
        ~Percolation();
        // opens the site (row, col) if it is not open already
        void open(int row, int col);
        // is the site (row, col) open?
        bool isOpen(int row, int col);
        // is the site (row, col) full?
        bool isFull(int row, int col);
        // returns the number of open sites
        int numberOfOpenSites();
        // does the system percolate?
        bool percolates();
        // test client (optional)
        void test();
        //the data board
        int matrix_len;
        std::vector< std::vector<int> > matrix;
        WeightedQuickUnionUFwithPC connect_matrix;



};

class PercolationStats{
    public:
        
        // perform independent trials on an n-by-n grid
        PercolationStats(int n, int trials);

        ~PercolationStats();

        // sample mean of percolation threshold
        double mean();

        // sample standard deviation of percolation threshold
        double stddev();

        // low endpoint of 95% confidence interval
        double confidenceLo();

        // high endpoint of 95% confidence interval
        double confidenceHi();

        std::vector<double> trial_record;


};

#endif



Percolation::Percolation(int n){
    auto row=std::vector<int> (n,0);
    matrix= std::vector< std::vector<int> > (n,row);
    matrix_len=n;
    //Initialize the array for UF algorithm. add 2 dummy nodes
    connect_matrix= WeightedQuickUnionUFwithPC(n*n + 2);
    //Connect the dummy nodes to the first row and the last row of the grids
    //Add the two dummy nodes at the end of the matrix is ok. 
    //The n*n+1 is the head dummy node, its index is n*n
    //The n*n+2 is the tail dummy node, its index is n*n+1
    for (int i(0); i<matrix_len; ++i ){
        connect_matrix.union2c(n*n, i);
        connect_matrix.union2c(n*n+1,n*n-1-i);
    }


}
Percolation::~Percolation(){}

void Percolation::open(int row, int col){
    matrix.at(row).at(col)=1;

}

bool Percolation::isOpen(int row, int col){
    
     return matrix.at(row).at(col)==1;
    
}

bool Percolation::isFull( int row, int col){

       
        //int row_length = (int) matrix[0].size();
        int index = row* matrix_len + col;
        return connect_matrix.connected(index, 0);
}
int Percolation::numberOfOpenSites(){
    int num_o_site{0};
    for(auto& row: matrix){
        num_o_site += std::count(row.begin(), row.end(),1);
    }
    return num_o_site;
}

bool Percolation::percolates(){
    //int matrix_len=(int) matrix[0].size();
    int last_dummy_node_index = matrix_len* matrix_len +1  ;
    int last_second_dummy_node_index = matrix_len* matrix_len;
    return connect_matrix.connected(0,last_dummy_node_index);

}


 int cal_index_in_connect_matrix(int x, int y, int matrix_len){
        return x*matrix_len+y;
    }

PercolationStats::PercolationStats(int n, int trials){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, n-1);
    
   

    for (int i{0}; i<trials; ++i ){
        Percolation percolation_ins(n);
        
        
        
        while(!percolation_ins.percolates()){
            


            //Open a random site
            int x=distrib(gen);
            int y= distrib(gen);
            while(percolation_ins.isOpen(x,y) ){
                x=distrib(gen);
                y=distrib(gen);
            }
            percolation_ins.open(x,y);
            
            //Pay attention to the dummy node when 
            //Calculating the index in the connect_matrix
            int index_in_connect_matrix= cal_index_in_connect_matrix(x,y, percolation_ins.matrix_len);
            //Examine its 4 neighbour
            
            
            try{
                //std::cout<<"The first neighbour"<< std::endl;
                bool legal_site_open=percolation_ins.isOpen(x,y+1);
                
                if(legal_site_open){
                int neighbor_index_in_connect_matrix = cal_index_in_connect_matrix(x,y+1, percolation_ins.matrix_len);
                percolation_ins.connect_matrix.union2c(index_in_connect_matrix, neighbor_index_in_connect_matrix);
                }
            }catch(std::out_of_range){
                //Leave empty
                //If it is out of range then skip the union operation
            }

            try{
                //std::cout<<"The second neighbour"<< std::endl;
                bool legal_site_open=percolation_ins.isOpen(x,y-1);
                if(legal_site_open){
                int neighbor_index_in_connect_matrix = cal_index_in_connect_matrix(x,y-1, percolation_ins.matrix_len);
                percolation_ins.connect_matrix.union2c(index_in_connect_matrix, neighbor_index_in_connect_matrix);
                }
            }catch(std::out_of_range){
                //Leave empty
                //If it is out of range then skip the union operation
            }

            try{
                //std::cout<<"The third neighbour"<< std::endl;
                bool legal_site_open=percolation_ins.isOpen(x-1,y);
                if(legal_site_open){
                int neighbor_index_in_connect_matrix = cal_index_in_connect_matrix(x-1,y, percolation_ins.matrix_len);
                percolation_ins.connect_matrix.union2c(index_in_connect_matrix, neighbor_index_in_connect_matrix);
                }
            }catch(std::out_of_range){
                //Leave empty
                //If it is out of range then skip the union operation
            }

            try{
                //std::cout<<"The fourth neighbour"<< std::endl;
                bool legal_site_open=percolation_ins.isOpen(x+1,y);
                if(legal_site_open){
                int neighbor_index_in_connect_matrix = cal_index_in_connect_matrix(x+1,y, percolation_ins.matrix_len);
                percolation_ins.connect_matrix.union2c(index_in_connect_matrix, neighbor_index_in_connect_matrix);
                }
            }catch(std::out_of_range){
                //Leave empty
                //If it is out of range then skip the union operation
            }
            


        }
        
        
        
        double percolation_threshold (0);
        double num_open_site= percolation_ins.numberOfOpenSites();
        double total_site = percolation_ins.matrix_len * percolation_ins.matrix_len;
        //percolation_threshold = (percolation_ins.numberOfOpenSites()) /(percolation_ins.matrix_len * percolation_ins.matrix_len);
        percolation_threshold =num_open_site/total_site;
        
        trial_record.push_back(percolation_threshold);


    }
}

PercolationStats::~PercolationStats(){}

double PercolationStats::mean(){
    double sum_of_percolation_threshold = std::accumulate(trial_record.begin(), trial_record.end(), 0.0);
   /*  std::cout<<"What is the mean: "<< sum_of_percolation_threshold<<std::endl;
    for (auto item : trial_record){
        std::cout << "record: "<<item<<std::endl;
    } */
    double T =(double) trial_record.size();
    double mean_val= sum_of_percolation_threshold / T;
    return mean_val;

}

double PercolationStats::stddev(){
    double sum_of_square(0);
    double mean_val = mean();
    for (auto& record : trial_record){
        sum_of_square += (record-mean_val)*(record-mean_val);
    }
    double result = sum_of_square/( (int) trial_record.size() - 1);

    return result;

}

double PercolationStats::confidenceLo(){
    double mean_val = mean();
    double standard_s = std::sqrt(stddev());
    int T = (int) trial_record.size();
    double result = mean_val - 1.96*standard_s / (std::sqrt(T)); 
    return result;

}

double PercolationStats::confidenceHi(){
    double mean_val = mean();
    double standard_s = std::sqrt(stddev());
    int T = (int) trial_record.size();
    double result = mean_val + 1.96*standard_s / (std::sqrt(T)); 
    return result;


}
    