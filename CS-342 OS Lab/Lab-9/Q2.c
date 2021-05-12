#include <stdio.h>
#include <string.h>  
#define MAX 1000

// Initiate Variables and Arrays
int proc, res;
int Available[MAX];
int Request[MAX][MAX];
int Allocation[MAX][MAX];
int Work[MAX];
int Finish[MAX];

// Utility function to 
// Detect deadlock
int detect()
{
	int i = 0;
	int loop = 0;

	// Loop P numner of times
	while(loop <= proc)
	{
		// Detect start of loop
		if(i == 0)
			loop++;

		// Flag to determine 
		// unavailability of resource 
		int flag = 0;
		for(int j = 0; j < res; j++)
		{
			if(Request[i][j] > Work[j])
				flag = 1;
		}

		// If Unfinished & Resources are available
		if(flag == 0 && Finish[i] == 0)
		{
			for(int j = 0; j < res; j++)
				Work[j] += Allocation[i][j];
			Finish[i] = 1;
		}
		i = (i + 1) % proc;
	}

	// If all process are done
	for(int i = 0; i < proc; i++)
		if(Finish[i] == 0)
			return 1;
	// Else Deadlock
	return 0;
}

// Driver Code
int main()
{
	// Processes
	printf("Enter the number of Processes: ");
	scanf("%d", &proc);

	// Resources
	printf("Enter the no of Resources: ");
	scanf("%d",&res);

	// Total Resources
	printf("Enter the Total resources:\n");
	for(int i = 0; i < res; i++)
		scanf("%d", &Available[i]);

	// Request Matrix
	printf("Enter the Request Matrix:\n");
	for (int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			scanf("%d", &Request[i][j]);
		}
	}

	// Allocation Matrix
	printf("Enter the Allocation Matrix:\n");
	for (int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			scanf("%d", &Allocation[i][j]);
		}
	}

	// Recalculate availability matrix
	for(int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			Available[j] -= Allocation[i][j];
		}
	}

	// Copy available to Work
	memcpy(Work, Available, res * sizeof(int));

	// Set all processes to Unfinished
	memset(Finish, 0, proc * sizeof(int));

	// Simulate
	if(detect())
		printf("Deadlock\n");
	else
		printf("Good\n");
}