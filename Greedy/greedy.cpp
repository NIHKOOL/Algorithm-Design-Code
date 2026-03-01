#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> start, stop;

//ACtivity selection - Greedy (The coorrect one)
void greedy(vector<int> &sol) { //O(nlgn)
    //sort by stop time
    vector<pair<int, int>> jobs(n);
    for (int i = 0; i < n; i++) jobs[i] = {stop[i], start[i]} ;
    sort(jobs.begin(), jobs.end());
    for (int i = 0; i < n; i++) {
        start[i] = jobs[i].second;
        stop[i]  = jobs[i].first;
    }

    // the end time of our latest selected job
    // assume that no job start earlier than time 0
    int last = -1;

    for (int i = 0; i < n; i++) {
        if (start[i] > last ) {
            //we can pick job i without conflict
            sol.push_back(i);
            last = stop[i];
        }
    }
}




int main() {

}

