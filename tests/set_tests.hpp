#ifndef _SET_TESTS_
#define _SET_TESTS_

#include <iostream>
#include "test_utils.hpp"
#include "equal_compare.hpp"
#include <set>
#include "set.hpp"

void test_set_empty_ctor(long count);
void test_set_insert_val(long count);
void test_set_size_empty_max(long count);
void test_set_copy_ctor(long count);
void test_set_begin_end(long count);
void test_set_rbegin_rend(long count);
void test_set_assignment_op(long count);
void test_set_range_ctor(long count);
void test_set_comparison(long count);
void test_set_find(long count);
void test_set_swap(long count);
void test_set_count_clear(long count);
void test_set_insert_range(long count);
void test_set_erase(long count);
void test_set_erase_pos(long count); 
void test_set_erase_val(long count);
void test_set_upper_bound(long count);
void test_set_lower_bound(long count);
void test_set_equal_range(long count);

#endif
