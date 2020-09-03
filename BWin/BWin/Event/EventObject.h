#pragma once

#include "../Core/FlagProperty.h"
#include "../Core/UntypedProperty.h"

#include "EventTarget.h"

namespace Win::Event{
	class Object : public Thread::Context{
	public:
		using StatesPropertyType = Core::Property::External<StateValueType, Core::Property::Flag::Integral>;
		using ResultPropertyType = Core::Property::Untyped::Owned<Object>;
		using TargetPropertyType = Core::Property::External<Event::Target &>;

		explicit Object(Event::Target &target);

		Object(Event::Target &context, Event::Target &target);

		StatesPropertyType States{ GetStatesSetter_(*this), GetStatesGetter_(*this), nullptr };
		ResultPropertyType Result{ ResultPropertyType::HandlerListType() };

		TargetPropertyType Context{ nullptr, GetTargetGetter_(*this, true) };
		TargetPropertyType Target{ nullptr, GetTargetGetter_(*this, false) };

		virtual void DoDefault();

	protected:
		virtual LRESULT InterpretBooleanResult_(bool value) const;

		virtual void StateChanged_(StateValueType changes);

		virtual void DoDefault_();

		virtual void CallDefaultHandler_();

		template <typename T>
		void AddResultHandler_(const typename Core::Property::Untyped::TypedHandler<T>::SetterType &setter, const typename Core::Property::Untyped::TypedHandler<bool>::SetterType &getter){
			Result.AddHandler_<T>(setter, getter);
		}

		template <typename T>
		void SetResult_(T value){
			result_ = (LRESULT)value;
			states_ |= State::ValueSet;
		}

		static TargetPropertyType::GetterType GetTargetGetter_(Object &self, bool isContext);

		static StatesPropertyType::SetterType GetStatesSetter_(Object &self);

		static StatesPropertyType::GetterType GetStatesGetter_(Object &self);

		template <typename T>
		static typename Core::Property::Untyped::TypedHandler<T>::SetterType GetResultSetter_(Object &self){
			return [&](T value){
				self.CheckContext_();
				self.SetResult_(value);
			};
		}

		template <typename T>
		static typename Core::Property::Untyped::TypedHandler<T>::GetterType GetResultGetter_(Object &self){
			return [&]{
				self.CheckContext_();
				return (T)self.result_;
			};
		}

		static typename Core::Property::Untyped::TypedHandler<bool>::SetterType GetBooleanResultSetter_(Object &self);

		static typename Core::Property::Untyped::TypedHandler<bool>::GetterType GetBooleanResultGetter_(Object &self);

		template <typename T>
		static void AddDefaultResultHandler_(Object &self){
			self.Result.AddHandler_<T>(GetResultSetter_<T>(self), GetResultGetter_<T>(self));
		}

		Event::Target &context_;
		Event::Target &target_;

		StateValueType states_ = 0u;
		LRESULT result_ = 0u;
	};

	template <class T>
	class TypedObject : public Object{
	public:
		using Object::Object;

	protected:
		virtual void DoDefault_() override{
			Context->Events.DispatchDefault(dynamic_cast<T &>(*this));
		}
	};

	class DefaultObject : public Object{
	public:
		using Object::Object;
	};

	template <class BaseT, class ValueT>
	class SingleValueObject : public BaseT{
	public:
		using BaseType = BaseT;
		using ValueType = ValueT;
		using ValuePropertyType = Core::Property::External<ValueT>;

		using BaseType::BaseType;

		template <typename... ArgTypes>
		explicit SingleValueObject(typename Core::Traits::Copy<ValueT>::Type value, ArgTypes &&... args)
			: BaseType(std::forward<ArgTypes>(args)...), value_(value){}

		virtual ~SingleValueObject() = default;

	protected:
		typename ValuePropertyType::GetterType GetValueGetter_(){
			return [&]() -> typename ValuePropertyType::ReturnType{
				this->CheckContext_();
				return value_;
			};
		}

		ValueT value_;
	};

	template <class BaseT, class ValueT, class SecondValueT = ValueT>
	class DoubleValueObject : public SingleValueObject<BaseT, ValueT>{
	public:
		using BaseType = SingleValueObject<BaseT, ValueT>;
		using ValueType = typename BaseType::ValueType;
		using SecondValueType = SecondValueT;

		using ValuePropertyType = typename BaseType::ValuePropertyType;
		using SecondValuePropertyType = Core::Property::External<SecondValueT>;

		using BaseType::BaseType;

		template <typename... ArgTypes>
		explicit DoubleValueObject(typename Core::Traits::Copy<ValueT>::Type value, typename Core::Traits::Copy<SecondValueT>::Type secondValue, ArgTypes &&... args)
			: BaseType(value, std::forward<ArgTypes>(args)...), secondValue_(secondValue){}

		virtual ~DoubleValueObject() = default;

	protected:
		typename SecondValuePropertyType::GetterType GetSecondValueGetter_(){
			return [&]() -> typename SecondValuePropertyType::ReturnType{
				this->CheckContext_();
				return secondValue_;
			};
		}

		SecondValueT secondValue_;
	};
}
