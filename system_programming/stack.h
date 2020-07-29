#include <stddef.h>

/*****************************/

typedef struct stack stack_t; 

stack_t* StackCreate(size_t capacity, size_t element_size); /*O(1)*/

int StackPush(stack_t *stack, const void *val);/*O(1)*/

void StackPop(stack_t *stack);/*O(1)*/

void* StackPeek(stack_t *stack);/*O(1)*/

int StackIsEmpty(const stack_t *stack);/*O(1)*/

size_t StackSize(const stack_t *stack);/*O(1)*/

void StackDestroy(stack_t *stack);/*O(1)*/
