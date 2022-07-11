import sys
import re
from os import listdir, makedirs
from os.path import isfile, join, exists, dirname
import subprocess
import signal
import shutil
import static


def main():
    shutil.rmtree(static.TEMP_FOLDER, ignore_errors=True)
    shutil.rmtree(static.LOG_FOLDER, ignore_errors=True)
    commands = {static.COMM_ALL:[], 
    static.COMM_VEC:[static.VEC_TESTS_H, static.VEC_TESTS_CPP], 
    static.COMM_STACK:[static.STACK_TESTS_H, static.STACK_TESTS_CPP],
    static.COMM_MAP:[static.MAP_TESTS_H, static.MAP_TESTS_CPP], 
    static.COMM_SET:[static.SET_TESTS_H, static.SET_TESTS_CPP], 
    static.COMM_UTIL:[static.UTILITY_TESTS_H, static.UTILITY_TESTS_CPP]}
    
    path, comm = parse_arguments(commands)
    print(f"Testing implementation in path: {path}, test mode: {comm}")

    #assemble tests --> vector
    with open(f"{static.TEST_FOLDER}/{commands[comm][0]}", "r") as header_file:
        h_lines = header_file.readlines()
    with open(f"{static.TEST_FOLDER}/{commands[comm][1]}", "r") as cpp_file:
        cpp_lines = cpp_file.readlines()

    includes = []

    add_test_headers(h_lines, includes)
    add_extra_headers(path, includes)
    create_source_files(h_lines, cpp_lines, includes)
    compile_tests(path)
    run_tests()

    # cleanup
    # shutil.rmtree(TEMP_FOLDER, ignore_errors=True)

def parse_arguments(commands):
    if (len(sys.argv) == 1):
        return (static.DEFAULT_PATH, static.COMM_ALL)
    elif (len(sys.argv) == 2):
        if sys.argv[1] in commands.keys():
            return (static.DEFAULT_PATH, sys.argv[1])
        else:
            return (sys.argv[1], static.COMM_ALL)
    else:
        if sys.argv[1] in commands.keys():
            return (sys.argv[2], sys.argv[1])
        else:
            for arg in sys.argv:
                if arg in commands.keys():
                    return (sys.argv[1], arg)
            return (sys.argv[1], static.COMM_ALL)

def create_source_files(h_lines, cpp_lines, includes):
    extra_source = ""
    with open(f"{static.TEST_FOLDER}/{static.EXTRA_FUNCS_CPP}", "r") as extra:
        extra_source = extra.read()
    while((loc := parse_header(h_lines)) >= 0):
        func_name = get_name(h_lines, loc)
        func_body: str = find_in_cpp(cpp_lines, func_name)
        out_string = build_outfile(includes, func_body, func_name, extra_source)
        write_to_source_file(out_string)
    print(f"generated {write_to_source_file.num} temp files")

def run_tests():
    print("Running tests:")
    results = {}
    print ("{:<3} {:<37} {:<11} {:<11} {:<11} {:<8}"
            .format('No.','Name','Compile','Pass','Exit','Perf'))
    for i in range(1, write_to_source_file.num + 1):
        exec_file = f"{static.TEMP_FOLDER}/a_{i}.out"
        if not exists(exec_file): 
            handle_compile_error(results, i)
            continue
        results[i] = ["OK"]
        process = subprocess.Popen(exec_file.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        try:
            output, error = process.communicate(timeout=static.TIMEOUT)
        except subprocess.TimeoutExpired:
            process.kill()
            handle_test_timeout(results, i)
            continue
        results[i].extend(handle_test_output(output))
        results[i].append(handle_proc_return(process))
        print_test_result(results, i)
        # print(output.decode("utf-8"), end="") # native test result

def handle_test_timeout(results, i):
    with open(f"{static.TEMP_FOLDER}/outfile_{i}.cpp", "r") as source:
        results[i]= ["OK", search_name_in_source(source).strip("-"), -1, "NONE", "TIMEOUT"]
        print_test_result(results, i)

def handle_compile_error(results, i):
    with open(f"{static.TEMP_FOLDER}/outfile_{i}.cpp", "r") as source:
        results[i]= ["FAIL", search_name_in_source(source).strip("-"), -1, "NONE", "NONE"]
        print_test_result(results, i)

def print_test_result(results: dict, i):
    p = dict(results)
    #Compiled:
    if p[i][0] == "FAIL": 
        p[i][0] = "❌"
    elif p[i][0] == "OK":
        p[i][0] = "✅"
    #Errors:
    if p[i][2] == 0:
        p[i][2] = "✅"
    elif p[i][2] == -1:
        p[i][2] = "🆖"
    else:
        p[i][2] = "❌"
    print (u"{:<3} {:<40} {:<8} {:<10} {:<10} {:<10}".format(i, 
            p[i][1], p[i][0], p[i][2], p[i][4], p[i][3]))


def handle_test_output(output):
    result = []
    name = get_name_from_output(output.decode("utf-8"))
    errors = get_errors_from_output(output.decode("utf-8"))
    perf = get_performance_from_output(output.decode("utf-8"))
    result.extend([name, errors, perf])
    return result


def get_performance_from_output(output):
    m = re.search(r"^.*?(?:performance: )(.*?) .*$", output, flags=re.DOTALL)
    perf = m.group(1) if m else "NONE"
    return perf

def get_errors_from_output(output):
    m = re.search(r"^.*?(\d+) (?=errors).*$", output, flags=re.DOTALL)
    number = int(m.group(1)) if m else -1
    return number

def get_name_from_output(output):
    m = re.search(r"^.*?\-(.*?)\-.*$", output, flags=re.DOTALL)
    name = m.group(1) if m else ""
    return name

def handle_proc_return(process):
    returned = "OK"
    if (process.returncode != 0 and process.returncode != None):
        if (process.returncode == -signal.SIGSEGV):
            returned = f"SEGFAULT"
        else:
            returned = f"CODE: {process.returncode}"
    return returned

def compile_tests(path):
    print (f"Compiling tests with {static.FLAGS} flags")
    for i in range(1, write_to_source_file.num + 1):
        bashCommand =   (f"c++ {static.TEMP_FOLDER}/outfile_{i}.cpp {static.TEST_FOLDER}/test_utils.cpp"
                        f" -I{path} -I{static.TEST_FOLDER} -o {static.TEMP_FOLDER}/a_{i}.out {static.FLAGS}")
        print (f"Compiling test {i}/{write_to_source_file.num}", end="\r", flush=True)
        process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        output, error = process.communicate()
        if error != b"" and "error" in error.decode("utf-8"):
            # print(error.decode("utf-8"))
            print(f"Test {i} compile failed, see compile log for details")
            compile_error_log(error.decode("utf-8"), i)

def compile_error_log(error, num):
    compile_log = f"{static.LOG_FOLDER}/compile_error_{num}.txt"
    makedirs(dirname(compile_log), exist_ok=True)
    name = ""
    with open(f"{static.TEMP_FOLDER}/outfile_{num}.cpp", "r") as source:
        name = search_name_in_source(source)
    with open(compile_log, "w") as out_file:
        out_file.write(f"{name}\n\n{error}")

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
    try:
        files_at_path = [f for f in listdir(path) if isfile(join(path, f))]
        for file in files_at_path:
            if file.endswith(".hpp"):
                includes.append(f'#include "{file}"\n')
    except FileNotFoundError:
        print(f"Tester error: path '{path}' not valid")
        exit(1)

#return line number with next prototype
def write_to_source_file(out_string):
    write_to_source_file.num += 1
    out_name = f"{static.TEMP_FOLDER}/outfile_{write_to_source_file.num}.cpp"
    makedirs(dirname(out_name), exist_ok=True)
    with open(out_name, "w") as out_file:
        out_file.write(out_string)
write_to_source_file.num = 0


def build_outfile(includes, func_body, func_name, extra):
    source  = ""
    for line in includes:
        source += line
    source += extra
    source +=   (f"extern std::string\ttest_name;\n{func_body}\n"
                f"int main(){{\n\t{func_name}({static.TEST_ITER_NUM});\n}}")
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


if __name__ == "__main__":
    main()