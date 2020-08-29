#pragma once

#include <list>
#include <mutex>
#include <memory>

#include "../Core/Property.h"

namespace Win::Thread{
	namespace Exception{
		class InvalidId : public Core::Exception::Base{
		public:
			InvalidId()
				: Base("Invalid ID: Cannot access element with specified ID."){}
		};
	}

	class Queue{
	public:
		enum class Event{
			Add,
			Remove,
		};

		using IdType = unsigned __int64;
		using EventCallbackType = std::function<void(Event)>;
		using CallbackType = std::function<void(IdType)>;

		explicit Queue(const EventCallbackType &eventCallback = nullptr)
			: eventCallback_(eventCallback){}

		IdType operator +=(const CallbackType &callback){
			std::lock_guard<std::mutex> guard(lock_);

			callbacks_.push_back(std::make_pair(IdType(), callback));
			if (eventCallback_ != nullptr)
				eventCallback_(Event::Add);

			return (callbacks_.rbegin()->first = reinterpret_cast<IdType>(&*callbacks_.rbegin()));
		}

		IdType operator +=(const std::function<void()> &callback){
			return operator +=([=](IdType){
				callback();
			});
		}

		Queue &operator -=(IdType id){
			std::lock_guard<std::mutex> guard(lock_);
			if (callbacks_.empty())
				throw Exception::InvalidId();

			for (auto it = callbacks_.begin(); it != callbacks_.end(); ++it){
				if (it->first == id){
					callbacks_.erase(it);
					if (eventCallback_ != nullptr)
						eventCallback_(Event::Remove);
					return *this;
				}
			}

			throw Exception::InvalidId();
		}

	protected:
		std::mutex lock_;
		std::list<std::pair<IdType, CallbackType>> callbacks_;
		EventCallbackType eventCallback_;
	};

	class ProxyQueue{
	public:
		using IdType = Queue::IdType;
		using CallbackType = Queue::CallbackType;

		using AddCallbackType = std::function<IdType(const CallbackType &)>;
		using RemoveCallbackType = std::function<void(IdType)>;

		ProxyQueue(const AddCallbackType &addCallback, const RemoveCallbackType &removeCallback)
			: addCallback_(addCallback), removeCallback_(removeCallback){}

		IdType operator +=(const CallbackType &callback){
			if (addCallback_)
				return addCallback_(callback);
			return IdType();
		}

		IdType operator +=(const std::function<void()> &callback){
			return operator +=([=](Queue::IdType){
				callback();
			});
		}

		ProxyQueue &operator -=(IdType id){
			if (removeCallback_)
				removeCallback_(id);
			else
				throw Exception::InvalidId();
			return *this;
		}

	protected:
		AddCallbackType addCallback_;
		RemoveCallbackType removeCallback_;
	};

	template <class OwnerT>
	class OwnedQueue : public Queue{
	public:
		using OwnerType = OwnerT;
		using CallbackPropertyType = Core::Property::External<CallbackType>;
		
		explicit OwnedQueue(const EventCallbackType &eventCallback = nullptr)
			: Queue(eventCallback), Next(nullptr, GetCallbackGetter_(*this)){}

	protected:
		friend OwnerT;

		CallbackPropertyType Next;

		static CallbackPropertyType::GetterType GetCallbackGetter_(OwnedQueue &self){
			return [&]() -> CallbackPropertyType::CopyType{
				IdType id;
				{//Scoped
					std::lock_guard<std::mutex> guard(self.lock_);
					if (self.callbacks_.empty())
						return (self.callback_ = nullptr);

					auto it = self.callbacks_.begin();
					id = it->first;

					self.callback_ = it->second;
					self.callbacks_.erase(it);
				}

				self.callback_(id);//Signal removal
				if (self.eventCallback_ != nullptr)
					self.eventCallback_(Event::Remove);

				return self.callback_;
			};
		}

		CallbackType callback_;
	};

	class QueueScope{
	public:
		using IdType = Queue::IdType;
		using CallbackType = Queue::CallbackType;

		QueueScope(Queue &queue)
			: queue_(queue){}

		~QueueScope(){
			if (!ids_.empty()){
				for (auto id : ids_){
					try{
						queue_ -= id;
					}
					catch (const Exception::InvalidId &){}
				}
			}
		}

		IdType operator +=(const CallbackType &callback){
			return queue_ += [=](IdType id){
				Remove_(id);
				callback(id);
			};
		}
		
		IdType operator +=(const std::function<void()> &callback){
			return operator +=([=](IdType){
				callback();
			});
		}

		QueueScope &operator -=(IdType id){
			try{
				queue_ -= id;
			}
			catch (const Exception::InvalidId &){}

			Remove_(id);

			return *this;
		}

	protected:
		std::list<IdType>::iterator Remove_(IdType id){
			return std::remove(ids_.begin(), ids_.end(), id);
		}

		Queue &queue_;
		std::list<IdType> ids_;
	};
}

namespace Win::Core::Property::Queue{
	template <class T>
	class Container : public Property::Container<T>{
	public:
		using IdType = Thread::Queue::IdType;

		using Property::Container<T>::operator =;

		template <typename T>
		IdType operator +=(const T &callback){
			return this->GetPtr_()->operator +=(callback);
		}

		Container &operator -=(IdType id){
			this->GetPtr_()->operator -=(id);
			return *this;
		}
	};
}

namespace Win::Core::Property{
	template <>
	class Object<Thread::Queue> : public Queue::Container<Thread::Queue>{
	public:
		using Queue::Container<Thread::Queue>::operator =;
		using Queue::Container<Thread::Queue>::operator +=;
		using Queue::Container<Thread::Queue>::operator -=;
	};

	template <class OwnerT>
	class Object<Thread::OwnedQueue<OwnerT>> : public Queue::Container<Thread::OwnedQueue<OwnerT>>{
	public:
		using Queue::Container<Thread::OwnedQueue<OwnerT>>::operator =;
		using Queue::Container<Thread::OwnedQueue<OwnerT>>::operator +=;
		using Queue::Container<Thread::OwnedQueue<OwnerT>>::operator -=;
	};
}
