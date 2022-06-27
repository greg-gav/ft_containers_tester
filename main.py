import sys
import re
import os
from os import listdir
from os.path import isfile, join, exists
import subprocess
import signal
import shutil

TEST_ITER_NUM = 1000
TEST_FOLDER = "./tests"
VEC_TESTS_H = "vector_tests.hpp"
VEC_TESTS_CPP = "vector_tests.cpp"
TEMP_FOLDER = "./tmp"
LOG_FOLDER = "./log"
FLAGS = "-Wall -Werror -Wextra -std=c++98"

def main():
    shutil.rmtree(TEMP_FOLDER, ignore_errors=True)
    shutil.rmtree(LOG_FOLDER, ignore_errors=True)
    path = get_path_or_exit()


    #assemble tests --> vector
    with open(f"{TEST_FOLDER}/{VEC_TESTS_H}", "r") as header_file:
        h_lines = header_file.readlines()
    with open(f"{TEST_FOLDER}/{VEC_TESTS_CPP}", "r") as cpp_file:
        cpp_lines = cpp_file.readlines()

    includes = []

    add_test_headers(h_lines, includes)
    add_extra_headers(path, includes)
    create_source_files(h_lines, cpp_lines, includes)
    compile_tests(path)
    run_tests()

    # cleanup
    # shutil.rmtree(TEMP_FOLDER, ignore_errors=True)


def create_source_files(h_lines, cpp_lines, includes):
    while((loc := parse_header(h_lines)) >= 0):
        func_name = get_name(h_lines, loc)
        func_body: str = find_in_cpp(cpp_lines, func_name)
        out_string = build_outfile(includes, func_body, func_name)
        write_to_source_file(out_string)
    print(f"generated {write_to_source_file.num} temp files")

def run_tests():
    for i in range(1, write_to_source_file.num + 1):
        exec_file = f"{TEMP_FOLDER}/a_{i}.out"
        if not exists(exec_file): continue
        process = subprocess.Popen(exec_file.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            output, error = process.communicate(timeout=30)
        except subprocess.TimeoutExpired:
            process.kill()
            print("Test timeout, killed")
        print(output.decode("utf-8"), end="")
        handle_proc_return(process)


def handle_proc_return(process):
    if (process.returncode != 0 and process.returncode != None):
        if (process.returncode == -signal.SIGSEGV):
            print("Segmentation fault")
        else:
            print(f"Abnormal return code: {process.returncode}")

def compile_tests(path):
    print (f"Compiling tests with {FLAGS} flags")
    for i in range(1, write_to_source_file.num + 1):
        bashCommand =   (f"c++ {TEMP_FOLDER}/outfile_{i}.cpp {TEST_FOLDER}/test_utils.cpp"
                        f" -I{path} -I{TEST_FOLDER} -o {TEMP_FOLDER}/a_{i}.out {FLAGS}")
        print (f"Test {i}/{write_to_source_file.num}", end="\r", flush=True)
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, error = process.communicate()
        if error != b"" and "error" in error.decode("utf-8"):
            # print(error.decode("utf-8"))
            print(f"Test {i} compile failed, see compile log for details")
            compile_error_log(error.decode("utf-8"), i)

def compile_error_log(error, num):
    compile_log = f"{LOG_FOLDER}/compile_error_{num}.txt"
    os.makedirs(os.path.dirname(compile_log), exist_ok=True)
    name = ""
    with open(f"{TEMP_FOLDER}/outfile_{num}.cpp", "r") as source:
        name = search_name_in_source(source)
    with open(compile_log, "w") as out_file:
        out_file.write(f"{name}\n\n")
        out_file.write(error)

def search_name_in_source(source):
    lines = source.readlines()
    for line in lines:
        if (m := re.search(r"^.*test_name.*\"(.*)\".*$", line)):
            return m.group(1)
    return ""

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
    out_name = f"{TEMP_FOLDER}/outfile_{write_to_source_file.num}.cpp"
    os.makedirs(os.path.dirname(out_name), exist_ok=True)
    with open(out_name, "w") as out_file:
        out_file.write(out_string)
write_to_source_file.num = 0


def build_outfile(includes, func_body, func_name):
    source  = ""
    for line in includes:
        source += line
    source +=   (f"extern std::string\ttest_name;\n{func_body}\n"
                f"int main(){{\n\t{func_name}({TEST_ITER_NUM});\n}}")
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
    path = "./test_data/pack1" #test code
    if len(sys.argv) == 2:
        path = sys.argv[1]
    return path

if __name__ == "__main__":
    main()