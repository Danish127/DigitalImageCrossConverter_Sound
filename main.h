/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.h
 * Author: pi
 *
 * Created on May 4, 2018, 4:15 PM
 */

#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

    
    //private:
    bool validNumOfArgs(int args, int min);
    char* flag;
    int getFlagIndex(char* flag);
    void handleHelp();
    void handleF2I(char** args);
    //void handleI2F(char** args);
    //void handleAIF(char** args);
    void handleError(int e);
    int findClosestSquare(long fSize);


#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */ 

