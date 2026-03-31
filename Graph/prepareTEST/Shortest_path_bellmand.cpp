#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

// สร้างโครงสร้างสำหรับเก็บเส้นเชื่อม (ง่ายกว่าการใช้ adjacency list ในกรณีนี้)
struct Edge {
    int u, v, weight;
};

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 5 โหนด คือ 0 ถึง 4)
    int n = 5;
    
    // กำหนดเส้นเชื่อมแบบมีทิศทาง {ต้นทาง, ปลายทาง, น้ำหนัก}
    vector<Edge> edges = {
        {0, 1, -1},  // ⚠️ เส้นทางติดลบ!
        {0, 2, 4},
        {1, 2, 3},
        {1, 3, 2},
        {1, 4, 2},
        {3, 2, 5},
        {3, 1, 1},
        {4, 3, -3}   // ⚠️ เส้นทางติดลบ!
    };

   
    vector<int> dist(n, INF);
    int start_node = 0;
    dist[start_node] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (auto edge : edges) {
            if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    bool has_negative_cycle = false;
    for (auto edge : edges) {
        if (dist[edge.u] != INF && dist[edge.u] + edge.weight < dist[edge.v]) {
            has_negative_cycle = true;
            break;
        }
    }

    


    

    // 5. แสดงผลลัพธ์
    cout << "---------------------------------------------------\n";
    if (has_negative_cycle) {
        cout << "🚨 ตรวจพบ 'วงวนติดลบ' (Negative Weight Cycle)!\n";
        cout << "ไม่สามารถหาระยะทางที่สั้นที่สุดได้ เพราะยิ่งเดินวนค่ายิ่งลดลงเรื่อยๆ\n";
    } else {
        cout << "ระยะทางสั้นที่สุดจากโหนดเริ่มต้น (" << start_node << ") ไปยังโหนดอื่นๆ:\n";
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) {
                cout << "ไปโหนด " << i << " : ไปไม่ถึง\n";
            } else {
                cout << "ไปโหนด " << i << " : ใช้ระยะทาง " << dist[i] << "\n";
            }
        }
    }
    cout << "---------------------------------------------------\n";

    return 0;
}