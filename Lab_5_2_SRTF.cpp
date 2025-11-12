#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;          // Process ID
    int at;          // Arrival Time
    int bt;          // Burst Time
    int rt;          // Remaining Time
    int wt;          // Waiting Time
    int tat;         // Turnaround Time
    int ct;          // Completion Time
    bool completed;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter Arrival Time and Burst Time of P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].id = i + 1;
        p[i].rt = p[i].bt;
        p[i].completed = false;
    }

    int completed = 0, current_time = 0;
    float total_wt = 0, total_tat = 0;
    vector<int> execution_order; // Gantt chart

    while (completed != n) {
        int idx = -1;
        int mn = INT_MAX;

        // Find process with minimum remaining time among arrived ones
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].completed && p[i].rt < mn) {
                mn = p[i].rt;
                idx = i;
            }
        }

        if (idx != -1) {
            execution_order.push_back(p[idx].id); // Record execution
            p[idx].rt--;
            current_time++;

            // If process is completed
            if (p[idx].rt == 0) {
                p[idx].completed = true;
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                total_wt += p[idx].wt;
                total_tat += p[idx].tat;
                completed++;
            }
        } else {
            // No process has arrived yet
            current_time++;
        }
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Turnaround Time = " << (total_tat / n);
    cout << "\nAverage Waiting Time = " << (total_wt / n);

    cout << "\n\nExecution Order:\n";
    for (int pid : execution_order)
    cout << "P" << pid << " ";
    cout << endl;

    return 0;
}
