#include "../App.h"

Win::Thread::Item::Item()
	: Item(App::Thread){}

Win::Thread::Item::Item(Object &thread) :
	Thread(nullptr, GetThreadGetter_(*this)),
	Queue(GetQueueAddCallback_(*this, false), GetQueueRemoveCallback_(*this, false)),
	LowPriorityQueue(GetQueueAddCallback_(*this, true), GetQueueRemoveCallback_(*this, true)),
	thread_(thread),
	queueScope_(thread.Queue),
	lowPriorityQueueScope_(thread.LowPriorityQueue)
{}

Win::Thread::Item::ThreadPropertyType::GetterType Win::Thread::Item::GetThreadGetter_(Item &self){
	return [&]() -> ThreadPropertyType::CopyType{
		return self.thread_;
	};
}

Win::Thread::ProxyQueue::AddCallbackType Win::Thread::Item::GetQueueAddCallback_(Item &self, bool isLowPriority){
	return [=, &self](const ProxyQueue::CallbackType &callback){
		return (isLowPriority ? (self.lowPriorityQueueScope_ += callback) : self.queueScope_ += callback);
	};
}

Win::Thread::ProxyQueue::RemoveCallbackType Win::Thread::Item::GetQueueRemoveCallback_(Item &self, bool isLowPriority){
	return [=, &self](ProxyQueue::IdType id){
		if (isLowPriority)
			self.lowPriorityQueueScope_ -= id;
		else
			self.queueScope_ -= id;
	};
}
