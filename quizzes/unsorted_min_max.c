#include <stdio.h>
#include <assert.h>

void UnsoretedMinMax(int *arr, size_t size)
{
	size_t i = 0;
	int min = 0;
	int max = 0;
	
	assert(arr);
	
	min = arr[0];
	max = arr[0];
	
	if (size%2)
	{
		++i;
	}
	
	for (; i < size; i+=2)
	{
		if (arr[i] > arr[i+1])
		{
			if (arr[i] > max)
			{
				max = arr[i];
			}
			if (arr[i+1] < min)
			{
				min = arr[i+1];
			}
		}
		else
		{
			if (arr[i+1] > max)
			{
				max = arr[i+1];
			}
			if (arr[i] < min)
			{
				min = arr[i];
			}
		}
	}
	printf("max = %d \nmin = %d \n", max, min);
}

int main()
{
	size_t size = 13;
	int arr[] = {1,2,3,45,6,7,8,9,10,2,-4,-6,-10};
	UnsoretedMinMax(arr,size);
	
	return 1;
}
