#pragma once

#include "Callable.h"
#include "typesfwd.h"

class Func : public Callable {
public:
	string prim_name();
	ListPtr lambda();
	EnvPtr env();
	ExprPtr eval();
	string printed_rep();
	ExprPtr apply(ListPtr args);
protected:
	Func(ListPtr lambda, EnvPtr env);
	Func(string prim_name);
private:
	// built-in function��special form
	string m_prim_name;

	// �û��Զ��庯��
	ListPtr m_lambda;
	EnvPtr m_env;

	friend FuncPtr make_func(ListPtr lambda, EnvPtr env);
	friend FuncPtr make_func(string prim_name);
};

FuncPtr make_func(ListPtr lambda, EnvPtr env);
FuncPtr make_func(string prim_name);
