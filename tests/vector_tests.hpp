#ifndef _VECTOR_TESTS_
#define _VECTOR_TESTS_

#include <iostream>
#include "test_utils.hpp"
#include <vector>

void test_vector_empty_ctor(long count);
void test_vector_param_ctor(long count);
void test_vector_two_param_ctor(long count);
void test_vector_size_capacity_empty(long count);
void test_vector_size_capacity_random(long count);
void test_vector_reserve(long count);
void test_vector_resize(long count);
void test_vector_push_back(long count);
void test_vector_pop_back(long count);
void test_vector_erase_pos(long count);
void test_vector_erase_iter(long count);
void test_vector_clear(long count);
void test_vector_reverse_iter(long count);
void test_vector_swap(long count);
void test_vector_insert_pos(long count);
void test_vector_insert_pos_num(long count);
void test_vector_insert_iter(long count);
void test_vector_comparison(long count);
void test_vector_assign_n(long count);
void test_vector_assign_range(long count);
void test_vector_assignment(long count);
void test_vector_copy_ctor(long count);
void test_vector_copy_range_ctor(long count);
void test_vector_access(long count);

#endif
