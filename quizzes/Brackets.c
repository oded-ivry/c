#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <string.h> /* strlen */
#include "../ds/src/stack.h" /* stack.h */

int ValidBrackets(char *str)
{
	int is_valid = 0;	
	char *p = NULL;	
	stack_t *stack = NULL;	

	assert(str);
	
	stack = StackCreate(strlen(str), sizeof(char));

	p = str;
	
	if ((*p != '}') || (*p == ')') || (*p == ']'))
	{
		return 0;
	}
	
	while (*p)
	{
		if ((*p == '}' && *(char *)StackPeek(stack) == '{') ||
			(*p == ')' && *(char *)StackPeek(stack) == '(') ||
			(*p == ']' && *(char *)StackPeek(stack) == '['))
		{
			StackPop(stack);
		}
		else
		{
			StackPush(stack, p);
		}
		++p;
	}
	
	if (StackIsEmpty(stack))
	{
		is_valid = 1;
	}

	return (is_valid);
}

int main()
{
	char brackets[] = "{[)()]}";

	if (ValidBrackets(brackets))
	{
		printf("The brackets are valid.\n");
	}
	else
	{
		printf("The brackets aren't valid.\n");
	}	

	return 0;
}

