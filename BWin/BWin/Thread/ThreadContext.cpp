#include "../App.h"

#include "ThreadContext.h"

Win::Thread::Context::Context()
	: Context(App::Thread.Ref){}

Win::Thread::Context::Context(Object &thread)
	: thread_(thread), queueScope_(thread.Queue.Ref), lowPriorityQueueScope_(thread.LowPriorityQueue.Ref){}

Win::Thread::Context::~Context() = default;

void Win::Thread::Context::CheckContext_() const{
	if (!thread_.IsContext)
		throw Exception::OutsideContext();
}

Win::Thread::Context::ThreadPropertyType::GetterType Win::Thread::Context::GetThreadGetter_(Context &self){
	return [&]() -> ThreadPropertyType::ReturnType{
		return self.thread_;
	};
}

Win::Thread::ProxyQueue::AddCallbackType Win::Thread::Context::GetQueueAddCallback_(Context &self, bool isLowPriority){
	return [=, &self](const ProxyQueue::CallbackType &callback){
		return (isLowPriority ? (self.lowPriorityQueueScope_ += callback) : (self.queueScope_ += callback));
	};
}

Win::Thread::ProxyQueue::RemoveCallbackType Win::Thread::Context::GetQueueRemoveCallback_(Context &self, bool isLowPriority){
	return [=, &self](ProxyQueue::IdType id){
		if (isLowPriority)
			self.lowPriorityQueueScope_ -= id;
		else
			self.queueScope_ -= id;
	};
}
