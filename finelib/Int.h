#pragma once

#include "Num.h"
#include "typesfwd.h"

class Int : public Num {
public:
	string printed_rep();
	ExprPtr eval();
	int get();
protected:
	Int(int x);
private:
	int m_x;

	friend IntPtr make_int(int x);
};

typedef shared_ptr<Int> IntPtr;

IntPtr make_int(int x);
