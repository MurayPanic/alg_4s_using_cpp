#include <iostream>
#include "gtest/gtest.h"

#define private public
    #include "SeamCarver.hpp"
#undef private

#define GTEST_COUT std::cout<< "[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[         ] "

TEST(SeamCarver_constructor, case_1){
	SeamCarver SC_ins{};
}

TEST(SeamCarver_constructor, case_2){

	std::string img_file_name="porsche.jpg";
	Picture PIC_ins(img_file_name);
	SeamCarver SC_ins(PIC_ins);

}

TEST(SeamCarver_picture, case_1){
	Picture PIC_ins(400,300);
	SeamCarver SC_ins(PIC_ins);
	auto PIC_member = SC_ins.picture();
	EXPECT_TRUE(PIC_member==PIC_ins);

}

TEST(SeamCarver_width, case_1){
	Picture PIC_ins(400,300);
	SeamCarver SC_ins(PIC_ins);
	EXPECT_EQ(SC_ins.width(),400);
}

TEST(SeamCarver_height, case_1){
	Picture PIC_ins(400,300);
	SeamCarver SC_ins(PIC_ins);
	EXPECT_EQ(SC_ins.height(),300);
}

TEST(SeamCarver_cal_pixel_energy, cast_1){

	std::string img_file_name="surfing.png";
	Picture PIC_ins(img_file_name);
	SeamCarver SC_ins(PIC_ins);

	double energy_1 = SC_ins.cal_pixel_energy(0,0);
	GTEST_COUT << "The energy at (0,0) is " << energy_1 <<std::endl;

	double energy_2 = SC_ins.cal_pixel_energy(80,60);
	GTEST_COUT << "The energy at (80,60) is " << energy_2 <<std::endl;

}

TEST(SeamCarver_cal_pixel_energy, cast_2){

	std::string img_file_name="surfing.png";
	Picture PIC_ins(img_file_name);
	SeamCarver SC_ins(PIC_ins);

	auto pixel_left = SC_ins.pic_data.get(59,80);
	GTEST_COUT<< "Pixel left val: "<< std::to_string(pixel_left[0])<<","
		  <<std::to_string( pixel_left[1] )<<","
		  <<std::to_string( pixel_left[2] ) <<std::endl;
	
	auto pixel_right = SC_ins.pic_data.get(61,80);
	GTEST_COUT<< "Pixel right val: "<< std::to_string(pixel_right[0])<<","
		  <<std::to_string( pixel_right[1] )<<","
		  <<std::to_string( pixel_right[2] ) <<std::endl;

	double x_gradient_square = std::pow(pixel_left[0]- pixel_right[0],2) +
				std::pow(pixel_left[1]- pixel_right[1],2) +
				std::pow(pixel_left[2]- pixel_right[2],2) ;
	GTEST_COUT<<"X gradient square: " << x_gradient_square <<std::endl;


	auto pixel_up = SC_ins.pic_data.get(60,81);
	GTEST_COUT<< "Pixel up val: "<< std::to_string(pixel_up[0])<<","
		  <<std::to_string( pixel_up[1] )<<","
		  <<std::to_string( pixel_up[2] ) <<std::endl;
	
	auto pixel_down = SC_ins.pic_data.get(60,79);
	GTEST_COUT<< "Pixel down val: "<< std::to_string(pixel_down[0])<<","
		  <<std::to_string( pixel_down[1] )<<","
		  <<std::to_string( pixel_down[2] ) <<std::endl;

	double y_gradient_square = std::pow(pixel_up[0]- pixel_down[0],2) +
				std::pow(pixel_up[1]- pixel_down[1],2) +
				std::pow(pixel_up[2]- pixel_down[2],2) ;
	GTEST_COUT<<"Y gradient square: " << y_gradient_square<<std::endl;;

	double expect_total_energy = std::sqrt(x_gradient_square + y_gradient_square);
	GTEST_COUT<< "Expect total energy: " << expect_total_energy<<std::endl;
				

	double energy_2 = SC_ins.cal_pixel_energy(80,60);
	GTEST_COUT << "The energy at (80,60) is " << energy_2 <<std::endl;

	EXPECT_EQ(expect_total_energy, energy_2);

}
TEST(SeamCarver_energy, case_1){

	std::string img_file_name="surfing.png";
	Picture PIC_ins(img_file_name);
	SeamCarver SC_ins(PIC_ins);

	double energy_1 = SC_ins.energy(0,0);
	GTEST_COUT << "The energy at (0,0) is " << energy_1 <<std::endl;

	double energy_2 = SC_ins.energy(60,80);
	GTEST_COUT << "The energy at (80,60) is " << energy_2 <<std::endl;
}


TEST(SeamCarver_show_energy_map, case_1){

	std::string img_file_name="surfing.png";
	Picture PIC_ins(img_file_name);
	SeamCarver SC_ins(PIC_ins);

	auto energy_map = SC_ins.energy_map;

	
	int i=0;
	for(auto iter =energy_map.begin<double>(); iter!=energy_map.end<double>(); ++iter){
		double energy_val = *iter;
		//*iter = energy_val* 0 +0.5;
		if( energy_val >255 && energy_val!=1000){
		GTEST_COUT<<"The original energy value is:" << energy_val<< std::endl;
		//GTEST_COUT<<"The revised energy value is: "<< *iter <<std::endl;
		++i;
		}
	}
	GTEST_COUT<<"Pixel that have energy larger than 255:" <<i<<std::endl;

	

	cv::imshow("Energy Map", energy_map);
	cv::waitKey(0);

	cv::Mat energy_img;
	energy_map.convertTo(energy_img, CV_8U);
	cv::imshow("Energy image", energy_img);
	cv::waitKey(0);
}

/*
TEST(SeamCarver_show_energy_map, case_2){

	Picture PIC_ins(300,400);
	SeamCarver SC_ins(PIC_ins);

	auto energy_map = SC_ins.energy_map;
	
	for(auto iter =energy_map.begin<float>(); iter!=energy_map.end<float>(); ++iter){
		double energy_val = *iter;
		*iter = (int)energy_val % 255;
		GTEST_COUT<<"The revised energy value is: "<< energy_val<<std::endl;
	}

	//cv::imshow("Energy Map", energy_map);
	//cv::waitKey(0);
}
*/
int main(int argc, char* argv[]){

    std::cout<<"This script is to test the SeamCarver head file"
            <<std::endl;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
