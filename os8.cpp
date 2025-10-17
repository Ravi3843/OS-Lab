#include <bits/stdc++.h>
using namespace std;

int main(){
   	int n,m;
	cout<<"enter no of processes";
	cin>> n;
	cout<<"Enter no of resources";
	cin>>m;
	cout<<"Enter value of resources";
	int res[m];
	for(int i=0; i<m; i++){
		cin>>res[i];
	}

	int maxi[n][m];
	cout<<"Enter max amt for each process which needed";
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
	  	      cin>>maxi[n][m];
	  	      
	  	}
	}
	
	cout<<"Enter value for allocation";
	int alloc[n][m];
	int need[n][m];
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
	  	      cin>>alloc[n][m];
	  	    need[i][j]=maxi[i][j]-alloc[i][j];
	  	}
	}
	
	int available[n][m];
	for(int j=0; j<m; j++){
	     int sum=0;
		for(int i=0; i<n; i++){
		   sum+=alloc[i][j];
		}
	  available[i][j]=res[j]-sum
	}
	
	 bool completed[n][m]={false};
	for(int i=0; i<n; i++){
           for(int j=0; j<m; j++){
            if(need[i][j]<available[i][j]) continue;
            else break;
            }
            available[i][j]+=alloc[i][j];
            completed[i][j]=true;
        }
            
	
	
	
		
	
	
	
	
	  
	  
