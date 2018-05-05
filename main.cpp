/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pi
 *
 * Created on May 4, 2018, 3:57 PM
 */

#include <cstdlib>
#include <string.h>
#include <fstream>
#include <math.h>
#include "main.h"
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    std::cout << argv[0];
    validNumOfArgs(argc, 2);
    flag = argv[1];
    switch (getFlagIndex(flag)) {
        case 0:
            handleHelp();
            break;
        case 1:
            validNumOfArgs(argc, 4);
            handleF2I(argv);
            break;
        case 2:
            validNumOfArgs(argc, 4);
            //handleI2F(argv);
            break;
        case 3:
            validNumOfArgs(argc, 5);
            //handleAIF(argv);
            break;
        case -1:
            handleError(2);
            break;
    }


    //std::string arg1 = argv[1];
    //std::string arg2 = argv[2];


    return 0;
}

bool validNumOfArgs(int args, int min) {

    if (args < min) {
        handleError(1);
        return false;
        
    }
    return true;
}

int getFlagIndex(char* flag){
    if(strcmp(flag, "-h") == 0){
        return 0;
    }
    if(strcmp(flag, "-f2i") == 0){
        return 1;
    }
    if(strcmp(flag, "-i2f") == 0){
        return 2;
    }
    if(strcmp(flag, "-aif") == 0){
        return 3;
    }
    return -1;
}

void handleHelp(){
    std::cout << "Currently supported flags:" << std::endl;
    std::cout << "-h \tDisplays help" << std::endl;
    std::cout << "-f2i \tConverts a file into an image\n\t\tUse -f2i sourceFilepath destFilepath" << std::endl;
    std::cout << "-i2f \tConverts an image into a file\n\t\tUse -i2f sourceFilepath destFilepath" << std::endl;
    std::cout << "-aif \tApplies an image filter\n\t\tUse -aif sourceFilepath filterFilepath destFilepath" << std::endl;
}

void handleF2I(char** args){
    char* sourceFilepath = args[2];
    char* destFilepath = args[3];
    
    ifstream sourceFile(sourceFilepath);
    //sourceFile.open(sourceFilepath);
    if(!sourceFile){
        handleError(3);
    }
    
    streampos begin,end;
    
    begin = sourceFile.tellg();
    sourceFile.seekg (0, ios::end);
    end = sourceFile.tellg();
    long fSize = (end-begin);
    
    
    int dimentions = findClosestSquare(fSize);
    std::cout << dimentions;
    cv::Mat img(dimentions/2, dimentions/2, CV_32F);
    int color = 0;
    for (int y = 0; y < dimentions/2; y++){
        for(int x = 0; x < dimentions/2; x++){
            
            //sourceFile >> color;
            color = x+y;
            img.at<cv::Vec2d>(cv::Point(x,y)) = color;
        }
    }
    
    cv::imshow(sourceFilepath, img);
    
}

void handleError(int e){
    std::string errorDescriptor = "";
    switch(e){
        case 1:
            errorDescriptor = "too few arguments";
            break;
        case 2:
            errorDescriptor = "unknown flag";
            break;
        case 3:
            errorDescriptor = "source file not valid";
            break;
    }
    std::cout << "ERROR ";
    std::cout << e;
    std::cout << ": ";
    std::cout << errorDescriptor;
    std::cout << std::endl << "Use -h for help" << std::endl;
            
    std::exit(0);
}

int findClosestSquare(long fileSize){
    float root = sqrt(fileSize);
    return ceil(root);
}