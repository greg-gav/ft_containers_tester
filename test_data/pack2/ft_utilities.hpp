#ifndef FT_UTILITIES_HPP
# define FT_UTILITIES_HPP

# include "iterator_traits.hpp"
# include "pair.hpp"
# include "reverse_iterator.hpp"

namespace ft {

/*
** This `non_const` struct is needed for removing
** const constraint from type (used in the RBTreeIterator)
*/
template<class T>
struct non_const { 
    typedef T type;
};

template<class T>
struct non_const <const T> {
    typedef T type;
};

/*
** This `choose` struct is needed for non-const and const iterator
** implementation without duplicating the code.
** copyright - Matt Austern. Generic Programming and the STL
*/
template<bool flag, class IsTrue, class IsFalse>
struct choose;

template<class IsTrue, class IsFalse>
struct choose<true, IsTrue, IsFalse> {
   typedef IsTrue type;
};

template<class IsTrue, class IsFalse>
struct choose<false, IsTrue, IsFalse> {
   typedef IsFalse type;
};

/*
** enable_if implementation
*/ 
template<bool Cond, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

/*
** is_integral implementation
*/ 

template<typename T, T v>
struct integral_constant {
    typedef integral_constant<T, v> type;
    typedef T                       value_type;
    static const T                  value = v;
    operator value_type() const { return value; }
};

typedef ft::integral_constant<bool, true>   true_type;
typedef ft::integral_constant<bool, false>  false_type;

template<typename> struct is_integral : ft::false_type {};
template<> struct is_integral<bool> : ft::true_type {};
template<> struct is_integral<char> : ft::true_type {};
template<> struct is_integral<wchar_t> : ft::true_type {};
template<> struct is_integral<short> : ft::true_type {};
template<> struct is_integral<int> : ft::true_type {};
template<> struct is_integral<long> : ft::true_type {};
template<> struct is_integral<long long> : ft::true_type {};
template<> struct is_integral<unsigned char> : ft::true_type {};
template<> struct is_integral<unsigned short> : ft::true_type {};
template<> struct is_integral<unsigned int> : ft::true_type {};
template<> struct is_integral<unsigned long> : ft::true_type {};
template<> struct is_integral<unsigned long long> : ft::true_type {};
template<> struct is_integral<const bool> : ft::true_type {};
template<> struct is_integral<const char> : ft::true_type {};
template<> struct is_integral<const wchar_t> : ft::true_type {};
template<> struct is_integral<const short> : ft::true_type {};
template<> struct is_integral<const int> : ft::true_type {};
template<> struct is_integral<const long> : ft::true_type {};
template<> struct is_integral<const long long> : ft::true_type {};
template<> struct is_integral<const unsigned char> : ft::true_type {};
template<> struct is_integral<const unsigned short> : ft::true_type {};
template<> struct is_integral<const unsigned int> : ft::true_type {};
template<> struct is_integral<const unsigned long> : ft::true_type {};
template<> struct is_integral<const unsigned long long> : ft::true_type {};
template<> struct is_integral<signed char> : ft::true_type {};
template<> struct is_integral<const signed char> : ft::true_type {};


/*
** equal implementation
*/
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2) {
    while (first1 != last1) {
        if (!(*first1 == *first2))
            return (false);
        ++first1; ++first2;
    }
  return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal (InputIterator1 first1, InputIterator1 last1,
            InputIterator2 first2, BinaryPredicate pred) {
    while (first1 != last1) {
        if (!pred(*first1,*first2))
            return (false);
        ++first1; ++first2;
    }
  return true;
}

/*
** lexicographical_compare implementation
*/
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2 ) {
        if (*first1 < *first2) return (true);
        if (*first2 < *first1) return (false);
    }
    return (first1 == last1) && (first2 != last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                              InputIterator2 first2, InputIterator2 last2,
                              Compare comp)
{
    for ( ; (first1 != last1) && (first2 != last2); ++first1, (void)++first2 ) {
        if (comp(*first1, *first2)) return (true);
        if (comp(*first2, *first1)) return (false);
    }
    return (first1 == last1) && (first2 != last2);
}

} // namespace brace

#endif