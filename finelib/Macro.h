#pragma once

#include "Callable.h"
#include "typesfwd.h"

class Macro : public Callable {
public:
	ListPtr lambda();
	EnvPtr env();
	ExprPtr eval();
	string printed_rep();
	ExprPtr apply(ListPtr args);
protected:
	Macro(ListPtr lambda, EnvPtr env);
private:
	ListPtr m_lambda;
	EnvPtr m_env;

	friend MacroPtr make_macro(ListPtr lambda, EnvPtr env);
};

MacroPtr make_macro(ListPtr lambda, EnvPtr env);
