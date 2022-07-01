#ifndef stack_hpp
# define stack_hpp
# include "vector.hpp"

namespace ft
{
	template<typename T, typename K = ft::vector<T> >
	class stack {
	public:
		typedef size_t		size_type;
		typedef T			value_type;
		typedef K			container_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		
	protected:
		container_type container;
		
	public:
		explicit stack(const container_type& container = container_type())
		:container(container) {}
		
		stack(const stack& other)
		:container(other.container) {}

		stack&			operator=(const stack& other)	{ container = other.container; return *this;	}
		bool			empty() const					{ return container.empty();						}
		size_t			size() const					{ return container.size();						}
		reference		top()							{ return container.back();						}
		const_reference top() const 					{ return container.back();						}
		void			push(const_reference val)		{ container.push_back(val);						}
		void 			pop()							{ container.pop_back();							}
		
		template<typename _T, typename _K>
		friend bool operator==	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);

		template<typename _T, typename _K>
		friend bool operator!=	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);

		template<typename _T, typename _K>
		friend bool operator<	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);

		template<typename _T, typename _K>
		friend bool operator<=	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);

		template<typename _T, typename _K>
		friend bool operator>	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);

		template<typename _T, typename _K>
		friend bool operator>=	(const stack<_T, _K>& lhs, const stack<_T, _K>& rhs);
	};

	template<typename T, typename K>
	bool operator==	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container == rhs.container); }

	template<typename T, typename K>
	bool operator!=	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container != rhs.container); }

	template<typename T, typename K>
	bool operator<	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container < rhs.container); }

	template<typename T, typename K>
	bool operator<=	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container <= rhs.container); }

	template<typename T, typename K>
	bool operator>	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container > rhs.container); }

	template<typename T, typename K>
	bool operator>=	(const stack<T, K>& lhs, const stack<T, K>& rhs) { return (lhs.container >= rhs.container); }
}

#endif
