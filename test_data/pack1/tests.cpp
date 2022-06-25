#include <iostream>

#include <map>
#include <set>
#include <stack>
#include <vector>
using namespace std;


#include "map.hpp"
#include "set.hpp"
#include "stack.hpp"
#include "vector.hpp"
// using namespace ft;

void test_rb_tree() 
{
	using namespace ft;

	std::cout << "Tests rb_tree\n-----------------" << std::endl;
	rb_tree<int> tree;
	std::cout << "Дерево после создания (пустое): \n";
	tree.print_tree();
	std::cout << std::endl;
	std::cout << "Размер дерева: " << tree.size() << "\n";
	std::cout << "Дерево после вставки элементов: \n";
	int numbers[] = {10,40,30,60,90,70,20,50,80,100,1,2,3,5,6,7,8,4,9,11,15,12,15,13,14,17,19,18,21,22,24,26,25};
	// int numbers[] = {10,40,30,60,90,70,20,50,80,100,1,2,3,5,6,7,8,4,9,11,15,12,15,13};
	int size = sizeof(numbers)/sizeof(numbers[0]);
	for(int i = 0; i < size; i++) 
		tree.insert(numbers[i]);	
	tree.print_tree();
	std::cout << std::endl;
	std::cout << "Размер дерева: " << tree.size() << "\n";
	std::cout << "Дерево слева направо (по возрастанию значений): \n";
	tree.print_in_order();
	std::cout << std::endl;
	std::cout << "Найти узел с значением 30: \n";
	std::cout << (*tree.find(30))<<std::endl;
	std::cout << "Дерево после удаления узла с значением 80: \n";
	tree.erase(80);
	tree.print_tree();
	std::cout << std::endl;
	std::cout << "Размер дерева: " << tree.size() << "\n";
	std::cout << "Красные и черные элементы дерева: \n";
	tree.print_details();

	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

void test_is_integral()
{
	// std::cout << std::boolalpha << std::endl;
	std::cout << "Tests is_integral\n-----------------" << std::endl;
	std::cout << "std::is_integral<int>::value:\t" << std::is_integral<int>::value << std::endl;
	std::cout << "ft::is_integral<int>::value:\t" << ft::is_integral<int>::value << std::endl;

	std::cout << "std::is_integral<double>::value:\t" << std::is_integral<double>::value << std::endl;
	std::cout << "ft::is_integral<double>::value:\t\t" << ft::is_integral<double>::value << std::endl;

	std::cout << "std::is_integral<unsigned char>::value:\t" << std::is_integral<unsigned char>::value << std::endl;
	std::cout << "ft::is_integral<unsigned char>::value:\t" << ft::is_integral<unsigned char>::value << std::endl;

	std::cout << "std::is_integral<unsigned short>::value:\t" << std::is_integral<unsigned short>::value << std::endl;
	std::cout << "ft::is_integral<unsigned short>::value:\t\t" << ft::is_integral<unsigned short>::value << std::endl;

	std::cout << "std::is_integral<unsigned int>::value:\t" << std::is_integral<unsigned int>::value << std::endl;
	std::cout << "ft::is_integral<unsigned int>::value:\t" << ft::is_integral<unsigned int>::value << std::endl;

	std::cout << "std::is_integral<unsigned long>::value:\t" << std::is_integral<unsigned long>::value << std::endl;
	std::cout << "ft::is_integral<unsigned long>::value:\t" << ft::is_integral<unsigned long>::value << std::endl;

	std::cout << "std::is_integral<wchar_t>::value:\t" << std::is_integral<wchar_t>::value << std::endl;
	std::cout << "ft::is_integral<wchar_t>::value:\t" << ft::is_integral<wchar_t>::value << std::endl;

	std::cout << "std::is_integral<signed char>::value:\t" << std::is_integral<signed char>::value << std::endl;
	std::cout << "ft::is_integral<signed char>::value:\t" << ft::is_integral<signed char>::value << std::endl;

	std::cout << "std::is_integral<short>::value:\t" << std::is_integral<short>::value << std::endl;
	std::cout << "ft::is_integral<short>::value:\t" << ft::is_integral<short>::value << std::endl;

	std::cout << "std::is_integral<long>::value:\t" << std::is_integral<long>::value << std::endl;
	std::cout << "ft::is_integral<long>::value:\t" << ft::is_integral<long>::value << std::endl;

	std::cout << "std::is_integral<long long>::value:\t" << std::is_integral<long long>::value << std::endl;
	std::cout << "ft::is_integral<long long>::value:\t" << ft::is_integral<long long>::value << std::endl;

	std::cout << "std::is_integral<char>::value:\t" << std::is_integral<char>::value << std::endl;
	std::cout << "ft::is_integral<char>::value:\t" << ft::is_integral<char>::value << std::endl;

	std::cout << "std::is_integral<bool>::value:\t" << std::is_integral<bool>::value << std::endl;
	std::cout << "ft::is_integral<bool>::value:\t" << ft::is_integral<bool>::value << std::endl;

	std::cout << std::endl;

	std::cout << "std::true_type::value:\t" << std::true_type::value << std::endl;
	std::cout << "ft::true_type::value:\t" << ft::true_type::value << std::endl;

	std::cout << "std::false_type::value:\t" << std::false_type::value << std::endl;
	std::cout << "ft::false_type::value:\t" << ft::false_type::value << std::endl;

	std::cout << std::endl;

	std::cout << "std::integral_constant<bool, true>::value:\t" << std::integral_constant<bool, true>::value << std::endl;
	std::cout << "ft::integral_constant<bool, true>::value:\t" << ft::integral_constant<bool, true>::value << std::endl;

	std::cout << "std::integral_constant<bool, false>::value:\t" << std::integral_constant<bool, false>::value << std::endl;
	std::cout << "ft::integral_constant<bool, false>::value:\t" << ft::integral_constant<bool, false>::value << std::endl;  

	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

void test_vector()
{
	std::cout << "Tests vector\n-----------------" << std::endl;
	clock_t test_timer = clock();

	vector<int> v;
    vector<char> vc;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);
    v.push_back(50);
    vc.push_back(71);
    vc.push_back(72);
    vc.push_back(73);
    vc.push_back(74);
 
    std::cout << "Vector size of type int : " << v.size() << std::endl;
    std::cout << "Vector capacity of type int : " << v.capacity() << std::endl;
    std::cout << "Vector elements of type int : ";
    for(std::size_t i = 0; i < v.size(); i++) 
        std::cout << v[i] << ' ';
	std::cout << std::endl;
    std::cout << "Vector size of type char : " << vc.size() << std::endl;
    std::cout << "Vector capacity of type char : " << vc.capacity() << std::endl;
	std::cout << "Vector elements of type char : ";
    for(std::size_t i = 0; i < vc.size(); i++) 
        std::cout << vc[i] << ' ';
	std::cout << std::endl;

    v.push_back(100);
	vc.push_back(70);
    std::cout << "\nAfter pushing an element :" << std::endl;
    std::cout << "Vector elements of type int : ";
    for(std::size_t i = 0; i < v.size(); i++) 
        std::cout << v[i] << ' ';
    std::cout << std::endl;
    // This was possible because we used templates
    std::cout << "Vector elements of type char : ";
    for(std::size_t i = 0; i < vc.size(); i++) 
        std::cout << vc[i] << ' ';
    std::cout << std::endl;
	std::cout << std::endl;

    std::cout << "Element at 1st index of type int: " << v.at(1)
         << std::endl;
    std::cout << "Element at 1st index of type char: "
         << vc.at(1) << std::endl;
 
	// using namespace std;
    v.pop_back();
    vc.pop_back();
    std::cout << "\nAfter deleting last element" << std::endl;
    std::cout << "Vector size of type int: " << v.size() << std::endl;
    std::cout << "Vector capacity of type int : "
         << v.capacity() << std::endl;
    std::cout << "Vector elements of type int: ";
    for(std::size_t i = 0; i < v.size(); i++) 
        std::cout << v[i] << ' ';
    std::cout << std::endl;
    std::cout << "Vector size of type char: " << vc.size()
         << std::endl;
    std::cout << "Vector capacity of type char : "
         << vc.capacity() << std::endl;
    std::cout << "Vector elements of type char: ";
    for(std::size_t i = 0; i < vc.size(); i++) 
        std::cout << vc[i] << ' ';
    std::cout << std::endl;

	std::cout << "*(v.begin()) : " << *(v.begin()) << std::endl;
	std::cout << "*(++v.begin()) : " << *(++v.begin()) << std::endl;
	std::cout << "*(v.begin()) : " << *(v.begin()) << std::endl;
	std::cout << "*(v.end() - 1) : " << *(v.end() - 1) << std::endl;

	std::cout << std::endl;
	std::cout << "Vector elements of type string: " << std::endl;

	vector<std::string> v1;
	v1.push_back("zero");
	v1.push_back("one");
	v1.push_back("two");
	v1.push_back("three");
	v1.push_back("four");
	std::cout << "Vector1 elements of type string: ";
    for(std::size_t i = 0; i < v1.size(); i++) 
        std::cout << v1[i] << ' ';
    std::cout << std::endl;

	vector<std::string> v2(v1.begin(), v1.end());
	std::cout << "Vector2 from vector of type string (from begin to end)\nVector2 elements of type string: ";
    for(std::size_t i = 0; i < v2.size(); i++) 
        std::cout << v2[i] << ' ';
    std::cout << std::endl;

	vector<std::string> v3(v2);
	std::cout << "Vector3 from vector2 of type string v3(v2)\nVector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	std::cout << "Vector3 of type string [1]: " << v3.at(1) << std::endl;
	std::cout << "Vector3 of type string [2]: " << v3[2] << std::endl;
	std::cout << "Vector3 of type string front: " << v3.front() << std::endl;
	std::cout << "Vector3 of type string back: " << v3.back() << std::endl;
	std::cout << "Vector3 of type string *data (pointer): " << *v3.data() << std::endl;

	vector<std::string>::iterator it = v3.begin();
	std::cout << "Vector3 of type string iterators: " ;
	for (; it < v3.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	vector<std::string>::reverse_iterator rvrIt = v3.rbegin();
	std::cout << "Vector3 of type string reverse iterators: " ;
	for (; rvrIt != v3.rend(); rvrIt++) {
		std::cout << *rvrIt << " ";
	}
	std::cout << std::endl;

	std::cout << "Vector3 of type string empty?: " << (v3.empty() ? "true" : "false") << std::endl;
	std::cout << "Vector3 of type string size: " << v3.size() << std::endl;
	std::cout << "Vector3 of type string max_size: " << v3.max_size() << std::endl;
	std::cout << "Vector3 of type string capacity: " << v3.capacity() << std::endl;

	std::cout << "Vector3 of type string clear\n";
	v3.clear();
	std::cout << "Vector3 of type string size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;
	std::cout << "Vector3 insert from vector2 (v3.insert(v3.begin(), v2.begin(), v2.end()))\n";
	v3.insert(v3.begin(), v2.begin(), v2.end());
	std::cout << "Vector3 of type string size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	std::cout << "Vector3 elements of type string erase [4]\n";
	v3.erase(v3.begin() + 4);
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	std::cout << "Before push_back vector3 size: " << v3.size() << std::endl;
	v3.push_back("five");
	v3.push_back("six");
	v3.push_back("seven");
	std::cout << "After (push_back * 3) vector3 size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	v3.pop_back();
	std::cout << "After pop_back vector3 size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	v3.resize(4);
	std::cout << "After resize(4) vector3 size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	v3.assign(3, "hippo");
	std::cout << "After v3.assign(3, 'hippo') vector3 size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;

	v3.swap(v2);
	std::cout << "After (v3.swap(v2)) vector3 size: " << v3.size() << std::endl;
	std::cout << "Vector3 elements of type string: ";
    for(std::size_t i = 0; i < v3.size(); i++) 
        std::cout << v3[i] << ' ';
    std::cout << std::endl;
	std::cout << "Vector2 size: " << v2.size() << std::endl;
	std::cout << "Vector2 elements of type string: ";
    for(std::size_t i = 0; i < v2.size(); i++) 
        std::cout << v2[i] << ' ';
    std::cout << std::endl;

	std::cout << "v3 == v2 ?: " << (v3 == v2 ? "true" : "false") << std::endl;
	std::cout << "v3 < v2 ?: " << (v3 < v2 ? "true" : "false") << std::endl;
	std::cout << "v3 >= v2 ?: " << (v3 >= v2 ? "true" : "false") << std::endl;

	// vector<int> v4;
	// for (int i = 0; i < 300000; i++)
	// 	v4.push_back(i);

	clock_t test_timer_finish = clock();
	printf("timing: %.2fms\n",
			(double)(test_timer_finish - test_timer) / CLOCKS_PER_SEC * 1000);

	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

void test_stack()
{
	std::cout << "Tests stack\n-----------------" << std::endl;
	clock_t test_timer = clock();

	stack<int> st;
	for (int i = 0; i < 50; i++)
		st.push(i * 3);
    std::cout << "Stack1 elements of type int: ";
	uint	tmp = st.size();
    for(std::size_t i = 0; i < tmp; i++)
	{
    	std::cout << st.top() << ' ';
		st.pop();
	}
	std::cout << std::endl;
	for (int i = 0; i < 50; i++)
		st.push(i * 3);
	std::cout << "Stack1 top element: " << st.top() << std::endl;
	std::cout << "Stack1 size: " << st.size() << std::endl;
	std::cout << "Stack1 is empty?: " << (st.empty() ? "true" : "false") << std::endl;

	stack<int> st2(st);
	std::cout << "Stack2: st2(st)" << std::endl;
	std::cout << "Stack2 top element: " << st2.top() << std::endl;
	std::cout << "Stack2 size: " << st2.size() << std::endl;
	std::cout << "Stack2 is empty?: " << (st2.empty() ? "true" : "false") << std::endl;
	std::cout << "Stack1 is empty?: " << (st.empty() ? "true" : "false") << std::endl;

	std::cout << "Stack2 push(215), push(201)" << std::endl;
	st2.push(215);
	st2.push(201);
	std::cout << "Stack2 top element: " << st2.top() << std::endl;
	std::cout << "Stack2 size: " << st2.size() << std::endl;
	std::cout << "Stack2 is empty?: " << (st2.empty() ? "true" : "false") << std::endl;

	stack<int> st3 = st2;
	std::cout << "Stack3: st3 = st2" << std::endl;
	std::cout << "st2 == st3 ?: " << (st2 == st3 ? "true" : "false") << std::endl;

	st3.pop();
	std::cout << "Stack3 pop()" << std::endl;
	std::cout << "Stack3 size: " << st3.size() << std::endl;
	std::cout << "Top element (st3): " << st3.top() << std::endl;
	std::cout << "st2 == st3 ?: " << (st2 == st3 ? "true" : "false") << std::endl;
	std::cout << "st2 != st3 ?: " << (st2 != st3 ? "true" : "false") << std::endl;
	std::cout << "st2 < st3 ?: " << (st2 < st3 ? "true" : "false") << std::endl;
	std::cout << "st2 >= st3 ?: " << (st2 >= st3 ? "true" : "false") << std::endl;

	clock_t test_timer_finish = clock();
	printf("timing: %.2fms\n",
			(double)(test_timer_finish - test_timer) / CLOCKS_PER_SEC * 1000);
	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

static void printMap(const map<std::string, int>& m) {
	std::cout << "{ ";
	for (map<std::string, int>::const_iterator it = m.begin(); it != m.end(); it++)
		std::cout << it->first << ':' << it->second << ' ';
	std::cout << "}\n";
}

void test_map()
{
	std::cout << "Tests map\n-----------------" << std::endl;
	clock_t test_timer = clock();

	map<std::string, int> map1;
	map1["cat"] = 11;
	map1["dog"] = 22;
	map1["horse"] = 33;
	map1["bird"] = 44;
	std::cout << "map1 elements: ";
	printMap(map1);

	map<std::string, int> map2(map1.find("dog"), map1.end());
	std::cout << "map2 (map1.find('dog'), map1.end()): " << std::endl;
	std::cout << "map2 elements: ";
	printMap(map2);

	map<std::string, int> map3(map1);
	std::cout << "map3 (map3(map1)): " << std::endl;
	std::cout << "map3 elements: ";
	printMap(map3);

	std::cout << "map3[dog] at: " << map3.at("dog") << std::endl;
	std::cout << "map3[fish] at: " << map3["fish"] << std::endl;
	std::cout << "map3 elements: ";
	printMap(map3);
	std::cout << "test reverse iterator:\nmap3 elements: ";
	map<std::string, int>::reverse_iterator rvrIt = map3.rbegin();
	std::cout << "{ ";
	for (; rvrIt != map3.rend(); rvrIt++) {
	std::cout << rvrIt->first << ':' << rvrIt->second << ' ';
	}
	std::cout << "}\n";

	std::cout << "map3 empty ?: " << (map3.empty() ? "true" : "false") << std::endl;
	std::cout << "map3 size: " << map3.size() << std::endl;

	std::cout << "map3 clear\n";
	map3.clear();
	std::cout << "map3 size: " << map3.size() << std::endl;
	std::cout << "map3 insert(map2.begin(), map2.end())\n";
	map3.insert(map2.begin(), map2.end());
	std::cout << "map3 size: " << map3.size() << std::endl;
	std::cout << "map3 elements: ";
	printMap(map3);

	std::cout << "map3: erase 'horse'\n";
	map3.erase(map3.find("horse"));
	std::cout << "map3: erase 'fish'\n";
	map3.erase("fish");
	std::cout << "map3 elements: ";
	printMap(map3);
	std::cout << "map3.swap(map2)\n";
	map3.swap(map2);
	std::cout << "map3 elements: ";
	printMap(map3);
	std::cout << "map2 elements: ";
	printMap(map2);

	std::cout << "map3 == map2 ?: " << (map3 == map2 ? "true" : "false") << std::endl;
	std::cout << "map3 < map2 ?: " << (map3 < map2 ? "true" : "false") << std::endl;
	std::cout << "map3 >= map2 ?: " << (map3 >= map2 ? "true" : "false") << std::endl;

	// map<int, int> map4;
	// for (int i = 0, j = 100; i < 300; i++, j++)
	// 	map4.insert(make_pair(i * 2, j));
	// std::cout << "map4 count 41: " << map4.count(41) << std::endl;
	// std::cout << "map4 count 50: " << map4.count(50) << std::endl;
	// std::cout << "map4 count 300005: " << map4.count(300005) << std::endl;
	// std::cout << "map4 find 26: " << map4.find(26)->first << std::endl;
	// std::cout << "map4 lower bound 127: " << map4.lower_bound(127)->first << std::endl;
	// std::cout << "map4 upper bound 244: " << map4.upper_bound(244)->first << std::endl;

	clock_t test_timer_finish = clock();
	printf("timing: %.2fms\n",
			(double)(test_timer_finish - test_timer) / CLOCKS_PER_SEC * 1000);
	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

static void printSet(const set<int>& s)
{
	std::cout << "{ ";
	for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
		std::cout << *it << ' ';
	std::cout << "}\n";
}

void test_set() {
	std::cout << "Tests set\n-----------------" << std::endl;
	clock_t test_timer = clock();

	set<int> set1;
	for (int i = 0; i < 10; i++)
		set1.insert(i * 3);
	std::cout << "set1 elements: ";
	printSet(set1);

	std::cout << "set2 (set1.find(15), set1.end()) \n";
	set<int> set2(set1.find(15), set1.end());
	std::cout << "set2 elements: ";
	printSet(set2);
	std::cout << "set3 (set1) \n";
	set<int> set3(set1);
	std::cout << "set3 elements: ";
	printSet(set3);
	std::cout << "set3 test reverse iterator \nset3 elements: ";
	std::cout << "{ ";
	for (set<int>::reverse_iterator rvrIt = set3.rbegin(); rvrIt != set3.rend(); rvrIt++)
		std::cout << *rvrIt << ' ';
	std::cout << "}\n";

	std::cout << "set3 empty ?: " << (set3.empty() ? "true" : "false") << std::endl;
	std::cout << "set3 size: " << set3.size() << std::endl;

	std::cout << "set3 clear\n";
	set3.clear();
	std::cout << "set3 size: " << set3.size() << std::endl;
	std::cout << "set3 insert (set2.begin(), set2.end())\n";
	set3.insert(set2.begin(), set2.end());
	std::cout << "set3 size: " << set3.size() << std::endl;
	std::cout << "set3 elements: ";
	printSet(set3);

	std::cout << "set3 erase 15\n";
	set3.erase(set3.find(15));
	std::cout << "set3 erase 27\n";
	set3.erase(27);
	std::cout << "set3 elements: ";
	printSet(set3);
	std::cout << "erase swap(set2)\n";
	set3.swap(set2);
	std::cout << "set3 elements: ";
	printSet(set3);
	std::cout << "set2 elements: ";
	printSet(set2);

	std::cout << "set3 == set2 ?: " << (set3 == set2 ? "true" : "false") << std::endl;
	std::cout << "set3 < set2 ?: " << (set3 < set2 ? "true" : "false") << std::endl;
	std::cout << "set3 >= set2 ?: " << (set3 >= set2 ? "true" : "false") << std::endl;

	// set<int> s4;
	// for (int i = 0; i < 300000; i++)
	// 	s4.insert(i * 2);
	// std::cout << "count 41: " << s4.count(41) << std::endl;
	// std::cout << "count 50: " << s4.count(50) << std::endl;
	// std::cout << "count 300005: " << s4.count(300005) << std::endl;
	// std::cout << "find 26: " << *(s4.find(26)) << std::endl;
	// std::cout << "lower bound 127: " << *(s4.lower_bound(127)) << std::endl;
	// std::cout << "upper bound 244: " << *(s4.upper_bound(244)) << std::endl;

	clock_t test_timer_finish = clock();
	printf("timing: %.2fms\n",
			(double)(test_timer_finish - test_timer) / CLOCKS_PER_SEC * 1000);
	std::cout << std::endl;
	std::cout << "=================\n" << std::endl;
}

int main()
{
	std::cout << std::endl;
	test_rb_tree();
	test_is_integral();
	test_vector();
	test_stack();
	test_map();
	test_set();

  return 0;
}

// c++ -Wall -Wextra -Werror -std=c++98 tests.cpp && ./a.out