#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> lru(vector<int>pages, int f){

    vector<vector<int>>ans;
    vector<int>frame(f,-1);
    vector<int>q;

    for(int page:pages){

        if(find(frame.begin(),frame.end(),page)!=frame.end()){ 
            q.erase(find(q.begin(),q.end(),page));
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

int main(){

    vector<int>pages={0,1,7,2,3,2,7,1,0,3};
    vector<vector<int>>ans=lru(pages,4);
    for(int i=0;i<pages.size();i++){
        for(int j=0;j<=4;j++){
            cout<<ans[i][j]<<" ";
        }
        cout<<endl;
    }


    return 0;
}