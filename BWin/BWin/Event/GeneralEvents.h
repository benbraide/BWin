#pragma once

#include "../Tree/TreeParent.h"

#include "MessageEvent.h"

namespace Win::Event{
	class IndexChange : public DoubleValueObject<TypedObject<IndexChange>, std::size_t>{
	public:
		using BaseType = DoubleValueObject<TypedObject<IndexChange>, std::size_t>;

		IndexChange(Event::Target &target, std::size_t oldValue, std::size_t value);

		IndexChange(Event::Target &context, Event::Target &target, std::size_t oldValue, std::size_t value);

		ValuePropertyType OldValue{ nullptr, GetValueGetter_() };
		ValuePropertyType Value{ nullptr, GetSecondValueGetter_() };
	};

	class ParentChange : public DoubleValueObject<TypedObject<ParentChange>, Tree::Parent *>{
	public:
		using BaseType = DoubleValueObject<TypedObject<ParentChange>, Tree::Parent *>;

		ParentChange(Event::Target &target, Tree::Parent *oldValue, Tree::Parent *value);

		ParentChange(Event::Target &context, Event::Target &target, Tree::Parent *oldValue, Tree::Parent *value);

		ValuePropertyType OldValue{ nullptr, GetValueGetter_() };
		ValuePropertyType Value{ nullptr, GetSecondValueGetter_() };

	protected:
		virtual void DoDefault_() override;
	};

	class AncestorChange : public DoubleValueObject<TypedObject<AncestorChange>, Tree::Parent *, std::size_t>{
	public:
		using BaseType = DoubleValueObject<TypedObject<AncestorChange>, Tree::Parent *, std::size_t>;

		AncestorChange(Event::Target &target, Tree::Parent *value, std::size_t index);

		AncestorChange(Event::Target &context, Event::Target &target, Tree::Parent *value, std::size_t index);

		ValuePropertyType Value{ nullptr, GetValueGetter_() };
		SecondValuePropertyType Index{ nullptr, GetSecondValueGetter_() };
	};

	class GainedParent : public SingleValueObject<TypedObject<GainedParent>, Tree::Parent *>{
	public:
		using BaseType = SingleValueObject<TypedObject<GainedParent>, Tree::Parent *>;

		GainedParent(Event::Target &target, Tree::Parent *value);

		GainedParent(Event::Target &context, Event::Target &target, Tree::Parent *value);

		ValuePropertyType Value{ nullptr, GetValueGetter_() };
	};

	class LostParent : public SingleValueObject<TypedObject<LostParent>, Tree::Parent *>{
	public:
		using BaseType = SingleValueObject<TypedObject<LostParent>, Tree::Parent *>;

		LostParent(Event::Target &target, Tree::Parent *oldValue);

		LostParent(Event::Target &context, Event::Target &target, Tree::Parent *oldValue);

		ValuePropertyType OldValue{ nullptr, GetValueGetter_() };
	};
}
