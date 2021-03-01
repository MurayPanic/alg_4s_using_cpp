#include <iostream>
#include <vector>
#include <cmath>

#include "Picture.hpp"

#ifndef SEAMCARVER_HPP
#define SEAMCARVER_HPP

//Class declaration
class SeamCarver;

#endif

//Class definition

class SeamCarver{

        public:
            SeamCarver();
            SeamCarver(Picture);
            ~SeamCarver();
            Picture picture();
            int width();
            int height();
            double energy(int, int);
            std::vector<int> findHorizontalSeam();
            std::vector<int> findVerticalSeam();
            void removeHorizontalSeam( std::vector<int>);
            void removeVerticalSeam( std::vector<int> );

 	private:
	    Picture pic_data;
	    cv::Mat energy_map;
	    void gen_energy_map();
	    double cal_pixel_energy(int, int);
            

};

//Constructor and deconstructor
SeamCarver::SeamCarver(){}

SeamCarver::SeamCarver(Picture PIC_ins): pic_data(PIC_ins){
	this->gen_energy_map();
}

SeamCarver::~SeamCarver(){}

//Member function
Picture SeamCarver::picture(){
	Picture PIC_ins = this->pic_data;
	return PIC_ins;
}

int SeamCarver::width(){
	return this->pic_data.width();
}

int SeamCarver::height(){
	return this->pic_data.height();
}

double SeamCarver::energy(int x, int y){
	//x is the column
	//y is the row
	return this->energy_map.at<double>(y,x);

}

void SeamCarver::gen_energy_map(){
	this->energy_map= cv::Mat::zeros(this->pic_data.height(),this->pic_data.width(), CV_64F);

	for(int row{0}; row< this->pic_data.height(); ++row){
		for(int col{0}; col< this->pic_data.width(); ++col){
			double tmp_energy= this->cal_pixel_energy(row, col);
			this->energy_map.at<double>(row, col) = tmp_energy; 
		
		}
	
	}
	

}

double SeamCarver::cal_pixel_energy(int row, int col){
	double total_energy{0};

	cv::Vec3b pixel_center = this->pic_data.get(col, row);


	double x_gradient;
	double y_gradient;
	try{
		//calculate x-gradient
		cv::Vec3b pixel_left = this->pic_data.get( col-1,row);
		cv::Vec3b pixel_right = this->pic_data.get(col+1,row);	
		x_gradient = cv::norm(pixel_left, pixel_right, cv::NORM_L2); 

		//calculate y-gradient
		cv::Vec3b pixel_up = this->pic_data.get( col,row+1);
		cv::Vec3b pixel_down = this->pic_data.get(col,row-1);	
		y_gradient = cv::norm(pixel_up, pixel_down, cv::NORM_L2);

		total_energy= std::sqrt( std::pow(x_gradient,2) + std::pow(y_gradient,2) );
	}catch(std::invalid_argument e){
		total_energy=1000.0;
	}

	return total_energy;
}
