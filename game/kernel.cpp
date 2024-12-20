#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include <cstdarg>
#include <functional>
#include <string>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<future>
#include <chrono>

#include "game.h"
#include "player.h"

using namespace std;

#define moveRunTime 1 //in second

condition_variable cv;


class defer{
    function<void()> func_;
    public:
        defer(function<void()> func):
        func_(func){

        }
        ~defer() {
            func_();
        }
        defer& operator=(const defer&) = delete;
        defer(const defer&) = delete;
};

enum ERROR {WRONG_PATH, MISSING_ARG};

void Terminate(string token) {
    cout << token << endl;
    exit(0);
}

void Error(ERROR err) {
    switch(err) {
        case WRONG_PATH:
            Terminate("Wrong Path");
        case MISSING_ARG:
            Terminate("Missing Command Argument");
    }
}

void getMeta(char *path, vector<pair<int, int> > &bomb, pair<int, int> &mapSize) {
    ifstream in;
    in.open(path);
    if(!in) {
        Error(WRONG_PATH);
    }
    int tmp, cnt = 0;
    int _;
    in >> mapSize.first;
    in >> mapSize.second;
    while(in >> tmp) {
        if(cnt&1 == 0) _ = tmp;
        else bomb.push_back({_, tmp});
        cnt++;
    }
}

void playerMoveRunner(Player &player, pair<int, int> &res) {
    res = player.move();
    cv.notify_one();
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        Error(MISSING_ARG);
    }

    vector<pair<int, int> > bomb;
    pair<int, int> mapSize;
    getMeta(argv[1], bomb, mapSize);

    Player player = Player();
    Game game = Game(bomb, mapSize.first, mapSize.second);

    bool timeout = false;

    for(int i=0;i<2;i++) {

        pair<int, int> res;
        thread playerMoveTh(playerMoveRunner, ref(player), ref(res));

        mutex mtx;
        unique_lock<mutex> lck(mtx);
        timeout = ( cv.wait_for(lck, chrono::seconds(moveRunTime)) == cv_status::timeout );
        if(timeout) {
            playerMoveTh.detach();
            break;
        }
        playerMoveTh.join();

        cout << res.first << ' ' << res.second << endl;
    }

    if(timeout) cout << "timeout";

}