#include<utility>
using namespace std;

#ifndef _PLAYER_H
#define _PLAYER_H

class Player{
    public:
        void init(int, int);
        pair<int, int> move(int**, bool&);
};

#endif