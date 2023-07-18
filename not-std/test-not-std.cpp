#include "not-std.h"


void testIsSame() {
	static_assert(not_std::is_same_v<int, int>);
	static_assert(!not_std::is_same_v<int, double>);
	static_assert(!not_std::is_same_v<double, int>);
	static_assert(!not_std::is_same_v<void, int>);
	static_assert(!not_std::is_same_v<int, void>);
}

void testIntegralAndBooleanContants() {
	static_assert(not_std::true_type::value);
	static_assert(!not_std::false_type::value);

	static_assert(not_std::integral_constant<int, 0>::value != 1000);
	static_assert(not_std::integral_constant<int, 1000>::value == 1000);
}

void testIfType() {
	static_assert(not_std::is_same_v<not_std::if_type_t<true, int, double>, int>);
	static_assert(not_std::is_same_v<not_std::if_type_t<false, int, double>, double>);
}

void testConjunction() {
	static_assert(not_std::conjunction_v<>);
	static_assert(not_std::conjunction_v<not_std::true_type>);
	static_assert(!not_std::conjunction_v<not_std::false_type>);
	static_assert(not_std::conjunction_v<not_std::true_type, not_std::true_type>);
	static_assert(!not_std::conjunction_v<not_std::true_type, not_std::false_type>);
	static_assert(!not_std::conjunction_v<not_std::false_type, not_std::true_type>);
	static_assert(!not_std::conjunction_v<not_std::false_type, not_std::false_type>);
	static_assert(not_std::conjunction_v<not_std::true_type, not_std::true_type, not_std::true_type>);
	static_assert(!not_std::conjunction_v<not_std::true_type, not_std::true_type, not_std::false_type>);

	static_assert(not_std::conjunction_v<not_std::true_type, std::true_type>);
	static_assert(!not_std::conjunction_v<not_std::false_type, std::true_type>);
}

void testDisjunction() {
	static_assert(!not_std::disjuntion_v<>);
	static_assert(not_std::disjuntion_v<not_std::true_type>);
	static_assert(!not_std::disjuntion_v<not_std::false_type>);
	static_assert(not_std::disjuntion_v<not_std::true_type, not_std::true_type>);
	static_assert(not_std::disjuntion_v<not_std::true_type, not_std::false_type>);
	static_assert(not_std::disjuntion_v<not_std::true_type, not_std::true_type, not_std::true_type>);
	static_assert(not_std::disjuntion_v<not_std::true_type, not_std::true_type, not_std::false_type>);
	static_assert(not_std::disjuntion_v<not_std::false_type, not_std::false_type, not_std::true_type>);

	static_assert(not_std::disjuntion_v<not_std::true_type, std::true_type>);
	static_assert(not_std::disjuntion_v<not_std::false_type, std::true_type>);
	static_assert(!not_std::disjuntion_v<not_std::false_type, std::false_type>);
}

void testRemoveConst() {
	static_assert(not_std::is_same_v<int, not_std::remove_const_t<int>>);

	static_assert(not_std::is_same_v<int, not_std::remove_const_t<int const>>);
	static_assert(not_std::is_same_v<int, not_std::remove_const_t<const int>>);

	static_assert(not_std::is_same_v<int volatile, not_std::remove_const_t<int const volatile>>);
	static_assert(not_std::is_same_v<int volatile, not_std::remove_const_t<int volatile const>>);
	static_assert(not_std::is_same_v<int volatile, not_std::remove_const_t<const int volatile>>);
}

void testRemoveVolatile() {
	static_assert(not_std::is_same_v<int, not_std::remove_volatile_t<int>>);

	static_assert(not_std::is_same_v<int, not_std::remove_volatile_t<int volatile>>);
	static_assert(not_std::is_same_v<int, not_std::remove_volatile_t<volatile int>>);

	static_assert(not_std::is_same_v<int const, not_std::remove_volatile_t<int const volatile>>);
	static_assert(not_std::is_same_v<int const, not_std::remove_volatile_t<int volatile const>>);
	static_assert(not_std::is_same_v<int const, not_std::remove_volatile_t<const int volatile>>);
}

void testRemoveCV() {
	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<int>>);

	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<int volatile>>);
	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<int const>>);

	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<int const volatile>>);
	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<int volatile const>>);
	static_assert(not_std::is_same_v<int, not_std::remove_cv_t<const int volatile>>);
}

void testTypePack() {
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, int>>);
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, not_std::type_pack<int>>>);
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, not_std::type_pack<int, double>>>);

	static_assert(not_std::is_same_v<int, not_std::get_tp_t<1, not_std::type_pack<double, int, double>>>);

	static_assert(not_std::is_same_v<void, not_std::get_tp_t<0, not_std::type_pack<>>>);
	static_assert(not_std::is_same_v<void, not_std::get_tp_t<1, not_std::type_pack<int>>>);
}