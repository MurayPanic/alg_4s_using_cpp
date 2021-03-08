#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

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
            std::vector<int > findHorizontalSeam();
            std::vector<int > findVerticalSeam();
            void removeHorizontalSeam( std::vector<int>);
            void removeVerticalSeam( std::vector<int> );

 	private:
	    Picture pic_data;
	    cv::Mat energy_map;
	    void genEnergyMap();
	    double calPixelEnergy(int, int);
	    bool validateCoordinate(int, int);
		
            

};

//Constructor and deconstructor
SeamCarver::SeamCarver(){}

SeamCarver::SeamCarver(Picture PIC_ins): pic_data(PIC_ins){
	this->genEnergyMap();
	
}

SeamCarver::~SeamCarver(){ }

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

void SeamCarver::genEnergyMap(){
	this->energy_map= cv::Mat::zeros(this->pic_data.height(),this->pic_data.width(), CV_64F);

	for(int row{0}; row< this->pic_data.height(); ++row){
		for(int col{0}; col< this->pic_data.width(); ++col){
			double tmp_energy= this->calPixelEnergy(row, col);
			this->energy_map.at<double>(row, col) = tmp_energy; 
		
		}
	
	}
	

}

double SeamCarver::calPixelEnergy(int row, int col){
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

std::vector<int > SeamCarver::findVerticalSeam(){

		std::vector<int > vertical_seam{}; 
		
		cv::Mat distTo= cv::Mat::zeros(this->pic_data.height(), this->pic_data.width(), CV_64FC1);
		cv::Mat pixelTo= cv::Mat::zeros(this->pic_data.height(), this->pic_data.width(), CV_32S );

		for(int row{0}; row< this->pic_data.height(); ++row){
			
			for(int col={0}; col< this->pic_data.width(); ++col){
				//std::cout<<"Now handle pixel: ("<<row<<","<<col<<")"<<std::endl;
				
				if(row==0){
					distTo.at<double>(row,col) =  this->energy(col, row);
					pixelTo.at<int>(row, col) = 0;
					continue;
				}

				
				distTo.at<double>(row, col) = this->energy(col, row);
				//std::cout<<"The wrighten energy is: "<<distTo.at<double>(row, col)<<std::endl;

				//validate the pixel corodinates for previous points (x-1, y-1) (x-1, y-1),(x+1, y-1)
				//find out the shortest length from previous point

				double dist_topleft= DBL_MAX;  //distance of previous point (row-1, col-1)
				double dist_top = DBL_MAX;	//distance of previous point (row-1, col)
				double dist_topright = DBL_MAX; //distance of previous point (row-1, col+1)
				
				if(this->validateCoordinate(row-1, col-1 )){
					dist_topleft= distTo.at<double>( row-1,col-1);
					//std::cout<<"find valid topleft: "<<dist_topleft<<std::endl;
					
				}

				if(this->validateCoordinate(row-1, col )){
					dist_top= distTo.at<double>(row-1, col);
					//std::cout<<"find valid top:"<< dist_top<<std::endl;
				}

				if(this->validateCoordinate(row-1, col+1 )){
					dist_topright= distTo.at<double>(row-1, col+1);
					//std::cout<<"find valid topright"<< dist_topright<<std::endl;
				}
				
				std::vector<double> dist_vec{dist_topleft, dist_top, dist_topright};
				

				auto tmp_distTo_iter= std::min_element(dist_vec.begin(), dist_vec.end());
				

				
				/*
				std::cout<<"The dist vec is:";
				for(auto item: dist_vec){
					std::cout<<item<< " ";
				}
				std::cout<<std::endl;
				
				
				std::cout<<"The minimum dist is"<< (*tmp_distTo_iter)<<std::endl;
				*/

				int tmp_pixelTo = std::distance(dist_vec.begin(), tmp_distTo_iter);
				

				distTo.at<double>(row,col) +=  (*tmp_distTo_iter);
				
				//std::cout<<"The final energy is: "<<distTo.at<double>(row, col)<<std::endl;

				
				
				
				pixelTo.at<int>(row, col) = tmp_pixelTo==0  ?  -1  :  (tmp_pixelTo==1 ? 0 : 1 );

				//std::cout<<"The Pixel to is is: "<<pixelTo.at<int>(row, col)<<std::endl;
				
			}
		}
	
		//Debug output
		/*
		for(int row{0}; row< this->pic_data.height(); ++row){
			for(int col{0}; col< this->pic_data.width(); ++col){
				std::cout<<" Target pixel: ("<<row<<","<<col<<")"<<":"
						<<"distTo: "<<distTo.at<double>(row,col)
						<<" PixelTo: "<<pixelTo.at<int>(row, col) 
						<<" Energy: "<< this->energy(col, row)
				<<std::endl;
				

			}
			
		}
		*/


		//find minimum energy
		
		std::vector<double> last_row_in_distTo{};
		int last_row_index = this->height()-1;

		for (int col{0}; col< this->width(); ++col){
				last_row_in_distTo.push_back( distTo.at<double>(last_row_index, col) );
		}
		
		auto min_energy_pos= std::min_element(last_row_in_distTo.begin(), last_row_in_distTo.end() );

		auto end_point_col= std::distance(last_row_in_distTo.begin(), min_energy_pos);

		//Find the seam
		int tmp_col = end_point_col;
		int tmp_row = last_row_index;

		for(tmp_row; tmp_row>=0; --tmp_row){
			
			vertical_seam.push_back(tmp_col);
			tmp_col += pixelTo.at<int>(tmp_row,tmp_col);
		}






		
		

		//Obtain the vertical seam from the distTo img
		
		return vertical_seam;


}


std::vector< int > SeamCarver::findHorizontalSeam(){
	//Transpose the image and re-calculate the energy map
	cv::transpose(this->pic_data.img_data, this->pic_data.img_data);
	this->genEnergyMap();

	//Use findVerticalSeam to get the seam
	auto horizontal_seam = this->findVerticalSeam();

	//Transpose the image and re-calculate the energy map
	cv::transpose(this->pic_data.img_data, this->pic_data.img_data);
	this->genEnergyMap();

	return horizontal_seam;
}



void SeamCarver::removeVerticalSeam(std::vector<int> vertical_seam){
	//check if it is a valid seam
	if(vertical_seam.size()!= this->height()){
		throw std::invalid_argument("The provided seam does not have valid length");
	}

	//Remove the seam by shifting one pixel to the left
	
	
	int row = this->height()-1;
	int last_col = this->width()-1;



	for(auto col: vertical_seam){
		for(int tmp_col=col; tmp_col<last_col;  ++tmp_col){
			this->pic_data.img_data.at<cv::Vec3b>(row, tmp_col)=
				this->pic_data.img_data.at<cv::Vec3b>(row, tmp_col+1);
		}
		--row;
	}

	//Cut the image
	cv::Mat seam_removed_image = this->pic_data.img_data.colRange(0, this->width()-2).clone();

	this->pic_data.img_data= seam_removed_image;

	//Recalculate the energy	
	this->genEnergyMap();

}


void SeamCarver::removeHorizontalSeam(std::vector<int> horizontal_seam){

	//Transpose the image
	cv::transpose(this->pic_data.img_data, this->pic_data.img_data);


	//Use removeVerticalSeam to remove the seam
	this->removeVerticalSeam(horizontal_seam);

	//Transpose the image and re-calculate the energy map
	cv::transpose(this->pic_data.img_data, this->pic_data.img_data);
	this->genEnergyMap();
}

bool SeamCarver::validateCoordinate(int row, int col){

	if(  0<=row && row< this->height() && 0<=col  && col < this->width()){
		return true;
	}else{
		return false;
	}

}
