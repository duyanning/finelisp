#pragma once

struct Word {
	string type;
	string content;
};

class Scanner {
public:
	Scanner(istream& ifs);
	Word get_word();
private:
	istream& m_is;
};
