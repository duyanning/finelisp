#pragma once

#include "typesfwd.h"

ExprPtr process_functions(string fname, ListPtr list);
ExprPtr process_normal_functions(FuncPtr f, ListPtr args);
ExprPtr process_prims(FuncPtr f, ListPtr args);
