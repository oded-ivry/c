#ifndef ILRD_STACK_CALC_H
#define ILRD_STACK_CALC_H

typedef enum calc_status{
		SUCCESS,
		SYNTAX_ERR,
		INTERNAL_ERR,
		OVERFLOW,
		DIV_ZERO	
}calc_status_t;

/*	Time compelexity is O(n)	*/

/*
*	Calculate and validates an expression
*
*	@params - pointer to input.
*	@params - pointer to double to store the result.
*			 
*	@return - status of calculation
*/

calc_status_t StackCalc(const char *input, double *result);


#endif /*ILRD_STACK_CALC_H*/
