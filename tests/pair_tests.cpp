#include "pair_tests.hpp"

extern std::string test_name;

void test_pair_construction(long count){
	//print job name
	test_name = "-PAIR CONSTRUCTION TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::pair<int, int> p1(42, 42);
		std::pair<int, int> p2;
		p2 = p1;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::pair<int, int> p1(42, 42);
		ft::pair<int, int> p2;
		p2 = p1;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}

void test_pair_type_change(long count){
	//print job name
	test_name = "-PAIR TYPE CHANGE TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::pair<char, int> p1('s', 42);
		std::pair<int, double> p2;
		p2 = p1;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::pair<char, int> p1('s', 42);
		ft::pair<int, double> p2;
		p2 = p1;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}

void test_pair_make_pair(long count){
	//print job name
	test_name = "-PAIR MAKE PAIR TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::pair<char, int> p1 = std::make_pair ('c', 42);
		(void) p1;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::pair<char, int> p1 = ft::make_pair ('c', 42);
		(void) p1;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}

void test_pair_comparisons(long count){
	//print job name
	test_name = "-PAIR COMPARISONS TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::pair<char, int> p1 = std::make_pair ('c', 42);
		std::pair<char, int> p2 = std::make_pair ('c', 21);
		bool res;
		res = (p1 == p2);
		res = (p1 != p2);
		res = (p1 < p2);
		res = (p1 <= p2);
		res = (p1 > p2);
		res = (p1 >= p2);
		(void) res;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::pair<char, int> p1 = ft::make_pair ('c', 42);
		ft::pair<char, int> p2 = ft::make_pair ('c', 21);
		bool res;
		res = (p1 == p2);
		res = (p1 != p2);
		res = (p1 < p2);
		res = (p1 <= p2);
		res = (p1 > p2);
		res = (p1 >= p2);
		(void) res;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}
