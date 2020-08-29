#pragma once

#include "ThreadQueue.h"

namespace Win::Thread{
	class Object;

	class Item{
	public:
		using ThreadPropertyType = Core::Property::External<Object &>;

		Item();

		explicit Item(Object &thread);

		ThreadPropertyType Thread;
		ProxyQueue Queue;
		ProxyQueue LowPriorityQueue;

	protected:
		static ThreadPropertyType::GetterType GetThreadGetter_(Item &self);

		static ProxyQueue::AddCallbackType GetQueueAddCallback_(Item &self, bool isLowPriority);

		static ProxyQueue::RemoveCallbackType GetQueueRemoveCallback_(Item &self, bool isLowPriority);

		Object &thread_;
		QueueScope queueScope_;
		QueueScope lowPriorityQueueScope_;
	};
}
