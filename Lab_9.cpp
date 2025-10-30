#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

int findBlock(const vector<int>& rem, int procSize, const string& method) {
    int idx = -1;
    if (method == "First") {
        for (int j = 0; j < (int)rem.size(); ++j)
            if (rem[j] >= procSize) return j;
    } else if (method == "Best") {
        int best = INT_MAX;
        for (int j = 0; j < (int)rem.size(); ++j)
            if (rem[j] >= procSize && rem[j] < best) { best = rem[j]; idx = j; }
    } else if (method == "Worst") {
        int worst = -1;
        for (int j = 0; j < (int)rem.size(); ++j)
            if (rem[j] >= procSize && rem[j] > worst) { worst = rem[j]; idx = j; }
    }
    return idx;
}

int main() {
    int nb, np;
    cout << "Enter number of memory blocks: ";
    cin >> nb;
    vector<int> blocks(nb);
    cout << "Enter block sizes:\n";
    for (int i = 0; i < nb; ++i) cin >> blocks[i];

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> proc(np);
    cout << "Enter process sizes:\n";
    for (int i = 0; i < np; ++i) cin >> proc[i];

    cout << "Choose allocation method (First / Best / Worst): ";
    string method; cin >> method;

    vector<int> remaining = blocks;
    vector<int> allocation(np, -1);
    queue<int> waiting;

    cout << "\n--- " << method << " Fit Allocation ---\n";

    // Step 1: Allocate all processes first
    for (int i = 0; i < np; ++i) {
        int idx = findBlock(remaining, proc[i], method);
        if (idx != -1) {
            allocation[i] = idx;
            remaining[idx] -= proc[i];
            cout << "P" << i+1 << " (" << proc[i] << ") allocated to Block " << idx+1 << endl;
        } else {
            waiting.push(i);
            cout << "P" << i+1 << " (" << proc[i] << ") is waiting (no suitable block)\n";
        }
    }

    // Step 2: Ask for compaction
    char ch;
    cout << "\nDo you want to perform compaction? (Y/N): ";
    cin >> ch;

    if (ch == 'Y' || ch == 'y') {
        int freeSpace = 0;
        for (int x : remaining) freeSpace += x;

        remaining.clear();
        remaining.push_back(freeSpace); // single big block after compaction

        cout << "\nCompaction done. Total free space = " << freeSpace << endl;

        // Try to allocate all waiting processes
        queue<int> newWait;
        while (!waiting.empty()) {
            int i2 = waiting.front(); waiting.pop();
            if (remaining[0] >= proc[i2]) {
                allocation[i2] = 0;
                remaining[0] -= proc[i2];
                cout << "After compaction: P" << i2+1 << " allocated.\n";
            } else newWait.push(i2);
        }
        waiting = newWait;
    } 
    else { 
        // If No → Show waiting processes and total free space
        int totalFree = 0;
        for (int x : remaining) totalFree += x;

        cout << "\n--- Memory Summary (Before Compaction) ---\n";
        cout << "Total free space available: " << totalFree << endl;

        if (!waiting.empty()) {
            cout << "Waiting processes: ";
            queue<int> temp = waiting;
            while (!temp.empty()) {
                cout << "P" << temp.front()+1 << " ";
                temp.pop();
            }
            cout << endl;
        } else {
            cout << "No waiting processes.\n";
        }
    }

    // Step 3: Final output
    cout << "\n--- Final Allocation Table (" << method << " Fit) ---\n";
    cout << "----------------------------------------\n";
    cout << "Process\tSize\tBlock Allocated\n";
    cout << "----------------------------------------\n";
    for (int i = 0; i < np; ++i) {
        if (allocation[i] != -1)
            cout << "P" << i+1 << "\t" << proc[i] << "\tBlock " << allocation[i]+1 << endl;
        else
            cout << "P" << i+1 << "\t" << proc[i] << "\tNot Allocated\n";
    }
    cout << "----------------------------------------\n";

    // Show final free space
    int finalFree = 0;
    for (int x : remaining) finalFree += x;
    cout << "Final total free space: " << finalFree << endl;

    if (!waiting.empty()) {
        cout << "Still waiting: ";
        while (!waiting.empty()) {
            cout << "P" << waiting.front()+1 << " ";
            waiting.pop();
        }
        cout << endl;
    } else {
        cout << "All processes allocated successfully.\n";
    }

    return 0;
}
