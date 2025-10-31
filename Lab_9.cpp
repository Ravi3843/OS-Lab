#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int findBlock(const vector<int>& rem, int size, const string& type) {
    int idx = -1;
    if (type == "First") {
        for (int i = 0; i < rem.size(); i++)
            if (rem[i] >= size) return i;
    } else if (type == "Best") {
        int best = INT_MAX;
        for (int i = 0; i < rem.size(); i++)
            if (rem[i] >= size && rem[i] < best) best = rem[i], idx = i;
    } else if (type == "Worst") {
        int worst = -1;
        for (int i = 0; i < rem.size(); i++)
            if (rem[i] >= size && rem[i] > worst) worst = rem[i], idx = i;
    }
    return idx;
}

int main() {
    int nb, np;
    cout << "Enter number of blocks: "; cin >> nb;
    vector<int> block(nb); cout << "Enter block sizes: ";
    for (int &b : block) cin >> b;

    cout << "Enter number of processes: "; cin >> np;
    vector<int> proc(np); cout << "Enter process sizes: ";
    for (int &p : proc) cin >> p;

    cout << "Choose method (First/Best/Worst): ";
    string method; cin >> method;

    vector<int> rem = block, alloc(np, -1);
    queue<int> wait;

    // Allocate processes
    for (int i = 0; i < np; i++) {
        int idx = findBlock(rem, proc[i], method);
        if (idx != -1) rem[idx] -= proc[i], alloc[i] = idx;
        else wait.push(i);
    }

    char ch;
    cout << "Perform compaction (Y/N)? ";
    cin >> ch;

    if (ch == 'Y' || ch == 'y') {
        int freeSpace = 0;
        for (int r : rem) freeSpace += r;
        rem = {freeSpace};
        queue<int> newWait;
        while (!wait.empty()) {
            int i = wait.front(); wait.pop();
            if (rem[0] >= proc[i]) rem[0] -= proc[i], alloc[i] = 0;
            else newWait.push(i);
        }
        wait = newWait;
    } else {
        int free = 0;
        for (int r : rem) free += r;
        cout << "\nFree space: " << free << "\nWaiting: ";
        queue<int> tmp = wait;
        while (!tmp.empty()) cout << "P" << tmp.front() + 1 << " ", tmp.pop();
        cout << endl;
    }

    cout << "\n--- Final Allocation ---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < np; i++)
        cout << "P" << i + 1 << "\t" << proc[i] << "\t"
             << (alloc[i] == -1 ? "Not Alloc" : "Block " + to_string(alloc[i] + 1)) << endl;

    int free = 0;
    for (int r : rem) free += r;
    cout << "Total Free Space: " << free << endl;

    if (!wait.empty()) {
        cout << "Still waiting: ";
        while (!wait.empty()) cout << "P" << wait.front() + 1 << " ", wait.pop();
        cout << endl;
    } else cout << "All allocated!\n";
}
