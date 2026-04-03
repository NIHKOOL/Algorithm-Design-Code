#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <cmath>

using namespace std;

// สถานะเป้าหมาย (1-9 และ A=10, B=11, C=12, D=13, E=14, F=15, 0=ช่องว่าง)
const string GOAL_STATE = "123456789ABCDEF0";

struct Node {
    string board;
    string path; // เก็บประวัติการเดินไว้ในนี้เลย เช่น "Up -> Right"
    int g;  // จำนวนการขยับ
    int f;  // g + h

    // ฟังก์ชันเปรียบเทียบ (เอาไว้ให้ Priority Queue เรียงค่า f จากน้อยไปมาก)
    bool operator>(const Node& other) const{
        return f > other.f;
    }
};

// L-1 distance
int get_manhattan(const string& board) {
    int dist = 0;
    for (int i = 0; i < 16; i++) {
        if (board[i] == '0') continue;

        // แปลงตัวอักษรกลับเป็นตัวเลข (1-15)
        int val;
        if (board[i] >= '1' && board[i] <= '9') val = board[i] - '0';
        else val = board[i] - 'A' + 10;

        // คำนวณตำแหน่งแถวและคอลัมน์
        int target_row = (val - 1) / 4;
        int target_col = (val - 1) % 4;
        int current_row = i / 4;
        int current_col = i % 4;

        dist += abs(current_row - target_row) + abs(current_col - target_col);
    }
    return dist;
}

// หาการขยับที่เป็นไปได้
vector<pair<string , string>> get_neighbors(string board) {
    vector<pair<string, string>> neighbors;
    int z = board.find('0');
    int r = z / 4;
    int c = z % 4;

    // ลองสลับตำแหน่ง (บน, ล่าง, ซ้าย, ขวา)
    if (r > 0) { string b = board; swap(b[z], b[z - 4]); neighbors.push_back({b, "Up"}); }
    if (r < 3) { string b = board; swap(b[z], b[z + 4]); neighbors.push_back({b, "Down"}); }
    if (c > 0) { string b = board; swap(b[z], b[z - 1]); neighbors.push_back({b, "Left"}); }
    if (c < 3) { string b = board; swap(b[z], b[z + 1]); neighbors.push_back({b, "Right"}); }
    
    return neighbors;
}

// นำกระบวนการทั้งหมดมาไว้ใน main
int main() {
    // ----------------------------------------------------
    // ส่วนตั้งค่าเริ่มต้น
    // ----------------------------------------------------
    string start_board = "123456789A0BDEFC";
    cout << "กำลังคำนวณหาทางแก้ 15-Puzzle...\n";

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_set<string> visited;

    // คำนวณค่าเริ่มต้นแล้วใส่ลงตะกร้า (Queue)
    int start_h = get_manhattan(start_board);
    pq.push({start_board, "", 0, start_h});

    // ----------------------------------------------------
    // ลูปการค้นหาคำตอบ (A* Search)
    // ----------------------------------------------------
    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // ถ้ากระดานปัจจุบันตรงกับเป้าหมาย -> พิมพ์คำตอบและจบโปรแกรม (return 0) ทันที
        if (current.board == GOAL_STATE) {
            cout << "เจอคำตอบแล้ว!\n";
            cout << "จำนวนการขยับ: " << current.g << " ครั้ง\n";
            cout << "ขั้นตอน: " << current.path << "\n";
            return 0; 
        }

        // ตรวจสอบว่าเคยมาสถานะนี้หรือยัง
        if (visited.count(current.board)) continue;
        visited.insert(current.board);

        // ทดลองขยับช่องว่างไปในทิศทางต่างๆ
        for (auto& neighbor : get_neighbors(current.board)) {
            string next_board = neighbor.first;
            string move = neighbor.second;

            if (!visited.count(next_board)) {
                int new_g = current.g + 1;
                int new_h = get_manhattan(next_board);
                
                string new_path = current.path.empty() ? move : current.path + " -> " + move;
                pq.push({next_board, new_path, new_g, new_g + new_h});
            }
        }
    }

    // ถ้าหลุดออกจาก While loop แปลว่าหาทางแก้ไม่ได้
    cout << "ไม่พบคำตอบสำหรับกระดานนี้\n";
    return 0;
}


