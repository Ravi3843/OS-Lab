#include <bits/stdc++.h>
using namespace std;

int main(){
    int nf, np;
    cout<<"Enter no of frames:";
    cin>>nf;
    cout<<"Enter no of pages:";
    cin>>np;

    vector<int> ref(np);
    for(int i=0; i<np; i++) cin>>ref[i];

    vector<int> frames;
    vector<int> lastUsed(nf, -1);   // track recent use time

    int hit = 0, fault = 0;
    int time = 0;

    cout<<"Ref\tFrame 1\tFrame 2\tFrame 3\tStatus\n";

    for(int i=0; i<np; i++){
        int page = ref[i];
        bool found = false;

        // check hit
        for(int j=0; j<frames.size(); j++){
            if(frames[j] == page){
                found = true;
                lastUsed[j] = time;
                break;
            }
        }

        if(found){
            hit++;
        }
        else{
            fault++;

            if(frames.size() < nf){
                frames.push_back(page);
                lastUsed[frames.size()-1] = time;
            }
            else{
                // find LRU index
                int lruIndex = 0;
                int minTime = lastUsed[0];

                for(int j = 1; j < nf; j++){
                    if(lastUsed[j] < minTime){
                        minTime = lastUsed[j];
                        lruIndex = j;
                    }
                }

                frames[lruIndex] = page;
                lastUsed[lruIndex] = time;
            }
        }

        // print output row
        cout << page << "\t";
        for(int j=0; j<nf; j++){
            if(j < frames.size()) cout << frames[j] << "\t";
            else cout << "-\t";
        }
        cout << (found ? "Hit" : "Fault") << endl;

        time++;
    }

    cout<<"Total faults:"<<fault<<" and total hits:"<<hit<<endl;
    cout<<"Fault rate:"<<(float)fault/np;
}
