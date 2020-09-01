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

		class AbortedOnReference : public Core::Exception::Base{
		public:
			AbortedOnReference()
				: Base("A synchronization request was aborted on a reference return type."){}
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

		template <class T>
		struct Promise<T &>{
			static void Set(std::promise<T *> &target, const std::function<T &()> &valueCallback){
				target.set_value(&valueCallback());
			}

			static void Set(std::promise<T *> &target){
				target.set_value(nullptr);
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

		template <class T>
		struct PromiseValue{
			static T Get(std::promise<T> &target){
				return target.get_future().get();
			}
		};

		template <class T>
		struct PromiseValue<T &>{
			static T &Get(std::promise<T *> &target){
				auto ptrValue = target.get_future().get();
				if (ptrValue == nullptr)
					throw Exception::AbortedOnReference();
				return *ptrValue;
			}
		};

		Context();

		explicit Context(Object &thread);

		virtual ~Context();

		ThreadPropertyType Thread{ nullptr, GetThreadGetter_(*this) };
		ProxyQueue Queue{ GetQueueAddCallback_(*this, false), GetQueueRemoveCallback_(*this, false) };
		ProxyQueue LowPriorityQueue{ GetQueueAddCallback_(*this, true), GetQueueRemoveCallback_(*this, true) };

		template <typename CallbackT>
		auto Use(const CallbackT &callback) const -> typename Core::Traits::Functor<CallbackT>::ReturnType{
			using ReturnT = typename Core::Traits::Functor<CallbackT>::ReturnType;
			using BaseReturnT = std::remove_reference_t<ReturnT>;

			if (thread_.IsContext)//Already inside thread context
				return callback();

			std::promise<std::conditional_t<std::is_reference_v<ReturnT>, BaseReturnT *, BaseReturnT>> promise;
			queueScope_ += [&](Queue::IdType id){
				if (id == 0u)
					Promise<ReturnT>::template Set(promise, callback);
				else//Callback is being removed from queue
					Promise<ReturnT>::template Set(promise);
			};

			return PromiseValue<ReturnT>::template Get(promise);
		}

	protected:
		virtual void CheckContext_() const;

		static ThreadPropertyType::GetterType GetThreadGetter_(Context &self);

		static ProxyQueue::AddCallbackType GetQueueAddCallback_(Context &self, bool isLowPriority);

		static ProxyQueue::RemoveCallbackType GetQueueRemoveCallback_(Context &self, bool isLowPriority);

		Object &thread_;
		mutable QueueScope queueScope_;
		QueueScope lowPriorityQueueScope_;
	};
}
