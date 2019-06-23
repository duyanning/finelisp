#pragma once

#include "typesfwd.h"

class Env;
typedef shared_ptr<Env> EnvPtr;

class Env {
public:
	Env(EnvPtr outter);
	void add_binding(SymPtr sym, ExprPtr expr);
	ExprPtr value_of(SymPtr sym);
protected:
private:
	EnvPtr m_outter;
	//hash_map<SymPtr, ExprPtr> m_bindings;
	map<SymPtr, ExprPtr> m_bindings;

	friend EnvPtr make_env(EnvPtr outter);
};

EnvPtr get_current_env();
void set_current_env(EnvPtr f);

EnvPtr make_env(EnvPtr outter);