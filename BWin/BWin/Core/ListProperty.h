#pragma once

#include <memory>

#include "NumericProperty.h"

namespace Win::Core::Property{
	namespace Exception{
		class InvalidIndex : public Base{
		public:
			InvalidIndex()
				: Base("Invalid index: Cannot access element at specified index."){}
		};
	}
}

namespace Win::Core::Property::List{
	template <class T>
	class Generic : public Container<T>{
	public:
		using SizeType = typename T::size_type;
		using ItemType = typename T::value_type;

		using ItemPropertyType = Property::External<ItemType>;
		using ItemInfoPropertyType = Property::External<std::pair<SizeType, ItemType>>;

		using LengthPropertyType = Property::External<SizeType>;
		using BooleanPropertyType = Property::External<bool>;

		using IteratorPropertyType = Property::External<typename T::iterator>;
		using ConstantIteratorPropertyType = Property::External<typename T::const_iterator>;

		using ReverseIteratorPropertyType = Property::External<typename T::reverse_iterator>;
		using ConstantReverseIteratorPropertyType = Property::External<typename T::const_reverse_iterator>;

		Generic() :
			Length(GetLengthSetter_(*this), GetLengthGetter_(*this)),
			IsEmpty(nullptr, GetIsEmptyGetter_(*this)),
			Begin(nullptr, GetBeginGetter_(*this)),
			End(nullptr, GetEndGetter_(*this)),
			CBegin(nullptr, GetCBeginGetter_(*this)),
			CEnd(nullptr, GetCEndGetter_(*this)),
			ReverseBegin(nullptr, GetReverseBeginGetter_(*this)),
			ReverseEnd(nullptr, GetReverseEndGetter_(*this)),
			CReverseBegin(nullptr, GetCReverseBeginGetter_(*this)),
			CReverseEnd(nullptr, GetCReverseEndGetter_(*this)),
			First(GetFirstSetter_(*this), GetFirstGetter_(*this)),
			Last(GetLastSetter_(*this), GetLastGetter_(*this)),
			Item(GetItemSetter_(*this), nullptr)
		{}

		Generic &operator =(typename Container<T>::CopyType) = delete;

		Generic &operator +=(typename Container<ItemType>::CopyType value){
			Insert_(value);
			return *this;
		}

		Generic &operator -=(typename Container<ItemType>::CopyType value){
			Remove_(value);
			return *this;
		}

		typename ItemType operator [](SizeType index) const{
			return GetItemAt_(index);
		}

		LengthPropertyType Length;
		BooleanPropertyType IsEmpty;

		IteratorPropertyType Begin;
		IteratorPropertyType End;

		ConstantIteratorPropertyType CBegin;
		ConstantIteratorPropertyType CEnd;

		ReverseIteratorPropertyType ReverseBegin;
		ReverseIteratorPropertyType ReverseEnd;

		ConstantReverseIteratorPropertyType CReverseBegin;
		ConstantReverseIteratorPropertyType CReverseEnd;

		ItemPropertyType First;
		ItemPropertyType Last;

		ItemInfoPropertyType Item;

	protected:
		virtual void Insert_(typename Container<ItemType>::CopyType value){
			this->GetValue_().push_back(value);
		}

		virtual void Remove_(typename Container<ItemType>::CopyType value){
			auto callback = [&]{
				return std::remove(GetBegin_(), GetEnd_(), value);
			};
			callback();
		}

		virtual void Update_(SizeType index, typename Container<ItemType>::CopyType value){
			*std::next(GetBegin_(), static_cast<typename IteratorPropertyType::ValueType::difference_type>(index)) = value;
		}

		virtual ItemType GetItemAt_(SizeType index) const{
			if (index < GetLength_())
				return *std::next(GetCBegin_(), index);
			throw Exception::InvalidIndex();
		}

		virtual void SetLength_(SizeType value){
			this->GetValue_().resize(value);
		}

		virtual SizeType GetLength_() const{
			return this->GetValue_().size();
		}

		virtual typename IteratorPropertyType::CopyType GetBegin_(){
			return (iter_ = this->GetValue_().begin());
		}

		virtual typename IteratorPropertyType::CopyType GetEnd_(){
			return (iter_ = this->GetValue_().end());
		}

		virtual typename ConstantIteratorPropertyType::CopyType GetCBegin_() const{
			return (citer_ = this->GetValue_().cbegin());
		}

		virtual typename ConstantIteratorPropertyType::CopyType GetCEnd_() const{
			return (citer_ = this->GetValue_().cend());
		}

		virtual typename ReverseIteratorPropertyType::CopyType GetReverseBegin_(){
			return (riter_ = this->GetValue_().rbegin());
		}

		virtual typename ReverseIteratorPropertyType::CopyType GetReverseEnd_(){
			return (riter_ = this->GetValue_().rend());
		}

		virtual typename ConstantReverseIteratorPropertyType::CopyType GetCReverseBegin_() const{
			return (criter_ = this->GetValue_().crbegin());
		}

		virtual typename ConstantReverseIteratorPropertyType::CopyType GetCReverseEnd_() const{
			return (criter_ = this->GetValue_().crend());
		}

		virtual void SetFirst_(typename Container<ItemType>::CopyType value){
			if (GetLength_() == 0u)
				Insert_(value);
			else
				Update_(0, value);
		}

		virtual ItemType GetFirst_() const{
			if (GetLength_() == 0u)
				throw Exception::InvalidIndex();
			return *GetCBegin_();
		}

		virtual void SetLast_(typename Container<ItemType>::CopyType value){
			if (auto length = GetLength_(); length == 0u)
				Insert_(value);
			else
				Update_((length - 1), value);
		}

		virtual ItemType GetLast_() const{
			if (GetLength_() == 0u)
				throw Exception::InvalidIndex();
			return *GetCReverseBegin_();
		}

		virtual void SetItemInfo_(typename ItemInfoPropertyType::CopyType value){
			if (auto length = GetLength_(); length <= value.first){
				if (length < value.first && value.first != static_cast<SizeType>(-1))
					SetLength_(value.first);
				Insert_(value.second);
			}
			else
				Update_(value.first, value.second);
		}

		static typename LengthPropertyType::SetterType GetLengthSetter_(Generic &self){
			return [&](SizeType value){
				return self.SetLength_(value);
			};
		}

		static typename LengthPropertyType::GetterType GetLengthGetter_(Generic &self){
			return [&]{
				return self.GetLength_();
			};
		}

		static BooleanPropertyType::GetterType GetIsEmptyGetter_(Generic &self){
			return [&]{
				return (self.GetLength_() == 0u);
			};
		}

		static typename IteratorPropertyType::GetterType GetBeginGetter_(Generic &self){
			return [&]() -> typename IteratorPropertyType::CopyType{
				return self.GetBegin_();
			};
		}

		static typename IteratorPropertyType::GetterType GetEndGetter_(Generic &self){
			return [&]() -> typename IteratorPropertyType::CopyType{
				return self.GetEnd_();
			};
		}

		static typename ConstantIteratorPropertyType::GetterType GetCBeginGetter_(Generic &self){
			return [&]() -> typename ConstantIteratorPropertyType::CopyType{
				return self.GetCBegin_();
			};
		}

		static typename ConstantIteratorPropertyType::GetterType GetCEndGetter_(Generic &self){
			return [&]() -> typename ConstantIteratorPropertyType::CopyType{
				return self.GetCEnd_();
			};
		}

		static typename ReverseIteratorPropertyType::GetterType GetReverseBeginGetter_(Generic &self){
			return [&]() -> typename ReverseIteratorPropertyType::CopyType{
				return self.GetReverseBegin_();
			};
		}

		static typename ReverseIteratorPropertyType::GetterType GetReverseEndGetter_(Generic &self){
			return [&]() -> typename ReverseIteratorPropertyType::CopyType{
				return self.GetReverseEnd_();
			};
		}

		static typename ConstantReverseIteratorPropertyType::GetterType GetCReverseBeginGetter_(Generic &self){
			return [&]() -> typename ConstantReverseIteratorPropertyType::CopyType{
				return self.GetCReverseBegin_();
			};
		}

		static typename ConstantReverseIteratorPropertyType::GetterType GetCReverseEndGetter_(Generic &self){
			return [&]() -> typename ConstantReverseIteratorPropertyType::CopyType{
				return self.GetCReverseEnd_();
			};
		}

		static typename ItemPropertyType::SetterType GetFirstSetter_(Generic &self){
			return [&](typename Container<ItemType>::CopyType value){
				return self.SetFirst_(value);
			};
		}

		static typename ItemPropertyType::GetterType GetFirstGetter_(Generic &self){
			return [&]{
				return self.GetFirst_();
			};
		}

		static typename ItemPropertyType::SetterType GetLastSetter_(Generic &self){
			return [&](typename Container<ItemType>::CopyType value){
				return self.SetLast_(value);
			};
		}

		static typename ItemPropertyType::GetterType GetLastGetter_(Generic &self){
			return [&]{
				return self.GetLast_();
			};
		}

		static typename ItemInfoPropertyType::SetterType GetItemSetter_(Generic &self){
			return [&](typename ItemInfoPropertyType::CopyType value){
				return self.SetItemInfo_(value);
			};
		}

		mutable typename IteratorPropertyType::ValueType iter_;
		mutable typename ConstantIteratorPropertyType::ValueType citer_;
		mutable typename ReverseIteratorPropertyType::ValueType riter_;
		mutable typename ConstantReverseIteratorPropertyType::ValueType criter_;
	};
}
