#include <vector>

#include <Windows.h>

#include "Core/NumericProperty.h"
#include "Core/FlagProperty.h"
#include "Core/ListProperty.h"
#include "Core/UntypedProperty.h"

#include "App.h"

int APIENTRY wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR cmd_line, int cmd_show){
	auto f = []{};

	auto sf = Win::Core::Traits::FunctionCast::Get(f);
	sf();

	auto sfc = Win::Core::Traits::FunctionReturnCast<int>::Get(f);

	auto mf = Win::Core::Traits::FunctionCast::Get(wWinMain);
	auto pmf = Win::Core::Traits::FunctionCast::Get(&wWinMain);

	using t = Win::Core::Traits::Functor<decltype(f)>::Args::FirstType;

	Win::Core::Property::Value<int> ip;
	Win::Core::Property::Value<int> sip;
	Win::Core::Property::Value<float> fp;

	ip = 9;
	sip = 9;
	fp = 18.9f;

	Win::Core::Property::Value<unsigned int, Win::Core::Property::Flag::Integral> iff;
	Win::Core::Property::External<unsigned int, Win::Core::Property::Flag::Integral> ief([](unsigned int){

	}, [](){
		return 0u;
	}, [](unsigned int, bool){
		return false;
	});

	iff = 36;

	Win::Core::Property::Value<std::vector<int>, Win::Core::Property::List::Generic> lp;

	lp += 9;
	lp += 8.1;

	for (auto itc : lp){
		itc += 9;
	}

	int lpl = lp.Length;
	lp.Length = 9;
	lpl = lp.Length;

	int lpf = lp.First;
	int lpll = lp.Last;

	lp.Item = std::make_pair<std::vector<int>::size_type, int>(14, 72);

	Win::Core::Property::Untyped::Variant<int, float, double> vp;

	vp = 9;
	int ivp = vp;

	vp = 4.5f;
	float fvp = vp;

	vp = 36.9;
	double dvp = vp;

	vp = ip;

	Win::Thread::Queue tq;
	auto id = tq += []{};
	tq -= id;
	//tq -= ip;

	Win::Thread::Queue &qn = Win::App::Thread->Queue.Ref;
	Win::App::Thread->Queue += []{};

	return 0;
}
