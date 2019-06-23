#include "std.h"
#include "Err.h"
#include "Expr.h"

Error::Error(string msg)
	:
	m_msg(msg)
{
}

string Error::msg()
{
	return m_msg;
}

WrongTypeArgumentErr::WrongTypeArgumentErr(string fname, string varname)
	:
	m_fname(fname),
	m_varname(varname)
{
}

string WrongTypeArgumentErr::msg()
{
	ostringstream oss;
	oss << "wrong type argument: " << m_fname << " " << m_varname << " failed." << endl;
	return oss.str();
}

WrongNumberOfArgumentsErr::WrongNumberOfArgumentsErr(int param_num, int arg_num)
	:
	m_param_num(param_num),
	m_arg_num(arg_num)
{
}

string WrongNumberOfArgumentsErr::msg()
{
	ostringstream oss;
	oss << "wrong number of argumets: " << m_param_num << " expected, but " << m_arg_num << " supplied." << endl;
	return oss.str();
}

void check_type(const char* pred_name, Pred pred, ExprPtr var)
{
	if (!pred(var)) {
		throw WrongTypeArgumentErr(pred_name, var->printed_rep());
	}
}

void check_args_num(int param_num, int arg_num)
{
	if (param_num != arg_num) {
		throw WrongNumberOfArgumentsErr(param_num, arg_num);
	}
}
