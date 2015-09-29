typedef enum {NUMBER,OPERATOR} TokenType;

struct Token{
	TokenType type;
	int value;
};

struct Token *createToken( TokenType type, int value ){
	struct Token *t = malloc( sizeof( struct Token ) );
	t->type = type;
	t->value = value;
	return t;
}

void print_token( struct Token *t ){
	printf("Token( type=%d, value=%d )",t->type,t->value);
}