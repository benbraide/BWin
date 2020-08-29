#pragma once

#include "Exception.h"
#include "Traits.h"

namespace Win::Core::Property{
	namespace Exception{
		class Base : public Core::Exception::Base{
		public:
			using Core::Exception::Base::Base;
		};

		class ReadOnly : public Base{
		public:
			ReadOnly()
				: Base("A value cannot be assigned to read-only property."){}
		};

		class WriteOnly : public Base{
		public:
			WriteOnly()
				: Base("Cannot read value from a write-only property."){}
		};
	}

	class Base{
	public:
		virtual ~Base() = default;
	};

	template <class T>
	class Container : public Base{
	public:
		using ValueType = T;
		using PtrType = std::remove_reference_t<T> *;
		using RefType = std::conditional_t<(!std::is_scalar_v<T> && (std::is_const_v<T> || !std::is_reference_v<T>)), T &, std::remove_reference_t<T> *>;
		using CopyType = typename Traits::Copy<T>::Type;

		template <bool IsRef>
		struct Ref_{
			static T &Get(Container &self){
				return self.GetValue_();
			}
		};

		template <>
		struct Ref_<false>{
			static std::remove_reference_t<T> *Get(Container &self){
				return &self.GetValue_();
			}
		};

		Container &operator =(CopyType value){
			SetValue_(value);
			return *this;
		}

		Container &operator =(const Container &value){
			SetValue_(value.GetValue_());
			return *this;
		}

		operator CopyType() const{
			return GetValue_();
		}

		operator RefType(){
			return Ref_<(!std::is_scalar_v<T> && (std::is_const_v<T> || !std::is_reference_v<T>))>::template Get(*this);
		}

		PtrType operator ->(){
			return GetPtr_();
		}

		bool operator ==(CopyType other) const{
			return (GetValue_() == other);
		}

		bool operator ==(const Container<T> &other) const{
			return (GetValue_() == other);
		}

		bool operator !=(CopyType other) const{
			return (GetValue_() != other);
		}

		bool operator !=(const Container<T> &other) const{
			return (GetValue_() != other);
		}

		friend bool operator ==(CopyType left, const Container &right){
			return (left == right.GetValue_());
		}

		friend bool operator !=(CopyType left, const Container &right){
			return (left != right.GetValue_());
		}

	protected:
		template <bool IsCopyAssignable>
		struct Copy_{
			static void Do(Container &self, CopyType value){
				self.GetValue_() = value;
			}
		};

		template <>
		struct Copy_<false>{
			static void Do(Container &self, CopyType){
				throw Exception::ReadOnly();
			}
		};

		virtual void SetValue_(CopyType value){
			Copy_<std::is_copy_assignable_v<T>>::template Do(*this, value);
		}

		virtual CopyType GetValue_() const{
			throw Exception::WriteOnly();
		}

		virtual T &GetValue_(){
			throw Exception::ReadOnly();
		}

		virtual PtrType GetPtr_(){
			return &GetValue_();
		}
	};

	template <class T>
	class Object : public Container<T>{
		using Container<T>::operator =;
	};

	template <class T, template<class> class BaseT = Object>
	class Value : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

	protected:
		virtual typename BaseType::CopyType GetValue_() const override{
			return value_;
		}

		virtual T &GetValue_() override{
			return value_;
		}

		T value_{};
	};

	template <class T, template<class> class BaseT>
	class Value<const T, BaseT> : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

		explicit Value(const T &value)
			: value_(value){}

	protected:
		virtual typename BaseType::CopyType GetValue_() const override{
			return value_;
		}

		const T value_;
	};

	template <class T, template<class> class BaseT = Object>
	class Reference : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

		explicit Reference(T &value)
			: value_(value){}

	protected:
		virtual void SetValue_(typename BaseType::CopyType value) override{
			value_ = value;
		}

		virtual typename BaseType::CopyType GetValue_() const override{
			return value_;
		}

		virtual T &GetValue_() override{
			return value_;
		}

		T &value_;
	};

	template <class T, template<class> class BaseT>
	class Reference<const T, BaseT> : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

		explicit Reference(const T &value)
			: value_(value){}

	protected:
		virtual typename BaseType::CopyType GetValue_() const override{
			return value_;
		}

		virtual typename BaseType::PtrType GetPtr_() override{
			return &value_;
		}

		const T &value_;
	};

	template <class T, template<class> class BaseT = Object>
	class External : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

		using SetterType = std::function<void(typename BaseType::CopyType)>;
		using GetterType = std::function<typename BaseType::CopyType()>;

		using RefGetterType = std::function<T &()>;
		using PtrGetterType = std::function<typename BaseType::PtrType()>;

		External(const SetterType &setter, const GetterType &getter, const PtrGetterType &ptrGetter = nullptr, const RefGetterType &refGetter = nullptr)
			: setter_(setter), getter_(getter), ptrGetter_(ptrGetter), refGetter_(refGetter){}

	protected:
		virtual void SetValue_(typename BaseType::CopyType value) override{
			if (setter_)
				setter_(value);
			else
				throw Exception::ReadOnly();
		}

		virtual typename BaseType::CopyType GetValue_() const override{
			if (!getter_)
				throw Exception::WriteOnly();
			return getter_();
		}

		virtual T &GetValue_() override{
			if (!refGetter_)
				throw Exception::ReadOnly();
			return refGetter_();
		}

		virtual typename BaseType::PtrType GetPtr_() override{
			if (!ptrGetter_)
				throw Exception::ReadOnly();
			return ptrGetter_();
		}

		SetterType setter_;
		GetterType getter_;
		PtrGetterType ptrGetter_;
		RefGetterType refGetter_;
	};
}
