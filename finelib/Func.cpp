#include "std.h"
#include "Func.h"
#include "Cell.h"
#include "Err.h"
#include "Env.h"
#include "Sym.h"
#include "primitive.h"

Func::Func(ListPtr lambda, EnvPtr env)
	:
	m_lambda(lambda),
	m_env(env)
{
}

Func::Func(string prim_name)
	:
	m_prim_name(prim_name)
{
}

ListPtr Func::lambda()
{
	return m_lambda;
}


EnvPtr Func::env()
{
	return m_env;
}

string Func::prim_name()
{
	return m_prim_name;
}

FuncPtr make_func(ListPtr lambda, EnvPtr env)
{
	return FuncPtr(new Func(lambda, env));
}

FuncPtr make_func(string prim_name)
{
	return FuncPtr(new Func(prim_name));
}

ExprPtr Func::eval()
{
	return nullptr;
}

string Func::printed_rep()
{
	return m_lambda->printed_rep();
}

ExprPtr process_normal_functions(FuncPtr f, ListPtr args)
{
	ExprPtr params_expr = f->lambda()->cdrlist()->car();
	if (dynamic_pointer_cast<Cell>(params_expr) == nullptr) {
		throw Error("params list not a list");
	}
	ListPtr params = static_pointer_cast<List>(params_expr);

	if (args->length() != params->length()) {
		throw Error("number no equal");
	}

	// 建立新栈帧
	EnvPtr new_env = make_env(f->env());
	// 在新栈帧中绑定参数和引数
	while (!params->is_nil()) {
		ExprPtr p_expr = params->car();
		SymPtr p_sym = static_pointer_cast<Sym>(p_expr);

		ExprPtr a_expr = args->car()->eval_trace();

		new_env->add_binding(p_sym, a_expr);

		params = params->cdrlist();
		args = args->cdrlist();
	}

	EnvPtr old_env = get_current_env();
	set_current_env(new_env);

	// 对body中各个表达式挨个求值
	ListPtr body_list = f->lambda()->cdrlist()->cdrlist();
	ExprPtr result;
	while (!body_list->is_nil()) {
		ExprPtr e = body_list->car();
		result = e->eval_trace();
		body_list = body_list->cdrlist();
	}

	// 恢复老的env
	set_current_env(old_env);

	return result;
}

ExprPtr process_prims(FuncPtr f, ListPtr args)
{
	string prim_name = f->prim_name();
	PrimFunc prim = get_prim_func(prim_name);
	return prim(args);
}

ExprPtr Func::apply(ListPtr args)
{
	FuncPtr me = static_pointer_cast<Func>(shared_from_this());
	if (!m_prim_name.empty()) {
		return process_prims(me, args);
	}
	else {
		return process_normal_functions(me, args);
	}
}
