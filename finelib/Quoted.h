#pragma once

#include "Single.h"
#include "typesfwd.h"

class Quoted : public Single {
public:
	string printed_rep();
	virtual ExprPtr eval();
protected:
	Quoted(ExprPtr x);
private:
	ExprPtr m_x;

	friend QuotedPtr make_quoted(ExprPtr x);
};

typedef shared_ptr<Quoted> QuotedPtr;
QuotedPtr make_quoted(ExprPtr x);
