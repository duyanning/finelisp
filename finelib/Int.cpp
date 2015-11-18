#include "std.h"
#include "Int.h"

Int::Int(int x)
	:
	m_x(x)
{
}

string Int::printed_rep()
{
	ostringstream oss;
	oss << m_x;
	return oss.str();
}

ExprPtr Int::eval()
{
	return shared_from_this();
}

int Int::get()
{
	return m_x;
}


IntPtr make_int(int x)
{
	return IntPtr(new Int(x));
}