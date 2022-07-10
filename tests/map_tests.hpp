#ifndef _MAP_TESTS_
#define _MAP_TESTS_

#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "test_utils.hpp"

void test_map_empty_ctor(long count);
void test_map_insert_val(long count);
void test_map_size_empty_max(long count);
void test_map_copy_ctor(long count);
void test_map_begin_end(long count);
void test_map_rbegin_rend(long count);
void test_map_operator_at(long count);
void test_map_assignment_op(long count);
void test_map_range_ctor(long count);
void test_map_comparison(long count);
void test_map_find(long count);
void test_map_swap(long count); 
void test_map_count_clear(long count);
void test_map_insert_range(long count);
void test_map_erase(long count);
void test_map_erase_pos(long count); 
void test_map_erase_val(long count);
void test_map_upper_bound(long count);
void test_map_lower_bound(long count);
void test_map_equal_range(long count);

#endif
