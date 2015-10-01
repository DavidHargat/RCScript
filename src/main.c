#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers.h"

/* 
* An operator is any char that represents a math operation.
* 	Ex. '+' of '1+1'*
*/

int substring_to_number(char *str, int start, int end){
	
	// Total number of digits in our output number.
	int num_of_digits = end-start;
	
	char sub[num_of_digits+1]; // The 'substring' 
	
	// substring, might wanna move this to it's own function
	memcpy( sub, &str[start], num_of_digits );
	sub[num_of_digits] = '\0';
	
	return strtol(sub, 0, 10);
}

// Converts a string of chars to an array of Tokens.
struct Token **string_to_tokens( char *str ){
	
	// Count how many tokens we should find in the string.
	int num_of_tokens = count_tokens( str );
	
	// pointer to an Array of tokens (not to be confused with an array of pointers)
	struct Token **tokens = malloc(sizeof(*tokens) * num_of_tokens);
	
	int tokenIndex = 0;
	
	int l = strlen( str );
	
	int i = 0, numberStart = 0, readingNumber = 0;;
	for( i=0; i<l+1; i++ ){
		char c = str[i];
		
		// If its numerical
		if ( char_is_numerical( c ) ){
			
			// Enter a state of 'reading a number'
			if( readingNumber == 0 ){
				readingNumber = 1;
				numberStart = i; // Save where this number begins 
				// ex. "123+23" [4] is the beginning of the number '23'
			}
			
		}else{
			// If we're in 'reading number mode', and we hit a char that is not numeric
			if( readingNumber == 1 ){
				// We got ourselves a number token.
				
				int value = substring_to_number(str,numberStart,i);
				
				struct Token *t = create_token( T_NUMBER, value );
				
				tokens[ tokenIndex ] = t;
				
				tokenIndex++;
				readingNumber = 0;
			}
			
			// 
			if ( char_is_symbol( c ) ){
				struct Token *t; 
				t = malloc( sizeof(struct Token) );
				t->value = 0;
				
				if( c == '+' ) t->type = T_PLUS;
				if( c == '-' ) t->type = T_MINUS;
				if( c == '*' ) t->type = T_MULTIPLY;
				if( c == '/' ) t->type = T_DIVIDE;
				if( c == '(' ) t->type = T_OPEN_P;
				if( c == ')' ) t->type = T_CLOSE_P;
				
				tokens[ tokenIndex ] = t;
				tokenIndex++;
			}
		}		
		
		if( !char_is_numerical( c ) && !char_is_operator( c) && (c != '\0') ){
			printf("Unknown Char: '%c' at %d \n",c,i);
		}	
	}
	
	return tokens;
}

void print_tokens( struct Token **tokens, int length ){
	int i;
	for( i=0; i<length; i++){
		print_token( tokens[i] );
	}
}

/* resolve_operation parameters: 
* 	*tokens: is the array of tokens we're mutating, 
*	length: is of *tokens 
*	index: of the operation we wish to resolve.
*
* Rather than returning a new 'token array' we modify the given array.
*/


void resolve_operation( struct Token **tokens, int length, int index){
	
	// Create pointers to the token at [index] as well as it's "neighbours" (i+1 and i-1)
	struct Token *t_op, *t_a, *t_b;
	t_op = tokens[index];
	t_a  = tokens[index-1];
	t_b  = tokens[index+1];
	
	// Extract the values from the numerical tokens.
	int a,b;
	a = t_a->value;
	b = t_b->value;

	// Extract the type from the operator.
	TokenType t = t_op->type;

	// Calculate the result.
	int result = 0;
	if (t == T_PLUS )
		result = a + b;
	if (t == T_MINUS )
		result = a - b;
	if (t == T_MULTIPLY )
		result = a * b;
	if (t == T_DIVIDE )
		result = a / b;

	/* 
	* STITCHING ( this part is kinda hard to follow, here's a visualization. )	
	* Lets say you want to stitch [3]
	* [0,1,2,3,4,5,6,7,8,9] // our beginning array
	* [0,1, , , ,5,6,7,8,9] // we're resolving (2,3,4) ex. (1,+,1)
	* [0,1, ,5,6,7,8,9]     // we move everything from (3+2) back two spaces.
	* [0,1,r,5,6,7,8,9]     // 'result' new resides where '2' was.
	*/
	
	// Move everything from index+2 back 2 spaces
	int start = index+2;
	int i;
	for( i=start; i<length; i++ ){
		tokens[i-2] = tokens[i];
	}
	
	// 'Shave' off the last two tokens as we have reduced the total size of the array.
	// Rather than 'removing' we assign them to null tokens.
	struct Token *T_NULL = create_token(-1,0);
	tokens[length-1] = T_NULL;
	tokens[length-2] = T_NULL;
	
	// Create a new 'result' token.
	struct Token *r = create_token(T_NUMBER,result);
	// Insert the 'result' token.
	tokens[index-1] = r;
	
	
}


void eval( char *str ){
	
	// Count number of tokens, print it.
	int num_of_tokens = count_tokens( str );
	printf( "Number Of Tokens: %d \n", num_of_tokens );
	
	// Convert the string to a token array.
	struct Token **tokens = string_to_tokens( str );
	
	// Print those tokens
	print_tokens( tokens, num_of_tokens );
	resolve_operation( tokens, num_of_tokens, 1 );
	printf("Resolved\n");
	print_tokens( tokens, num_of_tokens );
	
}

int main(int argc, char *argv[]){
	// Read file, print, run it through the interpreter.
	char *str = file_read_string( "test.rcs" );
	printf("File Input:\n'%s'\n",str);
	eval( str );
    return 0;
}