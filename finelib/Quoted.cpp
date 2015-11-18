#include "std.h"
#include "Quoted.h"

Quoted::Quoted(ExprPtr x)
	:
	m_x(x)
{
}

string Quoted::printed_rep()
{
	ostringstream oss;
	oss << "(quote ";
	oss << m_x->printed_rep();
	oss << ")";
	return oss.str();
}


ExprPtr Quoted::eval()
{
	return m_x;
}


QuotedPtr make_quoted(ExprPtr x)
{
	return QuotedPtr(new Quoted(x));
}