#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 6 โหนด คือ 0 ถึง 5)
    // ⚠️ กราฟที่จะทำ Topological Sort ได้ ต้องเป็นแบบ "มีทิศทาง (Directed)" และ "ไม่มีวงวน (Acyclic)"
    int n = 6;
    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0); // ตัวแปรใหม่: เอาไว้นับว่ามีเส้นชี้มาหาโหนดนี้กี่เส้น (In-degree)

    // กำหนดเส้นเชื่อมแบบมีทิศทาง (เช่น 5 ชี้ไป 2 แปลว่าต้องทำ 5 ก่อน 2)
    adj[5] = {2, 0};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};
    // โหนด 0 และ 1 ไม่มีชี้ไปหาใครเลย

    for (int i = 0; i < n; i++) {
        for (int neighbor : adj[i]) {
            in_degree[neighbor]++; 
        }
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order; 

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        topo_order.push_back(u); 

        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }



    // 5. ตรวจสอบผลลัพธ์และแสดงผล
    // ถ้าจำนวนโหนดในคำตอบ เท่ากับจำนวนโหนดทั้งหมด แปลว่าทำสำเร็จ
    if (topo_order.size() == n) {
        cout << "ผลลัพธ์ Topological Sort: ";
        for (int node : topo_order) {
            cout << node << " ";
        }
        cout << endl;
    } else {
        // ถ้าไม่เท่ากัน แปลว่ากราฟนี้แอบมี "วงวน (Cycle)" ทำให้มันเกิดอาการ Deadlock เรียงลำดับไม่ได้
        cout << "ไม่สามารถเรียงได้! กราฟนี้มี Cycle (วงวน) อยู่ข้างใน" << endl;
    }

    return 0;
}