#include<vector>
#include<utility>
#include <stdexcept>
#include<iostream>

#include "model.h"
#include "error_code.h"

using namespace std;

int dy[3] = {-1, 1, 0};
int dx[3] = {-1, 1, 0};

void game::update_show_board(int x, int y) {
    if(x <= 0 || y <= 0 || x > max_x || y > max_y) return;

    show_board[x][y] = board[x][y];
    if(board[x][y] > 0) return;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(show_board[x + dx[i]][y + dy[j]] == UNSHOWN) {
                update_show_board(x + dx[i], y + dy[j]);
            }
        }
    } 
} 

game::game(vector<pair<int, int> > mine, int a, int b) {
    for(auto x:mine) {
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                board[x.first + dx[i]][x.second + dy[j]]++;
            }
        } 
    }
    for(auto x:mine) board[x.first][x.second] = BOMB;
    for(int i=1;i<=a;i++)
        for(int j=1;j<=b;j++)
            show_board[i][j] = UNSHOWN;
    max_x = a;
    max_y = b;
}

bool game::check_bomb(int x, int y) {
    valid_move(x, y);
    return board[x][y] == BOMB;
}

void game::click(int x, int y) {
    increment_move();
    valid_move(x, y);
    if(board[x][y] == BOMB) GameLoss(); //left to be handled
    if(show_board[x][y] != UNSHOWN) return;
    update_show_board(x, y);
}

void game::increment_move() {
    move++;
}

void game::sb() {
    for(int i=1;i<=max_x;i++) {
        for(int j=1;j<=max_y;j++) 
            cout << show_board[i][j] << ' ';
        cout << endl;
    }
}

void game::b() {
    for(int i=1;i<=max_x;i++){
        for(int j=1;j<=max_y;j++) 
            cout << board[i][j] << ' ';
        cout << endl;
    }
}

void game::Error(int code) {
    string token;
    switch(code){
        case INVALID_MOVE:
            token = "Error " + to_string(code) + ": Invalid Move on move " + to_string(move);
            break;
        default:
            token = "unknown error";
    }
    game_terminate(token);
}

void game::GameLoss() {
    game_terminate("Game loss on move " + to_string(move));
}

bool game::valid(int x, int y) {
    return (1 <= x && x <= max_x && 1 <= y && y <= max_y);
}

void game::valid_move(int x, int y) {
    if(!valid(x, y)) Error(INVALID_MOVE);
}

void game::game_terminate(string token){
    cout << token << endl;
    exit(0);
}