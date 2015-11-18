#pragma once

#include "Expr.h"

class Single : public Expr {
public:
	virtual ExprPtr eval();
};

typedef shared_ptr<Single> SinglePtr;