
TEST_ITER_NUM = 100000
TIMEOUT = 30
DEFAULT_PATH = "../"
TEST_FOLDER = "./tests"
TEMP_FOLDER = "./tmp"
LOG_FOLDER = "./log"
VEC_TESTS_H = "vector_tests.hpp"
VEC_TESTS_CPP = "vector_tests.cpp"
STACK_TESTS_H = "stack_tests.hpp"
STACK_TESTS_CPP = "stack_tests.cpp"
MAP_TESTS_H = "map_tests.hpp"
MAP_TESTS_CPP = "map_tests.cpp"
SET_TESTS_H = "set_tests.hpp"
SET_TESTS_CPP = "set_tests.cpp"
UTILITY_TESTS_H = "utility_tests.hpp"
UTILITY_TESTS_CPP = "utility_tests.cpp"
EXTRA_FUNCS_CPP = "extra_funcs.cpp"
FLAGS = "-Wall -Werror -Wextra -std=c++98"
COMM_ALL = "all"
COMM_VEC = "vec"
COMM_STACK = "stack"
COMM_MAP = "map"
COMM_SET = "set"
COMM_UTIL = "util"
NC = "\x1B[0m"
COL_RED = "\x1B[0;31m"
COL_GRN = "\x1B[0;32m"
COL_YEL = "\x1B[0;33m"

def get_all_commands():
    return {COMM_ALL:[COMM_VEC, COMM_STACK, COMM_MAP, COMM_SET, COMM_UTIL], 
        COMM_VEC:[VEC_TESTS_H, VEC_TESTS_CPP], 
        COMM_STACK:[STACK_TESTS_H, STACK_TESTS_CPP],
        COMM_MAP:[MAP_TESTS_H, MAP_TESTS_CPP], 
        COMM_SET:[SET_TESTS_H, SET_TESTS_CPP], 
        COMM_UTIL:[UTILITY_TESTS_H, UTILITY_TESTS_CPP]}

if __name__ == "__main__":
    pass