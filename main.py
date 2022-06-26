import sys
import os


TEST_FOLDER = "./tests"
VEC_TESTS_H = "vector_tests.hpp"
VEC_TESTS_CPP = "vector_tests.cpp"
TEMP_FOLDER = "./tmp"
FLAGS = "-I./tests -Wall -Werror -Wextra -std=c++98"

def main():
    path = "./"
    
    if len(sys.argv) == 2:
        path = sys.argv[1]

    #assemble vector tests if arg == vec
    header_file =  open(f"{TEST_FOLDER}/{VEC_TESTS_H}", "r")
    cpp_file = open(f"{TEST_FOLDER}/{VEC_TESTS_CPP}", "r")
    out_name = f"{TEMP_FOLDER}/outfile.cpp"
    os.makedirs(os.path.dirname(out_name), exist_ok=True)
    out_file = open(out_name, "w")
    lines = header_file.readlines()
    add_func = False
    func_name = ""
    for l in lines:
        if l.startswith("#include"):
            out_file.write(l)
        if l.startswith("void "):
            out_file.write(l)
            add_func = True
            func_name = l
            break
    if add_func:
        cpplines = cpp_file.readlines()
        for i, l in enumerate(cpplines):
            if func_name in l:
               process_func(cpplines, i, out_file)

def process_func(lines, i, outfile):
    op = 1
    cl = 0
    for j in range(i, len(lines)):
        if "}" in lines[j]:
            cl += 1
        if op == cl:
            break
        if "{" in lines[j]:
            op += 1
        print (f"op {op} cl {cl}")    
    
            

if __name__ == "__main__":
    main()