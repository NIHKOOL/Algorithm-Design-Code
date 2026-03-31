#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 5 โหนด คือ 0 ถึง 4)
    int n = 5;
    vector<vector<int>> adj(n);

    adj[0] = {1, 2};     // โหนด 0 เชื่อมกับ 1, 2
    adj[1] = {0, 3, 4};  // โหนด 1 เชื่อมกับ 0, 3, 4
    adj[2] = {0};        // โหนด 2 เชื่อมกับ 0
    adj[3] = {1};        // โหนด 3 เชื่อมกับ 1
    adj[4] = {1};        // โหนด 4 เชื่อมกับ 1

    vector<bool> visited(n, false); 
    stack<int> s;                   

    s.push(0);

    while (!s.empty()) {
        int u = s.top();
        s.pop();

        if (!visited[u]) {
            visited[u] = true;  
            for (int v : adj[u]) {
                if (!visited[v]) {
                    s.push(v);
                }
            }       
        }
    }

    cout << endl;

    return 0;
}