#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> lru(vector<int>pages, int f){

    vector<vector<int>>ans;
    vector<int>frame(f,-1);
    vector<int>q;

    for(int page:pages){

        auto it=find(q.begin(),q.end(),page);
        if(it!=q.end()){ 
            q.erase(it);
            ans.push_back({1}); // page hit
        }
        else{
            ans.push_back({0}); // page fault

            if(q.size()==f){
                auto it=find(frame.begin(),frame.end(),q[0]);
                q.erase(q.begin());
                *it=page;
            }
            else{
                frame[q.size()]=page;
            }
        }
        q.push_back(page);
        
        for(int fm:frame)ans.back().push_back(fm);
    }
    return ans;
}

vector<vector<int>> optimal(vector<int>pages, int f){
    int p=pages.size();

    vector<vector<int>>ans;
    vector<int>frame(f,-1);
    map<int,stack<int>>mp; // store page and their next used ind

    mp[-1].push(INT_MAX);
    
    for(int i=p-1;i>=0;i--){ 
        if(mp[pages[i]].empty())mp[pages[i]].push(1e9); 
        mp[pages[i]].push(i);
    }

    for(int page: pages){

        if(find(frame.begin(),frame.end(),page)!=frame.end()){
            ans.push_back({1}); //page hit
        }
        else{
            ans.push_back({0}); // page fault

            int remove=0, nextused=0;
            for(int i=0;i<f;i++){
                if(mp[frame[i]].top()>nextused){
                    nextused=mp[frame[i]].top();
                    remove=i;
                }
            }
            frame[remove]=page;
        }
        mp[page].pop();
        for(int fm:frame)ans.back().push_back(fm);
    }
    return ans;
}

int main(){

    vector<int>pages={7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    vector<vector<int>>ans=optimal(pages,3);
    for(int i=0;i<pages.size();i++){
        for(int j=0;j<=3;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}