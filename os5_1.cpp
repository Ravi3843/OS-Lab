#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    bool completed;
};

bool compareByArrival(Process a, Process b) {
    return a.arrival_time < b.arrival_time;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for P" << i + 1 << ": ";
        cin >> processes[i].arrival_time;
        cout << "Enter burst time for P" << i + 1 << ": ";
        cin >> processes[i].burst_time;
        processes[i].completed = false;
    }

    sort(processes.begin(), processes.end(), compareByArrival);

    int current_time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;
    vector<int> sequence;

    while (completed != n) {
        int idx = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
                else if (processes[i].burst_time == min_burst) {
                    if (processes[i].arrival_time < processes[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            processes[idx].waiting_time = current_time - processes[idx].arrival_time;
            current_time += processes[idx].burst_time;
            processes[idx].turnaround_time = current_time - processes[idx].arrival_time;
            processes[idx].completed = true;
            sequence.push_back(processes[idx].pid);
            total_wt += processes[idx].waiting_time;
            total_tat += processes[idx].turnaround_time;
            completed++;
        } else {
            current_time++;
        }
    }

    
    cout << "\nExecution Order of Processes:\n";
    for (int i = 0; i < sequence.size(); ++i) {
        cout << "P" << sequence[i];
        if (i != sequence.size() - 1) cout << " -> ";
    }

    
    cout << "\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n";
    for (const auto& p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival_time << "\t"
             << p.burst_time << "\t" << p.waiting_time << "\t"
             << p.turnaround_time << "\n";
    }

    cout << "\nAverage Waiting Time: " << total_wt / n;
    cout << "\nAverage Turnaround Time: " << total_tat / n << endl;

    return 0;
}

