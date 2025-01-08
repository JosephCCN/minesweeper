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
        if(cnt % 2 == 0) _ = tmp;
        else bomb.push_back({_, tmp});
        cnt++;
    }
}

void playerMoveRunner(Player &player, pair<int, int> &res, int** showBoard, bool &flag) {
    res = player.move(showBoard, flag);
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
    vector<pair<int, int> > moveLog; 
    int** showBoard = (int**)malloc(sizeof(int*) * (1 + mapSize.first));
    for(int i=0;i<mapSize.first;i++) showBoard[i] = (int*)malloc(sizeof(int) * (1 + mapSize.second));

    for(;game.isPlaying();) {

        game.getShowBoard(showBoard);

        pair<int, int> res;
        bool flag = false;
        thread playerMoveTh(playerMoveRunner, ref(player), ref(res), showBoard, ref(flag));

        //count moveRunTime seconds
        mutex mtx;
        unique_lock<mutex> lck(mtx);
        timeout = ( cv.wait_for(lck, chrono::seconds(moveRunTime)) == cv_status::timeout ); //count timeout
        if(timeout) {
            playerMoveTh.detach();
            cout << "Error" << endl;
            cout << "Timeout on move " << game.getMove() << endl; 
            break;
        }
        playerMoveTh.join();
        moveLog.push_back(res);
        // check flag or click
        if(flag) {
            game.flag(res.first, res.second);
        }
        else {
            game.click(res.first, res.second);
        }
        
        if(game.isLoss()) {
            cout << "LOSS" << endl;
            cout << game.report() << endl;
        }
        else if(game.isError()) {
            cout << "Error" << endl;
            cout << game.report() << endl;
        }
    }

    for(auto x:moveLog) cout << x.first << ' ' << x.second << endl;
    if(game.isWin()) cout << game.report() << endl;

}