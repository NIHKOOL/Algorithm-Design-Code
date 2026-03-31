#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 5 โหนด คือ 0 ถึง 4)
    int n = 5;
    
    // กราฟแบบมีน้ำหนัก: เราจะเก็บข้อมูลเป็น pair<น้ำหนัก, โหนดปลายทาง>
    vector<vector<pair<int, int>>> adj(n);

    // กำหนดเส้นเชื่อมและน้ำหนัก (Undirected Graph ต้องใส่เส้นทางไป-กลับให้เหมือนกัน)
    // รูปแบบ: adj[โหนดต้นทาง].push_back({น้ำหนัก, โหนดปลายทาง});
    adj[0].push_back({2, 1}); adj[1].push_back({2, 0});
    adj[0].push_back({3, 3}); adj[3].push_back({3, 0});
    adj[1].push_back({1, 2}); adj[2].push_back({1, 1});
    adj[1].push_back({4, 3}); adj[3].push_back({4, 1});
    adj[1].push_back({5, 4}); adj[4].push_back({5, 1});
    adj[2].push_back({6, 4}); adj[4].push_back({6, 2});
    adj[3].push_back({7, 4}); adj[4].push_back({7, 3});





    vector<bool> visited(n, false); 
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int total_min_w = 0; 

    pq.push({0, 0});

    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;
        total_min_w += w;

        for (auto edge : adj[u]) {
            int next_w = edge.first;
            int v = edge.second;

            if (!visited[v]) {
                pq.push({next_w, v});
            }
        }
    }




    
    cout << "--------------------------------\n";
    cout << "ผลรวมน้ำหนักของ Minimum Spanning Tree คือ: " << total_min_w << endl;

    return 0;
}