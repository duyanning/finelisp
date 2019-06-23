#pragma once

#include "Single.h"
#include "typesfwd.h"

class Sym : public Single {
public:
	string get();
	string printed_rep();
	virtual ExprPtr eval();
protected:
	Sym(string name);
private:
	string m_name;

	friend SymPtr make_sym(string name);
};

typedef shared_ptr<Sym> SymPtr;

SymPtr make_sym(string name);
