#include "std.h"
#include "finelib.h"

Macro::Macro(ListPtr lambda, EnvPtr env)
	:
	m_lambda(lambda),
	m_env(env)
{
}

ListPtr Macro::lambda()
{
	return m_lambda;
}

EnvPtr Macro::env()
{
	return m_env;
}

MacroPtr make_macro(ListPtr lambda, EnvPtr env)
{
	return MacroPtr(new Macro(lambda, env));
}

ExprPtr Macro::eval()
{
	return nullptr;
}

string Macro::printed_rep()
{
	return m_lambda->printed_rep();
}

ExprPtr Macro::apply(ListPtr args)
{
	MacroPtr f = static_pointer_cast<Macro>(shared_from_this());

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

		// 不对引数求值
		ExprPtr a_expr = args->car();

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

	// 现在result就是macro的expansion，对其进行求值

	return result->eval_trace();
}
