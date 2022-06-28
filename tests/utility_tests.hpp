#ifndef _UTILITY_TESTS_
#define _UTILITY_TESTS_

#include "test_utils.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <type_traits>

void test_enableif_integral(long count);
void test_lexicographical_compare(long count);
void test_lexicographical_compare_with_cmp(long count);
void test_equal(long count);
void test_equal_with_pred(long count);
void test_pair_construction(long count);
void test_pair_type_change(long count);
void test_pair_make_pair(long count);
void test_pair_comparisons(long count);

#endif
