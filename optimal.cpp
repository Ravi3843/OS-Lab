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

    int hit = 0, fault = 0;

    cout<<"Ref\tFrame 1\tFrame 2\tFrame 3\tStatus\n";

    for(int i=0; i<np; i++){
        int page = ref[i];
        bool found = false;

        // check hit
        for(int f : frames){
            if(f == page){ found = true; break; }
        }

        if(found){
            hit++;
        }
        else{
            fault++;

            if(frames.size() < nf){
                frames.push_back(page);
            }
            else{
                int optIndex = -1;
                int farthest = -1;

                for(int j=0; j<nf; j++){
                    int curr = frames[j];
                    int nextUse = INT_MAX;   // assume never used again

                    for(int k = i+1; k < np; k++){
                        if(ref[k] == curr){
                            nextUse = k;
                            break;
                        }
                    }

                    if(nextUse > farthest){
                        farthest = nextUse;
                        optIndex = j;
                    }
                }

                frames[optIndex] = page;
            }
        }

        // print line
        cout << page << "\t";
        for(int j=0; j<nf; j++){
            if(j < frames.size()) cout << frames[j] << "\t";
            else cout << "-\t";
        }
        cout << (found ? "Hit" : "Fault") << endl;
    }

    cout<<"Total faults:"<<fault<<" and total hits:"<<hit<<endl;
    cout<<"Fault rate:"<<(float)fault/np;
}
