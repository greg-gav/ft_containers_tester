import sys
import re
import os
from os import listdir
from os.path import isfile, join
import subprocess

TEST_ITER_NUM = 100000
TEST_FOLDER = "./tests"
VEC_TESTS_H = "vector_tests.hpp"
VEC_TESTS_CPP = "vector_tests.cpp"
TEMP_FOLDER = "./tmp"
FLAGS = "-Wall -Werror -Wextra -std=c++98 -I./tests"

def main():
    path = get_path_or_exit()


    #assemble tests --> vector
    with open(f"{TEST_FOLDER}/{VEC_TESTS_H}", "r") as header_file:
        h_lines = header_file.readlines()
    with open(f"{TEST_FOLDER}/{VEC_TESTS_CPP}", "r") as cpp_file:
        cpp_lines = cpp_file.readlines()

    includes = []
    add_test_headers(h_lines, includes)

    add_extra_headers(path, includes)
    
    while((loc := parse_header(h_lines)) >= 0):
        func_name = get_name(h_lines, loc)
        func_body: str = find_in_cpp(cpp_lines, func_name)
        out_string = build_outfile(includes, func_body, func_name)
        write_to_source_file(out_string)
    print(f"written {write_to_source_file.num} files")

    compile_tests(path)


def compile_tests(path):
    for i in range(1, write_to_source_file.num + 1):
        bashCommand = f"c++ {TEMP_FOLDER}/outfile{i}.cpp {TEST_FOLDER}/test_utils.cpp -I{path} -I{TEST_FOLDER} -o {TEMP_FOLDER}/a{i}.out"
        print(bashCommand)
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
        output, error = process.communicate()

def add_test_headers(h_lines, includes):
    for line in h_lines:
        if line.lstrip().startswith("#include"):
            includes.append(line)

def add_extra_headers(path, includes):
    files_at_path = [f for f in listdir(path) if isfile(join(path, f))]
    for file in files_at_path:
        if file.endswith(".hpp"):
            includes.append(f'#include"{file}"\n')

#return line number with next prototype
def write_to_source_file(out_string):
    write_to_source_file.num += 1
    out_name = f"{TEMP_FOLDER}/outfile{write_to_source_file.num}.cpp"
    os.makedirs(os.path.dirname(out_name), exist_ok=True)
    out_file = open(out_name, "w")
    out_file.write(out_string)
    out_file.close()
write_to_source_file.num = 0


def build_outfile(includes, func_body, func_name):
    source  = ""
    for line in includes:
        source += line
    source += f"extern std::string\ttest_name;\n{func_body}\nint main(){{\n\t{func_name}({TEST_ITER_NUM});\n}}"
    return source


def parse_header(h_lines) -> int: 
    for i in range(parse_header.progress, len(h_lines) - 1):
        parse_header.progress += 1
        if re.search( r"^.*void .*$", h_lines[parse_header.progress]):
            return parse_header.progress
    return -1
parse_header.progress = 0


def process_func(lines, i):
    op = 0
    cl = 0
    j = 0
    full_func = ""
    for j in range(i, len(lines)):
        if "{" in lines[j]:
            op += 1
        if "}" in lines[j]:
            cl += 1
        if op == cl:
            break
    for k in range(i,j + 1):
        full_func += (lines[k])
    return full_func

def find_in_cpp(cpp_lines, func_name):
    for i, line in enumerate(cpp_lines):
        if m := re.match(r"^.*" + re.escape(func_name) + r"{1}\(.*$", line):
            num_lines = process_func(cpp_lines, i)
    return num_lines

def get_name(h_lines, loc):
    func_name = ""
    if m := re.search(r"^.* ([A-za-z_]+)\(.*$", h_lines[loc]):
        func_name = m.group(1)
    return func_name

def get_path_or_exit():
    path = "./test_data/pack0" #test code
    if len(sys.argv) == 2:
        path = sys.argv[1]
    return path

if __name__ == "__main__":
    main()