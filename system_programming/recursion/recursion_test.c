#include <stdio.h>
#include <string.h>
#include "recursion.h"
#define LIST_SIZE 10

#define TESTCASE(text, condition) printf(text); (condition) ? printf("OK\n"):\
														printf("FAIL\n")


void PrintIntsSLN(sl_node_t *sln)
{
	while (sln != NULL)
	{
		printf("%d, ", *(int*)sln->data);
		sln = sln->next;
	}
	printf("\n");
}
/******************************************************************************/
void FibTest()
{
	unsigned int i = 0;
	size_t n = 6;
	
	for(i = 0; i < n; ++i) 
	{
		printf("%lu ", Fibonacci(i));            
	}
	printf("\n");
	
}


void StrLenTest()
{
	char str[] = "12345";

	printf("%s ---> ",str);
	printf("%lu \n", StrLen(str));

}


void StrCmpTest()
{
	char str1[] = "oded";
	char str2[] = "odel";
	
	printf("StrCmp = %d \n", StrCmp(str1,str2));
}


void StrCpyTest()
{
	char str1[] = "oded";
	char str2[] = "odel";

	StrCpy(str1,str2);
	
	printf("StrCpy : oded ---> %s \n", str1);
}

void StrCatTest()
{
	char str1[100] = "oded";
	char str2[5] = "odel";

	printf("StrCat : oded + odel ---> %s \n", StrCat(str1,str2));
}

void SLFlipNodesTest()
{
	int i = 0;
	int arr[6] = {1,2,3,4,5,6};
	sl_node_t *node[6];
	sl_node_t *reversed_list = NULL;
	
		
	node[0] = SLCreateNode(&arr[i], NULL);
	
	for (i = 1; i < 6; ++i)
	{
		node[i] = SLCreateNode(&arr[i], node[i - 1]);
	}
	
	printf("Original list : ");
	PrintIntsSLN(node[5]);
	
	reversed_list = SLFlipNodes(node[5]);
	
	printf("Reversed list : ");
	PrintIntsSLN(reversed_list);
	
}

void StrStrTest()
{
	char str1[100] = "oded";
	char str2[5] = "odel";

	printf("StrCat : oded + odel ---> %s \n", StrCat(str1,str2));
}

void TestStackSort()
{
	stack_t *stk = NULL;
	int arr[6] = {1,2,3,4,5,6};
		
	printf("stack sort: \n");	
	
	stk = StackCreate(6, sizeof (int));
	
	StackPush(stk, &arr[4]);
	StackPush(stk, &arr[0]);
	StackPush(stk, &arr[5]);
	StackPush(stk, &arr[2]);
	StackPush(stk, &arr[1]);
	StackPush(stk, &arr[3]);
	

	printf("stack before: ");		
	while (!StackIsEmpty(stk))
	{
		printf("%d, ",*(int*)StackPeek(stk));
		StackPop(stk);
	}
	printf("\n");
	
	StackPush(stk, &arr[4]);
	StackPush(stk, &arr[0]);
	StackPush(stk, &arr[5]);
	StackPush(stk, &arr[2]);
	StackPush(stk, &arr[1]);
	StackPush(stk, &arr[3]);
	
	StackSort(stk);		
	
	printf("stack after: ");		
	while (!StackIsEmpty(stk))
	{
		printf("%d, ", *(int*)StackPeek(stk));
		StackPop(stk);
	}
	printf("\n");
	
	StackDestroy(stk);	
}

void TestStrStr()
{
	char *haystack_arr[] = {"1234", "abc123", "456", "A", ""};
	char *needle_arr[] = {"234", "abc123", "45678", "A", "Abc123"};
	char *my_res_arr[5] = {NULL};
	char *res_arr[5] = {NULL};
	size_t i = 0;
	int err_counter = 0;
	
	for (; i < sizeof(haystack_arr) / sizeof(haystack_arr[0]); ++i)
	{
		my_res_arr[i] = StrStr(haystack_arr[i], needle_arr[i]);
		res_arr[i] = strstr(haystack_arr[i], needle_arr[i]);
		
		if (my_res_arr[i] != res_arr[i])
		{
			++err_counter;
			printf("\nexp: %s, got: %s\n", res_arr[i], my_res_arr[i]);
		}
	}
	
	TESTCASE("\nStrStr: ", !err_counter);
}

/******************************************************************************/
int main()
{
/*	printf("Fibonacci test: ");*/
/*	FibTest();*/
/*	*/
/*	printf("StrLen test: ");*/
/*	StrLenTest();*/
/*	*/
/*	StrCmpTest();*/
/*	*/
/*	StrCpyTest();*/
	
/*	StrCatTest();*/

/*	StrStrTest();*/
	
/*	SLFlipNodesTest();*/

/*	TestStackSort();*/
	TestStrStr();
	return 0;
}
	
