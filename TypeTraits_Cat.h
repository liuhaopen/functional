#ifndef __CAT_TYPE_TRAITS_H_INCLUDED__
#define __CAT_TYPE_TRAITS_H_INCLUDED__

namespace Cat
{
	namespace Type
	{
		class NullType;

		//判断是否是指针类型
		template<typename T>
		class TypeTraits
		{
			template<class U>
			struct PointerTraits
			{
				enum{ Result = false };
				//typedef NullType PointeeType;
			};
			template<class U>
			struct PointerTraits<U*>
			{
				enum{ Result = true };
				//typedef U PointeeType;
			};
		public:
			enum
			{
				IsPointer = PointerTraits<T>::Result
			};
			//typedef PointerTraits<T>::PointeeType PointerType;
		};

		template<int V>
		struct Int2Type
		{
			enum{value=V};
		};
		template<typename T>
		struct Type2Type
		{
			typedef T Type;
		};
			


		template<typename T,typename U>
		class Conversion
		{
			typedef char Small;
			class Big{Small Dummy[2];};
			//重载两个Test函数，如果T可以转化为U那就会进入下面这个函数
			static Small Test(U);
			//如果T转化不成U类型的话就会进入static Big Test(...)这个函数
			static Big Test(...);
			//其实Test(MakeT())相当于Test(T),这个MakeT只是防止T类型没有public的构造函数的情况
			static T MakeT();
		public:
			enum
			{
				//T是否可以转为U类型
				IsExist = sizeof(Test(MakeT())) == sizeof(Small)
			};
			enum
			{
				//是否存在双向类型转换
				Exist2Way = IsExist && Conversion<U,T>::IsExist
			};
			enum
			{
				//是否是同种类型
				IsSame = false
			};
		};
		template<typename T>
		class Conversion<T,T>
		{
		public:
			enum
			{
				IsExist = 1,
				Exist2Way = 1,
				IsSame = 1
			};
		};


		//用于保存类的类型
		class TypeHolder
		{
		public:
			TypeHolder():m_bNeedDeletePtr(false){}
			virtual ~TypeHolder(){}
			virtual const void* GetValue() const = 0; 
			virtual TypeHolder * Clone() const = 0;
			//如果保留的是指针类型就可以在DeleteValue里面delete
			virtual void DeleteValue(){}
			void SetDeletePtr(bool needDelete){m_bNeedDeletePtr = needDelete;}
		protected:
			bool m_bNeedDeletePtr;//如果保存的是指针类型的数据，是否需要调用delete释放其数据
		};
		template<typename ValueType,bool isPointer>
		class Holder:public TypeHolder
		{
		public:
			Holder(const ValueType & value) : Value(value)/*,ValuePtr(&Value)*/{}
		public:
			virtual const void* GetValue() const
			{
				return GetValue(Int2Type<isPointer>());
			}
			ValueType GetValue()
			{
				return Value;
			}
			//当保存的值为引用时就返回其指针
			//void* GetValue(Int2Type<false>) const
			//{
			//	return &Value;
			//	//return ValuePtr;
			//}
			const void* GetValue(Int2Type<false>) const
			{
				return &Value;
				//return ValuePtr;
			}
			//当保存的值为指针时就直接返回指针所指的值
			void* GetValue(Int2Type<true>) const
			{
				return Value;
			}
			virtual TypeHolder * Clone() const
			{
				return new Holder(Value);
			}
			void DeleteValue(Int2Type<true>)
			{
				//保留的是指针的话就delete
				if (m_bNeedDeletePtr && Value!=NULL)
				{
					delete Value;
					Value = NULL;
				}
			}
			void DeleteValue(Int2Type<false>)
			{
				//如果保留的是普通对象就不会做什么了
			}
			~Holder()
			{
				DeleteValue(Int2Type<isPointer>());
			}
		public:
			ValueType Value;
			//ValueType* ValuePtr;
		private:
			Holder & operator=(const Holder &);
		};

	}//Type
}//Cat

//判断T类型是不是U的父类
#define SuperSubClass(T,U) \
	(Cat::Type::Conversion<const U*,const T*>::IsExist && !Cat::Type::Conversion<const T*,const void*>::IsSame)
#define SuperSubClass_Strict(T,U) \
	(SuperSubClass(T,U) && !Cat::Type::Conversion<const T,const U>::IsSame)

#define AnyType(DataType,Data) Cat::Type::Holder<DataType,Cat::Type::TypeTraits<DataType>::IsPointer>(Data)

#endif