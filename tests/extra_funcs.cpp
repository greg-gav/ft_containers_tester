#include <type_traits>

/* templates needed only for utility tests */
template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i) { return bool(i % 2); }

template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type
is_odd_ft (T i) { return bool(i % 2); }

static bool ft_comp (const std::string& s1, const std::string& s2){
    return s1 < s2;
}

static bool ft_is_first_greater(int& x, int& y) {
    return x > y;
}
/* end templates section */
