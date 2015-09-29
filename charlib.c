// Returns true ( 1 ) if char is an 'operator', false ( 0 ) if it is not.
int char_is_operator( char c ){
	
	if ( c == '+' ) return 1;
	if ( c == '-' ) return 1;
	if ( c == '*' ) return 1;
	if ( c == '/' ) return 1;
	
	return 0;
}

int char_is_symbol( char c ){
	
	if( char_is_operator( c ) ){
		return 1;
	}
	
	if( c == '(' ) return 1;
	if( c == ')' ) return 1;

	return 0;
}

// Returns true if char is numerical ( 0-9 )
int char_is_numerical( char c ){
	
	if( c == '0' ) return 1;
	if( c == '1' ) return 1;
	if( c == '2' ) return 1;
	if( c == '3' ) return 1;
	if( c == '4' ) return 1;
	if( c == '5' ) return 1;
	if( c == '6' ) return 1;
	if( c == '7' ) return 1;
	if( c == '8' ) return 1;
	if( c == '9' ) return 1;
	
	return 0;
}