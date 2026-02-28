#include <bits/stdc++.h>
using namespace std;

//Fibo
int fibo(int n) {
    if (n == 1 || n == 0) return n;
    if (n >= 2) return fibo(n-1) + fibo(n-2); 
}

vector<int> table;
//Fibi memo
//table is an array[1.n] init by 0
//top down
int fibo_memo(int n) {
    if (n == 1 || n == 0) return n;
    
    if (n >= 2) {
        if (table[n] > 0) {
            return table[n];
        }

        int value = fibo_memo(n-1) + fibo_memo(n-2);
        table[n] = value;
        return value;
    }
}

//bottom-up
int fibo_bottom_up(int n) {
    table[0] = 0;
    table[1] = 1;
    for (int i = 2; i <= n; i++) {
        table[i] = table[i-1] + table[i-2];

    }
    return table[n];

}

//binomial D&C
int bino_naive(int n, int r) {
    if (r == n) return 1;
    if (r == 0) return 1;

    int result = bino_naive(n-1,r) + bino_naive(n-1,r-1);
    return result;
}

//top down
int bino_memo(int n, int r) {
    if (r == n) return 1;
    if (r == 0) return 1;

    if (table[n][r] != -1) return table[n][r];
    
    int result = bino_memo(n-1,r) + bino_memo(n-1,r-1);
    table[n][r] = result;

    return result;

}

//bottom-up
int bino_DP(int n , int r) {
    for (int i = 0; i <= n; i++) {
        table[i][0] = 1;
        table[i][i] = 1;
    }

    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j < i; j++) {
            table[i][j] = table[i-1][j] + table[i-1][j-1];
        }
    }
    return table[n][r];
}

//MCM
//naive
for (i = 1; i <= a;i++) {
    for (j = 1; i <= c;j++) {
    sum = 0;
    for (k = 1;k <= b;k++) {
        sum += P[i][k] * Q[k][j];
    }
    R[i][j] = sum;
    }
}   

int mcm(int l,int r) {
    if (l < r) {
        minCost = MAX_INT;
        for (int i = l;i < r;i++) {
            my_cost = mcm(l,i) + mcm(i+1,r) + (a[l] * a[i+1] * a[r+1]);
            minCost = min(my_cost,minCost);
        }
        return minCost;
    } else {
        return 0;
}
}

int main() {}
