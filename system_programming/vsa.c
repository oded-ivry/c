#include <assert.h> /*asserts*/
#include <stdlib.h> /*labs*/
#include "./include/vsa.h" /*API for vsa*/

#define META_DATA_SIZE sizeof(vsa_t)
#define WORD_SIZE sizeof(size_t)

/******************************************************************************/
struct vsa
{
	long int block_size;
	
#ifndef NDEBUG
	size_t flag;
#endif
};
/******************************************************************************/
/* Advances current position to the next available block's position*/
static vsa_t *NextAvailableBlock(vsa_t *block)
{
	block = (vsa_t*)((char*)block + META_DATA_SIZE + (labs(block->block_size)));

	return(block);
}

/* Return a boolean value to whether the next block is empty or not */ 
static int IsNextBlockEmpty(vsa_t *block)
{
	long unsigned int move = labs(block->block_size);
	
	if (0 >= ((vsa_t*)((char*)block + move + META_DATA_SIZE))->block_size)
	{
		return 0;
	}
	
	return 1;	
}

/*Gives the next smaller number that divides by 8*/ 
static size_t PaddingDown(size_t num) 
{
    return (num - (num % 8));
}

/*Gives the next larger number that divides by 8*/ 
static size_t PaddingUp(size_t num) 
{
    while (0 != num % WORD_SIZE)
    {
    	++num;
    }
    
    return (num);
}

/******************************************************************************/	
/*	
*	create the vsa pool,
*	time complexity: O(1) 
*	@param memory_segment: pointer to alocated memory
*	@param segment_size:  size of memory_segment
*	@return pointer to v_pool, if fails return NULL
*/
vsa_t *VSAInit(void *memory_segment, size_t segment_size)
{
	vsa_t *v_pool = NULL;	
	size_t padded = 0;
	
	assert(memory_segment);
	assert(segment_size > 2 * META_DATA_SIZE);
	
	v_pool = memory_segment;
	padded = PaddingDown(segment_size);

	/*Sets correct size with paddings and Metadata*/
	v_pool->block_size = (long int)padded - (2 * META_DATA_SIZE);

	#ifndef NDEBUG
	v_pool->flag = 0xDEADBEEF;
	#endif
	
	/*Sets the last metadata to 0*/
	((vsa_t*)((char*)v_pool + padded - META_DATA_SIZE))->block_size = 0;
	
	#ifndef NDEBUG
	((vsa_t*)((char*)v_pool + padded - META_DATA_SIZE))->flag = 0xDEADBEEF;
	#endif
	return (v_pool);
}

/*	
*	allocate a block from the vsa pool
*	time complexity: O(n)
*	@param v_pool: pointer to the managing unit of the vsa
*	@param size: how much byte in the alocation requst
*	@return pointer to  a block from the v_pool, if fails return NULL
*/
void *VSAAlloc(vsa_t *v_pool, size_t size)
{
	size_t largest_chunk_size = 0;
	vsa_t *next_block = NULL;
	
	assert(v_pool);
	
	/*Defregments the memory + returns largest chunk size*/
	largest_chunk_size = VSALargestChunkAvailable(v_pool);
	size = PaddingUp(size);
	
	/*Checks if theres enough free space to allocate*/
	if (largest_chunk_size < size)
	{
		return NULL;
	}
	
	while (v_pool->block_size)
	{
		/*If value negative then the block is allocated -> move to next block*/
		if (0 > v_pool->block_size)
		{
			v_pool = NextAvailableBlock(v_pool);
		}
		else
		{	
			/*Is there enough space to allocate?*/
			if ((size_t)v_pool->block_size >= size)
			{
				/*Is there not enough space for allocation + metadata only?*/
				if ((size_t)v_pool->block_size <= size + META_DATA_SIZE)
				{
					v_pool->block_size *= -1;

					break;
				}
				/*Allocation + new metadata setup ; present metadata update*/
				else
				{
					next_block = (vsa_t*)((char*)v_pool + META_DATA_SIZE + size);
					next_block->block_size = 
						(v_pool->block_size - size - META_DATA_SIZE);
						
					#ifndef NDEBUG
					next_block->flag = 0xDEADBEEF;
					#endif
				
					v_pool->block_size = -1 * size;
					
					break;
				}
			}
			else
			{
				v_pool = NextAvailableBlock(v_pool);
			}
		}
	}
	
	return ((char*)v_pool + META_DATA_SIZE);
}
		
/*	
*	free the alocated memory
*	time complexity: O(1)
*	@param block: pointer to alocated block
*	undefined whan alrady free or if invalid pointer
*/
void VSAFree(void *block)
{
	assert(block);
	assert(((vsa_t*)block - 1)->flag == 0xDEADBEEF);
	
	((vsa_t*)block - 1)->block_size *= -1;
}	
	
/*	
*	finds the size of the largest empty chunk
*	time complexity: O(n)
*	@param v_pool: pointer to the managing unit of the vsa
*	@return the size of the largest chunk
*/
size_t VSALargestChunkAvailable(vsa_t *v_pool)
{
	size_t largest_chunk_size = 0;
		
	assert(v_pool);

	/*iterate through the memory till you reach last meata data*/
	while (v_pool->block_size)
	{
		/*if the block is allocated: move to next block*/
		if (v_pool->block_size < 0)
		{
			v_pool = NextAvailableBlock(v_pool);
		}
		else
		{	/*if the current block is lrager than the lragest chunk so far:
				set the new largest chunk to current block*/
			if ((size_t)v_pool->block_size > largest_chunk_size)
			{
				largest_chunk_size = v_pool->block_size;
			}
			/*if the next block is free: add its size to current 
				argest chunk size*/ 
			if (IsNextBlockEmpty(v_pool))
			{
				v_pool->block_size +=
					(NextAvailableBlock(v_pool))->block_size + META_DATA_SIZE;
			}
			else
			{
				v_pool = NextAvailableBlock(v_pool);
			}
		}
	}	
	
	return (PaddingDown(largest_chunk_size));	
}


