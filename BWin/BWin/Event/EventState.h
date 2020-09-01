#pragma once

namespace Win::Event{
	using StateValueType = unsigned __int32;

	struct State{
		static constexpr StateValueType StopPropagation		= (1u << 0x0000);
		static constexpr StateValueType PreventDefualt		= (1u << 0x0001);
		static constexpr StateValueType DoingDefault		= (1u << 0x0002);
		static constexpr StateValueType DoneDefault			= (1u << 0x0003);
		static constexpr StateValueType CallingHandler		= (1u << 0x0004);
		static constexpr StateValueType CalledHandler		= (1u << 0x0005);
		static constexpr StateValueType ValueSet			= (1u << 0x0006);
		static constexpr StateValueType StopListening		= (1u << 0x0007);
	};
}
