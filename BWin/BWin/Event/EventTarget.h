#pragma once

#include "../Thread/ThreadItem.h"

#include "EventCollection.h"

namespace Win::Event{
	class Target : public Thread::Item{
	public:
		using CollectionType = OwnedCollection<Target>;
		using BucketType = CollectionType::BucketType;
		using IdType = CollectionType::IdType;

		virtual ~Target() = default;

		CollectionType Events;

	protected:
		template <typename ObjectT>
		void AddBucket_(bool isDefault){
			Events.AddBucket_<ObjectT>(isDefault);
		}

		void AddBucket_(BucketType bucket){
			Events.AddBucket_(bucket);
		}

		template <typename CallbackT>
		IdType AddDefault_(const CallbackT &callback){
			return Events.AddDefault_(callback);
		}

		void RemoveDefault_(IdType id){
			Events.RemoveDefault_(id);
		}
	};
}
