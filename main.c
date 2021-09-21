#include "stack.h"
#include "stack.c"

int main(){
	stack* st = stack_init();
	printf("----- S043 STACK OPERATIONS -----\n");
	int choice = 0;
	do {
		printf("\t1 : Push Element\n");
		printf("\t2 : Pop Element\n");
		printf("\t3 : Peek Element\n");
		printf("\t4 : Print Stack\n");
		printf("\n\t0 : Exit\n");
		printf("\n Select : ");
		scanf(" %i", &choice);

		if (choice == 1){
			int obj = 0;
			printf("Enter integer to push onto stack : ");
			scanf(" %i", &obj);
			stack_push(st, obj);
			printf("Pushed %i onto the stack\nStack size : %I64u\n", obj, stack_size(st));
		} else if (choice == 2){
			int obj = stack_pop(st);
			printf("Popped integer : %i\nStack size : %I64u\n", obj, stack_size(st));
		} else if (choice == 3){
			int obj = stack_peep(st);
			printf("Peeped integer : %i\nStack size : %I64u\n", obj, stack_size(st));
		} else if (choice == 4){
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
		} else if (choice == 0){
			return 0;
		} else {
			printf("Invalid choice! \n");
		}
	} while (choice != 0);
	stack_del(st);
	return 0;
}