# ft_containers_tester

Tests for ft_containers including output and performance (compared to std::) on the same tasks.

![run_preview](https://github.com/greg-gav/ft_containers_tester/blob/main/sample_run.gif)
---
Usage:
---

python3 main.py [ path | test_mode ]

default: clone into ft_containers directory, launch
```
git clone https://github.com/greg-gav/ft_containers_tester
cd ft_containers_tester && python3 main.py
```

example:
```
python3 main.py ~/ft_containers vec
```
If path not specified, using default path: ../ (test files in parent directory)  
Files in 'path' should be your *.hpp implementation.

Available test modes:  
vec -> test vector implementation  
stack -> test stack implementation  
map -> test map implementation  
set -> test set implementation  
util -> test utilities implementation   
If test_mode not specified, using default mode: all (run all tests)

Running
```
python3 main.py 
```
is equivalent to: 
```
python3 main.py ../ all 
```

Test No. not in order running in multithreaded mode (test No's stay consistent between runs)

Folder structure:
- Compile errors log to log/
- Temporary cpp files and executables to tmp/


Compile:
- Indicates if the test compiled with your container (shouldn't be red).
- Compile is done in multithreaded mode

Pass:
- Indicates if your container functions the same as std one (shouldn't be red).

Exit:
- Indicates exit status of the test (should be "OK")

Performance:
- Performance is measured relative to std library. x1 is equal, higher is better (shouldn't be red)