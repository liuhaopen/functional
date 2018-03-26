#ifndef __FUNCTIONAL_STL_H__
#define __FUNCTIONAL_STL_H__

#include <string>
#include <list>
#include <stdio.h>
#include "TypeTraits_Cat.h"
#pragma warning(disable: 4100 4180 4244 4521 4522)

namespace stl
{
	class NullType;

#pragma region SlotFunctorBase��ʵ��
	template<typename ReturnType>
	class SlotFunctorBase
	{
	public:
		virtual ~SlotFunctorBase() {};
		virtual ReturnType runMethod()const = 0;
		//virtual ReturnType runMethod(){return ReturnType();}
		virtual SlotFunctorBase<ReturnType>* copy() = 0;
		virtual void setParam1(Cat::Type::TypeHolder* m_pArge1)const{}
		virtual void setParam2(Cat::Type::TypeHolder* m_pArge1)const{}
		virtual void setParam3(Cat::Type::TypeHolder* m_pArge1)const{}
	};
#pragma endregion SlotFunctorBase��ʵ��

#pragma region MemberFunctionSlot��Ա������֧��
	//֧��3�������İ汾
	template<typename T,typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	class MemberFunctionSlot : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef ReturnType(T::*MemberFunctionType)(ArgsType1,ArgsType2,ArgsType3);
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;
		typedef Cat::Type::Holder<ArgsType2,false> ArgeType2Holder;
		typedef Cat::Type::Holder<ArgsType3,false> ArgeType3Holder;

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj),m_pArge1(NULL),m_pArge2(NULL),m_pArge3(NULL)
		{}
		virtual void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		virtual void setParam2(Cat::Type::TypeHolder* arge2) const
		{
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			m_pArge2 = arge2->Clone();
			m_pArge2->SetDeletePtr(false);
		}
		virtual void setParam3(Cat::Type::TypeHolder* arge3) const
		{
			if (m_pArge3 != NULL)
			{
				delete m_pArge3;
				m_pArge3 = NULL;
			}
			m_pArge3 = arge3->Clone();
			m_pArge3->SetDeletePtr(false);
		}
		MemberFunctionSlot(MemberFunctionType func, T* obj,ArgsType1 arge1,ArgsType2 arge2,ArgsType3 arge3) :
			d_function(func),
			d_object(obj)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);

			m_pArge2 = new ArgeType2Holder(arge2);
			m_pArge2->SetDeletePtr(false);

			m_pArge3 = new ArgeType3Holder(arge3);
			m_pArge3->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			ArgeType2Holder* holder2 = static_cast<ArgeType2Holder*>(m_pArge2);
			ArgeType3Holder* holder3 = static_cast<ArgeType3Holder*>(m_pArge3);
			return (d_object->*d_function)(holder->GetValue(),holder2->GetValue(),holder3->GetValue());
		}

		virtual SlotFunctorBase<ReturnType>* copy()
		{
			MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,ArgsType3>* newCopy = new MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,ArgsType3>(this->d_function,this->d_object);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			if (m_pArge2 != NULL)
				newCopy->m_pArge2 = m_pArge2->Clone();
			if (m_pArge3 != NULL)
				newCopy->m_pArge3 = m_pArge3->Clone();
			return newCopy;
		}
		~MemberFunctionSlot()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			if (m_pArge3 != NULL)
			{
				delete m_pArge3;
				m_pArge3 = NULL;
			}
		}
	private:
		MemberFunctionType d_function;
		T* d_object;
		mutable Cat::Type::TypeHolder* m_pArge1;
		mutable Cat::Type::TypeHolder* m_pArge2;
		mutable Cat::Type::TypeHolder* m_pArge3;
	};
	template<typename T,typename ReturnType,typename ArgsType1,typename ArgsType2>
	class MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef ReturnType(T::*MemberFunctionType)(ArgsType1,ArgsType2);
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;
		typedef Cat::Type::Holder<ArgsType2,false> ArgeType2Holder;

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj),m_pArge1(NULL),m_pArge2(NULL)
		{}
		virtual void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		virtual void setParam2(Cat::Type::TypeHolder* arge2) const
		{
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			m_pArge2 = arge2->Clone();
			m_pArge2->SetDeletePtr(false);
		}
		MemberFunctionSlot(MemberFunctionType func, T* obj,ArgsType1 arge1,ArgsType2 arge2) :
			d_function(func),
			d_object(obj)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);

			m_pArge2 = new ArgeType2Holder(arge2);
			m_pArge2->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			ArgeType2Holder* holder2 = static_cast<ArgeType2Holder*>(m_pArge2);
			return (d_object->*d_function)(holder->GetValue(),holder2->GetValue());
		}

		virtual SlotFunctorBase<ReturnType>* copy()
		{
			MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>* newCopy = new MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>(this->d_function,this->d_object);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			if (m_pArge2 != NULL)
				newCopy->m_pArge2 = m_pArge2->Clone();
			return newCopy;
		}
		~MemberFunctionSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
		}
	private:
		MemberFunctionType d_function;
		T* d_object;
		mutable Cat::Type::TypeHolder* m_pArge1;
		mutable Cat::Type::TypeHolder* m_pArge2;
	};
	template<typename T,typename ReturnType,typename ArgsType1>
	class MemberFunctionSlot<T,ReturnType,ArgsType1,NullType,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef ReturnType(T::*MemberFunctionType)(ArgsType1);
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj),m_pArge1(NULL)
		{}
		void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		MemberFunctionSlot(MemberFunctionType func, T* obj,ArgsType1 arge1) :
			d_function(func),
			d_object(obj)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			return (d_object->*d_function)(holder->GetValue());
		}

		virtual SlotFunctorBase<ReturnType>* copy()
		{
			MemberFunctionSlot<T,ReturnType,ArgsType1,NullType,NullType>* newCopy = new MemberFunctionSlot<T,ReturnType,ArgsType1,NullType,NullType>(this->d_function,this->d_object);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			return newCopy;
		}
		~MemberFunctionSlot<T,ReturnType,ArgsType1,NullType,NullType>()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
		}
	private:
		MemberFunctionType d_function;
		T* d_object;
		mutable Cat::Type::TypeHolder* m_pArge1;
	};
	template<typename T,typename ReturnType>
	class MemberFunctionSlot<T,ReturnType,NullType,NullType,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef ReturnType(T::*MemberFunctionType)();

		MemberFunctionSlot(MemberFunctionType func, T* obj) :
			d_function(func),
			d_object(obj)
		{}
		virtual ReturnType runMethod() const
		{
			return (d_object->*d_function)();
		}
		virtual SlotFunctorBase<ReturnType>* copy()
		{
			MemberFunctionSlot<T,ReturnType,NullType,NullType,NullType>* newCopy = new MemberFunctionSlot<T,ReturnType,NullType,NullType,NullType>(this->d_function,this->d_object);
			return newCopy;
		}
	private:
		MemberFunctionType d_function;
		T* d_object;
	};

#pragma endregion MemberFunctionSlot��Ա������֧��

#pragma region FunctorPointerSlotȫ�ֺ�����֧��
	//֧��3�������İ汾
	template<typename T,typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	class FunctorPointerSlot : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;
		typedef Cat::Type::Holder<ArgsType2,false> ArgeType2Holder;
		typedef Cat::Type::Holder<ArgsType3,false> ArgeType3Holder;

		FunctorPointerSlot(T* functor) :
			d_functor(functor),m_pArge1(NULL),m_pArge2(NULL),m_pArge3(NULL)
		{}
		FunctorPointerSlot(T* functor,ArgsType1 arge1,ArgsType2 arge2,ArgsType3 arge3)
			:d_functor(functor)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);

			m_pArge2 = new ArgeType2Holder(arge2);
			m_pArge2->SetDeletePtr(false);

			m_pArge3 = new ArgeType3Holder(arge3);
			m_pArge3->SetDeletePtr(false);
		}
		virtual void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		virtual void setParam2(Cat::Type::TypeHolder* arge2) const
		{
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			m_pArge2 = arge2->Clone();
			m_pArge2->SetDeletePtr(false);
		}
		virtual void setParam3(Cat::Type::TypeHolder* arge3) const
		{
			if (m_pArge3 != NULL)
			{
				delete m_pArge3;
				m_pArge3 = NULL;
			}
			m_pArge3 = arge3->Clone();
			m_pArge3->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			ArgeType2Holder* holder2 = static_cast<ArgeType2Holder*>(m_pArge2);
			ArgeType3Holder* holder3 = static_cast<ArgeType3Holder*>(m_pArge3);
			return (*d_functor)(holder->GetValue(),holder2->GetValue(),holder3->GetValue());
		}
		virtual SlotFunctorBase<ReturnType>* copy()
		{
			FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,ArgsType3>* newCopy = new FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,ArgsType3>(this->d_functor);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			if (m_pArge2 != NULL)
				newCopy->m_pArge2 = m_pArge2->Clone();
			if (m_pArge3 != NULL)
				newCopy->m_pArge3 = m_pArge3->Clone();
			return newCopy;
		}
		~FunctorPointerSlot()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			if (m_pArge3 != NULL)
			{
				delete m_pArge3;
				m_pArge3 = NULL;
			}
		}
	private:
		T* d_functor;
		mutable Cat::Type::TypeHolder* m_pArge1;
		mutable Cat::Type::TypeHolder* m_pArge2;
		mutable Cat::Type::TypeHolder* m_pArge3;
	};
	template<typename T,typename ReturnType,typename ArgsType1,typename ArgsType2>
	class FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;
		typedef Cat::Type::Holder<ArgsType2,false> ArgeType2Holder;

		FunctorPointerSlot(T* functor) :
			d_functor(functor),m_pArge1(NULL),m_pArge2(NULL)
		{}
		FunctorPointerSlot(T* functor,ArgsType1 arge1,ArgsType2 arge2)
			:d_functor(functor)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);

			m_pArge2 = new ArgeType2Holder(arge2);
			m_pArge2->SetDeletePtr(false);
		}
		virtual void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		virtual void setParam2(Cat::Type::TypeHolder* arge2) const
		{
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
			m_pArge2 = arge2->Clone();
			m_pArge2->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			ArgeType2Holder* holder2 = static_cast<ArgeType2Holder*>(m_pArge2);
			return (*d_functor)(holder->GetValue(),holder2->GetValue());
		}
		virtual SlotFunctorBase<ReturnType>* copy()
		{
			FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>* newCopy = new FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>(this->d_functor);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			if (m_pArge2 != NULL)
				newCopy->m_pArge2 = m_pArge2->Clone();
			return newCopy;
		}
		~FunctorPointerSlot()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			if (m_pArge2 != NULL)
			{
				delete m_pArge2;
				m_pArge2 = NULL;
			}
		}
	private:
		T* d_functor;
		mutable Cat::Type::TypeHolder* m_pArge1;
		mutable Cat::Type::TypeHolder* m_pArge2;
	};
	template<typename T,typename ReturnType,typename ArgsType1>
	class FunctorPointerSlot<T,ReturnType,ArgsType1,NullType,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		typedef Cat::Type::Holder<ArgsType1,false> ArgeType1Holder;

		FunctorPointerSlot(T* functor) :
			d_functor(functor),m_pArge1(NULL)
		{}
		FunctorPointerSlot(T* functor,ArgsType1 arge1)
			:d_functor(functor)
		{
			m_pArge1 = new ArgeType1Holder(arge1);
			m_pArge1->SetDeletePtr(false);
		}
		virtual void setParam1(Cat::Type::TypeHolder* arge1) const
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
			m_pArge1 = arge1->Clone();
			m_pArge1->SetDeletePtr(false);
		}
		virtual ReturnType runMethod() const
		{
			ArgeType1Holder* holder = static_cast<ArgeType1Holder*>(m_pArge1);
			return (*d_functor)(holder->GetValue());
		}
		virtual SlotFunctorBase<ReturnType>* copy()
		{
			FunctorPointerSlot<T,ReturnType,ArgsType1,NullType,NullType>* newCopy = new FunctorPointerSlot<T,ReturnType,ArgsType1,NullType,NullType>(this->d_functor);
			if (m_pArge1 != NULL)
				newCopy->m_pArge1 = m_pArge1->Clone();
			return newCopy;
		}
		~FunctorPointerSlot()
		{
			if (m_pArge1 != NULL)
			{
				delete m_pArge1;
				m_pArge1 = NULL;
			}
		}
	private:
		T* d_functor;
		mutable Cat::Type::TypeHolder* m_pArge1;
	};
	template<typename T,typename ReturnType>
	class FunctorPointerSlot<T,ReturnType,NullType,NullType,NullType> : public SlotFunctorBase<ReturnType>
	{
	public:
		FunctorPointerSlot(T* functor) :
			d_functor(functor)
		{}

		virtual ReturnType runMethod() const
		{
			return (*d_functor)();
		}
		virtual SlotFunctorBase<ReturnType>* copy()
		{
			FunctorPointerSlot<T,ReturnType,NullType,NullType,NullType>* newCopy = new FunctorPointerSlot<T,ReturnType,NullType,NullType,NullType>(this->d_functor);
			return newCopy;
		}

	private:
		T* d_functor;
	};
#pragma endregion FunctorPointerSlotȫ�ֺ�����֧��

#pragma region Function ,��std::function

	template <typename ReturnType>
	class function;

	//ֻ������������
	template<typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	class function < ReturnType (ArgsType1,ArgsType2,ArgsType3) >
	{
	public:
		function():d_functor_impl(NULL){}

		template <typename T>
		function(const T* func)
			:d_functor_impl(new FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,ArgsType3>(func))
		{
		}

		template <typename T>
		function(ReturnType (T::*pMemFun)(ArgsType1,ArgsType2,ArgsType3),T *pObj)
			: d_functor_impl(new MemberFunctionSlot<T,ReturnType, ArgsType1,ArgsType2,ArgsType3>(pMemFun,pObj))
		{
		}
		function(SlotFunctorBase<ReturnType>& functor)
		{
			d_functor_impl = functor.copy();
		}
		ReturnType operator()(ArgsType1 a1,ArgsType2 a2,ArgsType3 a3) const
		{
			if (!connected())
			{
				printf("Cat_Error : function::()() Had Not Connected!\n");
			}
			d_functor_impl->setParam1(&Cat::Type::Holder<ArgsType1,false>(a1));
			d_functor_impl->setParam2(&Cat::Type::Holder<ArgsType2,false>(a2));
			d_functor_impl->setParam3(&Cat::Type::Holder<ArgsType3,false>(a3));
			return (*d_functor_impl).runMethod();

		}
		operator bool() const 
		{ 
			return connected();
		}
		~function()
		{
			cleanup();
		}
		//���ظ��ƹ��캯��
		function(const function& other)
		{
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			else
			{
				this->d_functor_impl = NULL;
			}
		}
		//���ظ�ֵ��
		function& operator=(const function &other)
		{
			cleanup();
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			return *this;
		}
		function& operator=(const function *other)
		{
			cleanup();
			if (other != NULL && other->d_functor_impl != NULL)
			{
				this->d_functor_impl = other->d_functor_impl->copy();
			}
			return *this;
		}
		function(function* func):d_functor_impl(NULL)
		{
			if (func != NULL)
			{
				this->d_functor_impl = func->d_functor_impl->copy();
			}
		}
		SlotFunctorBase<ReturnType>* getFunctor() const { return d_functor_impl; }
	protected:
		//���س�Ա�Ƿ���Ч���Ƿ��Ѿ����ӵ�һ�������Functorʵ��
		bool connected() const
		{
			return d_functor_impl != NULL;
		}
		//���Functor��ʵ��
		void cleanup()
		{
			if (d_functor_impl)
			{
				delete d_functor_impl;
				d_functor_impl = NULL;
			}
		}
	private:
		SlotFunctorBase<ReturnType>* d_functor_impl;
	};

	//ֻ������������
	template<typename ReturnType,typename ArgsType1,typename ArgsType2>
	class function < ReturnType (ArgsType1,ArgsType2) >
	{
	public:
		function():d_functor_impl(NULL){}

		template <typename T>
		function(const T* func)
			:d_functor_impl(new FunctorPointerSlot<T,ReturnType,ArgsType1,ArgsType2,NullType>(func))
		{
		}

		template <typename T>
		function(ReturnType (T::*pMemFun)(ArgsType1,ArgsType2),T *pObj)
			: d_functor_impl(new MemberFunctionSlot<T,ReturnType, ArgsType1,ArgsType2,NullType>(pMemFun,pObj))
		{
		}
		function(SlotFunctorBase<ReturnType>& functor)
		{
			d_functor_impl = functor.copy();
		}
		ReturnType operator()(ArgsType1 a1,ArgsType2 a2) const
		{
			if (!connected())
			{
				printf("Cat_Error : function::()() Had Not Connected!\n");
			}
			d_functor_impl->setParam1(&Cat::Type::Holder<ArgsType1,false>(a1));
			d_functor_impl->setParam2(&Cat::Type::Holder<ArgsType2,false>(a2));
			return (*d_functor_impl).runMethod();
		}
		operator bool() const 
		{ 
			return connected();
		}
		~function()
		{
			cleanup();
		}
		//���ظ��ƹ��캯��
		function(const function& other)
		{
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			else
			{
				this->d_functor_impl = NULL;
			}
		}
		//���ظ�ֵ��
		function& operator=(const function &other)
		{
			cleanup();
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			return *this;
		}
		function& operator=(const function *other)
		{
			cleanup();
			if (other != NULL && other->d_functor_impl != NULL)
			{
				this->d_functor_impl = other->d_functor_impl->copy();
			}
			return *this;
		}
		function(function* func):d_functor_impl(NULL)
		{
			if (func != NULL)
			{
				this->d_functor_impl = func->d_functor_impl->copy();
			}
		}
		SlotFunctorBase<ReturnType>* getFunctor() const { return d_functor_impl; }
	protected:
		//���س�Ա�Ƿ���Ч���Ƿ��Ѿ����ӵ�һ�������Functorʵ��
		bool connected() const
		{
			return d_functor_impl != NULL;
		}
		//���Functor��ʵ��
		void cleanup()
		{
			if (d_functor_impl)
			{
				delete d_functor_impl;
				d_functor_impl = NULL;
			}
		}
	private:
		SlotFunctorBase<ReturnType>* d_functor_impl;
	};

	//ֻ��һ��������
	template<typename ReturnType,typename ArgsType1>
	class function < ReturnType (ArgsType1) >
	{
	public:
		function():d_functor_impl(NULL){}

		template <typename T>
		function(const T* func)
			:d_functor_impl(new FunctorPointerSlot<T,ReturnType,ArgsType1,NullType,NullType>(func))
		{
		}

		template <typename T>
		function(ReturnType (T::*pMemFun)(ArgsType1),T *pObj)
			: d_functor_impl(new MemberFunctionSlot<T,ReturnType, ArgsType1,NullType,NullType>(pMemFun,pObj))
		{
		}
		function(SlotFunctorBase<ReturnType>& functor)
		{
			d_functor_impl = functor.copy();
		}
		ReturnType operator()(ArgsType1 a1) const
		{
			if (!connected())
			{
				printf("Cat_Error : function::()() Had Not Connected!\n");
				return (ReturnType)0;
			}
			d_functor_impl->setParam1(&Cat::Type::Holder<ArgsType1,false>(a1));
			return (*d_functor_impl).runMethod();
		}
		operator bool() const 
		{ 
			return connected();
		}
		~function()
		{
			cleanup();
		}
		//���ظ��ƹ��캯��
		function(const function& other)
		{
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			else
			{
				this->d_functor_impl = NULL;
			}
		}
		//���ظ�ֵ��
		function& operator=(const function &other)
		{
			cleanup();
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			return *this;
		}
		function& operator=(const function *other)
		{
			cleanup();
			if (other != NULL && other->d_functor_impl != NULL)
			{
				this->d_functor_impl = other->d_functor_impl->copy();
			}
			return *this;
		}
		function(function* func):d_functor_impl(NULL)
		{
			if (func != NULL)
			{
				this->d_functor_impl = func->d_functor_impl->copy();
			}
		}
		SlotFunctorBase<ReturnType>* getFunctor() const { return d_functor_impl; }
	protected:
		//���س�Ա�Ƿ���Ч���Ƿ��Ѿ����ӵ�һ�������Functorʵ��
		bool connected() const
		{
			return d_functor_impl != NULL;
		}
		//���Functor��ʵ��
		void cleanup()
		{
			if (d_functor_impl)
			{
				delete d_functor_impl;
				d_functor_impl = NULL;
			}
		}
	private:
		SlotFunctorBase<ReturnType>* d_functor_impl;
	};

	//����������
	template<typename ReturnType>
	class function < ReturnType () >
	{
	public:
		function():d_functor_impl(NULL){}

		template <typename T>
		function(const T* func)
			:d_functor_impl(new FunctorPointerSlot<T,ReturnType,NullType,NullType,NullType>(func))
		{
		}
		template <typename T>
		function(ReturnType (T::*pMemFun)(),T *pObj)
			: d_functor_impl(new MemberFunctionSlot<T,ReturnType, NullType,NullType,NullType>(pMemFun,pObj))
		{
		}
		function(SlotFunctorBase<ReturnType>& functor)
		{
			d_functor_impl = functor.copy();
		}
		ReturnType operator()() const
		{
			if (!connected())
			{
				printf("Cat_Error : function::()() Had Not Connected!\n");
			}
			return (*d_functor_impl).runMethod();
		}
		operator bool() const 
		{ 
			return connected();
		}
		~function()
		{
			cleanup();
		}
		//���ظ��ƹ��캯��
		function(const function& other)
		{
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			else
			{
				this->d_functor_impl = NULL;
			}
		}
		//���ظ�ֵ��
		function& operator=(const function &other)
		{
			cleanup();
			if (other.d_functor_impl != NULL)
			{
				this->d_functor_impl = other.d_functor_impl->copy();
			}
			return *this;
		}
		function& operator=(const function *other)
		{
			cleanup();
			if (other != NULL && other->d_functor_impl != NULL)
			{
				this->d_functor_impl = other->d_functor_impl->copy();
			}
			return *this;
		}
		function(function* func):d_functor_impl(NULL)
		{
			if (func != NULL)
			{
				this->d_functor_impl = func->d_functor_impl->copy();
			}
		}
		SlotFunctorBase<ReturnType>* getFunctor() const { return d_functor_impl; }
	protected:
		//���س�Ա�Ƿ���Ч���Ƿ��Ѿ����ӵ�һ�������Functorʵ��
		bool connected() const
		{
			return d_functor_impl != NULL;
		}
		//���Functor��ʵ��
		void cleanup()
		{
			if (d_functor_impl)
			{
				delete d_functor_impl;
				d_functor_impl = NULL;
			}
		}
	private:
		SlotFunctorBase<ReturnType>* d_functor_impl;
	};

	template<int _Nx>
	class _Ph
	{	// placeholder
	};
	namespace placeholders 
	{	// placeholders
		extern _Ph<1> _1;
		extern _Ph<2> _2;
		extern _Ph<3> _3;
	}
	//�����bind���������÷���STL����һ����
	//3�����ĺ�����
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1,ArgsType2,ArgsType3)> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2,ArgsType3),ClassType* obj,_Ph<1> placeholde,_Ph<2> placeholde2,_Ph<3> placeholde3)
	{
		return function<ReturnType(ArgsType1,ArgsType2,ArgsType3)>(memFunc,obj);
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1,ArgsType2)> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2,ArgsType3),ClassType* obj,_Ph<1> arge1,_Ph<2> arge2,ArgsType3 arge3)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc,obj);
		slot.setParam3(&Cat::Type::Holder<ArgsType3,false>(arge3));
		return slot;
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1)> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2,ArgsType3),ClassType* obj,_Ph<1> arge1,ArgsType2 arge2,ArgsType3 arge3)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc,obj);
		slot.setParam2(&Cat::Type::Holder<ArgsType2,false>(arge2));
		slot.setParam3(&Cat::Type::Holder<ArgsType3,false>(arge3));
		return slot;
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType()> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2,ArgsType3),ClassType* obj,ArgsType1 arge1,ArgsType2 arge2,ArgsType3 arge3)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc,obj,arge1,arge2,arge3);
		return slot;
	}
	//3������ȫ�ֺ�����
	template<typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1,ArgsType2,ArgsType3)> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2,ArgsType3),_Ph<1> placeholde,_Ph<2> placeholde2,_Ph<3> placeholde3)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2,ArgsType3),ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc);
		return slot;
	}
	template<typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1,ArgsType2)> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2,ArgsType3),_Ph<1> placeholde,_Ph<2> placeholde2,ArgsType3 arge3)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2,ArgsType3),ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc);
		slot.setParam3(&Cat::Type::Holder<ArgsType3,false>(arge3));
		return function<ReturnType(ArgsType1,ArgsType2)>(slot);
	}
	template<typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType(ArgsType1)> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2,ArgsType3),_Ph<1> placeholde,ArgsType2 arge2,ArgsType3 arge3)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2,ArgsType3),ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc);
		slot.setParam2(&Cat::Type::Holder<ArgsType2,false>(arge2));
		slot.setParam3(&Cat::Type::Holder<ArgsType3,false>(arge3));
		return function<ReturnType(ArgsType1)>(slot);
	}
	template<typename ReturnType,typename ArgsType1,typename ArgsType2,typename ArgsType3>
	function<ReturnType()> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2,ArgsType3),ArgsType1 arge1,ArgsType2 arge2,ArgsType3 arge3)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2,ArgsType3),ReturnType,ArgsType1,ArgsType2,ArgsType3> slot(memFunc,arge1,arge2,arge3);
		return slot;
	}
	//2�����ĺ�����
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2>
	function<ReturnType(ArgsType1,ArgsType2)> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2),ClassType* obj,_Ph<1> placeholde,_Ph<2> placeholde2)
	{
		return function<ReturnType(ArgsType1,ArgsType2)>(memFunc,obj);
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2>
	function<ReturnType(ArgsType1)> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2),ClassType* obj,_Ph<1> placeholde,ArgsType2 arge2)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,ArgsType2,NullType> slot(memFunc,obj);
		slot.setParam2(&Cat::Type::Holder<ArgsType2,false>(arge2));
		return slot;
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1,typename ArgsType2>
	function<ReturnType()> bind(ReturnType(ClassType::*memFunc)(ArgsType1,ArgsType2),ClassType* obj,ArgsType1 arge1,ArgsType2 arge2)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,ArgsType2,NullType> slot(memFunc,obj,arge1,arge2);
		return slot;
	}
	//2������ȫ�ֺ�����
	template<typename ReturnType,typename ArgsType1,typename ArgsType2>
	function<ReturnType(ArgsType1,ArgsType2)> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2),_Ph<1> placeholde,_Ph<2> placeholde2)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2),ReturnType,ArgsType1,ArgsType2,NullType> slot(memFunc);
		return slot;
	}
	template<typename ReturnType,typename ArgsType1,typename ArgsType2>
	function<ReturnType(ArgsType1)> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2),_Ph<1> placeholde,ArgsType2 arge2)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2),ReturnType,ArgsType1,ArgsType2,NullType> slot(memFunc);
		slot.setParam2(&Cat::Type::Holder<ArgsType2,false>(arge2));
		return function<ReturnType(ArgsType1)>(slot);
	}
	template<typename ReturnType,typename ArgsType1,typename ArgsType2>
	function<ReturnType()> bind(ReturnType(*memFunc)(ArgsType1,ArgsType2),ArgsType1 arge1,ArgsType2 arge2)
	{
		FunctorPointerSlot<ReturnType(ArgsType1,ArgsType2),ReturnType,ArgsType1,ArgsType2,NullType> slot(memFunc,arge1,arge2);
		return slot;
	}
	//1�����ĺ�����
	template<typename ReturnType,typename ClassType,typename ArgsType1>
	function<ReturnType(ArgsType1)> bind(ReturnType(ClassType::*memFunc)(ArgsType1),ClassType* obj,_Ph<1> placeholde)
	{
		return function<ReturnType(ArgsType1)>(memFunc,obj);
	}
	template<typename ReturnType,typename ClassType,typename ArgsType1>
	function<ReturnType()> bind(ReturnType(ClassType::*memFunc)(ArgsType1),ClassType* obj,ArgsType1 arge1)
	{
		MemberFunctionSlot<ClassType,ReturnType,ArgsType1,NullType,NullType> slot(memFunc,obj,arge1);
		return slot;
	}
	//1������ȫ�ֺ�����
	template<typename ReturnType,typename ArgsType1>
	function<ReturnType(ArgsType1)> bind(ReturnType(*memFunc)(ArgsType1),_Ph<1> placeholde)
	{
		FunctorPointerSlot<ReturnType(ArgsType1),ReturnType,ArgsType1,NullType,NullType> slot(memFunc);
		return slot;
	}
	template<typename ReturnType,typename ArgsType1>
	function<ReturnType()> bind(ReturnType(*memFunc)(ArgsType1),ArgsType1 arge1)
	{
		FunctorPointerSlot<ReturnType(ArgsType1),ReturnType,ArgsType1,NullType,NullType> slot(memFunc,arge1);
		return slot;
	}
	//0�����ĺ�����
	template<typename ReturnType,typename ClassType>
	function<ReturnType()> bind(ReturnType(ClassType::*memFunc)(),ClassType* obj)
	{
		return function<ReturnType()>(memFunc,obj);
	}
	template<typename ReturnType>
	function<ReturnType()> bind(ReturnType(*memFunc)())
	{
		FunctorPointerSlot<ReturnType(),ReturnType,NullType,NullType,NullType> slot(memFunc);
		return slot;
	}
	//�Ѵ�1������function����ת��Ϊ0�����ģ��п���ʵ����������������
	template<typename ReturnType,typename ArgsType1>
	function<ReturnType()> bind(const function<ReturnType(ArgsType1)>& ofunction,ArgsType1 arge1)
	{
		SlotFunctorBase<ReturnType>* functor = ofunction.getFunctor();
		if (functor != NULL)
		{
			function<ReturnType()> slot(*functor);
			slot.getFunctor()->setParam1(&Cat::Type::Holder<ArgsType1,false>(arge1));
			return slot;
		}
		printf("Cat_Error ::bind(const function<ReturnType(ArgsType1)>& ofunction,ArgsType1 arge1) Empty Functor!\n");
		return function<ReturnType()>();
	}

#ifndef CC_CALLBACK_0
#define CC_CALLBACK_0(__selector__,__target__, ...) stl::bind(&__selector__,__target__, ##__VA_ARGS__)
#endif
#ifndef CC_CALLBACK_1
#define CC_CALLBACK_1(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,##__VA_ARGS__)
#endif
#ifndef CC_CALLBACK_2
#define CC_CALLBACK_2(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,stl::placeholders::_2,##__VA_ARGS__)
#endif
#ifndef CC_CALLBACK_3
#define CC_CALLBACK_3(__selector__,__target__, ...) stl::bind(&__selector__,__target__,stl::placeholders::_1,stl::placeholders::_2,stl::placeholders::_3,##__VA_ARGS__)
#endif

#pragma endregion Function

}

#endif