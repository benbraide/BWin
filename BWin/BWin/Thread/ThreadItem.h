#pragma once

#include "ThreadContext.h"

namespace Win::Thread{
	class Item : public Context{
	public:
		using Context::Context;

		virtual ~Item() = default;
	};
}
