#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*calloc*/


/******************************************************************************/
typedef struct stack
{
	size_t element_size;
	void *current;
	void *head;
}stack_t;


/******************************************************************************/

/*allocates mem space for struct stack_t and capacity * element_size*/
stack_t *StackCreate(size_t capacity, size_t element_size)
{
	
	stack_t *stack = NULL;
	
	/*mem space for stack_t*/
	stack = (stack_t*)malloc(sizeof(stack_t)); 
	if (!stack)
	{
		return NULL;
	}
	/*mem space for the array of element_size * number of elements*/
	stack->head = (void*)malloc(capacity * element_size);  
	if (!stack->head)
	{
		free(stack); stack = NULL;
		
		return NULL;
	}
	stack->current = stack->head;
	stack->element_size = element_size;
	
	/*return the pointer to array*/
	return (stack);
} 

/*inserts a given value into the array as the first element and pushes all other 
	one position */
int StackPush(stack_t *stack, const void *val)
{
	int ret_val = 1;
	/*void *temp = NULL;*/
	
	assert(stack);
	assert(val);
	
	stack->current = memcpy(stack->current, val, stack->element_size);
	stack->current = (char*)stack->current + stack->element_size;
	if(NULL == stack->current )
	{
		ret_val = 0;
	}
	
	return (ret_val);
}

/* takes ptr current and pushes it back one element in the array*/
void StackPop(stack_t *stack)
{
	assert(stack);
	
	stack->current = (char*)stack->current - stack->element_size;	
}

/* return a ptr to the last element in the array (lifo)*/
void *StackPeek(stack_t *stack)
{
	assert(stack);
	
	return ((char*)stack->current - stack->element_size);
}

/*if ptr head is equal to ptr current position then array should be empty*/
int StackIsEmpty(const stack_t *stack)
{
	assert(stack);
	if (stack->head == stack->current)
	{
		return 1;
	}
	
	return 0;
}

/*divides the difference between ptr current and ptr head by element_size to 
	find number of current elemnts int the array*/
size_t StackSize(const stack_t *stack)
{
	size_t size = 0;
	
	assert(stack);
	
	size = ((char*)stack->current - (char*)stack->head) / stack->element_size;
	
	return(size);
}

/* frees ptr head , stack and initialize current to NULL */
void StackDestroy(stack_t *stack)
{
	assert(stack);
	assert(stack->head);
	
	stack->current = NULL;
	free(stack->head); stack->head = NULL;
	free(stack); stack = NULL;
}	
	



























