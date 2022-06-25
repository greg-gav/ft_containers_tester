#ifndef FT_TEMPLATES_HPP
# define FT_TEMPLATES_HPP

# include <iterator>

namespace ft
{
	template< class Iter >
	struct iterator_traits
	{
		typedef Iter	iterator_type;
		typedef typename Iter::difference_type			difference_type;
		typedef typename Iter::value_type				value_type;
		typedef typename Iter::pointer					pointer;
		typedef typename Iter::reference				reference;
		typedef typename Iter::iterator_category		iterator_category;
	};

	template< class T >
	struct iterator_traits< T* >
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< class T >
	struct iterator_traits< const T* >
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	template< class Category, class T, class Distance = std::ptrdiff_t,
		class Pointer = T*, class Reference = T& >
	struct iterator
	{
		typedef Category	iterator_category;	
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	template< class T >
	struct is_iterator
	{
		private:
			template< class C >
			static typename C::iterator_category f(int)
			{
				return C::iterator_category();
			}
			
			template< class C >
			static double	f(...)
			{
				return 0;
			}

		public:
			static const bool value = sizeof(f< T >(1)) != sizeof(double);
	};

	template< class T >
	struct is_iterator< T* >
	{
		static const bool value = true;
	};

	template< class Iter, class category = typename iterator_traits<Iter>::iterator_category>
	class reverse_iterator
	{
		public:
			typedef	Iter 	iterator_type;
			typedef	typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef	typename iterator_traits<Iter>::value_type			value_type;
			typedef	typename iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename iterator_traits<Iter>::pointer				pointer;
			typedef	typename iterator_traits<Iter>::reference			reference;

			reverse_iterator() : _iter() {}

			explicit reverse_iterator (iterator_type it) : _iter(it) {}
			
			reverse_iterator(const reverse_iterator & other) : _iter(other._iter) {}

			~reverse_iterator() {}

			iterator_type base() const
			{
				return (_iter);
			}

			reference operator*() const
			{
				iterator_type tmp = _iter;
				return (*(--tmp));
			}

			reverse_iterator& operator++()
			{
				--_iter;
				return (*this);
			}
			
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator--()
			{
				++_iter;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			
			pointer operator->() const
			{
				return &(operator*());
			}
			
			friend	bool operator==(reverse_iterator lhs, reverse_iterator rhs)
			{
				return lhs._iter == rhs._iter;
			}
			
			friend	bool operator!=(reverse_iterator lhs, reverse_iterator rhs)
			{
				return lhs._iter != rhs._iter;
			}

		private:
			iterator_type	_iter;
	};

	template< class Iter >
	class reverse_iterator< Iter, std::random_access_iterator_tag >
	{
		public:
			typedef	Iter 	iterator_type;
			typedef	typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef	typename iterator_traits<Iter>::value_type			value_type;
			typedef	typename iterator_traits<Iter>::difference_type		difference_type;
			typedef	typename iterator_traits<Iter>::pointer				pointer;
			typedef	typename iterator_traits<Iter>::reference			reference;

			reverse_iterator() : _iter() {}

			explicit reverse_iterator (iterator_type it) : _iter(it) {}
			
			reverse_iterator(const reverse_iterator & other) : _iter(other._iter) {}
			
			~reverse_iterator() {}

			iterator_type base() const
			{
				return (_iter);
			}

			reference operator*() const
			{
				iterator_type tmp = _iter;
				return (*(--tmp));
			}

			reverse_iterator operator+ (difference_type n) const
			{
				return (reverse_iterator(_iter - n));
			}

			reverse_iterator& operator++()
			{
				--_iter;
				return (*this);
			}
			
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator& operator+= (difference_type n)
			{
				_iter -= n;
				return (*this);
			}
			
			reverse_iterator operator- (difference_type n) const
			{
				return (reverse_iterator(_iter + n));
			}

			reverse_iterator& operator--()
			{
				++_iter;
				return (*this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}
			
			reverse_iterator& operator-= (difference_type n)
			{
				_iter += n;
				return (*this);
			}

			pointer operator->() const
			{
				return &(operator*());
			}
			
			reference operator[] (difference_type n) const
			{
				return (this->base()[-n - 1]);
			}
			
			friend	bool operator==(reverse_iterator lhs, reverse_iterator rhs)
			{
				return lhs._iter == rhs._iter;
			}
			
			friend	bool operator!=(reverse_iterator lhs, reverse_iterator rhs)
			{
				return lhs._iter != rhs._iter;
			}

		private:
			iterator_type	_iter;
	};

	template< class T >
	const T&	min( const T& a, const T& b )
	{
		if (a< b)
			return a;
		return b;
	}

	template< class T >
	void	swap(T & a, T & b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template< bool B, class T =  void > 
	struct enable_if
	{
	};
	
	template< class T > 
	struct enable_if< true , T >
	{
		typedef T type;
	};

	template< class T, bool v >
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const
		{
			return value;
		}
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template< class T > struct is_integral : public false_type{};

	template<> struct is_integral<bool> : public true_type{};
	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<signed char> : true_type{};
	template<> struct is_integral<unsigned char> : public true_type{};
	template<> struct is_integral<wchar_t> : public true_type{};
	template<> struct is_integral<char16_t> : public true_type{};
	template<> struct is_integral<short> : public true_type{};
	template<> struct is_integral<unsigned short> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<long> : public true_type{};
	template<> struct is_integral<unsigned long> : public true_type{};
	template<> struct is_integral<long long> : public true_type{};
	template<> struct is_integral<unsigned long long> : public true_type{};

	// Return value
	// true if all the elements in the range [first1,last1) compare equal  
	// to those of the range starting at first2, and false otherwise.
	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p )
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}

	// Return value
	// true if the first range is lexicographically less than the second.
	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) 
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
			InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2) 
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	template< class T1, class T2 >
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		
		T1	first;
		T2	second;
		
		pair() : first(), second() {}
		pair(const T1& x, const T2& y) : first(x), second(y) {}
		
		template< class U1, class U2 >
		pair(const pair< U1, U2 >& p) : first(p.first), second(p.second) {}
	};

	template< class T1, class T2 >
	pair< T1,T2 > make_pair(T1 t, T2 u)
	{
		return pair<T1, T2>(t, u);
	}

	template< class Key, class T, class Compare >
	struct compare_pair
	{
		bool operator()(const ft::pair< const Key, T > & first, const ft::pair< const Key, T > & second) const
		{
			return Compare()(first.first, second.first);
		}
	};

	template< class T1, class T2 >
	bool operator==( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
	{
		return !(lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator<( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
	{
		return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
	}

	template< class T1, class T2 >
	bool operator<=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
	{
		return !(lhs > rhs);
	}

	template< class T1, class T2 >
	bool operator>( const pair< T1,T2 >& lhs, const pair< T1,T2 >& rhs )
	{
		return (rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
	{
		return !(lhs < rhs);
	}

} // namespace ft

# endif
