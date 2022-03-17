/*
    @AUTHOR : Arnav Deo
    @LINK   : https://www.github.com/arnitdo
    @TITLE  : Stack Implementation in C
*/    

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef struct {
	int* base_ptr;
	size_t stack_size;
} stack;

// Fwd declaration

stack*  stack_init();
void	stack_push(stack*, int);
int		stack_pop(stack*);
size_t	stack_size(stack*);
int		stack_peep();
void 	stack_del(stack*);

// Implementation of prototypes

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
		return INT_MIN;
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

// Menu-driven options in main()

int main(){
	stack* st = stack_init();
	printf("----- STACK OPERATIONS -----\n");
	int choice = 0;
	do {
		printf("\t1 : Push Element\n");
		printf("\t2 : Pop Element\n");
		printf("\t3 : Peep Element\n");
		printf("\t4 : Print Stack\n");
		printf("\n\t0 : Exit\n");
		printf("\nSelect : ");
		scanf(" %i", &choice);

		if (choice == 1){
			int obj = 0;
			printf("Enter integer to push onto stack : ");
			scanf(" %i", &obj);
			stack_push(st, obj);
			printf("Pushed %i onto the stack\nStack size : %I64u\n", obj, stack_size(st));
		} else if (choice == 2){
			if (stack_size(st)){
				int obj = stack_pop(st);
				printf("Popped integer : %i\nStack size : %I64u\n", obj, stack_size(st));
			} else {
				printf("Stack is empty, nothing to pop!\n");
			}	
		} else if (choice == 3){
            if (stack_size(st)){
			    int obj = stack_peep(st);
			    printf("Peeped integer : %i\nStack size : %I64u\n", obj, stack_size(st));
            } else {
                printf("Stack is empty, nothing to peep!\n");
            }    
		} else if (choice == 4){
			if (stack_size(st)){
				stack* temp_st = stack_init();
				printf("----- BEGIN STACK PRINT -----\n");
				while (stack_size(st) != 0){
					int obj = stack_pop(st);
					printf("%i\n", obj);
					stack_push(temp_st, obj);
				}
				printf("----- END STACK PRINT -----\n");
				while (stack_size(temp_st) != 0){
					int obj = stack_pop(temp_st);
					stack_push(st, obj);
				}
				stack_del(temp_st);
			} else {
				printf("Stack is empty, nothing to print!\n");
			}	
		} else if (choice == 0){
			return 0;
		} else {
			printf("Invalid choice! \n");
		}
	} while (choice != 0);
	stack_del(st);
	return 0;
}
