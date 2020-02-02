#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 16

#define STACK_DEBUG 0

#if STACK_DEBUG
#define DEBUG(fmt, ...) printf("%s: " fmt, __FUNCTION__, __VA_ARGS__)
#else
#define DEBUG(fmt, ...)	
#endif

#define ERROR(fmt, ...) printf("%s: " fmt, __FUNCTION__, __VA_ARGS__)

#define INFO(fmt) printf("%s: " fmt, __FUNCTION__)

typedef struct stack{
	int (*stack[STACK_MAX_SIZE]) (int);
	int func_arg[STACK_MAX_SIZE];
	int stack_top;
} *STACK;

int stack_init(STACK *stk);
int stack_push(STACK *stk, int (*func)(int), int arg);
int stack_pop(STACK *stk);
void print_stack(STACK *stk);
