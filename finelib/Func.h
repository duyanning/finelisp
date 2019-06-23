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
	// built-in function跟special form
	string m_prim_name;

	// 用户自定义函数
	ListPtr m_lambda;
	EnvPtr m_env;

	friend FuncPtr make_func(ListPtr lambda, EnvPtr env);
	friend FuncPtr make_func(string prim_name);
};

FuncPtr make_func(ListPtr lambda, EnvPtr env);
FuncPtr make_func(string prim_name);
