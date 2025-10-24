#include <stdio.h>

int main(){
	int n;
	printf("Enter no of process:");
	scanf("%d", &n);
	int arr[n];
	printf("Enter burst time for processes:");
	for(int i=0; i<n; i++){
    		scanf("%d", &arr[i]);
	}
	int wait[n];
	float sum=0;
	wait[0]=0;
	for(int i=1; i<n; i++){
   		wait[i]=wait[i-1]+arr[i-1];
   		sum+=wait[i];
   	}
    	printf("Process\t waiting time\n");
 	for(int i=0; i<n; i++){
   		printf("%d\t %d\n", i+1, wait[i]);
   	}
   	printf("Average waiting time:%f\n",sum/n);
   	return 0;
 }
