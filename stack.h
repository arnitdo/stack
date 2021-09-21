#ifndef S043_STACK_IMPL
#define S043_STACK_IMPL

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int* base_ptr;
	size_t stack_size;
} stack;

stack*  stack_init();
void	stack_push(stack*, int);
int		stack_pop(stack*);
size_t	stack_size(stack*);
int		stack_peep();
void 	stack_del(stack*);

#endif