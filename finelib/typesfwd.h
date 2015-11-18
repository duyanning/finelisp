#pragma once

class Expr;
//class List;
class Cell;
class Single;
class Quoted;
class Num;
class Int;
class Str;
class Sym;
class Callable;
class Func;
class Macro;
class Env;
class True;

typedef shared_ptr<Expr> ExprPtr;
typedef shared_ptr<Cell> CellPtr;
typedef CellPtr ListPtr;
typedef shared_ptr<Single> SinglePtr;
typedef shared_ptr<Quoted> QuotedPtr;
typedef shared_ptr<Num> NumPtr;
typedef shared_ptr<Int> IntPtr;
typedef shared_ptr<Str> StrPtr;
typedef shared_ptr<Sym> SymPtr;
typedef shared_ptr<Callable> CallablePtr;
typedef shared_ptr<Func> FuncPtr;
typedef shared_ptr<Macro> MacroPtr;
typedef shared_ptr<Env> EnvPtr;
typedef shared_ptr<True> TruePtr;

