#include <stddef.h>
#include <stdio.h>

#define NUM_OF_BITS sizeof(int)*8

unsigned int NextSparseNum(unsigned int num)
{
	int i = 0;
	int flag = 1;
	
	++num;
	
	while (flag)
	{
		flag = 0;

		for (i = NUM_OF_BITS - 2; 0 <= i; --i)
		{
			if ((num & (1 << i)) && (num & (1 << (i + 1))))
			{
				flag = 1;
				num += (1 << i);
				for (; 0 <= i; --i)
				{
					num &= ~(1 << i);
				}
			}
		}
	}
	
	return (num);
}

int main()
{
	unsigned int num = 10;
	
	printf("%lu \n", NextSparseNum(num));
	return 0;
}











