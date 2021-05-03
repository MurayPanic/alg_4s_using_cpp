#include <iostream>
#include <filesystem>
#include <string>
#include <exception>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#ifndef PICTURE_HPP
#define PICTURE_HPP

//Class declaration
class Picture;

#endif


//Class definition
class Picture{

        public:
            	Picture();
            	Picture(std::string);
            	Picture(std::filesystem::path);
            	Picture(int, int);
            	Picture(Picture&);
            	~Picture();

            	bool operator==(Picture&);
		void operator=(const Picture&);
            	int height();
            	int width();
            	int getRGB(int, int);
		cv::Vec3b get(int, int);
            	void setRGB(int, int, int);
		void set(int, int, cv::Vec3b);
            	void show();
            	std::string toString();

	
		cv::Mat img_data;



};


//Constructor and deconstructor
Picture::Picture(){}

Picture::Picture(std::string img_file_name){
	
	std::string path_str = std::filesystem::current_path();
	path_str= path_str + "/"+ img_file_name;
	
	img_data = cv::imread(path_str);


}

Picture::Picture(std::filesystem::path img_file_path){


	std::string path_str = img_file_path;
	
	img_data = cv::imread(path_str);

};

Picture::Picture(int width, int height){
	this->img_data= cv::Mat::zeros(height, width, CV_8UC3);
};

Picture::Picture(Picture& that_pic_ins){
	this->img_data = that_pic_ins.img_data; 
};
Picture::~Picture(){};

//Operator
void Picture::operator=(const Picture& that_pic_ins){
	this->img_data = that_pic_ins.img_data;
}


bool Picture::operator==(Picture& that_pic_ins){

	if(this->img_data.empty() && that_pic_ins.img_data.empty()){
		return true;
	}

	if(this->img_data.cols != that_pic_ins.img_data.cols || this->img_data.rows != that_pic_ins.img_data.rows ){
		return false;
	}

	cv::Mat this_gray;
	cv::Mat that_gray;

	cv::cvtColor(this->img_data, this_gray, cv::COLOR_BGR2GRAY);
	cv::cvtColor(that_pic_ins.img_data, that_gray, cv::COLOR_BGR2GRAY);

		
	cv::Mat diff;
       	cv::compare(this_gray, that_gray, diff, cv::CMP_NE);
	int non_zero_num = cv::countNonZero(diff) ;

	return non_zero_num == 0;
}

//Member function:

void Picture::show(){
	std::string windows_name="Picture";
	cv::imshow(windows_name, this->img_data);
	cv::waitKey(0);

}

int Picture::height(){
	return this->img_data.rows;
}

int Picture::width(){
	return this->img_data.cols;

}

int Picture::getRGB(int col, int row){

	if(col > this->img_data.cols-1 || col<0 || row > this->img_data.rows-1 || row <0){
		throw std::invalid_argument("The provided coordination is out of range");
		
	}

	cv::Vec3b pixel_val= this->img_data.at<cv::Vec3b>(row,col);
	
	//Fomula provided by the website, it provides a RGB integer representation
	//int rgb = (r << 16) + (g << 8) + (b << 0)
	int rgb_rep = (pixel_val[2] << 16) + (pixel_val[1] << 8) + (pixel_val[0] <<0 );
	
	return rgb_rep;
	
}

cv::Vec3b Picture::get(int col, int row){


	if( col > this->img_data.cols-1|| col<0 || row > this->img_data.rows-1 ||row<0){
		throw std::invalid_argument("The provided coordination is out of range");
		
	}
	cv::Vec3b pixel_val= this->img_data.at<cv::Vec3b>(row,col);
	return pixel_val;

}

void Picture::setRGB(int col, int row, int rgb){
  	 int b = (rgb >>  0) & 0xFF;
  	 int g = (rgb >>  8) & 0xFF;
	 int r = (rgb >> 16) & 0xFF;

	 this->img_data.at<cv::Vec3b>(row,col)[0]=b;
	 this->img_data.at<cv::Vec3b>(row,col)[1]=g;
	 this->img_data.at<cv::Vec3b>(row,col)[2]=r;
}

void Picture::set(int col, int row, cv::Vec3b color){

	this->img_data.at<cv::Vec3b>(row,col)=color;
}

std::string Picture::toString(){
	std::string img_string="";
	int img_cols = this->width();
	int img_rows = this->height();
	for(int row{0}; row<img_rows; ++row){
		for(int col{0}; col<img_cols; ++col){
			int pixel_val = this->getRGB(col, row);
			std::string pixel_str = std::to_string(pixel_val);
			img_string+=pixel_str;
			if(col!= img_cols-1 ){
				img_string+=",";
			}else{
				img_string+="\n";
			}
		
		}
	}

	return img_string;
}

