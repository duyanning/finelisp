#include "std.h"
#include "Num.h"

bool numberp(ExprPtr e)
{
	return dynamic_pointer_cast<Num>(e) != nullptr;
}

