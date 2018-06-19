
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
void Push ( Stack *topOfStack, int value )
{									 
	Node *newNode = ( Node * ) malloc ( sizeof ( Node ) ) ;					
	
	newNode -> data = value ;													
	newNode -> next = topOfStack -> top;									 	
	
	topOfStack -> top = newNode ;											
}


// This function is used to pop data from the stack
// Returns the top stack value
// The parameter is the top node of the stack
int Pop ( Stack *topOfStack ) 
{
	Node *currNode ;																
	int result ;												
	
	if ( CheckStackEmpty ( topOfStack ) ) {									
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;
	}	
	
	currNode = topOfStack -> top ;												
	result = currNode -> data ;														 
	
	// Specify the address of the top node as the address of the next node
	topOfStack -> top = currNode -> next ;										 

	free ( currNode ) ;																
	
	return result ;	
}


// This function is used to determine what the value of the top node is
// Returns the value of the top node
// The parameter is the top node of the stack
int CurrentTopData ( Stack *topOfStack ) {

	if ( CheckStackEmpty ( topOfStack ) ) {
		printf ( "stack is empty" ) ;
		system ( "PAUSE" ) ;	
	}
	
	return topOfStack -> top -> data ;										
}


// This function is used to check whether the current value is an operator or not
// If the operator, returns 1
// Use the current value as a parameter
int WhetherOperator ( int value ) 
{
	return ( value == '+' || value == '-' || value == '*' || value == '/' ) ;
}


// This function is used to prioritize operators
// Returns the priority value by operator
// Use the current value as a parameter
int OperatorPriority ( int value ) 
{
	if ( value == '(' ) return 0 ;
	else if ( value == '+' || value == '-' ) return 1 ;
	else if ( value == '*' || value == '/' ) return 2 ;
	else return 3 ;
}



void infix_to_postfix ( char *src, char *dst, Stack *top_of_stack ) {
	InitTopAddr( top_of_stack ) ;
	
	while ( *src ) {
		if ( *src == '(' ) {
			Push ( top_of_stack, *src ) ;
			src++ ;
		} else if ( *src == ')' ) {
			while ( CurrentTopData ( top_of_stack ) != '(' ) {
				*dst++ = Pop ( top_of_stack ) ;
				*dst++ = ' ' ;
			}	
			Pop ( top_of_stack ) ;
			src++ ;
		} else if ( WhetherOperator ( *src ) ) {
			while ( !CheckStackEmpty ( top_of_stack ) && OperatorPriority ( CurrentTopData ( top_of_stack ) ) >= OperatorPriority ( *src ) ) {
				*dst++ = Pop ( top_of_stack ) ;
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
		*dst++ = Pop ( top_of_stack ) ;
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
			Push ( top_of_stack, Pop ( top_of_stack ) + Pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '*' ) {
			Push ( top_of_stack, Pop ( top_of_stack ) * Pop ( top_of_stack ) ) ;
			dst++ ;
		} else if ( *dst == '-' ) {
			a = Pop ( top_of_stack ) ;
			Push ( top_of_stack, Pop ( top_of_stack ) - a ) ;
			dst++ ;
		} else if ( *dst == '/' ) {
			a = Pop ( top_of_stack ) ;
			Push ( top_of_stack, Pop ( top_of_stack ) / a ) ;
			dst++ ;
		} else dst++;
	}
	return Pop ( top_of_stack ) ;	
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