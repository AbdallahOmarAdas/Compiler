/* scanner .h*/
#include "FileDescriptor.h"
#ifndef __SCANNER__H
#define __SCANNER__H
//Token types enumeration

typedef enum
{
	/* Literals */
	LX_IDENTIFIER, LX_INTEGER, LX_STRING, LX_FLOAT,
	/* Keywords */
	KW_PROGRAM,
	KW_VAR, KW_CONSTANT, KW_INTEGER, KW_BOOLEAN, KW_STRING, KW_FLOAT, KW_CHAR, KW_DOUBLE,
	KW_TRUE, KW_FALSE, KW_IF, KW_FI, KW_THEN, KW_ELSE,
	KW_WHILE, KW_DO, KW_OD,
	KW_AND, KW_OR,
	KW_READ, KW_WRITE,
	KW_FOR, KW_FROM, KW_TO, KW_BY,
	KW_FUNCTION, KW_PROCEDURE, KW_RETURN, KW_NOT, KW_BEGIN, KW_END,
	/* Operators */
	LX_LPAREN, LX_RPAREN, LX_LBRACKET, LX_RBRACKET,
	LX_COLON, LX_DOT, LX_SEMICOLON, LX_COMMA, LX_COLON_EQ,
	LX_PLUS, LX_MINUS, LX_STAR, LX_SLASH,
	LX_EQ, LX_NEQ, LX_LT, LX_LE, LX_GT, LX_GE, LX_EOF,
	LX_BAR, LX_AND, LX_EXCLAMATIONMARK, LX_LCURLYBRACKET, LX_RCURLYBRACKET, LX_IFEQ
}
LEXEME_TYPE;

// Definition of TOKEN, you can use a clase if you  want 
struct	TOKEN
{
	LEXEME_TYPE type;
	int value;  // can be used instead of the str_ptr for IDs and strings
	float float_value;
	 char str[256];
	 char *str_ptr; // points to strings or Identifiers, can use value
	              //instead but with type casting
};

class Scanner{
   //private:
		 ///*Fd
		// define your functions ..
		//I would define the following functions..
		// void skip_comments();
		// bool check_keyword(...)
		// TOKEN *get_id(..)
		// TOKEN *get_string(..)
		// TOKEN *get_int(..) // gets integers and floats

	public:
		FileDescriptor *Fd;
		int check_keyword(const char * word);
		void skip_comments();
		Scanner();
		~Scanner();
		int find_lx_op(char c);
		int find_lx_op2(const char* word);
		Scanner(FileDescriptor* fd);// { Fd = fd; /* write other code if needed*/};
		TOKEN* Scan(); 
		// You may define it as TOKEN *Scan(FileDescriptor *fd);

};
const char* type_name(LEXEME_TYPE lx);



#endif




