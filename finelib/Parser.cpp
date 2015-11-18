#include "std.h"
#include "Parser.h"
#include "finelib.h"

Parser::Parser(string s, bool is_filename)
{
	if (is_filename) {
		m_is = shared_ptr<istream>(new ifstream(s));
		if (!m_is) {
			throw Error("file " + s + " not found");
		}
	}
	else {
		m_is = shared_ptr<istream>(new istringstream(s));
	}

	m_scanner = shared_ptr<Scanner>(new Scanner(*m_is));


}


ExprPtr Parser::read_eval()
{
	ExprPtr last_result;
	m_word = m_scanner->get_word();
	while (m_word.type != "EOF") {
		ExprPtr expr = read_expr();
		last_result = expr->eval_trace();

		m_word = m_scanner->get_word();
	}
	return last_result;
}


ExprPtr Parser::read_expr()
{
	ExprPtr expr;
	if (m_word.type == "(") {
		expr = read_list();
	}
	else {
		expr = read_single();
	}

	return expr;
}


ListPtr Parser::read_list()
{

	CellPtr head = make_cell();
	CellPtr current = head;

	m_word = m_scanner->get_word();

	ExprPtr expr;
	if (m_word.type == ")") {
		return head;
	}
	else {
		expr = read_expr();
		head->setcar(expr);

		m_word = m_scanner->get_word();
	}

	while (m_word.type != ")") {
		if (m_word.type == ".") {
			m_word = m_scanner->get_word();
			expr = read_expr();
			current->setcdr(expr);

			m_word = m_scanner->get_word();
		}
		else if (m_word.type == ")") {
			break;
		}
		else {
			expr = read_expr();
			CellPtr new_cell = make_cell();
			new_cell->setcar(expr);
			current->setcdr(new_cell);
			current = new_cell;

			m_word = m_scanner->get_word();
		}
	}

	return head;
}


SinglePtr Parser::read_single()
{
	if (m_word.type == "sym") {
		return make_sym(m_word.content);
	}

	if (m_word.type == "int") {
#if defined(__CYGWIN32__) || defined(__MINGW32__)
        istringstream iss(m_word.content);
        int x;
        iss >> x;
        return make_int(x);
#else
		return make_int(stoi(m_word.content));
#endif
	}

	if (m_word.type == "str") {
		return make_str(m_word.content);
	}

	if (m_word.type == "t") {
		return make_true();
	}

	if (m_word.type == "'") {
		m_word = m_scanner->get_word();
		ExprPtr expr = read_expr();
		return make_quoted(expr);
	}

	return nullptr;
}


ExprPtr eval(string s)
{
	Parser parser(s, false);
	return parser.read_eval();
}
