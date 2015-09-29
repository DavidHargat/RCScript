#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charlib.c"
#include "token.c"

/* 
* An operator is any char that represents a math operation.
* 	Ex. '+' of '1+1'*
*/

// Counts the total number of tokens in a string

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
int string_to_tokens( char *str ){
	
	// Count how many tokens we should find in the string.
	int num_of_tokens = count_tokens( str );
	
	// Array of tokens
	struct Token tokens [num_of_tokens];
	
	int tokenIndex = 0;
	
	int l = strlen( str );
	
	int i = 0, numberStart = 0, readingNumber = 0;;
	for( i=0; i<l+1; i++ ){
		char c = str[i];
		
		// If its numerical
		if ( char_is_numerical( c ) ){
			
			if( readingNumber == 0 ){
				readingNumber = 1;
				numberStart = i;				
			}
			
		}else{
			// If the LAST char was numerical
			if( readingNumber == 1 ){
				
				// We got ourselves a number token.
				
				struct Token t;
				t.type = T_NUMBER;
				t.value = substring_to_number(str,numberStart,i);
				
				tokens[ tokenIndex ] = t;
				
				tokenIndex++;
				readingNumber = 0;
			}
		}
		
		if ( char_is_symbol( c ) ){
			struct Token t; 
			
			t.value = 0;
			
			if( c == '+' ) t.type = T_PLUS;
			if( c == '-' ) t.type = T_MINUS;
			if( c == '*' ) t.type = T_MULTIPLY;
			if( c == '/' ) t.type = T_DIVIDE;
			if( c == '(' ) t.type = T_OPEN_P;
			if( c == ')' ) t.type = T_CLOSE_P;
			
			tokens[ tokenIndex ] = t;
			tokenIndex++;
		}
		
		
		if( !char_is_numerical( c ) && !char_is_operator( c) && (c != '\0') ){
			printf("Unknown Char: '%c' at %d \n",c,i);
		}	
	}
	
	for( i=0; i<num_of_tokens; i++){
		print_token(&tokens[i]);
	}
}


void eval( char *str ){
	int num_of_tokens = count_tokens( str );
	
	printf( "Input: %s \n", str );	
	printf( "Number Of Tokens: %d \n", num_of_tokens );
	
	string_to_tokens( str );
}

int main(int argc, char *argv[])
{
	char *test_input = "123+(3-32)*34";
	
	eval( test_input );

    return 0;
}