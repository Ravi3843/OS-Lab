#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Process {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int wt;         // Waiting Time
    int tat;        // Turnaround Time
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    cout << "Enter arrival times:\n";
    for (int i = 0; i < n; i++) cin >> p[i].at;
    cout << "Enter burst times:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].bt;
        p[i].rt = p[i].bt;
        p[i].id = i + 1;
    }

    int tq;
    cout << "Enter time quantum: ";
    cin >> tq;

    queue<int> q;
    vector<int> sequence; // to store execution order

    int completed = 0, time = 0;
    vector<bool> inQueue(n, false);

    // push first process that has arrived
    for (int i = 0; i < n; i++) {
        if (p[i].at <= time && !inQueue[i]) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    while (completed != n) {
        if (q.empty()) { // CPU idle
            time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= time && !inQueue[i]) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = q.front();
        q.pop();
        sequence.push_back(p[i].id);

        int execTime = min(tq, p[i].rt);
        p[i].rt -= execTime;
        time += execTime;

        // check for newly arrived processes during this time
        for (int j = 0; j < n; j++) {
            if (p[j].at <= time && !inQueue[j] && p[j].rt > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        if (p[i].rt > 0)
            q.push(i);
        else {
            p[i].tat = time - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }

    // Output
    cout << "\nSequence of process execution: ";
    for (int id : sequence) cout << "P" << id << " ";

    float totalWT = 0, totalTAT = 0;
    cout << "\n\nProcess\tAT\tBT\tWT\tTAT\n";
    for (auto &x : p) {
        cout << "P" << x.id << "\t" << x.at << "\t" << x.bt
             << "\t" << x.wt << "\t" << x.tat << endl;
        totalWT += x.wt;
        totalTAT += x.tat;
    }

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;

    return 0;
}