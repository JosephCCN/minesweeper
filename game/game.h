#ifndef _MODEL_H
#define _MODEL_H

#include<vector>
#include<utility>
#include<string>

using namespace std;

enum STATE_CODE {PLAYING, WIN, LOSS, ERROR_END};
enum ERROR_CODE {INVALID_MOVE=401, DOUBLE_CLICK=402};

enum GRID_STATE {EMPTY=0, BOMB=10, UNSHOWN=11, FLAG=12};

struct State {
    STATE_CODE code;
    string token;
};

class Game{
    private:
        State gameState;
        int board[1005][1005];
        int show_board[1005][1005];
        int width = 0;
        int height = 0;
        int move = 0;
        int bombRemain;

        void update_show_board(int,int);
        void setState(STATE_CODE, string);
        void increment_move();
        bool valid(int, int);
        void valid_move(int, int);
        bool check_bomb(int, int);
        void Error(ERROR_CODE);
        void GameLoss();
        void init(int, int);
    public:
        Game(vector<pair<int, int> >, int, int);
        void click(int, int);
        void flag(int, int);
        State getState();
        bool isLoss();
        bool isWin();
        bool isError();
        bool isPlaying();
        string report();
        int getMove();
        void getShowBoard(int**);

        void sb();
        void b();
};

#endif
