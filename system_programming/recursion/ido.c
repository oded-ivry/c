#include <stdio.h> /* prints */
#include <string.h>
#include "recursion.h" /* h_file */

#define PRINTFAIL printf("\033[1;31m FAIL\n\033[0m")
#define PRINTPASS printf("\033[1;32m PASS\n\033[0m")
#define TESTCASE(text, condition) printf(text);(condition)?PRINTPASS:PRINTFAIL
#define PEEK_INT(stack) *(int*)StackPeek(stack)

#define TEST_SIZE 5
#define LIST_SIZE 10

void TestStrLenCpyCmpCat()
{
	char *test_len[TEST_SIZE] = {"", "is this long", "is this short", "\\\\\\121333211fdf", "1235489875541214"};
	char *test_cmp1[TEST_SIZE] = {"", "is this long", "is tis short", "\\\\\\121333211fdf", "1235479875541214"};
	char cpyto1[50] = {0};
	char cpyto2[50] = {0};
	int i = 0, counter = 0;
	
	for (i = 0; i < TEST_SIZE; ++i)
	{
		if (StrLen(test_len[i]) == strlen(test_len[i]))
		{
			++counter;
		}
		else
		{
			printf("strlen faild on string : %s\n", test_len[i]);
		}
	}
	TESTCASE("StrLen : ", (counter == TEST_SIZE));
	
	counter = 0;
	
	for (i = 0; i < TEST_SIZE; ++i)
	{
		if (StrCmp(test_len[i], test_cmp1[i]) == strcmp(test_len[i], test_cmp1[i]))
		{
			++counter;
		}
		else
		{
			printf("strcmp faild on strings : %s vs %s\n return is: %d, expec :%d \n", 
			test_len[i], test_cmp1[i], StrCmp(test_len[i], test_cmp1[i]), strcmp(test_len[i], test_cmp1[i]));
		}
	}
	TESTCASE("StrCmp : ", (counter == TEST_SIZE));
	
	counter = 0;
	
	for (i = 0; i < TEST_SIZE; ++i)
	{
		StrCpy(cpyto1, test_len[i]);
		if (0 == strcmp(test_len[i], cpyto1))
		{
			++counter;
		}
		else
		{
			printf("strcpy faild on strings : \"%s\" out is \"%s\"\n", test_len[i], cpyto1);
		}
	}
	TESTCASE("strcpy : ", (counter == TEST_SIZE));
	
	counter = 0;
	
	for (i = 0; i < TEST_SIZE; ++i)
	{
		strcpy(cpyto1, test_len[i]);
		strcpy(cpyto2, test_len[i]);
		strcat(cpyto1, test_cmp1[i]);
		StrCat(cpyto2, test_cmp1[i]);
		if (0 == strcmp(cpyto2, cpyto1))
		{
			++counter;
		}
		else
		{
			printf("strcat faild on expec :  \"%s\" out is \"%s\"\n", cpyto1, cpyto2);
		}
	}
	TESTCASE("strcat : ", (counter == TEST_SIZE));
}

void TestFibonacci()
{
	long fib_exp[TEST_SIZE + 1] = {1, 1 , 2 , 3, 5, 8};
	int i = 0, counter = 0;
	
	for (i = 0; i < TEST_SIZE + 1; ++i)
	{
		if (fib_exp[i] == Fibonacci(i))
		{
			++counter;
		}
		else
		{
			printf("fibonacci returns the %d num as %ld, should be %ld", i, fib_exp[i], Fibonacci(i));
		}
	}
	TESTCASE("fibonacci : ", (counter == TEST_SIZE + 1));
}



void TestStrStr()
{

}

void TestStackSort()
{
	stack_t * stack = NULL;
	int test_arr[LIST_SIZE] = {9, 5, 6, 3, 2, 1, 8, 4, 7, 0};
	int expec[LIST_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int i = 0, counter = 0;
	
	stack = StackCreate(50, sizeof(int));
	
	for (i = 0; i < LIST_SIZE; ++i)
	{
		StackPush(stack, &test_arr[i]);
	}
	
	StackSort(stack);

	for (i = 0; i < LIST_SIZE; ++i)
	{
		if (expec[i] == PEEK_INT(stack))
		{
			++counter;
		}
		else
		{
			printf("sorted stack is not sortet, element #%d is %d, should be %d\n", i,  PEEK_INT(stack), expec[i]);
		}
		StackPop(stack);
	}
	TESTCASE("SortedStack : ", (counter == LIST_SIZE));
	
	StackDestroy(stack);
}


static void SLListPrinter(sl_node_t* head)
{
	while (head)
	{
	printf("%d ", *(int*)head->data);
	head = head->next;
	}
	printf("\n");
}

void TestFliplist()
{
	int i = 0, counter = 0;
	int test[LIST_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	sl_node_t *head = NULL;
	sl_node_t *temp = NULL;
	
	printf("\nTestSLFlip Starts here:\n");
	for (i = LIST_SIZE; 0 <= i; --i)
	{
		head = SLCreateNode(&test[i], head);
	}
	head = SLFlipNodes(head);
	temp = head;
	for (i = LIST_SIZE; 0 < i; --i)
	{
		if (*(int*)temp->data != test[i])
		{
			printf("SLFlip FAIL%d\n", i);
			break;
		}
		else
		{
			++counter;
		}
		temp = temp->next;
		
	}
	if (counter == LIST_SIZE)
	{
		printf("SLFlip PASS\n");
	}
	else
	{
		printf("SLFLIP FAIL\n");
		SLListPrinter(head);
	}
	
	SLFree(head);
}

int main()
{
/*	TestStrLenCpyCmpCat();*/
/*	TestFibonacci();*/
/*	TestStrStr();*/
	TestStackSort();
/*	TestFliplist();*/
	
	return 0;
}
