#include <iostream>
#include "gtest/gtest.h"

#define private public
    #include "Picture.hpp"
#undef private

#define GTEST_COUT std::cout<<"[CUSTOM INFO] "
#define GTEST_LINE_HEADER "[          ] "

TEST(Picture_constructor, case_1){
	Picture PIC_ins{};
}


TEST(Picture_constructor, case_2){
	std::string img_file_name="porsche.jpg";
	Picture PIC_ins(img_file_name);
	//PIC_ins.show();
	

}

TEST(Picture_constructor, case_3){
	std::string path_str= std::filesystem::current_path();
	path_str = path_str + "/"+ "porsche.jpg";
	std::filesystem::path file_path(path_str);
	Picture PIC_ins(file_path);
	//PIC_ins.show();

}

TEST(Picture_constructor, case_4){
	Picture PIC_ins(600,800);
	//PIC_ins.show();
}

TEST(Pictuce_constructor, case_5){
	std::string path_str= std::filesystem::current_path();
	path_str = path_str + "/"+ "porsche.jpg";
	std::filesystem::path file_path(path_str);
	Picture PIC_ins(file_path);

	Picture PIC_ins_2(PIC_ins);
	//PIC_ins_2.show();
}


TEST(Pictuce_assign_operator, case_1){
	std::string path_str= std::filesystem::current_path();
	path_str = path_str + "/"+ "porsche.jpg";
	std::filesystem::path file_path(path_str);
	Picture PIC_ins(file_path);

	Picture PIC_ins_2{};
	PIC_ins_2 = PIC_ins;
	//PIC_ins_2.show();
}


TEST(Picture_equal_operator, case_1){

	std::string path_str= std::filesystem::current_path();
	path_str = path_str + "/"+ "porsche.jpg";
	std::filesystem::path file_path(path_str);
	Picture PIC_ins(file_path);

	Picture PIC_ins_2{};
	PIC_ins_2 = PIC_ins;
	bool equal_or_not= PIC_ins==PIC_ins_2 ;
	EXPECT_TRUE(equal_or_not);
	
	Picture PIC_ins_3(300,400);
	EXPECT_FALSE(PIC_ins == PIC_ins_3);
}

TEST(Picture_equal_operator, case_2){
	Picture PIC_ins(400,300);
	Picture PIC_ins_2(400,300);
	EXPECT_TRUE(PIC_ins == PIC_ins_2);

}

TEST(Picture_height, case_1){

	Picture PIC_ins(400,300);
	EXPECT_EQ(PIC_ins.height(), 300);
}

TEST(Picture_width, case_1){
	Picture PIC_ins(400,300);

	EXPECT_EQ(PIC_ins.width(), 400);
}

TEST(Picture_getRGB, case_1){
	Picture PIC_ins(300,400);
	int pixel_1= PIC_ins.getRGB(0,0);
	EXPECT_EQ(pixel_1, 0);
}

TEST(Picture_getRGB, case_2){
	std::string img_file_name="porsche.jpg";
	Picture PIC_ins(img_file_name);
	int pixel_1= PIC_ins.getRGB(0,0);
	GTEST_COUT<< "Pixel_1 value: " <<pixel_1<<std::endl;
	EXPECT_NE(pixel_1, 0);
}


TEST(Picture_getRGB, case_3){
	Picture PIC_ins(400,300);
	
	EXPECT_THROW(PIC_ins.getRGB(300,400), std::invalid_argument);

	EXPECT_THROW(PIC_ins.getRGB(400,300), std::invalid_argument);
}

TEST(Picture_get, case_1){
	std::string img_file_name="porsche.jpg";
	Picture PIC_ins(img_file_name);
	int pixel_1= PIC_ins.getRGB(0,0);
	GTEST_COUT<< "Pixel_1 value: " <<pixel_1<<std::endl;
	EXPECT_NE(pixel_1, 0);
	auto pixel_1_3_channels = PIC_ins.get(0,0);
	for(int i =0; i<3;++i){
		GTEST_COUT<<"The "<<i<<" channel: "<< (int)pixel_1_3_channels[i]
			<<std::endl;
	}
}

TEST(Picture_toString, case_1){

	Picture PIC_ins(10,20);
	
	GTEST_COUT << "The picture matrix is:"<<std::endl
		<<PIC_ins.toString() << std::endl;

}

int main(int argc, char* argv[]){

    std::cout<< "This script is to test the Picture head file"
            <<std::endl;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
