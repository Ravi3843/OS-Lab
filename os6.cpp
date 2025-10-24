#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int pid, at, bt, rt, ct, wt, tat;
};

int main() {
    int n, tq;
    cout << "Number of processes: "; cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        cout << "Arrival time and burst time for P" << p[i].pid << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }
    cout << "Time Quantum: "; cin >> tq;

    queue<int> q;
    int time = 0, completed = 0;
    vector<bool> inQueue(n, false);
    for (int i = 0; i < n; i++)
        if (p[i].at <= time) { 
        q.push(i); 
        inQueue[i] = true;
        }

    cout << "\nExecution Order: ";
    while (completed < n) {
        if (q.empty()) {
            time++;
            for (int i = 0; i < n; i++)
                if (!inQueue[i] && p[i].at <= time) { q.push(i); inQueue[i] = true; }
            continue;
        }
        int i = q.front(); q.pop();
        cout << "P" << p[i].pid << " ";
        int exec = min(tq, p[i].rt);
        time += exec;
        p[i].rt -= exec;

        for (int j = 0; j < n; j++)
            if (!inQueue[j] && p[j].at <= time) { q.push(j); inQueue[j] = true; }

        if (p[i].rt == 0) {
            completed++;
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        } else {
            q.push(i);
        }
    }

    double total_wt = 0, total_tat = 0;
    cout << "\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (auto& x : p) {
        cout << "P" << x.pid << "\t" << x.at << "\t" << x.bt << "\t" << x.wt << "\t" << x.tat << "\n";
        total_wt += x.wt;
        total_tat += x.tat;
    }
    cout << "Average Waiting Time: " << total_wt / n << "\n";
    cout << "Average Turnaround Time: " << total_tat / n << "\n";

    return 0;
}

