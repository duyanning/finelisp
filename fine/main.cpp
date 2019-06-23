#include "std.h"
#include "finelib.h"

void show_usage()
{
	cout << "fine a.fine" << endl;
}


int main(int argc, char* argv[])
try {
#ifdef _MSC_VER
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	init_finelib();

	if (argc != 2) {
		show_usage();
		return 0;
	}

	Parser parser(argv[1]);
	parser.read_eval();
}
catch (Err& err) {
	cout << "====== backtrace above ======" << endl;
	cout << err.msg() << endl;
}
