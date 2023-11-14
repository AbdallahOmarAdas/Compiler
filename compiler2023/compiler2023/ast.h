#include "SymbolTableEntry.h"
#ifndef __AST__H
#define __AST__H
//ast.h
#include "FileDescriptor.h"
/* Definitions of list datatypes */
/* List of AST nodes */
typedef SymbolTableEntry  symbol_table_entry;
//typedef AST  ast_node;
struct ast_node;
typedef struct ast_list_cell 
{
	ast_node *head; // pointer to  a tree
	 ast_list_cell *tail;  // this is the next pointer that you use typically in the list
} ast_list;

/* List of symbol table entries */
typedef struct ste_list_cell
{
	 symbol_table_entry *head; // pointer to a symbol table entry
	 ste_list_cell *tail; //  this is the next pointer that you use typically in the list
} ste_list;

//class ste_list {
//public:
//	symbol_table_entry* head;
//	ste_list* tail;
//	ste_list() {
//		head = NULL;
//		tail = NULL;
//	}
//};

////////////////////////////////////////////////////////////
/* Type of an AST node. */
typedef enum
{
	AST_VAR_DECL,		 /* TOP-LEVEL VARIABLE DECLARATION */
	AST_CONST_DECL,		 /* II CONSTANT DECLARATION */
	AST_ROUTINE_DECL,	 /* II PROCEDURE OR FUNCTION DECL. */
	AST_ASSIGN,			 /* ASSIGNMENT STATEMENT */
	AST_IF,				 /* IF-THEN-ELSE STATEMENT */
	AST_WHILE,			 /* WHILE STATEMENT */
	AST_FOR,			 /* FOR STATEMENT */
	AST_READ,			 /* READ STATEMENT */
	AST_WRITE,			 /* WRITE STATEMENT */
	AST_CALL,			 /* PROCEDURE CALL */
	AST_BLOCK,			 /* BEGIN-END BLOCK */
	AST_RETURN,			 /* RETURN STATEMENT */
	AST_VAR,			 /* VARIABLE REFERENCE */
	AST_INTEGER,		 /* INTEGER LITERAL */
	AST_STRING,			 /* STRING LITERAL */
	AST_BOOLEAN,		 /* BOOLEAN LITERAL */
	AST_TIMES,			 /*  OPERATOR */
	AST_DIVIDE,			/* / OPERATOR */
	AST_PLUS,			 /* + OPERATOR */
	AST_MINUS,			 /* -OPERATOR */
	AST_EQ,				/* = OPERATOR */
	AST_NEQ,			/* != OPERATOR */

	AST_LT, /* < OPERATOR */
	AST_LE, /* <= OPERATOR */
	AST_GT, /* > OPERATOR */
	AST_GE, /* >= OPERATOR */
	AST_AND, /* AND OPERATOR */
	AST_OR, /* OR OPERATOR */
	AST_CAND, /* CAND OPERATOR */
	AST_COR, /* COR OPERATOR */
	AST_NOT, /* NOT OPERATOR */
	AST_UMINUS, /* UNARY -OPERATOR */
	AST_EOF, /* END OF FILE */
	AST_FLOAT, /* FLOAT */
	AST_ITOF, /* CONVERT INTEGR TO FLOAT */
	AST_HEAD,
}AST_type;

//typedef enum {
//	TYPE_NONE,
//	TYPE_INTEGER,
//	TYPE_CHARPOINTER,
//	TYPE_FLOAT,
//	TYPE_DOUBLE,
//	TYPE_CHAR
//}J_type;
///////////////////////////////////////////////////////////////////////
/* The actual datatype for an abstract syntax tree (AST) node. */
typedef struct ast_node
{
 AST_type      type; /* Type of the AST node */
 union /* The fields depend on a node's type */
	{
	 struct{
			symbol_table_entry *name; /* Variable's symbol table entry */
			J_type type; /* Declared type of variable */
	 } a_var_decl;
	
	 struct{
			symbol_table_entry *name; /* Constant's symbol table entry */
			int value; /* Evaluated value of constant */
	 } a_const_decl;
	
	 struct{
			symbol_table_entry *name; /* Routine's symbol table entry */
			ste_list *formals; /* List of formal parameters */
			J_type result_type; /* Type of result (none_type for procedures) */
			struct ast_node *body; /* Body of routine */
	} a_routine_decl;
	
	 struct{
		     symbol_table_entry *lhs; /* Target of assignment */
			 struct ast_node *rhs; /* Right side of assignment */
	} a_assign;
	
	 struct{
			struct ast_node *predicate; /* Predicate */
			struct ast_node *conseq; /* Consequent */
			struct ast_node *altern; /* Alternative (NULL for if-then stmt) */
	} a_if;
	
	struct{
			struct ast_node *predicate; /* Predicate */
			struct ast_node *body; /* Body */
	} a_while;
	
	struct {
			symbol_table_entry *var; /* Index variable */
			struct ast_node *lower_bound; /* Lower iteration bound */
			struct ast_node *upper_bound; /* Upper iteration bound */
			struct ast_node *body; /* Body */
	}a_for;
	
	struct{
			symbol_table_entry *var; /* Target variable */
	} a_read;

	struct{
				symbol_table_entry *var; /* Source variable */
	} a_write;

	struct{
			symbol_table_entry *callee; /* Symbol table entry for function */
			ast_list *arg_list; /* List of actual arguments */
	} a_call;

	struct {
		ast_list* nodes_list; /* List of actual nodes */
	} a_head;
  
	struct{
		   ste_list *vars; /* Symbol table entries of local variables */
		  ast_list *stmts; /* Statements in block */
	} a_block;

	struct{
		struct ast_node *expr; /* Return value */
	} a_return;

	struct{
		symbol_table_entry *var; /* Symbol table entry for variable */
	} a_var;

	struct{
		int value; /* Integer value */
	} a_integer;

	struct{
		float value;
	} a_float;

	struct{
		char *string; /* String value */
	} a_string;

	struct{
		int value; /* Boolean value */
	}a_boolean;

	struct {
		struct ast_node* arg; /* Argument */
		J_type type;
	} a_unary_op;

	struct{
		struct ast_node *larg; /* Argument 1 */
		struct ast_node *rarg; /* Argument 2 */
		AST_type type;
		//j_type rel_type;
	} a_binary_op;

	struct {
		struct ast_node *arg;
	} a_itof; 
  
 } f;  // union 
} AST; // ASt structure

 /* Externally-visible functions: */
 ast_list *cons_ast (AST *, ast_list *);
 ste_list *cons_ste (SymbolTableEntry *, ste_list *);
 char* steName(SymbolTableEntry* e);
 int steConstValue(SymbolTableEntry* e);
 J_type steVarType(SymbolTableEntry* e);
 int eval_ast_expr (FileDescriptor* , AST *);//„‘ „ÿ·Ê»
 AST *make_ast_node (AST_type type, ...);//similler to printf
 void print_ast_node (FILE *, AST *);
  void nl_indent(FILE*, int);
  void p_a_n(FILE*, AST*, int);
  void print_ast_list(FILE*, ast_list*, const char*, int);
  void print_ste_list(FILE*, ste_list*, const char*, const char*, int);
  const char* jTypeName(J_type j);
#endif




