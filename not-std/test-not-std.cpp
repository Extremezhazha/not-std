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

void testGetTypePack() {
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, int>>);
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, not_std::type_pack<int>>>);
	static_assert(not_std::is_same_v<int, not_std::get_tp_t<0, not_std::type_pack<int, double>>>);

	static_assert(not_std::is_same_v<int, not_std::get_tp_t<1, not_std::type_pack<double, int, double>>>);

	static_assert(not_std::is_same_v<void, not_std::get_tp_t<0, not_std::type_pack<>>>);
	static_assert(not_std::is_same_v<void, not_std::get_tp_t<1, not_std::type_pack<int>>>);
}

void testIsTypePack() {
	static_assert(!not_std::is_tp_v<int>);

	static_assert(not_std::is_tp_v<not_std::type_pack<>>);

	static_assert(not_std::is_tp_v<not_std::type_pack<int>>);

	static_assert(not_std::is_tp_v<not_std::type_pack<int, int>>);
}

void testConcatTypePack() {
	static_assert(not_std::is_same_v<not_std::type_pack<>, not_std::concat_tp_t<not_std::type_pack<>, not_std::type_pack<>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::concat_tp_t<not_std::type_pack<int>, not_std::type_pack<>>>);
	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::concat_tp_t<not_std::type_pack<>, not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, int>, not_std::concat_tp_t<not_std::type_pack<int>, not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<
		not_std::type_pack<int, double, char, float>, 
		not_std::concat_tp_t<not_std::type_pack<int, double>, not_std::type_pack<char, float>>>);

}

void testConcatTypePackTail() {
	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::concat_tp_tail_t<not_std::type_pack<>, int>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, int>, not_std::concat_tp_tail_t<not_std::type_pack<int>, int>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, not_std::type_pack<int>>, not_std::concat_tp_tail_t<not_std::type_pack<int>, not_std::type_pack<int>>>);
}

void testConcatTypePackHead() {
	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::concat_tp_head_t<int, not_std::type_pack<>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, int>, not_std::concat_tp_head_t<int, not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<not_std::type_pack<int>, int>, not_std::concat_tp_head_t<not_std::type_pack<int>, not_std::type_pack<int>>>);
}

void testFlattenTypePack() {
	static_assert(not_std::is_same_v<int, not_std::flatten_tp_t<int>>);

	static_assert(not_std::is_same_v<not_std::type_pack<>, not_std::flatten_tp_t<not_std::type_pack<>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::flatten_tp_t<not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int>, not_std::flatten_tp_t<not_std::type_pack<not_std::type_pack<int>>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, int>, not_std::flatten_tp_t<not_std::type_pack<int, not_std::type_pack<int>>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, int, int, int, int>, 
		not_std::flatten_tp_t<not_std::type_pack<int, not_std::type_pack<int>, not_std::type_pack<not_std::type_pack<int, int>, int>>>>);
}

void testConcatAllTypePack() {
	static_assert(not_std::is_same_v<not_std::type_pack<int, int>, not_std::concat_all_tp_t<not_std::type_pack<int>, not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, double, int>, not_std::concat_all_tp_t<not_std::type_pack<int, double>, not_std::type_pack<int>>>);

	static_assert(not_std::is_same_v<not_std::type_pack<int, double, int>, not_std::concat_all_tp_t<not_std::type_pack<int>, not_std::type_pack<double>, not_std::type_pack<int>>>);

}

void testSplitTypePack() {
	static_assert(not_std::is_same_v<
		not_std::type_pack<not_std::type_pack<>, not_std::type_pack<>>,
		not_std::split_tp_t<0, not_std::type_pack<>>
	>);

	static_assert(not_std::is_same_v<
		not_std::type_pack<not_std::type_pack<>, not_std::type_pack<int>>,
		not_std::split_tp_t<0, not_std::type_pack<int>>
	>);

	static_assert(not_std::is_same_v<
		not_std::type_pack<not_std::type_pack<int>, not_std::type_pack<int>>,
		not_std::split_tp_t<1, not_std::type_pack<int, int>>
	>);

	static_assert(not_std::is_same_v<
		not_std::type_pack<not_std::type_pack<int>, not_std::type_pack<double, int>>,
		not_std::split_tp_t<1, not_std::type_pack<int, double, int>>
	>);

	static_assert(not_std::is_same_v<
		not_std::type_pack<not_std::type_pack<int, double>, not_std::type_pack<int>>,
		not_std::split_tp_t<2, not_std::type_pack<int, double, int>>
	>);
}

void testRemovePointer() {
	static_assert(not_std::is_same_v<int, not_std::remove_pointer_t<int>>);

	static_assert(not_std::is_same_v<int const, not_std::remove_pointer_t<int const>>);
	static_assert(not_std::is_same_v<int const volatile, not_std::remove_pointer_t<int const volatile>> );

	static_assert(not_std::is_same_v<int, not_std::remove_pointer_t<int*>>);
	static_assert(not_std::is_same_v<int, not_std::remove_pointer_t<int* const>>);
	static_assert(not_std::is_same_v<int, not_std::remove_pointer_t<int* const volatile>>);
}

void testRemoveExtent() {
	static_assert(not_std::is_same_v<int, not_std::remove_extent_t<int>>);
	static_assert(not_std::is_same_v<int, not_std::remove_extent_t<int[]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_extent_t<int[3]>>);

	static_assert(not_std::is_same_v<int[3], not_std::remove_extent_t<int[][3]>>);
	static_assert(not_std::is_same_v<int[2][3][4][5], not_std::remove_extent_t<int[1][2][3][4][5]>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_extent_t<int*>>);
}

void testRemoveAllExtent() {
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int[]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int[3]>>);

	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int[][3]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int[][3][4]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_t<int[1][2][3][4][5]>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_t<int* []>>);
	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_t<int* [3]>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_t<int*>>);
}

void testRemoveExtentExtended() {
	static_assert(not_std::is_same_v<int, not_std::remove_extent_extended_t<int>>);
	static_assert(not_std::is_same_v<int, not_std::remove_extent_extended_t<int[]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_extent_extended_t<int[3]>>);

	static_assert(not_std::is_same_v<int[3], not_std::remove_extent_extended_t<int[][3]>>);
	static_assert(not_std::is_same_v<int[2][3][4][5], not_std::remove_extent_extended_t<int[1][2][3][4][5]>>);

	static_assert(not_std::is_same_v<int, not_std::remove_extent_extended_t<std::array<int, 3>>>);
	static_assert(not_std::is_same_v<std::array<int, 4>, not_std::remove_extent_extended_t<std::array<std::array<int, 4>, 3>>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_extent_extended_t<int*>>);
}

void testRemoveAllExtentExtended() {
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[3]>>);

	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[][3]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[][3][4]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[1][2][3][4][5]>>);

	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[][3][4]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<int[1][2][3][4][5]>>);

	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<int, 3>>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<std::array<int, 4>, 3>>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<std::array<std::array<int, 5>, 4>, 3>>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<int[], 3>>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<int[4], 3>>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<int, 3>[]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<int, 4>[3]>>);
	static_assert(not_std::is_same_v<int, not_std::remove_all_extent_extended_t<std::array<std::array<std::array<std::array<int, 5>[], 4>, 3>[2], 1>>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_extended_t<int* []>>);
	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_extended_t<int* [3]>>);

	static_assert(not_std::is_same_v<int*, not_std::remove_all_extent_extended_t<int*>>);
}

void testIsWellFormed() {
	static_assert(not_std::is_well_formed_v<int>);
	static_assert(not_std::is_well_formed_v<int*>);
}

void testIsBoundedArray() {
	static_assert(!not_std::is_bounded_array_v<int>);
	static_assert(!not_std::is_bounded_array_v<int[]>);
	static_assert(not_std::is_bounded_array_v<int[3]>);
}

void testIsUnboundedArray() {
	static_assert(!not_std::is_unbounded_array_v<int>);
	static_assert(not_std::is_unbounded_array_v<int[]>);
	static_assert(!not_std::is_unbounded_array_v<int[3]>);
}

void testIsArray() {
	static_assert(!not_std::is_array_v<int>);
	static_assert(not_std::is_array_v<int[]>);
	static_assert(not_std::is_array_v<int[3]>);
}

void testIsLvalueReference() {
	static_assert(!not_std::is_lvalue_reference_v<int>);
	static_assert(not_std::is_lvalue_reference_v<int&>);
	static_assert(not_std::is_lvalue_reference_v<const int &>);
	static_assert(not_std::is_lvalue_reference_v<int & const>);
	static_assert(!not_std::is_lvalue_reference_v<int &&>);
	static_assert(!not_std::is_lvalue_reference_v<const int &&>);
	static_assert(!not_std::is_lvalue_reference_v<int && const>);
}

void testIsRvalueReference() {
	static_assert(!not_std::is_rvalue_reference_v<int>);
	static_assert(!not_std::is_rvalue_reference_v<int&>);
	static_assert(!not_std::is_rvalue_reference_v<const int&>);
	static_assert(!not_std::is_rvalue_reference_v<int& const>);
	static_assert(not_std::is_rvalue_reference_v<int&&>);
	static_assert(not_std::is_rvalue_reference_v<const int&&>);
	static_assert(not_std::is_rvalue_reference_v<int&& const>);
}

void testIsReference() {
	static_assert(!not_std::is_reference_v<int>);
	static_assert(not_std::is_reference_v<int&>);
	static_assert(not_std::is_reference_v<const int&>);
	static_assert(not_std::is_reference_v<int& const>);
	static_assert(not_std::is_reference_v<int&&>);
	static_assert(not_std::is_reference_v<const int&&>);
	static_assert(not_std::is_reference_v<int&& const>);
}
struct CannotBeDeaultConstructed {
public:
	CannotBeDeaultConstructed() = delete;
	CannotBeDeaultConstructed(CannotBeDeaultConstructed&& other) = delete;
	CannotBeDeaultConstructed(CannotBeDeaultConstructed& const other) = delete;
	int someMethod();
};

void testDeclVal() {
	static_assert(not_std::is_same_v<int, decltype(not_std::declval<CannotBeDeaultConstructed>().someMethod())>);
	static_assert(not_std::is_same_v<int, decltype(std::declval<CannotBeDeaultConstructed>().someMethod())>);
	// The following line should not compile
	// not_std::declval<CannotBeDeaultConstructed>();
}

void testAddLvalueReference() {
	static_assert(not_std::is_same_v<int&, not_std::add_lvalue_reference_t<int>>);
	static_assert(not_std::is_same_v<int&, not_std::add_lvalue_reference_t<int&>>);
	static_assert(not_std::is_same_v<int&, not_std::add_lvalue_reference_t<int&&>>);
}

void testAddRvalueReference() {
	static_assert(not_std::is_same_v<int&&, not_std::add_rvalue_reference_t<int>>);
	static_assert(not_std::is_same_v<int&, not_std::add_rvalue_reference_t<int&>>);
	static_assert(not_std::is_same_v<int&&, not_std::add_rvalue_reference_t<int&&>>);
}