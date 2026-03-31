#include <iostream>
#include <vector>
#include <iomanip> // เอาไว้จัดหน้าจอตอน print ตารางให้สวยๆ

using namespace std;

const int INF = 1e9; // ตัวแทนของค่าอนันต์ (ไปไม่ถึง)

int main() {
    // 1. สร้างกราฟตัวอย่าง (มี 4 โหนด คือ 0 ถึง 3)
    int n = 4;
    

    vector<vector<int>> dist(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // กำหนดเส้นเชื่อมและค่าน้ำหนัก (Directed Graph)
    // รูปแบบ: dist[ต้นทาง][ปลายทาง] = น้ำหนัก;
    dist[0][1] = 5;
    dist[0][3] = 10;
    dist[1][2] = 3;
    dist[2][3] = 1;
    dist[3][1] = -2; // ⚠️ มีเส้นทางติดลบได้ (แต่ต้องไม่เป็นวงวนติดลบ)



    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j]; 
                    }
                }
            }
        }
    }

    bool has_negative_cycle = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            has_negative_cycle = true;
            break;
        }
    }

    // 5. แสดงผลลัพธ์เป็นตาราง
    cout << "---------------------------------------------------\n";
    if (has_negative_cycle) {
        cout << "🚨 ตรวจพบ 'วงวนติดลบ' (Negative Cycle) ในกราฟ!\n";
    } else {
        cout << "ตารางระยะทางที่สั้นที่สุดจากทุกจุดไปยังทุกจุด:\n\n";
        
        // Print หัวตาราง
        cout << "    ";
        for (int i = 0; i < n; i++) cout << setw(5) << "to " << i;
        cout << "\n";

        // Print ข้อมูลในตาราง
        for (int i = 0; i < n; i++) {
            cout << "fr " << i << " |";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << "\n";
        }
    }
    cout << "---------------------------------------------------\n";

    return 0;
}