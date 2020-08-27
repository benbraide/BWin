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

	template <class T>
	class Container{
	public:
		using ValueType = T;
		using CopyType = typename Traits::Copy<T>::Type;

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
		virtual void SetValue_(CopyType value){
			GetValue_() = value;
		}

		virtual CopyType GetValue_() const{
			throw Exception::WriteOnly();
		}

		virtual T &GetValue_(){
			throw Exception::ReadOnly();
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
		virtual void SetValue_(typename BaseType::CopyType value) override{
			value_ = value;
		}

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

		const T &value_;
	};

	template <class T, template<class> class BaseT = Object>
	class External : public BaseT<T>{
	public:
		using BaseType = BaseT<T>;
		using BaseType::operator =;

		using SetterType = std::function<void(typename BaseType::CopyType)>;
		using GetterType = std::function<typename BaseType::CopyType()>;

		explicit External(const SetterType &setter, const GetterType &getter)
			: setter_(setter), getter_(getter){}

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

		SetterType setter_;
		GetterType getter_;
	};
}
