#ifndef HEADERS_H
#define HEADERS_H

typedef enum {T_NUMBER,T_PLUS,T_MINUS,T_MULTIPLY,T_DIVIDE,T_OPEN_P,T_CLOSE_P} TokenType;

struct Token{
	TokenType type;
	int value;
};

// file.c
char *file_read_string(char *filename);

// charlib.c
int char_is_operator( char c );
int char_is_symbol( char c );
int char_is_numerical( char c );

// token.c
struct Token *create_token( TokenType type, int value );
char *TokenType_to_string( TokenType t );
void print_token( struct Token *t );
int count_tokens( char *str );

// main.c
int substring_to_number(char *str, int start, int end);
struct Token **string_to_tokens( char *str );
void print_tokens( struct Token **tokens, int length );
void resolve_operation( struct Token **tokens, int length, int index);
void eval( char *str );

#endif