#pragma once

#include <vector>
#include <memory>
#include <variant>

#include "Property.h"

namespace Win::Core::Property{
	namespace Exception{
		class UnsupportedType : public Base{
		public:
			UnsupportedType()
				: Base("Specified type is not supported."){}
		};
	}
}

namespace Win::Core::Property::Untyped{
	class Handler{
	public:
		virtual ~Handler() = default;
	};

	template <class T>
	class TypedHandler : public Handler{
	public:
		using ValueType = T;
		using CopyType = typename Traits::Copy<T>::Type;

		using SetterType = std::function<void(CopyType)>;
		using GetterType = std::function<CopyType()>;

		TypedHandler(const SetterType &setter, const GetterType &getter)
			: setter_(setter), getter_(getter){}

		void SetValue(typename CopyType value){
			if (setter_)
				setter_(value);
			else
				throw Exception::ReadOnly();
		}

		typename CopyType GetValue() const{
			if (!getter_)
				throw Exception::WriteOnly();
			return getter_();
		}

	protected:
		SetterType setter_;
		GetterType getter_;
	};

	class Container{
	public:
		using HandlerType = std::shared_ptr<Handler>;
		using HandlerListType = std::vector<HandlerType>;

		explicit Container(const HandlerListType &handlers)
			: handlers_(handlers){}

		explicit Container(HandlerListType &&handlers)
			: handlers_(std::move(handlers)){}

		template <typename T>
		std::enable_if_t<!std::is_base_of_v<Property::Base, T>, Container> &operator =(const T &value){
			dynamic_cast<TypedHandler<std::remove_reference_t<T>> *>(GetHandler_<T>().get())->SetValue(value);
			return *this;
		}

		template <typename T>
		Container &operator =(const Property::Container<T> &value){
			return operator =(static_cast<T>(value));
		}

		template <typename T>
		operator T() const{
			return dynamic_cast<TypedHandler<std::remove_reference_t<T>> *>(GetHandler_<T>().get())->GetValue();
		}

	protected:
		template <typename T>
		HandlerType GetHandler_() const{
			for (auto it = handlers_.rbegin(); it != handlers_.rend(); ++it){
				if (dynamic_cast<TypedHandler<std::remove_reference_t<T>> *>(it->get()) != nullptr)
					return *it;
			}

			throw Exception::UnsupportedType();
		}

		HandlerListType handlers_;
	};

	template <class OwnerT>
	class Owned : public Container{
	public:
		using OwnerType = OwnerT;

		using Container::Container;
		using Container::operator =;

	protected:
		friend OwnerT;

		template <typename T>
		void AddHandler_(const typename TypedHandler<T>::SetterType &setter, const typename TypedHandler<T>::GetterType &getter){
			handlers_.push_back(std::make_shared<TypedHandler<T>>(setter, getter));
		}
	};

	template <class FirstT, class... RestT>
	class Variant : public Container{
	public:
		Variant()
			: Container({}){
			handlers_.reserve(sizeof...(RestT) + 1);
			AddHandler_<FirstT, RestT...>();
		}

		using Container::operator =;

	protected:
		void AddHandler_(){}

		template <typename T>
		void AddHandler_(){
			handlers_.push_back(std::make_shared<TypedHandler<T>>([=](typename Traits::Copy<T>::Type value){
				value_ = value;
			}, [=]() -> typename Traits::Copy<T>::Type{
				return std::get<T>(value_);
			}));
		}

		template <typename T, typename U, typename... V>
		void AddHandler_(){
			AddHandler_<T>();
			AddHandler_<U, V...>();
		}

		std::variant<FirstT, RestT...> value_;
	};
}
