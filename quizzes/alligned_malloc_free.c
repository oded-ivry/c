#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



														/*פיתרון לא נכון*/
static int IsPowTwo(size_t num)
{	
	return (!(num & (num - 1))); 
}

/******************************************************************************/
void *AlignedMalloc(size_t bytes, size_t align)
{
	void *mem_seg = NULL;
	size_t offset = 0;
	
	while ((bytes % align != 0) && !IsPowTwo(bytes))
	{
		++bytes;
		++offset;
	}
	printf("bytes: %lu \n", bytes);
	printf("align: %lu \n", align);
	printf("offset: %lu \n", offset); 	
	mem_seg = malloc(bytes + sizeof(size_t));
	if (!mem_seg)
	{
		return NULL;
	}
	
	*(size_t*)(((char*)mem_seg + offset)) = offset;
	
	return((char*)mem_seg + offset + sizeof(size_t));
}

/******************************************************************************/
void AllignedFree(void *ptr)
{
	size_t offset = 0;

	assert(ptr);

	ptr = (size_t*)ptr - 1;

	offset = *(size_t*)ptr;
	
	ptr = (void*)((char*)ptr - offset);

/*	while (offset != 0)	*/
/*	{*/
/*		--*(char*)&ptr;*/
/*		--offset;*/
/*	}*/
	
	free(ptr);	
}
/******************************************************************************/
int main()
{
	size_t bytes = 8;
	size_t align = 18;
	void *mem_seg = NULL;

	mem_seg = AlignedMalloc(bytes, align);
	
	printf("%lu \n", (size_t)mem_seg); 

	AllignedFree(mem_seg);
/*	printf("%d \n", IsPowTwo(align));*/
	return 1;
}
