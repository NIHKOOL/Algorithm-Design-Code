#include <iostream>
#include <vector>
using namespace std;

void combi(int n, 
            vector<int> &sol, 
            int len) {
    if (len < n ) { 
        sol[len] = 0;
        combi(n, sol, len+1); 

        sol[len] = 1;
        combi(n, sol, len+1); 
        
    } else {
        for (int i = 0; i < n; i++) {
            if (sol[i] == 1) cout << i +1 << " ";
        }
        cout << "." << endl;
    }
    
}

void combi_kn(int n, 
                vector<int> &sol, 
                int len,
                int k,
                int chosen) {
    if (len < n ) { 
        sol[len] = 0;
        combi_kn(n, sol, len+1, k, chosen); 

        if (chosen < k) {
            sol[len] = 1;
            combi_kn(n, sol, len+1, k, chosen + 1); 
        }
        
    } else {
        for (int i = 0; i < n; i++) {
            if (sol[i] == 1) cout << i +1 << " ";
        }
        cout << endl;
    }
    
}

void combi_exact(int n,
                vector<int> &sol,
                int len,
                int k,
                int chosen) {

    if (len < n) {
        if (len - chosen < n - k) {
            sol[len] = 0;
            combi_exact(n, sol, len+1, k, chosen);
        }
        if (chosen < k) {
            sol[len] = 1;
            combi_exact(n, sol, len+1, k, chosen+1);
        } 
    } else {
        for (int i = 0; i < n; i++) {
            if (sol[i] == 1) cout << i+1 << " ";
        }
        cout << endl;

    }

}

int main() {
    int n = 4;
    int k = 2;
    vector<int> sol(n);
    //combi (3,sol,0);
    //combi_kn(n, sol, 0, k, 0);
    combi_exact(n, sol, 0, k, 0);
}