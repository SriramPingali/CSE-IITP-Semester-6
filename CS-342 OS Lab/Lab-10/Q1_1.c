#include <stdio.h>
#define MAX 1000

int main()
{
	int n;
	char line[MAX];
	FILE* fp;

	fp = fopen("pages.txt", "r");
	fscanf(fp, "%[^\n]" ,line);

	printf("%s\n", line);
}