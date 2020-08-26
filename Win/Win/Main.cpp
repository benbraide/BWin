#include <iostream>

#include "Core/Traits.h"
#include "Core/Property.h"

int main(){
	auto f = []{
		std::cout << "Hello world!\n";
	};

	auto sf = Win::Core::Traits::FunctionCast::Get(f);
	sf();

	auto mf = Win::Core::Traits::FunctionCast::Get(main);
	auto pmf = Win::Core::Traits::FunctionCast::Get(&main);

	using t = Win::Core::Traits::Functor<decltype(f)>::FirstArgType;

	Win::Core::Property::Value<int> ip;
	Win::Core::Property::Value<int> sip;
	Win::Core::Property::Value<float> fp;

	ip = 9;
	sip = 9;
	fp = 18.9;

	std::cout << (ip == 9) << std::endl;
	std::cout << (9 == ip) << std::endl;

	std::cout << (ip == 9u) << std::endl;
	std::cout << (ip == fp) << std::endl;

	std::cout << (ip == sip) << std::endl;
	std::cout << (sip == ip) << std::endl;

	std::cout << (ip + 9) << std::endl;
	std::cout << (ip + 9.0f) << std::endl;

	std::cout << (9 + ip) << std::endl;
	std::cout << (9.0f + ip) << std::endl;

	std::cout << (ip + fp) << std::endl;
	std::cout << (fp + ip) << std::endl;

	std::cout << (ip + sip) << std::endl;
	std::cout << (sip + ip) << std::endl;

	ip += 9;

	std::cout << static_cast<int>(ip) << std::endl;

	ip += fp;

	std::cout << static_cast<int>(ip) << std::endl;

	return 0;
}
