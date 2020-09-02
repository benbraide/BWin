#include "MessageEvent.h"

Win::Event::MessageObject::MessageObject(Event::Target &target, const MSG &messageInfo, WNDPROC defaultCallback)
	: MessageObject(target, target, messageInfo, defaultCallback){}

Win::Event::MessageObject::MessageObject(Event::Target &context, Event::Target &target, const MSG &messageInfo, WNDPROC defaultCallback)
	: Object(context, target), messageInfo_(messageInfo), defaultCallback_(defaultCallback){}

void Win::Event::MessageObject::CallDefaultHandler_(){
	if (ShouldCallDefaultHandler_())
		SetResult_(GetDefaultHandlerValue_());
}

bool Win::Event::MessageObject::ShouldCallDefaultHandler_() const{
	return (defaultCallback_ != nullptr && messageInfo_.hwnd != nullptr && messageInfo_.message < WM_APP);
}

LRESULT Win::Event::MessageObject::GetDefaultHandlerValue_() const{
	return CallWindowProcW(defaultCallback_, messageInfo_.hwnd, messageInfo_.message, messageInfo_.wParam, messageInfo_.lParam);
}

Win::Event::MessageObject::MessagePropertyType::GetterType Win::Event::MessageObject::GetMessageGetter_(MessageObject &self){
	return [&]() -> MessagePropertyType::ReturnType{
		self.CheckContext_();
		return self.messageInfo_;
	};
}
