#include<vector>
#include<utility>
#include<iostream>
#include "model.h"
using namespace std;

int main(){
    vector<pair<int, int> > mine;
    mine.push_back({1, 1});
    mine.push_back({2, 2});
    game x(mine, 10, 10);
    x.sb();
    cout << endl;
    x.b();
    x.click(8,8);

    cout << "==========\n";

    x.sb();
    cout << endl;
    x.b();
}
