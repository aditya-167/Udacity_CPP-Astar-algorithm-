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
#include "board.h"

std::vector<std::vector<State>> Search(std::vector<std::vector<State>>board,int start[2],int goal[2]){
    std::vector<std::vector<int>> OpenList{};
    int x=start[0];
    int y=start[1];
    int g=0;
    int h=Heuristic(x,y,goal[0],goal[1]);
    AddToOpen(OpenList,x,y,g,h,board);
    while(OpenList.size()>0){
            CellSort(&OpenList);
            auto current=OpenList.back();
            OpenList.pop_back();
            x=current[0];
            y=current[1];
            board[x][y]=State::Path;
            if(x==goal[0] && y==goal[1]){
                board[start[0]][start[1]]=State::Start;
                board[goal[0]][goal[1]]=State::Finish;
                return board;
            }


            ExpandNeighbours(current,goal,OpenList,board);

    }
    std::cout<<"path Not found"<<std::endl;
    return std::vector<std::vector<State>> {};
}



bool compare(const std::vector<int> x,const std::vector<int> y){
    int f1=x[2]+x[3];
    int f2=y[2]+y[3];
    return f1>f2;
}

bool CheckValidCell(int x,int y,std::vector<std::vector<State>>&board){
bool on_x= (x>=0&&x<board.size());
bool on_y= (y>=0&&y<board.size());
if(on_x&&on_y)
    return board[x][y]==State::Free;
return false;
}

void ExpandNeighbours(std::vector<int>& current,int goal[2],std::vector<std::vector<int>>& OpenList,std::vector<std::vector<State>>& board){
    int x=current[0];
    int y=current[1];
    int g=current[2];
    for(int i=0;i<4;i++){
        int x2= x+Delta[i][0];
        int y2= y+Delta[i][1];
    if(CheckValidCell(x2,y2,board)){
        int g2=g+1;
        int h2=Heuristic(x2,y2,goal[0],goal[1]);
        AddToOpen(OpenList,x2,y2,g2,h2,board);
        }
    }
}

void CellSort(std::vector<std::vector<int>>* v){
std::sort(v->begin(),v->end(),compare);
}

int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

void AddToOpen(std::vector<std::vector<int>>& OpenList,int x,int y,int g, int h, std::vector<std::vector<State>>& board){
OpenList.push_back(std::vector<int>{x,y,g,h});
board[x][y]=State::Closed;
}



std::vector<State> ParseLine(std::string line){
    std::istringstream my_line(line);
    int n;
    char c;
    std::vector<State> row;
    while(my_line>>n>>c&&c==','){
        if (n==0)
            row.push_back(State::Free);
        else
            row.push_back(State::Obstacle);
    }
    return row;
}

void PrintBoard(std::vector<std::vector<State>> board){
for(int i=0;i<board.size();i++){
    for(int j=0;j<board[i].size();j++){
        std::cout<<CellState(board[i][j])<<" ";
    }
    std::cout<<std::endl;
}
}

char CellState(State cell){
    switch(cell){
    case(State::Obstacle): return (unsigned char)254;
    case(State::Path): return '/';
    case(State::Start): return 's';
    case(State::Finish): return 'f';
    default : return '0';
}

}

std::vector<std::vector<State>> readBoardFile(std::string path){
    std::ifstream my_file(path);
    std::vector<std::vector<State>> board;
	if (my_file) {

		std::string line;
		while (getline(my_file, line)) {
            std::vector<State> row=ParseLine(line);
            board.push_back(row);
		}
	}
	return board;

}



