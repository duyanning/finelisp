#include "std.h"
#include "True.h"

True::True()
{
}

string True::printed_rep()
{
	return "t";
}

ExprPtr True::eval()
{
	return shared_from_this();
}

TruePtr make_true()
{
	return TruePtr(new True);
}