#pragma once

#include <unordered_map>

#include "../Thread/ThreadContext.h"

#include "EventState.h"

namespace Win::Event{
	namespace Exception{
		class InvalidId : public Core::Exception::Base{
		public:
			InvalidId()
				: Base("Invalid ID: Cannot access event handler with specified ID."){}
		};

		class UnsupportedType : public Core::Exception::Base{
		public:
			UnsupportedType()
				: Base("Specified event type is not supported."){}
		};
	}

	class Target;
	class DefaultObject;

	class Handler{
	public:
		virtual ~Handler() = default;
	};

	template <class ObjectT>
	class ParameterTypedHandler : public Handler{
	public:
		using ObjectType = ObjectT;

		virtual ~ParameterTypedHandler() = default;
		
		virtual void Call(ObjectT &object) = 0;
	};

	template <class ReturnT, class ObjectT>
	class TypedHandler : public ParameterTypedHandler<ObjectT>{
	public:
		using ReturnType = ReturnT;
		using ObjectType = typename ParameterTypedHandler<ObjectT>::ObjectType;

		using CallbackType = std::function<ReturnT(ObjectT &)>;

		template <typename T>
		struct Caller{
			static void Call(ObjectT &object, const CallbackType &value){
				object.Result = value(object);
			}
		};

		template <>
		struct Caller<void>{
			static void Call(ObjectT &object, const CallbackType &value){
				value(object);
			}
		};

		explicit TypedHandler(const CallbackType &value)
			: value_(value){}

		virtual void Call(ObjectT &object) override{
			Caller<ReturnT>::template Call(object, value_);
		}

	protected:
		CallbackType value_;
	};

	class Bucket{
	public:
		using IdType = unsigned __int64;

		explicit Bucket(bool isDefault)
			: isDefault_(isDefault){}

		virtual ~Bucket() = default;

		virtual bool IsDefault() const{
			return isDefault_;
		}

		virtual void Remove(IdType id, bool isDefault) = 0;

	protected:
		bool isDefault_;
	};

	template <class ObjectT>
	class TypedBucket : public Bucket{
	public:
		using ObjectType = ObjectT;
		using HandlerType = std::shared_ptr<ParameterTypedHandler<ObjectT>>;
		using HandlerListType = std::list<std::pair<IdType, HandlerType>>;

		using Bucket::Bucket;

		virtual void Remove(IdType id, bool isDefault) override{
			auto &handlers = (isDefault ? defaultHandlers_ : handlers_);
			if (handlers.empty())
				throw Exception::InvalidId();

			for (auto it = handlers.begin(); it != handlers.end(); ++it){
				if (it->first == id){
					handlers.erase(it);
					return;
				}
			}

			throw Exception::InvalidId();
		}

		template <typename ReturnT>
		IdType Add(const std::function<ReturnT(ObjectT &)> &callback, bool isDefault){
			auto &handlers = (isDefault ? defaultHandlers_ : handlers_);
			handlers.push_back(std::make_pair<IdType, HandlerType>(IdType(), std::make_shared<TypedHandler<ReturnT, ObjectT>>(callback)));
			return (handlers.rbegin()->first = reinterpret_cast<IdType>(&*handlers.rbegin()));
		}

		template <typename ReturnT>
		IdType Add(const std::function<ReturnT(const ObjectT &)> &callback, bool isDefault){
			return Add<ReturnT>([=](ObjectT &e){
				callback(e);
			});
		}

		virtual void Call(ObjectT &object, bool isDefault){
			auto handlers = (isDefault ? defaultHandlers_ : handlers_);
			for (auto &hnadler : handlers){
				hnadler.second->Call(object);
				if (object.States | State::StopListening)
					Remove(hnadler.first, isDefault);

				if (object.States | State::StopPropagation)
					break;//Propagation stopped
			}
		}

	protected:
		HandlerListType handlers_;
		HandlerListType defaultHandlers_;
	};

	struct DefaultDispatcher{
		static std::pair<LRESULT, StateValueType> Trigger(Target &owner);
	};

	template <class TargetT>
	class Collection : public Thread::Context{
	public:
		using TargetType = TargetT;
		using IdType = Bucket::IdType;
		using BucketType = std::shared_ptr<Bucket>;

		explicit Collection(TargetT &owner)
			: owner_(owner){}

		template <typename CallbackT>
		IdType operator +=(const CallbackT &callback){
			return Add_(callback, false);
		}

		void operator -=(IdType id){
			Remove_(id, false);
		}

		template <typename ObjectT>
		void Dispatch(ObjectT &object) const{
			Use([&]{
				auto bucket = GetBucket_<ObjectT>();
				bucket->Call(object, false);

				if (bucket.get() == defaultBucket_.get() && !(object.States | State::StopPropagation)){
					auto resultInfo = DefaultDispatcher::Trigger(owner_);//Dispatch default event object
					if ((resultInfo.second & State::ValueSet) != 0)
						object.Result = resultInfo.first;//Override result

					if ((resultInfo.second & State::PreventDefualt) != 0)
						object.States += State::PreventDefualt;//Forward default prevention
				}

				object.DoDefault();
			});
		}
		
		template <typename ObjectT>
		void DispatchDefault(ObjectT &object) const{
			Use([&]{
				GetBucket_<ObjectT>()->Call(object, true);
			});
		}

		template <typename ObjectT, typename... ArgsTypes>
		std::pair<LRESULT, StateValueType> Trigger(ArgsTypes &&... args) const{
			return TriggerAs<LRESULT, ObjectT>(args...);
		}

		template <typename ReturnT, typename ObjectT, typename... ArgsTypes>
		std::pair<ReturnT, StateValueType> TriggerAs(ArgsTypes &&... args) const{
			ObjectT object(owner_, std::forward<ArgsTypes>(args)...);
			Dispatch(object);
			return std::make_pair<ReturnT, StateValueType>(object.Result, object.States);
		}

	protected:
		template <typename T>
		std::shared_ptr<TypedBucket<std::remove_reference_t<T>>> GetBucket_() const{
			for (auto bucket : buckets_){
				auto compatible = std::dynamic_pointer_cast<TypedBucket<std::remove_reference_t<T>>>(bucket);
				if (compatible)
					return compatible;
			}

			throw Exception::UnsupportedType();
		}

		template <typename CallbackT>
		IdType Add_(const CallbackT &callback, bool isDefault){
			using ReturnType = typename Core::Traits::Functor<CallbackT>::ReturnType;
			using ObjectType = typename Core::Traits::Functor<CallbackT>::Args::template At<0>::Type;
			using BaseObjectType = std::remove_cv_t<std::conditional_t<std::is_same_v<ObjectType, Core::Traits::NotAType>, DefaultObject, ObjectType>>;

			return Use([&]{
				auto bucket = GetBucket_<BaseObjectType>();
				auto id = dynamic_cast<TypedBucket<std::remove_reference_t<BaseObjectType>> *>(bucket.get())->Add<ReturnType>(callback, isDefault);

				refs_[id] = bucket;
				return id;
			});
		}

		void Remove_(IdType id, bool isDefault){
			Use([&]{
				if (refs_.empty())
					throw Exception::InvalidId();

				auto it = refs_.find(id);
				if (it == refs_.end())
					throw Exception::InvalidId();

				it->second->Remove(id, isDefault);
				refs_.erase(it);
			});
		}

		TargetT &owner_;
		BucketType defaultBucket_;
		std::list<BucketType> buckets_;
		std::unordered_map<IdType, BucketType> refs_;
	};

	template <class OwnerT>
	class OwnedCollection : public Collection<OwnerT>{
	public:
		using OwnerType = OwnerT;
		using BaseType = Collection<OwnerT>;

		using IdType = typename BaseType::IdType;
		using BucketType = typename BaseType::BucketType;

		using BaseType::BaseType;

	protected:
		friend OwnerT;

		template <typename ObjectT>
		void AddBucket_(bool isDefault){
			AddBucket_(std::make_shared<TypedBucket<ObjectT>>(isDefault));
		}

		void AddBucket_(BucketType bucket){
			BaseType::buckets_.push_back(bucket);
			if (bucket->IsDefault()){
				BaseType::defaultBucket_ = bucket;
				try{
					BaseType::template GetBucket_<DefaultObject>();
				}
				catch (const Exception::UnsupportedType &){
					AddBucket_<DefaultObject>(false);
				}
			}
		}

		template <typename CallbackT>
		IdType AddDefault_(const CallbackT &callback){
			return BaseType::Add_(callback, true);
		}

		void RemoveDefault_(IdType id){
			BaseType::Remove_(id, true);
		}
	};
}
