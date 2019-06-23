#include "std.h"
#include <gtest/gtest.h>
#include "finelib.h"

// fine --gtest_filter=FooTest.*-FooTest.Bar 运行所有“测试案例名称(testcase_name)”为FooTest的案例，但是除了FooTest.Bar这个案例

TEST(List_test, add)
{
	// ()
    EXPECT_EQ(eval("()")->printed_rep(), "nil");

	// (1 2)
    EXPECT_EQ(eval("'(1 2)")->printed_rep(), "(1 2)");

	// (a 'foo "b" 7)
    EXPECT_EQ(eval("'(a 'foo \"b\" 7)")->printed_rep(), "(a (quote foo) \"b\" 7)");

	// (1 a '(1 bar) "b" 7)
	EXPECT_EQ(eval("'(1 a '(1 bar) \"b\" 7)")->printed_rep(), "(1 a (quote (1 bar)) \"b\" 7)");
}

TEST(ListTest, car_and_cdr)
{
	// (car '()) => nil
	EXPECT_EQ(eval("(car '())")->printed_rep(), "nil");
	// (cdr '()) => nil
	EXPECT_EQ(eval("(cdr '())")->printed_rep(), "nil");

	// (car '(1)) => 1
	EXPECT_EQ(eval("(car '(1))")->printed_rep(), "1");
	//// (cdr '(1)) => nil
	EXPECT_EQ(eval("(cdr '(1))")->printed_rep(), "nil");

	// (cons 6 9) => (6 9)
	EXPECT_EQ(eval("(cons 6 9)")->printed_rep(), "(6 . 9)");

	// (cons '(2 5) '(6 9)) => ((2 5) 6 9)
	EXPECT_EQ(eval("(cons '(2 5) '(6 9))")->printed_rep(), "((2 5) 6 9)");
}

//TEST(ListTest, nil)
//{
//	EXPECT_FALSE(make_int(3)->is_nil());
//	EXPECT_FALSE(make_list()->add(3)->is_nil());
//	EXPECT_FALSE(make_list()->add_str("ok")->is_nil());
//	EXPECT_FALSE(make_list()->add(make_list())->is_nil());
//	EXPECT_TRUE(make_list()->is_nil());
//}
//
// 与上面测试C++代码的功能不同，下面是测试的lisp代码的功能，体现对eval的调用上。
TEST(built_in_functions_test, plus)
{
	EXPECT_EQ(eval("(+ 1 2)")->printed_rep(), "3");
}

TEST(built_in_functions_test, oneplus)
{
	// (1+ 2) => 3
	EXPECT_EQ(eval("(1+ 2)")->printed_rep(), "3");
}

TEST(built_in_functions_test, greaterthan)
{
	EXPECT_EQ(eval("(> 1 2)")->printed_rep(), "nil");
	EXPECT_EQ(eval("(> 2 1)")->printed_rep(), "t");
}

TEST(built_in_functions_test, prin1)
{
	// (prin1 "a") => "a"
	EXPECT_EQ(eval("(prin1 \"a\")")->printed_rep(), "\"a\"");
}

TEST(built_in_functions_test, cdr)
{
	// (cdr '(1 2 3)) => (2 3)
	EXPECT_EQ(eval("(cdr '(1 2 3))")->printed_rep(), "(2 3)");

	// (cdr '(1 2 3) 4) error
	EXPECT_ANY_THROW(eval("(cdr '(1 2 3) 4)"));

	// (cdr 9) error
	EXPECT_ANY_THROW(eval("(cdr 9)"));

}

TEST(built_in_functions_test, car)
{
	// (car '(1 2 3)) => 1
	EXPECT_EQ(eval("(car '(1 2 3))")->printed_rep(), "1");

	// (car '(1 2 3) 4) error
	EXPECT_ANY_THROW(eval("(car '(1 2 3) 4)"));

	// (car 1) error
	EXPECT_ANY_THROW(eval("(car 1)"));

}

TEST(built_in_functions_test, set)
{
	// (set 'x 2) => 2
	EXPECT_EQ(eval("(set 'x 2)")->printed_rep(), "2");

	// (set 'y 3) => 3
	EXPECT_EQ(eval("(set 'y 3)")->printed_rep(), "3");

	// (+ x y) => 5
	EXPECT_EQ(eval("(+ x y)")->printed_rep(), "5");
}

TEST(special_forms_test, if_)
{
	// (if 2 'a 'b) => a
	EXPECT_EQ(eval("(if 2 'a 'b)")->printed_rep(), "a");

	// (if '() 'a 'b) => b
	EXPECT_EQ(eval("(if '() 'a 'b)")->printed_rep(), "b");

	// (if '() 'a 'b 'c) => c
	EXPECT_EQ(eval("(if '() 'a 'b 'c)")->printed_rep(), "c");
}

TEST(built_in_functions_test, defmacro)
{
	// (defmacro inc (var) (list 'setq var (list '1+ var)))
	// (setq xx 1)
	// (inc xx) => 2
	EXPECT_EQ(eval(
		"(defmacro inc (var) (list 'setq var (list '1+ var)))\n"
		"(setq xx 1)\n"
		"(inc xx)"
		)->printed_rep(), "2");
}


TEST(built_in_functions_test, listp)
{
	// (listp '(1 2)) => t
	EXPECT_EQ(eval("(listp '(1 2))")->printed_rep(), "t");

	// (listp '()) => t
	EXPECT_EQ(eval("(listp '())")->printed_rep(), "t");

	// (listp 2) => nil
	EXPECT_EQ(eval("(listp 2)")->printed_rep(), "nil");
}

TEST(built_in_functions_test, consp)
{
	// (consp '(1 2)) => t
	EXPECT_EQ(eval("(consp '(1 2))")->printed_rep(), "t");

	// (consp '()) => nil
	EXPECT_EQ(eval("(consp '())")->printed_rep(), "nil");

	// (consp 2) => nil
	EXPECT_EQ(eval("(consp 2)")->printed_rep(), "nil");
}

TEST(built_in_functions_test, symbolp)
{
	// (symbolp t) => t
	// (symbolp nil) => t
	// (symbolp 1) => nil
	EXPECT_EQ(eval("(symbolp 1)")->printed_rep(), "nil");
	// (symbolp '()) => t
	// (symbolp ()) => t
	// (symbolp '(1 2)) => nil
}

TEST(built_in_functions_test, numberp)
{
	// (numberp 2) => t
	EXPECT_EQ(eval("(numberp 2)")->printed_rep(), "t");

	// (numberp '(1 2)) => nil
	EXPECT_EQ(eval("(numberp '(1 2))")->printed_rep(), "nil");
}

TEST(built_in_functions_test, list)
{
	// (list 'a (if (> 2 1) 'b 'a)) => (a b)
	EXPECT_EQ(eval("(list 'a (if (> 2 1) 'b 'a))")->printed_rep(), "(a b)");
}

TEST(const_test, t)
{
	// t => t
	EXPECT_EQ(eval("t")->printed_rep(), "t");
}

int main(int argc, char* argv[])
{
	//_CrtSetDbgFlag (_CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF);

	testing::InitGoogleTest(&argc, argv);
	init_finelib();
	return RUN_ALL_TESTS();
}
