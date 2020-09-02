#pragma once

#include "EventObject.h"

namespace Win::Event{
	class MessageObject : public Object{
	public:
		using MessagePropertyType = Core::Property::External<MSG &>;

		MessageObject(Event::Target &target, const MSG &messageInfo, WNDPROC defaultCallback);

		MessageObject(Event::Target &context, Event::Target &target, const MSG &messageInfo, WNDPROC defaultCallback);

		MessagePropertyType Message{ nullptr, GetMessageGetter_(*this) };

	protected:
		virtual void CallDefaultHandler_() override;

		virtual bool ShouldCallDefaultHandler_() const;

		virtual LRESULT GetDefaultHandlerValue_() const;

		static MessagePropertyType::GetterType GetMessageGetter_(MessageObject &self);

		MSG messageInfo_;
		WNDPROC defaultCallback_;
	};

	template <class T>
	class TypedMessageObject : public MessageObject{
	public:
		using MessageObject::MessageObject;

	protected:
		virtual void DoDefault_() override{
			Context->Events.DispatchDefault(dynamic_cast<T &>(*this));
		}
	};

	class Unknown : public TypedMessageObject<Unknown>{
	public:
		using BaseType = TypedMessageObject<Unknown>;
		using BaseType::BaseType;
	};
}
