#include "std.h"
#include "Single.h"

ExprPtr Single::eval()
{
	return shared_from_this();
}
