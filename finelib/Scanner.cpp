#include "std.h"
#include "Scanner.h"
#include "Err.h"

Scanner::Scanner(istream& ifs)
	:
	m_is(ifs)
{
}


//bool is_symchar(int c)
//{
//	if (isalnum(c)) {
//		return true;
//	}
//
//	if ('+' == c)
//		return true;
//
//	return false;
//}


Word Scanner::get_word()
{
	Word w;

	int c = m_is.get();

	// skip white space and comment
	while (isspace(c) || c == ';') {
		if (isspace(c)) {
			c = m_is.get();
		}
		else {
			m_is.ignore(numeric_limits<streamsize>::max(), '\n');
			c = m_is.get();
		}
	}

	if (c == '(') {
		w.type = "(";
		w.content = "(";
		return w;
	}

	if (c == ')') {
		w.type = ")";
		w.content = ")";
		return w;
	}

	if (c == '\'') {
		w.type = "'";
		w.content = "'";
		return w;
	}

	if (c == 't') {
		w.type = "t";
		w.content = "t";
		return w;
	}

	if (c == '\"') {
		string s;
		c = m_is.get();
		if (c == EOF) {
			throw Error("unexpected end of file");
		}

		while (c != '\"') {
			if (c != '\\') {
				s += c;
			}
			else {
				c = m_is.get();
				if (c == EOF) {
					throw Error("unexpected end of file");
				}
				switch (c) {
				case 'n':
					s += '\n';
					break;
				case '\\':
					s += '\\';
					break;
				case 't':
					s += '\t';
					break;
				default:
					throw Error("unknow escape character");
				} // switch
			} // if

			c = m_is.get();
			if (c == EOF) {
				throw Error("unexpected end of file");
			}

		} // while

		w.type = "str";
		w.content = s;
		return w;
	}


	if (c == EOF) {
		w.type = "EOF";
		w.content = "EOF";
		return w;
	}
	
	if (isdigit(c)) {
		ostringstream oss;
		while (isdigit(c)) {
			oss.put(c);
			c = m_is.get();
		}

		if (isspace(c) || c == ')' || c == EOF) {
			m_is.unget();
			w.type = "int";
			w.content = oss.str();

			return w;
		}

		while (!(isspace(c) || c == ')' || c == EOF)) {
			oss.put(c);
			c = m_is.get();
		}
		m_is.unget();
		w.type = "sym";
		w.content = oss.str();
		return w;

	}

	if (!(isspace(c) || c == ')' || c == EOF)) {
		ostringstream oss;
		while (!(isspace(c) || c == ')' || c == EOF)) {
			oss.put(c);
			c = m_is.get();
		}

		m_is.unget();
		w.type = "sym";
		w.content = oss.str();

		return w;

	}
	
	assert(false);
	return w;
	//string s;
	//stringstream oss(s);
	//while (c != ' ' && c != '\n' && c != '\"' && c != '(' && c != ')' && c != EOF) {
	//	//oss.put(c);
	//	oss << (char)c;

	//	c = m_is.get();

	//}
	//m_is.unget();
	//w.type = "sym";
	//w.content = oss.str();
	//return w;
}
