#include<iostream>
#include "percolation.hpp"


void conduct_an_percolation_exp(int n, int trials){
    std::cout<<"Now conduct experiment on "<< n <<" times " <<n << " grids "
             <<" for "<< trials <<" times "<< std::endl;

    PercolationStats PS_ins(n, trials);
    std::cout<<"mean = "<<PS_ins.mean()<<std::endl;
    std::cout<<"stddev = "<<PS_ins.stddev()<<std::endl;
    std::cout<<"95% confidence intervarl = ["<<PS_ins.confidenceLo()
            <<", "<< PS_ins.confidenceHi() <<"]" <<std::endl;
}


int main(){

    std::cout<<"This file is to conduct the percolation experiment"<< std::endl;
    conduct_an_percolation_exp(200,100);
    conduct_an_percolation_exp(200,100);
    conduct_an_percolation_exp(2,10000);
    conduct_an_percolation_exp(2,100000);
    return 0;
}