#ifndef MAP_HPP
# define MAP_HPP

# include "ft_templates.hpp"
# include "rb_tree.hpp"

namespace ft
{
	template< class Key, class T, class Compare = std::less<Key>,
		class Allocator = std::allocator< std::pair<const Key, T > > >
	class map
	{
		public:
			typedef Key								key_type;
			typedef T								mapped_type;
			typedef pair<const Key, T>				value_type;
			typedef std::size_t						size_type;
			typedef std::ptrdiff_t					difference_type;
			typedef compare_pair<Key, T, Compare>	pair_compare;
			typedef	Compare							key_compare;
			typedef Allocator						allocator_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef rb_tree_Iterator<pair<const Key, T> >		iterator;
			typedef rb_tree_ConstIterator<pair<const Key, T> >	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, value_type, key_compare, Allocator>;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					bool operator() (const value_type& x, const value_type& y) const
					{
						return (comp(x.first, y.first));
					}
			};

		private:
			rb_tree< pair< const Key, T >, pair_compare, Allocator >	_tree;

		public:
			map() : _tree() {}

			explicit map( const Compare& comp, const Allocator& alloc = Allocator() )
					: _tree(comp, alloc) {}
			
			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(),
				const Allocator& alloc = Allocator() )
			{
				(void)	comp;
				(void)	alloc;
				for (; first != last; ++first)
					_tree.insert(*first);
			}

			map( const map& other ) : _tree(other._tree) {}

			~map() {}

			map& operator=( const map& other )
			{
				_tree = other._tree;
				return *this;
			}
			
			allocator_type get_allocator() const
			{
				return _tree.get_allocator();
			}

			T& at( const Key& key )
			{
				iterator	it = find(key);
				if (it == end())
					throw std::out_of_range("map");
				return	it->second;
			}
			
			const T& at( const Key& key ) const
			{
				const_iterator	it = find(key);
				if (it == end())
					throw std::out_of_range("map");
				return	it->second;
			}

			T& operator[]( const Key& key )
			{
				pair<iterator, bool>	it = insert(ft::make_pair(key, T()));
				return	(it.first)->second;
			}

			bool empty() const
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

			iterator end()
			{
				return _tree.end();
			}

			const_iterator	end() const
			{
				return _tree.end();
			}

			reverse_iterator rbegin()
			{
				return _tree.rbegin();
			}
			
			const_reverse_iterator	rbegin() const
			{
				return _tree.rbegin();
			}
			
			reverse_iterator rend()
			{
				return _tree.rend();
			}
			
			const_reverse_iterator	rend() const
			{
				return _tree.rend();
			}

			void clear()
			{
				_tree.clear();
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

			size_type erase( const Key& key )
			{
				return _tree.erase(ft::make_pair(key, T()));
			}

			void	swap(map & other)
			{
				_tree.swap(other._tree);
			}

			size_type count( const Key& key ) const
			{
				return _tree.find(make_pair(key, T())) == _tree.end() ? 0 : 1;
			}

			iterator find( const Key& key )
			{
				return _tree.find(ft::make_pair(key, T()));
			}

			const_iterator find( const Key& key ) const
			{
				return _tree.find(ft::make_pair(key, T()));
			}

			pair<iterator,iterator> equal_range( const Key& key )
			{
				return _tree.equal_range(make_pair(key, T()));
			}

			pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				return _tree.equal_range(make_pair(key, T()));
			}

			iterator lower_bound( const Key& key )
			{
				return _tree.lower_bound(make_pair(key, T()));
			}

			const_iterator lower_bound( const Key& key ) const
			{
				return _tree.lower_bound(make_pair(key, T()));
			}

			iterator upper_bound( const Key& key )
			{
				return _tree.upper_bound(make_pair(key, T()));
			}

			const_iterator upper_bound( const Key& key ) const
			{
				return _tree.upper_bound(make_pair(key, T()));
			}

			key_compare key_comp() const
			{
				return key_compare();
			}

			value_compare value_comp() const
			{
				return value_compare(key_compare());
			}
	};

	template< class Key, class T, class Compare, class Allocator >
	bool operator==(const map<Key, T, Compare, Allocator> & lhs,
		const map<Key, T, Compare, Allocator> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator!=(const map<Key, T, Compare, Allocator> & lhs,
		const map<Key, T, Compare, Allocator> & rhs)
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator<(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator>(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Allocator >
	bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
		const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}
} // namespace ft

namespace std
{
	template< class Key, class T, class Compare, class Allocator >
	void swap( ft::map<Key, T, Compare, Allocator> & lhs,
		ft::map<Key, T, Compare, Allocator> & rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
