#include"type_traits"
template<class T>
void f(T a, typename alpaca::type_identity<T>::type b){};
void test_type_identity()
{
	f(1.0, 1);
}

void test_integral_constant()
{
	typedef alpaca::integral_constant<int, 2> two_t;
	typedef alpaca::integral_constant<int, 4> four_t;
	static_assert(two_t::value * 2 == four_t::value,"2*2 != 4");
	enum class my_e {
		e1,
		e2
	};
	typedef alpaca::integral_constant<my_e, my_e::e1> my_e_e1;
	typedef alpaca::integral_constant<my_e, my_e::e2> my_e_e2;
	static_assert(alpaca::is_same<my_e_e2, my_e_e2>::value,
		"my_e_e2 != my_e_e2");

}

void test_remove_cv()
{
	typedef alpaca::remove_cv<const int>::type type1;
	typedef alpaca::remove_cv<volatile int>::type type2;
	typedef alpaca::remove_cv<const volatile int>::type type3;
	typedef alpaca::remove_cv<const volatile int*>::type type4;
	typedef alpaca::remove_cv<int * const volatile>::type type5;

	static_assert(alpaca::is_same<int, type1>::value, "fail type1");
	static_assert(alpaca::is_same<int, type2>::value, "fail type2");
	static_assert(alpaca::is_same<int, type3>::value, "fail type3");
	//从 const volatile int * 移除 const/volatile 不修改该类型，因为该指针自身既非 const 亦非 volatile 
	static_assert(alpaca::is_same<const volatile int*, type4>::value, "fail type4");
	static_assert(alpaca::is_same<int*, type5>::value, "fail type5");
}