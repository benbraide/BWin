#include <Windows.h>

#include "Core/NumericProperty.h"
#include "Core/FlagProperty.h"

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR cmd_line, int cmd_show){
	auto f = []{};

	auto sf = Win::Core::Traits::FunctionCast::Get(f);
	sf();

	auto sfc = Win::Core::Traits::FunctionReturnCast<int>::Get(f);

	auto mf = Win::Core::Traits::FunctionCast::Get(wWinMain);
	auto pmf = Win::Core::Traits::FunctionCast::Get(&wWinMain);

	using t = Win::Core::Traits::Functor<decltype(f)>::FirstArgType;

	Win::Core::Property::Value<int> ip;
	Win::Core::Property::Value<int> sip;
	Win::Core::Property::Value<float> fp;

	ip = 9;
	sip = 9;
	fp = 18.9f;

	Win::Core::Property::Flag::Integral<unsigned int> iff;
	Win::Core::Property::External<unsigned int, Win::Core::Property::Flag::Integral> ief([](unsigned int){

	}, [](){
		return 0u;
	}, [](unsigned int, bool){
		return false;
	});

	iff = 36;

	return 0;
}
