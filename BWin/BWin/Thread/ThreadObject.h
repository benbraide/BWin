#pragma once

#include "../Core/Headers.h"

#include "ThreadQueue.h"

namespace Win::Thread{
	class Object{
	public:
		using QueuePropertyType = Core::Property::Value<OwnedQueue<Object>>;
		using BooleanPropertyType = Core::Property::External<bool>;

		Object();

		QueuePropertyType Queue;
		QueuePropertyType LowPriorityQueue;

		Core::Property::Value<const DWORD> Id;
		BooleanPropertyType IsContext;

	protected:
		static BooleanPropertyType::GetterType GetIsContextGetter_(Object &self);
	};
}
