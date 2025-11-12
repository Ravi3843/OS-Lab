#include <bits/stdc++.h>
using namespace std;


int main(){
    int nf, np;
    cout<<"Enter no of frames:";
    cin>>nf;
    cout<<"Enter no of pages:";
    cin>>np;
    vector<int> ref(np);
    for(int i=0; i<np; i++) cin>> ref[i];
    
    vector<int> frames;
    queue<int> q;
     int hit=0, fault=0;
     cout<<"Ref\tFrame 1\tFrame 2\tFrame 3\tStatus\n";
    for(int i=0; i<np; i++){
        int page=ref[i];
        bool found=false;
        for(auto f:frames) if(f==page){ found=true; break;}
        if(found) hit++;

        else { fault++;

            if(frames.size()<nf){
            frames.push_back(page);
            q.push(page);
            }

            else {
            int oldest=q.front(); q.pop();
              for(int j=0; j<nf; j++){
                if(frames[j]==oldest){
                    frames[j]=page;
                    break;
                }
              }
                 q.push(page);
            }
        }
     cout<<page<<"\t";
      for(int j=0; j<nf; j++){
        if(j<frames.size()) cout<<frames[j]<<"\t";
        else cout<<"-\t";
      }
      if(found) cout<<"Hit"<<endl;
      else cout<<"Fault"<<endl;
    }
    cout<<"Total faults:"<<fault<<" and total hits:"<<hit<<endl;
    cout<<"Fault rate:"<<(float)fault/np;
    return 0;
}