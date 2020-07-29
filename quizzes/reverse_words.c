#include <assert.h>
#include <stdio.h>
#include <string.h>


void ReverseWords(char *str1)
{
	char *str2 = NULL;
	char *start = NULL;
	char temp = 0;
	char *curr = NULL;
	char *end = NULL;
	
	assert(str1);
	
	str2 = str1 + strlen(str1);
	start = str1;
	end = str2;
	
	while (str1 != str2)
	{
		temp = *str1;
		*str1 = *str2;
		*str2 = temp;
		++str1;
		--str2;
	}
	
	str1 = start;
	str2 = str1;
	curr = str1;
	
	while (*str1)
	{
		while (*curr != 32) /*32*/
		{
			++curr;
			++str2;
		}
		while (str1 != str2)
		{
			temp = *str1;
			*str1 = *str2;
			*str2 = temp;
			++str1;
			--str2;
		}
		++curr;
		str1 = curr;
		str2 = curr;
	}
	str1 = start;
}

int main()
{
	char *str = "alon went to rd57";
	ReverseWords(str);
	printf("%s \n", str);
	
	return 0;
}
	
	
