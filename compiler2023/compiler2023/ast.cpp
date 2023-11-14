#include "ast.h"
//ast.c
/* Create and return a new abstract syntax tree (ASTT) node. The first
argument is the type of the node (one of AST_type). The rest of the
arguments are the fields of that type of node, in order. */


#include <stdio.h>
#include <varargs.h>
#include < stdarg.h >
//#include "compiler.h"
//#include "types.h"
#include "SymbolTable.h"
#include "ast.h"
/* Internal routines: */




///////////////////////////////////////////////////////////////////////
// page 2
const char* jword[7] = {
		"None", //0
	"Integer",
	"String",
	"Float",
	"Double",
	"Char",
	"Boolean"

};
const char* jTypeName(J_type j) {
	return jword[j];
}
AST* make_ast_node(AST_type va_alist,...)// va_dcl 
{
	AST *n = (AST *) malloc (sizeof (AST)); // change to new
	//AST* n = new AST();
	va_list ap;
	AST_type type;

	if (n == NULL) printf("malloc failed in make_ast_node\n");//fatal_error ("malloc failed in make_ast_node\n");
	
	va_start (ap, va_alist);
	//type = va_arg (ap, AST_type);
	type = va_alist;
	n->type = type;
	cout << "n->type: " << type << endl;
	switch (type) {
		case AST_VAR_DECL:
			n->f.a_var_decl.name = va_arg (ap, symbol_table_entry *);
			n->f.a_var_decl.type = va_arg (ap, J_type);
			break;

		case AST_CONST_DECL:
			n->f.a_const_decl.name = va_arg (ap,symbol_table_entry *);
			n->f.a_const_decl.value = va_arg (ap, int); 
			break;

		case AST_ROUTINE_DECL:
			n->f.a_routine_decl.name = va_arg (ap, symbol_table_entry *);
			n->f.a_routine_decl.formals = va_arg (ap, ste_list *);
			n->f.a_routine_decl.result_type = va_arg (ap, J_type );
			n->f.a_routine_decl.body = va_arg (ap, AST *);
			break;

		case AST_ASSIGN:		
			n->f.a_assign.lhs = va_arg (ap, symbol_table_entry *);	
			n->f.a_assign.rhs = va_arg (ap, AST *);
			break;

		case AST_IF:
			n->f.a_if.predicate = va_arg (ap, AST *);
			n->f.a_if.conseq = va_arg (ap, AST *);
			n->f.a_if.altern = va_arg (ap, AST *);
			break;

		case AST_WHILE:
			n->f.a_while.predicate = va_arg (ap, AST *);
			n->f.a_while.body = va_arg (ap, AST *);
			break;

		case AST_FOR:
			n->f.a_for.var = va_arg (ap, symbol_table_entry *);
			n->f.a_for.lower_bound = va_arg(ap, AST *);
			n->f.a_for.upper_bound = va_arg (ap, AST *);
			n->f.a_for.body = va_arg (ap, AST *);
			break;

		case AST_READ: //page 3
			n->f.a_read.var = va_arg (ap, symbol_table_entry *);
			break;

		case AST_WRITE:
			n->f.a_write.var = va_arg (ap, symbol_table_entry *);
			break;

		case AST_CALL:
			n->f.a_call.callee = va_arg (ap, symbol_table_entry*);
			n->f.a_call.arg_list = va_arg (ap, ast_list *);
			break;

		case AST_HEAD:
			n->f.a_head.nodes_list = va_arg(ap, ast_list*);
			break;

		case AST_BLOCK:
			n->f.a_block.vars = va_arg (ap, ste_list *);
			n->f.a_block.stmts = va_arg (ap, ast_list *);
		break;

		case AST_RETURN:
			n->f.a_return.expr = va_arg (ap, AST *);
			break;

		case AST_VAR:
			n->f.a_var.var = va_arg (ap, symbol_table_entry *);
			break;

		case AST_INTEGER:
			n->f.a_integer.value = va_arg (ap, int);
			break;

		case AST_FLOAT:
			n->f.a_float.value = va_arg (ap, float);
			break;
		case AST_STRING:
			n->f.a_string.string = va_arg (ap, char *);
			break;
		case AST_BOOLEAN:
			n->f.a_boolean.value = va_arg (ap, int);
			break;

		case AST_TIMES:
		case AST_DIVIDE:
		case AST_PLUS:
		case AST_MINUS:
		case AST_EQ:
		case AST_NEQ:
		case AST_LT:
		case AST_LE:
		case AST_GT:
		case AST_GE:
		case AST_AND:
		case AST_OR:
		case AST_CAND:
		case AST_COR:
			n->f.a_binary_op.larg = va_arg (ap, AST *);
			n->f.a_binary_op.rarg = va_arg (ap, AST *);
			break;

		case AST_NOT:
		case AST_UMINUS:
			n->f.a_unary_op.arg = va_arg (ap, AST *);
			break;
    // new page page 4
		case AST_ITOF:
			n->f.a_itof.arg = va_arg (ap, AST *);
			break;
		case AST_EOF:
			break;
		default:
			printf("Unknown type of AST node in make_ast_node\n");
			//fatal_error ("Unknown type of AST node in make_ast_node'n");
	}
	va_end(ap);
	return (n);
	
}
//////////////////////////////////////////////////////////////////////
/* Evaluate a constant expression represented as an AST. Return an
integer value. Errors are reported as errors in the user's program. */
int eval_ast_expr (FileDescriptor *fd, AST *n)
{
	if (n == NULL)
		printf("NULL AST in eval_ast_expr\n");
		//fatal_error ("NULL AST in eval_ast_expr'n");
	switch (n->type)
	{
	case AST_VAR:
		if (n->f.a_var.var->steType == STE_CONST)
			//return 9999999;
			return steConstValue(n->f.a_var.var);
		else
				printf("Cannot use variables in constant expressions\n");
				fd->reportError(" Cannot use variables in constant expressions",'a');
				return (0);
		case AST_INTEGER:
			return (n->f.a_integer.value);
		case AST_STRING:
			printf("Cannot use strings in constant expressions\n");
			fd->reportError( "Cannot use strings in constant expressions",'a');
			return (0);
		case AST_BOOLEAN:
			return (n->f.a_boolean.value);
		case AST_TIMES:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
					* eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_DIVIDE:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
					/ eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_PLUS:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				+ eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_MINUS:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				-eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_EQ:
			return (eval_ast_expr(fd, n->f.a_binary_op.larg)
				== eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_NEQ:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				!=eval_ast_expr (fd, n->f.a_binary_op.rarg)); // page 5
		case AST_LT:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				< eval_ast_expr (fd, n->f.a_binary_op.rarg));
	  case AST_LE:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				<= eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_GT:
		  return (eval_ast_expr(fd, n->f.a_binary_op.larg)
				> eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_GE:
		return (eval_ast_expr (fd, n->f.a_binary_op.larg)
			>= eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_AND:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				& eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_OR:
			return (eval_ast_expr(fd, n->f.a_binary_op.larg)
				| eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_CAND:
			return (eval_ast_expr(fd, n->f.a_binary_op.larg)
				& eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_COR:
			return (eval_ast_expr (fd, n->f.a_binary_op.larg)
				| eval_ast_expr (fd, n->f.a_binary_op.rarg));
		case AST_NOT:
			return (~ eval_ast_expr(fd, n->f.a_unary_op.arg));
		case AST_UMINUS:
			return (- eval_ast_expr (fd, n->f.a_unary_op.arg));
		default:
			printf("Unknown AST node in eval ast expr \n");
			//fatal error ("Unknown AST node in eval ast expr \n");
			return (0); 
		}
}

/////////////////////////////////////////////////////////////////////
/* Print (to the file F) the AST N. This routine doesn't try very hard
to format the output. */
void print_ast_node (FILE *f, AST *n)
{
	  p_a_n (f, n, 0);
}
///////////////////////////////////////////////////////////////////////
 void p_a_n (FILE *f, AST *n, int d)
{
if (n == NULL) return;
switch (n->type)
{
	cout << "n->type: " << n->type << endl;
// new page 6
	case AST_VAR_DECL:
//		printf ("var %s: %s;", (n->f.a_var_decl.name), jTypeName(n->f.a_var_decl.type));
		fprintf(f, "var %s: %s;", (n->f.a_var_decl.name), jTypeName((n->f.a_var_decl.type)));
		// nl_indent (f, d);
		break;
	case AST_CONST_DECL:
		fprintf (f, "constant %s = %d;", steName(n->f.a_const_decl.name),
					n->f.a_const_decl.value);
		nl_indent (f, d); 
		break;
	case AST_ROUTINE_DECL:
		{ 
			if (n->f.a_routine_decl.result_type == STE_NONE)
				fprintf (f, "procedure %s (", steName (n->f.a_routine_decl.name));
			else 
				fprintf (f, "function %s (", steName(n->f.a_routine_decl.name));
			print_ste_list (f, n->f.a_routine_decl.formals, "", ", ", -1);
			if (n->f.a_routine_decl.result_type == STE_NONE){
				fprintf (f, ")");
				nl_indent (f, d + 2);
			} else{
					//fprintf (f, ") : %s", type_name(n->f.a_routine_decl.result_type));
					fprintf(f, ") : %s", jTypeName(n->f.a_routine_decl.result_type));
					nl_indent (f, d + 2);
			} 
			p_a_n (f, n->f.a_routine_decl.body, d + 2);
			fprintf (f, ";");
			nl_indent(f, d);
		    break;
		}
	case AST_ASSIGN:
		fprintf (f, "%s := ", steName(n->f.a_assign.lhs));
		p_a_n (f, n->f.a_assign.rhs, d);
		break;
	case AST_IF:
		fprintf (f, "if ");
		p_a_n (f, n->f.a_if.predicate, d);
		fprintf (f, " then");
		nl_indent (f, d + 2);
		p_a_n (f, n->f.a_if.conseq, d + 2);
		if (n->f.a_if.altern != NULL){ 
			nl_indent (f, d);
			fprintf (f, "else");
			nl_indent (f, d + 2);
			p_a_n (f, n->f.a_if.altern, d + 2);
		}
	    break;
	case AST_WHILE:
		fprintf (f, "while ");
		p_a_n (f, n->f.a_while.predicate, d);
		fprintf (f, " do");
		nl_indent (f, d + 2);
		p_a_n (f, n->f.a_while.body, d + 2);
		nl_indent (f, d);
		fprintf (f, "od");// new page
		break;
	case AST_FOR:
		fprintf (f, "for %s = ", steName(n->f.a_for.var));
		p_a_n (f, n->f.a_for.lower_bound, d); 
		fprintf (f, " to "); 
        p_a_n (f, n->f.a_for.upper_bound, d);
		fprintf (f, " do");
		nl_indent (f, d + 2);
		p_a_n (f, n->f.a_for.body, d + 2);
		nl_indent (f, d);
		fprintf (f, "od");
		break;
	case AST_READ:
		fprintf (f, "read (%s)", steName(n->f.a_read.var));
		break; 
	case AST_WRITE:
		fprintf (f, "write (%s)", steName(n->f.a_read.var));
		break; 
	case AST_CALL:
		printf("hhhhhhhhhhhhhhhhhhhhhhhhhhh\n");
		fprintf(f, "%s (", steName(n->f.a_call.callee));
		print_ast_list (f, n->f.a_call.arg_list, ", ", -1);
		fprintf (f, ")");
		break;
	case AST_HEAD:
		print_ast_list(f, n->f.a_head.nodes_list, " ", 0);
		break;
	case AST_BLOCK:
		fprintf (f, "begin");
		nl_indent (f, d + 2);
		print_ste_list (f, n->f.a_block.vars, "var ", "", d + 2);
		print_ast_list (f, n->f.a_block.stmts, ";", d + 2);
		nl_indent (f, d);
		fprintf (f, "end");
	    break;
	case AST_RETURN:
		fprintf(f, "return (");
		p_a_n (f, n->f.a_return.expr, d);
		fprintf (f, ")");
		break;
	case AST_VAR:
		fprintf (f, "%s", steName(n->f.a_var.var));
		break; 
	case AST_INTEGER:
		fprintf (f, "%d", n->f.a_integer.value);
		break; 
	case AST_FLOAT:
		fprintf (f, "%f", n->f.a_float.value);
		break; 
	case AST_STRING:
		fprintf (f, "\n%s\n", n->f.a_string.string);
		break;
	case AST_BOOLEAN:
		fprintf (f, n->f.a_boolean.value ? "true" : "false");
		break;
	case AST_TIMES:
	case AST_DIVIDE: // new page
	case AST_PLUS:
	case AST_MINUS:
	case AST_EQ:
	case AST_NEQ:
	case AST_LT:
	case AST_LE:
	case AST_GT:
	case AST_GE:
	case AST_AND:
	case AST_OR:
	case AST_CAND:
	case AST_COR:
	  fprintf (f, "(");
	  p_a_n (f, n->f.a_binary_op.larg, d);
	  switch (n->type) {
		case AST_TIMES:
				fprintf (f, " * ");
				break;
		case AST_DIVIDE:
			fprintf (f, " / ");
			break;
		case AST_PLUS:
			fprintf (f, " + ");
			break;
		case AST_MINUS:
			fprintf (f, " -");
			break;
		case AST_EQ:
			fprintf (f, " = ");
			break;
		case AST_NEQ:
			fprintf (f, " != ");
			break;
		case AST_LT:
			fprintf (f, " < ");
			break;
		case AST_LE:
			fprintf (f, " <= ");
			break;
		case AST_GT:
			fprintf (f, " > ");
			break;
		 case AST_GE:
			fprintf (f, " >= ");
			break;
		case AST_AND:
			fprintf (f, " and ");
			break;
		case AST_OR:
			fprintf (f, " or ");
			break; // new page
		case AST_CAND:
			fprintf (f, " cand ");
			break;
		case AST_COR:
			fprintf (f, " cor ");
			break;
		default:
		break;
       }
	   p_a_n (f, n->f.a_binary_op.rarg, d);
	   fprintf (f, ")");
	   break;
	case AST_NOT:
		fprintf (f, "(not ");
		p_a_n (f, n->f.a_unary_op.arg, d);
		fprintf (f, ")");
		break;
	case AST_UMINUS:
		fprintf (f, "( -");
		p_a_n (f, n->f.a_unary_op.arg, d);
		fprintf (f, ")");
		break;
	case AST_EOF:
		fprintf (f, "EOF");
		break;
	default:
		printf("Unknown AST node type\n");
		//fatal error ("Unknown AST node type\n");
  } 
}
///////////////////////////////////////////////////
/* Print a list of AST nodes. */
 void print_ast_list (FILE *f, ast_list *L, const char *sep, int d)
{
	for ( ; L != NULL; L = L->tail){
		p_a_n (f, L->head, d);
		if (L->tail || d>0){
			fprintf (f, sep);
			if (L->tail && d >= 0) nl_indent (f, d);
		}
	}
}
////////////////////////////////////////////////////////////////
/* Print a list of symbol table entries along with their types. */
 void print_ste_list (FILE *f, ste_list *L, const char *prefix,const char *sep, int d)
{ 
	for ( ; L != NULL; L = L->tail) {
			//fprintf (f, "%s%s : %s", prefix, steName(L->head),typeName(ste_var_type (L->head)));
			fprintf(f, "%s%s : %s", prefix, steName(L->head), jTypeName(steVarType(L->head)));
			if (L->tail || d >= 0) fprintf (f, sep); // new page 10
			if (d >= 0) nl_indent (f, d);
   }
}
///////////////////////////////////////////////////
/* Print a newline and indent D space. */
 void nl_indent (FILE *f, int d)
{
	fprintf (f, "\n");
	while (d > 0) {
		fprintf(f, " ");
		d--;
	}
}

char* steName(SymbolTableEntry* e)
{	
	cout << "########################### name: ";
	if (e->Name == NULL) {
		cout << "########################### name nulll: ";
		return e->Name;
	}
	for (int i = 0; e->Name[i] != '\0'; i++) {
		cout << e->Name[i];
	}
	cout << endl;
	return e->Name;
}

int steConstValue(SymbolTableEntry* e)
{
	return e->constVal;
	
}

J_type steVarType(SymbolTableEntry* e)
{
	cout << "##########################: " << e->Type<<endl;
	return e->Type;
}
