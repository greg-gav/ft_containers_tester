#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> > 
	class stack
	{
		protected:
			Container	_container;
		
		public:
			typedef typename Container::value_type		value_type;
			typedef Container							container_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

			// https://en.cppreference.com/w/cpp/container/stack
			// Member functions
			explicit stack( const Container& cont = Container() ) : _container(cont) {}

			stack( const stack & other ) : _container(other._container) {}

			~stack() {}

			stack & operator=( stack const & other )
			{
				_container = other._container;
				return *this;
			}

			// Element access
			reference top()
			{
				return _container.back();
			}

			const_reference top() const
			{
				return _container.back();
			}

			// Capacity
			bool	empty() const
			{
				return _container.empty();
			}

			size_type size() const
			{
				return _container.size();
			}

			// Modifiers
			void push(const value_type& val)
			{
				_container.push_back(val);
			}

			void pop()
			{
				_container.pop_back();
			}

			// Non-member functions
			friend bool operator== (const stack & lhs, const stack & rhs)
			{
				return lhs._container == rhs._container;
			}

			friend bool operator!= (const stack & lhs, const stack & rhs)
			{
				return lhs._container != rhs._container;
			}

			friend bool operator< (const stack & lhs, const stack & rhs)
			{
				return lhs._container < rhs._container;
			}

			friend bool operator<= (const stack & lhs, const stack & rhs)
			{
				return lhs._container <= rhs._container;
			}

			friend bool operator> (const stack<T,Container>& lhs, const stack & rhs)
			{
				return lhs._container > rhs._container;
			}

			friend bool operator>= (const stack & lhs, const stack & rhs)
			{
				return lhs._container >= rhs._container;
			}
	};
} // namespace ft

#endif
