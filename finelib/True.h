#pragma once

#include "typesfwd.h"
#include "Single.h"

class True : public Single {
public:
	string printed_rep();
	ExprPtr eval();
	int get();
protected:
	True();
private:

	friend TruePtr make_true();
};

typedef shared_ptr<True> TruePtr;

TruePtr make_true();
