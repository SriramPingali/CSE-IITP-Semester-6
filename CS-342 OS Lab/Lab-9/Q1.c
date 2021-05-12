#include <stdio.h>
#include <string.h>  
#define MAX 1000

// Initiate Variables and arrays
int proc, res, done = 0;
int Available[MAX];
int Request[MAX][MAX];
int Allocation[MAX][MAX];
int Finish[MAX];

// Utility Function to
// Simulate Bankers Algorithm
int Bankers() 
{
    // Perform until all 
    // Processes are done
    while (1) 
    {
        done = 0;
        for (int i = 0; i < proc; i++) 
        {
            // Check for Unfinished Process 
            if (Finish[i] == 0) 
            {
            	int k;
            	// Check if required resources
            	// are available 
                for (int j = 0; j < res; j++) 
                {
                    k = j;
                    if (Request[i][j] > Available[j]) 
                    	break;
            	}

            	// If available perform operation
                if (k == res - 1) 
                {
                    for (int j = 0; j < res; j++) 
                    {
                        Available[j] += Allocation[i][j];
                    }

                    Finish[i] = 1;
                    done = 1;
                }
            }
        }
        if (done == 0) 
        	break;
    }
    return 0;
}

// Driver Code
int main() {
    printf("SIMULATION OF DEADLOCK PREVENTION\n");

    // Number of Processes
    printf("Enter the number of Processes: ");
	scanf("%d", &proc);

	// Number of Resources
	printf("Enter the no of Resources: ");
	scanf("%d",&res);

	// Allocation Matrix
    printf("Enter the Allocation Matrix:\n");
	for(int j = 0; j < res; j++)
	{
		for (int i = 0; i < proc; i++)
		{
			scanf("%d", &Allocation[i][j]);
		}
	}

	// Max Matrix
    printf("Enter the Max Matrix:\n");
	for(int j = 0; j < res; j++)
	{
		for (int i = 0; i < proc; i++)
		{
			scanf("%d", &Request[i][j]);
		}
	}

	// Availability Matrix
    printf("Enter the Availability Matrix:\n");
	for(int i = 0; i < res; i++)
		scanf("%d", &Available[i]);

	// Calculate Request Matrix
    for(int i = 0; i < proc; i++)
	{
		for(int j = 0; j < res; j++)
		{
			Request[i][j] -= Allocation[i][j];
		}
	}

	// Set all processes to unfinished
	memset(Finish, 0, proc * sizeof(int));

    // Emulate Bankers Algorithm
    Bankers();
    
    // All processes are done -> No deadlock
    if (done == 0) 
    {
        int flag = 1;
        for (int i = 0; i < proc; i++) 
        {
            if(Finish[i] == 0)
            	flag = 0;
        }
        if(flag) 
        {
            printf("There is no deadlock\n");
            return 0;
        }
    }

    // Avoiding Mutual exclusion, preemption, hold and wait to prevent deadlock
    for (int i = 0; i < proc; i++) 
    {
        if (done == 0) 
        {
            if (Finish[i] == 0) 
            {
                // Recheck if resources are available for Unfinished processes
                printf("- Failing: Mutual exclusion: ");
                for (int j = 0; j < res; j++) 
                {
                    if (Available[j] < Request[i][j]) 
                        Available[j] = Request[i][j];
                }

                // Emulate Bankers Algorithm
                Bankers();

                // Deadlock is avoided
                if (Finish[i]) 
                    printf("By allocating required resources to process %d deadlock is prevented\n", i);
                
                // Recheck if preempted processes have resources to be executed
                printf("- Lack of Preemption\n");
                for (int j = 0; j < res; j++) 
                {
                    if (Available[j] < Request[i][j]) 
                    {
                        Available[j] = Request[i][j];
                    }
                    Allocation[i][j] = 0;
                }

                // Emulate Bankers Algorithm
                Bankers();

                // Deadlock is avoided
                if (Finish[i])
                    printf("- Deadlock can be prevented by allocating needed resources\n");

                // Recheck if Hold and Wait processes have resources to be executed
                printf("- Failing: Hold and Wait condition\n");
                for (int j = 0; j < res; j++) 
                {
                    if (Available[j] < Request[i][j]) 
                        Available[j] = Request[i][j];
                }

                // Emulate Bankers Algorithm
                Bankers();
            }
        }
    }
}
