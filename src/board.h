"""
Created on Thu Feb 13 03:05:18 2020

@author: Aditya Srichandan
"""
#ifndef BOARD_H_
#def BOARD_H_

#include<vector>
#include<string>
#include<iostream>

enum class State {Free,Obstacle,Closed,Path,Start,Finish};
char CellState(State);
std::vector<State> ParseLine(std::string);
std::vector<std::vector<State>> readBoardFile(std::string);
std::vector<std::vector<State>> Search(std::vector<std::vector<State>>,int[2],int[2]);
void PrintBoard(std::vector<std::vector<State>>);
int Heuristic(int,int,int,int);
void AddToOpen(std::vector<std::vector<int>>&,int,int,int, int, std::vector<std::vector<State>>&);
void CellSort(std::vector<std::vector<int>>*);
bool compare(const std::vector<int>,const std::vector<int>);
void ExpandNeighbours(std::vector<int>&,int[2],std::vector<int>&,std::vector<std::vector<State>>&);
int Delta[4][2]{{-1,0},{0,-1},{1,0},{0,1}};
bool CheckValidCell(int,int,std::vector<std::vector<State>>&);

#endif
