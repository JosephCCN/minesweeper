#include<iostream>
#include<fstream>
#include<vector>
#include<utility>
#include <cstdarg>
#include <functional>
#include <string>

#include "game.h"
#include "player.h"

using namespace std;


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

int main(int argc, char *argv[]) {
    if(argc < 2) {
        Error(MISSING_ARG);
    }

    vector<pair<int, int> > bomb;
    pair<int, int> mapSize;
    getMeta(argv[1], bomb, mapSize);

    Player player = Player();
    Game game = Game(bomb, mapSize.first, mapSize.second);

}