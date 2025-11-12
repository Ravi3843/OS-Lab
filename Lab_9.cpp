#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int findBlock(vector<int>& block, int size, string type) {
    int idx = -1;
    if (type == "First") {
        for (int i = 0; i < block.size(); i++)
            if (block[i] >= size) return i;
    } else if (type == "Best") {
        int best = INT_MAX;
        for (int i = 0; i < block.size(); i++)
            if (block[i] >= size && block[i] < best)
                best = block[i], idx = i;
    } else if (type == "Worst") {
        int worst = -1;
        for (int i = 0; i < block.size(); i++)
            if (block[i] >= size && block[i] > worst)
                worst = block[i], idx = i;
    }
    return idx;
}

int main() {
    int nb, np;
    cout << "Enter number of blocks: "; cin >> nb;
    vector<int> block(nb);
    cout << "Enter block sizes: ";
    for (int& b : block) cin >> b;

    cout << "Enter number of processes: "; cin >> np;
    vector<int> proc(np);
    cout << "Enter process sizes: ";
    for (int& p : proc) cin >> p;

    cout << "Choose method (First/Best/Worst): ";
    string type; cin >> type;

    vector<int> alloc(np, -1);
    vector<int> rem = block;

    for (int i = 0; i < np; i++) {
        int idx = findBlock(rem, proc[i], type);
        if (idx != -1) rem[idx] -= proc[i], alloc[i] = idx;
    }

    cout << "Perform compaction (Y/N)? ";
    char ch; cin >> ch;

    if (ch == 'Y' || ch == 'y') {
        int free = 0;
        for (int r : rem) free += r;
        rem = { free };
        for (int i = 0; i < np; i++)
            if (alloc[i] == -1 && rem[0] >= proc[i])
                rem[0] -= proc[i], alloc[i] = 0;
    }

    cout << "\n--- Final Allocation ---\n";
    cout << "Process\tSize\tBlock\n";
    for (int i = 0; i < np; i++)
        cout << "P" << i + 1 << "\t" << proc[i] << "\t"
             << (alloc[i] == -1 ? "Not Allocated" : "Block " + to_string(alloc[i] + 1)) << "\n";

    int totalFree = 0;
    for (int r : rem) totalFree += r;
    cout << "Total Free Space: " << totalFree << endl;
}
