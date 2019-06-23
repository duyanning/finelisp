#include "std.h"
#include "Cell.h"
#include "Err.h"
#include "Str.h"
#include "Sym.h"
#include "Int.h"
#include "Quoted.h"
#include "funtions.h"
#include "Env.h"
#include "Func.h"

Cell::Cell(ExprPtr car, ExprPtr cdr)
	:
	m_car(car),
	m_cdr(cdr)
{
}

bool Cell::is_nil()
{
	if (!m_car) {
		return true;
	}

	return false;
}


int Cell::length()
{
	int len = 0;
	CellPtr p = static_pointer_cast<Cell>(shared_from_this());
	while (p) {
		len++;

		if (p->m_cdr == nullptr) {
			break;
		}
		else if (dynamic_pointer_cast<Cell>(p->m_cdr) == nullptr) {
			break;
		}
		else { // Cell
			p = static_pointer_cast<Cell>(p->m_cdr);
		}
	}

	return len;
}

ExprPtr Cell::car()
{
	if (is_nil()) {
		return make_nil();
	}

	return m_car;
}

ExprPtr Cell::cdr()
{
	if (is_nil()) {
		return make_nil();
	}

	return m_cdr;
}

CellPtr Cell::cdrlist()
{
	if (is_nil()) {
		return make_nil();
	}

	if (!m_cdr) {
		return make_nil();
	}

	if (dynamic_pointer_cast<Cell>(m_cdr) == nullptr) {
		throw Error("cdr is not a cell");
	}
	return static_pointer_cast<Cell>(m_cdr);
}

void Cell::setcar(ExprPtr car)
{
	m_car = car;
}

void Cell::setcdr(ExprPtr cdr)
{
	m_cdr = cdr;
}

string Cell::printed_rep()
{
	if (m_car == nullptr) {
		return "nil";
	}

	ostringstream oss;

	oss << "(";
	CellPtr p = static_pointer_cast<Cell>(shared_from_this());
	while (p) {
		oss << p->m_car->printed_rep();

		if (p->m_cdr == nullptr) {
			break;
		}
		else if (dynamic_pointer_cast<Cell>(p->m_cdr) == nullptr) {
			oss << " . " << p->m_cdr->printed_rep();
			break;
		}
		else { // Cell
			oss << " ";
			p = static_pointer_cast<Cell>(p->m_cdr);
		}
	}
	oss << ")";

	return oss.str();
}

ExprPtr Cell::eval()
{
	if (m_car == nullptr) {
		return shared_from_this();
	}

	ExprPtr value = m_car->eval_trace();

	if (value == nullptr) {
		throw Error("void function");
	}


	if (nullptr == dynamic_pointer_cast<Callable>(value)) {
		throw Error("not callable");
	}

	CallablePtr f = static_pointer_cast<Callable>(value);
	return f->apply(cdrlist());
}


CellPtr make_cell(ExprPtr car, ExprPtr cdr)
{
	return CellPtr(new Cell(car, cdr));
}

CellPtr make_nil()
{
	return make_cell(nullptr, nullptr);
}

CellPtr cons(ExprPtr a, ExprPtr d)
{
	CellPtr c = make_cell(a, d);
	return c;
}

bool consp(ExprPtr e)
{
	if (!dynamic_pointer_cast<Cell>(e))
		return false;
	CellPtr c = static_pointer_cast<Cell>(e);
	if (c->is_nil())
		return false;
	return true;
}

bool listp(ExprPtr e)
{
	return dynamic_pointer_cast<List>(e) != nullptr;
}
