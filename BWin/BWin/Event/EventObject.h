#pragma once

#include "../Core/FlagProperty.h"
#include "../Core/UntypedProperty.h"

#include "EventTarget.h"

namespace Win::Event{
	class Object : public Thread::Context{
	public:
		using StateValueType = unsigned __int32;
		using StatesPropertyType = Core::Property::External<StateValueType, Core::Property::Flag::Integral>;
		using ResultPropertyType = Core::Property::Untyped::Owned<Object>;
		using TargetPropertyType = Core::Property::Value<Event::Target &>;

		struct State{
			static constexpr StateValueType StopPropagation			= (1u << 0x0000);
			static constexpr StateValueType PreventDefualt			= (1u << 0x0001);
			static constexpr StateValueType DoingDefault			= (1u << 0x0002);
			static constexpr StateValueType DoneDefault				= (1u << 0x0003);
			static constexpr StateValueType CallingHandler			= (1u << 0x0004);
			static constexpr StateValueType CalledHandler			= (1u << 0x0005);
		};

		explicit Object(Event::Target &target);

		Object(Event::Target &context, Event::Target &target);

		StatesPropertyType States{ GetStatesSetter_(*this), GetStatesGetter_(*this), nullptr };
		ResultPropertyType Result{ ResultPropertyType::HandlerListType() };

		TargetPropertyType Context;
		TargetPropertyType Target;

		virtual void DoDefault();

	protected:
		virtual void StateChanged_(StateValueType changes);

		virtual void DoDefault_();

		virtual void CallDefaultHandler_();

		template <typename T>
		void AddResultHandler_(const typename Core::Property::Untyped::TypedHandler<T>::SetterType &setter, const typename Core::Property::Untyped::TypedHandler<bool>::SetterType &getter){
			Result.AddHandler_<T>(setter, getter);
		}

		static StatesPropertyType::SetterType GetStatesSetter_(Object &self);

		static StatesPropertyType::GetterType GetStatesGetter_(Object &self);

		template <typename T>
		static typename Core::Property::Untyped::TypedHandler<T>::SetterType GetResultSetter_(Object &self){
			return [&](T value){
				self.CheckContext_();
				self.result_ = (LRESULT)value;
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

		StateValueType states_ = 0u;
		LRESULT result_ = 0u;
	};
}
