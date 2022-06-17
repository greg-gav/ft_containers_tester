#include "test_utils.hpp"
#include "pair_tests.hpp"
#include "equal_compare_tests.hpp"
#include "enable_integral_tests.hpp"
#include "vector_tests.hpp"
#include "stack_tests.hpp"
#include "map_tests.hpp"
#include "set_tests.hpp"

extern const long   COUNT;
extern std::string	test_name;
Command 			comm = ALL;

int main(int argc, char** argv) {
	handle_args(argc, argv);
	init_cout();

	switch (comm) {
	case (ALL):
	case (PAIR):
		/*** pair performance ***/
		test_pair_construction(COUNT * 1000);
		test_pair_type_change(COUNT * 1000);
		test_pair_make_pair(COUNT * 1000);
		test_pair_comparisons(COUNT * 100);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(LEX):
		/*** equal and lexicographical_compare ***/
    	test_lexicographical_compare(COUNT * 100);
		test_lexicographical_compare_with_cmp(COUNT * 50);
		test_equal(COUNT * 100);
		test_equal_with_pred(COUNT * 100);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(INT):
		/*** enable_if and is_integral ***/
    	test_enableif_integral(COUNT * 2000);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(VEC):
		/*** vector ***/
    	test_vector_empty_ctor(COUNT * 100);
		test_vector_param_ctor(COUNT * 10);
		test_vector_two_param_ctor(COUNT * 10);
		test_vector_size_capacity_empty(COUNT * 100);
		test_vector_size_capacity_random(COUNT * 10);
		test_vector_reserve(COUNT * 5);
		test_vector_resize(COUNT * 5);
		test_vector_push_back(COUNT);
		test_vector_pop_back(COUNT);
		test_vector_erase_pos(COUNT);
		test_vector_erase_iter(COUNT);
		test_vector_clear(COUNT);
		test_vector_reverse_iter(COUNT);
		test_vector_swap(COUNT * 10);
		test_vector_insert_pos(COUNT);
		test_vector_insert_pos_num(COUNT);
		test_vector_insert_iter(COUNT);
		test_vector_comparison(COUNT);
		test_vector_assign_n(COUNT);
		test_vector_assign_range(COUNT);
		test_vector_assignment(COUNT);
		test_vector_copy_ctor(COUNT);
		test_vector_copy_range_ctor(COUNT);
		test_vector_access(COUNT * 10);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(STACK):
		/*** stack ***/
    	test_stack_empty_ctor(COUNT * 100);
    	test_stack_copy_ctor(COUNT);
    	test_stack_assignment(COUNT);
    	test_stack_size_empty_top(COUNT);
    	test_stack_push_pop(COUNT);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(MAP):
		/*** map ***/
		test_map_empty_ctor(COUNT * 10);
		test_map_insert_val(COUNT);
		test_map_insert_range(COUNT);
		test_map_size_empty_max(COUNT);
		test_map_begin_end(COUNT);
		test_map_rbegin_rend(COUNT);
		test_map_range_ctor(COUNT);
		test_map_copy_ctor(COUNT);
		test_map_assignment_op(COUNT);
		test_map_operator_at(COUNT);
		test_map_comparison(COUNT);
    	test_map_find(COUNT);
    	test_map_swap(COUNT);
    	test_map_count_clear(COUNT);
		test_map_erase(COUNT);
		test_map_erase_pos(COUNT);
		test_map_erase_val(COUNT);
		test_map_equal_range(COUNT);
		test_map_upper_bound(COUNT);
		test_map_lower_bound(COUNT);
		std::cout << std::endl;
		if (comm != ALL) { break; }
	case(SET):
		/*** set ***/
		test_set_empty_ctor(COUNT * 10);
		test_set_insert_val(COUNT);
		test_set_range_ctor(COUNT);
		test_set_insert_range(COUNT);
		test_set_copy_ctor(COUNT);
		test_set_assignment_op(COUNT);
		test_set_size_empty_max(COUNT);
		test_set_begin_end(COUNT);
		test_set_rbegin_rend(COUNT);
		test_set_comparison(COUNT);
		test_set_find(COUNT);
		test_set_swap(COUNT);
		test_set_count_clear(COUNT);
		test_set_erase(COUNT);
		test_set_erase_pos(COUNT);
		test_set_erase_val(COUNT);
		test_set_equal_range(COUNT);
		test_set_upper_bound(COUNT);
		test_set_lower_bound(COUNT);	
		std::cout << std::endl;
		if (comm != ALL) { break; }
	default:
		break;
	}
}
