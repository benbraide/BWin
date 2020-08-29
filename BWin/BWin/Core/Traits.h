#pragma once

#include <functional>

namespace Win::Core::Traits{
	struct NotAType;

	template <class T, bool IsScalar>
	struct Copy_{
		using Type = T;
	};

	template <class T>
	struct Copy_<T, false>{
		using Type = const T &;
	};

	template <class T>
	struct Copy{
		using Type = typename Copy_<T, std::is_scalar_v<T>>::Type;
	};

	template <class... TList>
	struct TypeList{
		template <typename... T>
		struct Pack_;

		using Pack = Pack_<TList...>;

		static const std::size_t Count = sizeof...(TList);

		template <std::size_t Index, bool IsOutOfBounds>
		struct At_{
			using Type = typename std::tuple_element<Index, std::tuple<TList...>>::type;
		};

		template <std::size_t Index>
		struct At_<Index, true>{
			using Type = NotAType;
		};

		template <std::size_t Index>
		struct At{
			using Type = typename At_<Index, (Count <= Index)>::Type;
		};

		using FirstType = typename At<0>::Type;
		using LastType = typename At<(Count - 1)>::Type;

		template <class T, class... IndexTList>
		struct IndexOf_;

		template <class T, class... IndexTList>
		struct IndexOf_<T, T, IndexTList...> : std::integral_constant<std::size_t, 0>{};

		template <class T, class U, class... IndexTList>
		struct IndexOf_<T, U, IndexTList...>
			: std::integral_constant<std::size_t, (1 + IndexOf_<T, IndexTList...>::template value)>{};

		template <class T>
		struct IndexOf{
			static constexpr std::size_t Value = IndexOf_<T, TList...>::template value;
		};
	};

	template <class ReturnT, class... ArgsT>
	struct FunctionContainer{
		using ReturnType = ReturnT;
		using Args = TypeList<ArgsT...>;

		using FunctionType = ReturnType(*)(ArgsT...);
		using StdFunctionType = std::function<ReturnType(ArgsT...)>;

		template <typename WithReturnT>
		using StdFunctionTypeWith = std::function<WithReturnT(ArgsT...)>;
	};

	template <class T>
	struct Function : FunctionContainer<NotAType>{
		using BaseType = FunctionContainer<NotAType>;
		using QualifiedType = T;

		static const bool IsValid = false;
		static const bool IsRaw = false;
		static const bool IsStatic = false;
		static const bool IsPointer = false;
		static const bool IsConstant = false;

		static auto Cast(const T &object){
			return object;
		}
	};

	template<>
	struct Function<void> : public FunctionContainer<NotAType>{
		using BaseType = FunctionContainer<NotAType>;
		using QualifiedType = void;

		static const bool IsValid = false;
		static const bool IsRaw = false;
		static const bool IsStatic = false;
		static const bool IsPointer = false;
		static const bool IsConstant = false;

		static auto Cast(){}
	};

	template<class ReturnT, class... ArgsT>
	struct Function<ReturnT(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = true;
		static const bool IsPointer = false;
		static const bool IsConstant = false;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ReturnT, class... ArgsT>
	struct Function<ReturnT(*)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(*)(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = true;
		static const bool IsPointer = true;
		static const bool IsConstant = false;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ClassT, class ReturnT, class... ArgsT>
	struct Function<ReturnT(ClassT:: *)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(ClassT:: *)(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = false;
		static const bool IsPointer = true;
		static const bool IsConstant = false;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ClassT, class ReturnT, class... ArgsT>
	struct Function<ReturnT(ClassT:: *)(ArgsT...) const> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(ClassT:: *)(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = false;
		static const bool IsPointer = true;
		static const bool IsConstant = true;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ReturnT, class... ArgsT>
	struct Function<std::function<ReturnT(ArgsT...)>> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = std::function<ReturnT(ArgsT...)>;

		static const bool IsValid = true;
		static const bool IsRaw = false;
		static const bool IsStatic = false;
		static const bool IsPointer = false;
		static const bool IsConstant = false;

		static auto Cast(const QualifiedType &object){
			return object;
		}
	};

	template <class T>
	struct Functor : Function<decltype(&T::operator ())>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(ArgsT...)> : Function<ReturnT(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(*)(ArgsT...)> : Function<ReturnT(*)(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<std::function<ReturnT(ArgsT...)>> : Function<std::function<ReturnT(ArgsT...)>>{};

	template <class ClassT, class ReturnT, class... ArgsT>
	struct Functor<ReturnT(ClassT:: *)(ArgsT...)> : Function<ReturnT(ClassT:: *)(ArgsT...)>{};

	template <class ClassT, class ReturnT, class... ArgsT>
	struct Functor<ReturnT(ClassT:: *)(ArgsT...) const> : Function<ReturnT(ClassT:: *)(ArgsT...) const>{};

	struct FunctionCast{
		template <class T>
		static auto Get(const T &object){
			return static_cast<typename Functor<T>::StdFunctionType>(object);
		}
	};

	template <class ReturnT>
	struct FunctionReturnCast{
		template <class T, bool IsSameType>
		struct Internal_;

		template <class T>
		struct Internal_<T, false>{
			static typename Functor<T>::template StdFunctionTypeWith<ReturnT> Get(const T &object, typename Copy<ReturnT>::Type value){
				return [=, callback = FunctionCast::Get(object)](auto... args){
					callback(args...);
					return value;
				};
			}
		};

		template <class T>
		struct Internal_<T, true>{
			static typename Functor<T>::template StdFunctionTypeWith<ReturnT> Get(const T &object, typename Copy<ReturnT>::Type value){
				return FunctionCast::Get(object);
			}
		};

		template <class T>
		static auto Get(const T &object, typename Copy<ReturnT>::Type value = ReturnT()){
			return Internal_<T, std::is_same_v<ReturnT, typename Functor<T>::ReturnType>>::template Get(object, value);
		}
	};

	template <>
	struct FunctionReturnCast<void>{
		template <class T, bool IsSameType>
		struct Internal_;

		template <class T>
		struct Internal_<T, false>{
			static typename Functor<T>::template StdFunctionTypeWith<void> Get(const T &object){
				return [=, callback = FunctionCast::Get(object)](auto... args){
					callback(args...);
				};
			}
		};

		template <class T>
		struct Internal_<T, true>{
			static typename Functor<T>::template StdFunctionTypeWith<void> Get(const T &object){
				return FunctionCast::Get(object);
			}
		};

		template <class T>
		static auto Get(const T &object){
			return Internal_<T, std::is_same_v<void, typename Functor<T>::ReturnType>>::template Get(object);
		}
	};
}
