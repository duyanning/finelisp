#include "std.h"
#include "Sym.h"
#include "Err.h"
#include "Env.h"


Sym::Sym(string name)
	:
	m_name(name)
{
}

string Sym::get()
{
	return m_name;
}

string Sym::printed_rep()
{
	return m_name;
}

unordered_map<string, SymPtr> sym_table;
//map<string, SymPtr> sym_table;
SymPtr make_sym(string name)
{
	SymPtr sym = sym_table[name];
	if (sym != nullptr) {
		return sym;
	}

	sym = SymPtr(new Sym(name));
	sym_table[name] = sym;

	return sym;
}


ExprPtr Sym::eval()
{
	EnvPtr env = get_current_env();
	ExprPtr value = env->value_of(static_pointer_cast<Sym>(shared_from_this()));

	if (value == nullptr) {
		ostringstream oss;
		oss << "void variable " << m_name;
		throw Error(oss.str());
	}

	return value;
}
