// not-std.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <array>

// TODO: Reference additional headers your program requires here.


namespace not_std {
	template <typename T, T value>
	struct integral_constant {
		inline constexpr static T value = value;
	};

	template <typename T>
	struct type_wrapper {
		using type = T;
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
	struct if_type<true, T, U> : type_wrapper<T> {};

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
	struct remove_const<Type const> : type_wrapper<Type> {};

	template <typename Type>
	using remove_const_t = typename remove_const<Type>::type;

	template <typename Type>
	struct remove_volatile : type_wrapper<Type> {};

	template <typename Type>
	struct remove_volatile<Type volatile> : type_wrapper<Type> {};

	template <typename Type>
	using remove_volatile_t = typename remove_volatile<Type>::type;

	template <typename Type>
	struct remove_cv : type_wrapper<typename remove_volatile_t<typename remove_const_t<Type>>> {};

	template <typename Type>
	using remove_cv_t = remove_cv<Type>::type;

	template <typename... Types>
	struct type_pack {};

	template <std::size_t idx, typename Type>
	struct get_tp : type_wrapper<Type> {};

	template <std::size_t idx, typename... Types>
	struct get_tp<idx, type_pack<Types...>> : type_wrapper<void> {};

	template <std::size_t idx, typename First, typename... Rest>
	struct get_tp<idx, type_pack<First, Rest...>> : get_tp<idx - 1, type_pack<Rest...>> {};

	template <typename First, typename... Rest>
	struct get_tp<0, type_pack<First, Rest...>> : type_wrapper<First> {};

	template <std::size_t idx, typename Type>
	using get_tp_t = typename get_tp<idx, Type>::type;

	template <typename T, typename U>
	struct concat_tp : type_wrapper<void> {};

	template <typename... Types1, typename... Types2>
	struct concat_tp<type_pack<Types1...>, type_pack<Types2...>> : type_wrapper<type_pack<Types1..., Types2...>> {};

	template <typename T, typename U>
	using concat_tp_t = typename concat_tp<T, U>::type;

	template <typename T, typename U>
	struct concat_tp_tail;

	template <typename U, typename... Types>
	struct concat_tp_tail<type_pack<Types...>, U> : concat_tp<type_pack<Types...>, type_pack<U>> {};

	template <typename T, typename U>
	using concat_tp_tail_t = typename concat_tp_tail<T, U>::type;

	template <typename T, typename U>
	struct concat_tp_head;

	template <typename U, typename... Types>
	struct concat_tp_head<U, type_pack<Types...>> : concat_tp<type_pack<U>, type_pack<Types...>> {};

	template <typename T, typename U>
	using concat_tp_head_t = typename concat_tp_head<T, U>::type;

	template <typename T>
	struct flatten_tp : type_wrapper<T> {};

	template <typename T>
	struct is_tp : false_type {};

	template <typename... Types>
	struct is_tp<type_pack<Types...>> : true_type {};

	template <typename Type>
	inline constexpr bool is_tp_v = is_tp<Type>::value;

	template <typename First, typename... Rest>
	struct flatten_tp<type_pack<First, Rest...>> : type_wrapper<
		 if_type_t<is_tp_v<typename flatten_tp<First>::type>,
			concat_tp_t<typename flatten_tp<First>::type, typename flatten_tp<type_pack<Rest...>>::type>,
			concat_tp_head_t<typename flatten_tp<First>::type, typename flatten_tp<type_pack<Rest...>>::type>>> {};

	template <typename Type>
	using flatten_tp_t = typename flatten_tp<Type>::type;

	template <template<typename, typename> typename Op, typename... Types>
	struct unary_right_fold : type_wrapper<void> {};

	template <template<typename, typename> typename Op, typename First, typename... Rest>
	struct unary_right_fold<Op, First, Rest...> : Op<First, typename unary_right_fold<Op, Rest...>::type> {};

	template <template<typename, typename> typename Op, typename First, typename Second>
	struct unary_right_fold<Op, First, Second> : Op<First, Second> {};

	template <typename... Types>
	using concat_all_tp_t = typename unary_right_fold<concat_tp, Types...>::type;

	template <typename... Types>
	struct concat_all_tp : type_wrapper<concat_all_tp_t<Types...>> {};

	template <std::size_t splitAt, typename Lhs, typename Rhs>
	struct split_impl;

	template <typename Lhs, typename Rhs>
	struct split_impl<0, Lhs, Rhs> : type_wrapper<type_pack<Lhs, Rhs>> {};

	template <std::size_t splitAt, typename RhsFirst, typename... LhsTypes, typename... RhsRest>
	struct split_impl<splitAt, type_pack<LhsTypes...>, type_pack<RhsFirst, RhsRest...>> : split_impl<splitAt - 1, type_pack<LhsTypes..., RhsFirst>, type_pack<RhsRest...>> {};

	template <std::size_t splitAt, typename Type>
	struct split_tp;

	template <std::size_t splitAt, typename... Types>
	struct split_tp<splitAt, type_pack<Types...>> : split_impl<splitAt, type_pack<>, type_pack<Types...>> {};

	template <std::size_t splitAt, typename Type>
	using split_tp_t = typename split_tp<splitAt, Type>::type;

	template <typename Type>
	struct is_non_cv_pointer : false_type {};

	template <typename Type>
	struct is_non_cv_pointer<Type*> : true_type {};

	template <typename Type>
	inline constexpr bool is_non_cv_pointer_v = is_non_cv_pointer<Type>::value;

	template <typename Type>
	struct remove_pointer_impl : type_wrapper<Type> {};

	template <typename Type>
	struct remove_pointer_impl<Type*> : type_wrapper<Type> {};

	template <typename Type>
	using remove_pointer_t = if_type_t<is_non_cv_pointer_v<remove_cv_t<Type>>, typename remove_pointer_impl<remove_cv_t<Type>>::type, Type>;

	template <typename Type>
	struct remove_pointer : type_wrapper<remove_pointer_t<Type>> {};

	template <typename Type>
	struct remove_extent : type_wrapper<Type> {};

	template <typename Type>
	struct remove_extent<Type[]> : type_wrapper<Type> {};

	template <typename Type, std::size_t size>
	struct remove_extent<Type[size]> : type_wrapper<Type> {};

	template <typename Type>
	using remove_extent_t = typename remove_extent<Type>::type;

	template <typename Type, template<typename, bool> typename recursive>
	struct remove_all_extent_recr_impl : recursive<Type, true> {};

	template <typename Type, template<typename, bool> typename recursive>
	struct remove_all_extent_recr_impl<Type[], recursive> : recursive<Type, false> {};

	template <typename Type, template<typename, bool> typename recursive, std::size_t size>
	struct remove_all_extent_recr_impl<Type[size], recursive> : recursive<Type, false> {};

	template <typename Type, bool isBase>
	struct remove_all_extent_impl : remove_all_extent_recr_impl<Type, remove_all_extent_impl> {};

	template <typename Type>
	struct remove_all_extent_impl<Type, true> : type_wrapper<Type> {};

	template <typename Type>
	using remove_all_extent = remove_all_extent_impl<Type, false>;

	template <typename Type>
	using remove_all_extent_t = typename remove_all_extent<Type>::type;

	template <typename Type>
	struct remove_extent_extended : remove_extent<Type> {};

	template <typename Type, std::size_t size>
	struct remove_extent_extended<std::array<Type, size>> : type_wrapper<Type> {};

	template <typename Type>
	using remove_extent_extended_t = typename remove_extent_extended<Type>::type;

	template <typename Type, bool isBase>
	struct remove_all_extent_extended_impl : remove_all_extent_recr_impl<Type, remove_all_extent_extended_impl> {};

	template <typename Type>
	struct remove_all_extent_extended_impl<Type, true> : type_wrapper<Type> {};

	template <typename Type, bool isBase, std::size_t size>
	struct remove_all_extent_extended_impl<std::array<Type, size>, isBase> : remove_all_extent_recr_impl<Type, remove_all_extent_extended_impl> {};

	template <typename Type,  std::size_t size>
	struct remove_all_extent_extended_impl<std::array<Type, size>, true> : remove_all_extent_recr_impl<Type, remove_all_extent_extended_impl> {};

	template <typename Type>
	using remove_all_extent_extended = remove_all_extent_extended_impl<Type, false>;

	template <typename Type>
	using remove_all_extent_extended_t = typename remove_all_extent_extended<Type>::type;

	template <typename ...Types>
	using void_t = void;

	template <typename Type, typename = void>
	struct is_well_formed_impl : false_type {};

	template <typename Type>
	struct is_well_formed_impl<Type, void_t<Type>> : true_type {};

	template <typename Type>
	struct is_well_formed : is_well_formed_impl<Type> {};

	template <typename Type>
	inline constexpr bool is_well_formed_v = is_well_formed<Type>::value;

	template <typename Type>
	inline constexpr bool is_unbounded_array_v = false;

	template <typename Type>
	inline constexpr bool is_unbounded_array_v<Type[]> = true;


	template <typename Type>
	inline constexpr bool is_bounded_array_v = false;

	template <typename Type, std::size_t Size>
	inline constexpr bool is_bounded_array_v<Type[Size]> = true;

	template <typename Type>
	inline constexpr bool is_array_v = is_bounded_array_v<Type> || is_unbounded_array_v<Type>;

	template <typename Type>
	struct is_unbound_array : bool_constant<is_unbounded_array_v<Type>> {};

	template <typename Type>
	struct is_bounded_array : bool_constant<is_bounded_array_v<Type>> {};

	template <typename Type>
	struct is_array : bool_constant<is_array_v<Type>> {};

	template <typename Type>
	inline constexpr bool is_lvalue_reference_v = false;

	template <typename Type>
	inline constexpr bool is_lvalue_reference_v<Type&> = true;

	template <typename Type>
	struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<Type>> {};
	
	template <typename Type>
	inline constexpr bool is_rvalue_reference_v = false;

	template <typename Type>
	inline constexpr bool is_rvalue_reference_v<Type&&> = true;

	template <typename Type>
	struct is_rvalue_reference : bool_constant<is_rvalue_reference_v<Type>> {};

	template <typename Type>
	inline constexpr bool is_reference_v = is_lvalue_reference_v<Type> || is_rvalue_reference_v<Type>;

	template <typename Type>
	struct is_reference : bool_constant<is_lvalue_reference_v<Type>> {};

	template <typename Type>
	inline constexpr bool always_false = false;

	template <typename Type>
	Type && declval() noexcept {
		static_assert(always_false<Type>, "DO NOT CALL declval()");
	}

	template <typename Type, typename = void>
	struct add_reference_impl {
		using lvref_type = Type;
		using rvref_type = Type;
	};

	template <typename Type>
	struct add_reference_impl<Type, void_t<Type>> {
		using lvref_type = Type &;
		using rvref_type = Type &&;
	};

	template <typename Type>
	using add_lvalue_reference_t = typename add_reference_impl<Type>::lvref_type;

	template <typename Type>
	struct add_lvalue_reference : type_wrapper<add_lvalue_reference_t<Type>> {};
	
	template <typename Type>
	using add_rvalue_reference_t = typename add_reference_impl<Type>::rvref_type;

	template <typename Type>
	struct add_rvalue_reference : type_wrapper<add_rvalue_reference_t<Type>> {};
};

