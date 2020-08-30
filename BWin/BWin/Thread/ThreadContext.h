#pragma once

#include <future>

#include "../Core/Exception.h"

#include "ThreadObject.h"

namespace Win::Thread{
	namespace Exception{
		class OutsideContext : public Core::Exception::Base{
		public:
			OutsideContext()
				: Base("Specified operation must be performed inside the object's thread context."){}
		};
	}

	class Context{
	public:
		using ThreadPropertyType = Core::Property::External<Object &>;

		template <class T>
		struct Promise{
			static void Set(std::promise<T> &target, const std::function<T()> &valueCallback){
				target.set_value(valueCallback());
			}

			static void Set(std::promise<T> &target){
				target.set_value(T());
			}
		};

		template <>
		struct Promise<void>{
			static void Set(std::promise<void> &target, const std::function<void()> &valueCallback){
				valueCallback();
				target.set_value();
			}

			static void Set(std::promise<void> &target){
				target.set_value();
			}
		};

		Context();

		explicit Context(Object &thread);

		virtual ~Context();

		ThreadPropertyType Thread{ nullptr, GetThreadGetter_(*this) };
		ProxyQueue Queue{ GetQueueAddCallback_(*this, false), GetQueueRemoveCallback_(*this, false) };
		ProxyQueue LowPriorityQueue{ GetQueueAddCallback_(*this, true), GetQueueRemoveCallback_(*this, true) };

		template <typename CallbackT>
		auto Use(const CallbackT &callback) -> typename Core::Traits::Functor<CallbackT>::ReturnType{
			using ReturnT = typename Core::Traits::Functor<CallbackT>::ReturnType;

			if (thread_.IsContext)//Already inside thread context
				return callback();

			std::promise<ReturnT> promise;
			queueScope_ += [&](Queue::IdType id){
				if (id == 0u)
					Promise<ReturnT>::Set(promise, callback);
				else//Callback is being removed from queue
					Promise<ReturnT>::Set(promise);
			};

			return promise.get_future().get();
		}

	protected:
		virtual void CheckContext_() const;

		static ThreadPropertyType::GetterType GetThreadGetter_(Context &self);

		static ProxyQueue::AddCallbackType GetQueueAddCallback_(Context &self, bool isLowPriority);

		static ProxyQueue::RemoveCallbackType GetQueueRemoveCallback_(Context &self, bool isLowPriority);

		Object &thread_;
		QueueScope queueScope_;
		QueueScope lowPriorityQueueScope_;
	};
}
