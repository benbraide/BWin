#include "EventObject.h"

Win::Event::Object::Object(Event::Target &target)
	: Object(target, target){}

Win::Event::Object::Object(Event::Target &context, Event::Target &target)
	: context_(context), target_(target){
	AddDefaultResultHandler_<LRESULT>(*this);

	AddDefaultResultHandler_<__int16>(*this);
	AddDefaultResultHandler_<unsigned __int16>(*this);

	AddDefaultResultHandler_<__int32>(*this);
	AddDefaultResultHandler_<unsigned __int32>(*this);

	AddDefaultResultHandler_<__int64>(*this);
	AddDefaultResultHandler_<unsigned __int64>(*this);

	AddDefaultResultHandler_<float>(*this);
	AddDefaultResultHandler_<double>(*this);
	AddDefaultResultHandler_<long double>(*this);

	Result.AddHandler_<bool>(GetBooleanResultSetter_(*this), GetBooleanResultGetter_(*this));
}

void Win::Event::Object::DoDefault(){
	CheckContext_();

	if ((states_ & (State::PreventDefualt | State::DoneDefault)) != 0u)
		return;//Done or prevented

	if ((states_ & State::DoingDefault) == 0u){
		states_ |= State::DoingDefault;

		DoDefault_();
		DoDefault();

		states_ &= ~State::DoingDefault;
		states_ |= State::DoneDefault;
	}
	else if ((states_ & (State::CallingHandler | State::CalledHandler)) == 0u){//Call default handler
		states_ |= State::CallingHandler;
		CallDefaultHandler_();

		states_ &= ~State::CallingHandler;
		states_ |= State::CalledHandler;
	}
}

LRESULT Win::Event::Object::InterpretBooleanResult_(bool value) const{
	return (value ? TRUE : FALSE);
}

void Win::Event::Object::StateChanged_(StateValueType changes){}

void Win::Event::Object::DoDefault_(){}

void Win::Event::Object::CallDefaultHandler_(){}

Win::Event::Object::TargetPropertyType::GetterType Win::Event::Object::GetTargetGetter_(Object &self, bool isContext){
	return [&]() -> TargetPropertyType::ReturnType{
		self.CheckContext_();
		return (isContext ? self.context_ : self.target_);
	};
}

Win::Event::Object::StatesPropertyType::SetterType Win::Event::Object::GetStatesSetter_(Object &self){
	return [&](StateValueType value){
		self.CheckContext_();
		if ((value & (State::StopPropagation | State::PreventDefualt | State::StopListening)) == 0u)
			return;//No allowed state specified

		self.states_ &= ~(State::StopPropagation | State::PreventDefualt | State::StopListening);//Remove previous
		self.states_ |= (value & (State::StopPropagation | State::PreventDefualt | State::StopListening));//Set applicable

		self.StateChanged_(value & (State::StopPropagation | State::PreventDefualt));//Alert
	};
}

Win::Event::Object::StatesPropertyType::GetterType Win::Event::Object::GetStatesGetter_(Object &self){
	return [&]{
		self.CheckContext_();
		return (self.states_ & (State::StopPropagation | State::PreventDefualt | State::ValueSet | State::StopListening));
	};
}

typename Win::Core::Property::Untyped::TypedHandler<bool>::SetterType Win::Event::Object::GetBooleanResultSetter_(Object &self){
	return [&](bool value){
		self.CheckContext_();
		self.SetResult_(self.InterpretBooleanResult_(value));
	};
}

typename Win::Core::Property::Untyped::TypedHandler<bool>::GetterType Win::Event::Object::GetBooleanResultGetter_(Object &self){
	return [&]{
		self.CheckContext_();
		return (self.result_ != FALSE);
	};
}
