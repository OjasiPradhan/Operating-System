#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include "alloc.h"

int main()
{
	
	if(init())
		return 1;	

	printf("Starting comprehensive tests (see details in code)\n");
	
	
	//test1
	char stringA[4096], stringB[4096], stringC[4096], stringD[4096], stringX[4096];
	for(int i = 0; i < 4095; i++)
	{
		stringA[i] = 'a';
		stringB[i] = 'b';
		stringC[i] = 'c';
		stringD[i] = 'd';
		stringX[i] = 'x';
	}

	stringA[4095] = stringB[4095] = stringC[4095] = stringD[4095] = stringX[4095] = '\0';

	char *strA = alloc(4096);
	char *strB = alloc(4096);
	char *strC = alloc(4096);
	char *strD = alloc(4096);

	for(int i = 0; i < 4095; i++)
	{
		strA[i] = 'a';
		strB[i] = 'b';
		strC[i] = 'c';
		strD[i] = 'd';
	}
	strA[4095] = strB[4095] = strC[4095] = strD[4095] = '\0';

	if(strcmp(stringA, strA) == 0 && strcmp(stringB, strB) == 0 && strcmp(stringC, strC) == 0 && strcmp(stringD, strD) == 0)
	  printf("Test 1 passed: allocated 4 chunks of 1KB each\n");
	else
	  printf("Test 1 failed: A: %d, B: %d, C: %d, D: %d\n", strcmp(stringA, strA), strcmp(stringB, strB), strcmp(stringC, strC), strcmp(stringD, strD));

	//test 2
	
	dealloc(strC);

	char *strX = alloc(4096);
	for(int i = 0; i < 4095; i++)
	{
		strX[i] = 'x';
	}
	strX[4095] = '\0';

	if(strcmp(stringX, strX) == 0)
	  printf("Test 2 passed: dealloc and realloc worked\n");
	else
	  printf("Test 2 failed: X: %d\n", strcmp(stringX, strX));

	//test 3
	
	char stringY[512], stringZ[512];
	for(int i = 0; i < 511; i++)
	{
		stringY[i] = 'y';
		stringZ[i] = 'z';
	}
	stringY[511] = stringZ[511] = '\0';

	dealloc(strB);

	char *strY = alloc(512);
	char *strZ = alloc(512);
	
	for(int i = 0; i < 511; i++)
	{
		strY[i] = 'y';
		strZ[i] = 'z';
	}
	strY[511] = strZ[511] = '\0';

	if(strcmp(stringY, strY) == 0 && strcmp(stringZ, strZ) == 0)
	  printf("Test 3 passed: dealloc and smaller realloc worked\n");
	else
	  printf("Test 3 failed: Y: %d, Z: %d\n", strcmp(stringY, strY), strcmp(stringZ, strZ));


	//test 4:
	dealloc(strZ);
	dealloc(strY);
	strY=alloc(4096);
	for(int i = 0; i < 4095; i++)
	{
		strY[i] = 'x';
	}
	strY[4095] = '\0';

	if(strcmp(stringX, strY) == 0)
	  printf("Test 4 passed: merge worked\n");
	else
	  printf("Test 4 failed: X: %d\n", strcmp(stringX, strX));

	//test 5:
	dealloc(strX);
	dealloc(strY);
	strX= alloc(2048);
	char  stringM[2048];
	for (int i=0;i<2047;i++){
		strX[i]=stringM[i]='z';
	}
	strX[2047]=stringM[2047]='\0';
	if (!strcmp(stringM, strX))
		printf("Test 5 passed: merge alloc 2048 worked\n");
	else
		printf("Test5 failed\n");
	

	if(cleanup())
		return 1;
	return 0;
}
