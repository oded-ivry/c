#include <assert.h> /*assert*/
#include "./include/fsa.h" /*API for fsa*/

#define FSA_SIZE sizeof(fsa_t)
#define META_DATA_SIZE 8
#define WORD_SIZE sizeof(size_t)
#define INDIRECT_META_DATA_SIZET *(size_t*)((char*)segment_start + fsa->next_free)

/******************************************************************************/

struct fsa 
{
	size_t next_free;
	size_t block_size;
	size_t n_blocks;
}; 

/*Gives the next number that divides by 8*/ 
static size_t NextWordsize(size_t num) 
{
    while (0 != num % 8)
    {
    	++num;
    }
    
    return (num);
}

static void Swap(size_t *a, size_t *b)
{
	size_t temp = 0;
	
	assert(a);
	assert(b);
	
	temp = *a;
	*a = *b;
	*b = temp;
	
}
/******************************************************************************/

/* Initiates the memory segment and fsa pool
* Undefined behavior when wrong usage of the function - FSASuggestSize O(n)
*
* @param1 - void pointer to memory_segment
* @param2 - segment size 
* @param3 - block size 
* @return - pointer fsa_t struct
*/ 
fsa_t *FSAInit(void *memory_segment, size_t segment_size, size_t block_size)
{
	size_t i = 0;
	
	char *segment_start = NULL;
	fsa_t *fsa = NULL;
	
	assert(memory_segment);
	assert(segment_size >  sizeof(fsa_t) + META_DATA_SIZE + WORD_SIZE);

	segment_start = (char*)memory_segment + FSA_SIZE;
	fsa = memory_segment;
	/*Initialize fsa pool parameters*/
	fsa->next_free = 0;
	fsa->block_size = NextWordsize(block_size) + META_DATA_SIZE;
		fsa->n_blocks = (segment_size - FSA_SIZE)  / fsa->block_size;
	
	/*Initialize blocks + Metadata*/ 
	for (i = 0; i < (fsa->n_blocks); ++i)
	{
		*(size_t*)((char*)segment_start + (i * fsa->block_size)) = 
			(i + 1) * fsa->block_size;	
	}
		
	return (fsa);
}


/* Suggests the appropriate size for the memory segment O(1)
* 
* @param1 - size of the block 
* @param2 - number of blocks 
* @return - number of suggested bytes to allocate
*/
size_t FSASuggestSize(size_t block_size, size_t n_blocks)
{
	return (FSA_SIZE + (n_blocks * (NextWordsize(block_size)) + (n_blocks * META_DATA_SIZE)));
}

/* Allocates a block into the fsa pool  O(1)

* @param - pointer to fsa_pool 
* @return - pointer to a block on success.
*			NULL on failure
*/
void *FSAAlloc(fsa_t *fsa_pool)
{
	size_t allocated_block = 0;
	char *segment_start = NULL;
	
	assert(fsa_pool);
	
	segment_start = (char*)fsa_pool + FSA_SIZE;

	if (fsa_pool->next_free  == fsa_pool->block_size * fsa_pool->n_blocks)
	{
		return NULL;
	}
	
	allocated_block = fsa_pool->next_free;
	Swap(&fsa_pool->next_free, (size_t*)((char*)segment_start + fsa_pool->next_free));
	
	/*points back to the right position of the block*/	
	return (void*)(segment_start + allocated_block + META_DATA_SIZE);
}


/* frees the block from the fsa pool O(1)
* Undefined behavior when the pointer to the block is incorrect
* 
* @param - pointer to a block 
* @return - No return
*/
void FSAFree(void *block)
{
	size_t *temp_metadata_value = 0;
	fsa_t *fsa_pool = NULL;
	
	assert(block);
	
	/*read metadata + return to start point*/
	temp_metadata_value = ((size_t*)block - 1);
	fsa_pool = (fsa_t*)((char*)block - META_DATA_SIZE - *temp_metadata_value - FSA_SIZE);

	Swap(temp_metadata_value, &fsa_pool->next_free);
}

/* counts the number of free blocks O(n)
* 
* @param - pointer to a memory pool
* @return - number of free block 
*/
size_t FSACountFree(fsa_t *fsa_pool)
{
	size_t max = 0;
	size_t current_next_free = 0;
	size_t counter = 0;
	
	assert(fsa_pool);
	
	max = fsa_pool->n_blocks * fsa_pool->block_size;
	
	current_next_free = fsa_pool->next_free;
	while (current_next_free != max)
	{
		++counter;
		current_next_free = *(size_t*)((char*)fsa_pool + FSA_SIZE + current_next_free);
	}
	
	return (counter);		
}











