#include <stdio.h>
#include "stack_calc.h"

#define TEST_SIZE 10
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;36m"
#define RESET "\033[0m"

#define TESTCASE(text, condition)	\
				printf(text);	\
				printf("%s\n", condition ? GREEN "Pass" RESET: RED "Fail" RESET);


/******************************************************************************/

void StackCalcTest()
{
	size_t i = 0;
	const char *input_arr[] = {"(2^3)^2^2",
						 "(5-3.6)",
					     " 5 * 3",
						 "5+3*2",
						 "5/0",
		   	       		 "5+*5",
						 "+*5-3",
						 "5$4",
						 "3+5+",
						 "5+3*2/"};
						 		  
	char *status_string[] = {"SUCCESS",
							 "SYNTAX_ERR",
							 "INTERNAL_ERR",
							 "OVERFLOW",
							 "DIV_ZERO"}; 
	double result = 0;
	double exp_result[] = {4096, 1.4, 15, 11, 0, 0, 0, 0, 0, 0};
	calc_status_t exp_status[] = {SUCCESS,
								   SUCCESS,
								   SUCCESS,
								   SUCCESS,
								   DIV_ZERO,
								   SYNTAX_ERR,
								   SYNTAX_ERR,
								   SYNTAX_ERR,
								   SYNTAX_ERR,
								   SYNTAX_ERR};
	calc_status_t act_status = SUCCESS;
	calc_status_t status = SUCCESS;
	
	printf(BLUE"****************************************\n"RESET);
	
	for (i = 0; i < 10; ++i)
	{
		result = 0;
		act_status = StackCalc(input_arr[i],&result);
		printf("Expected %s = %.2f \n"
				"Actual %s = %.2f \n"
				"Expected Status = %s \n"
				"Actual Status = %s \n",
				 input_arr[i], exp_result[i], input_arr[i], result, status_string[exp_status[i]], status_string[act_status]);
		if ( (exp_result[i] == result) && (exp_status[i] == act_status) )
		{
			printf(GREEN"Pass \n"RESET);
		}
		else
		{
			printf(RED"Fail \n"RESET);
		}
		printf(BLUE"****************************************\n"RESET);
	}
}

/******************************************************************************/
int main()
{
	StackCalcTest();
	return 0;
}
