			Lab-9 Report
----------------------------------------------------------
Name : P. V. Sriram
Roll No. : 1801CS37
----------------------------------------------------------
Q1)

To Compile: gcc Q1.c -o Q1
To Run: ./Q1

Input:
SIMULATION OF DEADLOCK PREVENTION                                                                       
Enter the number of Processes: 4                                                                        
Enter the no of Resources: 5                                                                            
Enter the Allocation Matrix:                                                                            
1 1 0 0                                                                                                 
0 1 0 0                                                                                                 
1 0 0 0                                                                                                 
1 0 1 0                                                                                                 
0 0 0 0                                                                                                 
Enter the Max Matrix:                                                                                   
1 1 0 1                                                                                                 
1 1 0 0                                                                                                 
1 1 0 1                                                                                                 
1 0 1 0                                                                                                 
1 1 1 1                                                                                                 
Enter the Availability Matrix:                                                                          
0 0 0 0 1 

Output:
- Failing: Mutual exclusion: By allocating required resources to process 0 deadlock is prevented        
- Lack of Preemption                                                                                    
- Deadlock can be prevented by allocating needed resources                                              
- Failing: Hold and Wait condition
----------------------------------------------------------
Q2)

To Compile: gcc Q2.c -o Q2
To Run: ./Q2

Input:
Enter the number of Processes: 4                                                                        
Enter the no of Resources: 5                                                                            
Enter the Total resources:                                                                              
2 1 1 2 1                                                                                               
Enter the Request Matrix:                                                                               
0 1 0 0 1                                                                                               
0 0 1 0 1                                                                                               
0 0 0 0 1                                                                                               
1 0 1 0 1                                                                                               
Enter the Allocation Matrix:                                                                            
1 0 1 1 0                                                                                               
1 1 0 0 0                                                                                               
0 0 0 1 0                                                                                               
0 0 0 0 0 

Output:
Deadlock
----------------------------------------------------------
Q3)

To Compile: gcc Q3.c -o Q3
To Run: ./Q3

Input:
Enter the number of Processes: 5                                                                        
Enter the no of Resources: 3                                                                            
Enter the Total resources:                                                                              
10 5 7                                                                                                  
Enter the Max Matrix:                                                                                   
7 5 3                                                                                                   
3 2 2                                                                                                   
9 0 2                                                                                                   
2 2 2                                                                                                   
4 3 3                                                                                                   
Enter the Allocation Matrix:                                                                            
0 1 0                                                                                                   
2 0 0                                                                                                   
3 0 2                                                                                                   
2 1 1                                                                                                   
0 0 2  

Output:
Safe Sequences are:                                                                                     
P1->P3->P0->P2->P4                                                                                      
P1->P3->P0->P4->P2                                                                                      
P1->P3->P2->P0->P4                                                                                      
P1->P3->P2->P4->P0                                                                                      
P1->P3->P4->P0->P2                                                                                      
P1->P3->P4->P2->P0                                                                                      
P1->P4->P3->P0->P2                                                                                      
P1->P4->P3->P2->P0                                                                                      
P3->P1->P0->P2->P4                                                                                      
P3->P1->P0->P4->P2                                                                                      
P3->P1->P2->P0->P4                                                                                      
P3->P1->P2->P4->P0                                                                                      
P3->P1->P4->P0->P2                                                                                      
P3->P1->P4->P2->P0                                                                                      
P3->P4->P1->P0->P2                                                                                      
P3->P4->P1->P2->P0