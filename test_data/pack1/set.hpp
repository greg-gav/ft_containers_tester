#ifndef	SET_HPP
# define SET_HPP

#include "ft_templates.hpp"
#include "rb_tree.hpp"

namespace ft
{
	template< class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> >
	class set
	{
		private:
			rb_tree<Key, Compare, Allocator>	_tree;

		public:
			typedef	Key									key_type;
			typedef	Key									value_type;
			typedef	std::size_t							size_type;
			typedef	std::ptrdiff_t						difference_type;
			typedef	Compare								key_compare;
			typedef	Allocator							allocator_type;
			typedef	value_type&							reference;
			typedef	const value_type&					const_reference;
			typedef	typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef typename rb_tree<Key, Compare, Allocator>::iterator					iterator;
			typedef typename rb_tree<Key, Compare, Allocator>::const_iterator			const_iterator;
			typedef	typename rb_tree<Key, Compare, Allocator>::reverse_iterator			reverse_iterator;
			typedef	typename rb_tree<Key, Compare, Allocator>::const_reverse_iterator	const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class set<key_type, key_compare, Allocator>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return (comp(x.first, y.first));
					}
			};

			set() : _tree() {}

			explicit set( const Compare& comp, const Allocator& alloc = Allocator() ) : _tree(comp, alloc) {}

			set( const set& other ) : _tree(other._tree) {}

			template< class InputIt >
			set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
			{
				(void) comp;
				(void) alloc;
				for (; first != last; ++first)
					_tree.insert(*first);
			}

			~set() {}

			set& operator=( const set& other )
			{
				_tree = other._tree;
				return *this;
			}

			allocator_type get_allocator() const
			{
				return _tree.get_allocator();
			}

			bool		empty() const
			{
				return _tree.empty();
			}

			size_type	size() const
			{
				return _tree.size();
			}

			size_type	max_size() const
			{
				return _tree.max_size();
			}

			iterator	begin()
			{
				return _tree.begin();
			}

			const_iterator	begin() const
			{
				return _tree.begin();
			}

			iterator	end()
			{
				return _tree.end();
			}

			const_iterator	end() const
			{
				return _tree.end();
			}

			reverse_iterator		rbegin()
			{
				return _tree.rbegin();
			}
			
			const_reverse_iterator	rbegin() const
			{
				return _tree.rbegin();
			}
			
			reverse_iterator		rend()
			{
				return _tree.rend();
			}
			
			const_reverse_iterator	rend() const
			{
				return _tree.rend();
			}

			pair<iterator,bool> insert( const value_type& value )
			{
				return _tree.insert(value);
			}

			iterator insert( iterator hint, const value_type& value )
			{
				return _tree.insert(hint, value);
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{
				_tree.insert(first, last);
			}

			void erase( iterator pos )
			{
				_tree.erase(pos);
			}

			void erase( iterator first, iterator last )
			{
				_tree.erase(first, last);
			}

			size_type erase( const value_type& key )
			{
				return _tree.erase(key);
			}

			iterator find( const value_type& key )
			{
				return _tree.find(key);
			}

			const_iterator find( const value_type& key ) const
			{
				return _tree.find(key);
			}

			pair<iterator,iterator> equal_range( const value_type& key )
			{
				return _tree.equal_range(key);
			}

			pair<const_iterator,const_iterator> equal_range( const value_type& key ) const
			{
				return _tree.equal_range(key);
			}

			iterator lower_bound( const value_type& key )
			{
				return _tree.lower_bound(key);
			}

			const_iterator lower_bound( const value_type& key ) const
			{
				return _tree.lower_bound(key);
			}

			iterator upper_bound( const value_type& key )
			{
				return _tree.upper_bound(key);
			}

			const_iterator upper_bound( const value_type& key ) const
			{
				return _tree.upper_bound(key);
			}

			void	swap(set & other)
			{
				_tree.swap(other._tree);
			}

			size_type count( const Key& key ) const
			{
				return _tree.find(key) == _tree.end() ? 0 : 1;
			}

			void clear()
			{
				_tree.clear();
			}

			key_compare key_comp() const
			{
				return key_compare();
			}

			value_compare value_comp() const
			{
				return value_compare(key_compare());
			}

	}; // class set

	template<class T, class Compare, class Allocator>
	bool	operator==(const set<T, Compare, Allocator> & lhs, const set<T, Compare, Allocator> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class T, class Compare, class Allocator>
	bool	operator!=(const set<T, Compare, Allocator> & lhs, const set<T, Compare, Allocator> & rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Compare, class Allocator>
	bool	operator<(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
	{
		return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class T, class Compare, class Allocator>
	bool	operator<=(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class T, class Compare, class Allocator>
	bool	operator>(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
	{
		return (rhs < lhs);
	}

	template<class T, class Compare, class Allocator>
	bool	operator>=(const set<T, Compare, Allocator>& lhs, const set<T, Compare, Allocator>& rhs)
	{
		return (!(lhs < rhs));
	}

} // namespace ft

namespace std
{
	template <class T, class Compare, class Allocator>
	void swap( ft::set<T, Compare, Allocator> & lhs, ft::set<T, Compare, Allocator> & rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
