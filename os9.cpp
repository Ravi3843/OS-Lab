#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void compactMemory(vector<int>& blocks) {
    vector<int> temp;
    int totalFreeSpace = 0;
    for (int block : blocks) {
        if (block != 0) temp.push_back(block);
        else totalFreeSpace += block;
    }
    blocks = temp;
    blocks.push_back(totalFreeSpace);
}

void allocateMemory(vector<int>& blocks, vector<int>& processes, int strategy) {
    vector<int> allocation(processes.size(), -1);
    cout << "Process Size  Block Allocated  Remaining Block Size" << endl;

    for (int i = 0; i < processes.size(); i++) {
        int idx = -1, bestIdx = -1, worstIdx = -1;
        int bestDiff = INT_MAX, worstDiff = -1;

        for (int j = 0; j < blocks.size(); j++) {
            if (blocks[j] >= processes[i]) {
                int diff = blocks[j] - processes[i];
                if (strategy == 1 && idx == -1) idx = j; // First Fit
                if (strategy == 2 && diff < bestDiff) { bestIdx = j; bestDiff = diff; } // Best Fit
                if (strategy == 3 && diff > worstDiff) { worstIdx = j; worstDiff = diff; } // Worst Fit
            }
        }

        int selectedIdx = (strategy == 1) ? idx : (strategy == 2) ? bestIdx : worstIdx;
        if (selectedIdx != -1) {
            blocks[selectedIdx] -= processes[i];
            cout << "P" << i + 1 << "          Block " << selectedIdx + 1 << "        " << blocks[selectedIdx] << endl;
        } else {
            cout << "P" << i + 1 << "        Not Allocated" << endl;
        }
    }

    cout << "Remaining Block Sizes: ";
    for (int block : blocks) cout << block << " ";
    cout << endl;
}

int main() {
    int numBlocks, numProcesses, strategy;
    cout << "Enter the number of memory blocks: ";
    cin >> numBlocks;
    vector<int> blocks(numBlocks);
    cout << "Enter the sizes of memory blocks: ";
    for (int& block : blocks) cin >> block;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    vector<int> processes(numProcesses);
    cout << "Enter the sizes of processes: ";
    for (int& process : processes) cin >> process;

    cout << "Enter the memory allocation strategy (1 = First Fit, 2 = Best Fit, 3 = Worst Fit): ";
    cin >> strategy;

    char compactionChoice;
    cout << "Perform compaction after allocation? (y/n): ";
    cin >> compactionChoice;

    allocateMemory(blocks, processes, strategy);

    if (compactionChoice == 'y' || compactionChoice == 'Y') {
        compactMemory(blocks);
        cout << "After Compaction, Remaining Block Sizes: ";
        for (int block : blocks) cout << block << " ";
        cout << endl;
    } else {
        cout << "Waiting processes: ";
        for (int i = 0; i < processes.size(); i++) {
            bool allocated = false;
            for (int block : blocks) {
                if (block >= processes[i]) {
                    allocated = true;
                    break;
                }
            }
            if (!allocated) cout << "P" << i + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}

