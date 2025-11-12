#include <bits/stdc++.h>
using namespace std;

struct process{
 int id, at, bt, rt, ct, tat, wt;
 bool completed;
 };

int main(){
   int n;
   cout<<"Enter no of processes:";
   cin>>n;
   vector<process> p(n);
   for(int i=0; i<n; i++){
       cout<<"Enter arrival time and burst time of P"<<i+1<<": ";
       cin>>p[i].at>>p[i].bt;
       p[i].id=i+1;
       p[i].rt=p[i].bt;
       p[i].completed=false;
   }
       vector<int> sequence;
       int completed=0, time=0;
       float tot_tat=0, tot_wt=0;
    while(completed<n){
        int index=-1, minbt=INT_MAX;
            for(int i=0; i<n; i++){
                if(p[i].at<=time && !p[i].completed && p[i].rt < minbt){
                      minbt=p[i].bt;
		              index=i;
                }
            }
        if(index!=-1){
           p[index].rt--;
           sequence.push_back(p[index].id);
           time++;
            if(p[index].rt==0){
                p[index].ct=time;
                p[index].tat=p[index].ct-p[index].at;
                p[index].wt=p[index].tat-p[index].bt;
                p[index].completed=true;
                tot_tat+=p[index].tat;
                tot_wt+=p[index].wt;
                completed++;
            }
        }
        else time++;
    }
     cout<<"Process execution order:";
     for(auto it:sequence){
         if(it==sequence.back()) cout<<it<<endl;
         else cout<<it<<"->";
     }
      cout<<"PID\tAT\tBT\tTAT\tWT"<< endl; 
     for(int i=0; i<n; i++){
         cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
     }
      cout<<"Average waiting time is "<<tot_wt/n<<endl;
       cout<<"Average turnaround time is "<<tot_tat/n<<endl;
}
