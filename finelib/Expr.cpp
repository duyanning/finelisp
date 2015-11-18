#include "std.h"
#include "Expr.h"
#include "Cell.h"

Expr::~Expr()
{
}


string Expr::printed_rep()
{
	return "what?";
}

ExprPtr Expr::eval_trace()
{
	try {
		return eval();
	}
	catch (...) {
		cout << printed_rep() << endl;
		throw;
	}
}

bool null(ExprPtr e)
{
	if (dynamic_pointer_cast<Cell>(e) == nullptr)
		return false;
	CellPtr c = static_pointer_cast<Cell>(e);
	return c->is_nil();
}
