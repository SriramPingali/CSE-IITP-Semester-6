#include <bits/stdc++.h>

using namespace std;

int data[4294967296];
int univ[1<<5];
int pointer = 0;

int unavailable = 0;
vector<int> unavail;

int fill(int size)
{
	int j = 0;
	for (int i = 0; i < 128; i++)
	{
		if(i == unavail[2*j])
			while(i != unavail[2*j+1])
				i++;
			i++;
			j++;
		data[pointer*(1<<17) + i] = 1;
		size--;

		if(size == 0)
			break;
	}
	pointer++;
	return 0;
}

int add_process(int pid, int proc_size)
{
	univ[pid] = pointer; 
	// fill(proc_size);
	return 0;
}

// int get_address()
// {
// 	int address = (pid * 1<<27) + (page_no * 1<<17) + (frame_off)
// }

int main()
{
	int pid, proc_size;

	cin >> pid >> proc_size;

	add_process(pid, proc_size);
}