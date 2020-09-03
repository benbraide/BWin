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

		class TypeMismatch : public Base{
		public:
			TypeMismatch()
				: Base("Cannot perform specified action because item types don't match."){}
		};
	}
}

namespace Win::Core::Property::List{
	template <class T, class ItemReturnT = typename T::value_type>
	class Generic : public Container<T>{
	public:
		using SizeType = typename T::size_type;
		using ItemType = typename T::value_type;
		using ItemReturnType = ItemReturnT;

		using ItemPropertyType = Property::External<ItemReturnT>;
		using ItemInfoPropertyType = Property::External<std::pair<SizeType, ItemReturnT>>;

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

		Generic &operator +=(typename Traits::Copy<ItemReturnType>::Type value){
			Insert_(value);
			return *this;
		}

		Generic &operator -=(typename Traits::Copy<ItemReturnType>::Type value){
			Remove_(value);
			return *this;
		}

		typename ItemReturnType operator [](SizeType index) const{
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
		template <bool IsSame>
		struct Helper_{
			static void Insert(Generic &self, typename Traits::Copy<ItemReturnType>::Type value){
				self.GetValue_().push_back(value);
			}

			static void Remove(Generic &self, typename Traits::Copy<ItemReturnType>::Type value){
				auto callback = [&]{//Suppress [[nodiscard]] attribute warning
					return std::remove(self.GetBegin_(), self.GetEnd_(), value);
				};
				callback();
			}

			static void Update(Generic &self, SizeType index, typename Traits::Copy<ItemReturnType>::Type value){
				*std::next(self.GetBegin_(), static_cast<typename IteratorPropertyType::ValueType::difference_type>(index)) = value;
			}

			static ItemReturnType GetItemAt(const Generic &self, SizeType index){
				if (index < self.GetLength_())
					return *std::next(self.GetCBegin_(), index);
				throw Exception::InvalidIndex();
			}

			static ItemReturnType GetFirst(const Generic &self){
				if (self.GetLength_() == 0u)
					throw Exception::InvalidIndex();
				return *self.GetCBegin_();
			}

			static ItemReturnType GetLast(const Generic &self){
				if (self.GetLength_() == 0u)
					throw Exception::InvalidIndex();
				return *self.GetCReverseBegin_();
			}
		};

		template <>
		struct Helper_<false>{
			static void Insert(Generic &self, typename Traits::Copy<ItemReturnType>::Type value){
				throw Exception::TypeMismatch();
			}

			static void Remove(Generic &self, typename Traits::Copy<ItemReturnType>::Type value){
				throw Exception::TypeMismatch();
			}

			static void Update(Generic &self, SizeType index, typename Traits::Copy<ItemReturnType>::Type value){
				throw Exception::TypeMismatch();
			}

			static ItemReturnType GetItemAt(const Generic &self, SizeType index){
				throw Exception::TypeMismatch();
			}

			static ItemReturnType GetFirst(const Generic &self){
				throw Exception::TypeMismatch();
			}

			static ItemReturnType GetLast(const Generic &self){
				throw Exception::TypeMismatch();
			}
		};

		virtual void Insert_(typename Traits::Copy<ItemReturnType>::Type value){
			Helper_<std::is_same_v<ItemType, ItemReturnType>>::template Insert(*this, value);
		}

		virtual void Remove_(typename Traits::Copy<ItemReturnType>::Type value){
			Helper_<std::is_same_v<ItemType, ItemReturnType>>::template Remove(*this, value);
		}

		virtual void Update_(SizeType index, typename Traits::Copy<ItemReturnType>::Type value){
			Helper_<std::is_same_v<ItemType, ItemReturnType>>::template Update(*this, index, value);
		}

		virtual ItemReturnType GetItemAt_(SizeType index) const{
			return Helper_<std::is_same_v<ItemType, ItemReturnType>>::template GetItemAt(*this, index);
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

		virtual void SetFirst_(typename Traits::Copy<ItemReturnType>::Type value){
			if (GetLength_() == 0u)
				Insert_(value);
			else
				Update_(0, value);
		}

		virtual ItemReturnType GetFirst_() const{
			return Helper_<std::is_same_v<ItemType, ItemReturnType>>::template GetFirst(*this);
		}

		virtual void SetLast_(typename Traits::Copy<ItemReturnType>::Type value){
			if (auto length = GetLength_(); length == 0u)
				Insert_(value);
			else
				Update_((length - 1), value);
		}

		virtual ItemReturnType GetLast_() const{
			return Helper_<std::is_same_v<ItemType, ItemReturnType>>::template GetLast(*this);
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
			return [&](typename ItemPropertyType::CopyType value){
				return self.SetFirst_(value);
			};
		}

		static typename ItemPropertyType::GetterType GetFirstGetter_(Generic &self){
			return [&]{
				return self.GetFirst_();
			};
		}

		static typename ItemPropertyType::SetterType GetLastSetter_(Generic &self){
			return [&](typename ItemPropertyType::CopyType value){
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

	template <typename T>
	auto begin(Generic<T> &list) -> typename Generic<T>::IteratorPropertyType::ValueType{
		return static_cast<typename T::iterator>(list.Begin);
	}

	template <typename T>
	auto end(Generic<T> &list) -> typename Generic<T>::IteratorPropertyType::ValueType{
		return list.End;
	}
}
