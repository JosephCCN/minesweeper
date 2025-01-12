#include<utility>
#include<thread>
#include<chrono>
#include<iostream>
#include "player.h"
using namespace std;

bool first = true;
int w, h;

void Player::init(int width, int height) {
    w = width;
    h = height;
}

pair<int, int> Player::move(int** board, bool &flag) {
    //TODO
    flag = true;
    if(first) {
        first = false;
        return {1, 1};
    }
    return {2, 2};
}