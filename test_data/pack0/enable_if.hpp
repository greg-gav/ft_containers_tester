#ifndef _ENABLE_IF_HPP_
#define _ENABLE_IF_HPP_

namespace ft
{
 /* enable_if */
 template<bool B, class T = void> 
 struct enable_if {};

 template<class T> 
 struct enable_if<true, T> { typedef T type; };

 /* integral_constant */
 template <class T, T v>
 struct integral_constant {
  static const T value = v;
  typedef T value_type;
  typedef integral_constant<T, v> type;
  operator T()const { return v; }
 };

 /* true_type false_type */
 typedef integral_constant<bool, true> true_type;
 typedef integral_constant<bool, false> false_type;
 
 /* is_integral */
 template <class T> struct is_integral : public false_type {};
 template <class T> struct is_integral<const T> : public is_integral<T> {};

 template<> struct is_integral<bool> : public true_type {};
 template<> struct is_integral<char> : public true_type {};
 template<> struct is_integral<char16_t> : public true_type {};
 template<> struct is_integral<char32_t> : public true_type {};
 template<> struct is_integral<wchar_t> : public true_type {};
 template<> struct is_integral<signed char> : public true_type {};
 template<> struct is_integral<short int> : public true_type {};
 template<> struct is_integral<int> : public true_type {};
 template<> struct is_integral<long int> : public true_type {};
 template<> struct is_integral<unsigned char> : public true_type {};
 template<> struct is_integral<unsigned short int> : public true_type {};
 template<> struct is_integral<unsigned int> : public true_type {};
 template<> struct is_integral<unsigned long int> : public true_type {};
}

#endif
