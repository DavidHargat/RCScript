typedef enum {T_NUMBER,T_PLUS,T_MINUS,T_MULTIPLY,T_DIVIDE,T_OPEN_P,T_CLOSE_P} TokenType;

struct Token{
	TokenType type;
	int value;
};

/*
* TYPES OF TOKENS
* 	SYMBOLS
*		OPERATOR
* 	NUMERICAL
*/

// Return a Token* with given parameters.
struct Token create_token( TokenType type, int value ){
	struct Token *t = malloc( sizeof( struct Token ) );
	t->type = type;
	t->value = value;
	return *t;
}

// Convert enum TokenType to a string.
char *TokenType_to_string( TokenType t ){
	if( t>=0 && t<=6 ){
		char *table[] = {"#","+","-","*","/","(",")"};
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

int count_tokens( char *str ){
	int l = strlen( str );
	
	int num_of_tokens = 0;
	
	int i,last;
	
	for( i=0; i<l; i++){
		char c = str[i];
		
		if ( char_is_symbol( c ) ){
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