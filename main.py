import sys
import os
import re

TEST_FOLDER = "./tests"
VEC_TESTS_H = "vector_tests.hpp"
VEC_TESTS_CPP = "vector_tests.cpp"
TEMP_FOLDER = "./tmp"
FLAGS = "-I./tests -Wall -Werror -Wextra -std=c++98"

def main():
    path = get_path_or_exit()

    #assemble tests --> vector
    with open(f"{TEST_FOLDER}/{VEC_TESTS_H}", "r") as header_file:
        h_lines = header_file.readlines()

    includes = []
    for line in h_lines:
        if line.startswith("#include"):
            includes.append(line)
            
    while(loc := parse_header(h_lines) > 0):
        break

    header_file =  open(f"{TEST_FOLDER}/{VEC_TESTS_H}", "r")
    cpp_file = open(f"{TEST_FOLDER}/{VEC_TESTS_CPP}", "r")
    out_name = f"{TEMP_FOLDER}/outfile.cpp"
    os.makedirs(os.path.dirname(out_name), exist_ok=True)
    out_file = open(out_name, "w")
    
    add_func = False
    func_name = ""
    for l in lines:
        if l.startswith("void "):
            out_file.write(l)
            add_func = True
            func_name = re.search(r"^.* ([A-za-z_]+)\(.*$", l).group(1)
            break
    out_file.write("std::string     test_name;\n")
    if add_func:
        cpplines = cpp_file.readlines()
        for i, l in enumerate(cpplines):
            if func_name in l:
                process_func(cpplines, i, out_file)

def process_func(lines, i, outfile):
    op = 0
    cl = 0
    j = 0
    for j in range(i, len(lines)):
        if "{" in lines[j]:
            op += 1
        if "}" in lines[j]:
            cl += 1
        if op == cl:
            break
    for k in range(i,j + 1):
        outfile.write(lines[k])

#return line number with next prototype
def parse_header(lines): 
    return 1
parse_header.progress = 0

def get_path_or_exit():
    path = "./"
    if len(sys.argv) == 2:
        path = sys.argv[1]
    return path

if __name__ == "__main__":
    main()