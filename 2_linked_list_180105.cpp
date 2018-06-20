
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


// This function is used to convert the infix to postfix
// There is no return value
// Use the input expression as an infix parameter
// Use output parameters as postfix
// The parameter is the top node of the stack
void InfixToPostfix ( char *infix, char *postfix, Stack *topOfStack ) 
{
	InitTopAddr( topOfStack ) ;
	
	while ( *infix ) {
		
		if ( *infix == '(' ) {
			Push ( topOfStack, *infix ) ;
			infix++ ;
		} 
		
		else if ( *infix == ')' ) {
			// Repeat until you meet '(', which you have accumulated on the stack
			while ( CurrentTopData ( topOfStack ) != '(' ) {
				*postfix++ = Pop ( topOfStack ) ;
				*postfix++ = ' ' ;
			}
			// Discard '('
			Pop ( topOfStack ) ;
			infix++ ;
		} 
		
		else if ( WhetherOperator ( *infix ) ) {
			// Until the operator in the infix is ??less than the operator in the stack
			while ( !CheckStackEmpty ( topOfStack ) 
					&& ( OperatorPriority ( CurrentTopData ( topOfStack ) ) >= OperatorPriority ( *infix ) ) ) {
						
				*postfix++ = Pop ( topOfStack ) ;
				*postfix++ = ' ' ;
			}
			Push ( topOfStack, *infix ) ;
			*infix++ ;
		} 
		
		else if ( *infix >= '0' && *infix <= '9' ) {
			do {
				*postfix++ = *infix++ ;	
			} while ( *infix >= '0' && *infix <= '9' );
			*postfix++ = ' ';
		} else infix ++ ;	
	}
	
	// Pop any remaining values ??on the stack
	while ( !CheckStackEmpty ( topOfStack ) ) {
		*postfix++ = Pop ( topOfStack ) ;
		*postfix++ = ' ' ;
	}
	
	postfix--;
	// Tells the end of the postfix
	*postfix = 0;
}


// This function is used for postfix calculation
// Return calculation result
// Use the expression converted to postfix as a parameter
// The parameter is the top node of the stack
int Calc ( char *postfix, Stack *topOfStack )
{
	int tmp ;
	
	InitTopAddr( topOfStack ) ;
	
	while ( *postfix ) {
		if ( *postfix >= '0' && *postfix <= '9' ) {
			tmp = 0 ;
			do {
				// Converting a character type number to an int type number
				tmp = tmp * 10 + *postfix - '0' ;
				postfix++ ;	
			} while ( *postfix >= '0' && *postfix <= '9' ) ;
			Push ( topOfStack, tmp ) ;
		} 
		
		else if ( *postfix == '+' ) {
			Push ( topOfStack, Pop ( topOfStack ) + Pop ( topOfStack ) ) ;
			postfix++ ;
		} 
		
		else if ( *postfix == '*' ) {
			Push ( topOfStack, Pop ( topOfStack ) * Pop ( topOfStack ) ) ;
			postfix++ ;
		} 
		
		else if ( *postfix == '-' ) {
			tmp = Pop ( topOfStack ) ;
			Push ( topOfStack, Pop ( topOfStack ) - tmp ) ;
			postfix++ ;
		}

		else if ( *postfix == '/' ) {
			tmp = Pop ( topOfStack ) ;
			Push ( topOfStack, Pop ( topOfStack ) / tmp ) ;
			postfix++ ;
		} 
		
		else postfix++;
	}
	return Pop ( topOfStack ) ;	
}



int main ( void ) 
{
	int result; 
	Stack linkedListStack;
	char inputInfix[100] , outputPostfix[100] ;
	
	printf ( "\nPlease enter an infix expression\n" ) ;
	
	scanf ( "\n%s", inputInfix ) ;
	
	InfixToPostfix ( inputInfix, outputPostfix, &linkedListStack ) ;
	
	printf ( "\nconver to postfix = %s", outputPostfix ) ;
	
	result = Calc ( outputPostfix, &linkedListStack ) ;
	
	printf ( "\nanswer is %d\n", result ) ;
	
	system ( "PAUSE" ) ; 
	return 1;
}



#endif