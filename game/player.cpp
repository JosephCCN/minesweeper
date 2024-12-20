#include<utility>
#include<thread>
#include<chrono>
#include "player.h"
using namespace std;

bool first = true;

pair<int, int> Player::move() {
    //TODO

    if(first) first = false;
    else this_thread::sleep_for(chrono::seconds(2));

    return {1, 1};
}