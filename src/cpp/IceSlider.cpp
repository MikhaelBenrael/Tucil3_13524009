#include "IceSlider.h"

IceSlider::IceSlider() : max_target_num(0) {}

bool IceSlider::loadMap(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return false;

    file >> rows >> cols;
    grid.resize(rows);
    cost_grid.assign(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        file >> grid[i];
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'Z') start_pos = {i, j};
            else if (isdigit(grid[i][j])) {
                int num = grid[i][j] - '0';
                target_positions[num] = {i, j}; 
                if (num > 0) max_target_num = max(max_target_num, num);
            }
        }
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            file >> cost_grid[i][j];
        }
    }
    file.close();
    loaded_filename = filename;
    return true;
}

int IceSlider::calculateHeuristic(int r, int c, int next_target, int h_type) {
    Point t_pos;
    if (next_target <= max_target_num) t_pos = target_positions[next_target];
    else t_pos = target_positions[0]; 

    int dr = abs(r - t_pos.r);
    int dc = abs(c - t_pos.c);

    if (h_type == 1) return dr + dc;                        
    if (h_type == 2) return sqrt(dr * dr + dc * dc);        
    if (h_type == 3) return max(dr, dc);                    
    return 0;
}

pair<State, bool> IceSlider::slide(State curr, char dir, int dr, int dc) {
    int r = curr.r, c = curr.c;
    int move_cost = 0;
    int current_target = curr.next_target;
    bool isValid = true;

    while (true) {
        int nr = r + dr;
        int nc = c + dc;

        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) { isValid = false; break; }

        char tile = grid[nr][nc];
        if (tile == 'X') break; 
        if (tile == 'L') { isValid = false; break; } 

        r = nr; c = nc;
        move_cost += cost_grid[r][c]; 

        if (isdigit(tile)) {
            int val = tile - '0';
            if (val > 0 && val == current_target) {
                current_target++; 
            } else if (val > 0 && val > current_target) {
                isValid = false; break; 
            } 
        }
    }

    if (isValid && grid[r][c] == '0' && current_target > max_target_num) {} 

    State next_state = {r, c, current_target, curr.cost + move_cost, 0, 0, curr.path + dir};
    return {next_state, isValid};
}

void IceSlider::solve(string algo, int h_type) {
    priority_queue<State, vector<State>, greater<State>> pq;
    
    vector<pair<string, int>> best_cost_list; 
    
    auto start_time = chrono::high_resolution_clock::now();
    int iterations = 0;

    State initial = {start_pos.r, start_pos.c, 1, 0, 0, 0, ""};
    if (algo != "BFS") initial.heuristic = calculateHeuristic(initial.r, initial.c, 1, h_type);
    pq.push(initial);

    State solution;
    bool found = false;

    vector<string> log_iterasi;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();
        iterations++;
        string current_path = curr.path.empty() ? "START" : curr.path;
        string log_text = "Iterasi " + to_string(iterations) + 
                          " | Posisi: (" + to_string(curr.r) + "," + to_string(curr.c) + ")" +
                          " | Next Target: " + to_string(curr.next_target) +
                          " | Cost: " + to_string(curr.cost) +
                          " | Path: " + current_path;
        log_iterasi.push_back(log_text);
        if (grid[curr.r][curr.c] == '0' && curr.next_target > max_target_num) {
            solution = curr;
            found = true;
            break;
        }

        string state_key = to_string(curr.r) + "," + to_string(curr.c) + "," + to_string(curr.next_target);
        
        bool skip_state = false;
        bool found_key = false;

        for (int i = 0; i < best_cost_list.size(); i++) {
            if (best_cost_list[i].first == state_key) {
                found_key = true;
                if (best_cost_list[i].second <= curr.cost) {
                    skip_state = true; 
                } else {
                    best_cost_list[i].second = curr.cost; 
                }
                break;
            }
        }

        if (skip_state) continue; 
        if (!found_key) {
            best_cost_list.push_back({state_key, curr.cost});
        }

        char dirs[] = {'U', 'D', 'L', 'R'};
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            pair<State, bool> res = slide(curr, dirs[i], dr[i], dc[i]);
            if (res.second) {
                State next_s = res.first;
                
                if (algo == "UCS") { next_s.f_value = next_s.cost; }
                else if (algo == "GBFS") { next_s.heuristic = calculateHeuristic(next_s.r, next_s.c, next_s.next_target, h_type); next_s.f_value = next_s.heuristic; }
                else if (algo == "A*") { next_s.heuristic = calculateHeuristic(next_s.r, next_s.c, next_s.next_target, h_type); next_s.f_value = next_s.cost + next_s.heuristic; }
                else if (algo == "BFS") { next_s.f_value = next_s.path.length(); }
                
                pq.push(next_s);
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    if (found) {
        cout << "\nSolusi" << endl;
        cout << "Path         : " << solution.path << endl;
        cout << "Total Cost   : " << solution.cost << endl;
        cout << "Iterasi      : " << iterations << endl;
        cout << "Waktu (ms)   : " << duration_micro.count() << " microsecond (" << duration_micro.count() / 1000.0 << " ms)\n" << endl;
        
        cout << ">> Apakah Anda ingin melakukan playback? (Ya/Tidak): ";
        string play; cin >> play;
        if (play == "Ya" || play == "ya") {
            runPlayback(solution.path);
        }

        cout << ">> Apakah Anda ingin menyimpan solusi? (Ya/Tidak): ";
        string saveOpt; cin >> saveOpt;
        if (saveOpt == "Ya" || saveOpt == "ya") {
            string base_name = loaded_filename;
            size_t pos = base_name.find_last_of("/\\");
            if (pos != string::npos) {
                base_name = base_name.substr(pos + 1);
            }
            string savePath = "solve/solusi_" + base_name;
            ofstream outFile(savePath);
            
            if (outFile.is_open()) {
                outFile << "Riwayat Iterasi\n";
                for (const string& log : log_iterasi) {
                    outFile << log << "\n";
                }
                outFile << "Path: " << solution.path << "\n";
                outFile << "Cost: " << solution.cost << "\n";
                outFile << "Total Iterasi: " << iterations << "\n";
                outFile << "Waktu: " << duration_micro.count() << " microsecond (" 
                        << duration_micro.count() / 1000.0 << " ms)\n";
                
                outFile.close();
                cout << ">> Berhasil disimpan di " << savePath << "\n";
            } else {
                cout << ">> Gagal menyimpan solusi.\n";
            }
        }
    } else {
        cout << "Solusi tidak ditemukan." << endl;
    }
}

void IceSlider::runPlayback(const string& path) {
    vector<vector<string>> frames;
    vector<string> temp_grid = grid;
    int r = start_pos.r, c = start_pos.c;
    int current_target = 1;

    frames.push_back(temp_grid); 

    for (char dir : path) {
        int dr = 0, dc = 0;
        if (dir == 'U') dr = -1; else if (dir == 'D') dr = 1;
        else if (dir == 'L') dc = -1; else if (dir == 'R') dc = 1;

        temp_grid[r][c] = '*'; 

        while (true) {
            int nr = r + dr, nc = c + dc;
            if (temp_grid[nr][nc] == 'X') break;
            r = nr; c = nc;

            if (isdigit(temp_grid[r][c])) {
                int val = temp_grid[r][c] - '0';
                if (val > 0 && val == current_target) {
                    temp_grid[r][c] = '*'; 
                    current_target++;
                }
            }
        }
        temp_grid[r][c] = 'Z'; 
        frames.push_back(temp_grid);
    }

    int step = 0;
    int max_step = frames.size() - 1;
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "Step " << step << " / " << max_step << endl;
        for (const string& row : frames[step]) cout << row << endl;
        
        cout << "\n[A] Mundur  [D] Maju  [J] Jump  [Q] Keluar: ";
        char cmd; cin >> cmd;
        cmd = toupper(cmd);

        if (cmd == 'A' && step > 0) step--;
        else if (cmd == 'D' && step < max_step) step++;
        else if (cmd == 'J') {
            cout << "Lompat ke step (0-" << max_step << "): ";
            int j; cin >> j;
            if (j >= 0 && j <= max_step) step = j;
        }
        else if (cmd == 'Q') break;
    }
}