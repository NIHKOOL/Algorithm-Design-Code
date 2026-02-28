#include <bits/stdc++.h>
using namespace std; 

void selection_sort(vector<int> &A) { //Θ(n^2)
    size_t pos = A.size()-1;
    for (; pos > 0; pos--) {
        int max_idx = 0;
        for (size_t i = 0; i <= pos; i++) {
            if (A[i] > A[max_idx]) {
                max_idx = i;
            }
        }
        swap(A[pos], A[max_idx]); //O(1)
    }
}

void insertion_sort(vector<int> &A) { //O(n^2)
    for (int pos = A.size()-2; pos >= 0; pos--) {
        int tmp = A[pos];
        size_t i = pos+1;
        while (i < A.size() && A[i] < tmp) {
            A[i-1] = A[i];
            i++;
        }
        A[i-1] = tmp;
    }
}




int main () {

}