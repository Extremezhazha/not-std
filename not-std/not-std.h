// not-std.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.


namespace not_std {
	template <typename T, T value>
	struct integral_constant {
		inline constexpr static T value = value;
	};

	template <bool value>
	using bool_constant = integral_constant<bool, value>;

	using true_type = bool_constant<true>;
	using false_type = bool_constant<false>;

	template <typename T, typename U>
	struct is_same : false_type {};

	template <typename T>
	struct is_same<T, T> : true_type {};

	template <typename T, typename U>
	inline constexpr bool is_same_v = is_same<T, U>::value;

	template <bool cond, typename T, typename U>
	struct if_type {
		using type = U;
	};

	template <typename T, typename U>
	struct if_type<true, T, U> {
		using type = T;
	};

	template <bool cond, typename T, typename U>
	using if_type_t = typename if_type<cond, T, U>::type;

	template <typename... Types>
	struct conjunction_impl : true_type {};

	template <typename... Rest>
	struct conjunction_impl<true_type, Rest...> : conjunction_impl<Rest...> {};

	template <typename... Rest>
	struct conjunction_impl<false_type, Rest...> : false_type {};

	template <typename... Types>
	struct conjunction : conjunction_impl<bool_constant<Types::value>...> {};

	template <typename... Types>
	inline constexpr bool conjunction_v = conjunction<Types...>::value;


	template <typename... Types>
	struct disjuntion_impl : false_type {};

	template <typename... Rest>
	struct disjuntion_impl<true_type, Rest...> : true_type {};

	template <typename... Rest>
	struct disjuntion_impl<false_type, Rest...> : disjuntion_impl<Rest...> {};

	template <typename... Types>
	struct disjuntion : disjuntion_impl<bool_constant<Types::value>...> {};

	template <typename... Types>
	inline constexpr bool disjuntion_v = disjuntion<Types...>::value;

	template <typename Type>
	struct remove_const {
		using type = Type;
	};

	template <typename Type>
	struct remove_const<Type const> {
		using type = Type;
	};

	template <typename Type>
	using remove_const_t = typename remove_const<Type>::type;

	template <typename Type>
	struct remove_volatile {
		using type = Type;
	};

	template <typename Type>
	struct remove_volatile<Type volatile> {
		using type = Type;
	};

	template <typename Type>
	using remove_volatile_t = typename remove_volatile<Type>::type;

	template <typename Type>
	struct remove_cv {
		using type = typename remove_volatile_t<typename remove_const_t<Type>>;
	};

	template <typename Type>
	using remove_cv_t = remove_cv<Type>::type;

	template <typename... Types>
	struct type_pack {};

	template <std::size_t idx, typename Type>
	struct get_tp {
		using type = Type;
	};

	template <std::size_t idx, typename... Types>
	struct get_tp<idx, type_pack<Types...>> {
		using type = void;
	};

	template <std::size_t idx, typename First, typename... Rest>
	struct get_tp<idx, type_pack<First, Rest...>> : get_tp<idx - 1, type_pack<Rest...>> {};

	template <typename First, typename... Rest>
	struct get_tp<0, type_pack<First, Rest...>> {
		using type = First;
	};

	template <std::size_t idx, typename Type>
	using get_tp_t = typename get_tp<idx, Type>::type;
};