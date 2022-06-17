#ifndef _COMPARE_TESTS_
#define _COMPARE_TESTS_

#include <vector>
#include <algorithm>
#include "equal_compare.hpp"
#include "test_utils.hpp"

void test_lexicographical_compare(long count);
void test_lexicographical_compare_with_cmp(long count);
void test_equal(long count);
void test_equal_with_pred(long count);

#endif
