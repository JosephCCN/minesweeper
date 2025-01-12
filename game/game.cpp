#include<vector>
#include<utility>
#include <stdexcept>
#include<iostream>

#include "game.h"

using namespace std;

int dy[3] = {-1, 1, 0};
int dx[3] = {-1, 1, 0};

void Game::update_show_board(int x, int y) {
    if(x <= 0 || y <= 0 || x > width || y > height) return;

    show_board[x][y] = board[x][y];
    if(board[x][y] != EMPTY) return; // stop update show_board if the grid is not empty

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(show_board[x + dx[i]][y + dy[j]] == UNSHOWN) {
                update_show_board(x + dx[i], y + dy[j]);
            }
        }
    } 
} 

Game::Game(vector<pair<int, int> > mine, int a, int b) {
    // calculate near bomb
    for(auto x:mine) {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                board[x.first + dx[i]][x.second + dy[j]]++;
            }
        } 
    }
    // set bomb location
    for(auto x:mine) board[x.first][x.second] = BOMB;

    //init show_board
    for(int i=1;i<=a;i++)
        for(int j=1;j<=b;j++)
            show_board[i][j] = UNSHOWN;

    width = a;
    height = b;
    bombRemain = mine.size();
    gameState.code = PLAYING;
    gameState.token = "";
}

bool Game::check_bomb(int x, int y) {
    valid_move(x, y);
    return board[x][y] == BOMB;
}

void Game::click(int x, int y) {
    increment_move();
    valid_move(x, y);
    if(show_board[x][y] != UNSHOWN || show_board[x][y] == FLAG) Error(DOUBLE_CLICK);
    if(board[x][y] == BOMB) {
        if(move == 1) { // first move will never click on a bomb
            for(int i=0;i<3;i++) {
                for(int j=0;j<3;j++) {
                    if(board[x + dx[i]][y + dy[j]] != BOMB) {
                        board[x + dx[i]][y + dy[j]] = max(0, board[x + dx[i]][y + dy[j]]--);
                    }
                }
            }
        }
        else {
            GameLoss();
            return;
        }
    }
    update_show_board(x, y);
}

//first flag call will put a flag on (@x, @y), second flag call will remove the flag on (@x, @y)
void Game::flag(int x, int y) {
    increment_move();
    valid_move(x, y);
    if(show_board[x][y] == FLAG) {
        show_board[x][y] = UNSHOWN;
        if(board[x][y] == BOMB) bombRemain++; //unflag a bomb grid
    }
    else if(show_board[x][y] == UNSHOWN) {
        show_board[x][y] = FLAG;
        if(board[x][y] == BOMB) bombRemain--; //flag a bomb grid
    }
    else{ //not flagged or unshown
        Error(DOUBLE_CLICK);
    }
    if(bombRemain == 0) setState(WIN, "Game Win and Finish on move " + to_string(move)); 
}

void Game::increment_move() {
    move++;
}

void Game::Error(ERROR_CODE code) {
    string token = "";
    switch(code){
        case INVALID_MOVE:
            token = "Error " + to_string(code) + ": Invalid Move on move " + to_string(move);
            break;
        case DOUBLE_CLICK:
            token = "Error " + to_string(code) + ": Double click on move " + to_string(move);
    }
    setState(ERROR_END, token);
}

void Game::GameLoss() {
    setState(LOSS, "Game loss on move " + to_string(move));
}

bool Game::valid(int x, int y) {
    return (1 <= x && x <= width && 1 <= y && y <= height);
}

void Game::valid_move(int x, int y) {
    if(!valid(x, y)) Error(INVALID_MOVE);
}

void Game::setState(STATE_CODE code, string token){
    this->gameState.code = code;
    this->gameState.token = token;
}

State Game::getState() {
    return this->gameState;
}

bool Game::isWin() {
    return this->gameState.code == WIN;
}

bool Game::isPlaying() {
    return this->gameState.code == PLAYING;
}

bool Game::isLoss() {
    return this->gameState.code == LOSS;
}

bool Game::isError() {
    return this->gameState.code == ERROR_END;
}

string Game::report() {
    return this->gameState.token;
}

int Game::getMove() {
    return this->move;
}

void Game::getShowBoard(int** playerBoard) {
    for(int i=1;i<=width;i++) {
        for(int j=1;j<=height;j++) playerBoard[i][j] = show_board[i][j];
    }
}

#ifndef IOSTREAM_INCLUDED
void Game::sb() {
    for(int i=1;i<=width;i++) {
        for(int j=1;j<=height;j++) 
            cout << show_board[i][j] << ' ';
        cout << endl;
    }
}

void Game::b() {
    for(int i=1;i<=width;i++){
        for(int j=1;j<=height;j++) 
            cout << board[i][j] << ' ';
        cout << endl;
    }
}
#endif