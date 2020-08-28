#pragma once

#include "Property.h"

namespace Win::Core::Property::Numeric{
	template <class T, bool GetByValue = false>
	class Number : public Container<T>{
	public:
		Number &operator =(T value){
			Container<T>::operator =(value);
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

	template <class T, bool GetByValue = false>
	class SignedNumber : public Number<T>{
	public:
		using Number<T>::operator =;

		auto operator -() const{
			return -this->GetValue_();
		}
	};

	template <class T, bool GetByValue = false>
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

	template <class T, bool GetByValue = false>
	class SignedInteger : public Integer<T>{
	public:
		using Integer<T>::operator =;

		auto operator -() const{
			return -this->GetValue_();
		}
	};
}

namespace Win::Core::Property{
	template <bool GetByValue>
	class Object<__int16> : public Numeric::SignedInteger<__int16>{
	public:
		using SignedInteger<__int16>::operator =;
	};

	template <bool GetByValue>
	class Object<unsigned __int16> : public Numeric::Integer<unsigned __int16>{
	public:
		using Integer<unsigned __int16>::operator =;
	};

	template <bool GetByValue>
	class Object<__int32> : public Numeric::SignedInteger<__int32>{
	public:
		using SignedInteger<__int32>::operator =;
	};

	template <bool GetByValue>
	class Object<unsigned __int32> : public Numeric::Integer<unsigned __int32>{
	public:
		using Integer<unsigned __int32>::operator =;
	};

	template <bool GetByValue>
	class Object<__int64> : public Numeric::SignedInteger<__int64>{
	public:
		using SignedInteger<__int64>::operator =;
	};

	template <bool GetByValue>
	class Object<unsigned __int64> : public Numeric::Integer<unsigned __int64>{
	public:
		using Integer<unsigned __int64>::operator =;
	};

	template <bool GetByValue>
	class Object<float> : public Numeric::SignedNumber<float>{
	public:
		using SignedNumber<float>::operator =;
	};

	template <bool GetByValue>
	class Object<double> : public Numeric::SignedNumber<double>{
	public:
		using SignedNumber<double>::operator =;
	};

	template <bool GetByValue>
	class Object<long double> : public Numeric::SignedNumber<long double>{
	public:
		using SignedNumber<long double>::operator =;
	};
}
