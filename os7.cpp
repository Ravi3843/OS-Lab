#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int arrival, burst, remaining, priority;
    int completion = 0, waiting = 0, turnaround = 0;
    bool added = false;
};

int main() {
    int n; cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].pid >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].remaining = p[i].burst;
    }

    const int TIME_QUANTUM = 3;
    queue<Process*> q1, q2;
    vector<string> gantt;
    int time = 0, completed = 0;

    while (completed < n) {
        for (auto& proc : p)
            if (!proc.added && proc.arrival <= time) {
                (proc.priority == 1 ? q1 : q2).push(&proc);
                proc.added = true;
            }

        if (!q1.empty()) {
            Process* curr = q1.front(); q1.pop();
            int t = min(TIME_QUANTUM, curr->remaining);
            for (int i = 0; i < t; i++) {
                gantt.push_back(curr->pid);
                time++;
                for (auto& proc : p)
                    if (!proc.added && proc.arrival <= time) {
                        (proc.priority == 1 ? q1 : q2).push(&proc);
                        proc.added = true;
                    }
            }
            curr->remaining -= t;
            if (curr->remaining > 0) q1.push(curr);
            else {
                curr->completion = time;
                curr->turnaround = curr->completion - curr->arrival;
                curr->waiting = curr->turnaround - curr->burst;
                completed++;
            }
        }
        else if (!q2.empty()) {
            Process* curr = q2.front(); q2.pop();
            for (int i = 0; i < curr->burst; i++) {
                gantt.push_back(curr->pid);
                time++;
                for (auto& proc : p)
                    if (!proc.added && proc.arrival <= time) {
                        (proc.priority == 1 ? q1 : q2).push(&proc);
                        proc.added = true;
                    }
            }
            curr->completion = time;
            curr->turnaround = curr->completion - curr->arrival;
            curr->waiting = curr->turnaround - curr->burst;
            completed++;
        }
        else {
            gantt.push_back("Idle");
            time++;
        }
    }

    
    vector<string> compressed;
    for (size_t i = 0; i < gantt.size(); i++)
        if (i == 0 || gantt[i] != gantt[i-1])
            compressed.push_back(gantt[i]);

    cout << "\nGantt Chart: ";
    for (size_t i = 0; i < compressed.size(); i++) {
        cout << compressed[i];
        if (i + 1 < compressed.size()) cout << " → ";
    }
    cout << "\n";

    cout << "Process | Arrival | Burst | Priority | Waiting | Turnaround\n";
    cout << "------------------------------------------------------------\n";

    double totalWT = 0, totalTAT = 0;
    for (auto& proc : p) {
        cout << left << setw(7) << proc.pid << " | "
             << setw(7) << proc.arrival << " | "
             << setw(5) << proc.burst << " | "
             << setw(8) << proc.priority << " | "
             << setw(7) << proc.waiting << " | "
             << setw(10) << proc.turnaround << "\n";
        totalWT += proc.waiting;
        totalTAT += proc.turnaround;
    }
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << totalWT / n << "\n";
    cout << "Average Turnaround Time: " << totalTAT / n << "\n";

    return 0;
}

