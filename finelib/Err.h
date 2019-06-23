#pragma once

#include "typesfwd.h"

class Err {
public:
	virtual string msg() = 0;
};

class Error : public Err {
public:
	Error(string msg);
	string msg();
private:
	string m_msg;
};

class WrongNumberOfArgumentsErr : public Err {
public:
	 WrongNumberOfArgumentsErr(int param_num, int arg_num);
	 string msg();
private:
	int m_param_num;
	int m_arg_num;
};

class WrongTypeArgumentErr : public Err {
public:
	WrongTypeArgumentErr(string fname, string varname);
	string msg();
private:
	string m_fname;
	string m_varname;
};

typedef bool Pred(ExprPtr);
void check_type(const char* pred_name, Pred pred, ExprPtr var);
void check_args_num(int param_num, int arg_num);

#define CHECK_TYPE(pred, var) check_type(#pred, pred, var)
#define CHECK_ARGS_NUM(param_num, arg_num) check_args_num(param_num, arg_num)
