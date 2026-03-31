#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    int n = 5;
    vector<vector<int>> adj(n);
    
    // กำหนดเส้นเชื่อม (Edges)
    adj[0] = {1, 2};     // โหนด 0 เชื่อมกับ 1, 2
    adj[1] = {0, 3, 4};  // โหนด 1 เชื่อมกับ 0, 3, 4
    adj[2] = {0};        // โหนด 2 เชื่อมกับ 0
    adj[3] = {1};        // โหนด 3 เชื่อมกับ 1
    adj[4] = {1};        // โหนด 4 เชื่อมกับ 1

    vector<bool> visited(n, false); 
    queue<int> q;                   

    q.push(0);
    visited[0] = true; 

    while (!q.empty()) {
        int u = q.front(); 
        q.pop();                 

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true; // ทำเครื่องหมายทันที เพื่อป้องกันการดึงเข้าคิวซ้ำซ้อน
                q.push(v);
            }
        }
    }
    return 0;
}