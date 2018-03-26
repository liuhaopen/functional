#include <stdlib.h>
#include <stdio.h>
#include <gtest/gtest.h>
#include "functional_stl.h"

//����ר�Ų���stl::function��

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
		//Ĭ���ǿյ�
		ASSERT_TRUE(func == NULL);
		func = CC_CALLBACK_0_TEST(TestClass::test,&testClass);
		ASSERT_TRUE(func != NULL);

		//������TestClass::test��isCallTested��������,��û����֮ǰ�Ƿ��ؼٵ�
		ASSERT_FALSE(testClass.isCallTested())<<"muse be the TestClass error!";
		func();
		ASSERT_TRUE(testClass.isCallTested())<<"func didn't call TestClass::test actualy!";
		func = nullptr;
	}
	//�������Ͷ����ԣ������Զ�������
	{
		stl::function<int(TestClass*,int,int)> func = CC_CALLBACK_3_TEST(TestClass::pointerTest_add,&testClass);
		ASSERT_EQ(1+2,func(&testClass,1,2));
	}
}

TEST(Function, BindParamTest)
{
	TestClass testClass;
	{
		//���󶨲���
		stl::function<int(int,int,int)> func0 = CC_CALLBACK_3_TEST(TestClass::add3,&testClass);
		ASSERT_EQ(1+2+3,func0(1,2,3));

		//�����һ������
		stl::function<int(int,int)> func1 = CC_CALLBACK_2_TEST(TestClass::add3,&testClass,3);
		ASSERT_EQ(1+2+3,func1(1,2));

		//�������������
		stl::function<int(int)> func2 = CC_CALLBACK_1_TEST(TestClass::add3,&testClass,2,3);
		ASSERT_EQ(1+2+3,func2(1));

		//�������������
		stl::function<int()> func3 = CC_CALLBACK_0_TEST(TestClass::add3,&testClass,1,2,3);
		ASSERT_EQ(1+2+3,func3());

		//���Գ�������
		const stl::function<int()>& func33 = func3;
		ASSERT_EQ(1+2+3,func33());
	}
	{
		//�����κ�ʵ��
		stl::function<int(int,int)> func = CC_CALLBACK_2_TEST(TestClass::add2,&testClass);
		ASSERT_EQ(1+2,func(1,2));

		//�������������
		stl::function<int(int)> func2 = CC_CALLBACK_1_TEST(TestClass::add2,&testClass,2);
		ASSERT_EQ(1+2,func2(1));

		//�����һ������
		stl::function<int()> func3 = CC_CALLBACK_0_TEST(TestClass::add2,&testClass,1,2);
		ASSERT_EQ(1+2,func3());
	}
	{
		//�����κ�ʵ��
		stl::function<int(int)> func = CC_CALLBACK_1_TEST(TestClass::returnParam,&testClass);
		ASSERT_EQ(1,func(1));

		//�����һ������
		stl::function<int()> func2 = CC_CALLBACK_0_TEST(TestClass::returnParam,&testClass,1);
		ASSERT_EQ(1,func2());
	}
	{
		//�����һ������
		stl::function<int()> func = CC_CALLBACK_0_TEST(TestClass::resturnInt,&testClass);
		ASSERT_EQ(1,func());
	}
	{
		//�������Ͷ����ԣ������Զ�������
		stl::function<int(TestClass*)> func2 = CC_CALLBACK_1_TEST(TestClass::pointerTest_add,&testClass,1,2);
		ASSERT_EQ(1+2,func2(&testClass));
	}
}

//���԰�ȫ�ֺ�����ʵ��
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
		//���󶨲���
		stl::function<int(int,int,int)> func0 = stl::bind(g_add3,stl::placeholders::_1,stl::placeholders::_2,stl::placeholders::_3);
		ASSERT_EQ(1+2+3,func0(1,2,3));

		//�����һ������
		stl::function<int(int,int)> func1 = stl::bind(g_add3,stl::placeholders::_1,stl::placeholders::_2,3);
		ASSERT_EQ(1+2+3,func1(1,2));

		//�������������
		stl::function<int(int)> func2 = stl::bind(g_add3,stl::placeholders::_1,2,3);
		ASSERT_EQ(1+2+3,func2(1));

		//�������������
		stl::function<int()> func3 = stl::bind(g_add3,1,2,3);
		ASSERT_EQ(1+2+3,func3());

		//���Գ�������
		const stl::function<int()>& func33 = func3;
		ASSERT_EQ(1+2+3,func33());
	}
	{
		//���󶨲���
		stl::function<int(int,int)> func0 = stl::bind(g_add2,stl::placeholders::_1,stl::placeholders::_2);
		ASSERT_EQ(1+2,func0(1,2));

		//�����һ������
		stl::function<int(int)> func1 = stl::bind(g_add2,stl::placeholders::_1,2);
		ASSERT_EQ(1+2,func1(1));

		//�������������
		stl::function<int()> func2 = stl::bind(g_add2,1,2);
		ASSERT_EQ(1+2,func2());
	}
	{
		//���󶨲���
		stl::function<int(int)> func0 = stl::bind(g_add1,stl::placeholders::_1);
		ASSERT_EQ(1,func0(1));

		//�����һ������
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
//�������Ͷ����ԣ������Զ�������
TEST_P(ReturnCharTest, CheckCharReturn)
{
	char n =  GetParam();
	TestClass testClass;
	{
		stl::function<char(char)> func = CC_CALLBACK_1_TEST(TestClass::returnChar,&testClass);
		ASSERT_EQ(n,func(n));
	}
}

//���Դ���ָ������Ƿ��Զ�ɾ��


//����ֱ�ӰѶ������functionת���ٲ�����function
TEST(Function, FunctionBindTest)
{
	TestClass testClass;
	{
		stl::function<int(int)> func1(&TestClass::returnParam,&testClass);
		stl::function<int()> func0 = stl::bind(func1,1);
		ASSERT_EQ(1,func0());
	}
}