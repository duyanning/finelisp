#pragma once

#include "Single.h"
#include "typesfwd.h"

class Str : public Single {
public:
	string printed_rep();

	string get();
protected:
	Str(string x);
private:
	string m_x;

	friend StrPtr make_str(string x);
};

typedef shared_ptr<Str> StrPtr;

StrPtr make_str(string x);
