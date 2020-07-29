#ifndef ILRD_RECURSION_H
#define ILRD_RECURSION_H

#include "s_list.h"
#include "stack.h"

/* in c file
static void StackInsert(stack_t *data);
*/

long Fibonacci(unsigned int n);

size_t StrLen(const char *str);

int StrCmp(const char *str1, const char *str2);

char *StrCpy(char *dest, const char *src);

char *StrCat(char *dest, const char *src);

char *StrStr(const char* haystack, const char *needle);

void StackSort(stack_t *stack);

sl_node_t *SLFlipNodes(sl_node_t *head);

#endif /*ILRD_RECURSION_H*/
