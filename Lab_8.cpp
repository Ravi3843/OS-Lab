#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> max(n, vector<int>(m)), alloc(n, vector<int>(m)), need(n, vector<int>(m));
    vector<int> avail(m), work(m);
    vector<bool> finish(n, false);
    vector<int> safeSeq;

    cout << "\nEnter Max matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "\nEnter Allocation matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "\nEnter Available resources:\n";
    for (int j = 0; j < m; j++) {
        cin >> avail[j];
        work[j] = avail[j];
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    // Display matrices
    cout << "\nProcess\tAllocation\tMax\t\tNeed\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i << "\t";
        for (int j = 0; j < m; j++) cout << alloc[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < m; j++) cout << max[i][j] << " ";
        cout << "\t\t";
        for (int j = 0; j < m; j++) cout << need[i][j] << " ";
        cout << endl;
    }

    cout << "\nAvailable resources: ";
    for (int j = 0; j < m; j++) cout << avail[j] << " ";
    cout << endl;

    // Banker's Algorithm to find safe sequence
    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                if (canAllocate) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) break;
    }

    // Output result
    if (count == n) {
        cout << "\nSystem is in a SAFE state.\nSafe sequence: ";
        for (int i = 0; i < n; i++)
            cout << "P" << safeSeq[i] << (i == n - 1 ? "\n" : " -> ");
    } 
    else {
        cout << "\nSystem is in an UNSAFE state.\n";
    }

    return 0;
}
