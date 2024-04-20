#include <bits/stdc++.h>
#include <pthread.h>
#include <sched.h>
using namespace std;

int main() {
    cout << "Default Max: " <<sched_get_priority_max(SCHED_OTHER) << '\n'
         << "Default Min: " << sched_get_priority_min(SCHED_OTHER) << '\n'
         << "FIFO Max: " << sched_get_priority_max(SCHED_FIFO) << '\n'
         << "FIFO Min: " << sched_get_priority_min(SCHED_FIFO) << '\n'
         << "RR Max: " << sched_get_priority_max(SCHED_RR) << '\n'
         << "RR Min: " << sched_get_priority_min(SCHED_RR) << '\n';
}