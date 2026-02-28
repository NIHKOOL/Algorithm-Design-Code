#include <iostream>
#include <vector> 
using namespace std;

void perm(int n, 
          vector<int> &sol, 
          int len, 
          vector<bool> &used) {
    if (len < n) {
        for (int i = 1; i <= n; i++) {
            if (used[i] == false) {
                used[i] = true;
                sol[len] = i;
                perm(n, sol, len+1, used);
                used[i] = false;
            }
        }
    } else {
        for (auto &x : sol) cout << x;
        cout << endl;

    }
}

void perm_kn(int n, 
            vector<int> &sol, 
            int len, 
            vector<bool> &used,
            int k) {
    if (len < k) {
        for (int i = 1; i <= n; i++) {
            if (used[i] == false) {
                used[i] = true;
                sol[len] = i;
                perm_kn(n, sol, len+1, used, k);
                used[i] = false;
            }
        }
    } else {
        for (auto &x : sol) cout << x;
        cout << endl;

    }
}

void perm_kn_replace(int n,
                    vector<int> &sol,
                    int len,
                    int k) {
    if (len < k) {
        for (int i = 0; i <= n; i++) {
            sol[len] = i;
            perm_kn_replace(n, sol, len+1,k);
        } 
    } else {
        for (auto &x : sol) cout << x;
        cout << endl;
    }
    

}

int main() {
    int n = 4;
    int k = 3;
    vector<int> sol(n);
    vector<bool> used(n+1);
    //perm(n, sol, 0, used, k)
    //perm_kn(n, sol, 0, used, k);
    perm_kn_replace(n, sol, 0, k);


}
