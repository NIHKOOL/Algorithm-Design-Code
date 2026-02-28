#include <bits/stdc++.h>
using namespace std;

//improving v0.1 using queue
int bsearch_slow(queue<int> &v, int k) {
    if (v.size() == 1) {
        if (v.front() == k) return 1;
        else return -1;
    } else {
        if (v.front() == k) return 1;
        v.pop();
        int r = bsearch_slow(v, k);
        //index++;
        return (r == -1) ? r : r+1;
    }
}

int bsearch_slow(vector<int> &v, int k) {
    queue<int> q;
    for (auto &x : v) q.push(x);
    return bsearch_slow(q, k);
}

//Much better v0.1
int bsearch_slow_2(vector<int> &v, int k, int start) {
    if (start == v.size() - 1) {
        if (v[start] == k) return start;
        return -1;
    } else {
        if (v[start] == k) return start;
        return bsearch_slow_2(v, k, start+1); 
    }
}

int bsearch_slow_2(vector<int> &v, int k) {
    return bsearch_slow_2(v, k, 0);
}

//v0.1 ver 3
int bsearch_slow_3(vector<int> &v, int k, int start) {
    if (v[start] == k) return start;
    if (start == v.size() - 1) return -1;
    return bsearch_slow_3(v, k, start+1);
} 

int bsearch_slow_3(vector<int> &v, int k) {
    return bsearch_slow_3(v, k, 0);
}

int bsearch(vector<int> &v, int k, int start, int stop) {
    if (start == stop) return v[start] == k ? start : -1;
    int m = (start + stop) >> 1; //bitwise shift right
    if (v[m] >= k) return bsearch(v, k, start, m); 
    else return bsearch(v, k, m+1, stop);
}

int bsearch(vector<int> &v, int k) {
    return bsearch(v, k, 0, v.size()-1);
}

//merger sort
void merge(vector<int> &v, int start, int m, int stop, vector<int> &tmp) {
    int bi = start; //index of B
    int ci = m+1;   //index of C
    for (int i = start; i <= stop; i++) {
        if (ci > stop)  { tmp[i] = v[bi++]; continue;}
        if (bi > m)     { tmp[i] = v[ci++]; continue;}
        tmp[i] = (v[bi] < v[ci]) ? v[bi++] : v[ci++];
    }
    for (int i = start; i <= stop; i++) v[i] = tmp[i];
}

void merge_sort(vector<int> &v, int start, int stop, vector<int> &tmp) {
    if (start < stop) {
        int m = (start + stop) >> 1;
        merge_sort(v, start, m, tmp);
        merge_sort(v, m+1, stop, tmp);
        merge(v, start, m, stop, tmp);
    }
}


