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
	
	float alpha=0.5;
	float appBurst[n+1];
	appBurst[0]=10;
	printf("Actual Burst time\t Estimste Burst time\n");
	
	for(int i=1; i<n+1; i++){
		appBurst[i]=(alpha*arr[i-1])+((1-alpha)*appBurst[i-1]);
	}
	
	for(int i=0; i<n; i++){
		printf("%d\t\t\t\t%f\n", arr[i],appBurst[i+1]);
	}
   	return 0;
 }
