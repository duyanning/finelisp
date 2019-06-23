#pragma once

#include "Scanner.h"
#include "Cell.h"
#include "Single.h"

class Parser {
public:
	Parser(string str, bool is_filename = true);
	ExprPtr read_eval();
private:
	ExprPtr read_expr();
	ListPtr read_list();
	SinglePtr read_single();

	shared_ptr<istream> m_is;
	shared_ptr<Scanner> m_scanner;
	Word m_word;
};

ExprPtr eval(string s);

// Expr ::= Cell | Single
// Cell :: = (Expr ...)
// Single ::= Int | Sym | Str | 'Expr