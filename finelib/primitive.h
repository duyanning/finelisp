#pragma once

#include "typesfwd.h"

typedef ExprPtr (*PrimFunc)(ListPtr args);

struct Prim {
	string lname;
	PrimFunc fnname;
};


#define DEFUN0(lname, fnname, sname)	\
ExprPtr fnname(ListPtr args); \
static Prim sname = { \
    lname, \
	fnname \
}; \
ExprPtr fnname


#define DEFUN(name)	DEFUN0((# name), (F ## name), (S ## name))


PrimFunc get_prim_func(string prim_name);
void install_prims();