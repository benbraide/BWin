#include "ThreadObject.h"

Win::Thread::Object::Object()
	: Id(GetCurrentThreadId()), IsContext(nullptr, GetIsContextGetter_(*this)){

}

Win::Thread::Object::BooleanPropertyType::GetterType Win::Thread::Object::GetIsContextGetter_(Object &self){
	return [&]{
		return (self.Id == GetCurrentThreadId());
	};
}
