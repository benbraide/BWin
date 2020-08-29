#pragma once

#include "Thread/ThreadObject.h"

namespace Win{
	class App{
	public:
		using ThreadPropertyType = Core::Property::External<Thread::Object &>;

		static ThreadPropertyType Thread;

	private:
		static Win::Thread::Object &GetThread_();

		static Win::Thread::Object *GetThreadPtr_();

		static thread_local std::shared_ptr<Win::Thread::Object> thread_;
	};
}
