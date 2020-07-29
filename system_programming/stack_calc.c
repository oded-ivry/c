#include <math.h> /*pow*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*   */
#include <string.h> /*strtod*/
#include "stack.h" /*API for stack*/
#include "stack_calc.h" /*API for stack_calc*/

size_t pow_precedence_addition = 0;
/******************************************************************************/

typedef enum states
{
	WAIT_FOR_NUM,
	WAIT_FOR_OP,
	RESOLVE,
	MAX_STATES
	
}current_state_t;

typedef enum op_precedence
{
	MINUS = 0,
	PLUS = 0,
	MULTIPLY = 1,
	DIVSION = 1,
	BRACKETS_OUT = 2,
	BRACKETS_IN = -2,
	BRACKETS_CLOSE = -1,
	POW_PRECEDEMCE = 3 
		
}op_precendence_t;

typedef struct info
{
	double *result;
	const char *input;
	stack_t *op_stack;
	stack_t *num_stack;	
	current_state_t state;
	calc_status_t status;
}info_t;
	
/******************************************************************************/
static op_precendence_t OPPrecedenceIn(char operand)
{
	op_precendence_t precedence = MINUS;
	
	switch (operand)
	{
		case '*':
			precedence = MULTIPLY;
			break;
		case '/':
			precedence = DIVSION;
			break;
		case '+':
			precedence = PLUS;
			break;
		case '(':
			precedence = BRACKETS_IN;
			break;
		case '^':
			precedence = POW_PRECEDEMCE + pow_precedence_addition -1;
			break;
	}
	
	return (precedence);
}

static op_precendence_t OPPrecedenceOut(char operand)
{
	op_precendence_t precedence = MINUS;
	
	switch (operand)
	{
		case '*':
			precedence = MULTIPLY;
			break;
		case '/':
			precedence = DIVSION;
			break;
		case '+':
			precedence = PLUS;
			break;
		case '(':
			precedence = BRACKETS_OUT;
			break;
		case '^':
			precedence = POW_PRECEDEMCE + pow_precedence_addition;
			break;
	}
	
	return (precedence);
}
/************************Input Functions***************************************/
static void Calculate(info_t *info)
{
	char operand = 0;
	double num1 = 0;
	double num2 = 0;
	
	
	if (StackIsEmpty(info->op_stack))
	{
		info->status = SYNTAX_ERR;
		info->state = RESOLVE;
		return;		
	}
	
	operand =  *(char*)StackPeek(info->op_stack);
	StackPop(info->op_stack);
	
	if (StackIsEmpty(info->num_stack))
	{
		info->status = SYNTAX_ERR;
		info->state = RESOLVE;
		return;		
	}
	
	num1 = *(double*)StackPeek(info->num_stack);
	StackPop(info->num_stack);	
	
	if (StackIsEmpty(info->num_stack))
	{
		info->status = SYNTAX_ERR;
		info->state = RESOLVE;
		return;		
	}
		
	num2 = *(double*)StackPeek(info->num_stack);
	StackPop(info->num_stack);
	
	if (operand == '/' && num1 == 0)
	{
		info->status = DIV_ZERO;
		info->state = RESOLVE;

		return;
	}
	
	switch (operand)
	{
		case '*':
			num2 *= num1;
			break;
		case '/':
			num2 /= num1;
			break;
		case '+':
			num2 += num1;
			break;
		case '-':
			num2 -= num1;
			break;
		case '^':
			num2 = pow(num2, num1);
			break;
	}
	
	StackPush(info->num_stack, &num2);
}

/******************************************************************************/
static void PushNum(info_t *info)
{
	double num = strtod(info->input, (char**)&info->input);
	
	StackPush(info->num_stack, &num);
	info->state = WAIT_FOR_OP;	
}

/******************************************************************************/
static void PushclosingBrackets(info_t *info)
{
	int push_flag = 0;
	
	/*Get operand precedence*/
	op_precendence_t precedence = OPPrecedenceOut(*info->input);

	
	if (StackIsEmpty(info->op_stack))
	{
		info->status = SYNTAX_ERR;
		info->state = RESOLVE;
	}	
	else
	{	
		while (!StackIsEmpty(info->op_stack) && *(char*)StackPeek(info->op_stack) != '(')
		{
			{
				Calculate(info);
			}
		}
		
		if (StackIsEmpty(info->op_stack))
		{
			info->status = SYNTAX_ERR;
			info->state = RESOLVE;
		}	
		else
		{
			StackPop(info->op_stack);
			++info->input;
			info->state = WAIT_FOR_OP;
		}		
	}
}
/******************************************************************************/
static void PushOperator(info_t *info)
{
	int push_flag = 0;
	
	/*Get operand precedence*/
	op_precendence_t precedence = OPPrecedenceOut(*info->input);
	
	char operand = *info->input;

	if (StackIsEmpty(info->op_stack))
	{
		StackPush(info->op_stack, &(*info->input));
		++info->input;
		info->state = WAIT_FOR_NUM;
	}
	else
	{	
		while (!StackIsEmpty(info->op_stack) && (0 == push_flag))
		{
			if (OPPrecedenceIn(*(char*)StackPeek(info->op_stack)) >= precedence)
			{
				Calculate(info);
			}
			else
			{
				StackPush(info->op_stack, &(*info->input));
				++info->input;
				info->state = WAIT_FOR_NUM;
				push_flag = 1;
			}
		}
	}
	
	if (operand == '^')
	{
		++pow_precedence_addition;
	}
}
/******************************************************************************/
static void PushOpenBrackets(info_t *info)
{
	StackPush(info->op_stack, &(*info->input));
	++info->input;
	info->state = WAIT_FOR_NUM;
}
/******************************************************************************/
static void SpaceInput(info_t *info)
{
	++info->input; 
}

static void InvalidInput(info_t *info)
{
	info->status = SYNTAX_ERR;
	info->state = RESOLVE; 
}

static void StringEnd(info_t *info)
{
	info->state = RESOLVE; 
	
}
/******************************************************************************/
static void Resolve(info_t *info)				
{
	if (info->status != SUCCESS)
	{
		return;
	}
		
	while (!StackIsEmpty(info->op_stack))
	{
		Calculate(info);
	}
	
	if (info->status != SUCCESS)
	{
		return;
	} 
	*info->result = *(double*)StackPeek(info->num_stack);
}
	
		
		 
/******************************************************************************/
static void	InitStateEventLUT(void (*state_table[2][256])(info_t*))
{	
	size_t i,j = 0;
	
	/*Initialize aentire LUT to point to InvalidInput*/
	for (i = 0; i < 2; ++i)
	{
		for (j = 0; j < 256; ++j)
		{
			state_table[i][j] = InvalidInput;
		}
	}
	
	
	for (i = 1; i <= 9; ++i)
	{
		state_table[WAIT_FOR_OP]['0' + i] = InvalidInput;
	}

	state_table[WAIT_FOR_NUM]['+'] = PushNum;
	state_table[WAIT_FOR_NUM]['-'] = PushNum;
	
	state_table[WAIT_FOR_NUM]['\0'] = StringEnd;
	state_table[WAIT_FOR_OP]['\0'] = StringEnd;
	
	state_table[WAIT_FOR_NUM][' '] = SpaceInput;
	state_table[WAIT_FOR_OP][' '] = SpaceInput;
	state_table[WAIT_FOR_NUM]['	'] = SpaceInput;
	state_table[WAIT_FOR_OP]['	'] = SpaceInput;
	
	for (i = 0; i <= 9; ++i)
	{
		state_table[WAIT_FOR_NUM]['0' + i] = PushNum;		
	}
	
	state_table[WAIT_FOR_OP]['+'] = PushOperator;
	state_table[WAIT_FOR_OP]['-'] = PushOperator;
	state_table[WAIT_FOR_OP]['/'] = PushOperator;	
	state_table[WAIT_FOR_OP]['*'] = PushOperator;
	state_table[WAIT_FOR_OP]['^'] = PushOperator;	

	state_table[WAIT_FOR_OP]['('] = PushOpenBrackets;
	state_table[WAIT_FOR_NUM]['('] = PushOpenBrackets;
	state_table[WAIT_FOR_OP][')'] = PushclosingBrackets;
}
/******************************************************************************/
calc_status_t StackCalc(const char *input, double *result)
{
	
	static void (*state_table[2][256])(info_t*) = {{NULL},{NULL}};
	info_t data_block = {NULL, NULL, NULL, NULL, WAIT_FOR_NUM, SUCCESS};

	assert(input);

	/*create stacks */	
	data_block.num_stack = StackCreate(1000, sizeof(double));
	if (!data_block.num_stack)
	{
		return INTERNAL_ERR;
	}		
	
	data_block.op_stack = StackCreate(1000, sizeof(char));
	if (!data_block.op_stack)
	{
		StackDestroy(data_block.num_stack);
		
		return INTERNAL_ERR;
	}

	data_block.input = input;
	data_block.result = result;
	
	InitStateEventLUT(state_table);
	
	while (RESOLVE != data_block.state)
	{
		state_table[data_block.state][(int)*(data_block.input)](&data_block);
	}
	
	Resolve(&data_block);
	
	StackDestroy(data_block.op_stack);
	StackDestroy(data_block.num_stack);
	
	return (data_block.status);
}	
	
/******************************************************************************/	
































































