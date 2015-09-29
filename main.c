#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.c"
#include "charlib.c"

/* 
* An operator is any char that represents a math operation.
* 	Ex. '+' of '1+1'*
*/

// Counts the total number of tokens in a string
int count_tokens( char *str ){
	int l = strlen( str );
	
	int num_of_tokens = 0;
	
	int i,last;
	
	for( i=0; i<l; i++){
		char c = str[i];
		
		if ( char_is_operator( c ) ){
			num_of_tokens++;
		}else{
			
			if ( char_is_numerical( c ) ){
				if( !char_is_numerical( last ) ){
					num_of_tokens++;
				}
			}else{
				// Invalid token or whitespace
			}
			
		}
		
		last = c;
	}
	
	return num_of_tokens;
}

int string_to_tokens( char *str ){
	int num_of_tokens = count_tokens( str );
	
	struct Token *tokens = malloc( sizeof(struct Token) * num_of_tokens );
	
	for( i=0; i<l; i++ ){
		char c = str[i];
		
		if( char_is_operator( c ) ){
			
		}
		
	}
}


void eval( char *str ){
	int num_of_tokens = count_tokens( str );
	
	printf( "Input: %s \n", str );	
	printf( "Number Of Tokens: %d \n", num_of_tokens );
}

int main(int argc, char *argv[])
{
	char *test_input = "123+3-32*34";
	
	eval( test_input );
	
	struct Token *t = createToken(NUMBER,0);
	print_token( t );
	
    return 0;
}