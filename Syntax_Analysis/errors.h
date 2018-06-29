#define error(string, value) if (Tk == value) return string

string err(int Tk) {
	error("a variable or function declaration", PROGRAM);
	error("a variable or function declaration", GLOBAL_STMTS);
	error("a variable or function declaration", GLOBAL_DECS);
	error("a statement (check manual for valid statements)", STMTS);
	error("an if statement", IF_STATEMENT);
	error("'owise'", OTHERWISE);
	error("'if'", OTHERWISE_BRANCH);
	error("'until'", UNTIL_STATEMENT);
	error("'while'", WHILE_STATEMENT);
	error("while", FOR_STATEMENT);
	error("an id for function declaration", FUNC_DECLARATION);
	error("return variables", RETURNS);
	error("a statement, check manual for valid statements", STMT);
	error("parameters", PARAMETERS);
	error("','", EXTRA_PARAMETERS);
//	error("an expression or list", EXPRORLIST);
	error("an expression", EXPR);
	error("an expression", EXPRA);
	error("an expression", EXPR1);
	error("an expression", EXPRB);
	error("an expression", EXPR2);
	error("an expression", EXPRC);
	error("an expression", EXPR3);
	error("an expression", EXPRD);
	error("an expression", EXPR4);
	error("an expression", EXPRE);
	error("an expression", EXPR5);
	error("an expression", EXPRF);
	error("an expression", EXPR6);
	error("an expression", EXPRG);
	error("an expression", EXPR7);
	error("increment or decrement", OP);
	error("an expression", EXPR8);
	error("an expression", EXPR9);
	error("an expression or ';'", FUNCORDATA);
//	error("'['", LIST_DATA);
//	error("Data list or '['", LST_DATA);
//	error("','", EXTRA_DIMENSION);
//	error("[", DIMENSION);
//	error("expression list or '['", PARAMORLST);
//	error("Data list or '['", LST_DATA_PARAMS);
}

#define ERR(string, value) if (focus == value) return string
string getErrorMessage(int focus, TOKEN current) {
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(PROGRAM), PROGRAM);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(GLOBAL_STMTS), GLOBAL_STMTS);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(GLOBAL_DECS), GLOBAL_DECS);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(STMTS), STMTS);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(IF_STATEMENT), IF_STATEMENT);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(OTHERWISE), OTHERWISE);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(OTHERWISE_BRANCH), OTHERWISE_BRANCH);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(UNTIL_STATEMENT), UNTIL_STATEMENT);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(WHILE_STATEMENT), WHILE_STATEMENT);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(FOR_STATEMENT), FOR_STATEMENT);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(FUNC_DECLARATION), FUNC_DECLARATION);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(RETURNS), RETURNS);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(STMT), STMT);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(PARAMETERS), PARAMETERS);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXTRA_PARAMETERS), EXTRA_PARAMETERS);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRORLIST), EXPRORLIST);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR), EXPR);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRA), EXPRA);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR1), EXPR1);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRB), EXPRB);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR2), EXPR2);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRC), EXPRC);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR3), EXPR3);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRD), EXPRD);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR4), EXPR4);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRE), EXPRE);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR5), EXPR5);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRF), EXPRF);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR6), EXPR6);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPRG), EXPRG);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR7), EXPR7);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(OP), OP);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR8), EXPR8);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXPR9), EXPR9);
    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(FUNCORDATA), FUNCORDATA);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(LIST_DATA), LIST_DATA);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(LST_DATA), LST_DATA);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(EXTRA_DIMENSION), EXTRA_DIMENSION);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(DIMENSION), DIMENSION);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(PARAMORLST), PARAMORLST);
//    ERR("Wrong token '" + current.lexeme + "', expecting "  + err(LST_DATA_PARAMS), LST_DATA_PARAMS);
}


#define ERROR2(string, value) if (focus == value) return string
string getErrorMessageType2(int focus, TOKEN current) {
	ERROR2("Expecting "  + err(PROGRAM) + " before " + current.lexeme, PROGRAM);
	ERROR2("Expecting "  + err(GLOBAL_STMTS) + " before " + current.lexeme, GLOBAL_STMTS);
	ERROR2("Expecting "  + err(GLOBAL_DECS) + " before " + current.lexeme, GLOBAL_DECS);
	ERROR2("Expecting "  + err(STMTS) + " before " + current.lexeme, STMTS);
	ERROR2("Expecting "  + err(IF_STATEMENT) + " before " + current.lexeme, IF_STATEMENT);
	ERROR2("Expecting "  + err(OTHERWISE) + " before " + current.lexeme, OTHERWISE);
	ERROR2("Expecting "  + err(OTHERWISE_BRANCH) + " before " + current.lexeme, OTHERWISE_BRANCH);
	ERROR2("Expecting "  + err(UNTIL_STATEMENT) + " before " + current.lexeme, UNTIL_STATEMENT);
	ERROR2("Expecting "  + err(WHILE_STATEMENT) + " before " + current.lexeme, WHILE_STATEMENT);
	ERROR2("Expecting "  + err(FOR_STATEMENT) + " before " + current.lexeme, FOR_STATEMENT);
	ERROR2("Expecting "  + err(FUNC_DECLARATION) + " before " + current.lexeme, FUNC_DECLARATION);
	ERROR2("Expecting "  + err(RETURNS) + " before " + current.lexeme, RETURNS);
	ERROR2("Expecting "  + err(STMT) + " before " + current.lexeme, STMT);
	ERROR2("Expecting "  + err(PARAMETERS) + " before " + current.lexeme, PARAMETERS);
	ERROR2("Expecting "  + err(EXTRA_PARAMETERS) + " before " + current.lexeme, EXTRA_PARAMETERS);
//	ERROR2("Expecting "  + err(EXPRORLIST) + " before " + current.lexeme, EXPRORLIST);
	ERROR2("Expecting "  + err(EXPR) + " before " + current.lexeme, EXPR);
	ERROR2("Expecting "  + err(EXPRA) + " before " + current.lexeme, EXPRA);
	ERROR2("Expecting "  + err(EXPR1) + " before " + current.lexeme, EXPR1);
	ERROR2("Expecting "  + err(EXPRB) + " before " + current.lexeme, EXPRB);
	ERROR2("Expecting "  + err(EXPR2) + " before " + current.lexeme, EXPR2);
	ERROR2("Expecting "  + err(EXPRC) + " before " + current.lexeme, EXPRC);
	ERROR2("Expecting "  + err(EXPR3) + " before " + current.lexeme, EXPR3);
	ERROR2("Expecting "  + err(EXPRD) + " before " + current.lexeme, EXPRD);
	ERROR2("Expecting "  + err(EXPR4) + " before " + current.lexeme, EXPR4);
	ERROR2("Expecting "  + err(EXPRE) + " before " + current.lexeme, EXPRE);
	ERROR2("Expecting "  + err(EXPR5) + " before " + current.lexeme, EXPR5);
	ERROR2("Expecting "  + err(EXPRF) + " before " + current.lexeme, EXPRF);
	ERROR2("Expecting "  + err(EXPR6) + " before " + current.lexeme, EXPR6);
	ERROR2("Expecting "  + err(EXPRG) + " before " + current.lexeme, EXPRG);
	ERROR2("Expecting "  + err(EXPR7) + " before " + current.lexeme, EXPR7);
	ERROR2("Expecting "  + err(OP) + " before " + current.lexeme, OP);
	ERROR2("Expecting "  + err(EXPR8) + " before " + current.lexeme, EXPR8);
	ERROR2("Expecting "  + err(EXPR9) + " before " + current.lexeme, EXPR9);
	ERROR2("Expecting "  + err(FUNCORDATA) + " before " + current.lexeme, FUNCORDATA);
//	ERROR2("Expecting "  + err(LIST_DATA) + " before " + current.lexeme, LIST_DATA);
//	ERROR2("Expecting "  + err(LST_DATA) + " before " + current.lexeme, LST_DATA);
//	ERROR2("Expecting "  + err(EXTRA_DIMENSION) + " before " + current.lexeme, EXTRA_DIMENSION);
//	ERROR2("Expecting "  + err(DIMENSION) + " before " + current.lexeme, DIMENSION);
//	ERROR2("Expecting "  + err(PARAMORLST) + " before " + current.lexeme, PARAMORLST);
//	ERROR2("Expecting "  + err(LST_DATA_PARAMS) + " before " + current.lexeme, LST_DATA_PARAMS);

}

