#pragma once

class Expr;
typedef shared_ptr<Expr> ExprPtr;

class Expr : public enable_shared_from_this<Expr> {
public:
	virtual ~Expr();
	virtual string printed_rep();
	virtual ExprPtr eval() = 0;
	ExprPtr eval_trace();
protected:
private:
};

bool consp(ExprPtr e);
bool listp(ExprPtr e);
bool null(ExprPtr e);
bool numberp(ExprPtr e);
