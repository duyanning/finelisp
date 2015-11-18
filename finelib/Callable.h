#pragma once 

#include "Single.h"
#include "typesfwd.h"

class Callable : public Single {
public:
	virtual ExprPtr apply(ListPtr args) = 0;
};
