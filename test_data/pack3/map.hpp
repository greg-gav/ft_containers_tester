#ifndef map_hpp
# define map_hpp
# include "RBTree.hpp"
# include "utils.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map {
	public:
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef pair<const Key, T>									value_type;
		typedef std::size_t											size_type;
		typedef std::ptrdiff_t										difference_type;
		typedef Compare												key_compare;
		typedef Allocator											allocator_type;
		typedef const value_type&									reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;

	private:
		class value_compare {
		public:
			value_compare(const key_compare& compare)
			:_compare(compare) {}
			
			bool operator()(const value_type& lhs, const value_type& rhs) const {
				return _compare(lhs.first, rhs.first);
			}
		private:
			key_compare _compare;
		};
		
	public:
		typedef RBTree<value_type, value_compare, allocator_type>	tree_type;
		typedef typename tree_type::iterator						iterator;
		typedef typename tree_type::const_iterator					const_iterator;
		typedef typename tree_type::reverse_iterator				reverse_iterator;
		typedef typename tree_type::const_reverse_iterator			const_reverse_iterator;
		
	public:
		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:_alloc(alloc),
		_tree(tree_type(comp, alloc)),
		_compare(comp) {}

		template<class InputIt>
		map(InputIt first, InputIt last, const Compare& compare = Compare(), const Allocator& alloc = Allocator())
		:_alloc(alloc),
		_tree(first, last, compare, _alloc),
		_compare(compare) {}
		
		allocator_type							get_allocator() const									{ return _tree.get_allocator(); }
	
		/* Element access */
		T&										at(const Key& key) {
			iterator res = _tree.find(ft::make_pair(key, mapped_type()));
			if (res == _tree.end())
				throw std::out_of_range("map::at: key not found");
			return res->second;
		}
		const T&								at(const Key& key) const {
			const_iterator res = _tree.find(ft::make_pair(key, mapped_type()));
			if (res == _tree.end())
				throw std::out_of_range("map::at: key not found");
			return res->second;
		}
		mapped_type&							operator[](const key_type& key) {
			return insert(make_pair(key, mapped_type())).first->second;
		}
		
		/* Observers */
		value_compare							value_comp() const										{ return _tree.value_comp();	}
		key_compare								key_comp() const										{ return _compare;				}
		/* Iterators */
		iterator								begin()													{ return _tree.begin();			}
		iterator								end()													{ return _tree.end();			}
		reverse_iterator						rbegin()												{ return _tree.rbegin();		}
		reverse_iterator						rend()													{ return _tree.rend();			}
		/* Capacity */
		bool									empty() const											{ return _tree.empty();			}
		size_type								size() const											{ return _tree.size();			}
		size_type								max_size() const										{ return _tree.max_size();		}
		/* Modifiers */
		void									clear()													{ _tree.clear();				}
		pair<iterator, bool>					insert(const value_type& value)							{ return _tree.insert(value);	}
		iterator								insert(iterator hint, const value_type& value)			{ return _tree.insert(hint, value); }
		template<class InputIt>
		void									insert(typename enable_if<!is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
			_tree.insert(first, last);
		}
		void 									erase(iterator pos)						{ _tree.erase(pos); }
		size_type								erase(const Key& key)					{ return _tree.erase(make_pair(key, mapped_type())); }
		void									erase(iterator first, iterator last)	{ _tree.erase(first, last); }
		void									swap(map& other)						{ std::swap(this->_compare, other._compare); _tree.swap(other._tree); }
		/* Lookup */
		size_type								count(const Key& key) const				{ return _tree.count(make_pair(key, mapped_type()));		}
		iterator								find(const Key& key)					{ return _tree.find(make_pair(key, mapped_type()));			}
		iterator								lower_bound(const key_type& key)		{ return _tree.lower_bound(make_pair(key, mapped_type()));	}
		const_iterator							lower_bound(const key_type& key) const	{ return _tree.lower_bound(make_pair(key, mapped_type()));	}
		iterator								upper_bound(const key_type& key)		{ return _tree.upper_bound(make_pair(key, mapped_type()));	}
		const_iterator							upper_bound(const key_type& key) const	{ return _tree.upper_bound(make_pair(key, mapped_type()));	}
		pair<iterator, iterator> 				equal_range(const key_type& key)		{ return _tree.equal_range(make_pair(key, mapped_type()));	}
		pair<const_iterator, const_iterator>	equal_range(const key_type& key) const	{ return _tree.equal_range(make_pair(key, mapped_type()));	}

		template<class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator==(const map<_Key, _T, _Compare, _Alloc>& lhs,
				const map<_Key, _T, _Compare, _Alloc>& rhs);

		template<class _Key, class _T, class _Compare, class _Alloc>
		friend bool operator<(const map<_Key, _T, _Compare, _Alloc>& lhs,
				const map<_Key, _T, _Compare, _Alloc>& rhs);
	
	private:
		allocator_type	_alloc;
		tree_type		_tree;
		key_compare		_compare;
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (lhs._tree == rhs._tree); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (lhs._tree < rhs._tree); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (rhs < lhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs > rhs); }

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs < rhs); }

	template<class Key, class T, class Compare, class Alloc>
	void swap(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { lhs.swap(rhs); }
}

#endif /* map_h */
