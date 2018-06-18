

// 스택을 구현하는 방법만 다르고 나머지는 로직은 배열으로 스택을 구현했을때와 같음 
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
	
	printf ( "\n식을 입력하세요.\n" ) ;
	scanf ( "\n%s", exp ) ;
	infix_to_postfix ( exp, postfix, &pstack ) ;
	printf ( "\nconver to postfix = %s", postfix ) ;
	result = calc ( postfix, &pstack ) ;
	printf ( "\nanswer is %d\n", result ) ;
	
	system ( "PAUSE" ) ; 
	return 1;
}



void init_stack_top ( Stack *top_of_stack  ) {
	top_of_stack -> top = NULL ;												// 스택의 맨위 주소를 NULL로 초기화 한다 
}



int is_stack_empty ( Stack *top_of_stack ) {
	if ( top_of_stack -> top == NULL ) return 1 ;								// 스택의 head 주소가 NULL 이면 스택이 비어있는 상태이므로 1을 반환한다. 
	else return 0 ; 
}



void push ( Stack *top_of_stack, int data_a ) {									 
	Node *new_node = ( Node * ) malloc ( sizeof ( Node ) ) ;					// data를 저장하기 위한 새로운 노드를 생성한다  
	
	new_node -> data = data_a ;													// 새로운 노드에 데이터를 저장한다. 
	new_node -> next = top_of_stack -> top;									 	// 새로운 노드에 다음 링크를 현재 스택의 최상단 노드의 주소로 지정한다. 
	
	top_of_stack -> top = new_node ;											// 스택의 최상단 노드의 주소를 새로운 노드로 지정한다. ( 새로운 노드는 최상단 노드가 됨 ) 
}



int pop ( Stack *top_of_stack ) {
	Node *curr ;																// Node 형 포인터 변수 curr 선언 
	int result ;												
	
	if ( is_stack_empty ( top_of_stack ) ) {									// 스택이 비었는지 검사 
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;
	}	
	
	curr = top_of_stack -> top ;												// curr의 주소를 스택 최상단 노드의 주소로 설정 
	result = curr -> data ;														// 스택 최상단 노드의 데이터 값을 result에 저장 
	
	top_of_stack -> top = curr -> next ;										// 스택 최상단 노드의 주소를 최상단 다음 노드로 지정 

	free ( curr ) ;																// 최상단 노드에 할당된 메모리를 해제한다. 
	
	return result ;
	
}


int current_top_data ( Stack *top_of_stack ) {

	if ( is_stack_empty ( top_of_stack ) ) {
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;	
	}
	
	return top_of_stack -> top -> data ;										// 최상단 노드의 데이터 값을 반환한다 
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