#ifndef ICE_SLIDER_H
#define ICE_SLIDER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point { 
    int r, c; 
};

struct State {
    int r, c;
    int next_target; 
    int cost;
    int heuristic;
    int f_value;
    string path;

    bool operator>(const State& other) const {
        return f_value > other.f_value;
    }
};

class IceSlider {
private:
    vector<string> grid;
    vector<vector<int>> cost_grid;
    int rows, cols;
    Point start_pos;    
    Point target_positions[10]; 
    int max_target_num;
    string loaded_filename;
public:
    IceSlider();
    bool loadMap(const string& filename);
    int calculateHeuristic(int r, int c, int next_target, int h_type);
    pair<State, bool> slide(State curr, char dir, int dr, int dc);
    void solve(string algo, int h_type);
    void runPlayback(const string& path);
};

#endif