#include "stack.h"

STACK main_stk;

int stack_init(STACK *stk)
{
	if (*stk)
		ERROR("Stack already init!%d \n", (-1));
	(*stk) = malloc(sizeof(struct stack));
	(*stk)->stack_top = -1;

	return (0);
}

int call_func_on_stack(STACK *stk)
{
	if (!(*stk))
		return (-1);

	int ret = 0;
	int stack_top;	

	for (stack_top = (*stk)->stack_top; stack_top >= 0; stack_top--){
		DEBUG("Call func %p with arg %d\n", (*stk)->stack[stack_top], (*stk)->func_arg[stack_top]);	
		int (*func) (int) = (*stk)->stack[stack_top];

		ret = func((*stk)->func_arg[stack_top]);
		
		if (ret != 0)
			ERROR("Func %p return error!\n", (*stk)->stack[stack_top]);
		stack_pop(stk);
	}
	
	return ret;
}

int stack_push(STACK *stk, int (*func)(int), int arg)
{
	if (!(*stk))
		return (-1);

	if (((*stk)->stack_top + 1) != STACK_MAX_SIZE){
		(*stk)->stack_top++;
	} else {
		ERROR("Stack is full! %d\n", (-2));
		return (-2);
	}

	(*stk)->stack[(*stk)->stack_top] = func;
	(*stk)->func_arg[(*stk)->stack_top] = arg;	

	DEBUG("Insert func %p on top %d with arg %d\n", (*stk)->stack[(*stk)->stack_top], (*stk)->stack_top, (*stk)->func_arg[(*stk)->stack_top]);

	return (0);
}


int stack_pop(STACK *stk)
{
	if (!(*stk))
		return (-1);
	if (((*stk)->stack_top < 0) || (!((*stk)->stack[(*stk)->stack_top])))
		return (-3);

	int stack_top = (*stk)->stack_top;

	DEBUG("Pop out stack top %d, func %p\n",
	stack_top, (*stk)->stack[(*stk)->stack_top]);

	(*stk)->stack[(*stk)->stack_top] = NULL;
	(*stk)->func_arg[(*stk)->stack_top] = 0;
	if (stack_top >= 0)
		(*stk)->stack_top--;

}

void print_stack(STACK *stk)
{
	if (!(*stk))
		return;

	int i;
	INFO("STACK: \n");
	for (i = (*stk)->stack_top; i >= 0; i--){
		printf("%d : %p\n", i, (*stk)->stack[i]);
	}
}

int func1(int x)
{
	printf("\tfunc %s on stack right now with x %d\n", __FUNCTION__, x);

	return 0;
}

int func2(int x)
{
	printf("\tfunc %s on stack right now with x %d\n", __FUNCTION__, x);

	return 0;
}

int main()
{
	stack_init(&main_stk);

	stack_push(&main_stk, func1, 1 << 7);
	stack_push(&main_stk, func2, 1 << 20);

	print_stack(&main_stk);

	int ret = 0;
	ret = call_func_on_stack(&main_stk);

	free(main_stk);

	return (0);
}
