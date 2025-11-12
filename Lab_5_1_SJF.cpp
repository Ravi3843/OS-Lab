#include <iostream>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, bt, wt, tat, ct;
    bool completed; // to mark if process is done
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    Process p[20];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        cout << "Enter Arrival Time and Burst Time of P" << i + 1 << ": ";
        cin >> p[i].at >> p[i].bt;
        p[i].completed = false; // initially not done
    }

    int completed = 0, time = 0;
    float totalWT = 0, totalTAT = 0;
    cout << "\nExecution Order: ";

    while (completed < n) {
        int idx = -1, minBT = 9999;
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            time++;
            continue;
        }

        cout << "P" << p[idx].id << " ";
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;
        p[idx].completed = true; // mark as done
        completed++;
    }

    cout << "\n\nProcess\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++)
        cout << "P" << p[i].id << "\t" 
             << p[i].at << "\t" 
             << p[i].bt << "\t" 
             << p[i].wt << "\t" 
             << p[i].tat << endl;

    cout << "\nAverage Waiting Time: " << totalWT / n;
    cout << "\nAverage Turnaround Time: " << totalTAT / n;
    return 0;
}
