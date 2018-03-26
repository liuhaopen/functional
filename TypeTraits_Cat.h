#ifndef __CAT_TYPE_TRAITS_H_INCLUDED__
#define __CAT_TYPE_TRAITS_H_INCLUDED__

namespace Cat
{
	namespace Type
	{
		class NullType;

		//�ж��Ƿ���ָ������
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
			//��������Test���������T����ת��ΪU�Ǿͻ���������������
			static Small Test(U);
			//���Tת������U���͵Ļ��ͻ����static Big Test(...)�������
			static Big Test(...);
			//��ʵTest(MakeT())�൱��Test(T),���MakeTֻ�Ƿ�ֹT����û��public�Ĺ��캯�������
			static T MakeT();
		public:
			enum
			{
				//T�Ƿ����תΪU����
				IsExist = sizeof(Test(MakeT())) == sizeof(Small)
			};
			enum
			{
				//�Ƿ����˫������ת��
				Exist2Way = IsExist && Conversion<U,T>::IsExist
			};
			enum
			{
				//�Ƿ���ͬ������
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


		//���ڱ����������
		class TypeHolder
		{
		public:
			TypeHolder():m_bNeedDeletePtr(false){}
			virtual ~TypeHolder(){}
			virtual const void* GetValue() const = 0; 
			virtual TypeHolder * Clone() const = 0;
			//�����������ָ�����;Ϳ�����DeleteValue����delete
			virtual void DeleteValue(){}
			void SetDeletePtr(bool needDelete){m_bNeedDeletePtr = needDelete;}
		protected:
			bool m_bNeedDeletePtr;//����������ָ�����͵����ݣ��Ƿ���Ҫ����delete�ͷ�������
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
			//�������ֵΪ����ʱ�ͷ�����ָ��
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
			//�������ֵΪָ��ʱ��ֱ�ӷ���ָ����ָ��ֵ
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
				//��������ָ��Ļ���delete
				if (m_bNeedDeletePtr && Value!=NULL)
				{
					delete Value;
					Value = NULL;
				}
			}
			void DeleteValue(Int2Type<false>)
			{
				//�������������ͨ����Ͳ�����ʲô��
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

//�ж�T�����ǲ���U�ĸ���
#define SuperSubClass(T,U) \
	(Cat::Type::Conversion<const U*,const T*>::IsExist && !Cat::Type::Conversion<const T*,const void*>::IsSame)
#define SuperSubClass_Strict(T,U) \
	(SuperSubClass(T,U) && !Cat::Type::Conversion<const T,const U>::IsSame)

#define AnyType(DataType,Data) Cat::Type::Holder<DataType,Cat::Type::TypeTraits<DataType>::IsPointer>(Data)

#endif