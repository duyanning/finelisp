#include "std.h"
#include "Str.h"

Str::Str(string x)
	:
	m_x(x)
{
}

string Str::printed_rep()
{
	ostringstream oss;
	oss << "\"" << m_x << "\"";
	return oss.str();
}

string Str::get()
{
	return m_x;
}

StrPtr make_str(string x)
{
	return StrPtr(new Str(x));
}
