#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

struct Process {
    string pid;
    int at, bt, pr, wt, tat, rt;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) {
        cout << "Enter ProcessID, ArrivalTime, BurstTime, Priority(1=High,2=Low): ";
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;
        p[i].rt = p[i].bt;
    }

    queue<int> q1, q2;
    int time = 0, completed = 0, tq = 3;
    vector<string> gantt;

    while (completed < n) {
        // Add newly arrived processes to their queues
        for (int i = 0; i < n; i++)
            if (p[i].at == time)
                (p[i].pr == 1 ? q1 : q2).push(i);

        if (!q1.empty()) { // High priority: Round Robin
            int i = q1.front(); q1.pop();
            gantt.push_back(p[i].pid);
            int exec = min(tq, p[i].rt);
            p[i].rt -= exec; time += exec;

            // Check for new arrivals during execution
            for (int t = 1; t <= exec; t++)
                for (int j = 0; j < n; j++)
                    if (p[j].at == time - exec + t)
                        (p[j].pr == 1 ? q1 : q2).push(j);

            if (p[i].rt > 0) q1.push(i);
            else { completed++; p[i].tat = time - p[i].at; p[i].wt = p[i].tat - p[i].bt; }
        }
        else if (!q2.empty()) { // Low priority: FCFS
            int i = q2.front(); q2.pop();
            gantt.push_back(p[i].pid);
            time += p[i].rt; p[i].rt = 0;
            completed++;
            p[i].tat = time - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
        }
        else time++; // idle CPU
    }

    cout << "\nGantt Chart: ";
    for (auto &x : gantt) cout << x << " ";
    cout << "\n\nProcess\tAT\tBT\tPR\tWT\tTAT\n";
    double avgWT = 0, avgTAT = 0;
    for (auto &x : p) {
        cout << x.pid << "\t" << x.at << "\t" << x.bt << "\t" << x.pr
             << "\t" << x.wt << "\t" << x.tat << endl;
        avgWT += x.wt; avgTAT += x.tat;
    }
    cout << fixed << setprecision(2);
    cout << "Average Waiting Time: " << avgWT / n << endl;
    cout << "Average Turnaround Time: " << avgTAT / n << endl;
}