#pragma once

#include <stdexcept>

namespace Win::Core::Exception{
	class Base : public std::exception{
	public:
		using exception::exception;
	};
}
