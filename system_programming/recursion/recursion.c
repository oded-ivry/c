#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "recursion.h"

typedef enum flags
{
	OFF,
	ON
}flag_t;


/******************************************************************************/
long Fibonacci(unsigned int n)
{
	if (n < 2)
	{
		return (n);
	}
	
	return (Fibonacci(n - 1) +
		   (Fibonacci(n - 2)));
}

/******************************************************************************/
size_t StrLen(const char *str)
{
	if (!*str)
	{
		return 0;
	}
	
	return (1 + (StrLen(str + 1)));
}
/******************************************************************************/
int StrCmp(const char *str1, const char *str2)
{
	
	if (*str1 != *str2)
	{
		return (*str1 - *str2);
	}
	
	++str1;
	++str2;
	
	return(StrCmp(str1,str2));
}
/******************************************************************************/
char *StrCpy(char *dest, const char *src)
{
	
/*	assert (strlen(src) <= strlen(dest));*/
	
	
	if (!*src)
	{
		return (dest);
	}
	
	*dest = *src;
	++dest;
	++src;
		
	return (StrCpy(dest, src));
}
/******************************************************************************/	
char *StrCat(char *dest, const char *src)
{
	char *dest_end = NULL;
	
/*	assert (strlen(src) <= strlen(dest));*/
	
	dest_end = dest + StrLen(dest);
	
	if (!*src)
	{
		return (dest);
	}
	
	*dest_end = *src;
	++dest_end;
	++src;
	*dest_end = '\0';
	
	
		
	return (StrCat(dest, src));
}

/******************************************************************************/
sl_node_t *SLFlipNodes(sl_node_t *head)
{
	sl_node_t *rest = NULL;
	

	if (!head->next)
	{
		return (head);
	}
	
	rest = (SLFlipNodes(head->next));
	
	head->next->next = head;
	head->next = NULL;

	
	return (rest);
}

/******************************************************************************/
static void StackInsert(stack_t *stack, int data)
{
	int temp = 0;
	
	if (StackIsEmpty(stack) || *(int*)StackPeek(stack) >= data)
	{
		StackPush(stack, &data);
		
		return;
	}
	
	temp = *(int*)StackPeek(stack);
	StackPop(stack);
	StackInsert(stack,data);
	StackPush(stack, &temp);
	
}
/****************************************************************************/

void StackSort(stack_t *stack)
{
	int temp = 0;
	
	assert(stack);
	
	if (StackIsEmpty(stack))
	{
		return;
	}
	
	temp = *(int*)StackPeek(stack);
	StackPop(stack);
	StackSort(stack);
	StackInsert(stack,temp);
}

/******************************************************************************/
char *StrStr(const char *haystack, const char *needle)
{
	const char *start = NULL;

	assert(haystack);
	assert(needle);
	
	if (!*needle)
	{ 
		return ((char*)haystack);
	}
	
	if (!*haystack)
	{
		return NULL;
	}
	
	if (*needle == *haystack && StrStr(haystack+1, needle+1) == haystack + 1)
	{
		return ((char*)haystack);	
	}

	return (StrStr(haystack + 1, needle));	
}


































