#include <stdio.h>
#include <string.h>  
#define MAX 1000

// Number of Processes and Resources
int proc, res;

// Utility Function to Capture safe sequences
int sequences(int Request[MAX][MAX], int Allocation[MAX][MAX],
		   int Work[MAX], int Finish[MAX], int temp[MAX], int index)
{
	// If index reaches number of processes, 
	// Print Sequences
	if(index == proc)
	{
		for(int i = 0; i < proc; i++)
			printf("P%d->", temp[i]);
		printf("\b\b  \n");
		return 0;
	}

	int i = 0;
	int loop = 0;

	// Loop for all processes
	for (int i = 0; i < proc; i++)
	{
		// Check availability of resources
		int flag = 0;
		for(int j = 0; j < res; j++)
		{
			if(Request[i][j] > Work[j])
				flag = 1;
		}
		// If unfinished and resources available
		if(flag == 0 && Finish[i] == 0)
		{
			for(int j = 0; j < res; j++)
				Work[j] += Allocation[i][j];
			Finish[i] = 1;
			temp[index] = i;

			// Recursive call for other sequences
			sequences(Request, Allocation, Work, Finish, temp, index + 1);
			for(int j = 0; j < res; j++)
				Work[j] -= Allocation[i][j];
			Finish[i] = 0;
		}
	}
}

int main()
{
	// Initiate arrays
	int Available[MAX];
	int Request[MAX][MAX];
	int Allocation[MAX][MAX];
	int Work[MAX];
	int Finish[MAX];
	int temp[MAX];
	int index = 0;

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

	// Max Matrix
	printf("Enter the Max Matrix:\n");
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

	// Calculate Availability Matrix
	for(int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			Available[j] -= Allocation[i][j];
		}
	}

	// Calculate Request Matrix
	for(int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			Request[i][j] -= Allocation[i][j];
		}
	}

	// Copy Available Matrix into Work Matrix
	memcpy(Work, Available, res * sizeof(int));
	// Set all processes to unfinished
	memset(Finish, 0, proc * sizeof(int));

	printf("\nSafe Sequences are:\n");
	sequences(Request, Allocation, Work, Finish, temp, index);
}