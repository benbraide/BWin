#pragma once

#include "ThreadItem.h"

namespace Win::Thread{
	class Object{
	public:
		using QueuePropertyType = Core::Property::Value<OwnedQueue<Object>>;

		Object(){}

		QueuePropertyType Queue;
		QueuePropertyType LowPriorityQueue;
	};
}
