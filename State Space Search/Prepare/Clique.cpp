#include <bits/stdc++.h>
using namespace std;

struct State {
    int idx;
    int current_sum;
    vector<int> team;
};

int n;
int power[55];
int adj[55][55];
int suffix_max[55]; // เก็บผลรวมพลังตั้งแต่คนที่ i ถึง n เพื่อใช้ในการ Bound

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; i++) cin >> power[i]; 

    // คำนวณ Suffix Sum เพื่อใช้ทำ Bound (ผลรวมพลังที่เหลืออยู่ทั้งหมดที่เป็นไปได้)
    suffix_max[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        suffix_max[i] = suffix_max[i + 1] + power[i];
    }

    for (int i = 1; i <= n; i++) {
        string row; cin >> row; 
        for (int j = 1; j <= n; j++) {
            adj[i][j] = row[j - 1] - '0'; 
        }
    }

    int max_power = 0;
    stack<State> s;
    s.push({1, 0, {}});

    while (!s.empty()) {
        State cur = s.top();
        s.pop();

        // 1. Update ค่าสูงสุดที่พบ
        max_power = max(max_power, cur.current_sum);

        // 2. Base Case: พิจารณาครบทุกคนแล้ว
        if (cur.idx > n) continue;

        // 3. --- กฎการตัดกิ่ง (The Bound) ---
        // ถ้าพลังปัจจุบัน + พลังของคนที่เหลือทุกคน ยังไม่ชนะ max_power ให้ข้ามกิ่งนี้ไปเลย
        if (cur.current_sum + suffix_max[cur.idx] <= max_power) {
            continue; 
        }

        // --- ทางเลือกที่ 1: ไม่เลือกพนักงานคนนี้ ---
        s.push({cur.idx + 1, cur.current_sum, cur.team});

        // --- ทางเลือกที่ 2: เลือกพนักงานคนนี้ ---
        bool can_join = true;
        for (int member : cur.team) {
            if (adj[cur.idx][member] == 0) {
                can_join = false;
                break;
            }
        }

        if (can_join) {
            vector<int> next_team = cur.team;
            next_team.push_back(cur.idx);
            s.push({cur.idx + 1, cur.current_sum + power[cur.idx], next_team});
        }
    }

    cout << max_power << endl;
    return 0;
}