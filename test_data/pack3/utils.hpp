#ifndef utils_hpp
# define utils_hpp

namespace ft
{
	template <bool B, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T> { typedef T type; };

	template <class T, class U>
	struct is_same { static const bool value = false; };

	template <class T>
	struct is_same<T, T> { static const bool value = true; };

	template<bool B, class T>
	struct conditional2 { typedef const T type; };
	 
	template<class T>
	struct conditional2<false, T> { typedef T type; };

	template <bool B, class T = void, class U = void>
	struct conditional {};

	template <class T, class U>
	struct conditional<true, T, U> { typedef T type; };

	template <class T, class U>
	struct conditional<false, T, U> { typedef U type; };


	/* ------	PAIR	------*/

	template <class T1, class T2>
	struct pair {
		typedef			T1			first_type;
		typedef			T2			second_type;

		pair(void)
		:first(first_type()),
		second(second_type()) {}
		
		template <class U, class V>
		pair(const pair<U,V>& pr)
		:first(pr.first),
		second(pr.second) {}
		
		pair(const first_type& a, const second_type& b)
		:first(a),
		second(b) {}

		first_type		first;
		second_type		second;
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair (T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs == rhs)); }

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(rhs < lhs)); }

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return (!(lhs < rhs)); }


	/* ------	SWAP	------*/

	template <class T>
	void swap (T& a, T& b)
	{
		T	tmp(a);
		a = b;
		b = tmp;
	}

	/* ------	COMPARE	------*/

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit < *lit)
				return (false);
			else if (*lit < *rit)
				return (true);
			++lit, ++rit;
		}

		return (rit != rend);
	}

	template <class T>
	bool lexicographical_compare (T & a, T & b)
	{
		return (a < b);
	}


	/* ------	EQUAL	------*/

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}

	template <class InputIterator1, class InputIterator2>
	  bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
	  while (first1!=last1) {
		if (!(*first1 == *first2))
		  return false;
		++first1; ++first2;
	  }
	  return true;
	}

	template <class T>
	bool equal (T & a, T & b)
	{
		return (a == b);
	}

	template<class T, bool v>
	struct integral_constant {
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const { return value; }
	};

	/* ------	IS_INTEGRAL	------*/

	template <class T> struct is_integral				: public ft::integral_constant<T, false> {};
	template <> struct is_integral<bool>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<signed char>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned char>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<wchar_t>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<char16_t>			: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<short>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned short>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<int>					: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned int>		: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<long>				: public ft::integral_constant<bool, true> {};
	template <> struct is_integral<unsigned long> 		: public ft::integral_constant<bool, true> {};
//	template <> struct is_integral<long long>			: public ft::integral_constant<bool, true> {};
//	template <> struct is_integral<unsigned long long> 	: public ft::integral_constant<bool, true> {};


	/* ------	IS_CONST ITERATOR	------*/

	template<typename T>
	struct is_const_pointer { static const bool value = false; };

	template<typename T>
	struct is_const_pointer<const T*> { static const bool value = true; };

	template <typename T>
	struct iterator_traits;
	template <typename TIterator>
	struct is_const_iterator
	{
		typedef typename iterator_traits<TIterator>::pointer pointer;
		static const bool value = is_const_pointer<pointer>::value;
	};

	/* ------	REMOVE_CONST	------*/

	template <typename T>
	struct remove_const
	{
		typedef T type;
	};
	template <typename T>
	struct remove_const<const T>
	{
		typedef T type;
	};
}

#endif
