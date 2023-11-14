#include "Parser.h"
#include "ast.h";
TOKEN* tok;

FileDescriptor *fd = new FileDescriptor();
Scanner scan(fd);
Parser pars(fd);
ast_list* astHeadList = new ast_list();
int coutnter = 0;
int cvar = 0;
int cargs = 0;
Parser::Parser(FileDescriptor* fd)
{
    this->fd = fd;

    tabl = new SymbolTable();;
}

//ast_list* parse_program();
//ast_list* parse_decl_list();
AST* parse_program();
ast_list* parse_decl_list();
AST* parse_decl();
J_type parse_type();
ste_list* parse_formal_list();
ste_list* parse_formal_list_tali();
ste_list* parse_formals();
ste_list* parse_fomals_prime();
AST* parse_block(char x);
ste_list* parse_var_decl_list(ste_list* steHeadList);
SymbolTableEntry* parse_var_decl();
ast_list* parse_stmt_list(ast_list*);
AST* parse_stmt();
AST* parse_Bexpr();
AST* parse_Bexpr_par(AST* C);
AST* parse_Cexpr();
AST* parse_Cexpr_par(AST* E);
AST* parse_Eexpr();
AST* parse_Eexpr_par(AST* F);
AST* parse_Fexpr();
AST* parse_Fexpr_par(AST* G);
AST* parse_Gexpr();
AST* parse_Hexpr();
AST* parse_id_expr_tail(SymbolTableEntry* e);
AST* parse_id_tail(SymbolTableEntry* e);
AST* parse_id_expr_tail(SymbolTableEntry* e);
AST* parse_arg_list(SymbolTableEntry* e);
AST* parse_arg_list_tail(SymbolTableEntry* e);
ast_list* parse_args(ast_list* headList);
ast_list* parse_args_tail(ast_list* headList);
AST* parse_if_tail();
AST* Parser::parse()
{
    AST* prog = new AST();
    cout << "parssing parse_program() " << endl;
    prog=parse_program();
    //cout << "match(LX_EOF)"<<endl;
    //match(LX_EOF);
    return prog;
}

AST* parse_program()
{
    FILE* f2 = fopen("out1.txt", "w");
    ast_list* astList = new ast_list();
    coutnter = 0;
    cout << "parssing parse_decl_list() " << endl;
    astList= parse_decl_list();
    print_ast_list(f2, astList, ", ", -1);
    return make_ast_node(AST_HEAD, astList);
    //return astList;
}
ast_list* parse_decl_list()
{
    ast_list* astList = new ast_list();
    if (tok->type == LX_EOF) {
        AST* varAST = new AST();
        cout << "match(LX_EOF)"<<endl;
        match(LX_EOF);
        varAST=make_ast_node(AST_EOF);
        if (coutnter == 0) {
            
            coutnter++;
            cout << "1111111111111111111111111111111111111111111111111" << endl;
            astHeadList->head = varAST;
            astHeadList->tail = NULL;
            return astHeadList;
        }
        else {
            coutnter++;
            astList->head = varAST;
            astList->tail = NULL;
            //astList->tail = parse_decl_list();


            //if (coutnter == 2)exit(0);
            return astList;
        }
    }
    else if ((tok->type == KW_VAR) || (tok->type == KW_CONSTANT) || (tok->type == KW_FUNCTION) || (tok->type == KW_PROCEDURE)) {
        AST* varAST=new AST();
        cout << "parssing parse_decl() " << endl;
        varAST=parse_decl();
        match(LX_SEMICOLON);
        if (coutnter == 0) {
            coutnter++;
            cout << "1111111111111111111111111111111111111111111111111" << endl;
            astHeadList->head = varAST;
            astHeadList->tail = NULL;
            astHeadList->tail = parse_decl_list();
            return astHeadList;
        }
        else {
            coutnter++;
            astList->head = varAST;
            astList->tail=parse_decl_list();
            

            //if (coutnter == 2)exit(0);
            return astList;
        }

        //return varAST;
    }
    else {
        /*if (coutnter == 0) {
            astHeadList->head = NULL;
            astHeadList->tail = NULL;
        }*/
        return NULL;
    }
        

    
}

AST* parse_decl()
{
   // FILE* f = fopen("out2.txt", "w");
    J_type t;
    ste_list* steList = new ste_list();
    char *str;
    SymbolTableEntry* e;
    //FILE* fout = fopen("out.txt", "w");
    AST* ast;
    FILE* f2 = fopen("out2.txt", "w");
    int constval=0;
    AST* astBlock = new AST();
    SymbolTable* stTemp = new SymbolTable();
    switch (tok->type)
    {
    case KW_VAR:
        cout << "match(KW_VAR)" << endl;
        match(KW_VAR);
        cout << "match(LX_IDENTIFIER)" << endl;
        str = tok->str;
        match(LX_IDENTIFIER);
        cout << "match(LX_COLON)" << endl;
        match(LX_COLON);
        cout << "parse_type()" << endl;
        t=parse_type();
        e= pars.tabl->PutSymbol(str, t,STE_VAR,0);
        if (e==NULL) {
            fd->reportError(str,'d');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: "<< e->constVal<<endl;
        cout << "var name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << endl;
        return make_ast_node(AST_VAR_DECL,e,t);
        break;
    case KW_CONSTANT:
        cout << "match(KW_CONSTANT)" << endl;
        match(KW_CONSTANT);
        cout << "match(LX_IDENTIFIER)" << endl;
        str = tok->str;
        match(LX_IDENTIFIER);
        cout << "match(LX_EQ)" << endl;
        match(LX_EQ);
    //cout << "match(LX_INTEGER)" << endl;
    //constval = tok->value;
    //match(LX_INTEGER);
        cout << "parse Bexpr()" << endl;
        constval = eval_ast_expr(fd,parse_Bexpr());
        e = pars.tabl->PutSymbol(str, STE_NONE, STE_CONST, constval);
        if (e == NULL) {
            fd->reportError(str, 'd');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "const name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << endl;
        return make_ast_node(AST_CONST_DECL, e, constval);
        break;
    case KW_FUNCTION:
        cout << "match(KW_FUNCTION)" << endl;
        match(KW_FUNCTION);
        cout << "match(LX_IDENTIFIER)" << endl;
        str = tok->str;
        match(LX_IDENTIFIER);
        pars.enterScope(stTemp);
        cout << "parse_formal_list()" << endl;
        steList=parse_formal_list();
        
        cout << "match(LX_COLON)" << endl;
        match(LX_COLON);
        t=parse_type();

        cout << "parse_block()" << endl;

        astBlock = parse_block('r');
        pars.exitScope(stTemp);
        e = pars.tabl->PutSymbol(str, t, STE_ROUTINE, 0);
        if (e == NULL) {
            fd->reportError(str, 'd');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "Function name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << endl;
        ast=make_ast_node(AST_ROUTINE_DECL, e, steList, t, astBlock);
        return ast;
        break;
    case KW_PROCEDURE:
        cout << "match(KW_PROCEDURE)" << endl;
        match(KW_PROCEDURE);
        cout << "match(LX_IDENTIFIER)" << endl;
        str = tok->str;
        match(LX_IDENTIFIER);
        e = pars.tabl->PutSymbol(str, STE_NONE, STE_ROUTINE, 0);
        if (e == NULL) {
            fd->reportError(str, 'd');
        }
        pars.enterScope(stTemp);
            cout << "parse_formal_list()" << endl;
            steList = parse_formal_list();
            print_ste_list(f2, steList, "", ", ", -1);
            fprintf(f2, "\n==============\n");
            pars.tabl->PrintAll(f2);
            fprintf(f2, "\n==============\n");
        cout << "parse_block()" << endl;

        astBlock = parse_block('r');
        pars.exitScope(stTemp);
        fprintf(f2, "\n==============\n");
        pars.tabl->PrintAll(f2);
        fprintf(f2, "\n==============\n");
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "Procedure name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << endl;
        //parse_block();

        fprintf(f2,"hwllp\n");
        print_ste_list(f2, steList, "", ", ", -1);
        ast = make_ast_node(AST_ROUTINE_DECL, e, steList, STE_NONE, astBlock);
        return ast;
        break;
    default:
        
        break;
    }
    return nullptr;
}
J_type parse_type() {
    cout << "-----------------tok->type form parse typr: " << tok->type << endl;
    switch (tok->type)
    {
    case KW_INTEGER:
        cout << " match(KW_INTEGER)" << endl;
        match(KW_INTEGER);
        return STE_INT;
        break;
    case KW_BOOLEAN:
        match(KW_BOOLEAN);
        return STE_BOOLEAN;
        break;
    case KW_STRING:
        match(KW_STRING);
        return STE_STRING;
        break;
    default:
        fd->reportError("expected valid data type: ",' ');
        return STE_NONE;
        break;
    }
}
ste_list* parse_formal_list() {
    cout << "match(LX_LPAREN)" << endl;
    match(LX_LPAREN);
    cout << "parse_formal_list_tali" << endl;
    ste_list* s = new ste_list();
    s=parse_formal_list_tali();
    
    return s;
}

ste_list* parse_formal_list_tali() {
    if (tok->type==LX_RPAREN) {
        cout << "match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return NULL;
    }
    else if(tok->type == LX_IDENTIFIER)
    {
        ste_list* s= new ste_list();
        cout << "parse_formals" << endl;
        s= parse_formals();
        cout << "match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return s;
    }
    else {
        fd->reportError(type_name(LX_IDENTIFIER), 'p');
    }
}
ste_list* parse_formals() {
    J_type t;
    char* str;
    SymbolTableEntry* e;
    ste_list* steList = new ste_list();
    
    str = tok->str;
    cout << "match(LX_IDENTIFIER)" << endl;
    match(LX_IDENTIFIER);
    cout << "match(LX_COLON)" << endl;
    match(LX_COLON);
    cout << "parse_type" << endl;
    t = parse_type();
    e = pars.tabl->PutSymbol(str, t, STE_VAR, 0);
    if (e == NULL) {
        fd->reportError(str, 'd');
    }
    steList->head = e;
    steList->tail = NULL;
    cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
    cout << "var name: ";
    for (int i = 0; e->Name[i] != '\0'; i++) {
        cout << e->Name[i];
    }
    cout << endl;
    cout << "parse_fomals_prime" << endl;
    steList->tail=parse_fomals_prime();
    return steList;
       
}
ste_list* parse_fomals_prime() {
    //steList->tail = NULL;
    ste_list* steList = new ste_list();
    if (tok->type == LX_COMMA) {
        J_type t;
        char* str;
        SymbolTableEntry* e;
        cout << "match(LX_COMMA)" << endl;
        match(LX_COMMA);
        str = tok->str;
        cout << "match(LX_IDENTIFIER)" << endl;
        match(LX_IDENTIFIER);
        cout << "match(LX_COLON)" << endl;
        match(LX_COLON);
        cout << "parse_type" << endl;
        t=parse_type();
        e = pars.tabl->PutSymbol(str, t, STE_VAR, 0); 
        if (e == NULL) {
            fd->reportError(str, 'd');
        }
        steList->head = e;
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "var name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << endl;
        cout << "parse_fomals_prime" << endl;
        steList->tail = parse_fomals_prime();
        return steList;
    }
    else {
        cout << "lamda case return" << endl;
        //head = NULL;
         steList->head = NULL;
         steList->tail = NULL;
         return NULL;
       // return NULL;
    }
}
AST* parse_block(char x) {
    AST* ast = new AST();
    cout << "match(KW_BEGIN)" << endl;
    match(KW_BEGIN);
    cvar = 0;
    ste_list* steHeadList = new ste_list();
    ast_list* astHeadList = new ast_list();
    SymbolTable* tmep = new SymbolTable();
    
    if (x != 'r')pars.enterScope(tmep);
    steHeadList = parse_var_decl_list(steHeadList);
    astHeadList =parse_stmt_list(astHeadList);
    cout << "match(KW_END)" << endl;
    match(KW_END);
    
    if (x != 'r')pars.exitScope(tmep);

    FILE* f2 = fopen("Text1.txt", "w");
    print_ste_list(f2, steHeadList, "", ", ", -1);
    ast = make_ast_node(AST_BLOCK, steHeadList, astHeadList);
    return ast;
}
ste_list* parse_var_decl_list(ste_list* steHeadList) {
    ste_list* steList = new ste_list();
    if (tok->type==KW_VAR) {
        cout << "parse_var_decl()";
        if (cvar==0) {
            cvar++;
            
            steHeadList->head= parse_var_decl();
            cout << "match(LX_SEMICOLON)" << endl;
            match(LX_SEMICOLON);
            steHeadList->tail = NULL;
            steHeadList->tail= parse_var_decl_list(steHeadList);
            return steHeadList;
        }
        else {
            
            cvar++;
            steList->head= parse_var_decl();
            cout << "match(LX_SEMICOLON)" << endl;
            match(LX_SEMICOLON);
            steList->tail = parse_var_decl_list(steHeadList);
            return steList;
        }
    }
    else {
        return NULL;
    }
    
}
SymbolTableEntry* parse_var_decl() {
    J_type t;
    char* str;
    SymbolTableEntry* e;

    cout << "match(KW_VAR)" << endl;
    match(KW_VAR);
    cout << "match(LX_IDENTIFIER)" << endl;
    str = tok->str;
    match(LX_IDENTIFIER);
    cout << "match(LX_COLON)" << endl;
    match(LX_COLON);
    cout << "parse_type()" << endl;
    t = parse_type();
    e = pars.tabl->PutSymbol(str, t, STE_VAR, 0);
    if (e == NULL) {
        fd->reportError(str, 'd');
    }
    cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
    cout << "var name: ";
    for (int i = 0; e->Name[i] != '\0'; i++) {
        cout << e->Name[i];
    }
    cout << endl;
    return e;
}
ast_list* parse_stmt_list(ast_list* headlist) {
    AST* as = new AST();
    ast_list* astlist = new ast_list();
    if ((tok->type==LX_IDENTIFIER)|| (tok->type == KW_IF) || (tok->type == KW_WHILE) || (tok->type == KW_FOR) || (tok->type == KW_READ) || (tok->type == KW_WRITE) || (tok->type == KW_RETURN) || (tok->type == KW_BEGIN)){
       as= parse_stmt();
       if (coutnter == 0) {
           coutnter++;
           cout << "1111111111111111111111111111111111111111111111111" << endl;
           headlist->head = as;
           headlist->tail = NULL;
           cout << "LX_SEMICOLON" << endl;
           match(LX_SEMICOLON);
           headlist->tail = parse_stmt_list(headlist);
           return headlist;
       }
       else {
           coutnter++;
           astlist->head = as;
           cout << "LX_SEMICOLON" << endl;
           match(LX_SEMICOLON);
           astlist->tail = parse_stmt_list(headlist);
           //if (coutnter == 2)exit(0);
           return astlist;
       }
    }
    else if((tok->type == KW_END)) {
        //lamda case
        return NULL;
    }
    else {
        //error
        fd->reportError("expected end keyword or valid statment that the grammer accept it",'a');
    }
}
AST* parse_stmt() {
    AST* ast = new AST();
    J_type t;
    char* str;
    SymbolTableEntry* e;
    if ((tok->type == LX_IDENTIFIER)) {
        cout << "match(LX_IDENTIFIER)" << endl;
        str = tok->str;
        match(LX_IDENTIFIER);
        e = pars.getSymbolFromTable(str);
        if (e == NULL) {
            fd->reportError(str, 'n');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "var name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << "parse_id_tail() called from stmt" << endl;
        return parse_id_tail(e);
        
    }
    else if (tok->type == KW_READ) {
        cout << "match(KW_READ)" << endl;
        match(KW_READ);
        cout << "match(LX_LPAREN)" << endl;
        match(LX_LPAREN);
        str = tok->str;
        cout << "match(LX_IDENTIFIER)" << endl;
        match(LX_IDENTIFIER);
        e = pars.getSymbolFromTable(str);
        if (e == NULL) {
            fd->reportError(str, 'n');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "var name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << "match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return make_ast_node(AST_READ,e);
    }
    else if (tok->type == KW_WRITE) {
        cout << "match(KW_WRITE)" << endl;
        match(KW_WRITE);
        cout << "match(LX_LPAREN)" << endl;
        match(LX_LPAREN);
        str = tok->str;
        cout << "match(LX_IDENTIFIER)" << endl;
        match(LX_IDENTIFIER);
        e = pars.getSymbolFromTable(str);
        if (e == NULL) {
            fd->reportError(str, 'n');
        }
        cout << "J_type: " << e->Type << " ste_type: " << e->steType << " const val: " << e->constVal << endl;
        cout << "var name: ";
        for (int i = 0; e->Name[i] != '\0'; i++) {
            cout << e->Name[i];
        }
        cout << "match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return make_ast_node(AST_WRITE, e);
    }
    else if (tok->type == KW_RETURN) {
        cout << "match(KW_RETURN)" << endl;
        match(KW_RETURN);
        cout << "match(LX_LPAREN)" << endl;
        match(LX_LPAREN);
        ast = parse_Bexpr();
        cout << "match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return make_ast_node(AST_RETURN, ast);
    }
    else if (tok->type == KW_BEGIN) {
        ast = parse_block('b');
        return ast;
    }
    else if (tok->type == KW_WHILE) {
        AST *exp, *stmt;
        cout << "match(KW_WHILE)" << endl;
        match(KW_WHILE);
        exp = parse_Bexpr();
        cout << "match(KW_DO)" << endl;
        match(KW_DO);
        stmt = parse_stmt();
        cout << "match(KW_OD)" << endl;
        match(KW_OD);
        return make_ast_node(AST_WHILE, exp,stmt);
    }
    else if (tok->type == KW_FOR) {
        AST* Lexp, *Rexp, * stmt;
        cout << "match(KW_FOR)" << endl;
        match(KW_FOR);
        str = tok->str;
        cout << "match(LX_IDENTIFIER)" << endl;
        match(LX_IDENTIFIER);
        e = pars.getSymbolFromTable(str);
        if (e == NULL) {
            fd->reportError(str, 'n');
        }
        cout << "match(LX_COLON_EQ)" << endl;
        match(LX_COLON_EQ);
        Lexp = parse_Bexpr();
        cout << "match(KW_to)" << endl;
        match(KW_TO);
        
        Rexp = parse_Bexpr();
        cout << "match(KW_Do)" << endl;
        match(KW_DO);
        stmt = parse_stmt();
        cout << "match(KW_OD)" << endl;
        match(KW_OD);
        return make_ast_node(AST_FOR, e,Lexp,Rexp, stmt);
    }
    else if (tok->type == KW_IF) {
        AST* exp, * stmt,*elseif;
        cout << "match(KW_IF)" << endl;
        match(KW_IF);
        exp = parse_Bexpr();
        cout << "match(KW_THEN)" << endl;
        match(KW_THEN);
        stmt = parse_stmt();
        elseif = parse_if_tail();
        return make_ast_node(AST_IF, exp, stmt, elseif);
    }
    else {
        fd->reportError("vaild statment", 'p');
    }
}
AST* parse_if_tail() {
    if (tok->type==KW_ELSE) {
        AST* alt;
        cout << "match(KW_ELSE)" << endl;
        match(KW_ELSE);
        alt = parse_stmt();
        cout << "match(KW_FI)" << endl;
        match(KW_FI);
        return alt;
    }
    else if (tok->type == KW_FI) {
        cout << "match(KW_FI)" << endl;
        match(KW_FI);
        return NULL;
    }
    else {
        fd->reportError("vaild fi or else keyword ", 'p');
    }
}
AST* parse_id_tail(SymbolTableEntry* e) {
    if (tok->type==LX_COLON_EQ) {
        if (e->steType == STE_ROUTINE)fd->reportError("connat assign value to a routine", 'a');
        if (e->steType == STE_CONST)fd->reportError("connat change or reassign value for a constant", 'a');
        cout << "LX_COLON_EQ" << endl;
        match(LX_COLON_EQ);
        cout << "parse_Bexpr()" << endl;
        return make_ast_node(AST_ASSIGN, e, parse_Bexpr());
    }
    else {
        if (e->steType == STE_VAR)fd->reportError("the variable connat have an argument list", 'a');
        if (e->steType == STE_CONST)fd->reportError("the constant connat have an argument list", 'a');
        return parse_arg_list(e);
    }
}
AST* parse_Bexpr() {
    cout << "BBBBBBBBBBBBBBB exprition" << endl;
    AST* Cexpr, * Bexpr_par;
    Cexpr = parse_Cexpr();
    Bexpr_par = parse_Bexpr_par(Cexpr);
    //AST* intVal= make_ast_node(AST_INTEGER ,eval_ast_expr(fd, Bexpr_par));
    //return intVal;
    return Bexpr_par;
}
AST* parse_Bexpr_par(AST* B) {
    AST* Cexpr, * Bexpr_par;
    cout << "we now in parse_Fexpr_par" << endl;
    if (tok->type == KW_AND) {
        cout << "match(KW_AND)" << endl;
        match(KW_AND);
        Cexpr = parse_Cexpr();
        Bexpr_par = make_ast_node(AST_AND, B, Cexpr);
        B = parse_Bexpr_par(Bexpr_par);
    }
    else if (tok->type == KW_OR) {
        cout << "match(KW_OR)" << endl;
        match(KW_OR);
        cout << "parse Eexpr" << endl;
        Cexpr = parse_Cexpr();
        Bexpr_par = make_ast_node(AST_OR, B, Cexpr);
        B = parse_Bexpr_par(Bexpr_par);
    }
    return B;
}
AST* parse_Cexpr() {
    cout << "parse_Gexpr() form parse_Fexpr" << endl;
    AST* Fexpr, * Cexpr_par;
    Fexpr = parse_Eexpr();
    Cexpr_par = parse_Cexpr_par(Fexpr);
    return Cexpr_par;
}
AST* parse_Cexpr_par(AST* C) {
    AST* Eexpr, * Cexpr_par;
    cout << "we now in parse_Fexpr_par" << endl;
    if (tok->type == LX_EQ) {
        cout << "match(LX_EQ)" << endl;
        match(LX_EQ);
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_EQ, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    else if (tok->type == LX_NEQ) {
        cout << "match(LX_NEQ)" << endl;
        match(LX_NEQ);
        cout << "parse Eexpr" << endl;
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_NEQ, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    else if (tok->type == LX_GT) {
        cout << "match(LX_GT)" << endl;
        match(LX_GT);
        cout << "parse Eexpr" << endl;
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_GT, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    else if (tok->type == LX_GE) {
        cout << "match(LX_GE)" << endl;
        match(LX_GE);
        cout << "parse Eexpr" << endl;
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_GE, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    else if (tok->type == LX_LT) {
        cout << "match(LX_LT)" << endl;
        match(LX_LT);
        cout << "parse Eexpr" << endl;
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_LT, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    else if (tok->type == LX_LE) {
        cout << "match(LX_LE)" << endl;
        match(LX_LE);
        cout << "parse Eexpr" << endl;
        Eexpr = parse_Eexpr();
        Cexpr_par = make_ast_node(AST_LE, C, Eexpr);
        C = parse_Cexpr_par(Cexpr_par);
    }
    return C;
}

AST* parse_Eexpr() {
    cout << "parse_Gexpr() form parse_Fexpr" << endl;
    AST* Fexpr, * Eexpr_par;
    Fexpr = parse_Fexpr();
    Eexpr_par = parse_Eexpr_par(Fexpr);
    return Eexpr_par;
}
AST* parse_Eexpr_par(AST* E) {
    AST* Fexpr, * Eexpr_par;
    cout << "we now in parse_Fexpr_par" << endl;
    if (tok->type == LX_PLUS) {
        cout << "match(LX_PLUS)" << endl;
        match(LX_PLUS);
        Fexpr = parse_Fexpr();
        Eexpr_par = make_ast_node(AST_PLUS, E, Fexpr);
        E = parse_Eexpr_par(Eexpr_par);
    }
    else if (tok->type == LX_MINUS) {
        cout << "match(LX_MINUS)" << endl;
        match(LX_MINUS);
        cout << "parse Fexpr" << endl;
        Fexpr = parse_Fexpr();
        Eexpr_par = make_ast_node(AST_MINUS, E, Fexpr);
        E = parse_Eexpr_par(Eexpr_par);
    }
    return E;
}
AST* parse_Fexpr() {
    cout << "parse_Gexpr() form parse_Fexpr" << endl;
    AST *Gexpr, *Fexpr_par;
    Gexpr= parse_Gexpr();
    Fexpr_par=parse_Fexpr_par(Gexpr);
    return Fexpr_par;
}
AST* parse_Fexpr_par(AST* F) {
    AST* Gexpr, * Fexpr_par;
    cout << "we now in parse_Fexpr_par" << endl;
    if (tok->type == LX_STAR) {
        cout << "match(LX_STAR)" << endl;
        match(LX_STAR);
        Gexpr= parse_Gexpr();
        Fexpr_par =make_ast_node(AST_TIMES, F,Gexpr);
        F = parse_Fexpr_par(Fexpr_par);
    }
    else if (tok->type == LX_SLASH) {
        cout << "match(LX_SLASH)" << endl;
        match(LX_SLASH);
        cout << "parse Gexpr" << endl;
        Gexpr = parse_Gexpr();
        Fexpr_par = make_ast_node(AST_DIVIDE, F, Gexpr);
        F = parse_Fexpr_par(Fexpr_par);
    }
    

        return F;
    
}
AST* parse_Gexpr() {
    cout << "we now in parse_Gexpr" << endl;
    AST* Gexpr;
    if (tok->type==LX_MINUS) {
        cout << "match(LX_MINUS)" << endl;
        match(LX_MINUS);
        cout <<"parse Gexpr" << endl;
       // Gexpr
        return make_ast_node(AST_UMINUS, parse_Gexpr());
    }
    else if (tok->type == KW_NOT) {
        cout << "match(KW_NOT)" << endl;
        match(KW_NOT);
        cout << "parse Gexpr" << endl;
        return make_ast_node(AST_NOT, parse_Gexpr());
    }
    else {
        
        return parse_Hexpr();
    }
}
AST* parse_Hexpr() {
    AST* ret = new AST();
    if (tok->type==LX_INTEGER) {
        cout << " match(LX_INTEGER)" << endl;
        int val = tok->value;
        match(LX_INTEGER);
        ret = make_ast_node(AST_INTEGER,val);
        return ret;
    }
    else if (tok->type == LX_STRING) {
        cout << " match(LX_STRING)" << endl;
        char* chptr = tok->str;
        match(LX_STRING);
        ret = make_ast_node(AST_STRING, chptr);
        return ret;
    }
    else if (tok->type == KW_TRUE) {
        cout << " match(KW_TRUE)" << endl;
        match(KW_TRUE);
        ret = make_ast_node(AST_BOOLEAN, 1);
        return ret;
    }
    else if (tok->type == KW_FALSE) {
        cout << " match(KW_FALSE)" << endl;
        match(KW_FALSE);
        ret = make_ast_node(AST_BOOLEAN, 0);
        return ret;
    }
    else if (tok->type == LX_LPAREN) {
        cout << " match(LX_LPAREN)" << endl;
        match(LX_LPAREN);
        cout << " ((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((" << endl;
        cout << "parse_Bexpe() called from Hexpe" << endl;
        ret=parse_Bexpr();
        cout << " match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
        return ret;
    }
    else if (tok->type == LX_IDENTIFIER) {
        cout << " match(LX_IDENTIFIER)" << endl;
        char* name = tok->str;
        SymbolTableEntry *e = new SymbolTableEntry();
        match(LX_IDENTIFIER);
        cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
        e = pars.getSymbolFromTable(name);
        return parse_id_expr_tail(e);
       /* ret = make_ast_node(AST_VAR,e);
        return ret;*/
    }
    else {
        fd->reportError("valid token for Hexpr grammer ", 'p');
    }
}
AST* parse_id_expr_tail(SymbolTableEntry* e) {
    if (tok->type==LX_LPAREN) {
        if (e->steType == STE_VAR)fd->reportError("the variable connat have a argument list", 'a');
        if (e->steType == STE_CONST)fd->reportError("the constant connat have an argument list", 'a');
        cout << "parse_arg_list()" << endl;
        return parse_arg_list(e);
    }
    else {
        if (e->steType == STE_ROUTINE)fd->reportError(e->Name, 'm');
        cout << "lamda case in parse_id_expr_tail" << endl;
        return make_ast_node(AST_VAR, e);
    }
}
AST* parse_arg_list(SymbolTableEntry* e) {
    cout << " match(LX_LPAREN)" << endl;
    match(LX_LPAREN);
    return parse_arg_list_tail(e);
}
AST* parse_arg_list_tail(SymbolTableEntry* e) {
    AST* ret = new AST();
    if (tok->type==LX_RPAREN) {
        cout << ")))))) match(LX_RPAREN)" << endl;
        match(LX_RPAREN);
       // ast_list* headList =NULL;
        //headList->head = NULL;
        //headList->tail = NULL;
        ret = make_ast_node(AST_CALL,e, NULL);
    }
    else {
        cout << "parse_args() " << endl;
        ast_list* headList = new ast_list();
        headList=parse_args(headList);
        cout << " match(RX_LPAREN)" << endl;
        match(LX_RPAREN);
        cargs = 0;
        FILE* ff = fopen("out4.txt","w");
        print_ast_list(ff,headList, ", ", 0);
        fclose(ff);
        ret = make_ast_node(AST_CALL, e, headList);
    }
}
ast_list* parse_args(ast_list* headList) {
    ast_list* List = new ast_list();
    cout << "parse Bexpr() from parse_args" << endl;
    if (cargs==0) {
        cargs++;
        headList->head=parse_Bexpr();
        cout << "parse ards_tail() from parse_args" << endl;
        headList->tail = parse_args_tail(headList);
        return headList;
    }
    else {
        cargs++;
        List->head = parse_Bexpr();
        cout << "parse ards_tail() from parse_args" << endl;
        //List->tail = NULL;
        List->tail = parse_args_tail(headList);
        return List;
    }
    

    //return headList;
}
ast_list* parse_args_tail(ast_list* headList) {
    if (tok->type==LX_COMMA) {
        cout << " match(LX_COMMA)" << endl;
        match(LX_COMMA);
        return parse_args(headList);
    }
    else {
        cout << "nnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn" << endl;
        return NULL;
    }
}
void Parser::enterScope(SymbolTable* stTemp)
{
    //stTemp = new SymbolTable();
    stTemp->nextST = tabl;
    tabl = stTemp;
}

void Parser::exitScope(SymbolTable* stTemp)
{

    stTemp = tabl;
    tabl = tabl->nextST;
    //delete stTemp;
    cout << "end" << endl;
}
SymbolTableEntry* Parser::getSymbolFromTable(const char* str)
{
    SymbolTable* temp = tabl;
    // stTemp = tabl;
    while (temp != NULL)
    {

        if (temp->GetSymbol(str) != NULL) {
            return temp->GetSymbol(str);

        }
        temp = temp->nextST;
    }
    return NULL;

}
int  getIdetifier(FILE* fp, char* str, J_type& type)
{
    char s1[64] = "\0", s2[64] = "\0", s3[64] = "\0";
    //int n = fscanf(fp,"%s%s%s\n", s1,s2,s3);
    int n = fscanf(fp, "%s", s1);
    if (strcmp(s1, "begin") == 0) {
        return 1;
    }
    else if (strcmp(s1, "end") == 0) {
        return 2;
    }
    else if (strcmp(s1, "\0") == 0) {
        return 4;
    }
    else {
        n = fscanf(fp, "%s%s", s2, s3);
        strcpy(str, s2);
        type = SymbolTableEntry::getType(s1);  // notice how we call a static function or data member
        return 3;
    }
    ///printf("%s  %s  %s  \n",s1,s2,s3);
    //printf ("(n= %d,%s,%s,%s)\n", n, s1, s2, s3);

    //printf ("-(%d,%s)\n",(int)type, str); //to make sure  it is reading correctly

}
void match(LEXEME_TYPE lx) {
    if (lx == tok->type) {
        cout << "lx :"<<lx << endl;
        tok=scan.Scan();
        return;
    }
    else {
        //fd->ungetChar();
        fd->reportError(type_name(lx), 'p');
        exit(1);
    }
}
Parser::~Parser()
{
    //delete tabl;
    //delete fd;
}
int main() {
    FILE* fout = fopen("out.txt", "w");
    tok=scan.Scan();
    AST *head= pars.parse();
    print_ast_node(fout,head);
    //ast_list* astList =pars.parse();
    //print_ast_list(fout, astList, " ", 0);
    //make_ast_node();
    
    //pars.parse();
    //cout << "token type: " << tok->type << endl;
    //        if (tok->str != NULL) {
    //        cout << " token->str = ";
    //        for (int i = 0; tok->str[i] != '\0'; i++) {
    //            cout << tok->str[i];
    //        }
    //        cout << endl;
    //    }
    //match(KW_CHAR);
    //cout << "scan.Fd->getCharNum(): " << scan.Fd->getCharNum() << endl;
    //cout << "pars.fd->getCharNum(): " << pars.fd->getCharNum() << endl;
    // pars.fd->getCharNum();
    //FileDescriptor *fd=new FileDescriptor();
    //STE_TYPE type;
    //char str[64];
    //Parser pars(fd);
    //fp = fopen("t.txt", "r");
    //if (!fp) return 0;
    //FILE* fout = fopen("out.txt", "w");   //set fout = stdout for screen output

    //fprintf(fout, "\n**(Test 1)**: Reading from the file t.txt and creating a symnol table with size = 19(default)\n\n");
    //int n;
    //bool Added;
    //SymbolTable* stTemp = new SymbolTable();
    //while (!feof(fp))
    //{
    //    n = getIdetifier(fp, str, type);
    //    if (n == 1) {
    //        // when detect begin
    //        pars.enterScope(stTemp);

    //    }
    //    else if (n == 2) {
    //        // when detect end
    //        fprintf(fout, "\n==============\n");
    //        pars.tabl->PrintAll(fout);
    //        fprintf(fout, "\n==============\n");
    //        pars.exitScope(stTemp);

    //    }
    //    else if (n == 4) {
    //        cout << "new line" << endl;
    //    }
    //    else if (n == 3)
    //    {
    //        Added = pars.tabl->PutSymbol(str, type);
    //        if (!Added)fprintf(fout, "Entry %s Already Exists\n", str);
    //    }
    //}
    //fclose(fp);


    //fprintf(fout, "\n==============\n");
    //pars.tabl->PrintAll(fout);
    //pars.tabl->PrintSymbolStats(fout);
    //fprintf(fout, "\n==============\n");

    //fprintf(fout, "\n\n**(Test 2)**: Searching for some Variables in the Symobol Table Created\n\n");
    //
    //printf("GetSymbol %s\n", pars.tabl->GetSymbol("k", fout)->toString());
    //printf("GetSymbol %d\n", pars.tabl->ste_var_type(pars.tabl->GetSymbol("k", fout)));
    ////printf("GetSymbol %d", pars.tabl->GetSymbol("k", fout)->getType());
    //pars.tabl->GetSymbol("k", fout);
    //pars.tabl->GetSymbol("x", fout);
    //pars.tabl->GetSymbol("dog", fout);

    //pars.tabl->ClearSymbolTable();
    //fprintf(fout, "\nClear Global Symbol Table\n==============\n");
    //pars.tabl->PrintAll(fout);
    //fprintf(fout, "\n==============\n");

    //fprintf(fout, "\n\n**(Test 2)**: Searching for some Variables in the Symobol Table Created\n\n");
    //pars.tabl->GetSymbol("m", fout);
    //pars.tabl->GetSymbol("k", fout);
    //pars.tabl->GetSymbol("x", fout);
    //pars.tabl->GetSymbol("dog", fout);

    //fprintf(fout, "\n------------------done-------------------\n");
    fclose(fout);
    //delete pars.tabl;
    return 0;
}
