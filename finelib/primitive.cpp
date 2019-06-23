#include "std.h"
#include "primitive.h"
#include "finelib.h"

unordered_map<string, PrimFunc> prim_name_to_func;

void defsubr(Prim* prim)
{
	string prim_name = prim->lname;
	PrimFunc prim_func = prim->fnname;

	prim_name_to_func[prim_name] = prim_func;


	SymPtr symbol = make_sym(prim_name);
	FuncPtr func = make_func(prim_name);

	EnvPtr env = get_current_env();
	env->add_binding(symbol, func);
}

PrimFunc get_prim_func(string prim_name)
{
	return prim_name_to_func[prim_name];
}

// (listp OBJECT)
DEFUN(listp)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());

	ExprPtr arg = args->car()->eval_trace();

	if (listp(arg)) {
		return make_true();
	}
	else {
		return make_nil();
	}
}

// (numberp OBJECT)
DEFUN(numberp)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());

	ExprPtr arg = args->car()->eval_trace();

	if (numberp(arg)) {
		return make_true();
	}
	else {
		return make_nil();
	}
}

// (if COND THEN ELSE...)
DEFUN(if)
(ListPtr args)
{
	ExprPtr COND = args->car()->eval_trace();
	ExprPtr result;
	if (!null(COND)) {
		ExprPtr THEN = args->cdrlist()->car();
		result = THEN->eval_trace();
	}
	else {
		ListPtr ELSES = args->cdrlist()->cdrlist();
		while (!ELSES->is_nil()) {
			ExprPtr e = ELSES->car();
			result = e->eval_trace();
			ELSES = ELSES->cdrlist();
		}
	}
	return result;
}

DEFUN0("+", Fplus, Splus)
(ListPtr args)
{
	int sum = 0;
		
	while (!args->is_nil()) {
		ExprPtr x = args->car()->eval_trace();
		CHECK_TYPE(numberp, x);

		sum += static_pointer_cast<Int>(x)->get();

		args = args->cdrlist();
	}

	return make_int(sum);
}

DEFUN0("1+", F1plus, S1plus)
(ListPtr args)
{
	int sum = 1;

	CHECK_ARGS_NUM(1, args->length());
	ExprPtr arg = args->car()->eval_trace();
	CHECK_TYPE(numberp, arg);

	sum += static_pointer_cast<Int>(arg)->get();

	return make_int(sum);
}

DEFUN0(">", Fgt, Sgt)
(ListPtr args)
{
	ExprPtr x_expr = args->car()->eval_trace();
	ExprPtr y_expr = args->cdrlist()->car()->eval_trace();
		
	IntPtr x = static_pointer_cast<Int>(x_expr);
	IntPtr y = static_pointer_cast<Int>(y_expr);

	if (x->get() > y->get()) {
		return make_true();
	}
	else {
		return make_nil();
	}
}

DEFUN(prin1)
(ListPtr args)
{
	ExprPtr x = args->car()->eval_trace();
	cout << x->printed_rep();
	return x;
}

DEFUN(car)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());

	ExprPtr arg = args->car()->eval_trace();
	CHECK_TYPE(listp, arg);

	ListPtr l = static_pointer_cast<List>(arg);
	return l->car();
}

DEFUN(cdr)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());

	ExprPtr arg = args->car()->eval_trace();
	CHECK_TYPE(listp, arg);

	ListPtr l = static_pointer_cast<List>(arg);
	return l->cdrlist();
}

DEFUN(cons)
(ListPtr args)
{
		ExprPtr a = args->car()->eval_trace();
		ExprPtr d = args->cdrlist()->car()->eval_trace();
		return cons(a, d);
}


// (set SYMBOL NEWVAL)
DEFUN(set)
(ListPtr args)
{
	SymPtr symbol = static_pointer_cast<Sym>(args->car()->eval_trace());
	ExprPtr newval = args->cdrlist()->car()->eval_trace();

	EnvPtr env = get_current_env();
	env->add_binding(symbol, newval);

	return newval;
}

// (setq [SYM VAL]...)
DEFUN(setq)
(ListPtr args)
{
	SymPtr symbol = static_pointer_cast<Sym>(args->car());
	ExprPtr newval = args->cdrlist()->car()->eval_trace();

	EnvPtr env = get_current_env();
	env->add_binding(symbol, newval);

	return newval;
}

// (lambda ARGS BODY)
DEFUN(lambda)
(ListPtr args)
{
	FuncPtr func = make_func(cons(make_sym("lambda"), args), get_current_env());
	return func;
}

// (defun NAME ARGLIST BODY)
DEFUN(defun)
(ListPtr args)
{
	SymPtr symbol = static_pointer_cast<Sym>(args->car());

	ListPtr lambda = cons(make_sym("lambda"),
						args->cdrlist());
	FuncPtr func = make_func(lambda, get_current_env());

	EnvPtr env = get_current_env();
	env->add_binding(symbol, func);

	return args->car();
}

// (list &rest OBJECTS)
DEFUN(list)
(ListPtr args)
{
	stack<ExprPtr> evaluated_args;

	while (!args->is_nil()) {
		ExprPtr e = args->car()->eval_trace();
		evaluated_args.push(e);
		args = args->cdrlist();
	}

	ListPtr new_list;
	while (evaluated_args.size() > 0) {
		new_list = cons(evaluated_args.top(), new_list);
		evaluated_args.pop();
	}

	return new_list;
}

// (consp OBJECT)
DEFUN(consp)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());

	ExprPtr arg = args->car()->eval_trace();

	if (consp(arg)) {
		return make_true();
	}
	else {
		return make_nil();
	}
}

// (symbolp OBJECT)
DEFUN(symbolp)
(ListPtr args)
{
	CHECK_ARGS_NUM(1, args->length());
	
	ExprPtr arg = args->car()->eval_trace();

	if (dynamic_pointer_cast<Sym>(arg) != nullptr) {
		return make_true();
	}

	return make_nil();
}

// (defmacro NAME ARGLIST BODY)
DEFUN(defmacro)
(ListPtr args)
{
	SymPtr symbol = static_pointer_cast<Sym>(args->car());

	ListPtr lambda = cons(make_sym("lambda"),
						args->cdrlist());
	MacroPtr macro = make_macro(lambda, get_current_env());

	EnvPtr env = get_current_env();
	env->add_binding(symbol, macro);

	return args->car();
}


void install_prims()
{
	defsubr(&Slistp);
	defsubr(&Snumberp);
	defsubr(&Sif);
	defsubr(&Splus);
	defsubr(&Sgt);
	defsubr(&Sprin1);
	defsubr(&Scar);
	defsubr(&Scdr);
	defsubr(&Scons);
	defsubr(&Sset);
	defsubr(&Ssetq);
	defsubr(&Slambda);
	defsubr(&Sdefun);
	defsubr(&Slist);
	defsubr(&Sconsp);
	defsubr(&Sdefmacro);
	defsubr(&Ssymbolp);
	defsubr(&S1plus);
}
