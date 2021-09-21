#include "stack.h"
#include <string.h>

stack* stack_init(){
	stack* s = (stack*) malloc(sizeof(stack));
	s->base_ptr = NULL;
	s->stack_size = 0;
	return s;
}

void stack_push(stack* stack_ptr, int obj){
	stack_ptr->stack_size++;
	size_t stack_mem_size = stack_ptr->stack_size * sizeof(int);
	int* old_ptr = stack_ptr->base_ptr;
	stack_ptr->base_ptr = (int*) malloc(stack_mem_size);
	if (stack_ptr->base_ptr == NULL){
		fprintf(stderr, "ERROR ALLOCATING %I64u BYTES FOR STACK AT ADDRESS %p\n", stack_mem_size, (void*) stack_ptr->base_ptr);
		exit(1);
	}
	memcpy(stack_ptr->base_ptr, old_ptr, stack_mem_size - sizeof(int));
	free(old_ptr);
	*(stack_ptr->base_ptr + (stack_ptr->stack_size - 1)) = obj;
}

int stack_pop(stack* stack_ptr){
	if (stack_ptr->stack_size == 0){
		fprintf(stderr, "STACK UNDERFLOW AT %p", (void*) stack_ptr->base_ptr);
		exit(1);
	} else if (stack_ptr->stack_size == 1){
		int obj = *(stack_ptr->base_ptr);
		stack_ptr->stack_size--;
		stack_ptr->base_ptr = NULL;
		return obj;
	} else {
		int obj = *(stack_ptr->base_ptr + stack_ptr->stack_size - 1);
		stack_ptr->stack_size--;
		return obj;
	}
	return INT_MIN;
}

size_t stack_size(stack* stack_ptr){
	return stack_ptr->stack_size;
}

int stack_peep(stack* stack_ptr){
	if (stack_ptr->stack_size != 0){
		int obj = *(stack_ptr->base_ptr + (stack_ptr->stack_size - 1));
		return obj;
	}
	return INT_MIN;
}

void stack_del(stack* stack_ptr){
	free(stack_ptr->base_ptr);
	stack_ptr->base_ptr = NULL;
	stack_ptr->stack_size = 0;
	free(stack_ptr);
	stack_ptr = NULL;
}