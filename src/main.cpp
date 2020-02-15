"""
Created on Thu Feb 13 03:05:18 2020

@author: Aditya Srichandan
"""

#include<algorithm>
#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<fstream>
#include"board.h"

int main() {
    std::vector<std::vector<State>> my_board=readBoardFile("board.txt");
    int start[2] {0,1};
    int goal[2] {4,3};
    std::vector<std::vector<State>>Solution = Search(my_board,start,goal);
    PrintBoard(Solution);
    return  0;
}
