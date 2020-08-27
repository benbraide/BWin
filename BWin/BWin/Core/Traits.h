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

	template <class ReturnT, class... ArgsT>
	struct FunctionContainer{
		using ReturnType = ReturnT;

		using FunctionType = ReturnType(*)(ArgsT...);
		using StdFunctionType = std::function<ReturnType(ArgsT...)>;

		template <typename WithReturnT>
		using StdFunctionTypeWith = std::function<WithReturnT(ArgsT...)>;

		static const std::size_t ArgsCount = sizeof...(ArgsT);

		template <std::size_t Index, bool IsOutOfBounds>
		struct Args_{
			using Type = typename std::tuple_element<Index, std::tuple<ArgsT...>>::type;
		};

		template <std::size_t Index>
		struct Args_<Index, true>{
			using Type = NotAType;
		};

		template <std::size_t Index>
		struct Args{
			using Type = typename Args_<Index, (ArgsCount <= Index)>::Type;
		};

		using FirstArgType = typename Args<0>::Type;
		using LastArgType = typename Args<(ArgsCount - 1)>::Type;
	};

	template <class T>
	struct Function{
		using BaseType = NotAType;
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
	struct Function<void>{
		using BaseType = NotAType;
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
	struct Function<ReturnT(__stdcall)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__stdcall)(ArgsT...);

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
	struct Function<ReturnT(__fastcall)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__fastcall)(ArgsT...);

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
	struct Function<ReturnT(__vectorcall)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__vectorcall)(ArgsT...);

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

	template<class ReturnT, class... ArgsT>
	struct Function<ReturnT(__stdcall *)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__stdcall *)(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = true;
		static const bool IsPointer = true;
		static const bool IsConstant = false;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ReturnT, class... ArgsT>
	struct Function<ReturnT(__fastcall *)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__fastcall *)(ArgsT...);

		static const bool IsValid = true;
		static const bool IsRaw = true;
		static const bool IsStatic = true;
		static const bool IsPointer = true;
		static const bool IsConstant = false;

		static auto Cast(QualifiedType object){
			return static_cast<typename BaseType::StdFunctionType>(object);
		}
	};

	template<class ReturnT, class... ArgsT>
	struct Function<ReturnT(__vectorcall *)(ArgsT...)> : FunctionContainer<ReturnT, ArgsT...>{
		using BaseType = FunctionContainer<ReturnT, ArgsT...>;
		using QualifiedType = ReturnT(__vectorcall *)(ArgsT...);

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
	struct Functor<ReturnT(__stdcall)(ArgsT...)> : Function<ReturnT(__stdcall)(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(*)(ArgsT...)> : Function<ReturnT(*)(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(__stdcall *)(ArgsT...)> : Function<ReturnT(__stdcall *)(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(__fastcall *)(ArgsT...)> : Function<ReturnT(__fastcall *)(ArgsT...)>{};

	template <class ReturnT, class... ArgsT>
	struct Functor<ReturnT(__vectorcall *)(ArgsT...)> : Function<ReturnT(__vectorcall *)(ArgsT...)>{};

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
