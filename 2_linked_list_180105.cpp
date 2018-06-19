
#if 1
#include <stdio.h>
#include <stdlib.h>


// The structure to store the data and the next address
typedef struct _node {
	int data;
	struct _node *next ;	
} Node ;


// The structure that stores the top address of the stack
typedef struct _stack {
	Node *top ;	
} Stack ;


// This function is used to initialize the top address of the stack
// There is no return value
// The parameter is the top node of the stack
void InitTopAddr ( Stack *topOfStack  ) 
{
	topOfStack -> top = NULL ;												
}


// This function is used to check if the current stack is empty
// If the stack is empty, it returns a value of 1
// The parameter is the top node of the stack
int CheckStackEmpty ( Stack *topOfStack  ) 
{
	if ( topOfStack -> top == NULL ) 
		return 1 ;								
	else 
		return 0 ; 
}


// This function is used to push data into the stack
// There is no return value
// The parameter is the top node of the stack
// The parameter ( value ) is used as the data to be stored in the stack.
void Push ( Stack *topOfStack, int value ) {									 
	Node *newNode = ( Node * ) malloc ( sizeof ( Node ) ) ;					
	
	newNode -> data = value ;													
	newNode -> next = topOfStack -> top;									 	
	
	topOfStack -> top = newNode ;											
}



int pop ( Stack *top_of_stack ) {
	Node *curr ;																// Node 형 포인터 변수 curr 선언 
	int result ;												
	
	if ( CheckStackEmpty ( top_of_stack ) ) {									// 스택이 비었는지 검사 
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

	if ( CheckStackEmpty ( top_of_stack ) ) {
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
	InitTopAddr( top_of_stack ) ;
	
	while ( *src ) {
		if ( *src == '(' ) {
			Push ( top_of_stack, *src ) ;
			src++ ;
		} else if ( *src == ')' ) {
			while ( current_top_data ( top_of_stack ) != '(' ) {
				*dst++ = pop ( top_of_stack ) ;
				*dst++ = ' ' ;
			}	
			pop ( top_of_stack ) ;
			src++ ;
		} else if ( is_operator ( *src ) ) {
			while ( !CheckStackEmpty ( top_of_stack ) && prec_operator ( current_top_data ( top_of_stack ) ) >= prec_operator ( *src ) ) {
				*dst++ = pop ( top_of_stack ) ;
				*dst++ = ' ' ;
			}
			Push ( top_of_stack, *src ) ;
			*src++ ;
		} else if ( *src >= '0' && *src <= '9' ) {
			do {
				*dst++ = *src++ ;	
			} while ( *src >= '0' && *src <= '9' );
			*dst++ = ' ';
		} else src ++ ;	
	}
	
	while ( !CheckStackEmpty ( top_of_stack ) ) {
		*dst++ = pop ( top_of_stack ) ;
		*dst++ = ' ' ;
	}
	dst--;
	*dst = 0;
}




int calc ( char *dst, Stack *top_of_stack ) {
	int a ;
	
	InitTopAddr( top_of_stack ) ;
	
	while ( *dst ) {
		if ( *dst >= '0' && *dst <= '9' ) {
			a = 0 ;
			do {
				a = a * 10 + *dst - '0' ;
				dst++ ;	
			} while ( *dst >= '0' && *dst <= '9' ) ;
			Push ( top_of_stack, a ) ;
		} else if ( *dst == '+' ) {
			Push ( top_of_stack, pop ( top_of_stack ) + pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '*' ) {
			Push ( top_of_stack, pop ( top_of_stack ) * pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '-' ) {
			a = pop ( top_of_stack ) ;
			Push ( top_of_stack, pop ( top_of_stack ) - a ) ;
			dst++ ;
		} else if ( *dst == '/' ) {
			a = pop ( top_of_stack ) ;
			Push ( top_of_stack, pop ( top_of_stack ) / a ) ;
			dst++ ;
		} else dst++;
	}
	return pop ( top_of_stack ) ;	
}



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



#endif