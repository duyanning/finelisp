#pragma once

#include "Expr.h"
#include "typesfwd.h"

class Cell;
typedef shared_ptr<Cell> CellPtr;
typedef CellPtr ListPtr;
typedef Cell List;

class Cell : public Expr {
public:
	bool is_nil();
	int length();
	ExprPtr car();
	ExprPtr cdr();
	CellPtr cdrlist();

	void setcar(ExprPtr car);
	void setcdr(ExprPtr cdr);

	string printed_rep();
	ExprPtr eval();
protected:
	Cell(ExprPtr car, ExprPtr cdr);
private:
	ExprPtr m_car;
	ExprPtr m_cdr;

	friend CellPtr make_cell(ExprPtr car, ExprPtr cdr);
};

CellPtr make_cell(ExprPtr car = nullptr, ExprPtr cdr = nullptr);
CellPtr cons(ExprPtr a, ExprPtr d);
CellPtr make_nil();
