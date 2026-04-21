#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <fstream>

using namespace std;

const int dr[] = {1, -1, 0, 0};
const int dc[] = {0, 0, 1, -1};
const char move_chars[] = {'U', 'D', 'L', 'R'};
const int reverse_dir[] = {1, 0, 3, 2};

int n, target_n;
int orig_grid[70][70];
int grid[70][70];
int target_grid[70][70];
int er, ec, orig_er, orig_ec;

struct Pos { int r, c; };
int piece_count[105];
Pos pieces[105][4500];
int grid_piece_idx[70][70];
string current_path = "";
string best_path = "";
bool found_solution = false;

// 🌟 Zero-Allocation Arrays
int empty_vis[70][70];
int empty_cur_vis = 0;
int parent_d[70][70];
pair<int, int> parent_p[70][70];
bool locked[70][70];
string fallback_path = "";

bool is_target_matched() {
    for (int i = 0; i < target_n; i++) {
        for (int j = 0; j < target_n; j++) {
            if (grid[i + 1][j + 1] != target_grid[i][j]) return false;
        }
    }
    return true;
}

int get_global_h() {
    int h = 0;
    for (int tr = 0; tr < target_n; tr++) {
        for (int tc = 0; tc < target_n; tc++) {
            int val = target_grid[tr][tc];
            int actual_r = tr + 1, actual_c = tc + 1;
            if (grid[actual_r][actual_c] == val) continue;
            int min_d = 1e9;
            for (int i = 0; i < piece_count[val]; i++) {
                int d = abs(pieces[val][i].r - actual_r) + abs(pieces[val][i].c - actual_c);
                if (d < min_d) min_d = d;
            }
            h += min_d;
        }
    }
    return h;
}

void do_move_ida(int d) {
    int nr = er + dr[d], nc = ec + dc[d];
    int val = grid[nr][nc], idx = grid_piece_idx[nr][nc];
    swap(grid[er][ec], grid[nr][nc]);
    pieces[val][idx] = {er, ec};
    grid_piece_idx[er][ec] = idx;
    er = nr; ec = nc;
    current_path += move_chars[d];
}

void undo_move_ida(int d) {
    int rev_d = reverse_dir[d];
    int nr = er + dr[rev_d], nc = ec + dc[rev_d];
    int val = grid[nr][nc], idx = grid_piece_idx[nr][nc];
    swap(grid[er][ec], grid[nr][nc]);
    pieces[val][idx] = {er, ec};
    grid_piece_idx[er][ec] = idx;
    current_path.pop_back();
    er = nr; ec = nc;
}

int dfs_ida(int g, int threshold, int last_dir) {
    if (found_solution) return -1;
    int h = get_global_h();
    int f = g + h;
    if (f > threshold) return f;

    if (h == 0 && is_target_matched()) {
        found_solution = true;
        best_path = current_path;
        return -1;
    }

    int min_exceed = 1e9;
    for (int d = 0; d < 4; d++) {
        if (last_dir != -1 && d == reverse_dir[last_dir]) continue;
        int nr = er + dr[d], nc = ec + dc[d];
        if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
            do_move_ida(d);
            int res = dfs_ida(g + 1, threshold, d);
            if (res == -1) return -1;
            if (res < min_exceed) min_exceed = res;
            undo_move_ida(d);
        }
    }
    return min_exceed;
}

void do_move_fallback(int d) {
    int nr = er + dr[d], nc = ec + dc[d];
    swap(grid[er][ec], grid[nr][nc]);
    er = nr; ec = nc;
    fallback_path += move_chars[d];
}

struct Node {
    int r, c, cost;
    bool operator>(const Node& o) const { return cost > o.cost; }
};

vector<pair<int, int>> get_best_piece_path(int target_val, int tr, int tc) {
    // 1. BFS หาระยะทางของช่องว่าง
    vector<vector<int>> dist_e(n, vector<int>(n, 1e9));
    queue<pair<int, int>> qe;
    qe.push({er, ec});
    dist_e[er][ec] = 0;
    while (!qe.empty()) {
        auto [r, c] = qe.front(); qe.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !locked[nr][nc]) {
                if (dist_e[r][c] + 1 < dist_e[nr][nc]) {
                    dist_e[nr][nc] = dist_e[r][c] + 1;
                    qe.push({nr, nc});
                }
            }
        }
    }

    // 2. Dijkstra หาเส้นทางลากกระเบื้อง (Highway Routing)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<vector<int>> dist_p(n, vector<int>(n, 1e9));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(n, {-1, -1}));

    pq.push({tr, tc, 0});
    dist_p[tr][tc] = 0;

    while (!pq.empty()) {
        auto [r, c, cost] = pq.top(); pq.pop();
        if (cost > dist_p[r][c]) continue;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !locked[nr][nc]) {
                // Highway Logic: ให้ขอบมีค่า Cost สูง บังคับแผ่นกระเบื้องมุดตรงกลาง
                int move_cost = 1;
                if (nr == 0 || nc == 0 || nr == n - 1 || nc == n - 1) move_cost = 5;

                if (dist_p[r][c] + move_cost < dist_p[nr][nc]) {
                    dist_p[nr][nc] = dist_p[r][c] + move_cost;
                    parent[nr][nc] = {r, c};
                    pq.push({nr, nc, dist_p[nr][nc]});
                }
            }
        }
    }

    // 3. 🌟 เลือกชิ้นส่วนที่ดีที่สุด (จุดที่แก้ไขบั๊ก)
    int best_score = 2e9;
    int found_r = -1, found_c = -1;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (grid[r][c] == target_val && !locked[r][c] && dist_p[r][c] != 1e9) {
                // ใชั dist_p (แผนที่หลบหลีกจริง) แทนที่การใช้ระยะกระจัด (Manhattan)
                int score = dist_p[r][c] * 5 + dist_e[r][c];

                if (score < best_score) {
                    best_score = score;
                    found_r = r; found_c = c;
                } else if (score == best_score) {
                    // Tie-breaker: ถ้าคะแนนเท่ากัน ให้เลือกชิ้นที่อยู่ใกล้เป้าหมายมากกว่า
                    if (dist_p[r][c] < dist_p[found_r][found_c]) {
                        found_r = r; found_c = c;
                    }
                }
            }
        }
    }

    vector<pair<int, int>> path;
    if (found_r == -1) return path;

    int curr_r = found_r, curr_c = found_c;
    while (curr_r != tr || curr_c != tc) {
        path.push_back({curr_r, curr_c});
        auto p = parent[curr_r][curr_c];
        curr_r = p.first; curr_c = p.second;
    }
    path.push_back({tr, tc});
    return path;
}

bool move_empty_to(int tr, int tc, int avoid_r, int avoid_c) {
    if (er == tr && ec == tc) return true;
    empty_cur_vis++;

    queue<pair<int, int>> q;
    q.push({er, ec});
    empty_vis[er][ec] = empty_cur_vis;
    parent_d[er][ec] = -2;

    bool found = false;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == tr && c == tc) { found = true; break; }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                if (empty_vis[nr][nc] != empty_cur_vis && !locked[nr][nc] && !(nr == avoid_r && nc == avoid_c)) {
                    empty_vis[nr][nc] = empty_cur_vis;
                    parent_d[nr][nc] = i;
                    parent_p[nr][nc] = {r, c};
                    q.push({nr, nc});
                }
            }
        }
    }
    if (!found) return false;

    vector<int> path;
    int curr_r = tr, curr_c = tc;
    while (curr_r != er || curr_c != ec) {
        path.push_back(parent_d[curr_r][curr_c]);
        auto p = parent_p[curr_r][curr_c];
        curr_r = p.first; curr_c = p.second;
    }
    for (int i = (int)path.size() - 1; i >= 0; i--) do_move_fallback(path[i]);
    return true;
}

void solve_fallback() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) locked[i][j] = false;

    for (int i = 0; i < target_n; i++) {
        for (int j = 0; j < target_n; j++) {
            // Snake Traversal
            int actual_j = (i % 2 == 0) ? j : (target_n - 1 - j);

            int target_val = target_grid[i][actual_j];
            int tr = i + 1, tc = actual_j + 1;

            if (grid[tr][tc] == target_val) {
                locked[tr][tc] = true;
                continue;
            }

            while (grid[tr][tc] != target_val) {
                vector<pair<int, int>> piece_path = get_best_piece_path(target_val, tr, tc);

                if (piece_path.size() < 2) {
                    bool moved = false;
                    for (int d = 0; d < 4; d++) {
                        int nr = er + dr[d], nc = ec + dc[d];
                        if (nr >= 0 && nr < n && nc >= 0 && nc < n && !locked[nr][nc]) {
                            do_move_fallback(d); moved = true; break;
                        }
                    }
                    if (!moved) break;
                    continue;
                }

                int pr = piece_path[0].first;
                int pc = piece_path[0].second;

                bool stuck = false;
                for (size_t k = 1; k < piece_path.size(); k++) {
                    int next_r = piece_path[k].first;
                    int next_c = piece_path[k].second;

                    bool ok = move_empty_to(next_r, next_c, pr, pc);
                    if (!ok) {
                        stuck = true;
                        for (int d = 0; d < 4; d++) {
                            int nr = er + dr[d], nc = ec + dc[d];
                            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !locked[nr][nc] && !(nr == pr && nc == pc)) {
                                do_move_fallback(d); break;
                            }
                        }
                        break;
                    }

                    int move_dir = -1;
                    if (er == pr + 1 && ec == pc) move_dir = 1;
                    else if (er == pr - 1 && ec == pc) move_dir = 0;
                    else if (er == pr && ec == pc + 1) move_dir = 3;
                    else if (er == pr && ec == pc - 1) move_dir = 2;
                    if (move_dir != -1) {
                        do_move_fallback(move_dir);
                        pr = next_r; pc = next_c;
                    }
                }
                if (stuck) continue;
            }
            locked[tr][tc] = true;
        }
    }
}

string optimize_path(string path) {
    string opt = "";
    for (char c : path) {
        if (!opt.empty()) {
            char last = opt.back();
            if ((last == 'U' && c == 'D') || (last == 'D' && c == 'U') ||
                (last == 'L' && c == 'R') || (last == 'R' && c == 'L')) {
                opt.pop_back(); continue;
            }
        }
        opt += c;
    }
    return opt;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n)) return 0;
    for(int i=0; i<105; i++) piece_count[i] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            orig_grid[i][j] = grid[i][j];
            int val = grid[i][j];
            if (val == -1) {
                er = orig_er = i;
                ec = orig_ec = j;
            } else if (val > 0) {
                pieces[val][piece_count[val]] = {i, j};
                grid_piece_idx[i][j] = piece_count[val]++;
            }
        }
    }

    target_n = n - 2;
    for (int i = 0; i < target_n; i++) {
        for (int j = 0; j < target_n; j++) cin >> target_grid[i][j];
    }

    if (is_target_matched()) {
        cout << "S\n"; return 0;
    }

    int threshold = get_global_h();
    while (threshold <= 55) {
        int res = dfs_ida(0, threshold, -1);
        if (found_solution || res == 1e9) break;
        threshold = res;
    }

    if (found_solution) {
        cout << best_path << "S\n";
    } else {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) grid[i][j] = orig_grid[i][j];
        er = orig_er; ec = orig_ec;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) empty_vis[i][j] = 0;

        solve_fallback();
        cout << optimize_path(fallback_path) << "S\n";
    }



    
    return 0;
}
