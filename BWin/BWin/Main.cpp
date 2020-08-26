#include <Windows.h>

#include "Core/Property.h"

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR cmd_line, int cmd_show){
	auto f = []{};

	auto sf = Win::Core::Traits::FunctionCast::Get(f);
	sf();

	auto mf = Win::Core::Traits::FunctionCast::Get(wWinMain);
	auto pmf = Win::Core::Traits::FunctionCast::Get(&wWinMain);

	using t = Win::Core::Traits::Functor<decltype(f)>::FirstArgType;

	Win::Core::Property::Value<int> ip;
	Win::Core::Property::Value<int> sip;
	Win::Core::Property::Value<float> fp;

	ip = 9;
	sip = 9;
	fp = 18.9;

	return 0;
}
