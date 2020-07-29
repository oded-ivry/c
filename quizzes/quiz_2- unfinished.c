#include<stdio.h>
#define LOWER(x) ((x>='A'&&x<='Z')?(x+32):x)

void TF(int num)
{
	int i = 1;
	
	for ( i; i <= num; ++i)
	{
		if ( (i % 3 == 0) && (i % 5 == 0) )
		{
			printf("TF\n");
		}
		else if (i % 3 == 0)
		{
			printf("T\n");
		}
		else if (i % 5 == 0)
		{
			printf("F\n");
		}
		else
		{
			printf("%d\n",num);
		}
	}
}

char *Reversed(char *str)
{
	char *start = str;
	char *end   = (str + strlen(str) - 1);
	
	assert(str != NULL );
	
	while ( start < end)
	{
		temp   = LOWER(*end);
		*end   = LOWER(*start);
		*start = temp;
		++start;
		--end;
	}
	
	return (str);
}
	
	







int main()
{
	int num = 80;
	char str[] = "odedODED";
	TF(num);
	printf("%s \n",Reveresed(str);
	
	return 1;
}







