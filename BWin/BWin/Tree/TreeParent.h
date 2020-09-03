#pragma once

#include "../Core/ListProperty.h"

#include "TreeObject.h"

namespace Win::Tree{
	class Parent;

	class Children : public Core::Property::List::Generic<std::list<Object *>, Object &>{
	public:
		using ListType = std::list<Object *>;
		using BaseType = Core::Property::List::Generic<std::list<Object *>, Object &>;

		using BaseType::operator +=;
		using BaseType::operator -=;

		explicit Children(Parent &parent);

		Children &operator -=(std::size_t index);

	private:
		virtual ReturnType GetValue_() const override;

		virtual void Insert_(typename Core::Traits::Copy<ItemReturnType>::Type value) override;

		virtual void Remove_(typename Core::Traits::Copy<ItemReturnType>::Type value) override;

		Parent &parent_;
	};

	class Parent{
	public:
		using ChildrenListType = Children::ListType;

		virtual ~Parent();

		Tree::Children Children{ *this };

	protected:
		ChildrenListType children_;
	};
}
