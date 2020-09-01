#include "EventObject.h"

std::pair<LRESULT, Win::Event::StateValueType> Win::Event::DefaultDispatcher::Trigger(Target &owner){
	return owner.Events.Trigger<DefaultObject>();
}
