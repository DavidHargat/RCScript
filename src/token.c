#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "headers.h"

/*
* TYPES OF TOKENS
* 	SYMBOLS
*		OPERATOR
* 	NUMERICAL
*/

// Return a struct Token* with given parameters.
struct Token *create_token( TokenType type, int value ){
	struct Token *t = malloc( sizeof( struct Token ) );
	t->type = type;
	t->value = value;
	return t;
}

// Convert enum TokenType to a string.
char *TokenType_to_string( TokenType t ){
	char *table[] = {"#","+","-","*","/","(",")"};
	int l = sizeof( *table ) / sizeof( char );
	if( t >= 0 && t <= l ){
		return table[t];		
	}else{
		return "None";
	}
}

// Print a token to console.
void print_token( struct Token *t ){
	if( t->type == T_NUMBER ){
		printf("T ( %d ) \n",t->value);
	}else{
		printf("T ( %s ) \n",TokenType_to_string(t->type));
	}
}

// Counts the total number of tokens in a string
int count_tokens( char *str ){
	int num_of_tokens = 0, l = strlen( str ), i;
	
	for( i=0; i<l; i++){
		char c = str[i];	
		if ( char_is_symbol( c ) ){
			num_of_tokens++;
		}else if( char_is_numerical(c) && !char_is_numerical(str[i-1]) ) {
			num_of_tokens++;
		}
	}
	
	return num_of_tokens;
}