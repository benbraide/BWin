#include "GeneralEvents.h"

Win::Event::IndexChange::IndexChange(Event::Target &target, std::size_t oldValue, std::size_t value)
	: IndexChange(target, target, oldValue, value){}

Win::Event::IndexChange::IndexChange(Event::Target &context, Event::Target &target, std::size_t oldValue, std::size_t value)
	: BaseType(oldValue, value, context, target){}

Win::Event::ParentChange::ParentChange(Event::Target &target, Tree::Parent *oldValue, Tree::Parent *value)
	: ParentChange(target, target, oldValue, value){}

Win::Event::ParentChange::ParentChange(Event::Target &context, Event::Target &target, Tree::Parent *oldValue, Tree::Parent *value)
	: BaseType(oldValue, value, context, target){}

void Win::Event::ParentChange::DoDefault_(){
	BaseType::DoDefault_();
	if (auto parentContext = dynamic_cast<Tree::Parent *>(&context_); parentContext != nullptr){

	}
}

Win::Event::AncestorChange::AncestorChange(Event::Target &target, Tree::Parent *value, std::size_t index)
	: AncestorChange(target, target, value, index){}

Win::Event::AncestorChange::AncestorChange(Event::Target &context, Event::Target &target, Tree::Parent *value, std::size_t index)
	: BaseType(value, index, context, target){}

Win::Event::GainedParent::GainedParent(Event::Target &target, Tree::Parent *value)
	: GainedParent(target, target, value){}

Win::Event::GainedParent::GainedParent(Event::Target &context, Event::Target &target, Tree::Parent *value)
	: BaseType(value, context, target){}

Win::Event::LostParent::LostParent(Event::Target &target, Tree::Parent *oldValue)
	: LostParent(target, target, oldValue){}

Win::Event::LostParent::LostParent(Event::Target &context, Event::Target &target, Tree::Parent *oldValue)
	: BaseType(oldValue, context, target){}
