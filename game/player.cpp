#include<utility>
#include<thread>
#include<chrono>
#include<iostream>
#include "player.h"
using namespace std;

bool first = true;

pair<int, int> Player::move(int** board, bool &flag) {
    //TODO
    // cout << board[1][1] << endl;
    // flag = true;
    if(first) {
        first = false;
        return {1,2};
    }
    flag = true;
    return {1, 1};
}