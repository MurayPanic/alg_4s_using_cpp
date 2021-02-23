#include <iostream>
#include <filesystem>
#include <string>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/viz/types.hpp>

#ifndef PICTURE_HPP
#define PICTURE_HPP

//Class declaration
class Picture;

#endif


class Picture{

        public:
            Picture();
            Picture(std::string);
            Picture(std::filesystem::path);
            Picture(int, int);
            Picture(Picture&);
            ~Picture();

            bool operator=(Picture&);
            int getRGB(int, int);
            void setRGB(int, int, int);
            int height();
            int width();
            void show();
            std::string toString();
            



};