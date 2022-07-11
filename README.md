# ft_containers_tester
Tests for ft_containers

---
Usage:
---

python3 main.py [ path | test_mode ]

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