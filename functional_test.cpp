#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "functional_stl.h"

//本类专门测试stl::function类

#define nullptr NULL

#define CC_CALLBACK_0_TEST(__selector__,__target__, ...) stl::bind(&__selector__,__target__, ##__VA_ARGS__)
#define CC_CALLBACK_1_TEST(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,##__VA_ARGS__)
#define CC_CALLBACK_2_TEST(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,stl::placeholders::_2,##__VA_ARGS__)
#define CC_CALLBACK_3_TEST(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,stl::placeholders::_2,stl::placeholders::_3,##__VA_ARGS__)

class TestClass
{
public:
	TestClass():callTested(false){}
	void test()
	{
		callTested = true;
	}
	int resturnInt()
	{
		return 1;
	}
	int returnParam(int a)
	{
		return a;
	}
	char returnChar(char a)
	{
		return a;
	}
	int add2(int a,int b)
	{
		return a+b;
	}
	int add3(int a,int b,int c)
	{
		return a+b+c;
	}
	bool isCallTested() const { return callTested; }
	void setCallTested(bool val) { callTested = val; }

	int pointerTest_add(TestClass* pObj,int a,int b)
	{
		return pObj->add2(a,b);
	}
private:
	bool callTested;
};

TEST(Function, EmptyUse)
{
	TestClass testClass;
	{
		stl::function<void()> func;
		//默认是空的
		ASSERT_TRUE(func == NULL);
		func = CC_CALLBACK_0_TEST(TestClass::test,&testClass);
		ASSERT_TRUE(func != NULL);

		//调用了TestClass::test后isCallTested将返回真,还没调用之前是返回假的
		ASSERT_FALSE(testClass.isCallTested())<<"muse be the TestClass error!";
		func();
		ASSERT_TRUE(testClass.isCallTested())<<"func didn't call TestClass::test actualy!";
		func = nullptr;
	}
	//任意类型都可以，包括自定义类型
	{
		stl::function<int(TestClass*,int,int)> func = CC_CALLBACK_3_TEST(TestClass::pointerTest_add,&testClass);
		ASSERT_EQ(1+2,func(&testClass,1,2));
	}
}

TEST(Function, BindParamTest)
{
	TestClass testClass;
	{
		//不绑定参数
		stl::function<int(int,int,int)> func0 = CC_CALLBACK_3_TEST(TestClass::add3,&testClass);
		ASSERT_EQ(1+2+3,func0(1,2,3));

		//绑定最后一个参数
		stl::function<int(int,int)> func1 = CC_CALLBACK_2_TEST(TestClass::add3,&testClass,3);
		ASSERT_EQ(1+2+3,func1(1,2));

		//绑定最后两个参数
		stl::function<int(int)> func2 = CC_CALLBACK_1_TEST(TestClass::add3,&testClass,2,3);
		ASSERT_EQ(1+2+3,func2(1));

		//绑定最后三个参数
		stl::function<int()> func3 = CC_CALLBACK_0_TEST(TestClass::add3,&testClass,1,2,3);
		ASSERT_EQ(1+2+3,func3());

		//测试常量引用
		const stl::function<int()>& func33 = func3;
		ASSERT_EQ(1+2+3,func33());
	}
	{
		//不绑定任何实参
		stl::function<int(int,int)> func = CC_CALLBACK_2_TEST(TestClass::add2,&testClass);
		ASSERT_EQ(1+2,func(1,2));

		//绑定最后两个参数
		stl::function<int(int)> func2 = CC_CALLBACK_1_TEST(TestClass::add2,&testClass,2);
		ASSERT_EQ(1+2,func2(1));

		//绑定最后一个参数
		stl::function<int()> func3 = CC_CALLBACK_0_TEST(TestClass::add2,&testClass,1,2);
		ASSERT_EQ(1+2,func3());
	}
	{
		//不绑定任何实参
		stl::function<int(int)> func = CC_CALLBACK_1_TEST(TestClass::returnParam,&testClass);
		ASSERT_EQ(1,func(1));

		//绑定最后一个参数
		stl::function<int()> func2 = CC_CALLBACK_0_TEST(TestClass::returnParam,&testClass,1);
		ASSERT_EQ(1,func2());
	}
	{
		//绑定最后一个参数
		stl::function<int()> func = CC_CALLBACK_0_TEST(TestClass::resturnInt,&testClass);
		ASSERT_EQ(1,func());
	}
	{
		//任意类型都可以，包括自定义类型
		stl::function<int(TestClass*)> func2 = CC_CALLBACK_1_TEST(TestClass::pointerTest_add,&testClass,1,2);
		ASSERT_EQ(1+2,func2(&testClass));
	}
}

//测试绑定全局函数的实参
void g_voidMethod()
{
}
int g_return1()
{
	return 1;
}
int g_add1(int a)
{
	return a;
}
int g_add2(int a,int b)
{
	return a+b;
}
int g_add3(int a,int b,int c)
{
	return a+b+c;
}
TEST(Function, GlobalMethodTest)
{
	{
		//不绑定参数
		stl::function<int(int,int,int)> func0 = stl::bind(g_add3,stl::placeholders::_1,stl::placeholders::_2,stl::placeholders::_3);
		ASSERT_EQ(1+2+3,func0(1,2,3));

		//绑定最后一个参数
		stl::function<int(int,int)> func1 = stl::bind(g_add3,stl::placeholders::_1,stl::placeholders::_2,3);
		ASSERT_EQ(1+2+3,func1(1,2));

		//绑定最后两个参数
		stl::function<int(int)> func2 = stl::bind(g_add3,stl::placeholders::_1,2,3);
		ASSERT_EQ(1+2+3,func2(1));

		//绑定最后三个参数
		stl::function<int()> func3 = stl::bind(g_add3,1,2,3);
		ASSERT_EQ(1+2+3,func3());

		//测试常量引用
		const stl::function<int()>& func33 = func3;
		ASSERT_EQ(1+2+3,func33());
	}
	{
		//不绑定参数
		stl::function<int(int,int)> func0 = stl::bind(g_add2,stl::placeholders::_1,stl::placeholders::_2);
		ASSERT_EQ(1+2,func0(1,2));

		//绑定最后一个参数
		stl::function<int(int)> func1 = stl::bind(g_add2,stl::placeholders::_1,2);
		ASSERT_EQ(1+2,func1(1));

		//绑定最后两个参数
		stl::function<int()> func2 = stl::bind(g_add2,1,2);
		ASSERT_EQ(1+2,func2());
	}
	{
		//不绑定参数
		stl::function<int(int)> func0 = stl::bind(g_add1,stl::placeholders::_1);
		ASSERT_EQ(1,func0(1));

		//绑定最后一个参数
		stl::function<int()> func1 = stl::bind(g_add1,1);
		ASSERT_EQ(1,func1());
	}
	{
		stl::function<int()> func1 = stl::bind(g_return1);
		ASSERT_EQ(1,func1());
	}
}

class ReturnCharTest : public::testing::TestWithParam<char>{};
INSTANTIATE_TEST_CASE_P(Function, ReturnCharTest, testing::Values('a','b','\0','c',' '));
//任意类型都可以，包括自定义类型
TEST_P(ReturnCharTest, CheckCharReturn)
{
	char n =  GetParam();
	TestClass testClass;
	{
		stl::function<char(char)> func = CC_CALLBACK_1_TEST(TestClass::returnChar,&testClass);
		ASSERT_EQ(n,func(n));
	}
}

//测试传入指针参数是否自动删除


//测试直接把多参数的function转成少参数的function
TEST(Function, FunctionBindTest)
{
	TestClass testClass;
	{
		stl::function<int(int)> func1(&TestClass::returnParam,&testClass);
		stl::function<int()> func0 = stl::bind(func1,1);
		ASSERT_EQ(1,func0());
	}
}