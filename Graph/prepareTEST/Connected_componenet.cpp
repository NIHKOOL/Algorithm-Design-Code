#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 7 โหนด คือ 0 ถึง 6)
    int n = 7;
    vector<vector<int>> adj(n);
    
    // กำหนดเส้นเชื่อม (ตั้งใจทำให้มันขาดออกจากกันเป็น 3 กลุ่ม)
    // กลุ่มที่ 1: โหนด 0, 1, 2 เชื่อมถึงกัน
    adj[0] = {1};
    adj[1] = {0, 2};
    adj[2] = {1};

    // กลุ่มที่ 2: โหนด 3, 4 เชื่อมถึงกัน
    adj[3] = {4};
    adj[4] = {3};

    // กลุ่มที่ 3: โหนด 5, 6 เชื่อมถึงกัน
    adj[5] = {6};
    adj[6] = {5};

    vector<bool> visited(n, false); 
    int component_count = 0; 

    for (int i = 0; i < n; i++) {

        if (!visited[i]) {
            component_count++;

            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            // --- จบ BFS ของกลุ่มนี้ ---
            
            cout << endl; // ขึ้นบรรทัดใหม่เพื่อเตรียมแสดงผลกลุ่มต่อไป
        }
    }

    cout << "สรุป: กราฟนี้มีทั้งหมด " << component_count << " Connected Components\n";

    return 0;
}