typedef enum {NUMBER,OPERATOR} TokenType;

struct Token{
	TokenType type;
	int value;
};