#include "std.h"
#include <gtest/gtest.h>
#include "finelib.h"

TEST(built_in_functions_test, lambda)
{
	// (lambda (x y) (+ x y)) => (lambda (x y) (+ x y))
	EXPECT_EQ(eval("(lambda (x y) (+ x y))")->printed_rep(), "(lambda (x y) (+ x y))");

	// ((lambda (x) (if (> x 3) 'a 'b)) 2) => b
	EXPECT_EQ(eval("((lambda (x) (if (> x 3) 'a 'b)) 2)")->printed_rep(), "b");

	// (defun foo (x y) (+ x y)) => foo
	eval("(defun foo (x y) (+ x y))");
	EXPECT_EQ(static_pointer_cast<Func>(get_current_env()->value_of(make_sym("foo")))->lambda()->printed_rep(),
		"(lambda (x y) (+ x y))");

	// (foo 2 8) => 10
	EXPECT_EQ(eval("(foo 2 8)")->printed_rep(), "10");
}
