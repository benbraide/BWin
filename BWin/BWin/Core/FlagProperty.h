#pragma once

#include "Property.h"

namespace Win::Core::Property::Flag{
	template <class T>
	class Integral : public Container<T>{
	public:
		Integral &operator =(T value){
			Container<T>::operator =(value);
			return *this;
		}

		Integral &operator =(const Container<__int16> &value){
			return (*this = static_cast<__int16>(value));
		}

		Integral &operator =(const Container<unsigned __int16> &value){
			return (*this = static_cast<unsigned __int16>(value));
		}

		Integral &operator =(const Container<__int32> &value){
			return (*this = static_cast<__int32>(value));
		}

		Integral &operator =(const Container<unsigned __int32> &value){
			return (*this = static_cast<unsigned __int32>(value));
		}

		Integral &operator =(const Container<__int64> &value){
			return (*this = static_cast<__int64>(value));
		}

		Integral &operator =(const Container<unsigned __int64> &value){
			return (*this = static_cast<unsigned __int64>(value));
		}

		Integral &operator +=(__int16 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<__int16> &value){
			return (*this += static_cast<__int16>(value));
		}

		Integral &operator +=(unsigned __int16 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<unsigned __int16> &value){
			return (*this += static_cast<unsigned __int16>(value));
		}

		Integral &operator +=(__int32 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<__int32> &value){
			return (*this += static_cast<__int32>(value));
		}

		Integral &operator +=(unsigned __int32 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<unsigned __int32> &value){
			return (*this += static_cast<unsigned __int32>(value));
		}

		Integral &operator +=(__int64 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<__int64> &value){
			return (*this += static_cast<__int64>(value));
		}

		Integral &operator +=(unsigned __int64 value){
			this->SetValue_((this->GetValue_() | static_cast<T>(value)));
			return *this;
		}

		Integral &operator +=(const Container<unsigned __int64> &value){
			return (*this += static_cast<unsigned __int64>(value));
		}

		Integral &operator -=(__int16 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<__int16> &value){
			return (*this -= static_cast<__int16>(value));
		}

		Integral &operator -=(unsigned __int16 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<unsigned __int16> &value){
			return (*this -= static_cast<unsigned __int16>(value));
		}

		Integral &operator -=(__int32 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<__int32> &value){
			return (*this -= static_cast<__int32>(value));
		}

		Integral &operator -=(unsigned __int32 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<unsigned __int32> &value){
			return (*this -= static_cast<unsigned __int32>(value));
		}

		Integral &operator -=(__int64 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<__int64> &value){
			return (*this -= static_cast<__int64>(value));
		}

		Integral &operator -=(unsigned __int64 value){
			this->SetValue_((this->GetValue_() & ~static_cast<T>(value)));
			return *this;
		}

		Integral &operator -=(const Container<unsigned __int64> &value){
			return (*this -= static_cast<unsigned __int64>(value));
		}

		operator bool() const{
			return (this->GetValue_() != static_cast<T>(0));
		}

		bool operator &(__int16 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<__int16> &other) const{
			return (*this & static_cast<T>(static_cast<__int16>(other)));
		}

		bool operator &(unsigned __int16 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<unsigned __int16> &other) const{
			return (*this & static_cast<T>(static_cast<unsigned __int16>(other)));
		}

		bool operator &(__int32 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<__int32> &other) const{
			return (*this & static_cast<T>(static_cast<__int32>(other)));
		}

		bool operator &(unsigned __int32 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<unsigned __int32> &other) const{
			return (*this & static_cast<T>(static_cast<unsigned __int32>(other)));
		}

		bool operator &(__int64 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<__int64> &other) const{
			return (*this & static_cast<T>(static_cast<__int64>(other)));
		}

		bool operator &(unsigned __int64 other) const{
			return HasAll_(static_cast<T>(other));
		}

		bool operator &(const Container<unsigned __int64> &other) const{
			return (*this & static_cast<T>(static_cast<unsigned __int64>(other)));
		}

		bool operator |(__int16 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<__int16> &other) const{
			return (*this | static_cast<T>(static_cast<__int16>(other)));
		}

		bool operator |(unsigned __int16 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<unsigned __int16> &other) const{
			return (*this | static_cast<T>(static_cast<unsigned __int16>(other)));
		}

		bool operator |(__int32 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<__int32> &other) const{
			return (*this | static_cast<T>(static_cast<__int32>(other)));
		}

		bool operator |(unsigned __int32 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<unsigned __int32> &other) const{
			return (*this | static_cast<T>(static_cast<unsigned __int32>(other)));
		}

		bool operator |(__int64 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<__int64> &other) const{
			return (*this | static_cast<T>(static_cast<__int64>(other)));
		}

		bool operator |(unsigned __int64 other) const{
			return HasOne_(static_cast<T>(other));
		}

		bool operator |(const Container<unsigned __int64> &other) const{
			return (*this | static_cast<T>(static_cast<unsigned __int64>(other)));
		}

	protected:
		virtual bool HasOne_(T value) const{
			return ((this->GetValue_() & value) != static_cast<T>(0));
		}

		virtual bool HasAll_(T value) const{
			return ((this->GetValue_() & value) == value);
		}
	};
}

namespace Win::Core::Property{
	template <class T>
	class External<T, Flag::Integral> : public Flag::Integral<T>{
	public:
		using BaseType = Flag::Integral<T>;
		using BaseType::operator =;

		using SetterType = std::function<void(typename BaseType::CopyType)>;
		using GetterType = std::function<typename BaseType::CopyType()>;
		using QueryType = std::function<bool(typename BaseType::CopyType, bool)>;

		explicit External(const SetterType &setter, const GetterType &getter, const QueryType &query)
			: setter_(setter), getter_(getter), query_(query){}

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

		virtual bool HasOne_(T value) const override{
			return ((query_ == nullptr) ? BaseType::template HasOne_(value) : query_(value, false));
		}

		virtual bool HasAll_(T value) const override{
			return ((query_ == nullptr) ? BaseType::template HasAll_(value) : query_(value, true));
		}

		SetterType setter_;
		GetterType getter_;
		QueryType query_;
	};
}
