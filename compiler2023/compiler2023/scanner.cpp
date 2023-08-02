#include "scanner.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <conio.h>
#pragma warning(disable : 4996)

using namespace std;


std::string numberr;
const int keys = 30; /* number of keywords */
const char* keyword[] = {
"and", "begin", "boolean", "by", "constant",
"do", "else", "end", "false", "fi", "float", "for", "from",
"function", "if", "integer", "not", "od", "or", "procedure",
"program", "read", "return", "string", "then", "to", "true",
"var", "while", "write"
};
LEXEME_TYPE key_type[] = {
KW_AND, KW_BEGIN, KW_BOOLEAN, KW_BY, KW_CONSTANT,
KW_DO, KW_ELSE, KW_END, KW_FALSE, KW_FI, KW_FLOAT,
KW_FOR, KW_FROM, KW_FUNCTION, KW_IF, KW_INTEGER, KW_NOT,
KW_OD, KW_OR, KW_PROCEDURE, KW_PROGRAM, KW_READ, KW_RETURN,
KW_STRING, KW_THEN, KW_TO, KW_TRUE, KW_VAR, KW_WHILE, KW_WRITE
};

int Scanner::check_keyword(const char* word)
{
	for (int i = 0; i < keys;i++) {
		if (strcmp(word,keyword[i])==0) {
			return i;
		}	
}
	return -1;
}
void Scanner::skip_comments()
{
	cout << "comment detected"<<endl;//just skip the current line
	Fd->getCurrLine();
}
Scanner::Scanner()
{
    char fileName[] = "Text.txt";
    Fd = new FileDescriptor(fileName);
}
Scanner::~Scanner()
{
    Fd->close();
    Fd->~FileDescriptor();
}

bool isOperator(char ch)						//check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&' || ch == ':' || ch == ')' || ch == '(' ||
        ch == '!' || ch == '.' || ch == ';' || ch == '[' || ch == ']' || ch == ',' || ch == '{' || ch == '}')
    {
        return true;
    }
    return false;
}
char op[20] = {'+','-','*','/' ,'>' ,'<' ,'=', '|' ,'&',':',')','(','!','.',';','[',']',',','{','}' };    
LEXEME_TYPE op_type[] = {
    LX_PLUS, LX_MINUS, LX_STAR, LX_SLASH, LX_GT, LX_LT,
    LX_EQ,LX_BAR,LX_AND,LX_COLON, LX_RPAREN, LX_LPAREN,
    LX_EXCLAMATIONMARK, LX_DOT, LX_SEMICOLON,LX_LBRACKET, LX_RBRACKET,LX_COMMA,LX_LCURLYBRACKET,LX_RCURLYBRACKET

};
//(s == "<=" || s == ">=" || s == "!=" || s == ":=" || s == "==")
const char* op2[]={ "<=" ,">=" , "!=" ,":=" ,"=="};
int op2_key = 5;
LEXEME_TYPE op2_type[] = {
    LX_LE,LX_GE,LX_NEQ,LX_COLON_EQ,LX_IFEQ
};
int Scanner::find_lx_op2(const char* word)
{
    for (int i = 0; i < op2_key; i++) {
        if (strcmp(word, op2[i]) == 0) {
            return i;
        }
    }
    return -1;
}
int Scanner::find_lx_op(char c) {
    for (int i = 0; i < 20; i++) {
        if (c == op[i]) {
            return i;
        }
    }
    return -1;
}
//int x[7]={5,6,7,8}
bool isOperator2(char ch)						//check if the given character is an operator or not
{
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' ||
        ch == '=' || ch == '|' || ch == '&' || ch == ':' || ch == ')' || ch == '(' ||
        ch == ';' || ch == '[' || ch == ']' || ch == ',' || ch == '{' || ch == '}')
    {
        return true;
    }
    return false;
}

typedef enum {
    digit_class,litter_class,symbol_class,iligel_Class
}get_class;

int getClassType(char c) {
    if (c >= '0' && c <= '9')
        return digit_class;
    else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return litter_class;
    else if (isOperator(c) || (c == '"') || (c == '#'))
        return symbol_class;
    else
        return iligel_Class;
}

TOKEN* Scanner::Scan()
{

    //Scanner scan;
    TOKEN* token=new TOKEN;
    char temp;
    while (1) {
        temp = Fd->getChar();
        if (Fd->getCharNum() == -1000) {
            cout << "EOF " << endl;
            std::string ss="EOF";
            token->type = LX_EOF;
            strcpy(token->str, ss.c_str());
            break;
        }
        if ((temp == '\n') || (temp == '\r')) {
            continue;
            //temp = Fd->getChar();
        }
        else if (temp == ' ' || temp == '\t') {
            continue;
           // temp = Fd->getChar();
        }
        else if (getClassType(temp) == iligel_Class) {
            cout << int(temp)<< "fffffffffffffffffffffffffffff" << endl;
            if ((int(temp) != 8) && (int(temp) != 16)) {
                Fd->ungetChar();
                char msg[] = "illegal token detected ";
                Fd->reportError(msg, temp);
                Fd->getCurrLine();
                continue;
            }
        }
        else if (getClassType(temp) == symbol_class ) {
            
            if (temp == '#') {
                temp = Fd->getChar();
                if (temp == '#') {
                    while (1) {
                        temp = Fd->getChar();
                        if (temp == '#') {
                            temp = Fd->getChar();
                            if (temp == '#') {
                                //cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
                                break;
                            }
                            else {
                                Fd->ungetChar();
                                char msg[] = "expexted double ";
                                Fd->reportError(msg, '#');
                            }
                        }
                        cout << temp << endl;
                        if ((temp == '\r') || (temp == EOF)) {
                            //skip_comments();
                            //break;
                            continue;
                        }
                       // cout << "999999999999999999999999999999" << endl;
                    }
                    //skip_comments();
                }
                else {
                    Fd->ungetChar();
                    char msg[] = "expexted double ";
                    Fd->reportError(msg, '#');
                }
                continue;
            }
            else if (temp == '"') {
                bool flagFindString = false;
                std::string s;
                s += "";
                int i = 0;
                while (1) {
                    i++;
                    temp = Fd->getChar();
                    //cout << i << " char is '" << temp << "'"<<endl;
                    if (temp == '"') {
                        cout << "string detected " << s.c_str() << endl;
                        flagFindString = true;
                        break;
                    }
                    if (temp == '\r') {//new line in windows is \r\n
                        //while(temp)
                        Fd->reportError("un-terminated string ", ' ');
                        Fd->ungetChar();
                        //scan.Fd->getCurrLine();
                        break;
                    }
                    
                    s += temp;
                }
                if (flagFindString) {

                    token->type = LX_STRING;
                    strcpy(token->str, s.c_str());
                    break;
                }
            }
            //else if ((!isOperator(temp)))
            //{
            //    Fd->ungetChar();
            //    char msg[] = "illegal token detected ";
            //    Fd->reportError(msg, temp);
            //    Fd->getCurrLine();
            //    continue;
            //}
            else if (isOperator(temp) == true) {// negative and positive 
                char temp2 = Fd->getChar();
                bool flag = false;
                if ((temp == '-')) {// temp == '+' ||
                    if (getClassType(temp2) == digit_class) {
                        numberr += temp;
                        Fd->ungetChar();
                        continue;
                    }

                }
                if (isOperator(temp2) == true ) {
                    std::string s;
                    s += temp;
                    s += temp2;

                    if (s == "<=" || s == ">=" || s == "!=" || s == ":=" || s == "==") { // 4+-5
                        cout << "operand detected" << s.c_str() << endl;
                        int t = find_lx_op2(s.c_str());
                        token->type = op2_type[t];
                        strcpy(token->str, s.c_str());
                        break;
                    }

                    else {
                        cout << "(" << temp << ")" << " IS AN OPERATOR\n";
                        int t = find_lx_op(temp);
                        std::string ss;
                        ss += temp;
                        token->type = op_type[t];
                        strcpy(token->str, ss.c_str());
                        Fd->ungetChar();
                        break;
                    }

                }
                else  {
                    
                    cout << "(" << temp << ")" << " IS AN OPERATOR\n";
                    int t = find_lx_op(temp);
                    std::string ss;
                    ss += temp;
                    token->type = op_type[t];
                    strcpy(token->str, ss.c_str());
                    Fd->ungetChar();
                    break;
                }
            }

        }
        else if (getClassType(temp) == litter_class) {
            int count = 0;
            std::string s;
            bool flagIlligleIdent = false;
            while ((temp != ' ') && (temp != '\r') && (!isOperator2(temp))) {//
                s += temp;

                if ((getClassType(temp) != litter_class) && (getClassType(temp) != digit_class) && (temp != '_') && (temp != '\0') && (!isOperator2(temp))) {// &&(temp !='\n')
                    Fd->ungetChar();
                    flagIlligleIdent = true;
                    break;
                }
                temp = Fd->getChar();
                if (isOperator2(temp)) {
                    Fd->ungetChar();
                }

            }
            if (!flagIlligleIdent) {
                int t = check_keyword(s.c_str());
                if ( t== -1) {
                    cout << "detect identifier" << "  " << s.c_str() << endl;
                    token->type = LX_IDENTIFIER;
                    strcpy(token->str, s.c_str());
                    break;
                }
                else {
                    cout << "detect keyword" << "  " << s.c_str() << endl;
                    token->type = key_type[t];
                    strcpy(token->str, s.c_str());
                    break;
                }
            }
            else {
                char msg[] = "illegal identifier detect ";
                Fd->reportError(msg, temp);
                Fd->getCurrLine();
            }
        }


        else if (getClassType(temp) == digit_class) {
            std::string s;

            bool flagIlligleInt = false;
            while ((temp != ' ') && (temp != '\r') && (!isOperator2(temp))) {//&& (isArithmaticOperator(temp))
                s += temp;
                temp = Fd->getChar();
                if ((getClassType(temp) != digit_class) && (temp != ' ') && (temp != '\r') && (!isOperator2(temp))) {//&&(!isArithmaticOperator(temp))
                    flagIlligleInt = true;
                    Fd->ungetChar();
                    break;
                }
                if (isOperator2(temp)) {
                    Fd->ungetChar();
                }
            }
            if (flagIlligleInt) {
                char msg[] = "illegal integer detect ";
                Fd->reportError(msg, temp);
                Fd->getCurrLine();
            }
            else {
                int intValue = stoi(s.c_str());
                if ((numberr.length() != 0) && (numberr == "-")) {
                    intValue = -1 * intValue;
                    numberr = "";
                }
                cout << "detect integer " << intValue << endl;
                token->type = LX_INTEGER;
                token->value = intValue;
                break;
            }
        }

    }
    return token;
}

int main() {
    Scanner scan;
    TOKEN* tok;
    while (1) {
        tok=scan.Scan();
    cout << " token->type = " << tok->type << endl;
    if (tok->type == LX_INTEGER)cout << " token->value = " << tok->value << endl;
    else if (tok->type == LX_EOF) { 
        if (tok->str != NULL) {
            cout << " token->str = ";
            for (int i = 0; tok->str[i] != '\0'; i++) {
                cout << tok->str[i];
            }
            cout << endl;
        }
        exit(0);
    }
    else {
        if (tok->str != NULL) {
            cout << " token->str = ";
            for (int i = 0; tok->str[i] != '\0'; i++) {
                cout << tok->str[i];
            }
            cout << endl; 
        }
    }
    }
}