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

	template <class T>
	class Number : public Container<T>{
	public:
		Number &operator =(__int16 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(unsigned __int16 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(__int32 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(unsigned __int32 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(__int64 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(unsigned __int64 value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(float value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(double value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		Number &operator =(long double value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		template <typename ValueT>
		Number &operator =(const Number<ValueT> &value){
			this->SetValue_(static_cast<T>(value));
			return *this;
		}

		operator __int16() const{
			return static_cast<__int16>(this->GetValue_());
		}

		operator unsigned __int16() const{
			return static_cast<unsigned __int16>(this->GetValue_());
		}

		operator __int32() const{
			return static_cast<__int32>(this->GetValue_());
		}

		operator unsigned __int32() const{
			return static_cast<unsigned __int32>(this->GetValue_());
		}

		operator __int64() const{
			return static_cast<__int64>(this->GetValue_());
		}

		operator unsigned __int64() const{
			return static_cast<unsigned __int64>(this->GetValue_());
		}

		operator float() const{
			return static_cast<float>(this->GetValue_());
		}

		operator double() const{
			return static_cast<double>(this->GetValue_());
		}

		operator long double() const{
			return static_cast<long double>(this->GetValue_());
		}

		auto operator +() const{
			return +this->GetValue_();
		}

		bool operator ==(__int16 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<__int16> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(unsigned __int16 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(__int32 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<__int32> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(unsigned __int32 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(__int64 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<__int64> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(unsigned __int64 other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(float other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<float> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(double other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<double> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(long double other) const{
			return (this->GetValue_() == other);
		}

		bool operator ==(const Number<long double> &other) const{
			return (this->GetValue_() == other);
		}

		bool operator !=(__int16 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<__int16> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(unsigned __int16 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(__int32 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<__int32> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(unsigned __int32 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(__int64 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<__int64> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(unsigned __int64 other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(float other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<float> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(double other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<double> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(long double other) const{
			return (this->GetValue_() != other);
		}

		bool operator !=(const Number<long double> &other) const{
			return (this->GetValue_() != other);
		}

		bool operator <(__int16 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<__int16> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(unsigned __int16 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(__int32 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<__int32> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(unsigned __int32 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(__int64 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<__int64> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(unsigned __int64 other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(float other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<float> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(double other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<double> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(long double other) const{
			return (this->GetValue_() < other);
		}

		bool operator <(const Number<long double> &other) const{
			return (this->GetValue_() < other);
		}

		bool operator <=(__int16 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<__int16> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(unsigned __int16 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(__int32 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<__int32> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(unsigned __int32 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(__int64 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<__int64> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(unsigned __int64 other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(float other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<float> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(double other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<double> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(long double other) const{
			return (this->GetValue_() <= other);
		}

		bool operator <=(const Number<long double> &other) const{
			return (this->GetValue_() <= other);
		}

		bool operator >=(__int16 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<__int16> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(unsigned __int16 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(__int32 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<__int32> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(unsigned __int32 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(__int64 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<__int64> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(unsigned __int64 other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(float other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<float> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(double other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<double> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(long double other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >=(const Number<long double> &other) const{
			return (this->GetValue_() >= other);
		}

		bool operator >(__int16 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<__int16> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(unsigned __int16 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(__int32 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<__int32> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(unsigned __int32 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(__int64 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<__int64> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(unsigned __int64 other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(float other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<float> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(double other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<double> &other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(long double other) const{
			return (this->GetValue_() > other);
		}

		bool operator >(const Number<long double> &other) const{
			return (this->GetValue_() > other);
		}

		auto operator +(__int16 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<__int16> &other) const{
			return (this->GetValue_() + other.operator __int16());
		}

		auto operator +(unsigned __int16 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() + other.operator unsigned __int16());
		}

		auto operator +(__int32 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<__int32> &other) const{
			return (this->GetValue_() + other.operator __int32());
		}

		auto operator +(unsigned __int32 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() + other.operator unsigned __int32());
		}

		auto operator +(__int64 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<__int64> &other) const{
			return (this->GetValue_() + other.operator __int64());
		}

		auto operator +(unsigned __int64 other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() + other.operator unsigned __int64());
		}

		auto operator +(float other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<float> &other) const{
			return (this->GetValue_() + other.operator float());
		}

		auto operator +(double other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<double> &other) const{
			return (this->GetValue_() + other.operator double());
		}

		auto operator +(long double other) const{
			return (this->GetValue_() + other);
		}

		auto operator +(const Number<long double> &other) const{
			return (this->GetValue_() + other.operator long double());
		}

		auto operator -(__int16 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<__int16> &other) const{
			return (this->GetValue_() - other.operator __int16());
		}

		auto operator -(unsigned __int16 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() - other.operator unsigned __int16());
		}

		auto operator -(__int32 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<__int32> &other) const{
			return (this->GetValue_() - other.operator __int32());
		}

		auto operator -(unsigned __int32 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() - other.operator unsigned __int32());
		}

		auto operator -(__int64 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<__int64> &other) const{
			return (this->GetValue_() - other.operator __int64());
		}

		auto operator -(unsigned __int64 other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() - other.operator unsigned __int64());
		}

		auto operator -(float other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<float> &other) const{
			return (this->GetValue_() - other.operator float());
		}

		auto operator -(double other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<double> &other) const{
			return (this->GetValue_() - other.operator double());
		}

		auto operator -(long double other) const{
			return (this->GetValue_() - other);
		}

		auto operator -(const Number<long double> &other) const{
			return (this->GetValue_() - other.operator long double());
		}

		auto operator *(__int16 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<__int16> &other) const{
			return (this->GetValue_() * other.operator __int16());
		}

		auto operator *(unsigned __int16 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() * other.operator unsigned __int16());
		}

		auto operator *(__int32 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<__int32> &other) const{
			return (this->GetValue_() * other.operator __int32());
		}

		auto operator *(unsigned __int32 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() * other.operator unsigned __int32());
		}

		auto operator *(__int64 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<__int64> &other) const{
			return (this->GetValue_() * other.operator __int64());
		}

		auto operator *(unsigned __int64 other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() * other.operator unsigned __int64());
		}

		auto operator *(float other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<float> &other) const{
			return (this->GetValue_() * other.operator float());
		}

		auto operator *(double other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<double> &other) const{
			return (this->GetValue_() * other.operator double());
		}

		auto operator *(long double other) const{
			return (this->GetValue_() * other);
		}

		auto operator *(const Number<long double> &other) const{
			return (this->GetValue_() * other.operator long double());
		}

		auto operator /(__int16 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<__int16> &other) const{
			return (this->GetValue_() / other.operator __int16());
		}

		auto operator /(unsigned __int16 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<unsigned __int16> &other) const{
			return (this->GetValue_() / other.operator unsigned __int16());
		}

		auto operator /(__int32 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<__int32> &other) const{
			return (this->GetValue_() / other.operator __int32());
		}

		auto operator /(unsigned __int32 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<unsigned __int32> &other) const{
			return (this->GetValue_() / other.operator unsigned __int32());
		}

		auto operator /(__int64 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<__int64> &other) const{
			return (this->GetValue_() / other.operator __int64());
		}

		auto operator /(unsigned __int64 other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<unsigned __int64> &other) const{
			return (this->GetValue_() / other.operator unsigned __int64());
		}

		auto operator /(float other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<float> &other) const{
			return (this->GetValue_() / other.operator float());
		}

		auto operator /(double other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<double> &other) const{
			return (this->GetValue_() / other.operator double());
		}

		auto operator /(long double other) const{
			return (this->GetValue_() / other);
		}

		auto operator /(const Number<long double> &other) const{
			return (this->GetValue_() / other.operator long double());
		}

		template <typename ValueT>
		Number &operator +=(const ValueT &value){
			return (*this = *this + value);
		}

		template <typename ValueT>
		Number &operator -=(const ValueT &value){
			return (*this = *this - value);
		}

		template <typename ValueT>
		Number &operator *=(const ValueT &value){
			return (*this = *this * value);
		}

		template <typename ValueT>
		Number &operator /=(const ValueT &value){
			return (*this = *this / value);
		}

		friend bool operator ==(__int16 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(unsigned __int16 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(__int32 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(unsigned __int32 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(__int64 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(unsigned __int64 left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(float left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(double left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator ==(long double left, const Number &right){
			return (left == right.GetValue_());
		}

		friend bool operator !=(__int16 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(unsigned __int16 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(__int32 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(unsigned __int32 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(__int64 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(unsigned __int64 left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(float left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(double left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator !=(long double left, const Number &right){
			return (left != right.GetValue_());
		}

		friend bool operator <(__int16 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(unsigned __int16 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(__int32 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(unsigned __int32 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(__int64 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(unsigned __int64 left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(float left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(double left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <(long double left, const Number &right){
			return (left < right.GetValue_());
		}

		friend bool operator <=(__int16 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(unsigned __int16 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(__int32 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(unsigned __int32 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(__int64 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(unsigned __int64 left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(float left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(double left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator <=(long double left, const Number &right){
			return (left <= right.GetValue_());
		}

		friend bool operator >=(__int16 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(unsigned __int16 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(__int32 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(unsigned __int32 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(__int64 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(unsigned __int64 left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(float left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(double left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >=(long double left, const Number &right){
			return (left >= right.GetValue_());
		}

		friend bool operator >(__int16 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(unsigned __int16 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(__int32 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(unsigned __int32 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(__int64 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(unsigned __int64 left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(float left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(double left, const Number &right){
			return (left > right.GetValue_());
		}

		friend bool operator >(long double left, const Number &right){
			return (left > right.GetValue_());
		}

		friend auto operator +(__int16 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(unsigned __int16 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(__int32 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(unsigned __int32 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(__int64 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(unsigned __int64 left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(float left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(double left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator +(long double left, const Number &right){
			return (left + right.GetValue_());
		}

		friend auto operator -(__int16 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(unsigned __int16 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(__int32 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(unsigned __int32 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(__int64 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(unsigned __int64 left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(float left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(double left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator -(long double left, const Number &right){
			return (left - right.GetValue_());
		}

		friend auto operator *(__int16 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(unsigned __int16 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(__int32 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(unsigned __int32 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(__int64 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(unsigned __int64 left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(float left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(double left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator *(long double left, const Number &right){
			return (left * right.GetValue_());
		}

		friend auto operator /(__int16 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(unsigned __int16 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(__int32 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(unsigned __int32 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(__int64 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(unsigned __int64 left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(float left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(double left, const Number &right){
			return (left / right.GetValue_());
		}

		friend auto operator /(long double left, const Number &right){
			return (left / right.GetValue_());
		}
	};

	template <class T>
	class SignedNumber : public Number<T>{
	public:
		using Number<T>::operator =;

		auto operator -() const{
			return -this->GetValue_();
		}
	};

	template <class T>
	class Integer : public Number<T>{
	public:
		using Number<T>::operator =;

		Integer &operator ++(){
			Container<T>::template SetValue_(this->GetValue_() + static_cast<T>(1));
			return *this;
		}

		auto operator ++(int){
			auto value = this->GetValue_();
			Container<T>::template SetValue_(value + static_cast<T>(1));
			return value;
		}

		Integer &operator --(){
			Container<T>::template SetValue_(this->GetValue_() - static_cast<T>(1));
			return *this;
		}

		auto operator --(int){
			auto value = this->GetValue_();
			Container<T>::template SetValue_(value - static_cast<T>(1));
			return value;
		}

		auto operator %(__int16 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<__int16> &other) const{
			return (this->GetValue_() % other.operator __int16());
		}

		auto operator %(unsigned __int16 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() % other.operator unsigned __int16());
		}

		auto operator %(__int32 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<__int32> &other) const{
			return (this->GetValue_() % other.operator __int32());
		}

		auto operator %(unsigned __int32 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() % other.operator unsigned __int32());
		}

		auto operator %(__int64 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<__int64> &other) const{
			return (this->GetValue_() % other.operator __int64());
		}

		auto operator %(unsigned __int64 other) const{
			return (this->GetValue_() % other);
		}

		auto operator %(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() % other.operator unsigned __int64());
		}

		auto operator <<(__int16 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<__int16> &other) const{
			return (this->GetValue_() << other.operator __int16());
		}

		auto operator <<(unsigned __int16 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() << other.operator unsigned __int16());
		}

		auto operator <<(__int32 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<__int32> &other) const{
			return (this->GetValue_() << other.operator __int32());
		}

		auto operator <<(unsigned __int32 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() << other.operator unsigned __int32());
		}

		auto operator <<(__int64 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<__int64> &other) const{
			return (this->GetValue_() << other.operator __int64());
		}

		auto operator <<(unsigned __int64 other) const{
			return (this->GetValue_() << other);
		}

		auto operator <<(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() << other.operator unsigned __int64());
		}

		auto operator >>(__int16 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<__int16> &other) const{
			return (this->GetValue_() >> other.operator __int16());
		}

		auto operator >>(unsigned __int16 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() >> other.operator unsigned __int16());
		}

		auto operator >>(__int32 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<__int32> &other) const{
			return (this->GetValue_() >> other.operator __int32());
		}

		auto operator >>(unsigned __int32 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() >> other.operator unsigned __int32());
		}

		auto operator >>(__int64 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<__int64> &other) const{
			return (this->GetValue_() >> other.operator __int64());
		}

		auto operator >>(unsigned __int64 other) const{
			return (this->GetValue_() >> other);
		}

		auto operator >>(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() >> other.operator unsigned __int64());
		}

		auto operator &(__int16 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<__int16> &other) const{
			return (this->GetValue_() & other.operator __int16());
		}

		auto operator &(unsigned __int16 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() & other.operator unsigned __int16());
		}

		auto operator &(__int32 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<__int32> &other) const{
			return (this->GetValue_() & other.operator __int32());
		}

		auto operator &(unsigned __int32 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() & other.operator unsigned __int32());
		}

		auto operator &(__int64 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<__int64> &other) const{
			return (this->GetValue_() & other.operator __int64());
		}

		auto operator &(unsigned __int64 other) const{
			return (this->GetValue_() & other);
		}

		auto operator &(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() & other.operator unsigned __int64());
		}

		auto operator |(__int16 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<__int16> &other) const{
			return (this->GetValue_() | other.operator __int16());
		}

		auto operator |(unsigned __int16 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() | other.operator unsigned __int16());
		}

		auto operator |(__int32 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<__int32> &other) const{
			return (this->GetValue_() | other.operator __int32());
		}

		auto operator |(unsigned __int32 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() | other.operator unsigned __int32());
		}

		auto operator |(__int64 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<__int64> &other) const{
			return (this->GetValue_() | other.operator __int64());
		}

		auto operator |(unsigned __int64 other) const{
			return (this->GetValue_() | other);
		}

		auto operator |(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() | other.operator unsigned __int64());
		}

		auto operator ^(__int16 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<__int16> &other) const{
			return (this->GetValue_() ^ other.operator __int16());
		}

		auto operator ^(unsigned __int16 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<unsigned __int16> &other) const{
			return (this->GetValue_() ^ other.operator unsigned __int16());
		}

		auto operator ^(__int32 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<__int32> &other) const{
			return (this->GetValue_() ^ other.operator __int32());
		}

		auto operator ^(unsigned __int32 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<unsigned __int32> &other) const{
			return (this->GetValue_() ^ other.operator unsigned __int32());
		}

		auto operator ^(__int64 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<__int64> &other) const{
			return (this->GetValue_() ^ other.operator __int64());
		}

		auto operator ^(unsigned __int64 other) const{
			return (this->GetValue_() ^ other);
		}

		auto operator ^(const Integer<unsigned __int64> &other) const{
			return (this->GetValue_() ^ other.operator unsigned __int64());
		}

		template <typename ValueT>
		Integer &operator <<=(const ValueT &value){
			return (*this = *this << value);
		}

		template <typename ValueT>
		Integer &operator >>=(const ValueT &value){
			return (*this = *this >> value);
		}

		template <typename ValueT>
		Integer &operator &=(const ValueT &value){
			return (*this = *this & value);
		}

		template <typename ValueT>
		Integer &operator |=(const ValueT &value){
			return (*this = *this | value);
		}

		template <typename ValueT>
		Integer &operator ^=(const ValueT &value){
			return (*this = *this ^ value);
		}

		friend auto operator %(__int16 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator %(unsigned __int16 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator %(__int32 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator %(unsigned __int32 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator %(__int64 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator %(unsigned __int64 left, const Integer &right){
			return (left % right.GetValue_());
		}

		friend auto operator <<(__int16 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator <<(unsigned __int16 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator <<(__int32 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator <<(unsigned __int32 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator <<(__int64 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator <<(unsigned __int64 left, const Integer &right){
			return (left << right.GetValue_());
		}

		friend auto operator >>(__int16 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator >>(unsigned __int16 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator >>(__int32 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator >>(unsigned __int32 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator >>(__int64 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator >>(unsigned __int64 left, const Integer &right){
			return (left >> right.GetValue_());
		}

		friend auto operator &(__int16 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator &(unsigned __int16 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator &(__int32 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator &(unsigned __int32 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator &(__int64 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator &(unsigned __int64 left, const Integer &right){
			return (left & right.GetValue_());
		}

		friend auto operator |(__int16 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator |(unsigned __int16 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator |(__int32 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator |(unsigned __int32 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator |(__int64 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator |(unsigned __int64 left, const Integer &right){
			return (left | right.GetValue_());
		}

		friend auto operator ^(__int16 left, const Integer &right){
			return (left ^ right.GetValue_());
		}

		friend auto operator ^(unsigned __int16 left, const Integer &right){
			return (left ^ right.GetValue_());
		}

		friend auto operator ^(__int32 left, const Integer &right){
			return (left ^ right.GetValue_());
		}

		friend auto operator ^(unsigned __int32 left, const Integer &right){
			return (left ^ right.GetValue_());
		}

		friend auto operator ^(__int64 left, const Integer &right){
			return (left ^ right.GetValue_());
		}

		friend auto operator ^(unsigned __int64 left, const Integer &right){
			return (left ^ right.GetValue_());
		}
	};

	template <class T>
	class SignedInteger : public Integer<T>{
	public:
		using Integer<T>::operator =;

		auto operator -() const{
			return -this->GetValue_();
		}
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

		using SetterType = std::function<void(const T &)>;
		using GetterType = std::function<const T &()>;

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

	template <>
	class Object<__int16> : public SignedInteger<__int16>{
	public:
		using SignedInteger<__int16>::operator =;
	};

	template <>
	class Object<unsigned __int16> : public Integer<unsigned __int16>{
	public:
		using Integer<unsigned __int16>::operator =;
	};

	template <>
	class Object<__int32> : public SignedInteger<__int32>{
	public:
		using SignedInteger<__int32>::operator =;
	};

	template <>
	class Object<unsigned __int32> : public Integer<unsigned __int32>{
	public:
		using Integer<unsigned __int32>::operator =;
	};

	template <>
	class Object<__int64> : public SignedInteger<__int64>{
	public:
		using SignedInteger<__int64>::operator =;
	};

	template <>
	class Object<unsigned __int64> : public Integer<unsigned __int64>{
	public:
		using Integer<unsigned __int64>::operator =;
	};

	template <>
	class Object<float> : public SignedNumber<float>{
	public:
		using SignedNumber<float>::operator =;
	};

	template <>
	class Object<double> : public SignedNumber<double>{
	public:
		using SignedNumber<double>::operator =;
	};

	template <>
	class Object<long double> : public SignedNumber<long double>{
	public:
		using SignedNumber<long double>::operator =;
	};
}
