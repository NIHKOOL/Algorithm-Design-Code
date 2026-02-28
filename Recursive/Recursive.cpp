#include <bits/stdc++.h>
using namespace std;

//calculate sum 0..n
int recur1(int n) {
    if (n <= 0) {
        //terminating case 
        return 0;
    } else {
        //recursion case 
        return recur1(n-1) + n;
    }
}

void draw_tri(int level, int max) {
    if (level <= max) {
        for (int j = 0; j < level; j++) 
            printf("*");
        printf("\n");
        draw_tri(level + 1, max); 
    }
}



