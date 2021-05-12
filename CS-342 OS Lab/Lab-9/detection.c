#include<stdio.h>
#define m1 1000
int max_res[m1];
int reqmat[m1][m1];
int allocmat[m1][m1];
int work[m1];
int finish[m1];
int search_acc(int p,int r){
   for(int i=0;i<p;i++){
   	if(finish[i]==0){
   		int c=0;
   		for(int j=0;j<r;j++){
          if(reqmat[i][j]>work[j]){
          	c++;
          }
   		}
   		if(c==0){
   			return i;
   		}
   	}
   }
   return -1;
}

int main(){

	int p,r;
	printf("Enter the no of process: ");
	scanf("%d",&p);
	printf("Enter the no of resources: ");
	scanf("%d",&r);
	int i,j;
	for(i=0;i<r;i++){
		printf("Total Amount of the Resource R%d : ",i+1);
        scanf("%d",&max_res[i]);
	}

	printf("Enter the request matrix:\n");
	
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
            scanf("%d",&reqmat[i][j]);
		}
	}

	printf("Enter the allocation matrix:\n");
	for(i=0;i<p;i++){
		for(j=0;j<r;j++){
            scanf("%d",&allocmat[i][j]);
		}
	}
	int cnt=0;
	for(j=0;j<r;j++){
		int sum=0;
		for(i=0;i<p;i++){
           sum=sum+allocmat[i][j];
		}
		work[j]=max_res[j]-sum;
	}
	for(i=0;i<p;i++){
		finish[i]=0;
	}
    for(i=0;i<p;i++){
      int c=0;
      for(j=0;j<r;j++){
      	if(allocmat[i][j]>0){
      		c++;
      	}
      }
      if(c==0){
      	finish[i]=1;
      	cnt++;
      }
    }
    int exi=0;
    while(cnt!=p){
        int te=search_acc(p,r);
        if(te==-1){
        	break;
        }
        else{
        	for(j=0;j<r;j++){
        		work[j]=work[j]+allocmat[te][j];
        		finish[te]=1;
        		cnt++;
        	}
        }
     }

     for(i=0;i<p;i++){
     	if(finish[i]==0){
     		exi++;
     	}
     }
    
     if(exi){
     	printf("Deadlock detected\n");
     }
     else{
     	printf("There is no chance for Deadlock because there was atleast one safe state\n");
     }



}



























// Enter the no of process: 4
// Enter the no of resources: 5
// Total Amount of the Resource R1: 2
// Total Amount of the Resource R2: 1
// Total Amount of the Resource R3: 1
// Total Amount of the Resource R4: 2
// Total Amount of the Resource R5: 1
// Enter the request matrix:
// 0 1 0 0 1
// 0 0 1 0 1
// 0 0 0 0 1
// 1 0 1 0 1
// Enter the allocation matrix:
// 1 0 1 1 0
// 1 1 0 0 0
// 0 0 0 1 0
// 0 0 0 0 0