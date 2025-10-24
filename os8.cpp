#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool isSafeState(const vector<vector<int>>& max, const vector<vector<int>>& allocation,
                 const vector<int>& available, vector<int>& safeSequence) {
    int numProcesses = max.size();
    int numResources = available.size();
    
    vector<vector<int>> need(numProcesses, vector<int>(numResources));
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    vector<int> work = available;
    vector<bool> finish(numProcesses, false);

    safeSequence.clear();

    int count = 0;
    while (count < numProcesses) {
        bool found = false;

        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canComplete = true;
                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canComplete = false;
                        break;
                    }
                }

                if (canComplete) {
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    safeSequence.push_back(i);
                    count++;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

int main() {
    int numProcesses, numResources;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resource types: ";
    cin >> numResources;

    vector<int> available(numResources);
    cout << "Enter the available instances of each resource: ";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
    }

    vector<vector<int>> max(numProcesses, vector<int>(numResources));
    cout << "Enter the Max matrix (Max[i][j] for process i and resource j):" << endl;
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> max[i][j];
        }
    }

    vector<vector<int>> allocation(numProcesses, vector<int>(numResources));
    cout << "Enter the Allocation matrix (Allocation[i][j] for process i and resource j):" << endl;
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocation[i][j];
        }
    }

    vector<int> safeSequence;

    if (isSafeState(max, allocation, available, safeSequence)) {
        cout << "System is in a safe state." << endl;
        cout << "Safe sequence: ";
        for (int i = 0; i < safeSequence.size(); i++) {
            cout << "P" << safeSequence[i] << " ";
        }
        cout << endl;
    } else {
        cout << "System is in an unsafe state." << endl;
    }

    return 0;
}

