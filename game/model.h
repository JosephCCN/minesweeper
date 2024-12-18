#ifndef _MODEL_H
#define _MODEL_H

#include<vector>
#include<utility>
#include<string>

using namespace std;


class game{
    private:
        int board[1005][1005];
        int show_board[1005][1005];
        int max_x = 0;
        int max_y = 0;
        int move = 0;

        const int BOMB = -1;
        const int UNSHOWN = -1;

        void update_show_board(int,int);
        void game_terminate(string);
        void increment_move();
        bool valid(int, int);
        void valid_move(int, int);
        bool check_bomb(int, int);
        void Error(int);
        void GameLoss();
    public:
        game(vector<pair<int, int> >, int, int);
        void click(int, int);
        void sb();
        void b();
};

#endif
