#include "std.h"
#include "Env.h"
#include "Expr.h"

EnvPtr current_env;

EnvPtr get_current_env()
{
	if (current_env == nullptr) {
		current_env = EnvPtr(make_env(nullptr));
	}

	return current_env;
}

void set_current_env(EnvPtr f)
{
	current_env = f;
}

Env::Env(EnvPtr outter)
	:
	m_outter(outter)
{
}

void Env::add_binding(SymPtr sym, ExprPtr expr)
{
	m_bindings[sym] = expr;
}

ExprPtr Env::value_of(SymPtr sym)
{
	// 先在自己里面找
	ExprPtr value = m_bindings[sym];
	if (value != nullptr) {
		return value;
	}

	// 找不到就去外围找
	if (m_outter == nullptr) {
		return nullptr;
	}
	return m_outter->value_of(sym);
}

EnvPtr make_env(EnvPtr outter)
{
	return EnvPtr(new Env(outter));
}