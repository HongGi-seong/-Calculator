

// ������ �����ϴ� ����� �ٸ��� �������� ������ �迭���� ������ ������������ ���� 
#if 0
#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int data;
	struct _node *next ;	
} Node ;

typedef struct _stack {
	Node *top ;	
} Stack ;

void init_stack_top ( Stack *top_of_stack ) ;
int is_stack_empty ( Stack *top_of_stack  ) ;
void push ( Stack *top_of_stack, int data_a ) ;
int pop ( Stack *top_of_stack ) ;
int current_top_data ( Stack *top_of_stack ) ;
int is_operator ( int a ) ;
int prec_operator ( int a ) ;
void infix_to_postfix ( char *src, char *dst, Stack *top_of_stack ) ;
int calc ( char *dst, Stack *top_of_stack ) ;


int main ( void ) {
	int a, result; 
	Stack pstack;
	char exp[100] , postfix[100] ;
	
	printf ( "\n���� �Է��ϼ���.\n" ) ;
	scanf ( "\n%s", exp ) ;
	infix_to_postfix ( exp, postfix, &pstack ) ;
	printf ( "\nconver to postfix = %s", postfix ) ;
	result = calc ( postfix, &pstack ) ;
	printf ( "\nanswer is %d\n", result ) ;
	
	system ( "PAUSE" ) ; 
	return 1;
}



void init_stack_top ( Stack *top_of_stack  ) {
	top_of_stack -> top = NULL ;												// ������ ���� �ּҸ� NULL�� �ʱ�ȭ �Ѵ� 
}



int is_stack_empty ( Stack *top_of_stack ) {
	if ( top_of_stack -> top == NULL ) return 1 ;								// ������ head �ּҰ� NULL �̸� ������ ����ִ� �����̹Ƿ� 1�� ��ȯ�Ѵ�. 
	else return 0 ; 
}



void push ( Stack *top_of_stack, int data_a ) {									 
	Node *new_node = ( Node * ) malloc ( sizeof ( Node ) ) ;					// data�� �����ϱ� ���� ���ο� ��带 �����Ѵ�  
	
	new_node -> data = data_a ;													// ���ο� ��忡 �����͸� �����Ѵ�. 
	new_node -> next = top_of_stack -> top;									 	// ���ο� ��忡 ���� ��ũ�� ���� ������ �ֻ�� ����� �ּҷ� �����Ѵ�. 
	
	top_of_stack -> top = new_node ;											// ������ �ֻ�� ����� �ּҸ� ���ο� ���� �����Ѵ�. ( ���ο� ���� �ֻ�� ��尡 �� ) 
}



int pop ( Stack *top_of_stack ) {
	Node *curr ;																// Node �� ������ ���� curr ���� 
	int result ;												
	
	if ( is_stack_empty ( top_of_stack ) ) {									// ������ ������� �˻� 
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;
	}	
	
	curr = top_of_stack -> top ;												// curr�� �ּҸ� ���� �ֻ�� ����� �ּҷ� ���� 
	result = curr -> data ;														// ���� �ֻ�� ����� ������ ���� result�� ���� 
	
	top_of_stack -> top = curr -> next ;										// ���� �ֻ�� ����� �ּҸ� �ֻ�� ���� ���� ���� 

	free ( curr ) ;																// �ֻ�� ��忡 �Ҵ�� �޸𸮸� �����Ѵ�. 
	
	return result ;
	
}


int current_top_data ( Stack *top_of_stack ) {

	if ( is_stack_empty ( top_of_stack ) ) {
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;	
	}
	
	return top_of_stack -> top -> data ;										// �ֻ�� ����� ������ ���� ��ȯ�Ѵ� 
}



int is_operator ( int a ) {
	return ( a == '+' || a == '-' || a == '*' || a == '/' ) ;
}



int prec_operator ( int a ) {
	if ( a == '(' ) return 0 ;
	else if ( a == '+' || a == '-' ) return 1 ;
	else if ( a == '*' || a == '/' ) return 2 ;
	else return 3 ;
}



void infix_to_postfix ( char *src, char *dst, Stack *top_of_stack ) {
	init_stack_top ( top_of_stack ) ;
	
	while ( *src ) {
		if ( *src == '(' ) {
			push ( top_of_stack, *src ) ;
			src++ ;
		} else if ( *src == ')' ) {
			while ( current_top_data ( top_of_stack ) != '(' ) {
				*dst++ = pop ( top_of_stack ) ;
				*dst++ = ' ' ;
			}	
			pop ( top_of_stack ) ;
			src++ ;
		} else if ( is_operator ( *src ) ) {
			while ( !is_stack_empty ( top_of_stack ) && prec_operator ( current_top_data ( top_of_stack ) ) >= prec_operator ( *src ) ) {
				*dst++ = pop ( top_of_stack ) ;
				*dst++ = ' ' ;
			}
			push ( top_of_stack, *src ) ;
			*src++ ;
		} else if ( *src >= '0' && *src <= '9' ) {
			do {
				*dst++ = *src++ ;	
			} while ( *src >= '0' && *src <= '9' );
			*dst++ = ' ';
		} else src ++ ;	
	}
	
	while ( !is_stack_empty ( top_of_stack ) ) {
		*dst++ = pop ( top_of_stack ) ;
		*dst++ = ' ' ;
	}
	dst--;
	*dst = 0;
}




int calc ( char *dst, Stack *top_of_stack ) {
	int a ;
	
	init_stack_top ( top_of_stack ) ;
	
	while ( *dst ) {
		if ( *dst >= '0' && *dst <= '9' ) {
			a = 0 ;
			do {
				a = a * 10 + *dst - '0' ;
				dst++ ;	
			} while ( *dst >= '0' && *dst <= '9' ) ;
			push ( top_of_stack, a ) ;
		} else if ( *dst == '+' ) {
			push ( top_of_stack, pop ( top_of_stack ) + pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '*' ) {
			push ( top_of_stack, pop ( top_of_stack ) * pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '-' ) {
			a = pop ( top_of_stack ) ;
			push ( top_of_stack, pop ( top_of_stack ) - a ) ;
			dst++ ;
		} else if ( *dst == '/' ) {
			a = pop ( top_of_stack ) ;
			push ( top_of_stack, pop ( top_of_stack ) / a ) ;
			dst++ ;
		} else dst++;
	}
	return pop ( top_of_stack ) ;	
}

#endif