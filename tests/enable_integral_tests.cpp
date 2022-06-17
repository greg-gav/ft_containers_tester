#include "enable_integral_tests.hpp"

extern std::string test_name;

/* the return type (bool) is only valid if T is an integral type */
/* std template */
template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i) { return bool(i % 2); }
/* ft template */
template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type
is_odd_ft (T i) { return bool(i % 2); }

void test_enableif_integral(long count){
	//print job name
	test_name = "-ENABLE IF IS INTEGRAL TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		is_odd(i);
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		is_odd_ft(i);
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}
